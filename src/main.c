/* According to POSIX.1-2001, POSIX.1-2008 */
#include <sys/select.h>

#include <stdio.h>

#include "error/error.h"

#include "parameters/parameters.h"

#include "irc/irc.h"

#include "meta_net/meta_net.h"

#include "pervasive.h"

static void print_help (const char runnable [const restrict static 1])
{
   printf
   (
      "JabberHive - IRC Gateway\n"
      "Software Version %d\n"
      "Protocol Version %d\n"
      "\nUsages:\n"
      "   GATEWAY:\t%s SOCKET_NAME IRC_SERVER IRC_NICK IRC_CHANNEL IRC_PORT"
      " [OPTIONS]\n"
      "   SHOW HELP:\tAnything else.\n"
      "\nParameters:\n"
      "   SOCKET_NAME:\tValid UNIX socket.\n"
      "   IRC_SERVER:\tAddress of the IRC server. Prefixing with '#' will"
      " enable SSL.\n"
      "   IRC_NICK:\tIRC nick to be used.\n"
      "   IRC_CHANNEL:\tIRC channel to connect to.\n"
      "   IRC_PORT:\tPort to use for the IRC connection.\n"
      "\nOptions:\n"
      "   -6, --ipv6:\tEnables IPv6.\n"
/*
      "   -l, --request-pipelining:\tRequests the JabberHive pipelining mode.\n"
*/
      "   -c, --print-chat:\tDisplays IRC conversations on stdout.\n"
      "   -i, --print-additional-info:\tDisplays received JH info messages on"
      " stdout.\n"
      "   -u USERNAME, --username USERNAME:\tSets the IRC username.\n"
      "   -r REALNAME, --realname REALNAME:\tSets the IRC realname.\n"
      "   -p PASSWORD, --password PASSWORD:\tSets the IRC password.\n",
      JH_PROGRAM_VERSION,
      JH_PROTOCOL_VERSION,
      runnable
   );
}

static int initialize
(
   struct JH_irc irc [const restrict static 1],
   struct JH_meta_net socket [const restrict static 1],
   struct JH_parameters params [const restrict static 1],
   const int argc,
   const char * argv [const static argc]
)
{
   if (JH_parameters_initialize(params, argc, argv) < 0)
   {
      print_help(argv[0]);

      return -1;
   }

   JH_meta_net_initialize(socket);

   if (JH_irc_initialize(irc, params, socket) < 0)
   {
      JH_meta_net_finalize(socket);

      return -1;
   }

   return 0;
}

static int connect_all
(
   struct JH_irc irc [const restrict static 1],
   struct JH_meta_net socket [const restrict static 1],
   struct JH_parameters params [const restrict static 1]
)
{
   if (JH_meta_net_connect(socket, params) < 0)
   {
      return -1;
   }

   if (JH_irc_connect(irc) < 0)
   {
      return -1;
   }

   return 0;
}

static int event_handling_loop
(
   struct JH_irc irc [const restrict static 1],
   struct JH_meta_net socket [const restrict static 1],
   struct JH_parameters params [const restrict static 1]
)
{
   struct timeval tv;
   fd_set in_set, out_set;
   int fd_max, error;
   int timeouts;

   timeouts = 0;

   for (;;)
   {

      tv.tv_usec = 250000;
      tv.tv_sec = 0;

      FD_ZERO(&in_set);
      FD_ZERO(&out_set);

      fd_max = 0;

      if (JH_irc_pre_select(irc, &in_set, &out_set, &fd_max) < 0)
      {
         JH_meta_net_finalize(socket);

         return -1;
      }

      if
      (
         JH_meta_net_pre_select
         (
            socket,
            &in_set,
            &out_set,
            &fd_max
         ) < 0
      )
      {
         JH_irc_finalize(irc);

         return -1;
      }

      error =
         select
         (
            (fd_max + 1),
            &in_set,
            &out_set,
            (fd_set *) NULL,
            &tv
         );

      if (error < 0)
      {
         JH_ERROR
         (
            stderr,
            "Unable to select the sockets: %s.",
            strerror(error)
         );
      }
      else if (error == 0)
      {
         timeouts += 1;

         /* 1200 timeouts => 5min */
         if (timeouts >= 1200)
         {
            if (JH_irc_is_testing_connection(irc))
            {
               JH_S_ERROR
               (
                  stderr,
                  "Timed out due to lack of response to connection test."
               );

               JH_irc_finalize(irc);

               return -1;
            }
            else if (JH_irc_start_connection_test(irc) < 0)
            {
               JH_S_ERROR(stderr, "Timed out due to failed connection test.");

               JH_irc_finalize(irc);

               return -1;
            }

            timeouts = 0;
         }
      }
      else
      {
         timeouts = 0;
      }

      if (JH_irc_post_select(irc, &in_set, &out_set) < 0)
      {
         JH_meta_net_finalize(socket);

         return -1;
      }

      if
      (
         JH_meta_net_post_select
         (
            socket,
            &in_set,
            &out_set
         ) < 0
      )
      {
         JH_irc_finalize(irc);

         return -1;
      }

      JH_meta_net_handle_reply
      (
         socket,
         irc,
         params
      );
   }

   return 0;
}

int main (const int argc, const char * argv [const static argc])
{
   struct JH_parameters params;
   struct JH_meta_net socket;
   struct JH_irc irc;

   if (initialize(&irc, &socket, &params, argc, argv) < 0)
   {
      return -1;
   }

   if (connect_all(&irc, &socket, &params) < 0)
   {
      JH_irc_finalize(&irc);
      JH_meta_net_finalize(&socket);

      return -1;
   }

   return event_handling_loop(&irc, &socket, &params);
}
