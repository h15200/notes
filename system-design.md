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

- the previous was called "service oriented architecture" where multiple
  services existed, but were coupled with shared resources
- Monolithic one or a group of machines (servers) handle ALL services.
- Server Orientated Architecture. precursor to microservices where different
  servers shared some data
- Microservice is a single business unit where each service is a self contained
  set of logic

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

## web server vs application server

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

### Message Queue / Brokers

- an offline system which allows for asyncronous work
- partition tolerant as it usually has replicas and some consensus algorithm
  system. for example, `RabbitMQ` uses `Zookeeper` nodes to ensure data is intact
- a message queue is used by a service to just say "ok we got the request, but we won't try to do it now and will instead put it on a todo list". This ensures that the server doesn't get overloaded and the requests are never lost, for the price of delayed processing
- The notifier is the `producer` and the services doing the actual work is `consumer`. The consumer takes a task from the queue and works on it when it's ready.
- a COMBINATION of services that include having a NOTIFIER (producer) that keeps track of which servers (consumers) are healthy (heartbeat sent to notifier). You can have a message queue with one consumer, or multiple consumers but there is only one producer.
- The notifier (or producer) also has access to a db that keeps a queue of asynchronous tasks to persist tasks. Once it's in a queue, that message or task won't be lost
- very similar to load balancing (with health server heartbeat checks on all services (consumers) that are doing the "work") but the main difference being message queues are ASYNCHRONOUS for time consuming tasks and load balancing is SYNCHRONOUS
- the consumer and producer can be in the same service where the work is being handled, or separate where multiple other services have access
- a variety of ways that this can be handled. For example, you can just tell the client "ok we did it!" while in reality it's happening a little after
- queues are used to effectively manage requests in a large-scale distributed system to allow us to decouple our processes and distribute/throttle processing load.
- The notifier also acts as a load balancer to distribute requests.
- ex. `RabbitMQ`, `kafka` (although Kafka is more `streaming`, which is a hybrid online/offline system with more features)

#### Methods of storing message queue

- if it's stored in memory, a server outage will not keep that info

- solution: store the queue in a database, each server sends a NOTIFIER a heartbeat every 10 seconds. If a server dies, the notifier consults the db and reroutes unfinished tasks to another server.
  - most message queue solutions have fault tolerance by storing the queue in a db

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
- `serializability` is another term to describe the ACID properties. each read/write
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

#### Parquet file format

- Apache Parquet is a column oriented data file FORMAT.
- used for OLAP and has highly efficient data compression / decompression
- supports complex data types

#### Types of nosql dbs

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
- Most popular search engines include Elastic Search and Solr (based on Apache Lucene
  ) as well as Apache Splunk
- Lucene uses LSM + SS table and strings are tokenized. Also possible to
  search for numbers and geolocations. Lucene engine is open source and
  is for single nodes.
- ElasticSearch is a service that takes the lucene engine over a distributed
  cluster

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
- two ways

  1. leader-follower replication (single leader)

  - the majority of db replication is leader-follower, especially if you only
    have 1 data center. multi-leader should only be used in special circumstances
    in multi-data center systems
  - leader usually keeps a `row based log` that describes each row, and
    the follower reads from it. `CDC` is generally done this way as well
    The old way was to use the write-ahead log which contained low level byte
    block data, but that does not work in different db engines
  - usually there is 1 `synchronous` follower as a backup for fallback, but
    the other followers are updated `asynchronously`
  - provides partition toerance, load management, as well as latency (can serve at edge)
  - if requirement is strongly consistent, the write happens only if all
    writes to follwers are complete. Realistically, this is not worth it
    for data centers that are far away because the round trips are too laggy.
    For that, the compromise is eventually consistency and higher throughput
  - PRO easy to implement compared to multi-leader
  - CON the more followers there are, the more latent it becomes
  - CON you need logic (consensus algo) to promote a follower as a leader (Raft , Pax)

  2. multi-leader replication

