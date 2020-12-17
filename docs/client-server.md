# Overview of communications

## Components

There are three moving parts; the broker, the game simulation server, and the client. 
At the moment these three communicate via the STOMP protocol, although this will change
to AMQP 1.0 / ISO 19464 in the near future.

### Broker

Initially the ActiveMQ 5.y broker was utilized for development via a broker uri like
tcp://host:ip?wireFormat=stomp&keepAlive=true
and is known to work well.

At the moment testing is moving toward using the newer ActiveMQ Artemis 2.y broker. A
caveat here is that the keepAlive=true setting above is not honoured and thus at the moment
after one minute the connection will time out.

Below we will assume that there is a broker at host:port listening for the STOMP protocol,
configured for anonymous access, and ignore the keep alive issue.

### Game Simulation Server

The srt-game-server project builds to an executable that accepts the --broker-uri arg from
the commandline. In the local, non-containerized, environment this is utilized like:
./srt-game-server --broker-uri "tcp://192.168.2.4:61613?wireFormat=stomp"

While in the containerized case, if built using the Dockerfile in the containerbuild
directory, the entrypoint executed inside the container reads the BROKER_URI environment
variable and passes it along via --broker-uri ${BROKER_URI}.

Upon running the game simulation server first connects to the broker via the provided
broker URI. In particular it connects:

- A consumer to the queue "COMMAND.IN"
- A producer to the topic "GAME.EVENT.OUT"

i.e. the game server receives commands from all clients via COMMAND.IN,
and sends out game updates to all clients via GAME.EVENT.OUT.

### Client

The client must also first connect to the broker using the broker uri at the same host:port
where it is expected to "talk" STOMP at the moment via:

- A consumer to the topic "GAME.EVENT.OUT"
- A producer to the queue "COMMAND.IN"

i.e. the client sends commands, such as join/leave, and input to the game server through
the broker via the COMMAND.IN queue that the server is listening on. Once "joined" it
receives regular game simulations snapshots from the game server via GAME.EVENT.OUT.

### Order of operations

- Start broker
- Start srt-game-server
  - srt-game-server connects to the broker at host:port
- Start client
  - client connects to the broker at host:port
  - client creates a message containing a SecurityCommandBuffer of type JOIN and sends it to COMMAND.IN
    - In response the srt-game-server creates a player for the client and the unique UUID back [more detail required]
  - client can now transition to the in game state where it can receive updates in box2d proto format via GAME.EVENT.OUT
  - client creates messages containing a RawInputCommandBuffer with type DUALSTICK containing the players UUID and sends
  them to COMMAND.IN
    - client continues to loop on providing input via COMMAND.IN and receiving updates via GAME.EVENT.OUT
- Disconnect the client
  - client creates a message containing a SecurityCommandBuffer of type LEAVE with its unique UUID and sends it to COMMAND.IN
  - srt-game-server "forgets" about this particular client
  