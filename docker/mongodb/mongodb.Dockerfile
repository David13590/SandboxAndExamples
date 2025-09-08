FROM mongo:latest

RUN apt-get update && apt-get install -y \
	mongodb-mongosh
RUN apt-get update -y

EXPOSE 8081
