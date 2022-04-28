# Apache Kafka

- developed by Linkedin
- `Apache` is a non for profit open source organization

## Main concept is `Data in Motion` vs `Data at rest`

## related terms

- K8s, (Kubernetes)
- GCP (google cloud platform)
- GKE (Google Kubernetes Engine) GCP container engine

- traditionally, `data at rest` systems use cron jobs to look for data updates to trigger services. Example in linked if a user changes jobs on a profile, there are associated events that should trigger. For Linkedin to KNOW that a job changed, it used to run a check periodically. This is passive

- the same system can be improved if the job change automatically triggers the jobs. As data changes, there are pre-defined jobs that run after that change event

## Transactional event vs Non-transactional events

- a transactional event is `changing a profile`, `making a connection request`, `messaging a connect`

- non-transactional events include `clicking on a link`, `navigating to a subpage` etc..

- non-trasactional events are often not tracked, but provide tons of insight and value on user behavior

- most user interactions (about 99.9%) are `non-transactional`

- to truly be a digital first company, one must keep track of non-transactional events.

## how to store/track non-transactional events

- traditional systems can't do this because of the sheer quantity as well as the optimizations. Traditional dbs are best to store data at rest and does not react to any events. Message queues DO that, but not at this scale

- Instead of each data warehouse having to connect to each down stream microservice, the first goal of Apache Kafka was to make a `data-in-motion` system that sits between the storage layer and the downstream services where data can be published, and services can subscribed to react to those changes at scale

## basic mechanism

- a database pushes (writes) events to a `commit log` where it's stored sequentially.

- a service (reader) can access any of the evetns and the commit log can be shared by multiple readers.

- data is also compressed so that the commit log can handle volume at scale.

- a distributed architecture where it can be run as a cluster on different machines.

  - when a new cluster (computer) is added to the system, the logs are distributed evenly again (lke adding a new server)

- with this system, all you need to get data is to subscribe to the topic.

- in vanilla Kafka, data from the `commit log` is stored in local brokers (computers). as your data grows, you need to scale the storage.

### stream

- a `stream` is the `commit log` that has multiple `records`.
- `record` === `event` === `message`
  - a `record` consists of `headers`, and a `body` (a key-value pair where the value contains business relevant data, although the key is optional), and a `timestamp`
  - the `key` in the body is used to determine where in the `partition` a record is written to
- a `stream` is immutable
- a stream has history and new events are added to the end
- a stream is open ended (does not end)

## Confluent

### connectors

- as a company uses more and more databases, it becomes harder to keep track of all the different types of data.

- at Confluent, there is a data integration mechanism where a universal api can connect with various different databases so it's easy for companies to use multiple dbs

### continuous data processing

- all microservices are now event-driven. It reads from the distributed Kafka log commits and reacts

- to build event-driven applications easier, Confluent created 2 processing frameworks

1. `KStreams (Kafka Strems)` - a java library that provides high level abstractions for common event-driven patterns such as `filtering`, `joining`, `aggregating`

2. `ksqlDB (Kafka SQL DB)` - allows people to define common processing patterns in event feeds using familiar SQL like syntax. Even if you don't know java, you can use ksqlDB to write sql code to work with Kafka

### Cloud native vs on-prem

- on-prem usually means the company has a physical data center

## Cloud integration

- Initially, the Confluent Plaform was the only available Confluent product and it was used for `on-prem`, `private cloud` or `public cloud` integration. Confluent was not involved in connecting Confluent to cloud services.

- `Confluent Cloud` is a cloud native solution to kafka.

  - In vanilla Kafka, data is stored in brokers (machines) including historical data that you may want to keep around. It is also hard to scale as the requirements are coupled with the amount of data that's being computed.

  - With Confluent Cloud, storage is elastic because it's using cloud resources more efficiently. The most necessary data is kept in local brokers, but historical data (the vast majority) is kept in block storage and lowering total computation and storage costs. The storage need is decoupled from computation needs, so scaling is elastic and adding brokers is easier

  - because of the storage efficiency in Confluent Cloud, customers now have infinite retention on historical data.

