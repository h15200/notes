# how computer hardware works

## CPU or Micro Processing Unit

- Central Processing Unit asks many billion times a second, "what do you want me to do next"
- 32 or 63 pins
- talks only with the `main memory`
- have historically gotten smaller and more powerful

### inner cpu calls

- register -> L1,2,3 cache -> RAM
  - as we go up, the calls get slower but allows for more capacity

## order of magnitude for latency

### sub nanosecond

- register calls within the CPU

### 1-10 nanoseconds

- still inside the CPU
- L1 and L2 cache.

### 10 - 100 nanoseconds

- L3 cache within the CPU
- RAM access

### 100 - 1000 nanoseconds

- OS call (uses kernel)

### 1 - 10 microseconds

- context switching between threads (processes)

### 10 - 100 microseconds

- reading 1mb of data sequentially from contiguous memory (array)
- nginx network proxy processing 1 http request (since it does not involve tls handshake)
- to read something very small (8kb) from SSD
  - reading from disk is much faster than writing to disk

### 100 - 1000 microseconds

- writing (10 x slower than read ops) something small to SSD drive
- same zone (zone is a subregion in a modern cloud provider) network round trip
- memcache (redis) read operation INCLUDING the network round trip
  - note that in-memory kv stores reads are much faster than any ssd reads

### 1 - 10 milliseconds

- intra-zone (zone to another zone, still within same region) round trip network call
- seek-time of a HDD (physical arms moving)

### 10 - 100 milliseconds

- roundtrip from 2 close cloud regions (us-west to us-east, or us-east to western-europe)
- reading 1GB sequentially from RAM

### 100 - 1000 milliseconds

- a slow hashing algorithm like Bcrypt
- TLS handshake
- roundtrip two long-distance regions (us west to Singapore)
- reading 1GB sequentially from SSD

### 1 second

- transferring 1GB of data over network within same cloud region

## Main Memory or Random Access Memory

- looks like a long strip
- stores programs
- feeds to CPU to give instructions on what to do next
- the basic cycle of programming is :
  - CPU asks the memory "what do I do?"
  - the memory feeds the CPU with instructions
  - CPU finishes task, then asks "what do I do next?"
  - repeat
- is not persistent. Loses all data when the computer is powered off
- very fast

## Secondary Storage or Hard Drive

- unlike main storage (ram), persists data even when computer is turned off
- slower than main storage
- while the computer is turned off, OS, file systems, and applications live here
- once the computer is running, those are loaded into the main memory on load

## motherboard (for desktops)

- contains all components
- possibly to replace/swap out components like memory, secondary storage, CPU

## caching

- Generally, "Computational Cost" is MEMORY ACCESS COST, which is why caching is important!
- each computer core has its own caching (l1 and l2 cache) that is contained within a core
- Each level of cache adds a significant "cost" in caching. L3 goes outside the core and
  is a shared cache between all available cores
- The next level is the DRAM (main memory), then SSD, then the Network

- caching is effective when we access memory in predictable patterns in SEQUENCE! so
  a block of consecutive memory is more efficient then random pointers. A js array
  or go slice is less expensive than a linked list.
