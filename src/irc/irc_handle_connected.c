#include <libircclient/libircclient.h>

#include "../error/error.h"

#include "../parameters/parameters.h"

#include "irc.h"
#include "irc_event_handlers.h"

void JH_irc_handle_connected_event
(
   irc_session_t * session,
   __attribute__((unused)) const char * event,
   __attribute__((unused)) const char * origin,
   __attribute__((unused)) const char ** params,
   __attribute__((unused)) unsigned int count
)
{
   struct JH_irc * irc;

   irc = (struct JH_irc *) irc_get_ctx(session);

   JH_S_DEBUG(stderr, 1, "[IRC] Connected.");

   if
   (
      irc_cmd_join
      (
         session,
         JH_parameters_get_irc_channel(irc->params),
         0
      )
      != 0
   )
   {
      JH_ERROR
      (
         stderr,
         "[IRC] Unable to join: %s",
         irc_strerror(irc_errno(session))
      );
   }
}
