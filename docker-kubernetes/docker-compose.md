# Docker Compose

- Configure relationships between containers
- Save docker container run settings in a easy to read file
- Create one linear development startups
- **NOTE**: not designed for production environments, ideal for local development and test

## docker-compose.yml

Default config file, could be any (specify with -f)

### Template

```yaml
version: '3.1'  # if no version is specified then v1 is assumed. Recommend v2 minimum

services:  # containers. same as docker run
  servicename: # a friendly name. this is also DNS name inside network
    image: # Optional if you use build:
    command: # Optional, replace the default CMD specified by the image
    environment: # Optional, same as -e in docker run
    volumes: # Optional, same as -v in docker run
    depends_on: # Tells compose the relationships between the containers
    build:  # Will tell compose how to build image when no image in cache (or when specified)
      context:  # Where to build dockerfile (eg. .)
      dockerfile: # Name of dockerfile (eg. nginx.Dockerfile)

  servicename2:

volumes: # Optional, same as docker volume create

networks: # Optional, same as docker network create
```

## Miscelanea

DNS names (set as aliases) for containers in a compose file come from the
service name declared in the .yml

## docker-compose

### Commands

#### *up*

Setup volumes/networks and start all containers

    docker-compose up -d --build

- d: to run in the background
- build: to rebuild images

The bridge network is created at runtime by default so the containers can
communicate with one another across it.

### *build*

    docker-compose build

#### *down*

Stop all containers and remove cont/vol/net

    docker-compose down -v --rmi local


- v: To remove also the volumes
- rmi local: remove images which do not have custom tag (no image name)

#### *logs*

    docker-compose logs -f

#### *ps*

Similar to ls


#### *top*

Get current process running on containers



