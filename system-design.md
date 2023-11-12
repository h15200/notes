# System(s) Design

Big picture ideas with no code.
Frequent interview questions, but no clear, ONE answer.

Can be broken down to 3 main categories.

1. scoping
2. sketching
3. identifying bottlenecks

## fact sheet

Reading 1MB fastest to slowest:

- RAM (.25ms)
- SSD (1ms)
- Network (10ms)
- HDD (20ms)
- Inter-continental round trip (150ms)

so sending 1GB over the network would take 10 seconds

9's outage time per year

- two 9s: 90 hours
- three 9s: 9 hours
- four 9s: 1 hour
- five 9s: 5 minutes
- most major cloud services offer 99.95% so just under 4 9s

## Scoping the problem

1. Understand the question

Ask questions to understand the constraints and use cases

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
- what network bandwidth usage are we expecting? Crucial in deciding how would we manage traffic and balance load between servers

## Capacity Planning

1. Throughput/load estimation (for example, servers handling write operations in social media)

   - rps / qps (request or query per second) is the main metric
   - Ask for average daily users, and possibly guess the rest
   - for ex. for social media, try 100 million users who
     - suppose 5 writes on average = 500 million a day
     - get average qps by dividing 500 million by (24 \* 3600 ~ 100,000) = 5000
     - 5,000 qps for AVERAGE, but for peak, you might multiple by 3 = 15,000 qps
     - one service might handle 1,000 second, so you'll need some redundancy, load balancer etc..

2. Storage estimation

   - how much data to keep eg 5 years
   - multiply daily _ 30 _ 12 \* 5
     - byte 1
     - kb 1 x 10 ^ 3
     - megabyte 1 x 10 ^ 6 (million)
     - gigabyte 1 x 10 ^ 9 (billion)
     - tera 1 x 10 ^ 12 (trillion)
     - peta 1 x 10 ^ 15 (quadrillion)

3. Bandwith estimation (how much data is being processed per second)
   - take the value form #1 (rps) and multiple by how much data is processed
     per query

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

## network failure

- when the network is down, let network protocols (ip/tcp) handle the errors.
- if individual nodes fail, see below

## types of node failures

- fail stop (a crash)

  - solution 1 restart and load last good state (more latency)
  - solution 2 replicate state and fail over to another node (expensive)

- byzantine failure (all node failures that do NOT crash)
  - best bet is to add some code so that this turns into a proper fail stop
  - better assertions

## Main tools

### Microservice architecture

Monolithic - one or a group of machines (servers) handle ALL services.
Microservice is a single business unit. It doesn't not mean it's small. It's just a way of identifying a unit of business logic like sign in, check out, etc.. and each of them usually have a dedicated db.

A client may talk to a `gateway` which then communicates to a microservice.

#### Pros and Cons

Monolithic architecture

PROS

1. Easier to organize for smaller teams
2. Less duplication of code
3. Faster as there are no additional network calls

CONS

1. nothing is decoupled, so there's too much responsibility on each server
2. single point of failure for the entire system rather than just that one business logic

Microservice architecture

PROS

1. Easier to design the system
2. Less dependency between servers, so the business can keep going even if one microservice fails
3. Easier to identify bottlenecks and debug problems with a streamlined approach

CONS

1. Harder to initially design
2. Needs a good architect

   Ways to reason about which service to use..

If there are only 2 microservices, it's a sign you should just use a monolithic structure.

## protocols

- `ip/tcp` (ensures delivery with handshakes and acknowledgements).
  - guarantees FIFO delivery. If the same process sends two messages, the
    first one will be processed by the receiver first. Implemented with
    an ack step. A sends to B, B sends ack back. Only then can A send another
    message to B. The roundtrip network call makes it safe and guarantees ordering,
    but is slower
  - tcp have built in encryption using TLS
  - web sockets are built with ip/tcp
  - is not a strict client-server model. Data can go both ways in any order
  - eventual consistency
- `udp` (no acknowledgement flow, so FASTER but some packets will be lost) video, voice
  - does not guarantee FIFO delivery and has weak consistency but is fast
  - used in `DNS` and voice/video apps
