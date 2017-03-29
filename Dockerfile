FROM ubuntu:latest

RUN apt-get -y update
RUN apt-get install -y g++ make cmake

COPY . /usr/src/music-io-application-server
WORKDIR /usr/src/music-io-application-server

RUN cmake .
RUN make

EXPOSE 8000

CMD ["sh", "-c", "./Tp_Taller_de_Programacion_2_App_Server"]
