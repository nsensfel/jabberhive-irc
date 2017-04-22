# Taken from https://github.com/sgielen/libdazeus-irc


#Copyright (c) Sjors Gielen, 2010-2012
#All rights reserved.
#
#Redistribution and use in source and binary forms, with or without
#modification, are permitted provided that the following conditions are met:
#    * Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#    * Neither the name of the DaVinci or DaZeus team nor the
#      names of its contributors may be used to endorse or promote products
#      derived from this software without specific prior written permission.
#
#THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
#ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
#WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
#DISCLAIMED. IN NO EVENT SHALL SJORS GIELEN OR CONTRIBUTORS BE LIABLE FOR ANY
#DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
#(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
#LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
#ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
#SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


# Once done, this will define
#
#  LibIRCClient_FOUND - system has LibIRCClient
#  LibIRCClient_INCLUDE_DIRS - the LibIRCClient include directories
#  LibIRCClient_LIBRARIES - link these to use LibIRCClient

include(LibFindMacros)

# Include dir
find_path(LibIRCClient_INCLUDE_DIR
  NAMES libircclient.h
  PATHS ${LibIRCClient_PKGCONF_INCLUDE_DIRS}
      /usr/include /sw/include /usr/local/include
      /usr/include/libircclient /sw/include/libircclient
      /usr/local/include/libircclient
)

# Finally the library itself
find_library(LibIRCClient_LIBRARY
  NAMES ircclient
  PATHS ${LibIRCClient_PKGCONF_LIBRARY_DIRS}
      /usr/lib /lib /sw/lib /usr/local/lib
)

set(LibIRCClient_PROCESS_INCLUDES LibIRCClient_INCLUDE_DIR)
set(LibIRCClient_PROCESS_LIBS LibIRCClient_LIBRARY)
libfind_process(LibIRCClient)
