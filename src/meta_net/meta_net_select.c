#include <stdio.h>
#include <sys/select.h>

#include "meta_net.h"

int JH_meta_net_pre_select
(
   struct JH_meta_net socket [const restrict static 1],
   fd_set in [const restrict static 1],
   fd_set out [const restrict static 1],
   int max_fd [const restrict static 1]
)
{
   FD_SET(socket->fd, in);

   if (socket->out.length != 0)
   {
      FD_SET(socket->fd, out);
   }

   if ((*max_fd) < socket->fd)
   {
      *max_fd = socket->fd;
   }

   return 0;
}

int JH_meta_net_post_select
(
   struct JH_meta_net socket [const restrict static 1],
   fd_set in [const restrict static 1],
   fd_set out [const restrict static 1]
)
{
   if (FD_ISSET(socket->fd, in))
   {
      if (JH_meta_net_read(socket) < 0)
      {
         /* TODO: Try to reconnect. */
         return -1;
      }
   }

   if ((socket->out.length != 0) && FD_ISSET(socket->fd, out))
   {
      if (JH_meta_net_write(socket) < 0)
      {
         /* TODO: Try to reconnect. */
         return -1;
      }
   }

   return 0;
}
