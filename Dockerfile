FROM gcc:latest

WORKDIR /ysh

RUN mkdir /ysh/bin

COPY ["./", "/ysh"]

