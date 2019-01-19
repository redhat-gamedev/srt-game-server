# Generated on 2019-1-11 22:36:30 by version 0.7.0 of mulle-xcode-to-cmake
# Command line:
#    mulle-xcode-to-cmake export CMSTest.xcodeproj

project( CMSTest)

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
else()
   set( CMAKE_POSITION_INDEPENDENT_CODE TRUE)

   if( WIN32)
   # windows
   else()
   # linux / gcc
      set( BEGIN_ALL_LOAD "-Wl,--whole-archive")
      set( END_ALL_LOAD "-Wl,--no-whole-archive")
   endif()
endif()


##
## CMSTest Files
##

# uncomment this for mulle-objc to search libraries first
# set( CMAKE_FIND_FRAMEWORK "LAST")

set( SOURCES
CMSTest/Application/Heartbeat.cpp
CMSTest/Application/Server.cpp
CMSTest/Application/main.cpp
CMSTest/Commands/ACommand.cpp
CMSTest/Commands/CommandConsumer.cpp
CMSTest/Commands/CommandQueue.cpp
CMSTest/Commands/DualStickRawInputCommand.cpp
CMSTest/Commands/JoinSecurityCommand.cpp
CMSTest/Commands/LeaveSecurityCommand.cpp
CMSTest/Commands/RawInputCommand.cpp
CMSTest/Commands/SecurityCommand.cpp
CMSTest/Commands/SecurityCommandBufferFactory.cpp
CMSTest/Events/EntityGameEventFactory.cpp
CMSTest/Events/EventDispatcher.cpp
CMSTest/Events/SecurityGameEventFactory.cpp
CMSTest/Game/AB2DEntity.cpp
CMSTest/Game/AEntity.cpp
CMSTest/Game/B2DBullet.cpp
CMSTest/Game/B2DPod.cpp
CMSTest/Game/B2DWorld.cpp
CMSTest/Game/Bullet.cpp
CMSTest/Game/BulletFactory.cpp
CMSTest/Game/Pod.cpp
CMSTest/Game/PodFactory.cpp
CMSTest/Game/World.cpp
CMSTest/Network/MessageConsumer.cpp
CMSTest/Network/MessageDispatcher.cpp
CMSTest/Network/SimpleAsyncConsumer.cpp
CMSTest/Network/SimpleAsyncProducer.cpp
CMSTest/Proto/CommandBuffer.pb.cc
CMSTest/Proto/DualStickRawInputCommandBuffer.pb.cc
CMSTest/Proto/EntityGameEventBuffer.pb.cc
CMSTest/Proto/GameEventBuffer.pb.cc
CMSTest/Proto/RawInputCommandBuffer.pb.cc
CMSTest/Proto/SecurityCommandBuffer.pb.cc
CMSTest/Proto/box2d.pb.cc
CMSTest/Shared/Timer.cpp
)

find_library( BOX2_D_LIBRARY Box2D)
message( STATUS "BOX2_D_LIBRARY is ${BOX2_D_LIBRARY}")
find_library( PROTOCOL_BUFFERS_LIBRARY ProtocolBuffers)
message( STATUS "PROTOCOL_BUFFERS_LIBRARY is ${PROTOCOL_BUFFERS_LIBRARY}")
find_library( ACTIVEMQ_CPP_LIBRARY activemq-cpp)
message( STATUS "ACTIVEMQ_CPP_LIBRARY is ${ACTIVEMQ_CPP_LIBRARY}")

set( STATIC_DEPENDENCIES
${ACTIVEMQ_CPP_LIBRARY}
${BOX2_D_LIBRARY}
${PROTOCOL_BUFFERS_LIBRARY}
)

find_library( POCO_FOUNDATIOND_60_LIBRARY PocoFoundationd.60)
message( STATUS "POCO_FOUNDATIOND_60_LIBRARY is ${POCO_FOUNDATIOND_60_LIBRARY}")
find_library( APR_1_0_LIBRARY apr-1.0)
message( STATUS "APR_1_0_LIBRARY is ${APR_1_0_LIBRARY}")
find_library( APRUTIL_1_0_LIBRARY aprutil-1.0)
message( STATUS "APRUTIL_1_0_LIBRARY is ${APRUTIL_1_0_LIBRARY}")
find_library( CRYPTO_1_0_0_LIBRARY crypto.1.0.0)
message( STATUS "CRYPTO_1_0_0_LIBRARY is ${CRYPTO_1_0_0_LIBRARY}")
find_library( SSL_1_0_0_LIBRARY ssl.1.0.0)
message( STATUS "SSL_1_0_0_LIBRARY is ${SSL_1_0_0_LIBRARY}")

set( DEPENDENCIES
${APRUTIL_1_0_LIBRARY}
${APR_1_0_LIBRARY}
${CRYPTO_1_0_0_LIBRARY}
${POCO_FOUNDATIOND_60_LIBRARY}
${SSL_1_0_0_LIBRARY}
)


##
## CMSTest
##

add_executable( CMSTest MACOSX_BUNDLE
${SOURCES}
${PUBLIC_HEADERS}
${PROJECT_HEADERS}
${PRIVATE_HEADERS}
${RESOURCES}
)

target_include_directories( CMSTest
   PUBLIC
)

target_link_libraries( CMSTest
${BEGIN_ALL_LOAD}
${STATIC_DEPENDENCIES}
${END_ALL_LOAD}
${DEPENDENCIES}
)
