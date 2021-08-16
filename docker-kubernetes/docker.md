
# Docker and Kubernetes


## Resources

Landscape with a map of all technology stack: https://landscape.cncf.io/?zoom=120


Docker CE: community edition
Docker EE: enterprise edition (support + extra features)

- [Inmutable infraestructure](https://www.oreilly.com/radar/an-introduction-to-immutable-infrastructure/)
- [The 12 factors](https://12factor.net/)

## Miscellany

### Image vs container

Image: app we want to run
Container: instance of that image running as a process

Many containers can be running off the same image

### Image registry

Like GitHub for source code, most important: Docker Hub

### Container vs VM

Containers are not mini VM's, they are just process

Try do a docker container ps to see the process id of a container
Then, try `ps aux | grep <name>` and this process will be available and seeable outside

They are just process running on the host

## Container

#### *run*

    docker container run --publish 80:80 nginx [COMMANDS]

- nginx: pull nginx image
- publish: open port 80 on the host IP and routes that traffic to container IP, port 80

  bind error if host port is being used

- --detach: run in background
- -it: interactive and tty (open a prompt) if "bash" is passed as commands
- --rm: removes container after execution (useful for testing)

        docker container run --rm -it <image> bash

- --net-alias
    With --net-alias, one container can access the other container only if they are
    on the same network. In other words, in addition to --net-alias foo and
    --net-alias bar, you need to start both containers with --net foobar_net after
    creating the network with docker network create foobar_net

Process:

1. Looks for image locally in image cache
2. Looks in remote image repository (Docker Hub)
3. Download latest version (nginx:latest)
4. Creates new container based on that image and prepares to start
5. Gives a virtual IP on a private network inside docker engine
6. Opens up a port 80 on host and forwards to port 80 in container
7. Start container by using the CMD in the image Dockerfile

#### *stop*

Stop a running container

    docker container stop <container>

#### *start*

Start an stopped container

    docker container start -ai <container>

- ai: attach interactive

#### *exec*

Execute a command on a container (for example, a terminal)

    docker container exec -it <container> bash

Exec run an additional process so when exiting, container will still running

#### *ls*

Show running containers

    docker container ls

Show all containers

    docker container ls -a

#### *logs*

Last logs of container

    docker container logs <container>

#### *top, inspect, stats*

Get top execution result of a container

    docker container top <container>

Inspect: details of one container config
Stats: performance stats for all containers

#### *rm*

Remove containers

    docker container rm [--force] <conteiner> [<container2> ...]

- force to remove running containers

### Virtual networks

Dockers are attached to a virtual network (docker0), which can access internet
via NAT You can also create a private network for some dockers and make them
interact with each other.

To view docker IP:

    docker container inspect --format '{{ .NetworkSettings.IPAddress }}' <docker>

DNS resolution works by default when creating a bridge network
The default bridge network does NOT have DNS resolution, so you can pass --link
when creating a container.

## Network driver

Built-in or 3rd party extensions that give you virtual network features

#### *ls*

Show all networks

    docker network ls

- bridge/docker0: default network which is NAT'ed behind the Host IP (by default all containers are attached to it)
- host: special network that gains performance by skipping virtual network but sacrifices security of container model
- none: removes eth0 and only leaves you with localhost interface in container

#### *inspect*

Show information of network such as containers attached to it

    docker network inspect <network>

#### *connect*

When container is not running (use container run --network <network>)

When container is running

    docker network connect <network> <container>

It dynamically creates a NIC (Network Interface Controller) in a container on an existing virtual network
This command will not disconnect previous network container were attached, it will just creates a new network adapter on the container

### Good practices

- Create apps so frontend/backend si on same Docker network
- Their inter-communication never leaves host
- All externally exposed ports closed by default
- Manually expose ports via -p
- Never rely on IP addresses (use DNS naming) => always creates custom networks
(which have enabled DNS resolution by default) (docker compose will simplify
this)

### Container Lifetime & Persintent Data

Containers are innmutable and ephemeral

- Inmutable: only re-deploy containers, not change
- Separation of concerns: unique data will be persistant on the layers until container is removed
- Data volumes: outside container Unique FS
- Bind Mounts: link container path to host path

#### Data Volumes

VOLUME:


## Image

- App binaries and dependencies
- Metadata about the image data and how to run the image
- Ordered collection of root filesystem changes and the corresponding execution
  parameters for use within a container runtime
- Not a complete OS. No kernel, no drivers... the host will provide them for Docker
- Small as one file or big as distro

### Layers

Make layers about changes
Every layer gets a unique SHA

Example:

1. Start from ubuntu
2. Install packages with apt
3. Set environment variable
4. Copy some files
5. Open a port

If another image uses the same version of Ubuntu than previous one, it will
reuse that layer, saving time and space (cache) (knows how to match layers
thanks to SHA)

Custom image:

1. Custom
2. Install Apache
3. Open port 80
4. Copy website A | Copy website B  (this will create two images but only 5
   layers will be stored (1-3, 4 and 5)

### Copy On Write (COW)

- Layers work under COW paradigm. Every layer works as an independent file system.
- Multiple containers can share a layer and if they dont write on it, it will
be only one layer stored
- If a container writes on the common layer, a diff of the files edited on that
layer will be stored locally on the container (who has modified the layer)
layer
- Containers are really a running process and those diff files

### Naming image

- Repository: username/image_name (if it is official only will have image_name)
- Tag: labels to point to Image ID's (many labels could be created to point to same ID)
- Image ID: unique identifier

### Dockerfile

    - FROM <image>:<tag> => base OS (if no OS is needed use 'scratch')
    - ENV <key> <value>
    - RUN <bash commands> \
         && <more bash commands> \
         && ...
         => every RUN step will create a different docker layer
    - EXPOSE <port> <port> ... => expose these ports on the docker virtual network you still need to use -p or -P to open/forward these ports on host
    - CMD ["commands", "more commands"] => required: run this command when container is launched (only one CMD allowed, so if there are multiple, last one wins)
    - WORKDIR <dir> => change working directory, preferred to 'RUN cd <path>'
    - COPY <src> <dst> => copy files from local machine into container

#### Good practices

- When a layer changes, all following layers need to be rebuilt
- Always copy code or things to be changed at the very end
- Split RUN commands when needed focussing on reusability

### Commands

#### *pull*

Download an image

    docker image pull <image_name>

#### *ls*

List installed images

    docker image ls

#### *prune*

Clean up dangling images

#### *history*

Show layers of changes made in image

    docker image history <image>

#### *inspect*

Shows image metadata

    docker image inspect <image>

#### *tag*

Create a new tag for a given tag

    docker image tag <old-tag> <new-tag>

#### *build*

Create an image from a Dockerfile file

    docker image build -t <image_name> .

## System

#### *prune*

Clean up everything

#### *df*

Show docker filesystem usage
