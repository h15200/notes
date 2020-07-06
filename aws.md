# Cloud servers and cloud providers

Cloud server is powerful physical or virtual infrastructure that performs application and informatin processing storage.

Cloud providers allows devs to use cloud servers

Amazon Web Services provides hundreds of services to fit the need of devs

## EC2

The workhorse of aws.

- Instances: virtual computing environments
- Amazon Machine Images: preconfigured templates for your instances
- Instance types: various CPU configurations, memory, storage, networking capacity
- regions and zones: multiple physical locations for your resources
- Kay pairs: provide secure login information with SSH
- Security groups: Firewall that enables you to specify the protocols, ports, and IP ranges that can reach your instances

## AMI (amazon machine images & instances)

From an AMI, you launch an EC2 instance, which is a copy of the AMI running as a virtual server in the cloud. You can launch multiple instances of an AMI.

Instances can be run on various hardware configurations for CPU, RAM, and network capacity options.

More resources = more cost

There are regions available globally. You can even use multiple instances and design it such that if one instance fails, another instance will take over
