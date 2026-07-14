FROM debian:trixie-slim

WORKDIR /s1

RUN apt update && \
    apt install -y \
    bchunk \
    binutils-mipsel-linux-gnu \
    build-essential \
    cpp-mipsel-linux-gnu \
    gcc-mipsel-linux-gnu \
    git \
    python3 \
    pip

RUN git config --global --add safe.directory /s1

RUN python3 -m pip install --break-system-packages colorama GitPython matplotlib pandas watchdog levenshtein cxxfilt