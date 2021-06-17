# Data Store

This document describes details about the Alele internal data store. While we mostly use 'data store' as singular
through the documentation, Alele is in fact using multiple different data stores internally to store all the data
efficiently.

## Meta Store

Meta Store is the store that stores metadata about the entities and allows quick and efficient queries, including
full-text searchm.

After lots of research, the only viable solution appears to be the Xapian library. It also scores extra points for
already being used in Akonadi, so we know what to expect.

Xapian database provides combination of quick term-based retrieval as well as advanced full-text search functionality.
There is a single database per content type (one DB for emails, one for contacts, etc.), since each has a slightly
different "schema". Extra effort is made to index only relevant data.

You can find detailed schema description in the documentation for each domain-specific data type.

Xapian database does NOT contain the original payloads (eg. entire emails), those are stored in payload data store.

## Payload Data Store

The Payload Data Store keeps the original documents (emails, contacts) so they can be presented to the user, or modified
and uploaded to a remote server. Payload Data Store is not centrally managed by Alele, but instead by individual
resources. This allows resources to optimize in cases like Maildir, which can already be used as a fast and reliable
data store.

In other cases, like e.g. CalDAV , a default data store implementation can be used to store the raw vCards on disk.

## Retrieval

When client wants to retrieve data from Alele, it first queries the Meta Store to retrieve a list of IDs. As the
Meta Store starts returning results, the client starts enqueing retrieval requests upon the resources to provide
the actual payload data. The clients can do this in two ways - either by streaming back the payload from their
Payload Data Store, or by sending a pointer and/or file descriptor to the actual file where the client can read the
data from themselves.


