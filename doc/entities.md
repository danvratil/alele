# Entities

Entities is a common name for all data types handled by Alele. Entity can be an email, contact,
calendar event, etc.

This document describes some characteristics that are common to all Entities.

## ID

Each entity is uniquely identified. The identifier doesn't have to be purely numerical, but must be globally
unique. Currently the implementation uses `<PREFIX><DOCUMENT_ID>` format where `<PREFIX>` is a single-letter
prefix identifying the data type, and thus the server-side storage to query. `<DOCUMENT_ID>` is then a number
assigned by the Meta Store when the entity was first created.

## Multipart Structure

While this affects mostly emails, the nature of this feature is something that makes sense to be
supported universally. Each entity can have multiple parts (think headers, body and attachment for emails,
or calendar event with attachment), some of which may not be locally cached, but can be retrieved
upon demand from the remote service.

Each part has a nested numerical identifier, where each number indicates index of the part within its container.
The index is counted from 0. Each number is separated by a dot (`.`). For example, if we have an email with
following structure:

   mime/rfc882
    |- headers
    `- multipart/mixed
        |- multipart/alternative
        |   |- text/plain
        |   `- text/html
        |- image/jpeg
        `- application/zip

Let's say we want to refer to the `text/html` part. It's identified would be `0.1.0.1`:

   0 - mime/rfc882 is top-level
   1 - multipart/mixed is second subpart of mime/rfc822
   0 - multipart/alternative is first subpart of the multipart/mixed part
   1 - text/html is second subpart of the multipart/alternative part

The ZIP attachment would be identified as `0.1.2`:

   0 - mime/rfc882 is top-level
   1 - multpart/mixed is second subpart of the mime/rfc822 message
   2 - application/zip is third subpart of the multipart/fixed part

The full structure description is always available to the client, which can then request specific part
from the Alele storage. If the part is not available locally, the resource will post a remote request
to retreive it and will stream it back to the client (and cache it locally, if requested).
