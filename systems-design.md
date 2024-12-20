# Systems Design

## quick facts

- draw.io
- most servers can handle about 10,000 - 100,000 qps depending on type
- generally RDBMS as a System of Records (Source of Truth, OLTP) is recommended
- when a db reaches 10s of Terrabytes, then a NoSql option becomes a priority
  even if the data is relational

- if a network fails, let the protocol (tcp) handle it
- if a node fails, be able to explain what happens and how it's handled
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

## Steps

1. Scope the problem
2. Capacity Planning

   - Throughput/load estimation (for example, servers handling write operations in social media)
   - rps / qps (request or query per second) is the main metric
   - Ask for average daily users, and possibly guess the rest
   - for ex. for social media, try 100 million users who

     - suppose 5 writes on average = 500 million a day
     - get average qps by dividing 500 million by (24 \* 3600 ~ 100,000) = 5000
     - 5,000 qps for AVERAGE, but for peak, you might multiple by 3 = 15,000 qps
     - one service might handle 1,000 second, so you'll need some redundancy, load balancer etc..

   - Storage estimation

   - how much data to keep eg 5 years
   - multiply daily _ 30 _ 12 \* 5

     - byte 1
     - kb 1 x 10 ^ 3
     - megabyte 1 x 10 ^ 6 (million)
     - gigabyte 1 x 10 ^ 9 (billion)
     - tera 1 x 10 ^ 12 (trillion)
     - peta 1 x 10 ^ 15 (quadrillion)

   - Bandwith estimation (how much data is being processed per second)

   - take the value form #1 (rps) and multiple by how much data is processed
     per query

3. Define your data model

4. Define your API

5. High Level Design (draw.io)
   Draw a block diagram with 5-6 boxes representing core components (client, load balancer, servers, CDN, database)

6. Detailed Design
   Dig deeper into these high level components.
   Take trade offs, pros and cons of each decision
   ex.

- how should we partition our data to distribute to multiple dbs?
- How would we handle hot users who tweet a lot or follow lots of people?
- since user's timeline will contain most recent (and relevant) tweets, should we try to store our data in such a way that is optimized to scan latest tweets?
- How much and at which layer should we introduce caches to speed things up?
- What components need better load balancing?

## Data Models and Query Languages

The relational model (Relational Data Base Management Systems) became the dominant
system as they were generalalized and scaled well beyond their original scope

### Databases (relational, non-relational)

- On Line Transactional Process or `OLTP system` requires fast updates. `RDBMS` is the choice
  - streaming
  - data needs to be in the Gigabytes but not larger
- On Line Analytics Process or `OLAP system` needs optimized reads and inserts,
  but can have slow updates since it doesn't usually need to be a live system
  - batch processing
  - data can be in the Terrabytes or Petabytes
- note that technically, data warehousing is just the storage, and `OLAP` is
  one way to process that data.
  - Columnar like `Hbase`, `BigQuery`, `Snowflake`, `Redshift`
    - note that Columnar dbs can be SQL OR Nosql. `BigQuery`, `Redshift`, and `Snowflake`
      are SQL colmnar dbs. `Hbase` is noSql.
  - you can also use SQL to extract data from noSql dbs. The querying method
    is decoupled from the db type.

Reasons for:

#### Relational db (sql)

- generally, most companies will want an RDBMS as the primary source of truth until they scale
  to the point where it just can't scale.
  - The first millions of users still won't break your SQL db
  - Breaking point is around the need of > 5TB a year
  - other exceptions include metadata-driven data sets (document store),
    massive amounts of ingestion of data in the thousands per second,
    super low-latency applications
- ACID compliant. data is structured and unchanging, strong consistency
- A relational database that supports SQL (most of them) has the power of running SQL directly without having to load the data in memory.
- `serializability` is the term to describe the Isolation level (AC[I]D) properties.
  each read/write
  is ordered and transactional. usually done via `2 phase locking`

- sql systems use `write-ahead logs` to keep track of all modofications in disk
  before changing the table. This allows for full recovery after power outages

#### Trasactions and ACID

