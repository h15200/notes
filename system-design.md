# System(s) Design

Big picture ideas with no code.
Frequent interview questions, but no clear, ONE answer.

Can be broken down to 3 main categories.

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
- what network bandwidth usage are we expecting? Crucial in deciding how would we manage traffic and balance load between servers

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

If there are only 2 microservices, it's a sign you should just use a monlithic structure.

### Proxies

- Forward (default) proxies sit between the client and server on behalf of the CLIENT. It can be used as a cache, add/remove headers. It masks the client IP to the server. Most notable example is a VPN (Virtual Private Network).

- Reverse proxy also sits in the SAME place as a forward proxy, in between the client and server but on behalf of the SERVER. It can log, cache, load balance or do anything as an additional step before the original client request reaches the server.

ex- Nginx

### Load balancers

Hardware vs Software
Hardware load balancers are actual structures.
Software load balancers are USUALLY what systems design interviews are refering to. Software is more flexible in what you can do.

- is a type of reverse proxy (most of the time) as a reverse proxy sits in between the client and server on behalf of the server.
- can be set for the database, or even on the dns layer (google.com has many IPs and the DNS roundrobin will assign a requeset to the correct dns server to respond with a domain name)
- helps scale horizontally by distributing requests to multiple servers
- avoids duplicate requests

Load Balancers can use different algos to choose a server.

#### Server-Selection Strategy with load balancers

1. random
2. round robin (cycles through all servers in order). more ven than random
3. weighted round robin - certain servers have weight (priority) based on power of individual servers or past performance and are given more requests.
4. Ip based asssignment - Client request ip address will be hashed and used to assign to an index number of server. Each individual client is always sent to the same server to maximize cache functionality.
5. Path based - requests are distributed based on the path of the request. Each server specializes in specific functionality. Speeds up deployment as you only need to re-write code for 1 server type.

Random, round robin, and weighted round robin will not work with server side in-memory caching because it won't maximize cache hits as the requests will come from random clients.

Multiple load balancers can have different strategies in a singular system.

clients => path based LB => weighted RR LB x 2 => servers

### Hashing

Hashing becomes VERY important if your system uses any kind of in-memory server side caching because your client needs to request to the SAME server every time to avoid cache misses.

Anything that makes in data, and returns an integer that points to an index of a sample size. IP address, username, any data can be hashed.

2 main hashing algos in systems design

Consistent Hashing (often used by Load balancers) and Rendezvous Hashing (highest random weight hashing)

#### Consistent hashing in load balancers

Traditionally, when scaling horizontally, it might look like

name fetches
server 1 does a - n
server 2 does n - z

when adding server 3, it goes a third, a third a third

`fault tolerance` - how to protect against a crashed server or machine
`allocation` - the way a request is mapped to a server.

Consistent hashing allows a load balancer to allocate the request that protects against fault tolerance AND scalibility based on efficiency of existing cache. In minimizes the number of keys that need to be remapped when a hash table gets resized.

Consistent hashing is used to preserve the most common users (that are already cached) so instead of going 0 - 33%, 33 - 66, 66-100 in the new model, you slice the LAST percentage of each existing server and assign them to the new ones to scale efficiently so that requests in 0 - 24% range will still be routed to the same server.

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

Hybrid solution: use write-throughs for sensitive information. Use write-back for non-critical data.

ex challenge "we've got a distributed system and we want to manage request calls"
solution:

### Message Queue / Brokers

a COMBINATION of services that include having a NOTIFIER that keeps track of which servers are healthy (heartbeat sent to notifier)

The notifier also has access to a db that keeps a queue of asynchronous tasks

queues are used to effectively manage requests in a large-scale distributed system to allow us to decouple our processes and distribute/throttle processing load.

The notifier also acts as a load balancer to distribute requests.

ALL OF THESE services are handled by a message queue.

#### Methods of storing message queue

if it's stored in memory, a server outage will not keep that info

solution: store the queue in a database, each server sends a NOTIFIER a heartbeat every 10 seconds. If a server dies, the notifier consults the db and reroutes unfinished tasks to another server.

### Databases

Reasons for:
Relational - ACID complicance. data is structured and unchanging
Non-Relational - large volumes of data that require little to no structure, makes the most of cloud computing and storage for horizontal scaling

Techniques

#### Optimizing queries

#### Indexing

background - a sorted record can be searched with binary log2 N time, but an unsorted one will require linear time.

Indexing will create another data structure which holds the field value and a pointer to the record, allowing binary searches to be performed.

Doewside is that these index structures will require more disk space, so you are sacrificing space for time.

#### Sharding - Data partitioning over multiple databases

Break up a big db into many smaller parts.

Horizontal partitioning separates rows (users a-j, j-z)

Vertical partitioning separates columns (categories)

- avoids failures
  CONS
- can be tricky to determine HOW to shard efficiently without slowing down queries.
- joins can be expensive over different shards

#### Redundancy and Replication - remove single points of failure by having replicas or backups of a db or server.
