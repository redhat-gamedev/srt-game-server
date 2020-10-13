# CMSTest

CMSTest originated as a proof of concept backend multiplayer game server with the end goal of supporting clients in web browsers via a messaging broker.

It is written in C++ and depends on the following libraries:
* [Apache CMS](https://activemq.apache.org/components/cms) - messaging API
* [Box2D](https://box2d.org) - 2D physics engine
* [POCO C++ Libraries](https://pocoproject.org) - cross-platform C++ libraries for building network and internet-based applications
* [Protocol Buffers](https://developers.google.com/protocol-buffers) - language-neutral, platform-neutral extensible mechanism for serializing structured data

And has traditionally been using [Apache ActiveMQ](activemq.apache.org) as the message broker. Original development took place in Xcode, 
with an unsophisticated CMake based build more recently added.

The initial client proof of concept is the corresponding [NMSTest](https://github.com/RoddieKieley/NMSTest).