- abstraction used that provide ACID properties. a single command will either
  all succeed, or all fail without any side effects

- "I" isolation is hard to implement. How do you have concurrent writes
  without race conditions
  - Actual serial execution
    - idea is to implement all queries on a single thread. simple to implement
    - only possible if it's an in-memory database
    - usually not practical to run large queries on a single thread
  - Two Phase Locking
    - each object has a lock and only available one query at a time
    - most frequent implementation in most dbs
    - poor performance when unnecessary locking happens, along with frequent deadlocks
  - Serializable Snapshot Isolation
    - Optimistic control where you assume there are no concurrency issues
    - rolled back only when a bug is detected

#### Non relational db (no sal)

- BASE (basically available, soft state, eventual consistency)
- is essentially a hash table. constant time operations
- has less structure and less querying power
- makes the most of cloud computing and storage for horizontal scaling.

- key-value store dbs (the majority of non-relational dbs) are used often to cache
- examples DynamoDb, Redis (in-memory storage only, often used for rate-limiting), Etcd (used for leader election), ZooKeeper (used for leader election)
- some may offer strong consistency, but since no sql dbs are not ACID compliant, some may only offer eventual consistency (usually with a trade-off of having faster performance)

## Monolith vs Microservice architecture

- the previous was called "service oriented architecture" where multiple
  services existed, but were coupled with shared resources
- Monolithic one or a group of machines (servers) handle ALL services.
- Server Orientated Architecture. precursor to microservices where different
  servers shared some data
- Microservice is a single business unit where each service is a self contained
  set of logic

### Pros and Cons

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

- Microservice Registry
  - a database that keeps track of all instances of each service. This can
    be in the hundreds for large companies
  - when making api (either client side or server to server rpc), it's necessary
    to have a service-discovery step using the service registry to see
    which instances are available for load balancing properly in LB or Api Gateway

## protocols

- `ip/tcp` (ensures delivery with handshakes and acknowledgements).
  - at least one time delivery. Uses a checksum to see if the entire package
    was delivered successfully before sending back an ack
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
  - `webhooks` use http
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

### web server vs application server

- a web server serves static data
- an application server serves dynamic data, often from dbs. In modern architecture,
  static data is served from something like an s3 bucket with a CDN in front of it

### REST vs RPC

- rpc describes the behavior, not the resource
- rpc is often used between services

- RPC and REST calls comparison
  Operation RPC REST
  Signup POST /signup POST /persons
  Resign POST /resign DELETE /persons/1234
- https://github.com/donnemartin/system-design-primer#hypertext-transfer-protocol-http
- RPCs are invoked with names that describe the behavior like functions and
  abstracts details about resources

### DNS

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
- `Akamai`, `Aws CloudFront`

### Proxies

- Forward (default) proxies sit between the client and server on behalf of the CLIENT.
  It can be used as a cache, add/remove headers. It masks the client IP to the server.
  Most notable example is a VPN (Virtual Private Network).
- While in the general context of proxies, a reverse proxy points to all proxies
  that function on behalf of the backend, there is another usage of this term
  that is a lot more specific (see next section `reverse proxy vs api gateway vs load balancers`)

#### Reverse Proxy vs Api Gateway vs Load Balancing

- A `reverse proxy` works like this.
  Client -> proxy -> a server -> BACK to proxy -> client
- used to intercept all requests from the client and
  all responses from the servers. It is useful even if you just have 1 instance
  of a server because it handles:

  - security: hide identity of backend servers
  - caching
  - auth: ssl termination
  - compression

- an `Api Gateway` is useful in a `service-oriented architecture` or a `micro
service` architecture as it acts as a single point of entry for a variety of
  backend APIs. This is likely overkill for a monolith
- features include

  - routing requests from single point of entry (crucial in refactoring from
    monolith to micro services)
  - authn
  - authz
  - monitoring logs for incoming traffic
  - rate limiting

- a `load balancer` handles traffic load to muitiple nodes of the same service.
  this is not useful for single instances, as all traffic will just hit the same node.
  Some `api gateways` also handle the function of a load balancer, so the term
  `load balancer` refers to this singular functionality. Unlike a `reverse proxy`,
  a load balancer doesn't receive data back form the server. It routes the req,
  but the res goes straight to the client -

