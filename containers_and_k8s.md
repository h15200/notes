# Context

- first came bare metal servers connected to each other in a single data server
- VMs to have more flexible resource sharing. Each VM has OS layer data
- Containers are more lightweight and does not have any data below OS layer.
    - containers like `Docker` recommends a best practice to have one process
    per container
    - issue is that there is no easy way for containers to talk to each other,
    so juggling multiple containers within an app is tricky
    - you need an installation script to start the container apps, but there
    is no good solution when  machines fail 
- Kubernetes or k8s solves the problem with containers by introducing a new
unit of node called `pods`. Each `pod` can host multiple containers. A pod
has its own ip address so communciating within one pod between containers
can be done in localhost. The orchestration layer also handles starting
and self healing when nodes die. 

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
