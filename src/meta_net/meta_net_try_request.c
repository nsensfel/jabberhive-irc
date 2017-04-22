#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdint.h>

#include "../error/error.h"

#include "../parameters/parameters.h"

#include "meta_net.h"

/******************************************************************************/
/** MEMORY ALLOCATION *********************************************************/
/******************************************************************************/
static int ensure_string_capacity
(
   char * string [const restrict static 1],
   size_t string_capacity [const restrict static 1],
   const size_t string_required_capacity
)
{
   char * new_string;

   if (string_required_capacity <= *string_capacity)
   {
      return 0;
   }

   new_string =
      (char *) realloc
      (
         (void *) *string,
         ((size_t) string_required_capacity) * sizeof(char)
      );

   if (new_string == (char *) NULL)
   {
      JH_S_ERROR
      (
         stderr,
         "Unable to reallocate memory to match string's required size."
      );

      return -1;
   }

   *string_capacity = string_required_capacity;
   *string = new_string;

   return 1;
}

/******************************************************************************/
/** EXPORTED ******************************************************************/
/******************************************************************************/
int JH_meta_net_handle_user_message
(
   struct JH_meta_net socket [const restrict static 1],
   const char string [const restrict static 1],
   const size_t string_size
)
{
   if (socket->out.length != 0)
   {
      return 1;
   }

   if
   (
      ensure_string_capacity
      (
         &(socket->out.data),
         &(socket->out.capacity),
         string_size
      )
      < 0
   )
   {
      return -1;
   }

   memcpy
   (
      (void *) socket->out.data,
      (const void *) string,
      (string_size * sizeof(char))
   );

   socket->out.length = string_size;
   socket->out.index = 0;

   socket->has_request_in_progress = 1;

   return 0;
}

int JH_meta_net_handle_user_action
(
   struct JH_meta_net socket [const restrict static 1],
   const char string [const restrict static 1],
   const size_t string_size
)
{
   if (socket->out.length != 0)
   {
      return 1;
   }

   if
   (
      ensure_string_capacity
      (
         &(socket->out.data),
         &(socket->out.capacity),
         (string_size + (JH_META_NET_ACTION_STRING_LENGTH + 1))
      )
      < 0
   )
   {
      return -1;
   }

   memcpy
   (
      (void *) socket->out.data,
      (const void *) JH_META_NET_ACTION_STRING,
      (JH_META_NET_ACTION_STRING_LENGTH * sizeof(char))
   );

   socket->out.data[JH_META_NET_ACTION_STRING_LENGTH] = ' ';

   memcpy
   (
      (void *) (socket->out.data + (JH_META_NET_ACTION_STRING_LENGTH + 1)),
      (const void *) string,
      (string_size * sizeof(char))
   );

   socket->out.length = string_size;
   socket->out.index = 0;

   socket->has_request_in_progress = 1;

   return 0;
}

int JH_meta_net_read
(
   struct JH_meta_net socket [const restrict static 1]
)
{
   const int old_errno = errno;
   ssize_t in_bytes_count;

   if ((SIZE_MAX - JH_META_NET_READ_SIZE) < socket->in.length)
   {
      JH_S_ERROR
      (
         stderr,
         "Unable to read from JabberHive socket: max buffer size reached."
      );

      return -1;
   }

   if
   (
      ensure_string_capacity
      (
         &(socket->in.data),
         &(socket->in.capacity),
         (socket->in.length + JH_META_NET_READ_SIZE)
      )
      < 0
   )
   {
      return -1;
   }

   errno = 0;

   in_bytes_count =
      read
      (
         socket->fd,
         (&(socket->in.data) + socket->in.length),
         (size_t) JH_META_NET_READ_SIZE
      );

   if (in_bytes_count < 0)
   {
      if (errno == EAGAIN)
      {
         errno = old_errno;

         return 0;
      }

      JH_ERROR
      (
         stderr,
         "Unable to read from JabberHive socket: %s.",
         strerror(errno)
      );

      errno = old_errno;

      return -1;
   }

   errno = old_errno;

   /* Safe. */
   socket->in.length += (size_t) in_bytes_count;

   while (socket->in.index < socket->in.length)
   {
      if (socket->in.data[socket->in.index] == '\n')
      {
         break;
      }

      socket->in.index += 1;
   }

   return 0;
}