- Hardware vs Software

- Hardware load balancers are actual structures. expensive
- Software load balancers are USUALLY what systems design interviews are referring to. Software is more flexible in what you can do.
- ex. HAProxy, nginx

- can be set for the database, or even on the dns layer (google.com has many IPs and the DNS round robin will assign a request to the correct dns server to respond with a domain name) - helps scale horizontally by distributing requests to multiple servers - avoids duplicate requests - ONLY makes sense if you have multiple servers to route to

      - Load Balancers can use different algos to choose a server.
      - round robin, IP based (L4 ex AWS NetworkLoadBalancer), app info based

  (L7 AWS ApplicationLoadBalancer) - because L4 only has access to basic info like IP address, it is simpler
  to configure and requires less computation power. On the other hand, l7
  is more config and computation but has access to all application layer
  headers, so is more efficient for load balancing

      - some load balancers don't support certain protocols like UDP (AWS)

- examples `nginx` is both a `reverse proxy` AND a `l7 load balancer`
- usage: for monoliths, usually a `reverse proxy` and a `load balancer` is enough,
  so something like `nginx` is a great fit, while SOA or micro services will often require an api gateway to organize
  the fleet of servers

#### Server-Selection Strategy with load balancers

1. random
2. round robin (cycles through all servers in order). more ven than random
3. weighted round robin - certain servers have weight (priority) based on power of individual servers or past performance and are given more requests.
4. Ip based assignment - Client request ip address will be hashed and used to assign to an index number of server. Each individual client is always sent to the same server to maximize cache functionality.
5. Path based - requests are distributed based on the path of the request. Each server specializes in specific functionality. Speeds up deployment as you only need to re-write code for 1 server type.

- Random, round robin, and weighted round robin will not work with server side in-memory caching because it won't maximize cache hits as the requests will come from random clients.
- Multiple load balancers can have different strategies in a singular system.
- clients => path based LB => weighted RR LB x 2 => servers

### Hashing

- Concept of an algorithm that takes input and returns an item in an alloted number of buckets.
- Hashing becomes VERY important if your system uses any kind of in-memory server side caching because your client needs to request to the SAME server every time to avoid cache misses.
- Anything that makes in data, and returns an integer that points to an index of a sample size. IP address, username, any data can be hashed.
  2 main hashing algos in systems design

- Consistent Hashing (often used by Load balancers) and Rendezvous Hashing (highest random weight hashing)

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

## Storage systems

Systems can be broadly separated by usage and urgency

- By usage
  1. Systems of Record (OLTP)
     - the "source of truth" db
     - normalized
     - comes from user input, for example
  2. Derived Data System
     - data that was replicated from a source of truth
     - denormalized by nature
     - often optimized for an OLAP system
- By urgency
  1. Servers
     - Online system
     - the objective is to respond to the request as soon as possible
     - response time is the key metric
  2. Batch processing systems
     - Offline system
     - a job is run on a schedule. there is no user waiting for the result
     - key metric is throughput
  3. Stream processing system
     - hybrid system
     - like batch, but the job is done immediately after and piped

## Batch processing, HDFS, MapReduce, and Dataflow Engine

In the simplest terms:
A system where the input is some `distributed file system` and the output is
`derived data`

- high level workflow:
  `OLTP db -> HDFS (raw data lake) -> Batch Process (MapReduce, Spark, etc..) -> Data Warehouse OLAP (cleaned up data)
`

UNIX Commands

- the best example of a single node batch processing system is Unix commands
- it uses memory effficiently by trying to use in-memory, but switching to
  disk when necessary
- the interface is simple with stdin / stdout / files with a great piping system
- very efficient way to search for strings, process data, then output to a file
- BUT it only works on 1 node

A distributed batch processing system is like Unix for many nodes.

- usually within one data center with many connected nodes with a daemon process
  that allows to peek into each other's files
