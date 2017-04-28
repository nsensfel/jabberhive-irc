#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#include "../error/error.h"

#include "parameters.h"

static int parse_port
(
   struct JH_parameters param [const restrict static 1],
   const char argv [const restrict]
)
{
   long long int input;
   const int old_errno = errno;

   errno = 0;

   input = strtoll(argv, (char **) NULL, 10);

   if
   (
      (errno != 0)
      || (input > (long long int) USHRT_MAX)
      || (input < 1)
   )
   {
      JH_FATAL
      (
         stderr,
         "Invalid or value for parameter 'port', accepted "
         "range is "
         "[1, %hu] (integer).",
         USHRT_MAX
      );

      errno = old_errno;

      return -1;
   }

   param->port = (unsigned short) input;

   errno = old_errno;

   return 0;
}

static void set_default_to_all_fields
(
   struct JH_parameters param [const restrict static 1]
)
{
   param->print_chat = 0;
   param->print_additional_info = 0;
   param->socket_name = (const char *) NULL;
   param->server = (const char *) NULL;
   param->password = (const char *) NULL;
   param->nick = (const char *) NULL;
   param->username = (const char *) NULL;
   param->realname = (const char *) NULL;
   param->channel = (const char *) NULL;
   param->port = 0;
   param->use_ipv6 = 0;
}

static int is_valid
(
   struct JH_parameters param [const restrict static 1]
)
{
   int valid;

   valid = 1;

   if (param->socket_name == (const char *) NULL)
   {
      JH_S_FATAL(stderr, "Missing parameter: Zero of One socket name.");

      valid = 0;
   }

   if (param->server == (const char *) NULL)
   {
      JH_S_FATAL(stderr, "Missing parameter: IRC server address.");

      valid = 0;
   }

   if (param->nick == (const char *) NULL)
   {
      JH_S_FATAL(stderr, "Missing parameter: IRC nick.");

      valid = 0;
   }

   if (param->channel == (const char *) NULL)
   {
      JH_S_FATAL(stderr, "Missing parameter: IRC channel.");

      valid = 0;
   }

   if (param->port == 0)
   {
      JH_S_FATAL(stderr, "Missing parameter: IRC port.");

      valid = 0;
   }

   return valid;
}

static void set_parameters
(
   struct JH_parameters param [const restrict static 1],
   int const argc,
   const char * argv [const static argc]
)
{
   if (argc < 2)
   {
      return;
   }

   param->socket_name = argv[1];

   if (argc < 3)
   {
      return;
   }

   param->server = argv[2];

   if (argc < 4)
   {
      return;
   }

   param->nick = argv[3];

   if (argc < 5)
   {
      return;
   }

   param->channel = argv[4];

   if (argc < 6)
   {
      return;
   }

   parse_port(param, argv[5]);
}

static int set_options
(
   struct JH_parameters param [const restrict static 1],
   int const argc,
   const char * argv [const static argc]
)
{
   int i;

   for (i = (JH_PARAMETERS_COUNT + 1); i < argc; ++i)
   {

      if
      (
         JH_STRING_EQUALS("-6", argv[i])
         || JH_STRING_EQUALS("--ipv6", argv[i])
      )
      {
         param->use_ipv6 = 1;
      }
      else if
      (
         JH_STRING_EQUALS("-c", argv[i])
         || JH_STRING_EQUALS("--print-chat", argv[i])
      )
      {
         param->print_chat = 1;
      }
      else if
      (
         JH_STRING_EQUALS("-i", argv[i])
         || JH_STRING_EQUALS("--print-additional-info", argv[i])
      )
      {
         param->print_additional_info = 1;
      }
      else if
      (
         JH_STRING_EQUALS("-u", argv[i])
         || JH_STRING_EQUALS("--username", argv[i])
      )
      {
         if (i == (argc - 1))
         {
            JH_FATAL(stderr, "Missing value for option \"%s\".", argv[i]);

            return -1;
         }

         param->username = argv[++i];
      }
      else if
      (
         JH_STRING_EQUALS("-r", argv[i])
         || JH_STRING_EQUALS("--realname", argv[i])
      )
      {
         if (i == (argc - 1))
         {
            JH_FATAL(stderr, "Missing value for option \"%s\".", argv[i]);

            return -1;
         }

         param->realname = argv[++i];
      }
      else if
      (
         JH_STRING_EQUALS("-p", argv[i])
         || JH_STRING_EQUALS("--password", argv[i])
      )
      {
         if (i == (argc - 1))
         {
            JH_FATAL(stderr, "Missing value for option \"%s\".", argv[i]);

            return -1;
         }

         param->password = argv[++i];
      }
      else
      {
         JH_FATAL(stderr, "Unrecognized option \"%s\".", argv[i]);

         return -1;
      }
   }

   return 0;
}

int JH_parameters_initialize
(
   struct JH_parameters param [const restrict static 1],
   int const argc,
   const char * argv [const static argc]
)
{
   set_default_to_all_fields(param);

   set_parameters(param, argc, argv);

   if (!is_valid(param))
   {
      return -1;
   }

   return set_options(param, argc, argv);
}
