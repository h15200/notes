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
- Generally, windows or linux. There is a dedicated Mac hardware instance but it's expensive
- Amazon Machine Images: preconfigured templates for your instances
- Instance types: various CPU configurations, memory, storage, networking capacity
- regions and zones: multiple physical locations for your resources
- Kay pairs: provide secure login information with SSH
- Security groups: Firewall that enables you to specify the protocols, ports, and IP ranges that can reach your instances
- IP address types
  - public IP address
    - IP address is lost every time the instance is stopped and restarted, though it retains a private ip address. Can not be moved between instances
  - private IP address
    - retained between start/stops
    - mapped via the OS and the elastic network
  - Elastic IP address
    - static public IP address
    - you are charged if not used
    - associated with private IP address
    - Can be moved between instances and Elastic Network Adapters
- Instances can be launched into specific Subnet types within an availability zone
  - public
    - a public subnet within a VPC can comminicate to the internet through the `Internet Gateway` and the public IP is also accessible from the internet
  - private
    - won't have any internet connectivity by default
    - only private IPs are available
    - best practice whenever possible, EVEN if it is public facing because we can add a load balancer to it later
    - still possible to reach out to the internet via a `NAT gateway` on a separate route table. Instead of going straight to the Internet Gateway, the outbound traffic goes out via NAT gateway (not inbound)
- Instance types (determines hardware profile and cost)
- AMI (Amazon Machine Image) determines the OS. ex. Windows + Microsoft SQL
  - generally, SSH (secure shell) to connect to linux and RDP (remote desktop protocol) to connect to windows instances
- User Data defines the script to run when the instance runs for the first time
- Metadata service allows users to get data about the instance
- both `User Data` and `Metadata` version can be set when the instance is created under "Details"
- to give an ec2 instance acess (for example, to an s3 bucket), there are two ways:
  - configure AWS CLI with access key of an IAM user. access key is stored as plain text in the instance itself and it's a long term credential, so this is not recommeded
    - if you go to the instance inside `.aws/credentials`, the access key and pw is there in plain text which would compromise anything that the IAM user has access to
  - (best practice) use IAM role with s3 permissions. The instance can then assume this role without storing any long term credentials anywhere
    - create a role with the necessary permission policies
    - go to the instance -> action -> modify IAM role -> select the newly created policy
  - note that both of these things are using AWS `sts` (security token service) but for IAM roles, the tokens are short-lived and done in the background
- `Placement Groups`
  - a `cluster` is a bunch of nodes that are physically close in proximity (same AZ, maybe even same rack or adjacent rack) to ensure high performance, tightly coupled workloads and low inter-instance latency
  - a `partition` spreads resources so nodes are not sharing underlying hardware. ex. 2 instances in one AZ, another 2 in another AZ. each `partiion` is on a different aws rack
  - `spread` every `instance` is on a different AWS rack. No 2 instances are on the same rack. Used for small number of highly critical instances that always need to be available
- `Network Interface Types` (aka Network Adaptors). EC2 usually chooses a subnet (private or public) to connect via network interface outside the AZ of the instance. Multiple interfaces can exist (ex 1 for public, 1 for private subnet)
  but they must be in the same AZ
  - `ENI - Elastic Network Interface`
    - the default option for when you don't have high performance requirements
  - `ENA - Elastic Network Adaptor`
    - higher bandwith and lower inter-instance latency
  - `EFA - Elastic Fabric Adaptor`
    - for tightly coupled, high compute applications (ML). Often used along with `cluster` placement group in single AZ
- IP Addresses
  - public IP addresses are dynamic and change when instances are restarted
  - private ID addresses stay with the instance. When you reach out to a public network, the Internet Gateway performs NAT (network address translation) and changes the source to the public IP
  - elastic IPs is static. This can be associated with network interfaces so that it will stay the same. Can be moved between instances and Elastic Network Adaptors
- private subnets and `Bastion hosts` are common use cases for private ec2 instances
- a `NAT gateway` is different from an Internet Gateway. It's just for outbound traffic from a private subnet

  - The NAT gateway always needs to be in the `public` subnet on behalf of the private subnet. It's the same as Bastian hosts, but going the other direction.
  - the public subnet uses an elastic ip address to translate the public IP to keep it protected

  ### Subnet Routing table, CIDR, and Bastion Hosts

- the network within a VPC
- CIDR block (Classless Inter Domain Routing) is a group of IP addresses that share a network prefix and number of bits
- A public subnet route table might look like:

```
Destination          Target
172.31.0.0/16        Local          // the "172...." is the CIDR block, and all addresses within this block will be routed LOCALLY via the VPC router
0.0.0.0/0            igw-id        // 0.0.0.0/0 means ANYTHING else. The outside world. The target is igw = "internet gate way" or the outside world
```

- a `private` subnet does not have a non-vsc block for the outside world. No public ips are configured on purpose. Both the private and public subnets do share the CIDR block
- if you want to connect to the private subnet from your laptop, it is not possible to do it directly. Instead, you need to first connect to
  the public subnet via the public IGW and then that public subnet needs to communciate to the private subnet via the VPC router. In this case, that public subnet
  is called the `Bastion Host` (aka `Jump Host`)
