# RPC

This document describes the RPC mechanism used by Alele.

RPC is based on ZeroMQ.

# Architecture

                   Client 1 : Client 2
                            :
    Channel Channel Channel : Channel Channel Channel
       |       |       |    :    |       |       |
       `-------|-------'    :    `-------|-------'
               |            :            |
            Router          :         Router
               |            :            |
               `-------,    :    ,-------'
                       |    :    |
 . . . . . . . . . . . | . . . . | . . . . . . . . . . . . .
                       |         |   Server
                       `----v----'
                            |
                          Router
                            |
                      ChannelHandler
                            |
       ,-------v-------v----+-----v-------v-------, 
       |       |       |          |       |       |
    Channel Channel Channel   Channel Channel Channel