- the exception to the rule, often when you have multiple data centers
- also, if you absolutely need to optimize for writes
- each data center can have 1 leader and followers
- when one data center goes down, the others can continue operating
- data needs to be synced and merged when multiple writes need to be resolved
- ex. google calendar is essentially multi-leader as all of your devices
  are leaders with write access. When you don't have internet access,
  it is partitioned but the write will happen when you're back online (consistency
  over availability)
- will need additional load balancing logic for writes
- all replicas can write and read and sync with each other
- conflict resolution strategies:
  - avoid write conflicts by assigning dbs to regions
  - last write wins. Cassandra (easy to implement, but issues. offline writes? lost writes)
  - on-read. store conflicting values and make the client resolve on-read
  - on-write. merge writes when there is a conflict on the 2nd write
- how to detect concurrency
  - need to use version vectors to detect missing versions
- PROS:
  - fast writes as throughput is more than 1 node like in single node
  - allows for multi-region, global service
- CONS:
  - write conflicts from multiple leaders

3. Leader-less replication

- send write/reads to all nodes in parallel
- when a certain number of nodes respond with success, the client is told it's a success
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

#### Federation / Partitioning

- also called `functional partitioning`
- instead of using one huge db, smaller dbs are in charge of a piece of the whole data
- eg a separate db per topic. Different from sharding where each db still has
  a subset of the entire data
- example might be separating audio into the actual audio (to some blob storage like s3)
  and metadata (a document storage db)
- Multiple nodes are used for partitions. Each partition has its own follower and
  usually some read replicas.
  - one node can be Leader of partition 1 and Follower of partitions 2 and 3
  - `hash partitioning` or consistent hashing where the key is hashes of data is used to evenly
    distribute load so there are no skews / hot spots
    - this still doesn't have for ex. if the same hashed key is used to read/write
      like in celebrity instagrams. For that, have some logic like if followers
      exceed a certain point, add 2 random strings to the hash so that reads
      and writes on the celebrity are partitioned and not concentrated in 1 partition
  - mongo and cassandra uses `md5`, not an especially strong cryptographic hash
    algo since it's just used to search for keys
- CONS adds additional logic, data is not as organized, hard to figure out where
  to get the appropritate data, may not work with certain business logic

#### Partitioning (horizontal scaling) Data partitioning over multiple databases

- each database still has the whole data, but only a subset of it
  - eg for all users, one db will be in charge of lastName A-D, then E-H etc..

`Partitioning` or `sharding` will decrease latency, increase throughput and can be done in 2 ways:

- Horizontal partitioning separates (users a-j, j-z) into smaller shards (or partitions) of the same columns

  - can be done in RDBMS and no-SQL, but much easier with noSQL
    - 2 methods of horizontal partitioning:
    1. Range of keys
    - ex. "A-D" in last names goes to one shard, then "E-K"
    - PROS easy to implement
    - CONS could have uneven data, can have hot spots
    2. By Range of Hash of keys
    - hash a last name, then take a range of those hashes
    - PROS even data
    - CONS can't do range queries since lastnames are now random, still can
      have hot spots

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

- Vertical partitioning separates columns (categories) into shards (or partitions) for ex when a column is rarely used, it is stored elsewhere.

  - don't confuse vertical partitioning with vertical scaling. Both horizontal and vertical partitioning is a form of horizontal
    scaline since it requires multiple machines rather than upgrading one machine

- when sharding, just like in servers and load balancers, must take into account hot spots and aim for an even distribution by using a good hashing function that guarantees uniformity.
- consistent hashing strategy is necessary to keep cache misses to a minimum when
  instances go down

- Pros and Cons

  - Pros: avoids failures
  - Cons: Must take into account hot spots (if partitioning by region, are certain regions hot spots?)
    can be hard to determine HOW to shard efficiently
    joins can be expensive over different shards

- different for SQL vs NO-SQL dbs.

- note that sharding is much simpler in noSql because you don't have to worry about joins and dependencies within a table
- dyanamoDb has built in functionalities out of the box

#### Denormalization vs Normalization

