#Build
ARG fedora_version=33
FROM fedora:${fedora_version} as build-env

COPY containerbuild/srt.repo /etc/yum.repos.d/
RUN sudo dnf install Box2D-2.3.1-12.fc32.x86_64 Box2D-devel-2.3.1-12.fc32.x86_64 compat-openssl10 openssl poco-devel poco-foundation protobuf protobuf-devel gcc g++ cmake git qpid-proton-cpp qpid-proton-cpp-devel --assumeyes --verbose

WORKDIR /tmp/srt-game-server/src/Proto
RUN for i in $(ls -lC1 *.proto); do protoc $i --cpp_out=.; done;
RUN mkdir /tmp/build
WORKDIR /tmp/build

RUN echo `pwd`
RUN ls -lR /tmp/srt-game-server
RUN echo "Running cmake /tmp/srt-game-server"
RUN cmake /tmp/srt-game-server
RUN echo "Running cmake --build ."
RUN cmake --build .

# Run
FROM fedora:${fedora_version} as base-env
COPY containerbuild/srt.repo /etc/yum.repos.d/
RUN sudo dnf install Box2D-2.3.1-12.fc32.x86_64 Box2D-devel-2.3.1-12.fc32.x86_64 compat-openssl10 openssl poco-devel poco-foundation protobuf protobuf-devel qpid-proton-cpp qpid-proton-cpp-devel --assumeyes --verbose

ENV USER_UID=1000
ENV USER_NAME=srt
ENV EXECUTABLE_NAME=srt-game-server.bin
ENV EXECUTABLE=/home/${USER_NAME}/bin/${EXECUTABLE_NAME}
ENV BROKER_URI="tcp://127.0.0.1:5672"
ENV LOG_LEVEL="1"
ENV SLEEP_CYCLE="1500"

WORKDIR /

RUN mkdir -p /home/${USER_NAME}/bin
#COPY bin/${EXECUTABLE_NAME} /home/${USER_NAME}/bin
COPY --from=build-env /tmp/build/srt-game-server /home/${USER_NAME}/bin/${EXECUTABLE_NAME}
COPY containerbuild/bin/entrypoint /home/${USER_NAME}/bin

RUN chown -R `id -u`:0 /home/${USER_NAME}/bin && chmod -R 755 /home/${USER_NAME}/bin
USER ${USER_UID}:0
ENTRYPOINT "/home/srt/bin/entrypoint" "--broker-uri" "$BROKER_URI" "-v" "$LOG_LEVEL" "--sleep-cycle" "$SLEEP_CYCLE"

LABEL \
      com.srt.component="srt-game-server" \
      description="Space Ring Things game physics server" \
      io.k8s.description="Main game simulation container for Space Ring Things" \
      io.k8s.display-name="Space Ring Things 0.2" \
      maintainer="Roddie Kieley <rkieley@apache.org>" \
      name="roddiekieley/srt-game-server" \
      summary="Space Ring Things game physics server" \
      version="0.2"
