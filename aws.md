# Cloud servers and cloud providers

Cloud server is powerful physical or virtual infrastructure that performs application and informatin processing storage.

Cloud providers allows devs to use cloud servers

Amazon Web Services provides hundreds of services to fit the need of devs

AWS prodives a globally distributed IaaS (infrastructure as a service) that provides access to enterprise grade solutions for companies.

## EC2

The workhorse of aws. basic servers

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

## EB (Elastic Beanstalk)

Amazon's GUI for EC2 to make the process easier.

WARNING! A database instance that is part of your environment is tied to the lifecycle of your environment. You can't remove it from your environment once added. If you terminate the environment, the database instance is terminated as well!

## S3

Data is stored as objects in buckets that can be accessed using a key. Not a server

## RDS (relational database service), DynamoDB is for non-relational db

provides RD instances that are easily integrated with AWS.

## ECR (Elastic container registry)

fully-managed container registry that makes it easy for developers to store images
used for static file serving

## IAM

Amazon's tool to control account level security. This allows you to control who can access what in your AWS account.