- `http` built on top of ip/tcp with encryption and identify verification
  - is a client-server model. The client must first request, and the server replies
- `smpp` (short message texting) twilio
  - based on TCP
- `websocket` peer network
  - built on top of TCP, and is faster than `xmpp` but less secure
- `xmpp` peer network
  - `xmpp` built with TCP, but is slower but more secure than websocket. It has additional encryption logic on top of TLS, which TCP also has
- `smtp` (simple mail tranfser protocol)
  - used to send email via ip/tcp. tcp ensures eventual delivery
- `ftp` (file transfer protocol)
  - based on TCP and is faster than `http` as it is a "pure" tcp protocol with no additional headers

## DNS

- "Domain Name System"
- how does it work? Basically, a gigantic key value pair of human readeable text to ip address
- from a local machine adding a url:

  - your most local dns router (usually Internet Service Provider) will first see if
    they have the result in cache
  - if not, it will look for another dns that might have it
  - keeps going until the `root` dns
  - at each layer, this search will be cached for a certain amount of time
  - this caching policy is based on `TTL` (time to live) set on each dns server

- managed solutions include `AWS Route 53` and `Cloudflare`
- usually will also load balance traffic and keep track of services that are down
  due to maintenance

### CDN

- "content delivery networks" works very similarly to DNS.
- it leverages data centers around the world and serves the end user from
  the closest `edge`
- You can have a Push policy where the CDN gets data every time the original sever gets updated
- or a Pull policy where the CDN gets data from the server when a customer makes a request. This is
  cached, so the 2nd customer will get a cached result. This is better for high traffic content
- like DNS, there is a TTL policy set on CDN
- Akamai, Aws CloudFront

### Proxies

- Forward (default) proxies sit between the client and server on behalf of the CLIENT. It can be used as a cache, add/remove headers. It masks the client IP to the server. Most notable example is a VPN (Virtual Private Network).

- Reverse proxy also sits in the SAME place as a forward proxy, in between the client and server but on behalf of the SERVER. It can log, cache, load balance or do anything as an additional step before the original client request reaches the server.

- all load balancers are also reverse-proxies. you can have a reverse-proxy even if you only have 1 service to do things like config, routing, optimization for faster first paint etc...

- `Nginx` is a popular reverse proxy used for load balancing

### Load balancers

