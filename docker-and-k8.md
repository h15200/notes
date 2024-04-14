# Docker

## Context

- first came bare metal servers connected to each other in a single data server
- Server computers used to host one app, which often did not utilizie the full
  capacticy of the machine.
- then came VMs to have more flexible resource sharing. Each VM has OS layer data
- Virtual machines were developed to have multiple apps with multiple OS's,
  controlled by the `hypervisor`.
  - there was still a necessity to manage the OS and applications
- Then containers were developed to do the same thing that virtual machines did
  but on only ONE OS (linux) to pacakge multiple apps. Instead of a hypervisor
  who oversees multiple OS's, a `docker daemon` is overseeing multiple apps
  without the need of multiple OS.
  - Containers are MUCH faster and more light-weight than virtual machines,
    as it doesn't have any extra data below the OS layer, making them highly scalable and portable.
  - containers like `Docker` recommends a best practice to have one process
    per container
  - issue is that there is no easy way for containers to talk to each other,
    so juggling multiple containers within an app is tricky
  - you need an installation script to start the container apps, but there
    is no good solution when machines fail
  - automatically scale apps based on demand
  - cloud native, meaning it can be run on any public cloud
- Kubernetes or k8s solves the problem with containers by introducing a new
  unit of node called `pods`. Each `pod` can host multiple containers. A pod
  has its own ip address so communciating within one pod between containers
  can be done in localhost. The orchestration layer also handles starting
  and self healing when nodes die.

- Docker is an easy way to work with containers
- `Dockerhub` is like github, for containers
- k8s is used for containers to talk to each other
- `helm` is used to easily create k8s applications

## Container Images

- Templates for containers. Can be kept in a dockerhub repo and shared freely
  between developers on a team, across different testing and staging, and
  production platforms.
- Each container is instantiated from a container image.
- If everyone in an app's ecosystem is using a container instantiated from the
  same image, they're all guaranteed to be using the same dependencies.
- each container image has the bare essential binaries for the os like `Alpine`

### Layering

- Images can be built on top of another image.
  ex. - if you want to create an image that will build a container running the Ubuntu 16.0.4 distro AND node 10.15, we can build the node image on TOP of the Ubuntu image.
- Docker starts from a base linux kernel that ALL containers use, then layer the differences on top of that kernel.

## Dockerfile

- To define a docker image, we create a text file called Dockerfile, and execute with `docker build`
  How to add a new layer to an existing image inside a dockerfile

```
FROM node:10.15
WORKDIR /usr/src/app
COPY package.json /usr/src/app
RUN npm install
COPY . /usr/src/app
CMD node index.js
EXPOSE 3000
```

## general workflow

- Make dockerfile
- run `docker build` -> make a single docker image (read-only) based on `DockerFile`
- run `docker run` -> make actual docker container (read-write) on top layer, with underlying read-only info based on image
- `docker compose` -> start multiple containers at once based on `compose.yaml` file

Linked to Docker Hub, which is often then connected to Travis CI, and AWS

## Union File System

- docker images are stored as series of `read-only layers`
- when we start a container, Docker takes the image and adds a `read-write layer`
- If the running container modifies an existing file, the file is copied out of
  the underlying read-only layer and into the top-most read-write layer.
- The version in the read-write layer hides the underlying file, but does not
  destroy it. It still exists in the underlying layer.
- When a Docker container is deleted, relaunching the image will start a fresh
  container WITHOUT any changes made in the previously running container. Without
  volumes, container changes on the read-write level will not persist!

## Volumes

- A docker container has underlying read only image info as well as write
  level changes.
- Volumes are Docker's mechanism for sharing changes on the read-write level
  of a container, which lives on the `host file system`.
- Docker host file system will take the dockerfile image, build the container,
  then put the info from the volume on TOP to get the latest version of the
  docker container.

## docker-compose

- Containers are runtime environments. Usually run only a single main process
  in one Docker container.
- One container provides one service in your project. If you only need one
  container, `Docker build` suffices
- It is not unusual to have multiple containers running each process that rely
  on each other.
- Rather than manually coordinating the creation of these containers at run
  time, we can use the `docker-compose` file to coordinate them using a `YAML` file.
- use `Docker compose` to run the instructions in `compose.yaml` file to run
  and coordinate multiple containers and dependencies

## YAML - "YAML Ain't Markup Language"

- ends with `.yml`
- human-readable structured data format that is used for configuration files.
  Simple syntax like indentation and dashes, dictionaries, and arrays.
- Be VERY careful about whitespace and indentation

```
version: "3"
services:
  test:
    image: stuff
    container_name: "test"
```

## k8s

- Units

  - `Cluster` is the orchestration layer which has a control plane and nodes.
    Can be deployed on a physical machine or a VM. Also has services to
    expose pods.
  - `Node` is a machine or a vm that serves as a worker. has a `kubelet`
    to communicate with the cluster control plane, and contains a bunch of pods
  - `Pod`
    - runs on Nodes
    - smallest deployable unit in k8s
    - hosts multiple containers

- k8s cluster coordinates a group of highly available computers to work as a single unit

  - the control plane coordingates the cluster with self healing, scaling,
    and monitoring health of nodes
  - the nodes within a cluster are the actual workers doing the work to run apps

- k8s generally runs on a private network and is not exposed to the outside world

  - within the same cluster, all pods are visible from services
  - t

- `kubectl` gives users access to Kubernetes API to communicate within a cluster
- cli can be used to monitor deployments, logs, health status of
  nodes and pods
