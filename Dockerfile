FROM ubuntu:latest
RUN mkdir project
COPY gRPCinstall.sh ./project
RUN ./project/gRPCinstall.sh
COPY . ./project
# This sets up basic docker container but does not compile code
# The task is to make sure compilations occurs correctly but for 
# some reason this does not take place. Please solve this