FROM ubuntu:24.04

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    curl \
    zip \
    unzip \
    ninja-build \
    pkg-config \
    && rm -rf /var/lib/apt/lists/*

# Create user matching Jenkins (1000 is the first user on Ubuntu)
ARG UID=1000
ARG GID=1000

RUN groupadd -g $GID jenkins || true \
 && useradd -m -u $UID -g $GID jenkins || true

WORKDIR /workspace

RUN git clone https://github.com/microsoft/vcpkg.git \
 && ./vcpkg/bootstrap-vcpkg.sh

RUN chown -R jenkins:jenkins /workspace

ENV VCPKG_ROOT=/workspace/vcpkg
ENV CMAKE_TOOLCHAIN_FILE=/workspace/vcpkg/scripts/buildsystems/vcpkg.cmake
ENV VCPKG_FEATURE_FLAGS=manifests,binarycaching
ENV VCPKG_DEFAULT_BINARY_CACHE=/vcpkg-cache
ENV VCPKG_DISABLE_METRICS=1

CMD ["bash"]