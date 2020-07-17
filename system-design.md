# System(s) Design

Big picture ideas with no code.
Frequent interview questions, but no clear, ONE answer.

Can be broken down to 3 things

1. scoping
2. sketching
3. identifying bottlenecks

## Scoping the problem

1. Understand the question

Ask questions to understand the contraints and use cases

- Who are our users and what are their needs?
- what is the exact scope of the problem?
- what are non-functional requirements?
- what are our stretch goals?

ex. "designing twitter"

questions might be

- 'how many total users do we expect? how many active users a day?'
- 'can users tweet and follow others?'
- 'should we also design to create and display user's timeline?'
- 'will tweets contain photos and videos?'
- 'should I design the front end as well as the back end?'

2. Get a rough estimate of scale

- what scale is expected from the system (number of users, daily active users, number of new tweets, how many followers per user on average)
- how much storage would we need? (photos, videos)
- what network bandwidth usage are we expecting? Crucial in deciding h ow would we manage traffic and balance load between servers

## Sketching up an abstract design

Illustrate the building blocks of the system and the relationships between them

3. Mock out a basic UI (if front end is required)
   Very rough sketch

Consider what will be required for your user(s) to complete a single transaction, from initiation to feedback. what UI elements are required?

4. Define your data model

- choose a database, as well as block storage for things like photos and videos
- define the data model early to clarify how data will flow among different components
- sql vs no sql

5. Define your API

- define what APIs are expected from the system.
  postTweet(userId, tweetData, userLocation, timeStamp)

6. High Level Design
   Draw a block diagram with 5-6 boxes representing core components (client, load balancer, servers, CDN, database)

7. Detailed Design
   Dig deeper into these high level components.
   Take trade offs, pros and cons of each decision
   ex.

- how should we partition our data to distribute to multiple dbs?
- How would we handle hot users who tweet a lot or follow lots of people?
- since user's timeline will contain most recent (and relevant) tweets, should we try to store our data in such a way that is optimized to scan latest tweets?
- How much and at which layer should we introduce caches to speed things up?
- What components need better load balancing?

## Identifying and addressing the bottlenecks

apply fundamental principles of scalable system design

8. Try to discuss as many bottlenecks as possible and different approaches to mitigate

- is there any single point of failure in our system?
- Do we have enough replicas of the data if we lose a few servers?
- do we have enough copies of different services running, such that a few failures will not cause a total system shutdown?
- how are we monitoring the performance of our service? Do we get alerts whenever critical components fail?

## Main tools

### Load balancers

- helps scale horizontally by distributing requests to multiple servers

#### Consistent hashing in load balancers

Traditionally, when scaling horizontally, it might look like

name fetches
server 1 does a - n
server 2 does n - z

when adding server 3, it goes a third, a third a third

`fault tolerance` - how to protect against a crashed server or machine
`allocation` - the way a request is mapped to a server.

Consistent hashing allows a load balancer to allocate the request that protects against fault tolerance AND scalibility based on efficiency of existing cache.

Consistent hashing is used to preserve the most common users (that are already cached) so instead of going 0 - 33%, 33 - 66, 66-100 in the new model, you slice the LAST percentage of each existing server and assign them to the new ones to scale efficiently

### Caching

- enable you to make vastly better use of the resources you already have
- recently requested data is likely to be requested again
- used in almost every layer of computing: hardware, operating systems, web browsers, web apps

Cache Invalidation

- keeping the cache in sync with the db is a new issue created by having a cache
- if a data is modified in the database, it needs to be invalidated in the cache to keep data consistent

methods of invalidation

- Write-through cache: data is written into the cache and the corresponding database at the same time
- Write-back cache: data is written to cache ALONE, and completion is immediately confirmed to the client. The storage write is done later, when traffic is low.

ex challenge "we've got a distributed system and we want to manage request calls"
solution:

### Message Brokers (Queues)

- queues are used to effectively manage requests in a large-scale distributed system to allow us to decouple our processes and distribute/throttle processing load.

### Proxies

A proxy server is a piece of hardware/software that sits between the client and the server. It receives requests from clients and relays them to the back end servers over the internet..
Typically, proxies are used to filter or log requests, block sites, provide anonimity.
Its cache can also serve a lot of requests

### Reverse Proxies

Sits between the internet and the back-end-server.
Used for load balancing, web acceleration via transforming requests (adding/removing headers, encrypting/decrypting, or compression), and adding additional security for your back end serverse.
Like proxies, can serve requests from its own cache as well.

### Databases

Reasons for:
Relational - ACID complicance. data is structured and unchanging
Non-Relational - large volumes of data that require little to no structure, makes the most of cloud computing and storage for horizontal scaling

### Sharding - Data partitioning

Break up a big db into many smaller parts.

Horizontal partitioning ex - (zipcodes less than 50000 are on one db, above on another)
Vertical partitioning ex - (all entries with id 0 - 10000 on db1, 10001-20000 on db2, etc..0)

Redundancy and Replication - remove single points of failure by having replicas or backups of a db or server.