- Uses a distributed file system as the input (or object storage like `S3`)
- a DFS can store files of any encoding, so it is "raw" data, called a `Data Lake`
- like unix commands, does not mutate the input
- MapReduce can be run as a batch process on an HDFS to clean up the data, then
  send to a Data Store (`ETL`)
- fault tolerant and all distributed nodes act as if they were one node like Unix commands
- Dataflow Engines like `Spark, Flink` do a better job than MapReduce

- because DFS and batch processing has opened a world of unformatted raw data,
  there is a lot of tech around having a common standard for OLAP work

### Parquet file format

- Apache Parquet is a column oriented data file FORMAT.
- used for OLAP and has highly efficient data compression / decompression
- supports complex data types
- also see `apache iceberg`

## Stream Processing

- when message are unbounded, it is a `stream` of data. Unlike a batch system,
  this is not a purely `offline` system. somewhere between `online` and `offline`
  as messages are read, but it can be asynchronous depending on the situation
- aliases include `pub sub model`, `producer-consumer model`
- related terms include `webhook`, `message queue`, `message broker`, `kafka`, `flink`

- stream systems can be differentiated by 2 categories

1. What happens when consumers can't keep with messages being produced?
   a. Drop Messages
   b. Tell producers to stop messages
   c. Buffer messages in queue until traffic is cleared

2. What happens when nodes die?
   a. messages are lost
   b. messages are recovered

### Simple stream processing systems without any intermediary nodes

#### Protocol level stream processing

- it is possible to use UDP at the application level and have a direct
  notification system without any intermediary nodes as the simplest streaming system
- will drop messages when consumers aren't ready, and messages are lost and the
  application will need to handle those situations
- not good for important messages

#### Using http or rpc

- it's possible for a server to listen for an event and directly send a push
  notificaiton to the client. this is what `webhooks` are
- again, it is for simple sparse events. won't handle consumers that aren't
  ready or lost nodes very well

### Robust solutions using intermediary nodes

- usually a system of intermediary nodes are required to ensure durability
  and scaling of large quantities of events
- abstracts the logic from the application layer

#### Non-log based Message Queue aka AMQ (Advanced Message Queue Protocol) systems

- ensures some scaling
- a message broker is a hybrid `database server` and a traditional server that
  is optimized for handling streams as traditional dbs are optimized for retrieval/mutations.
- it may use in-memory buffers or disk writes to handle for busy consumers
  - if only in-memory, a broker outage will lose messages, but most will
    have some kind of disk persistence
- messages are DELETED after the consumer is done processing them, so it deals
  with relatively a small pool of streams at any given point
- partition tolerant as it usually has replicas and some consensus algorithm
  system. for example, `RabbitMQ` uses `Zookeeper` nodes to ensure data is intact
  - like a distributed database system, a controller monitor health, handles
    failovers, distributing work to the right nodes, etc.. to ensure durability
- since messages are deleted from memory once it's processed, the input is
  mutated. Is not repeatable like batch processing or log-based Message queues (see below)

Consumer strategies

#### Log based message queue sytems (kakfa, aws kinesis)

- has partitions per topic
- broker appends data to a log and saves to disk. messages are not lost
- monotonic offset allows for ordering of messages
- main difference from message brokers is that it does not delete messages even
  after consumers process them, and stores it on disk, allowing for `replayability`
  from the consumer side by changing the offset
- read-only and does not mutate

- when there are multiple consumers, there are two strategies

1. `load balance` to one consumer
2. `fan out` to all consumers

When using a log based approach, you generally fan out to all consumers in
a partition. An AMQP system usually opts for load balancing, so if you don't
need ordering of messages, a log based queue may not be needed

- often used for `Change Data Capture` for near real time logging

## Types of nosql dbs

1. k-v store (in-memory ones like `redis`, `memcached`, or non-in-memory like `Riak`)

   - simple data used for caching
   - not suitable for analytics since it doesn't have secondary indices, but
     implementation is similar to wide-column dbs like Cassandra.

2. document store (`mongo`, `dynamo`, `elasticsearch`, `aws s3`)

   - for storing semi-structured data like XML, JSON, BSON.
   - high flexibility with changing data structure
   - generally used for fast insertion and quick retrieval of user metadata
   - compared to columnar, optimized for Writes