- Normalized data
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
  - 2 main types of indexing data structures `b-tree` and `Log Structured Merge` (LSM)
    - as an exception, `hash maps` can be used to index very small amount of data
      a hash index gets extremely slow if it spills outside RAM and requires disk. often,
      not realistic. Ranged queries also are very slow in a hash index.
  - standard is `b-tree` (mySql, postgres) where reads are optimized over writes.
    There is an in-memory Page Cache and a disk B-Tree component. A write-ahead log
    keeps track of all operations and writes to disk
    and good for sorting data (useful in structured data)
  - `LSM` has faster writes since it only writes to a buffer and scales better but bad at sorting
    (most Nosql dbs use LSM)
- using optimized SQL commands

### Leader Election

- the same idea of threads and locks but in a distributed system
- used when only 1 of the replicated nodes should be responsible fo something

  - for example if you have a subscription service like Netflix, when using a 3rd party service like paypal to process payments, you don't want that 3rd party service to have direct access to your UsersDb.

  - another example is replicated dbs. Only the main active one should be in charge of writing so data is consistent

- Usually there is a service that sits between your db and the 3rd party service that has access to your db and checks the status of `payments` or something, and communicates with the payment service. When you have important logic like payment, you want passive redundancies of this middle service so that only one "leader" takes care of the logic and the others are on standby.

- The logic of multiple machines agreeing on a leader can be very complicated. The act of sharing this state of knowing who the leader is done with a `consensus algorithm`, specifically like `Paxos` & `Raft`

- example of apps that use a consensus algo under the hood - `zookeeper`, `Etcd` (EtsyDee) are both strongly consistent and highly available key-value storage that's often used to implement leader election

#### Apache Zookeeper (leader follower model) in detail

- basically a namespace with a bunch of nodes that it keeps track of
- used in db read-replication as well as message queues (rabbitMQ) and Kafka
- when you have replication, you need consensus.
- also used for service discovery
- In a zookeeper service, the same set of data is held in multiple machines
- one machine is the leader.
- clients connect to any instance of those nodes to get data
- reads can be done from any node, leader or follower
- writes must go through leader
- uses distributed locks, so read consistency is guaranteed

### Consistency, Availability, CAP Theorem

- availability is measured by `9s`. Five 9s means there are outages of seconds over a year
- in reality, most major cloud vendors promise `99.95%`, which is about 20 minutes of down time a month
- Strong Consistency (aka `Linearizability`) means data is rarely stale. Eventual consistency means the data will sync over a period of time (seconds or minutes) when the network traffic is low.
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
  - strong consistency (linearizability)
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
- this can be thwarted by Rate Limiting which returns an error code `429` "Too many requests" on a request based on parameters like ip address / user, number of requests per minute, region. There are 2 main implementations

  - token bucket system where each unique IP address may have x tokens that
    gets used per request. At a certain time interval, tokens fill back up.
    When tokens run out, error 429
  - sliding window system where each unique IP address has n requests available
    per time window. It refreshes after 1-n seconds

- DDoS (DISTRIBUTED DoS) attacks are done from multiple client sources, and is harder to prevent with a simple rate limiting on ip address / user. In a distributed system, the rate limiting will need to be checked against another entity that connects to ALL replicas of the server like a redis server
- Implementation can be done with a key-value in memory store like `redis`. The server gets a request, then asks redis "hey are we doing ok with rate limiting?" before responding

## Online vs Offline systems

- Online systems or `services` wait for a request and try to handle them quickly.
  - low latency and availability is prioritized
  - ex. web servers, dbs, caches
- Offline systems or `batch processing` systems process lots of data
  - high throughput is prioritized
  - `mapReduce` is a classic example of an offline system. Was the original method
  - `spark` uses DataFlow Engines which is an upgrade to mapReduce. This is
    currently the popular implementations of batch processing
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

- MapReduce algos have fault tolerance by using Idempotent Operations in both the Map and Reduce steps to shield against outages
- common tasks including sorting, word count, grep
- for every mapReduce task, you already know the volume of data you're working with since it's an `offline` system. There
  are no uncertainties like users making requests from a UI. You don't have to add a server for a spike or worry
  about consistent hashing!
  - the predecessor to `Dataflow Engines` like apache `Spark` and `Flink`

### Dataflow Engine

