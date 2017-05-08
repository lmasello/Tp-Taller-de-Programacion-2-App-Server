FROM ubuntu:latest

RUN apt-get -y update
RUN apt-get install -y g++ make cmake git pkg-config
RUN apt-get install -y wget

RUN wget https://github.com/mongodb/mongo-c-driver/releases/download/1.6.1/mongo-c-driver-1.6.1.tar.gz && \
    tar xzf mongo-c-driver-1.6.1.tar.gz && \
    cd mongo-c-driver-1.6.1 && \
    ./configure --disable-automatic-init-and-cleanup && \
    make && make install

RUN git clone https://github.com/mongodb/mongo-cxx-driver.git \
        --branch releases/stable --depth 1 && \
    cd mongo-cxx-driver/build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local ..  && \
    make EP_mnmlstc_core && \
    make && make install

ADD . /code
WORKDIR /code

RUN cmake .
RUN make

EXPOSE 8000

CMD ["sh", "-c", "Tp_Taller_de_Programacion_2_App_Server"]
