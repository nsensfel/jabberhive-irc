#include "../error/error.h"

#include "../irc/irc.h"
#include "../parameters/parameters.h"

#include "meta_net.h"

void JH_meta_net_handle_reply
(
   struct JH_meta_net socket [const restrict static 1],
   struct JH_irc irc [const restrict static 1],
   const struct JH_parameters params [const restrict static 1]
)
{
   if (socket->in.index == 0)
   {
      /* No reply to handle. */
      return;
   }

   socket->in.data[socket->in.index] = '\0';

   if (JH_IS_PREFIX("!CPV ", socket->in.data))
   {
   }
   else if (JH_IS_PREFIX("!CPS ", socket->in.data))
   {
   }
   else if (JH_IS_PREFIX("!GR ", socket->in.data))
   {
      /* TODO: /me vs message should be handled prior to this. */
      JH_irc_send_message(irc, (socket->in.data + 4));

      JH_DEBUG
      (
         stderr,
         /* TODO: Parameter dependent behavior. */
         JH_DEBUG_DISPLAY_IRC_MSG_EXCHANGES,
         "<%s> %s",
         JH_parameters_get_irc_nick(params),
         (socket->in.data + 4)
      );
   }
   else if (JH_IS_PREFIX("!AI ", socket->in.data))
   {
      /* TODO: Parameter dependent behavior. */
      JH_DEBUG
      (
         stderr,
         1,
         "Received: %s.",
         socket->in.data
      );
   }
   else if (JH_IS_PREFIX("!P ", socket->in.data))
   {
      socket->has_request_in_progress = 0;
   }
   else if (JH_IS_PREFIX("!N ", socket->in.data))
   {
      JH_S_WARNING(stderr, "Received Negative reply.");

      socket->has_request_in_progress = 0;
   }
   else
   {
      JH_WARNING
      (
         stderr,
         "Unsupported reply received: %s.",
         socket->in.data
      );
   }
}
