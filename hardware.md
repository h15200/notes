# how computer hardware works

## CPU or Micro Processing Unit

- Central Processing Unit asks many billion times a second, "what do you want me to do next"
- 32 or 63 pins
- talks only with the `main memory`
- have historically gotten smaller and more powerful

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
