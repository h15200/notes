# Cloud servers and cloud providers

Cloud server is powerful physical or virtual infrastructure that performs application and informatin processing storage.

Cloud providers allows devs to use cloud servers

Amazon Web Services provides hundreds of services to fit the need of devs

AWS prodives a globally distributed IaaS (infrastructure as a service) that provides access to enterprise grade solutions for companies.

## Scaling overview

- general idea of scaling in order:

  - users > 100
    - start with Route 53, and a VPC wrapper around your infra
    - Add elastic ip and ec2 or, more managed options that scale better like
      ECS (elastic container service) or EKS
    - a relational db like RDS
      - Aurora serverless has auto scaling for SQL if you know you will grow
    - start with monolithic app if you're not sure
  - users > 1,000 - add ALB and some extra instances of servers to scale horizontally
    - nodes in different availability zones for fault tolerance
    - add new new nodes of db, read replicas of db
  - users > 10,000
    - add read replicas in dbs
      - think about replication methods and trade-offs
    - add Cloudfront and serve static content on the edge
      - or, the more modern way would to be use a hosted service like
        Amplify which manages the front-end
    - add ElasiCache (managed in-memory cache nodes)
    - add Dynamo to federate some data like metadata
  - users > 100,000
    - auto scale with `CloudWatch` that sits after the load balancer which
      automatically adds pools of nodes to services that are being most heavily
      requested (around users > 500,000)
  - users > 500,000 metrics, logging, observability dashboards CloudWatch can handle metrics as well with anomaly detection break up monolithic architecture into soa or microservice architecture
    - containerizing with ECS, k8s layer with EKS
    - loose coupling with message queues, event driven system
  - users > 1 million
    - Multi-AZ infra for partition tolerance in one data center
      - use services that auto scale like s3, ALB, SWS, or manage your own
        multi az config for things that don't lke EC2
    - federation of dbs to NoSql, GraphDbs from main RDS
      - something like DynamoDB will give scaling functionality out of the box
    - around joins get very slow around TB of data
    - sharding and horizontally scale dbs.
      - requires more application logic, usually harder for RDBMS
  - users > 10 million
    - multi-AZ to multi-region (word wide) tolerance

## self managed to fully managed spectrum

- frontend

  - EC2 with web server like Nginx
  - Cloudfront serving static S3
  - Cloudfront and Amplify hosting

- services

  - EC2
  - ECS/EKS
  - Fargate (managed serverless)

- messaging
  - SQS
  - Kinesis

Generally, (in 2023), most services replicate across az's in a single region
and some allow for global out of the box

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

- Amazon's automated service to remove the neeed to
  manage EC2 yourself

## S3

- Data is stored as objects in buckets that can be accessed using a key. Not a server, so technically serverless
- scales automatically
- up to 5tb
- replicated across AZs

## RDS (relational database service), DynamoDB is for non-relational db

- at the lowest level, you can manage your own db (postgres, for ex) in an
  ec2 instance
- fully managed options include `RDS` (sql), `Dynamo` (nosql), `Neptune` (graph)
- `RDS` is compatible with more dbs and has native functions
  - can replicate multi-AZ within one region
- `Aurora` is MySQL or PostgreSQL compatible and does auto scaling up to 64TB,
  15 read replicas and backups to s3 (within multi zones in 1 region) as
  well as serverless options. Some native functions are not available
  - Aurora can also replicate instances globally (multi-region)
- Dynamo can be replicated across multiple AZs in the same region

## ECR (Elastic container registry)

fully-managed container registry that makes it easy for developers to store images
used for static file serving

## IAM

Amazon's tool to control account level security. This allows you to control who can access what in your AWS account.

## Route 53

- dns
- global

## Cloudfront

- a CDN that's usually backed by S3
- can use it just as an edge serving mechanism with any caching if you set
  `ttl` to 0 seconds
- global

## Shield

- a WAF (Web application firewall) used to protect against DDoS (Distributed Denial of Service)

## LBs

- regional, multi-az
- ELB (elastic Load Balancer) was used at L4 (network) and L7(application) previously,
  but now is named "Classic Load Balancer"

- NLB (Network Load balancer) is the new and improved product at layer 3
- ALB (Application Load balancer) is the new and improved product at layer 7
- typically, start with an ALB as it has more features like health checks,
  monitoring/logging, count-based routing, http2

- Nginx still has features that are not supported in ALB such as caching in the LB,
  supporting UDP and TCP so it is often useful to have an nginx proxy AFTER ALB

## Elasticache

- managed in-memory cache nodes that uses either `Memcached` or `Redis`
- scale from one to many nodes
- self healing, muti-AZ deployments
- fast data stores are used to rate limit requests

## CloudWatch for auto scale

- sits in after loadbalancer and automatically increase nodes in servers
  where needed (not the db layer, just web servers)

## Elastic Search (Kibana)

- a way to search through logs and metrics quickly.
- has a visualization tool, `Kibana`
- built off of open source Apache Lucene

## SQS (simple queuing service)

- message queue service
- reliable multi-az, FIFO
- offline batch processing, not real time

## MSK (Managed streaming for kafka)

- use case for companies that are already using and managing their own
  kakfa
- more config with kafka compared to Kinesis

## Kinesis streaming

- AWS version of kafka
- real time data processing

## VPC

- Virtual Private Clouds provided high security
- only subnets within the same VPC can communicate with each other
- as an exception, a `NAT Gateway` (Network Address Translation) can be
  opened from a service within a VPC to reach outside. This connection can
  only be initiated from the secure, VPC side
- created in one region
  - subnets available in multi-az

### VPC Peering, VPC Private Linking to connect to other cloud networks

- VPC Peering is bi-directional. This is slightly
  more risk as both parties can send data
- Private Linking is unidirectional and more secure but less flexible

## Amplify

- manage hosted service that can serve front-end without the trouble of
  managing S3 + Cloudfront
