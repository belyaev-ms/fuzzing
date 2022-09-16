FROM ubuntu:20.04 AS fuzzing-env

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y git && rm -rf /var/lib/apt/lists/*
WORKDIR /tmp
RUN git clone https://github.com/google/fuzzing.git fuzzing
WORKDIR /tmp/fuzzing/tutorial/libFuzzer
RUN sed -i 's/sudo //g' ./install-deps.sh
RUN sed -i 's/libgcrypt11-dev/libgcrypt20-dev/g' ./install-deps.sh
RUN apt-get update \
    && ./install-deps.sh \
    && apt-get install -y \
        clang \
        clang-tidy \
        cppcheck \
        lcov \
        libboost-all-dev \
        libtinfo5 \
    && rm -rf /var/lib/apt/lists/*

FROM fuzzing-env

RUN mkdir /root/src && mkdir /root/build
WORKDIR /root/build