# Use an official Ubuntu as a parent image
FROM ubuntu:latest

# Install Qt and other dependencies
RUN apt-get update && apt-get install -y \
    qtbase5-dev \
    g++ \
    make \
    git 

RUN apt install -y build-essential
# Set the working directory in the container
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app

# Compile the Qt project
RUN apt-get install -y cmake libzmq3-dev
RUN qmake /app/QUaServer/src/amalgamation/amalgamation.pro #/app/QUaServer/src/amalgamation
RUN make all
RUN qmake /app/MyServer/MyServer.pro
RUN make

# Make port 4840 available to the world outside this container
#EXPOSE 4840

# Run your server when the container launches
#CMD ["./MyServer"]
