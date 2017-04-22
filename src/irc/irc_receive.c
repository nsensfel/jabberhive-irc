#include <string.h>

#include <libircclient/libircclient.h>

#include "../meta_net/meta_net.h"

#include "irc.h"
#include "irc_event_handlers.h"

void JH_irc_handle_channel_message_event
(
   irc_session_t * session,
   const char * event,
   const char * origin,
   const char ** params,
   unsigned int count
)
{
   struct JH_irc * irc;

   irc = (struct JH_irc *) irc_get_ctx(session);

   JH_meta_net_handle_user_message
   (
      irc->jh_net,
      params[1],
      strlen(params[1])
   );
}

void JH_irc_handle_ctcp_action_event
(
   irc_session_t * session,
   const char * event,
   const char * origin,
   const char ** params,
   unsigned int count
)
{
   struct JH_irc * irc;

   irc = (struct JH_irc *) irc_get_ctx(session);

   JH_meta_net_handle_user_action
   (
      irc->jh_net,
      params[0],
      strlen(params[0])
   );
}
