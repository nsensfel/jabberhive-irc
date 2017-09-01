## What is JabberHive?
JabberHive is a modular Reply Bot system. All "modules" are in fact separate
programs linked together using the JabberHive Protocol. Please refer to the
protocol for more information.

## Component Description
* IRC Gateway for a JabberHive network.

## JabberHive Protocol Compatibility
* **Protocol Version(s):** 1.
* **Inbound Connections:** None.
* **Outbound Connections:** Single.
* **Pipelining:** No.
* **Behavior:** Gateway.

## Dependencies
- POSIX compliant OS.
- C compiler (with C99 support).
- (GNU) make.
- libircclient.

## How to Build
* Download the source code.
* Enter the following command: ``$ make``.
* Run ``$ ./jh-cli`` to see how to use the binary.

## Example of Use
* Create an IRC gateway that will connect to the JabberHive network through the
   socket ``/tmp/lc0``, and to IRC on ``irc.foonetic.net``, port ``6667``,
   with the nickname ``jabberhivebot``, channel ``#jabberhive``, with the
   username ``JabberHive``, and the realname ``JabberHive IRC Gateway``; with
   chat being printed to stdout: ``./jh-irc /tmp/lc0 "irc.foonetic.net"
   "jabberhivebot" "#jabberhive" "6667" -u "JabberHive" -r
   "JabberHive IRC Gateway" -c``
