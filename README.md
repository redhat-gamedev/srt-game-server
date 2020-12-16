# srt-game-server

## Overview

srt-game-server originated as a proof of concept backend multiplayer game server with the end goal of supporting clients in web browsers via a messaging broker.

It is written in C++ and depends on the following libraries:
* [Apache CMS v3.9.4](https://activemq.apache.org/components/cms) - messaging API
* [Box2D v2.3.0](https://box2d.org) - 2D physics engine
* [POCO C++ Libraries v1.9.0](https://pocoproject.org) - cross-platform C++ libraries for building network and internet-based applications
* [Protocol Buffers v3.6.1](https://developers.google.com/protocol-buffers) - language-neutral, platform-neutral extensible mechanism for serializing structured data

And has traditionally been using [Apache ActiveMQ](activemq.apache.org) as the message broker. Original development took place in Xcode, 
with an unsophisticated CMake based build more recently added.

## Containerization

In the containerbuild directory is a Fedora 30 based Dockerfile for running the srt-game-server via your favorite container runtime.
Build and run testing was performed using podman on a Fedora 30 host.

## Quick and Dirty Local Testing
You can run an Artemis broker locally in a container, and then connect the
game server to it. Currently, the broker must be run with a root-ful
container (via `sudo`).

In one terminal:

```
sudo podman run --name artemis -it --rm -p 61613:61613 \
-e AMQ_USER=admin -e AMQ_PASSWORD=admin -e AMQ_ALLOW_ANONYMOUS=true \
quay.io/artemiscloud/activemq-artemis-broker:latest
```

In another terminal:

```
export BROKER_IP=`sudo podman inspect artemis | grep IPAddress | cut -d: -f2 | cut -d\" -f2`
podman run --name srt-game-server \
-e BROKER_URI="tcp://$BROKER_IP:61613?wireFormat=stomp" \
-it --rm quay.io/redhat-gamedev/srt-game-server:latest
```