- in AWS, we would
  1. create a private subnet
  2. create a new route table for that subnet
  3. create a private EC2 instance on that new private subnet with key pair
  4. create a public EC2 instance with key pair on the public subnet in the same AZ as the private subnet as the Bastion host
  5. make copy of key pair PEM file and set to `chmod 600` so only you have access
  6. `ssh -i <pemFIle> user@<privateSubnetAddress>` will get you access to the private subnet. To check, `ping google.com` and nothing should return. cancel out and see 0 data received
- this process in reverse is used if the private subnet needs outside access for library downloads
  - put a Nat gateway on the public subnet
  - put that Nat gateway address in the private subnet route table
  - Nat Instances was the older way of doing this, which was essentially an Ec2 instance where the source/destination check is disabled. This is rarely used as NAT gateways are fully managed by AWS.
- `Nitro Instances` and `Nitro Enclaves`
  - underlying platform for next gen EC2 instances
  - eliminiates performance penalties for virtual instances
  - Nitro hardware is broken down into specific types so optimize every aspect of an instance separately
  - `Nitro Enclaves` provides more security with isolated environments, encryption, and more network restrictions
- Pricing and use cases
  - `On demand` No interruptions to service, but billed by time. Good for several hours of uninterrupted work
  - `Reserved` Committed with discount. Can set time schedule. 1 or 3 year committment
  - `Spot Instances` Compute heavy but can be interrupted
  - `Dedicated instances` Isolated instance with more control. Enterprise with sensitive data
  - `Dedicated hosts` Isolated instances and hardware control. ex. Database with per socket licensing
- Summary
  - EC2 allows virtual instances in the cloud
  - user has full control of OS layer
  - key pairs are used to securely connect
  - storage is either Amazon EBS (persistent) or Instance store (non-persistent)
  - Amazon Machine Image (AMI) provides config required to launch an instance. includes:
    - template for the root volume
    - launch permissions
    - AMI's are region scoped. You can only launch AMI from the region where it's stored
  - benefits include:
    - elastic computing to launch thousands of instances
    - control of full root/admin ccess
    - flexible choice of types, OS, software
    - reliable and available
    - secure and fully integrated with VPC
    - inexpensive with choices
  - communicates to the outside world via NAT GW or IGW via public subnets.
  - Public IP addresses change when an instance stop/starts, so not usable as a static address
  - Elastic IP addresses are used as a public IP to be static
  - Place groups `cluster` same rack (AI), `partition` some in same az, some in others, `spread` every single instance in different rack (mission critical with highest availability)

## ELB (Elastic load balancing) / auto scaling

- ASG (auto scaling groups) allow a minimum number of instances
- Autoscaling works with EC2, ECS, EKS by launching/terminating instances and integrates with services such as `CloudWatch`
  - works within VPC, so possible to auto scale over multiple AZs
  - all instances send CPU health to CloudWatch at an interval (5 or 1 minute). CloudWatch notifies auto scale and if an instannce hits a number like > 80% of capacity,
    it adds a new instance
  - also adds a new node if one fails to ensure availability
  - scaling policy can be run by metrics, or on a schedule to account for peak hours
  - types of auto scaling:
    - simple scaling (the default). the next 2 choices are preferrable
    - step scaling. configure how many instances to launch if the CPU usage is over by x amount
    - scheduled scaling. add a spike schedule
- elastic LB ensures that the traffic is distributed evenly within those instanaces with high avilability
  - works alongside auto scaler to distribute evenly. health checks notify the ASG to terminate/instantiate instances as necessary
  - note that per instance redundancy is taken care of AWS. For example, there's no need to implement RAID1 disk mirroring
    to have a backup CPU disk or having 2 network interface cards.
  - the high level load balancing that should be implemented by the user is in anticipation of an instance failing or an entire az failing. the combination
    of cross-AZ ASGs and load balancing should take care of those scenarios
  - specific types of Elastic Load balancers:
    - Application Load Balancer (L7) operates at the request level and has access to http headers so can have path, host, query param based routing. use for http(s) apps.
    - Network Load Balancer (L4) operates at the network protocol level, so only has access to IP address but is very high performing and offers low latency. tcp or udp apps
    - Gateway Load Balancer has a very different use case from the above two. sits in front of virtual appliances such as firewalls and operates at L3 (packets)
    - `target groups` must be set to tell the load balancer where to send the traffic (EC2, IP address, Lambda Function, etc..)
  - `secure listeners`
    - if `ALB`
      - used to assign SSL, TLS certs to the load balancer
      - for ALB, the SSL is used between the user and the LB, but not between the LB and the application. This is usually ok as that part is already within the VPC
      - is is also possible to have end to end encryption if you use another cert for LB <-> Instances
    - if `NLB`
      - possible to have full encryption from user all the way to the instance
      - a public cert must be used

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

- Amazon's tool to control account level security. This allows you to control who can access what in your AWS account.
- generally best practice to never use the root user until you have to. Create a new IAM account and log in to the IAM, not root
- users and roles
  - IAM users are people who work in AWS regularly. they are granted the least permissions to do their tasks
  - Roles are short term delegation of permissions to people who need temporary access. They only assume some permissions.
- Permission boundaries are set so that users can't create a new IAM user with more permissions than they have
- condition permissions can be used to restrict users from certain IP addresses

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

## Elasticache

- managed in-memory cache nodes that uses either `Memcached` or `Redis`
- scale from one to many nodes
- self healing, muti-AZ deployments
- fast data stores are used to rate limit requests

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
- in terms of scope, it can span across MULTIPLE AZs, so Region -> VPC -> AZs. however, subnets within a VPC must be contained to 1 az
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

```

```
