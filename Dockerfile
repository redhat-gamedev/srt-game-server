#Build
FROM fedora:30 as build-env

RUN sudo dnf install activemq-cpp activemq-cpp-devel apr apr-util apr-util-devel Box2D Box2D-devel compat-openssl10 openssl crypto-utils poco-devel poco-foundation protobuf protobuf-devel gcc g++ cmake git --assumeyes --verbose
#RUN mkdir -p /tmp/srt-game-server/build

ADD . /tmp/srt-game-server
RUN mkdir /tmp/build
WORKDIR /tmp/build

RUN echo `pwd`
RUN ls -lR /tmp/srt-game-server
RUN echo "Running cmake /tmp/srt-game-server"
RUN cmake /tmp/srt-game-server
RUN echo "Running cmake --build ."
RUN cmake --build .


# Run
FROM fedora:30 as base-env

RUN sudo dnf install activemq-cpp activemq-cpp-devel apr apr-util Box2D Box2D-devel compat-openssl10 openssl crypto-utils poco-devel poco-foundation protobuf protobuf-devel --assumeyes --verbose

ENV USER_UID=1000
ENV USER_NAME=srt
ENV EXECUTABLE_NAME=srt-game-server.bin
ENV EXECUTABLE=/home/${USER_NAME}/bin/${EXECUTABLE_NAME}
ENV BROKER_URI="tcp://127.0.0.1:61613?wireFormat=stomp"

WORKDIR /

RUN mkdir -p /home/${USER_NAME}/bin
#COPY bin/${EXECUTABLE_NAME} /home/${USER_NAME}/bin
COPY --from=build-env /tmp/build/srt-game-server /home/${USER_NAME}/bin/${EXECUTABLE_NAME}
COPY containerbuild/bin/entrypoint /home/${USER_NAME}/bin

RUN chown -R `id -u`:0 /home/${USER_NAME}/bin && chmod -R 755 /home/${USER_NAME}/bin
USER ${USER_UID}:0
ENTRYPOINT "/home/srt/bin/entrypoint" "--broker-uri" "$BROKER_URI"

LABEL \
      com.srt.component="srt-game-server" \
      description="Space Ring Things game physics server" \
      io.k8s.description="Main game simulation container for Space Ring Things" \
      io.k8s.display-name="Space Ring Things 0.1" \
      maintainer="Roddie Kieley <rkieley@apache.org>" \
      name="roddiekieley/srt-game-server" \
      summary="Space Ring Things game physics server" \
      version="0.1"
