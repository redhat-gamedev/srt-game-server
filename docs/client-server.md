# Overview of communications

## Components

There are three moving parts; the broker, the game simulation server, and the client. Each
of these communicate via the 
[AMQP v1.0](http://docs.oasis-open.org/amqp/core/v1.0/os/amqp-core-overview-v1.0-os.html#toc) / 
[ISO 19464:2014](https://www.iso.org/standard/64955.html) messaging protocol. The messaging
protocol is utilized by way of the [Qpid Proton](http://qpid.apache.org/proton/index.html)
messaging library.

### Broker

Testing, as documented in the [README](../README.md) utilizes the latest 
[ActiveMQ Artemis](https://activemq.apache.org/components/artemis/)
message broker. Below we will assume that there is a broker at host:port listening for the AMQP protocol,
configured for anonymous access.

### Game Simulation Server

The srt-game-server project builds to an executable that accepts the --broker-uri arg from
the commandline. In the local, non-containerized, environment this is utilized like:
./srt-game-server --broker-uri "tcp://192.168.2.4:5672"

While in the containerized case, if built using the Dockerfile in the containerbuild
directory, the entrypoint executed inside the container reads the BROKER_URI environment
variable and passes it along via --broker-uri ${BROKER_URI}.

Upon running the game simulation server first connects to the broker via the provided
broker URI. In particular it connects:

- A consumer to the anycast address "COMMAND.IN"
- A producer to the multicast address "GAME.EVENT.OUT"

i.e. the game server receives commands from all clients via COMMAND.IN,
and sends out game updates to all clients via GAME.EVENT.OUT.

### Client

The client must also first connect to the broker using the broker uri at the same host:port
where it is expected to "talk" AMQP via the following two addresses:

- A consumer to the multicast address "GAME.EVENT.OUT"
- A producer to the anycast address "COMMAND.IN"

i.e. the client sends commands, such as join/leave, and input to the game server through
the broker via the COMMAND.IN anycast address that the server is listening on. Once "joined" it
receives regular game simulations snapshots from the game server via GAME.EVENT.OUT.

### Order of operations

- Start broker
- Start srt-game-server
  - srt-game-server connects to the broker at host:port
- Start client
  - client connects to the broker at host:port
  - client creates a message containing a SecurityCommandBuffer of type JOIN and sends it to COMMAND.IN
    - In response the srt-game-server creates a player for the client and for the moment utilizes the
      UUID as sent by the client. Originally the UUID was generated server side, however it was changed
      in looking forward to when web-client auth integration is completed.
  - client can now transition to the in game state where it can receive updates in 
    [box2d protobuf format](../src/Proto/box2d.proto)
    via GAME.EVENT.OUT
  - client creates messages containing a RawInputCommandBuffer with type DUALSTICK containing the
    players UUID and sends them to COMMAND.IN
    - client continues to loop on providing input via COMMAND.IN and receiving updates via GAME.EVENT.OUT
- Disconnect the client
  - client creates a message containing a SecurityCommandBuffer of type LEAVE with its unique UUID
    and sends it to COMMAND.IN
  - srt-game-server "forgets" about this particular client
  