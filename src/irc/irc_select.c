#include <libircclient/libircclient.h>
#include <unistd.h>

#include "../error/error.h"

#include "irc.h"

int JH_irc_pre_select
(
   struct JH_irc irc [const restrict static 1],
   fd_set in [const restrict static 1],
   fd_set out [const restrict static 1],
   int max_fd [const restrict static 1]
)
{
   while (!irc_is_connected(irc->session))
   {
      JH_S_ERROR(stderr, "[IRC] Not connected.");

      /* TODO: reconnect or fail. */
      if (JH_irc_connect(irc) != 0)
      {
         JH_ERROR
         (
            stderr,
            "[IRC] Failed to connect: %s.",
            irc_strerror(irc_errno(irc->session))
         );

      }
      sleep(10);
   }

   if (irc_add_select_descriptors(irc->session, in, out, max_fd) != 0)
   {
      JH_ERROR
      (
         stderr,
         "[IRC] Failed to add file descriptors to select: %s.",
         irc_strerror(irc_errno(irc->session))
      );

      return -1;
   }

   return 0;
}

int JH_irc_post_select
(
   struct JH_irc irc [const restrict static 1],
   fd_set in [const restrict static 1],
   fd_set out [const restrict static 1]
)
{
   if (irc_process_select_descriptors(irc->session, in, out) != 0)
   {
      /* TODO: reconnect or fail. */
      JH_ERROR
      (
         stderr,
         "[IRC] Failed select file descriptors: %s.",
         irc_strerror(irc_errno(irc->session))
      );

      return -1;
   }

   return 0;
}
