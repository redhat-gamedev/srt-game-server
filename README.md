# srt-game-server

## Overview

srt-game-server originated as a proof of concept backend multiplayer game server with the end goal of supporting clients in web browsers via a messaging broker.

It is written in C++ and depends on the following libraries:
* [Box2D v2.3.0](https://box2d.org) - 2D physics engine
* [POCO C++ Libraries v1.9.0](https://pocoproject.org) - cross-platform C++ libraries for building network and internet-based applications
* [Protocol Buffers v3.y](https://developers.google.com/protocol-buffers) - language-neutral, platform-neutral extensible mechanism for serializing structured data
* [Qpid Proton v0.31](http://qpid.apache.org/proton/index.html) - [AMQP v1.0](http://docs.oasis-open.org/amqp/core/v1.0/os/amqp-core-overview-v1.0-os.html#toc) / [ISO 19464:2014](https://www.iso.org/standard/64955.html) messaging protocol

And has traditionally been using [Apache ActiveMQ](activemq.apache.org) as the message broker. Original development took place in Xcode, 
with an unsophisticated CMake based build more recently added.

## Visual Studio Remote Container Support

If you have [Visual Studio Code](https://code.visualstudio.com/) with the [Remote Container extension](https://code.visualstudio.com/docs/remote/containers), you are able to build, run, and debug the game server without having to install anything additional on your laptop.

The container has docker installed and mounts the hosts /var/run/docker.sock so you can run containers on the host machine

### Starting up VS Code

1. Clone the git repo
2. Open Visual Studio Code in the root of repo
3. When prompted to open the folder in a container, accept the prompt

### Building the code

1. Simply run the "Build" task
   * This will use cmake to create the necessary build information and then build the server

### Debugging (and Running) the code

1. Open a terminal and run the Artemis broker in a container
```
docker run --name artemis -it --rm -p 5672:5672 \
-e AMQ_USER=admin -e AMQ_PASSWORD=admin -e AMQ_ALLOW_ANONYMOUS=true \
quay.io/artemiscloud/activemq-artemis-broker:latest
```
2. Go to the Debug tab
3. Click the play button for "Launch Main" 
   * When prompted enter the hostname or IP address of the artemis broker and also the port number 
     (e.g. 5672 - the default insecure AMQP port)
4. The game server should start up and connect to the broker

## Containerization
In the containerbuild directory is a Fedora 33-based Dockerfile for running
the srt-game-server via your favorite container runtime. Build and run
testing was performed using podman on a Fedora 33 host.

You can build the container using the following command, ensuring first that
you are in the root folder of this repo:

```
podman build -v `pwd`:/tmp/srt-game-server:Z -t localhost/redhat-gamedev/srt-game-server:latest .
```

## Quick and Dirty Local Testing
You can run an Artemis broker locally in a container, and then connect the
game server to it. Currently, the broker must be run with a root-ful
container (via `sudo`).

In one terminal:

```
sudo podman run --name artemis -it --rm -p 5672:5672 \
-e AMQ_USER=admin -e AMQ_PASSWORD=admin -e AMQ_ALLOW_ANONYMOUS=true \
quay.io/artemiscloud/activemq-artemis-broker:latest
```

In another terminal:

```
export BROKER_IP=`sudo podman inspect artemis | grep IPAddress | cut -d: -f2 | cut -d\" -f2`
podman run --name srt-game-server \
-e BROKER_URI="tcp://$BROKER_IP:5672" \
-it --rm quay.io/redhat-gamedev/srt-game-server:latest
```