3. Columnar, or wide column store (`Apache Cassandra`, `Apache HBase`, `Google BigTable`, `AWS Redshift`)

   - a "super" key-value store where the key is an entire column, allowing
     for nested complex data
   - compared to document stores, optimized for reads
   - great use case for analytics

   - for datawarhousing `redshift`, `snowflake`, `big query`
   - for OLAP `hbase`

4. graph (neo4j)
   - used best to store data like social media relationships

- Other slight variations for data storage
  - Blob/object store (can be relational or not relational) - `s3`
  - Block Storage (`AWS EBS`) which has the same set blocks of memory
  - Distributed File Storage (`google file system`, `aws efs`)

#### differences SQL, NoSql

- at the highest scale (Terra or petabytes of data), a sql solution will slow
  down with joins and write operations despite optimizations. At that point,
  the only solution is the easily scale with a noSql solution like DynamoDB
- any point before that level of scaling, most companies will benefit with the
  structure of a sql solution like postgres as the single point of truth
  - parts of the Sql db can splinter off for ex. metrics to a nosql db or
    an async offline system that does batch processing (ETL) with something
    like Spark that sends data to a warehouse. Searchable data can go to Elastic Search
  - `ETL` is primarily used when you go from a `OLTP system` to a `OLAP` system

#### Search index

- it is common for the primary RDBMS to send data to a secondary db for metrics/analytics
- data lakes / data warehouses often use OLAP systems with a star schema like snowflake
  or lsm + ss table like HBase to store data for fast reads.
- To search OVER those dbs, we need a search engine
- Most popular search engines include Elastic Search, Solr, and Apache Splunk (all based on Apache Lucene
  ).
- Lucene uses LSM + SS table and strings are tokenized. Also possible to
  search for numbers and geolocations (geohash). Lucene engine is open source and
  is for single nodes. ElasticSearch, Solr is the distributed version of Lucene
- Generally, the main use case for hdfs (mapReduce) is distributed batch
  processing and the main use case for Lucene is string searches. Those frameworks
  (`ES, Splunk`) allows Lucene to be used in a distributed system

#### data warehouse

- a special type of database that specializes in analysis
- often uses a relational model, but a different optimization from what's used
  for traditional transactions - uses `star` schema or `snowflake`
- example of data warehouses `snowflake`, `bigQuery`, `redshift`
- related but not exactly the same topic, some dbs are optimized for real time analytics
  and not the actual storage aspect. `druid`, `influxDb`

### Other specialized Storage Paradigms

- BLOB (Binary Large Object) Store is used to store an arbitrary unstructured source of data (video, image, audio, binary).
  - a subclass of noSql
  - A relational db can't store blobs.
  - Usually functions like a key-value store, but a blob store is optimized for big unstructured data
    while a key-value store is optimized for simple value.
  - `GCS (google cloud storage)` `S3 (amazon)`
- Time Series
  - used for monitoring by storing timestamps. Write once, read many times
    over time ranges queries.
    Can be set so certain events can trigger read/write. example `InfluxDb`, `Prometheus`, `Druid`
  - ingests millions of writes per second, which is higher throughput than normal OLAP system
  - different function as a data warehouse
- Graph db
  - SQL and no SQL dbs rely on a table format. But if the data has a ton of
    relationships with individual data points, a graph may be a better representation.
  - Social Networks are a good use case.
  - `Neo4j`. The language used to parse graph databases is `cypher`.
    Cipher queries make finding graph connections much easier
- Spatial db optimized for spatial data like locations on a map. Queries based on locations can not be optimized based on column indexing like with regular data. Doing queries like "locations in the vicinity of x" is done much better using tree data structures.
  Usually uses a `quad tree` or general `geo spacial hashing` algorithm
  - first, split the world into sections. Each section is reprented by a char
  - within each parent region, split into more sections. concatenate another char. repeat
  - for each longitude/latitude point in the world, you can then get the geo hash
    and a depth which corresponds to the length of the string to get a match of
    all nearby records.
  - ex. full geo hash might be "3kajs31". depth 3 = "3ka" so all other
    records with the hash "3ka" will be found
    - pitfall. If a point is right next to another section of the world, they
      wil not show up in the search. you may have to get multiple neighboring
      sections to get all close points

