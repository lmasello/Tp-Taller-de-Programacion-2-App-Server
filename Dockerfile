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

###########################################3
# Mongo Installation:
# Import MongoDB public GPG key AND create a MongoDB list file
RUN apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv EA312927
RUN apt-get update
RUN apt-get install -y --no-install-recommends software-properties-common
RUN echo "deb http://repo.mongodb.org/apt/ubuntu $(cat /etc/lsb-release | grep DISTRIB_CODENAME | cut -d= -f2)/mongodb-org/3.2 multiverse" | tee /etc/apt/sources.list.d/mongodb-org-3.2.list

# Update apt-get sources AND install MongoDB
RUN apt-get update && apt-get install -y mongodb-org

# Create the MongoDB data directory
RUN mkdir -p /data/db
#############################################3

WORKDIR /code
COPY . .

RUN cmake .
RUN make

EXPOSE 8000

ENTRYPOINT ["./start.sh"]
