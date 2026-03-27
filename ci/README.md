# Install Jenkins using Docker Compose

This directory contains a Docker Compose configuration for a quick setup of Jenkins. This setup is not intended for production systems. This setup is designed only for local development of this project.

Credits: This approach is taken from https://github.com/vdespa/install-jenkins-docker, which in turn is mostly based on the [official instructions](https://www.jenkins.io/doc/book/installing/docker/) but takes advantage of Docker Compose (by using a `docker-compose.yml` file) to reduce the number of steps needed to get Jenkins up and running.

# Docker Installation

## Step 0

Install Docker locally (Docker Desktop is easiest).

## Step 1

Open a terminal window in this directory. Then build the Jenkins Docker image:

```
docker build -t my-jenkins .\jenkins\
```

## Step 3

Start Jenkins:

```
docker compose up -d
```

## Step 4

Open Jenkins by going to: [http://localhost:8080/](http://localhost:8080/) and finish the installation process.

## Step 5

Navigate to the Plugins menu and install the Docker Pipeline plugin to enable Docker Agents in Jenkins pipelines.

## Step 6

If you wish to stop Jenkins, run:

```
docker compose down
```

If you wish to start Jenkins again later, just run the same command from Step 3.


# Removing Jenkins

Once you are done playing with Jenkins, maybe it is time to clean things up.

Run the following command to terminate Jenkins and to remove all volumes and images used:

```
docker compose down --volumes --rmi all 
```