- another type of batch processing
- examples of Dataflow Engines include `Spark` and `Flink`
- improvement to map reduce

- what's the issue with mapReduce?

  - inefficient for jobs that require many mapReduce calls/iterations (page rank)
  - tons of disk I/O due to materializing intermediate state to HDFS (Hadoop Distributed File System)

- uses `Resilient Distributed Datasets` where in memory data structure is used
- majority of data is kept in memory and is faster than mapReduce
- comes at a cost of using more RAM
- one more possible compromise is that it has slightly worse fault tolerance than
  MapReduce as it does not keep all intermediary state, but the general
  increase in performance is often worth these tradeoffs. As a result,
  mapReduce is no longer used for large scale computation in modern tech stacks

#### Flink

- in addition to being a batch processor like `Spark`, it also has stream
  processing capabilities
- stream processing is a hybrid `online` and `offline` system
- flink itself is not a message broker but runs on them as consumers on a cluster
  of message queues like Kafka
- each flink instance has its own kv store to persist stateful changes
- deals with fault tolerance by periodically replicating in-node local data to durable
  storage such as S3 or HDFS

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
- if the data is small (5 pictures for a dating site), then you have the choice
  of storing in a Distributed File System (pics are saved to machines directly)
  where the pros are faster, cheaper, easier to implement. Cons are not secure or consistent
- a blob store like S3 is NOT ACID compliant, but it's more secure and persistent
  and can store bigger data.
- If the static data is large (songs, videos) or is sensitive, then a blob store is probably better
- Both distributed file systems and blob storage will be governed by a service
  that has its own table with userId, imageId, and a reference to the DFS/blob table with an image URL.
- auth / gateway service
- in most systems with a user that requires a profile via email/password, always
  make the point to send that info as a hashed token (instead of the password itself)
  and that the client will always connect to gateway service that takes care of auth.
  If authenticated, the gateway will then forward the request to the correct
  microservice. Then it will also forward the response back to the client.

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

### newSql (sql backed, but with a twist) `Google Spanner`, `aws aurora`, `voltDB`

- Google Spanner uses `TrueTime` to sync their clocks, which solves the issue of
  having logical clocks (version vectors, etc.. that takes up time)
- provides ACID transactions (is relational), linearizability (strong consistency)
  where replicas are consistent. Best of both sql and nosql while maintaining
  good performance
- 2 phase locking does not require locks on reading. how?
- since they have trueTime, they use a reliable timestamp to order operations and
  only read from a lower timestamp (a completed transaction)
- TrueTime computes a min and max time for operations and returns a very
  good prediction
- to use TrueTime, it must synchronize in google data centers, so it can't
  be used in other dbs.

- `aurora` is another newSql db which claims a 35x boost to performance compared
  to traditional sql cloud solutions (memory page cache + b-tree disk).
- Aurora decouples the cache and disk on two different servers and they are
  both replicated/scaled independently.
- allows for multiple region

- `VoltDB`
- traditionally, sql db use two phase locking to implement transaction
  serializability
- VoltDB uses single threaded execution and data is stored in-memory instead on disk
- ideally, you want to use one partition, but the fact that it's only in-memory
  usually means you need sharding for large data. Generally, not a good idea
  if your data is large
- removing locks allows for much higher performance

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

## classic examples

- chat app

  - remember that group chat is just the service messaging each individual.
  - usually a TLS bidirectional protocol like websockets

- design a collaborative editing text platform (google docs)

  - high level: all clients with authz has write permission, and will perform
    both read/writes. Write conflict resolution is crucial
  - `commutative` is an algebraic property that means ordering doesn't matter
  - ex. adding something to a set, or incrementing a counter is commutative
  - low level problem: Array writes (which represent strings) are not `commutative`

  ```
  'car'

  user 1 adds 's' to index 3 -> 'cars'
  user 2 adds 'big ' to index 0 -> 'big car'

  if user 1 changes take effect before user 2, 'big cars'
      but if not, 'bigscar' (because index 3 is on the whitespace)

  depending on ordering, the final string is different!

  we can get either 'hellooo'
  ```

  - solution 1 `Operational Transform`
    - a function that converts ordered operations into a proper array
      such that each local copy converges in the way it's supposed to
    - Operational Transform requires total ordering, meaning it must use
      a singler leader write algorithm or a consensus algorithm to determine
      which writes came first, slowing down the process. This is used by
      google docs
  - solution 2 `Conflict Free Replicated Data Types`, (CRDT)
    - data structure that each write/read replica can hold locally that
      holds state of historical changes that all converge to the same value.
    - removes the need for write bottlenecks
    - typically, CRDTs work well with commutative operations, but it can also
      be modified to work with arrays (text) by using sets and splitting insertion
      indices
  - both solutions are very complicated to implement

