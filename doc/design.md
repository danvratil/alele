# Design

This document describes the design of the Alele service.

## Introduction

Think of Alele as a streaming service - the client sends a request and will start receiving stream of relevant data
from Alele. Extra effort is made to return the most relevant information first - for example when querying calendar
events, events from the current day/week/month are streamed first, the rest later or on demand.

Now there are several ways how to achieve that. In case of Alele, the clients can all access a shared database that
is always in a consistent and valid state. This offloads the Alele server which can focus on serializing and storing
the data in most efficient way possible.

One thing that we took as a lesson from Akonadi is to find a middle ground between the service being completely type
agnostic and overly specialized. In Akonadi, the server had zero knowledge about the contents of the data it stored.
There we some minimal metadata, but that's all. This proved to be a major obstacle in optimizing performance of
Akonadi. On the other hand, we don't want to have to half-rewrite the whole thing whenever we would want to introduce
a new type (say, calendar events). Instead the design should be done in such a way that Alele understands each data
type well enough so it can query it efficiently.

## Architecture

Alele follows the server-client architecture that was introduced by Akonadi. Similar to Akonadi, there is a single
central process, the Alele server. This server manages the underlying data store and is the only process capable of
writing into the data store. The server also manages a set of resources (like Akonadi resources) that ensure that the
local and remote storages are kept in sync. Non-remote resources (like maildir) must provide an efficient way to sync
the data without duplicating them in the Alele data store. Finally, Alele has a messaging bus, sending out notifications
about changes to the data stores. The bus can be used by the synchronizing resources as well as clients to stay
up-to-date.

Clients should only connect to Alele in order to post updates to the data store and to receive notifications about
changes. To read data, the clients may ask Alele server about certain details, but ultimately they should query
the datastore on their own through the Alele client libraries.

## Data Store

See [datastore.md](./datastore.md) for details regarding the datastore.


