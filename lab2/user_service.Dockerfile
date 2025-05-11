# syntax=docker/dockerfile:1.7-labs

# Этап сборки
FROM gcc:15.1.0 as builder

# Фиксируем версии для безопасности
ENV POCO_VERSION=1.14.1
ENV TZ=Europe/Moscow

# Установка зависимостей с очисткой кэша
RUN apt-get update && \
    apt-get install -y \
    git \
    cmake \
    libpq-dev \
    libssl-dev \
    zlib1g-dev \
    librdkafka-dev

RUN apt-get update && \
    apt-get install -y \
    libpq5 \
    libssl3 \
    zlib1g \
    librdkafka++1 \
    libboost-system1.74.0 \
    python3 \
    pip \
    && rm -rf /var/lib/apt/lists/* && \
    ldconfig

RUN git clone -b poco-$POCO_VERSION-release --depth 1 https://github.com/pocoproject/poco.git && \
    cd poco && \
    mkdir cmake-build && \
    cd cmake-build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DENABLE_TESTS=OFF .. && \
    cmake --build . --parallel $(nproc) && \
    cmake --install . && \
    cd ../.. && \
    rm -rf poco

WORKDIR /app

RUN ldconfig
COPY requirements.txt .
RUN pip3 install -r /app/requirements.txt --break-system-packages
