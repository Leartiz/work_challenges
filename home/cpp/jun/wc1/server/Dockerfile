FROM ubuntu:22.04

# ***

RUN apt update 

RUN apt install -y \
    build-essential \
    qt6-base-dev \
    libboost-all-dev \
    lua5.4 \
    liblua5.4-dev 

RUN rm -rf /var/lib/apt/lists/*

# ***

ENV PATH="/usr/lib/qt6/bin:${PATH}"

WORKDIR /wc1
COPY . .

RUN qmake --version

WORKDIR /wc1/app
RUN qmake 
RUN make

CMD ["./main"]