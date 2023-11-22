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

### Elastic IP

- public ip addresses get rotated over time, so always best to link an elastic
  ip to EC2 instances so it's static

## AMI (amazon machine images & instances)

From an AMI, you launch an EC2 instance, which is a copy of the AMI running as a virtual server in the cloud. You can launch multiple instances of an AMI.

Instances can be run on various hardware configurations for CPU, RAM, and network capacity options.

More resources = more cost

There are regions available globally. You can even use multiple instances and design it such that if one instance fails, another instance will take over

## EB (Elastic Beanstalk)

Amazon's GUI for EC2 to make the process easier.

WARNING! A database instance that is part of your environment is tied to the lifecycle of your environment. You can't remove it from your environment once added. If you terminate the environment, the database instance is terminated as well!

## S3

- Data is stored as objects in buckets that can be accessed using a key. Not a server, so technically serverless
- scales automatically

## RDS (relational database service), DynamoDB is for non-relational db

- at the lowest level, you can manage your own db (postgres, for ex) in an
  ec2 instance
- fully managed options include `RDS` (sql), `Dynamo` (nosql), `Neptune` (graph)
- `RDS` is compatible with more dbs and has native functions
- `Aurora` is MySQL or PostgreSQL compatible and does auto scaling up to 64TB,
  15 read replicas and backups to s3 (within multi zones in 1 region) as
  well as serverless options. Some native functions are not available

## ECR (Elastic container registry)

fully-managed container registry that makes it easy for developers to store images
used for static file serving

## IAM

Amazon's tool to control account level security. This allows you to control who can access what in your AWS account.

## Route 53

- dns

## Cloudfront

- a CDN that's usually backed by S3

## Shield

- a WAF (Web application firewall) used to protect against DDoS (Distributed Denial of Service)

## LBs

- ELB (elastic Load Balancer) was used at L4 (network) and L7(application) previously,
  but now is named "Classic Load Balancer"

- NLB (Network Load balancer) is the new and improved product at layer 3

- ALB (Application Load balancer) is the new and improved product at layer 7

- Nginx still has features that are not supported in ALB such as caching in the LB,
  supporting UDP and TCP so it is often useful to have an nginx proxy AFTER ALB

## Elasticache

- an in-memory k-v store like `Redis`
- fast data stores are used to rate limit requests

## Elastic Search (Kibana)

- a way to search through logs and metrics quickly.
- has a visualization tool, `Kibana`
- built off of open source Apache Lucene

## VPC

- Virtual Private Clouds provided high security
- only subnets within the same VPC can communicate with each other
- as an exception, a `NAT Gateway` (Network Address Translation) can be
  opened from a service within a VPC to reach outside. This connection can
  only be initiated from the secure, VPC side

### VPC Peering, VPC Private Linking to connect to other cloud networks

- VPC Peering is bi-directional. This is slightly
  more risk as both parties can send data
- Private Linking is unidirectional and more secure but less flexible
