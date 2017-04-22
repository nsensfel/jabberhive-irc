#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "../error/error.h"

#include "../parameters/parameters.h"

#include "meta_net.h"

static int open_socket
(
   struct JH_meta_net s [const restrict static 1],
   const char socket_name [const restrict static 1]
)
{
   struct sockaddr_un addr;
   int flags;
   const int old_errno = errno;

   errno = 0;

   s->fd = socket(AF_UNIX, SOCK_STREAM, 0);

   if (s->fd == -1)
   {
      JH_FATAL
      (
         stderr,
         "Unable to create socket: %s.",
         strerror(errno)
      );

      errno = old_errno;

      return -1;
   }

   errno = old_errno;

   memset((void *) &addr, 0, sizeof(addr));

   addr.sun_family = AF_UNIX;

   strncpy
   (
      (void *) addr.sun_path,
      (const void *) socket_name,
      (sizeof(addr.sun_path) - 1)
   );

   errno = 0;

   if (connect(s->fd, (struct sockaddr *) &addr, sizeof(addr)) == -1)
   {
      JH_FATAL
      (
         stderr,
         "Unable to connect to address: %s.",
         strerror(errno)
      );

      errno = old_errno;

      close(s->fd);

      return -1;
   }

   errno = 0;

   flags = fcntl(s->fd, F_GETFD, 0);

   if (flags < 0)
   {
      JH_FATAL
      (
         stderr,
         "Unable to get fd flag information for JabberHive socket: %s.",
         strerror(errno)
      );

      errno = old_errno;

      close(s->fd);

      return -1;
   }

   errno = 0;

   if (fcntl(s->fd, F_SETFL, (flags | O_NONBLOCK)) == -1)
   {
      JH_FATAL
      (
         stderr,
         "Unable to get fd flag information for JabberHive socket: %s.",
         strerror(errno)
      );

      errno = old_errno;

      close(s->fd);

      return -1;
   }

   errno = old_errno;

   return 0;
}

int JH_meta_net_connect
(
   struct JH_meta_net socket [const restrict static 1],
   const struct JH_parameters params [const restrict static 1]
)
{
   return
      open_socket
      (
         socket,
         JH_parameters_get_socket_name(params)
      );
}

void JH_meta_net_initialize
(
   struct JH_meta_net socket [const restrict static 1]
)
{
   socket->in.data = (char *) NULL;
   socket->in.capacity = 0;
   socket->in.length = 0;
   socket->in.index = 0;

   socket->out.data = (char *) NULL;
   socket->out.capacity = 0;
   socket->out.length = 0;
   socket->out.index = 0;

   socket->fd = -1;
   socket->has_request_in_progress = 0;
}

void JH_meta_net_finalize
(
   struct JH_meta_net socket [const restrict static 1]
)
{
   /* TODO */
}
