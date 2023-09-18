# Use an official Ubuntu as a parent image
#FROM ubuntu:latest
FROM arm32v7/ubuntu:latest

# Install Qt and other dependencies
RUN apt-get update && apt-get install -y \
    qtbase5-dev \
    g++ \
    make \
    git 
RUN apt-get install -y cmake libzmq3-dev


RUN apt install -y build-essential
# Set the working directory in the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Compile the Qt project
WORKDIR /app/QUaServer/src/amalgamation/
RUN qmake amalgamation.pro #/app/QUaServer/src/amalgamation
RUN make all

WORKDIR /app/MyServer/
RUN qmake MyServer.pro
RUN make

# Make port 4840 available to the world outside this container
EXPOSE 4841

# Run your server when the container launches
CMD ["./MyServer"]
