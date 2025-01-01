FROM alpine

# ***

RUN apk add --no-cache \
    build-base \
    qt6-qtbase-dev \
    lua5.4 \
    lua5.4-dev \
    wget

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

RUN echo "BOOST_INCLUDE_DIR=${BOOST_INCLUDE_DIR}" && \
    echo "BOOST_LIBRARY_DIR=${BOOST_LIBRARY_DIR}"

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