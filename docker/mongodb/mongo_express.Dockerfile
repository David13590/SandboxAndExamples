FROM mongo-express:latest

RUN apt update && apt install -y \
	mongodb-mongosh
RUN apt-get update -y

EXPOSE 8081	
