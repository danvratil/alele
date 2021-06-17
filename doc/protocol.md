# Protocol

This document describes the protocol used to communicate between clients and Alele.

## Technology

The data exhcnage is done through ZeroMQ. ZeroMQ is a broker-less messaging queue, supporting various
messaging patterns. ZeroMQ itself doesn't care about the format or structure of the message it carries,
this is up to the sending and receiving side to agree upon.

The messages are transported using MessagePack format, which is an efficient streaming protocol.

## Protocols

There are in fact several protocols, depending on who is talking to whom.

### Resource-Server Protocol

This is a protocol used by Resources to talk to Alele Server and vice verse.

### Alele Notification Protocol

This is a general protocol used by Alele to push out notifications regarding changes.

### Client Protocol

This is a protocol used by clients to talk to the Alele server and resources.



