#Build
ARG fedora_version=33
FROM fedora:${fedora_version} as build-env

RUN sudo dnf install Box2D.x86_64 Box2D-devel.x86_64 compat-openssl10 openssl poco-devel poco-foundation protobuf protobuf-devel gcc g++ cmake git qpid-proton-cpp qpid-proton-cpp-devel yaml-cpp-devel --assumeyes --verbose

COPY CMakeLists.txt /tmp/srt-game-server/
COPY config.yaml /tmp/srt-game-server/
COPY src/ /tmp/srt-game-server/src/

WORKDIR /tmp/srt-game-server/src/Proto
RUN for i in `ls -lC1 *.proto`; do `echo protoc $i --cpp_out=.`; done;
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
RUN sudo dnf install Box2D.x86_64 Box2D-devel.x86_64 compat-openssl10 openssl poco-devel poco-foundation protobuf protobuf-devel qpid-proton-cpp qpid-proton-cpp-devel yaml-cpp --assumeyes --verbose

ENV USER_UID=1000
ENV USER_NAME=srt
ENV EXECUTABLE_NAME=srt-game-server.bin
ENV EXECUTABLE=/home/${USER_NAME}/bin/${EXECUTABLE_NAME}
ENV BROKER_URI=tcp://artemiscloud:5672
ENV LOG_LEVEL=1
ENV SLEEP_CYCLE=1500

WORKDIR /

RUN mkdir -p /home/${USER_NAME}/bin
#COPY bin/${EXECUTABLE_NAME} /home/${USER_NAME}/bin
COPY --from=build-env /tmp/build/srt-game-server /home/${USER_NAME}/bin/${EXECUTABLE_NAME}
COPY config.yaml /
COPY containerbuild/bin/entrypoint /home/${USER_NAME}/bin

RUN chown -R `id -u`:0 /home/${USER_NAME}/bin && chmod -R 755 /home/${USER_NAME}/bin
USER ${USER_UID}:0
ENTRYPOINT /home/srt/bin/entrypoint --broker-uri ${BROKER_URI} --sleep-cycle ${SLEEP_CYCLE}
CMD [-v, ${LOG_LEVEL}]

LABEL \
      com.srt.component="srt-game-server" \
      description="Space Ring Things game physics server" \
      io.k8s.description="Main game simulation container for Space Ring Things" \
      io.k8s.display-name="Space Ring Things 0.3" \
      maintainer="Roddie Kieley <rkieley@apache.org>" \
      name="roddiekieley/srt-game-server" \
      summary="Space Ring Things game physics server" \
      version="0.3"
