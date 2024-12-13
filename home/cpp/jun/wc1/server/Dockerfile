FROM ubuntu:22.04

# ***

RUN apt update 

RUN apt install -y build-essential
RUN apt install -y qt6-base-dev
RUN apt install -y lua5.4
RUN apt install -y liblua5.4-dev
RUN apt install -y wget

RUN rm -rf /var/lib/apt/lists/*

# ***

RUN wget https://boostorg.jfrog.io/artifactory/main/release/1.86.0/source/boost_1_86_0.tar.gz
RUN tar -xvzf boost_1_86_0.tar.gz 

RUN cd boost_1_86_0 && \
    ./bootstrap.sh && \
    ./b2 toolset=gcc threading=multi link=shared,static --prefix=/usr/local && \
    cd ..
RUN rm -rf boost_1_86_0.tar.gz

# ***

ENV BOOST_INCLUDE_DIR=/boost_1_86_0
ENV BOOST_LIBRARY_DIR=/boost_1_86_0/stage/lib

ENV PATH="/usr/lib/qt6/bin:${PATH}"

# ***

RUN echo "Boost dir contents:" && \
    ls -al /boost_1_86_0/stage/lib

WORKDIR /wc1
COPY . .

RUN echo "qmake version:" && \
    qmake --version

ENV CC=gcc
ENV CXX=g++

# Application only!
WORKDIR /wc1/app 
RUN qmake CONFIG+=release
RUN make

CMD ["./app"]