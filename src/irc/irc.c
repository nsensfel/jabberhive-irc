#include <libircclient/libircclient.h>

#include <string.h>

#include "../error/error.h"

#include "../parameters/parameters.h"

#include "irc.h"
#include "irc_event_handlers.h"

int JH_irc_initialize
(
   struct JH_irc irc [const restrict static 1],
   const struct JH_parameters params [const restrict static 1],
   struct JH_meta_net jh_net [const restrict static 1]
)
{
   memset((void *) &(irc->callbacks), 0, sizeof(irc_callbacks_t));

   irc->callbacks.event_connect     = JH_irc_handle_connected_event;
   irc->callbacks.event_join        = JH_irc_do_nothing;
   irc->callbacks.event_nick        = JH_irc_do_nothing;
   irc->callbacks.event_quit        = JH_irc_do_nothing;
   irc->callbacks.event_part        = JH_irc_do_nothing;
   irc->callbacks.event_mode        = JH_irc_do_nothing;
   irc->callbacks.event_topic       = JH_irc_do_nothing;
   irc->callbacks.event_kick        = JH_irc_do_nothing;
   irc->callbacks.event_channel     = JH_irc_handle_channel_message_event;
   irc->callbacks.event_privmsg     = JH_irc_do_nothing;
   irc->callbacks.event_notice      = JH_irc_do_nothing;
   irc->callbacks.event_invite      = JH_irc_do_nothing;
   irc->callbacks.event_umode       = JH_irc_do_nothing;

   irc->callbacks.event_ctcp_rep    = JH_irc_do_nothing;
   irc->callbacks.event_ctcp_action = JH_irc_handle_ctcp_action_event;
   irc->callbacks.event_unknown     = JH_irc_do_nothing;
   irc->callbacks.event_numeric     = JH_irc_handle_numeric_event;

   irc->callbacks.event_dcc_chat_req = JH_irc_handle_dcc_chat_req_event;
   irc->callbacks.event_dcc_send_req = JH_irc_handle_dcc_send_req_event;

   irc->session = irc_create_session(&(irc->callbacks));
   irc_set_ctx(irc->session, (void *) irc);

   irc->params = params;
   irc->jh_net = jh_net;

   if (!(irc->session))
   {
      JH_S_FATAL(stderr, "Unable to create IRC session.");

      return -1;
   }

   return 0;
}

int JH_irc_connect (struct JH_irc irc [const restrict static 1])
{
   if (JH_parameters_get_irc_is_ipv6(irc->params))
   {
      if
      (
         irc_connect6
         (
            irc->session,
            JH_parameters_get_irc_server(irc->params),
            JH_parameters_get_irc_port(irc->params),
            JH_parameters_get_irc_password(irc->params),
            JH_parameters_get_irc_nick(irc->params),
            JH_parameters_get_irc_username(irc->params),
            JH_parameters_get_irc_realname(irc->params)
         ) != 0
      )
      {
         JH_FATAL
         (
            stderr,
            "[IRC] Unable to attempt connection (IPv6): %s.\n",
            irc_strerror(irc_errno(irc->session))
         );

         return -1;
      }
   }
   else
   {
      if
      (
         irc_connect
         (
            irc->session,
            JH_parameters_get_irc_server(irc->params),
            JH_parameters_get_irc_port(irc->params),
            JH_parameters_get_irc_password(irc->params),
            JH_parameters_get_irc_nick(irc->params),
            JH_parameters_get_irc_username(irc->params),
            JH_parameters_get_irc_realname(irc->params)
         ) != 0
      )
      {
         JH_FATAL
         (
            stderr,
            "[IRC] Unable to attempt connection: %s.\n",
            irc_strerror(irc_errno(irc->session))
         );

         return -1;
      }
   }

   return 0;
}

void JH_irc_finalize (struct JH_irc irc [const restrict static 1])
{
   /* TODO */
}

void JH_irc_do_nothing
(
   irc_session_t * session,
   const char * event,
   const char * origin,
   const char ** params,
   unsigned int count
)
{
}

void JH_irc_handle_numeric_event
(
   irc_session_t * session,
   unsigned int event,
   const char * origin,
   const char ** params,
   unsigned int count
)
{
}

int JH_irc_test_connection
(
   struct JH_irc irc [const restrict static 1]
)
{
   if
   (
      irc_cmd_topic
      (
         irc->session,
         JH_parameters_get_irc_channel(irc->params),
         (const char *) NULL
      )
      != 0
   )
   {
      JH_S_ERROR(stderr, "Could not request IRC topic to test connection.");

      return -1;
   }

   JH_S_DEBUG(stdout, 1, "Testing connection...");

   return 0;
}
