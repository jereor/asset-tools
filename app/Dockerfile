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

WORKDIR /workspace
RUN git clone https://github.com/microsoft/vcpkg.git \
 && ./vcpkg/bootstrap-vcpkg.sh \
 && chown -R 1000:1000 /workspace/vcpkg

ENV VCPKG_DISABLE_METRICS=1
ENV VCPKG_FEATURE_FLAGS=manifests,binarycaching
ENV VCPKG_DEFAULT_BINARY_CACHE=/vcpkg-cache
ENV VCPKG_ROOT=/workspace/vcpkg
ENV CMAKE_TOOLCHAIN_FILE=/workspace/vcpkg/scripts/buildsystems/vcpkg.cmake

CMD ["bash"]