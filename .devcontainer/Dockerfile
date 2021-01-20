#Build
FROM fedora:30 as build-env

RUN sudo dnf install activemq-cpp activemq-cpp-devel apr apr-util apr-util-devel Box2D Box2D-devel compat-openssl10 openssl crypto-utils poco-devel poco-foundation protobuf protobuf-devel gcc g++ cmake git --assumeyes --verbose

USER root

RUN dnf install -y skopeo wget zsh jq iputils httpd-tools procps

RUN dnf -y install dnf-plugins-core && \
    dnf config-manager --add-repo https://download.docker.com/linux/fedora/docker-ce.repo && \
    dnf -y install docker-ce-cli

# install stern
RUN cd /usr/local/bin && \
    wget https://github.com/wercker/stern/releases/download/1.11.0/stern_linux_amd64 -O /usr/local/bin/stern && \
    chmod 755 /usr/local/bin/stern && \
# install knative client
    wget -qO- https://mirror.openshift.com/pub/openshift-v4/clients/serverless/0.17.3/kn-linux-amd64-0.17.3.tar.gz | tar -zxvf - -C /usr/local/bin ./kn && chmod 755 /usr/local/bin/kn && \
# install hey
    wget https://mwh-demo-assets.s3-ap-southeast-2.amazonaws.com/hey_linux_amd64 -O /usr/local/bin/hey && \
    chmod 755 /usr/local/bin/hey && \
# install istioctl
    curl -L https://github.com/istio/istio/releases/download/1.4.7/istioctl-1.4.7-linux.tar.gz | tar -zxvf - -C /usr/local/bin && chmod 755 /usr/local/bin/istioctl

# FIXME: move with other dnf packages
RUN dnf -y install unzip

# install AWS cli
RUN curl "https://d1vvhvl2y92vvt.cloudfront.net/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip" && \
    unzip awscliv2.zip && ./aws/install && rm awscliv2.zip && rm -rf ./aws 
    # && ln -s /usr/local/bin/aws2 /usr/local/bin/aws

# install a more modern version of tkn
RUN curl -L https://github.com/tektoncd/cli/releases/download/v0.13.1/tkn_0.13.1_Linux_x86_64.tar.gz | \
    tar -xvzf - -C /usr/local/bin/ tkn && chmod 755 /usr/local/bin/tkn

# overwrite existing oc with the absolute newest version of the openshift client
RUN curl -L https://mirror.openshift.com/pub/openshift-v4/clients/ocp/latest/openshift-client-linux.tar.gz | \
    tar -xvzf - -C /usr/local/bin/ oc && chmod 755 /usr/local/bin/oc && ln -s /usr/local/bin/oc /usr/local/bin/kubectl

# Add latest helm 3.0 client
RUN wget https://mirror.openshift.com/pub/openshift-v4/clients/helm/latest/helm-linux-amd64 -O /usr/local/bin/helm && \
    chmod 755 /usr/local/bin/helm


ENV USER_UID=1000
ENV USER_NAME=srt
ENV EXECUTABLE_NAME=srt-game-server.bin
ENV EXECUTABLE=/home/${USER_NAME}/bin/${EXECUTABLE_NAME}
ENV BROKER_URI="tcp://127.0.0.1:61613?wireFormat=stomp"

# Add $USER_NAME as $USER_UID to root group
RUN useradd -u $USER_UID -g 0 $USER_NAME

USER ${USER_UID}:0

# install and configure ohmyzsh for jboss user
RUN wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh
#COPY .zshrc.example $HOME/.zshrc