## Confluent Cloud

## architecture

- Confluent Cloud uses a combination of GCP, AWS, and Azure

### Planes

- In cloud services and paas (platform as a service) there are 2 major components

1. control plane (customer control plane)

- handles provision flows, api config, creating clusters
- is a way to communicate with the mothership vpc (see below)

2. data plane

- how to access services (in Confluent, connectors)
- is a way to connect to the network, or the satellite vpcs (see below)

### VCP, cluster, zones

- one "unit" of cluster is thought of as 1 k8s cluster, and that means 1 `VCP` (virtual private cloud) must also be created for each 1 k8s cluster.

  - in that k8s cluster, there could be 1 or more Kafka clusters

- When a VPC is created, by extension kubernetes cluster zookeeper cluster, kafka cluster(2) and all other types running on that VCP will also be created

- a VCP has a relational database inside it (Postgres usually)

- a VCP can either be `single-zone` or `multi-zone`. Zone in this context refers to the cloud provider's availablility zones.

### Env

- there are 4 envs in Confluent Cloud

1. prod - many regions in all clouds we're officially deployed in
2. stag- 2 regions in AWS, one in GCP, 2 Azure
3. devel- 1 AWS, 1 GCP, 2 Azure
4. Private development (cpd)

Notice how all of them are using different accounts to keep them 100% isolated from each other

- per each `environment`, there is only ONE `mothership`, which is a special VPC which has the golden source of truth for all high-level desired state.

- all other VPCs in the same env that is not a `mothership` are considered `satellites`

- the `mothership` contains a db that has info on all satellites (network_id, k8_cluster identifier, orgName, etc..)

### Satellites

- satellites are all VPCs (and the k8s clusters that are in them) that are NOT the mothership.

- satellites are in AWS, GCP, Azure in many regions

- `GCP Satellites` are just the VPC and a GKE (Google kubernetes engine)

- `AWS Satellites` are VPC with its own network with no direct internet access. Outbound connections are allowed through internet gateways. A single k8s cluster is deployed into each of these satellite VPC's with its own set of DNS names for the masters managed through `route53`

### "Mothership" (always AWS us-west-2)

- the term `mothership` can be used to refer to several different things in conversation

1. The data that is the source of truth for all desired state
2. The mothership VPC itself (in AWS us-west-2 region)
3. The k8s cluster within that mothership VPC
4. The Kafka cluster in that k8s cluster
5. The set of services in that k8s cluster
6. The Postgres database in that mothership VPC

