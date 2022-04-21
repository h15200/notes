# Apache Kafka

- developed by Linkedin
- `Apache` is a non for profit open source organization

## Main concept is `Data in Motion` vs `Data at rest`

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

- in vanilla Kafka, data is stored in local brokers (computers). as your data grows, you need to scale the storage.

## Confluent adds more functionality on top of Kafka

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