quad trees are trees that have 0 or 4 children used to do location searches used to index two-dimensional spatial data (like longitude, latitude)

```
         (node)
            |
(node) (node) (node) (node)
 null    null  |      null
        4 more nodes
```

### database partition tolerance strategies

- leader follower replication
  - a lot of sql solutions provide this out of the box (postgres, mySql)
- leader leader replication
- federation
- sharding
- denormalization
- sql tuning

#### Replication

- prevent a single point of failure by replicating a db to a backup in case the main fails.
- if set up correctly, a main db failure will seamlessly be taken over by the replica until the main is back online again. once it's back, the main will resume as the primary db
- 3 main leader/follow paradigms

1. Single leader replication (Single data center, read heavy system)

   - optimizes reads
   - the majority of db replication is leader-follower, especially if you only
     have 1 data center. multi-leader should only be used in special circumstances
     in multi-data center systems
   - leader usually keeps a `row based log` that describes each row, and
     the follower reads from it. Row based logs describe each row of a table
     unlike the older `write-ahead logs` which describe the strict db operations
     in bytes of block data.
     Row based logs are easier to port over different software versions.
     `CDC` is generally done this way as well
   - usually there is 1 `synchronous` follower as a backup for fallback, but
     the other followers are updated `asynchronously`
   - provides partition toerance, load management, as well as latency (can serve at edge)
   - if requirement is strongly consistent, the write happens only if all
     writes to follwers are complete. Realistically, this is not worth it
     for data centers that are far away because the round trips are too laggy.
     For that, the compromise is eventually consistency and higher throughput
   - PROS:
     - easy to implement compared to multi-leader - relatively fast writes if using async (just copy to 1 follower, then assume
       rest is fine)
   - CONS
     - Failover (the leader node going down) is still tricky to reason with as
       a consensus needs to be built about who the new leader is (Raft, Pax)
       - generally, when a leader goes down, it persists the state of when it
         went down in a log. One of the follower nodes become the leader. When
         the original node comes back up, it catches up to the leader by comparing
         the logs
     - if synchronous, the more followers there are, the more latent it becomes
     - `read from writes` (an update may not reflect
       until there is logic that dictates that when you update to a leader, you
       should also read from it so you see the changes)
     - `monotonic writes` the changes must not appear to be going backwards if
       using async followers. solve by always reading from the same node
     - Dependencies ex a comment answer should not propage before commant questions.
       solve by grouping together dependencies as one unit of change

2. multi-leader replication (multi data centers or heavy write loads or
   offline write support, or collaborative writes like google docs, calendar apps
   , figma)

   - the exception to the rule, often when you have multiple data centers,
     have very high write loads, or need to support offline writes.
   - SOME nodes can read and write. Most can only read. Classic example is in a
     multi datacenter system, each data center has 1 leader.
   - eliminates cross-datacenter network calls. In theory if the client connects
     to the leader in one data center, the followers will get updated via the
     local data center network
   - also, if you absolutely need to optimize for writes
   - each data center can have 1 leader and followers
   - when one data center goes down, the others can continue operating
   - data needs to be synced and merged when multiple writes need to be resolved
   - ex. google calendar is essentially multi-leader as all of your devices
     are leaders with write access. When you don't have internet access,
     it is partitioned but the write will happen when you're back online (consistency
     over availability)
   - will need additional load balancing logic for writes to decide which data center
     leader will process the write
   - For BOTH multi-leader AND leader-less replication, the writes need to resolve
     conflicts, which is the biggest CON of non single-leader replication!
   - how to detect concurrency
     - need to use version vectors to detect missing versions
   - PROS (applies to both multi leader and leader-less):
     - fast writes as throughput is more than 1 node like in single node
     - allows for multi-region, global service
     - if one data center goes down, the others keep going
   - CONS (applies to both multi leader and leader-less):
     - write conflicts from multiple leaders
     - main ways to deal
       - avoid write conflicts by assigning certain sets of data to one data center
       - last write wins. Cassandra (easy to implement, but issues. offline writes? lost writes)
       - on-read. store conflicting values and make the client resolve on-read
       - on-write. merge writes when there is a conflict on the 2nd write

