# Docker

- Dev Ops : help devs have the same exact environment when coding a project.
- Server computers used to host one app, which often did not utilizie the full
  capacticy of the machine.
- Virtual machines were developed to have multiple apps with multiple OS's,
  controlled by the `hypervisor`.
- Then containers were developed to do the same thing that virtual machines did
  but on only ONE OS (linux) to pacakge multiple apps. Instead of a hypervisor
  who oversees multiple OS's, a `docker daemon` is overseeing multiple apps
  without the need of multiple OS.
- Containers are MUCH faster and more light-weight than virtual machines,
  making them highly scalable and portable.

- Virtual machines = multiple houses
- Containers = multiple apartment units

- Dockerhub like github, for containers

## Container Images

- Templates for containers. Can be kept in a dockerhub repo and shared freely
  between developers on a team, across different testing and staging, and
  production platforms.
- Each container is instantiated from a container image.
- If everyone in an app's ecosystem is using a container instantiated from the
  same image, they're all guaranteed to be using the same dependencies.

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
- run `docker build` -> make docker image (read-only)
- run `docker run` -> make actual docker container (read-write) on top layer, with underlying read-only info based on image
- `docker compose` -> orchestrates the starting and stopping of containers

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
- One container provides one service in your project.
- It is not unusual to have multiple containers running each process that rely
  on each other.
- Rather than manually coordinating the creation of these containers at run
  time, we can use docker-compose to coordinate them using a `YAML` file.

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
