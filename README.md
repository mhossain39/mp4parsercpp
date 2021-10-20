# mp4parsercpp
Parse and get info + data from mp4 file


Tested on Ubuntu 18.04

# Install package dependencies
RUN apt-get update
RUN apt-get install -y --no-install-recommends \
        build-essential \
        wget \
        libcurl4-openssl-dev \
        ca-certificates \
        cmake
RUN apt-get clean

# Build Application

g++ parsemp4.cpp  -o mp4parser -lcurl


# Run Application

./mp4parser