3. Leader-less replication (Cassandra, Dynamo, Riak)

   - send write/reads to all nodes in parallel
   - when a certain number of nodes respond with success, the client is told it's a success
   - the biggest difference between this and multi leader is that when a node dies,
     it just gets ignored. There is no failover, since we continue writing to the other
     ones.
   - to avoid stale data, READ operations are sent to multiple nodes in parallel
     to compare the version number and read from the newest data

   - strategies to repair failed writes
     1. anti-entropy
     - a background process to look at all nodes, and get most updated data (version info) and
       propagate to other nodes
     2. read repair (more common)
     - repair on read. read in parallel from all nodes and find the most updated
       node with a quorum
     - quorum can be found by setting the number of total replica nodes as an odd number like 7. Then,
       set the number of threshold writes W to (n + 1) / 2 = 4.
     - first, send write operations to all 7 nodes. If you get a success from at least 4,
       consider it a success
     - now if you READ from any 4 nodes (Read R should be same as W), you are
       guaranteed that at least 1 node will have the most updated writes. Use
       that to read-repair the other nodes that missed writes. repair as you read
     - this quorum is not consistent because if the client does NOT receive success
       in situations where W - 1 nodes successfully wrote, those writes are still
       existing and need to be rolled back eventually
     - write conflicts still exist if two write calls reach a node in different ordering.
       must have some kind of conflict resolution
   - pros and cons
     - PROS like multi-leader, this is only viable in a multi data center, multi region setup
     - CONS still need conflict resolution, not consistent, slow reads when using read-repair

#### Federation / Functional Partitioning

- When each node has a part of the row data
- ex Audio
  - one db holds metadata
  - one db holds url to s3 bucket
- this is generally easy when the data allows you to do it

#### Partitioning (horizontal scaling)

- each database still has whole rows, but not all of the records
- generally, much harder to do on an RDBMS. Often used in document stores
- often used in conjunction with replication as one node can be Leader of partition 1 and Follower of partitions 2 and 3
- 2 Main ways

  1. Using a range of keys per machine (lastname a-g, g-m etc..)
     - PRO
       - easy to do range queries
       - easy to know which node holds the key
     - CONS
       - will have skews, or hot spots (busy nodes) and may defeat the purpose of
         paritioning
  2. Using a hash of keys `hash partitioning`. The hashing algo can be easy
     like `md5`, which is used in `mongoDB` and `Cassandra`
     - PROS
       - balanced load
     - CONS
       - need to query every machine for range queries as keys are not ordered
       - adds additional logic.

- secondary indexing

  - when you shard a db, you need to have a secondary index (a subset of
    the primary index) to do queries
  - secondary indexing will speed up reads, but the method will determine
    what kind of write penalty you'll incur
    within individual shards, since your primary index is now split up
  - 2 options to secondary index
    1. local
    - only indexes what's available for that shard
    - PROS fast on write as the secondary index is kept on the shard only
    - CONS slow on read because we don't know which partition a query lands on,
      so we need to read from every single partition secondary index to find a match
    2. global
    - all index ranges are held in one partition, regardless of if that data
      is in that shard. For example, "lastNames a - d" is on parition a.
    - PROS fast on read because you already know what partition has that index
      so no need to go through every partition
    - CONS slow on write

- Pros and Cons

  - Pros: avoids failures
  - Cons: Must take into account hot spots (if partitioning by region, are certain regions hot spots?)
    can be hard to determine HOW to shard efficiently
    joins can be expensive over different shards

- different for SQL vs NO-SQL dbs.

- note that sharding is much simpler in noSql because you don't have to worry about joins and dependencies within a table
- dyanamoDb has built in functionalities out of the box

#### Denormalization vs Normalization

