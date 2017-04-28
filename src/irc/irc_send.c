#include <libircclient/libircclient.h>

#include "../pervasive.h"

#include "../parameters/parameters.h"

#include "../error/error.h"

#include "irc.h"

int JH_irc_send_message
(
   struct JH_irc irc [const restrict static 1],
   const char msg [const restrict static 1]
)
{
   if
   (
      irc_cmd_msg
      (
         irc->session,
         JH_parameters_get_irc_channel(irc->params),
         msg
      )
      != 0
   )
   {
      JH_ERROR
      (
         stderr,
         "[IRC] Unable to send message: %s.",
         irc_strerror(irc_errno(irc->session))
      );

      /* TODO: what to do in case of failure? */

      return -1;
   }

   if (JH_parameters_get_print_chat(irc->params))
   {
      printf
      (
         "[CHAT] <%s> %s\n",
         JH_parameters_get_irc_nick(irc->params),
         msg
      );
   }

   return 0;
}

int JH_irc_send_action
(
   struct JH_irc irc [const restrict static 1],
   const char msg [const restrict static 1]
)
{
   if
   (
      irc_cmd_me
      (
         irc->session,
         JH_parameters_get_irc_channel(irc->params),
         msg
      )
      != 0
   )
   {
      JH_ERROR
      (
         stderr,
         "[IRC] Unable to send emote: %s.",
         irc_strerror(irc_errno(irc->session))
      );

      /* TODO: what to do in case of failure? */

      return -1;
   }

   if (JH_parameters_get_print_chat(irc->params))
   {
      printf
      (
         "[CHAT] *%s %s*\n",
         JH_parameters_get_irc_nick(irc->params),
         msg
      );
   }

   return 0;
}