- there are several important services inside the mothership

  - `scheduler-service` (handles which physical clusters should exist, where they are scheduled, how many resources they require, api credentials, etc.. )
  - `gateway-service`
  - `org-service`
  - `auth-service`
  - `metrics-service` (uses Elasticsearch as it's backing store)

  - services inside the mothership are accessible through the `control plane (user management plane)` and the services communicate with each other via `grpc` with Protobuf messages.

  - Control plane component exist in each satellite as well including Kubernetes control plane, cloud-layer auto-scaling groups, synce-service and psc-operator.

- a mothership cluster also has its own postgres DB running in the same AWS VPC for state storage.

### Global mothership kafka

- a special kafka cluster which sites inside an env, inside a mothership VPC, inside that mothership kubernetes cluster.

- has producers and consumers spread around all of the satellites

- in `prod`, this means that the global mothership kafka is linked all over the globe from both GCP and AWS.

### Scheduler service

- sits inside the mothership cluster and does the main kafka thing, which is producing events that the satellites are listening for.

- is the main service responsible for handling kafka clusters by choosing which kubernetes cluster to start a physical kafka cluster in, which physical kafka cluster to create a new logical kafka cluster in, etc..

- functions as both a producer and a consumer to the global mothership kafka cluster.

- it inserts/modifies/deletes info into/out of the mothership DB
- creates and sends the appropriate messages into the global mothership kafka cluster

### sync-service

- each satellite has a sync-service that consume the messages produced by the `scheduler-service`.

- scheduler is the producer, sync is the listener

- all sync-services consume messages but messages are designated for selected satellites. If you're a satellite that gets a message that's not designed for you, the message is consumed but is immediately thrown away

- when a message is designated for a sync-service, it reacts by creating a special kubernetes object called `Physical Stateful Clusters` or `PSC`s

### Provisioning FLow

- a user creates a cluster
- scheduler decides what to do and puts info into the mothership DB
- scheduler produces messages to global mothership kafka cluster
- sync-services consume the message, and all but one do nothing
- the appropriate sync-service creates an appropriate PSC in its kubernetes cluster
- the operator reacts by creating all the other kubernetes components:

  - namespace
  - persistent volumes
  - statefulset
  - deployments
  - pods
  - configmaps
  - secrets
  - services

### Kafka logical clusters vs physical clusters

- the smallest "unit" of kafka is a `kafka broker` or a `kafka node`

- a `kafka cluster` is a group of `kafka nodes`, or `kafka brokers`

- a `topic` is created on Kafka, but a `stream` is used in `ksqldb`. To import a topic as a stream, there needs to be a valid `schema` attached to it

- physical cluster is a traditional kafka cluster (non cloud)
- logical cluster is the cloud native version of a kafka cluster that leverages cloud scaling

### Kafka data model Confluent Cloud org

- a conflent cloud `organization` has 2 tiers

1. professional
2. enterprise

### resiliency

- Apache `ZooKeeper` (key-value store) is used to manage kafka clusters
- typically run in a cluster of 3 or 5 servers, called an `ensemble`
- uses `ZAB` consensus algorithm to achieve a quorum and elect leader
- stores `ACLs` and `secrets`

### retention policy

- all data has a default retention policy of 1 week and the record will be purged from the partition after that

### delivery policy

- all ensures `at-least-once` delivery with acknowledgement

- 3 levels of ack

1. no ack (fastest, but no insurance that all records are being sent)
2. only leader (only leader partitions will ack)
3. all (leader and follower partitions will all ack. slowest, but ensures all delivery)

### topics, partitions, and consumers

- the `commit log` has a bunch of `records`, all with metadata about the data (`topic`)and header and timestamp
- a `topic` will have multiple producers and consumers and paritions
- the `record` is then spread to the appropriate `partition` based on the `topic`, which are spread across `brokers`.
- the `key` will assign partitions. If there are no keys, the producer will just use `round-robbin` distribution to be assigned to a random partition
  - each `broker` handles many `partitions`. paritions are stored on the brokers' disk
- in Kafka there are three terms `topic`, `partition`, `segment`
- a `partition` is smaller groups that comprise a topic. Partitions are made to parallelize work and increase the throughput Kafka by splitting a topic
- a `segment` breaks down the partition further and creates physical files using the `rolling-fie` strategy (when a segment file is full, the next one is allocated by the broker.)
- topics are broken down into `partitions`
  - it is possible to re-partition a topic after it's created
  - the optimal number is derived from testing throughput for producers and consumers.
- if a consumer is subscribing to a certain topic, it is consuming from all of the partitions that make up that topic
- consumers are single-threaded. To scale, you can add consumers (up to the max of the total number of paritions for a topic) to create `consumer groups`
- consumers usually run infinitely `while (true) { // read logic}` by polling at intervals (defaulting to 500ms)
- adding / removing consumers will auto scale

### schema registry

- topics can be defined by a schema built on `avro`, `json`, or `protobuffers`
- schemas can be updated
- schemas are held in kafka topics themselves
- ksql streams need schemas to connect to a topic. (a `topic` may or may not have a schema, but a `ksql stream` requires a schema)

### connectors

- you can plug in external `sources` and `sinks` to the kafka ecosystem via `connectors` or `connect clusters`
- ex. you can read records from a db, stream them as topics, then have consumers write to some other external db even if those are NOT currently part of kafka

### ksqlDB

- not a `db` but more a materialized view of a stream
- used to build apps (ksaql streming application)
- output can be another stream, or some logic
- uses sql syntax and functions like aggregations
- possible to CRUD streams, connectors
