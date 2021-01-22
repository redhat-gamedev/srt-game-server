project(srt-game-server)

cmake_minimum_required (VERSION 3.4)

#
# mulle-bootstrap environment
#

# check if compiling with mulle-bootstrap (works since 2.6)

if( NOT MULLE_BOOTSTRAP_VERSION)
  include_directories( BEFORE SYSTEM
dependencies/include
addictions/include
)

  set( CMAKE_FRAMEWORK_PATH
dependencies/Frameworks
addictions/Frameworks
${CMAKE_FRAMEWORK_PATH}
)

  set( CMAKE_LIBRARY_PATH
dependencies/lib
addictions/lib
${CMAKE_LIBRARY_PATH}
)

set( DEPENDENCIES_DIR dependencies)
set( ADDICTIONS_DIR addictions)

endif()


#
# Platform specific definitions
#

if( APPLE)
   # # CMAKE_OSX_SYSROOT must be set for CMAKE_OSX_DEPLOYMENT_TARGET (cmake bug)
   # if( NOT CMAKE_OSX_SYSROOT)
   #    set( CMAKE_OSX_SYSROOT "/" CACHE STRING "SDK for OSX" FORCE)   # means current OS X
   # endif()
   #
   # # baseline set to 10.6 for rpath
   # if( NOT CMAKE_OSX_DEPLOYMENT_TARGET)
   #   set(CMAKE_OSX_DEPLOYMENT_TARGET "10.6" CACHE STRING "Deployment target for OSX" FORCE)
   # endif()

   set( CMAKE_POSITION_INDEPENDENT_CODE FALSE)

   set( BEGIN_ALL_LOAD "-all_load")
   set( END_ALL_LOAD)
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # enable C++11 standard
else()
   set( CMAKE_POSITION_INDEPENDENT_CODE TRUE)
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -ldl") # enable C++11 standard; include pthread and dynamic loading

   if( WIN32)
   # windows
   else()
   # linux / gcc
      set( BEGIN_ALL_LOAD "-Wl,--whole-archive")
      set( END_ALL_LOAD "-Wl,--no-whole-archive")
   endif()
endif()

##
## Debug
##
set(CMAKE_BUILD_TYPE Debug)

##
## srt-game-server Files
##

# uncomment this for mulle-objc to search libraries first
# set( CMAKE_FIND_FRAMEWORK "LAST")

set( SOURCES
src/Application/Heartbeat.cpp
src/Application/Server.cpp
src/Application/main.cpp
src/Commands/ACommand.cpp
src/Commands/CommandConsumer.cpp
src/Commands/CommandQueue.cpp
src/Commands/DualStickRawInputCommand.cpp
src/Commands/JoinSecurityCommand.cpp
src/Commands/LeaveSecurityCommand.cpp
src/Commands/RawInputCommand.cpp
src/Commands/SecurityCommand.cpp
src/Commands/SecurityCommandBufferFactory.cpp
src/Events/EntityGameEventFactory.cpp
src/Events/EventDispatcher.cpp
src/Events/SecurityGameEventFactory.cpp
src/Game/AB2DEntity.cpp
src/Game/AEntity.cpp
src/Game/B2DBullet.cpp
src/Game/B2DPod.cpp
src/Game/B2DWorld.cpp
src/Game/Bullet.cpp
src/Game/BulletFactory.cpp
src/Game/Pod.cpp
src/Game/PodFactory.cpp
src/Game/World.cpp
src/Network/MessageConsumer.cpp
src/Network/MessageDispatcher.cpp
src/Network/SimpleAsyncConsumer.cpp
src/Network/SimpleAsyncProducer.cpp
src/Proto/CommandBuffer.pb.cc
src/Proto/DualStickRawInputCommandBuffer.pb.cc
src/Proto/EntityGameEventBuffer.pb.cc
src/Proto/GameEventBuffer.pb.cc
src/Proto/RawInputCommandBuffer.pb.cc
src/Proto/SecurityCommandBuffer.pb.cc
src/Proto/box2d.pb.cc
src/Shared/Timer.cpp
        src/Application/Configuration.cpp src/Application/Configuration.h)

find_library( BOX2_D_LIBRARY Box2D)
message( STATUS "BOX2_D_LIBRARY is ${BOX2_D_LIBRARY}")
find_library( PROTOCOL_BUFFERS_LIBRARY protobuf)
message( STATUS "PROTOCOL_BUFFERS_LIBRARY is ${PROTOCOL_BUFFERS_LIBRARY}")
find_library( ACTIVEMQ_CPP_LIBRARY activemq-cpp)
message( STATUS "ACTIVEMQ_CPP_LIBRARY is ${ACTIVEMQ_CPP_LIBRARY}")

set( STATIC_DEPENDENCIES
${ACTIVEMQ_CPP_LIBRARY}
${BOX2_D_LIBRARY}
${PROTOCOL_BUFFERS_LIBRARY}
)

find_library( POCO_FOUNDATIOND_60_LIBRARY PocoFoundation)
message( STATUS "POCO_FOUNDATIOND_60_LIBRARY is ${POCO_FOUNDATIOND_60_LIBRARY}")
find_library( APR_1_0_LIBRARY apr-1)
message( STATUS "APR_1_0_LIBRARY is ${APR_1_0_LIBRARY}")
find_library( APRUTIL_1_0_LIBRARY aprutil-1)
message( STATUS "APRUTIL_1_0_LIBRARY is ${APRUTIL_1_0_LIBRARY}")
find_library( CRYPTO_1_0_2_LIBRARY crypto)
message( STATUS "CRYPTO_1_0_2_LIBRARY is ${CRYPTO_1_0_2_LIBRARY}")
find_library( SSL_1_0_2_LIBRARY ssl)
message( STATUS "SSL_1_0_2_LIBRARY is ${SSL_1_0_2_LIBRARY}")

set( DEPENDENCIES
${APRUTIL_1_0_LIBRARY}
${APR_1_0_LIBRARY}
${CRYPTO_1_0_2_LIBRARY}
${POCO_FOUNDATIOND_60_LIBRARY}
${SSL_1_0_2_LIBRARY}
)


##
## srt-game-server
##

add_executable(srt-game-server MACOSX_BUNDLE
${SOURCES}
${PUBLIC_HEADERS}
${PROJECT_HEADERS}
${PRIVATE_HEADERS}
${RESOURCES}
)

target_include_directories(srt-game-server
   PUBLIC SYSTEM
        /usr/local/include/activemq-cpp
        /usr/include/activemq-cpp-3.9.4
        /usr/include/apr-1
        /usr/local/include
        /opt/local/include
        /opt/local/include/apr-1
)

target_link_libraries(srt-game-server
${BEGIN_ALL_LOAD}
${STATIC_DEPENDENCIES}
${END_ALL_LOAD}
${DEPENDENCIES}
)