- Normalized data (SQL)
  - no duplicated data (optimal space)
  - needs more time to read via joins, but faster writes
  - used mostly in RDBMS
- Denormalized data
  - duplicated (suboptimal space)
  - faster reads, slower writes
  - used mostly in OLAP systems (noSql columnars)

#### SQL tuning

- Indexing popular columns
  - faster reads with penalty to writes as we are adding a new data structure
  - indexing uses extra memory to keep track of a way to handle sorting in
    non-primary keys
  - 2 main types of indexing data structures (aka storage engines)`page-oriented` (like b-tree) and `Log Structured Merge` (LSM)
    - as an exception, `hash maps` can be used to index very small amount of data
      a hash index gets extremely slow if it spills outside RAM and requires disk. often,
      not realistic. Ranged queries also are very slow in a hash index.
  - standard engine for relational dbs is `b-tree`, a specific
    implementation of `page-oriented` engines used by (mySql, postgres) where reads are optimized over writes.
    There is an in-memory Page Cache and a disk B-Tree component. A write-ahead log
    keeps

### ACID in depth

- `Atomocity` the ability to abort the whole transaction if something goes wrong
- `Consistency` is expecting a deterministic result when querying for the same thing
- `Isolation` the hardest to solve. Concurrent requests don't step on each
  others toes. Different levels implemented by different systems
- `Durability` when a node dies, does it have a backup when it comes back

- Generally, the most interesting problem is in `Isolation`

#### Isolation

- the more isolation, the more expensive throughputj

- Two main tiers. Note that these are not set at the DB level, but can usually
  be toggled in the config of a db.
  - Not Serializable (weak isolation, but still counts as isolation in ACID)
    1. No dirty reads or writes
       - does a basic job, but certain states can still cause weird data
    2. Snapshot Isolation
       - better than the above, but worse than total serializability
  - Serializable - queries are done as if they are done in order. concurrent reads and writes
    don't change the behavior and acts as if each operation was done in order - resource intense. trade-off of throughput vs true serializability - uses either `two phase locking` for reads and writes, or `Searializable
Snapshot Isolation`, which is an updated version of the non-serializable
    `snapshot isolation`. Two phase locking is a slightly older tech which is
    more resource intense, but is still used by many dbs

### Consistency (as in Linearizability) in depth

- `consistency` is a bad word in systems design. it can mmean any of the following:

  - consistency in ACID means internal rules within a node or row must apply
    to all
  - in CAP, it means how accurate data is across multiple nodes and if
    a distributed system acts as if it was one node. better word for this is
    `linearizability`

- `Serializability` vs `Linearizability` similar concepts, but different parts of system
  - Serial as in ACID (Isolation) The ability for concurrent transactions
    to not put the system in a bad state.
  - Linear as in CAP (Consistency). The ability for multiple nodes to act
    as if it were one node (data is same between all nodes)
- `Linearizable` system == `Strong Consistency`
  - a truly linearizable system must be using single-leader replication
    without async copying to followers WITH a consensus protocol.
    is slow and is not `available` follower breakage would down system until
    it is repaired and updated) but acts as if it were on one node
  - a consensus protocol (zookeeper, etcd) is a system with controller node that keeps
    track of all node health
  - multi-leader or leaderless (anything with more than 1 writer) is not
    truly linearizable because of write conflicts

#### Systems for consensus (Etcd, zookeeper)

- a consensus protocol is necessary for certain things to function in a distributed
  systems with multiple nodes
- a controller node needs to keep track of multiple nodes
- the main use cases of a consensus protocol include
  1. Membership (are all nodes healthy? which node died?)
  2. Leader Election for failover (which follower has the most recent data that
     needs to be promoted as the new leader)
  3. (Optionally) used in service discovery in gateway services to locate
     IPs of virtual machines which is dynamic. May not need a consensus algo,
     but it's often used since the controller node is aware of all leader nodes
     and can easily locate them

#### GeoHash

- services like Yelp, Uber
- splits the world into squares, then hashes
- each additional append to the hash zooms in on more sub-squares
- usually used via ElasticSearch, but sometimes with Postgres