- design twitter news feed

  - celebrities vs non-celebrities have opposite solutions
  - normal people should send all changes to a user cache which propagates
    the news feed before the user is on the page
  - with celebrities, it's better if that info is pulled from the db cache
    each time a user visits the news feed

- design dropbox
  - when data exceeds a reasonable mount (in the PBs), use somebody else's
    solution like s3 which scales infinitely
  - storage in chunks so that each file change doesn't require entire file
    uploads to s3

## deep dive

### cassandra vs Hbase

- similarities

  - Both are wide column, meaning it's good for analytics and column based reads
  - both are noSql using LSM as indexing method, so relatively fast writes
    compared to sql b-trees
  - both scale relatively well because sharding is easier without joins
  - both have eventual consistency

- Differences

  - HBase uses a distributed file system to implement (hadoop). It also
    has a single leader replication strategy while Cassandra has multi leader
  - Cassandra writes are faster since multi leader, but for conflict resolution
    they use a simple last-write-wins, which is not reliable because of timestamps
  - HBase single leader means more throughput on writes, but consistent
  - Cassandra is better for customer facing apps that require fast writes, but
    Hbase is better for Data Lakes since it has faster reads and batch job
    processing (mapReduce, or Data Flow engline like Spark)

### cassandra vs riak

- cassandra is a wide-column and riak is key-value, but similar in that
  they both use multi-leader replication and writes
- Riak uses CRDT (conflict-free replication data types) to resolve conflicts,
  which are similar to version vectors. Cassandra uses a simple last-write-wins.
  Riak is more reliable since it's not dependent on faulty server timestamps,
  but it doesn't do well with analytics since it's just a key-value store

## mongoDB

- noSql document store, but capable of transactions. Sort of in-between two
  worlds. Uses b-tree despite it being a noSql, allowing for slower writes but
  fast reads.
- Easy to use for fast mvps
- uses denormalized data, so again, fast reads but slow writes

## Riak vs Redis vs Memcached

- Riak is a key-value store on disk. Not in-memory
  - uses multi/no leader replication with conflict resolution so writes are
    a bit slow but consistent
- Memcached is a very simple in memory key-value store which does not have any
  replication measures or failure handling. It does have paritions with consistent
  hash ring, but there are no handling of faults.
- Redis builds on top of basic features in Memcached.
  - has two modes. (Single Node) and (Cluster)
  - In single mode, has transactions and range queries
  - In cluster mode uses single leader replication with automatic failover.
    if the write node fails, another will be chosen via gossip protocol. Note
    that if a leader fails before writing, some writes could fail

### Object (blob) store vs HDFS

- blob stores like S3 scale. you pay for what you need
- object store is faster because there is no concurrency guarantees
- you need a distributed file system if you need to run batch/stream jobs
- if there is no need to run jobs, use object stores over DFSs
- CDN can be put up behind blob stores to distribute file closer to the end user

## Getting info to client from server

1. Long polling
   - use a regular http connection at an interval
   - connect/disconnect every call cost resources
   - easy to implement, more stress on server
   - check the status of provisioning a resource that is async
2. Websockets
   - TCP connection which stays open. can allow for 50k connections at a time
   - less resource intensive on server, but more on client
   - used for chat apps. maybe overkill for infrequent updates
   - chat apps
3. Server sent events
   - Unlike polling, the server uses a persistent HTTP connection and sends
     a unidirectional message to the client
   - newsfeed updates, stock tickers
