#include <libircclient/libircclient.h>

#include "../pervasive.h"

#include "../parameters/parameters.h"

#include "irc.h"

int JH_irc_send_message
(
   struct JH_irc irc [const restrict static 1],
   const char msg [const restrict static 1]
)
{
   if (JH_IS_PREFIX("/me ", msg))
   {
      /* TODO: what to do in case of failure? */
      (void) irc_cmd_me
      (
         irc->session,
         JH_parameters_get_irc_channel(irc->params),
         (msg + 4)
      );
   }
   else
   {
      /* TODO: what to do in case of failure? */
      (void) irc_cmd_msg
      (
         irc->session,
         JH_parameters_get_irc_channel(irc->params),
         msg
      );
   }

   return 0;
}