- Client -> load balancer -> a specific server -> Client
- (note that the load balancer doesn't get the data back from server)

- Hardware vs Software

  - Hardware load balancers are actual structures. expensive
  - Software load balancers are USUALLY what systems design interviews are referring to. Software is more flexible in what you can do.
    - ex. HAProxy, nginx

- is a type of reverse proxy (most of the time) as a reverse proxy sits in between the client and server on behalf of the server.
- can be set for the database, or even on the dns layer (google.com has many IPs and the DNS round robin will assign a request to the correct dns server to respond with a domain name)
- helps scale horizontally by distributing requests to multiple servers
- avoids duplicate requests
- ONLY makes sense if you have multiple servers to route to

- Load Balancers can use different algos to choose a server.
  - round robin, IP based (L4 ex AWS NetworkLoadBalancer), app info based
    (L7 AWS ApplicationLoadBalancer)
- because L4 only has access to basic info like IP address, it is simpler
  to configure and requires less computation power. On the other hand, l7
  is more config and computation but has access to all application layer
  headers, so is more efficient for load balancing

- some load balancers don't support certain protocols like UDP (AWS)

### reverse proxy

- Client -> proxy -> a server -> BACK to proxy -> client
- although techcnically load balancers are a type of reverse proxy, it could
  also be thought of a different thing
- reverse proxies usually handles auth, security, etc.. things that need to be done on all of your servers
- nginx has both L7 load balancing AND web server capabilities

- while a load balancer is only useful when you have multiple services,
  a reverse proxy is useful even with one server as it's just the gateway that
  handles logic

#### Server-Selection Strategy with load balancers

1. random
2. round robin (cycles through all servers in order). more ven than random
3. weighted round robin - certain servers have weight (priority) based on power of individual servers or past performance and are given more requests.
4. Ip based assignment - Client request ip address will be hashed and used to assign to an index number of server. Each individual client is always sent to the same server to maximize cache functionality.
5. Path based - requests are distributed based on the path of the request. Each server specializes in specific functionality. Speeds up deployment as you only need to re-write code for 1 server type.

Random, round robin, and weighted round robin will not work with server side in-memory caching because it won't maximize cache hits as the requests will come from random clients.

Multiple load balancers can have different strategies in a singular system.

clients => path based LB => weighted RR LB x 2 => servers

### Hashing

Concept of an algorithm that takes input and returns an item in an alloted number of buckets.

Hashing becomes VERY important if your system uses any kind of in-memory server side caching because your client needs to request to the SAME server every time to avoid cache misses.

Anything that makes in data, and returns an integer that points to an index of a sample size. IP address, username, any data can be hashed.

2 main hashing algos in systems design

Consistent Hashing (often used by Load balancers) and Rendezvous Hashing (highest random weight hashing)

### types of faults

- crash fault - server crashes
- ommision fault - a message is lost
- Byzantine fault - all others. malicious info, compromised node

#### Consistent hashing in load balancers

Traditionally, when scaling horizontally, it might look like

name fetches
server 1 does a - n
server 2 does n - z

when adding server 3, it goes a third, a third a third

`fault tolerance` - how to protect against a crashed server or machine
`allocation` - the way a request is mapped to a server.

Consistent hashing allows a load balancer to allocate the request that protects against fault tolerance AND scalability based on efficiency of existing cache. In minimizes the number of keys that need to be remapped when a hash table gets resized.

Consistent hashing is used to preserve the most common users (that are already cached) so instead of going 0 - 33%, 33 - 66, 66-100 in the new model, you slice the LAST percentage of each existing server and assign them to the new ones to scale efficiently so that requests in 0 - 24% range will still be routed to the same server.

- 2 main types
  - layer 4 load balancer is in the transport layer and hs access to TCP or UDP protocol info, so hashing is done on some combination of `Source IP`, `Source Port`, `Destination IP`, `Destination Port`, `Protocol Type`
  - layer 7 load balancers operate on the app layer so they have access to the HTTP headers (as opposed to transport protocol info) so will hash on URL, cookies, content type, and other meta data

#### Rendezvous Hashing

Each client has a weighted "ranking" of servers to go to. If a server goes down, then you simply pick the 2nd pick server.

With rendezvous hashing, if one server goes down, only those clients who picked that server as the highest ranking server will be re-routed to their 2nd ranked servers, and all other clients will continue making requests to the same server, allowing cache hits and more consistent allocation.

### Caching

- enable you to make vastly better use of the resources you already have
- recently requested data is likely to be requested again
- used in almost every layer of computing: hardware, operating systems, web browsers, web apps
- servers can have their own in memory cache, but data will be lost if it dies. It is usually better (even if slower) to use a global cache like Redis that all servers will go through. A global cache acts like another db, but it stores far less, is a key-value pair, and is still much faster than a db.

When using a global cache, we must consider updating the cache AND the db.

Cache Invalidation

- keeping the cache in sync with the db is a new issue created by having a cache
- if a data is modified in the database, it needs to be invalidated in the cache to keep data consistent

methods of invalidation

- Write-through cache: data is written into the cache and the corresponding database at the same time. Accurate, but it's expensive to make calls to the db to update during peak time.
- Write-back (deferred) cache: data is written to cache ALONE, and completion is immediately confirmed to the client. The db write is done later, when traffic is low. It is less expensive, but bad if the server goes down and skips the db write step.

Hybrid solution: use write-through for sensitive information. Use write-back for non-critical data.

ex challenge "we've got a distributed system and we want to manage request calls"
solution:

#### Load balancers vs Gateway service (or API gateway)

- these are 2 different things. Load balancers are more hands off, and usually only provides the actual routing to servers, and caching

- an API gateway has all of that plus more bells and whistles like rate limiting, monitoring, and auth and replaces the job of a load balancers

- both of these options can be used as the front door for your app, but load balancers are usually cheaper

### Message Queue / Brokers

- a message queue is used by a service to just say "ok we got the request, but we won't try to do it now and will instead put it on a todo list". This ensures that the server doesn't get overloaded and the requests are never lost, for the price of delayed processing

- The notifier is the `producer` and the services doing the actual work is `consumer`. The consumer takes a task from the queue and works on it when it's ready.

- a COMBINATION of services that include having a NOTIFIER (producer) that keeps track of which servers (consumers) are healthy (heartbeat sent to notifier). You can have a message queue with one consumer, or multiple consumers but there is only one producer.

- The notifier (or producer) also has access to a db that keeps a queue of asynchronous tasks to persist tasks. Once it's in a queue, that message or task won't be lost

- very similar to load balancing (with health server heartbeat checks on all services (consumers) that are doing the "work") but the main difference being message queues are ASYNCHRONOUS for time consuming tasks and load balancing is SYNCHRONOUS

- the consumer and producer can be in the same service where the work is being handled, or separate where multiple other services have access

- a variety of ways that this can be handled. For example, you can just tell the client "ok we did it!" while in reality it's happening a little after

- queues are used to effectively manage requests in a large-scale distributed system to allow us to decouple our processes and distribute/throttle processing load.

- The notifier also acts as a load balancer to distribute requests.

- ex. `RabbitMQ`, `kafka`

#### Methods of storing message queue

- if it's stored in memory, a server outage will not keep that info

- solution: store the queue in a database, each server sends a NOTIFIER a heartbeat every 10 seconds. If a server dies, the notifier consults the db and reroutes unfinished tasks to another server.
  - most message queue solutions have fault tolerance by storing the queue in a db

### Databases (relational, non-relational)

Reasons for:

#### Relational db (sql)

- ACID compliant. data is structured and unchanging, strong consistency
- A relational database that supports SQL (most of them) has the power of running SQL directly without having to load the data in memory.

#### Non relational db (no sal)

- is essentially a hash table. constant time operations
- has less structure and less querying power
- makes the most of cloud computing and storage for horizontal scaling.

- key-value store dbs (the majority of non-relational dbs) are used often to cache
- examples DynamoDb, Redis (in-memory storage only, often used for rate-limiting), Etcd (used for leader election), ZooKeeper (used for leader election)
- some may offer strong consistency, but since no sql dbs are not ACID compliant, some may only offer eventual consistency (usually with a trade-off of having faster performance)

### Other specialized Storage Paradigms

- BLOB (Binary Large Object) Store is used to store an arbitrary unstructured source of data (video, image, audio, binary). A relational db can't store blobs. Usually functions like a key-value store, but a blob store is optimized for big unstructured data. A key-value store is optimized for simple value. Examples - `GCS (google cloud storage)` `S3 (amazon)`

- Time Series - used for monitoring by storing timestamps. Can be set so certain events can trigger read/write. example `InfluxDb`, `Prometheus`

- Graph db - SQL and no SQL dbs rely on a table format. But if the data has a ton of relationships with individual data points, a graph may be a better representation. Social Networks are a good use case. Ex - `Neo4j`. The language used to parse graph databases is `cypher`. Cipher queries make finding graph connections much easier

- Spatial db optimized for spatial data like locations on a map. Queries based on locations can not be optimized based on column indexing like with regular data. Doing queries like "locations in the vicinity of x" is done much better using tree data structures. Usually uses a `quad tree` algorithm

quad trees are trees that have 0 or 4 children used to do location searches used to index two-dimensional spatial data (like longitude, latitude)

```
         (node)
            |
(node) (node) (node) (node)
 null    null  |      null
        4 more nodes
```

#### Optimizing queries

#### Indexing (read-optimization)

- a sorted record will allow binary search O(log2 N), but an unsorted one will require linear time.

- indexing will create another data structure which holds the field value and a pointer to the record, allowing binary searches to be performed. Like a table of contents.

- Downside is that these index structures will require more disk space, so you are sacrificing space for time. ALSO, this will optimize for read, but slow down write operations slightly because you'd have to write to the normal db, then write to the index as well

- this strategy needs to be implemented in relational dbs on frequent rows. SOME no-sql dbs have this baked in, some do not but it's case-by-case

### database failures

- two main ways of ensuring backup
  - replicating, or duplicating the main db. The backup will take over if the main goes down.
  - sharding (splitting up) a db will increase throughput by lessening the load and distributing

#### Replication - preventing an outage with

- prevent a single point of failure by replicating a db to a backup in case the main fails.
- the replica must be `synced` have the exact info the main db has. As such, if any write function fails to the Replica, it should NOT be done to the main at all
  - this is not the case with most regional databases. Ex. if a facebook db server in north america is updated, then a db in asia doesn't need to have Immediate sync. It can update async such that a fb user in Asia receives an updated feed slightly after North American users.
  - this strategy of NOT syncing regional dbs will give you better latency to avoid the round trip syncing immediately.
- if set up correctly, a main db failure will seamlessly be taken over by the replica until the main is back online again. once it's back, the main will resume as the primary db
  - you can replicate primary dbs (two-way syncing necessary) or replicate a read-only db which only steps up as the primary when the current primary goes down

#### Sharding - Data partitioning over multiple databases

- if scaling horizontally (adding machines) with state-less servers, all you need is to copy the business logic. sometimes if you have an in-memory key-value storage like Redis for caching, you need to worry about hash strategies (use `consistent hashing` or `rendezvous hashing`). with dbs, there's an extra layer as it carries its own data

- it's not efficient for all dbs to have the same data. Better to break up a big db into many smaller parts.
- this logic is usually written in a reverse-proxy (on behalf of the db) so that certain data goes to a particular shard

`Partitioning` or `sharding` will decrease latency, increase throughput and can be done in 2 ways:

- Horizontal partitioning separates (users a-j, j-z) into smaller shards (or partitions) of the same columns

- Vertical partitioning separates columns (categories) into shards (or partitions) for ex when a column is rarely used, it is stored elsewhere.

  - don't confuse vertical partitioning with vertical scaling. Both horizontal and vertical partitioning is a form of horizontal
    scaline since it requires multiple machines rather than upgrading one machine

- when sharding, just like in servers and load balancers, must take into account hot spots and aim for an even distribution by using a good hashing function that guarantees uniformity.

- Pros and Cons

  - Pros: avoids failures
  - Cons: Must take into account hot spots (if partitioning by region, are certain regions hot spots?)
    can be hard to determine HOW to shard efficiently
    joins can be expensive over different shards

- different for SQL vs NO-SQL dbs.

- note that sharding is much simpler in noSql because you don't have to worry about joins and dependencies within a table
- dyanamoDb has built in funcationalities out of the box

### Leader Election

- the same idea of threads and locks but in a distributed system
- used when only 1 of the replicated nodes should be responsible fo something

  - for example if you have a subscription service like Netflix, when using a 3rd party service like paypal to process payments, you don't want that 3rd party service to have direct access to your UsersDb.

  - another example is replicated dbs. Only the main active one should be in charge of writing so data is consistent

- Usually there is a service that sits between your db and the 3rd party service that has access to your db and checks the status of `payments` or something, and communicates with the payment service. When you have important logic like payment, you want passive redundancies of this middle service so that only one "leader" takes care of the logic and the others are on standby.

- The logic of multiple machines agreeing on a leader can be very complicated. The act of sharing this state of knowing who the leader is done with a `consensus algorithm`, specifically like `Paxos` & `Raft`

- example of apps that use a consensus algo under the hood - `zookeeper`, `Etcd` (EtsyDee) are both strongly consistent and highly available key-value storage that's often used to implement leader election

#### Zookeeper (leader follower model) in detail

- when you have replication, you need consensus.
- In a zookeeper service, the same set of data is held in multiple machines
- one machine is the leader.
- clients connect to any instance of those nodes to get data
- reads can be done from any node, leader or follower
- writes must go through leader
- uses distributed locks, so read consistency is guaranteed

### Consistency, Availability, CAP Theorem

- availability is measured by `9s`. Five 9s means there are outages of seconds over a year
- in reality, most major cloud vendors promise `99.95%`, which is about 20 minutes of down time a month
- Strong Consistency means data is rarely stale. Eventual consistency means the data will sync over a period of time (seconds or minutes) when the network traffic is low.
- CAP theorem (Consistency, Availability, Partition)

  - in the event of a `Network Partition (server failure, network failure)` a system must prioritize either `consistency` (pause user operations until network is back up) or `availability` (continue allowing users to make API calls, but data is not consistent)
  - For example, if the "likes" service that tracks the number of likes is the issue, probably ok to prioritize `availability` and keep allowing users continue
  - for something like a bank statement, that's not the case

- real life examples:
  - weak consistency
    - Tech: Memcache
    - examples: Voice app, real time video game, video chat
  - eventual consistency
    - tech: Amazon S3, Amazon SimpleDB, SMTP (email protocol)
    - examples: social media likes, DNS
  - strong consistency
    - tech: RDBMS, file systems
    - examples: bank transactions

### Consistency models

1. Strictly Consistent (locks all other threads during reads and writes). Distributed
   systems are rarely strictly consistent
2. Sequentially Consistent. Don't care about reads, but writes stall system and stays consistent.
   Works well when there are more reads than writes
3. FIFO (PRAM) Consistency - both reads and writes are not locked, ordering within one system
   is good, but not other systems
4. Eventual Consistency - no ordering. On write, update the cache eventually

### Peer-to-peer networks

- used often in file distribution systems
- built with tcp/ip
- when big data needs to be transferred to many clients or peers

```
         one machine with stuff
                  |
      1,000 peers who needs the stuff
```

- transferring the big chunk to each peer will take a very long time
- sharding the info into several servers will divide the time by the number of servers, but it's still extra resources

- Solution: Keep using that one machine, but divide the data into 1,000 pieces and send those 1/1000 data to each peer. Then, each peer will share with each other in parallel (ex. peer 1 <-> peer 2 while peer3 <-> peer4 etc.. )

- implementation: Each peer needs to know the order of what peer to talk to via `gossip protocol` or `epidemic protocol` where the peers talk amongst themselves to figure out what peers to talk to each other based on current data fragments. Under the hood there is a distributed hash table that tracks the progress of each peer and its data fragment.

- ex. `Kraken` used by uber

### Polling (continuous req-res loop at an interval) and Streaming (event driven)

- when a client needs to request data that is continuously being updated like the weather or the status or something, the standard request model is not optimal
- to see regularly updated pieces of data, `polling` or `streaming` can be used
- `streaming` is also called `pushing`. The opposite of this, the traditional http req-res model is `pulling` because the client initiates contact with a req to pull data.

- `Polling` the client simply sends a request based on a set interval. ex. client checks the status every 5 seconds. This could work for something that has regular changes, but not great for specific event change updates like a text message as data will be stale between the interval `n`. This can be mitigated by lowering the poll interval but it comes with extra load on the server.

- `Streaming (Http streaming)` - client makes a req to server, then the server sends back data indefinitely. After the initial req, the server proactively continues sending data on event changes

- Two ways of implementing HTTP streaming. Chunked and Server-Sent-Events.

  - the server sends data as "Chunked" meaning incomplete and indefinitely keeps sending data back to client

  - Can stream over simple http.
  - not good for bidirectional communication

- One is not necessarily better than the other. If the data needs instantaneous updating, use streaming. If the data only needs to be updated at an interval, use polling. Implementation of polling is a lot easier

- web sockets use TCP connections

- both of these concepts work in a simple setup, but a publish/subscribe pattern will be needed with persistent data in a large scale distributed system

- XMPP is a peer-to-peer protocol unlike the usual client-server model. It can be used for chat as well as an alternative to web sockets, but is slower and more secure.
- Websocket (faster, TCP, less secure). XMPP (peer-to-peer, slower, more secure)

- pub/sub and streaming are the same "category" of techniques as the client signs up to a topic. Polling is not, as it's just a repeated http request

- `long polling` keeps the connection alive so that some parsing steps can be skipped over after the initial req. it is a technique used to make polling more efficient

### in the context of network types

- polling uses req-res communication, but at a fixed interval
- streaming doesn't require a request, but is event based. Event driven communication includes Streaming, WebHooks, WebSockets.

### Webhooks

- you register a server with an event (typically a single event) and a callback URL
- when the event gets updated, send POST request to callback URL
- good for specific events. Multiple events can be noisy and server will have to handle a lot of traffic

### WebSockets

- Client and Server handshakes initially (http), then switches to a bidirectional TCP.
- is low latency communication and less overhead compared to http since you're not dealing with headers.
- hard to scale and not secure

### PubSub Model

- very similar to message queues, except the message can be received by MULTIPLE subscribers

- an extension of the concept of streaming. Streaming works with a simple connection, but what if we need a large scale distributed system (micro services system) where the data message needs to be persisted in the event of outages.

- a pubsub model consists of 4 entities

  - Publisher - servers that emit messages to topics
  - Topic - where the messages are stored based on channels of specific information
  - Subscriber - listens to specific topics for messages
  - Message - the set of operations transferred from publishers -> topics which will also go from topics -> subscribers

- unlike the streaming websocket model, the publishers and subscribers don't know and don't care about each other. The topic is the storage of the operations and handles receiving data from publisher and sending data to subscribers

- PubSub models will often come with powerful guarantees like `at-least-once-delivery`, `persistent storage`, `ordering` of messages. Note that it's impossible to guarantee `ONLY-once-delivery` and the same message could be sent multiple times if a connection is dropped because of the way message receipts work. ex. - topic 1 sends a message to subscriber1. subscriber1 gets the data but the network is disconnected right before it sends a "received" receipt, so when the network is back, it receives message1 again as a duplicate

- Keeping the above concept of the possibility of getting the same operation message multiple times, it's important to set up PubSub models with `Idempotent Operations` where the outcome is the same whether an operation is done once or multiple times.

- Popular solutions `Apache Kafka`, `Google Cloud Pub/Sub`

### CDN or CDA

- content delivery network is a group of servers around the world that can lower latency, add redundancies and fault-tolerance when delivering static data

- sits in the DNS layer to route calls to PHYSICALLY different location servers. This is conceptually similar to a load balancer, but is different as load balancers usually distributes network calls to individual severs that are all close together in location.

### Rate limiting

- DoS (Denial of Service) attacks involve spamming a server with requests to damage or take down the service.

- this can be thwarted by Rate Limiting which returns an error code `429` "Too many requests" on a request based on parameters like ip address / user, number of requests per minute, region

- DDoS (DISTRIBUTED DoS) attacks are done from multiple client sources, and is harder to prevent with a simple rate limiting on ip address / user. In a distributed system, the rate limiting will need to be checked against another entity that connects to ALL replicas of the server like a redis server

- Implementation can be done with a key-value in memory store like `redis`. The server gets a request, then asks redis "hey are we doing ok with rate limiting?" before responding

## Online vs Offline systems

- Online systems or `services` wait for a request and try to handle them quickly.
  - low latency and availability is prioritized
  - ex. web servers, dbs, caches
- Offline systems or `batch processing` systems process lots of data
  - high throughput is prioritized
  - `mapReduce` is a classic example of an offline system
  - message queues are also offline
- streaming systems are between the two

### MapReduce

- https://youtu.be/sGuGBkH79iI?si=T2Y0gEMikXRNNS6u

- processing data set over multiple machines (as a result of horizontal scaling) is challenging
- is a way to get derived data
- a framework that allows processing of very large data in a distributed system quickly
  2 main steps:

map - take the dataset and map to key-value pairs, then shuffle them to organize these pairs such that the pairs of the same key are routed to the same machine - example. if there were 10 documents, each word might have all the documents where it appears "the": [1,4,5]

reduce - reduce the shuffled key-value pair and transform them into more meaningful data. - all the mapper servers pool info into reducer machines. one reducer will be in charge of tallying all "the": occurences

- the results are all stored in a `distributed file system`, an abstraction over a cluster of machines that allows
  them to act like one large file system.
  implementations include `Google File System` and `Hadoop Distributed File System`.
  Files are split into chunks of a certain moderate size < Gb and those chunks are sharded across a cluster of machines.

- also used in batch processors like apache `Spark` and `Flink`
- MapReduce algos have fault tolerance by using Idempotent Operations in both the Map and Reduce steps to shield against outages
- common tasks including sorting, word count, grep
- for every mapReduce task, you already know the volume of data you're working with since it's an `offline` system. There
  are no uncertainties like users making requests from a UI. You don't have to add a server for a spike or worry
  about consistent hashing!

### Security http and https

- an IP (internet protocol) packet is the base level of network communication
- TCP (transmission control protocol) is a protocol that sits on top of IP to ensure delivery in order (early email would send fragmented) by establishing a handshake and keeping the connection open. Websockets use TCP
- Http (hyper text transfer protocol) sits on top of TCP and has additional info with a Head and Body

Http can be intercepted by a malicious actor in a `man-in-the-middle- attack`.

- `SSL` (secure sockets layer) is the older framework that http can sit on top of to ensure a secure connection. The modern version of this is `TLS` (transport layer security) and http that sits on top of `TLS` is called `https`

- While `SSL` is not used often anymore, the `SSL certificate` is still a part of the TLS flow.

- a `https` (s stands for security) protocol sits on top of`tls`, which means the protocol will encrypt the message to avoid `man-in-the middle` attacks using either a `symmetric` (1 key) or `asymmetric` (2 keys) encryption along with an `SSL` certificate. Tls handshakes are similar to tcp handshakes, but it has a strict encryption / decryption step.

- `AES` (advanced encryption standard) is a widely used symmetric key encryption algorithm and is considered the gold standard of encryption.

### Common points

- storing static data

- if the data is small (5 pictures for a dating site), then you have the choice of storing in a Distributed File System (pics are saved to machines directly) where the pros are faster, cheaper, easier to implement. Cons are not secure or consistent

- a blog store like S3 is NOT ACID compliant, but it's more secure and persistent and can store bigger data.

- If the static data is large (songs, videos) or is sensitive, then a blob store is probably better

- Both distributed file systems and blob storage will be governed by a service that has its own table with userId, imageId, and a reference to the DFS/blob table with an image URL.

- auth / gateway service

- in most systems with a user that requires a profile via email/password, always make the point to send that info as a hashed token (instead of the password itself) and that the client will always connect to gateway service that takes care of auth. If authenticated, the gateway will then forward the request to the correct micro service. Then it will also forward the response back to the client.

### blob db vs distributed file system

- Blob storage is the SAME as object store (S3), but they are different from K-V stores/db (Redis), also different from Block Storage (AWS EBS) and different from DFS (AWS EFS)

  - Blob storage is useful for unstructured data (metadata, images)
  - DFS is useful when you need a hierarchy (., ..) and a tree structure and dynamic sizing
  - Block Storage is useful when the data is uniform since it divides each block into equal size

- a blob store can be relational or non-relational key-value pair
  - if it's relational, it is ACID compliant.
  - use a blob store if the info is unstructured and sensitive
- a distributed file system is usually cheaper and faster. should be first choice
  - you still need a db to map the imageId or dataId to FileUrl

### Api Design

- distinct from systems design. it is not a subset of system design, but a sibling of it
- apis are important for all companies, but some like Stripe will have an entire business which is selling access to one api.
- designing api is important as it becomes extremely hard to edit / remove an api once it is used by services and users.
- large companies will require a rigorous review process before creating a new api.

The final product of "design Stripe Api" should look like a proto file like this:

```
# Entity Definitions:

## User
- id: uuid
- name: string
- email: string

## User
CreateUser(user: User) returns User
GetSingleUser(uuid) returns User
ListUsers(uuid[]) returns User[]
UpdateUser(uuid, updatedUser:User) returns User
DeleteUser(uuid) returns deleted User

## Card
Create
Get
Update
Delete

## Charge
Create
Get
Update


```

## testing resiliency

- some companies like uber will use a tool like `hailstorm` that randomly shuts down a microservice and logs what happens to find weaknesses

- distributed systems can be so large and complex that it's possible to lose track of all service dependencies. Ex.. an owner of a microservice may not be completely clear on what othe
