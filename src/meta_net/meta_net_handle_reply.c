#include "../error/error.h"

#include "../irc/irc.h"
#include "../parameters/parameters.h"

#include "meta_net.h"

static void handle_generated_reply
(
   struct JH_meta_net socket [const restrict static 1],
   struct JH_irc irc [const restrict static 1],
   const struct JH_parameters params [const restrict static 1]
)
{
   if
   (
      JH_IS_PREFIX
      (
         JH_META_NET_ACTION_STRING " ",
         (
            socket->in.data
            +
            (
               JH_META_NET_GR_STRING_LENGTH
               + 1 /* ' ' */
            )
         )
      )
   )
   {
      JH_irc_send_action
      (
         irc,
         (
            socket->in.data
            +
            (
               JH_META_NET_GR_STRING_LENGTH
               + 1 /* ' ' */
               + JH_META_NET_ACTION_STRING_LENGTH
               + 1 /* ' ' */
            )
         )
      );
   }
   else if
   (
      socket->in.index
      >
      (
         JH_META_NET_GR_STRING_LENGTH
         + 1 /* ' ' */
      )
   )
   {
      JH_irc_send_message
      (
         irc,
         (
            socket->in.data
            +
            (
               JH_META_NET_GR_STRING_LENGTH
               + 1 /* ' ' */
            )
         )
      );
   }
}

static void move_to_next_reply
(
   struct JH_meta_net socket [const restrict static 1]
)
{
   if (socket->in.index < socket->in.length)
   {
      memmove
      (
         (void *) socket->in.data,
         (const void *) (socket->in.data + socket->in.index + 1),
         ((socket->in.length - 1) - socket->in.index) * sizeof(char)
      );
   }

   socket->in.length = (socket->in.length - 1) - socket->in.index;

   for
   (
      socket->in.index = 0;
      (socket->in.index < socket->in.length);
      socket->in.index += 1
   )
   {
      if (socket->in.data[socket->in.index] == '\n')
      {
         return;
      }
   }

   socket->in.index = 0;
}

static void handle_additional_info
(
   struct JH_meta_net socket [const restrict static 1],
   const struct JH_parameters params [const restrict static 1]
)
{
   if (JH_parameters_get_print_additional_info(params))
   {
      printf
      (
         "[JH][AI] %s\n",
         (
            socket->in.data
            +
            (
               JH_META_NET_AI_STRING_LENGTH
               + 1 /* ' ' */
            )
         )
      );
   }
}

void JH_meta_net_handle_reply
(
   struct JH_meta_net socket [const restrict static 1],
   struct JH_irc irc [const restrict static 1],
   const struct JH_parameters params [const restrict static 1]
)
{
   while
   (
      (socket->in.length != 0)
      && (socket->in.data[socket->in.index] == '\n')
   )
   {
      socket->in.data[socket->in.index] = '\0';

      if
      (
         JH_IS_PREFIX
         (
            JH_META_NET_CPV_STRING " ",
            socket->in.data
         )
      )
      {
      }
      else if
      (
         JH_IS_PREFIX
         (
            JH_META_NET_CPS_STRING " ",
            socket->in.data
         )
      )
      {
      }
      else if
      (
         JH_IS_PREFIX
         (
            JH_META_NET_GR_STRING " ",
            socket->in.data
         )
      )
      {
         handle_generated_reply(socket, irc, params);
      }
      else if
      (
         JH_IS_PREFIX
         (
            JH_META_NET_AI_STRING " ",
            socket->in.data
         )
      )
      {
         handle_additional_info(socket, params);
      }
      else if
      (
         JH_IS_PREFIX
         (
            JH_META_NET_P_STRING " ",
            socket->in.data
         )
      )
      {
         socket->has_request_in_progress = 0;
      }
      else if
      (
         JH_IS_PREFIX
         (
            JH_META_NET_N_STRING " ",
            socket->in.data
         )
      )
      {
         JH_S_WARNING(stderr, "[JH] Received Negative reply.");

         socket->has_request_in_progress = 0;
      }
      else
      {
         JH_WARNING
         (
            stderr,
            "[JH] Unsupported reply received: %s.",
            socket->in.data
         );
      }

      move_to_next_reply(socket);
   }
}
