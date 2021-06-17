# Emails

This document describes how emails are being dealt with in Alele, which mostly means how they are stored in the
Meta Store and Payload Store.

## Meta Store

Each email indexes the following boolean terms:

 * From
 * To
 * CC
 * BCC
 * Organization
 * Reply-To
 * List-Id
 * X-Mailing-List
 * Date
 * Subject
 * Flags
    * Read
    * Has Attachment
    * Important
    * Watched
    * ToAct
    * Deleted
    * Spam
    * IsReplied
    * IsIgnored
    * IsForwarded
    * IsSent
    * IsQueued
    * IsHam
    * IsEncrypted
    * IsSigned
    * HasInvitation

The following terms are indexed for full-text search:

 * Subject
 * Plain-text body
 * Names of attachments

Regarding the meail body and attachments, extra effort must be made to index only relevant content. That is, if the
email has text/plain content type, then the entire body is indexed. If the email is multipart/alternative and contains
text/plain part, the plaintext can be extracted from the text/plain subpart. If there's only text/html, the plain text
can be extracted by stripping all HTML tags.

The Subject should be stripped of common prefixes, like "Re:" and "Fwd:" for indexing purposes.

## Payload Store

It seems sensible to use a well known format with some optimizations on top. For that reason,
resources that sync emails from a remote server (via IMAP or other means) will use the Maildir
format to store emails locally. A local SQLite database can be used to store extra metadata like
mapping between local and remote IDs and some additonal information regarding synchronization.


