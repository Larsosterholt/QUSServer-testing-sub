# Use an official Ubuntu as a parent image
FROM ubuntu:latest 
#sudo docker build -t my_server_image .

#sudo docker buildx build --output type=docker --platform linux/arm/v7 -t my_server_image_raspberry_pi .
#FROM arm32v7/ubuntu:latest

# Install Qt and other dependencies
RUN apt-get update && apt-get install -y \
    qtbase5-dev \
    qt5-qmake \
    g++ \
    make 
#    git \

RUN    apt-get install -y cmake libzmq3-dev


RUN apt install -y build-essential
# Set the working directory in the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Compile the SDK
WORKDIR /app/QUaServer/src/amalgamation/
RUN qmake amalgamation.pro #/app/QUaServer/src/amalgamation
RUN make all

# Compile the server
WORKDIR /app/MyServer/
RUN qmake MyServer.pro
RUN make

# Make port 4841 available to the world outside this container
EXPOSE 4841

# Run your server when the container launches
CMD ["./MyServer"]
