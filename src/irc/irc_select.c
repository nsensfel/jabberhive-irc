#include <libircclient/libircclient.h>

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
      /* TODO: reconnect or fail. */
      JH_irc_connect(irc);
      /* TODO: wait a bit... */
   }

   irc_add_select_descriptors(irc->session, in, out, max_fd);

   return 0;
}

int JH_irc_post_select
(
   struct JH_irc irc [const restrict static 1],
   fd_set in [const restrict static 1],
   fd_set out [const restrict static 1]
)
{
   if (!irc_process_select_descriptors(irc->session, in, out))
   {
      /* TODO: reconnect or fail. */
   }

   return 0;
}
