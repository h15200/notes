# Networking

- networking is simply connecting systems so they can talk to each other
- can be thought of as a road to the next system
- determines the best path to get to your destination
- in the most basic term, networking is one PC reaching another PC

## Components of networking

- Routers
  - Routing Protocols
- Switches
  - Redundancies
- Cables
- LAN Connections
- WAN Connections

## OSI Model (Open Systems Interconnect Model)

- 7 layers of communication
- `networking` refers to the first four steps of the OSI model

- Layer 1 Physical (media signal and binary transmission) [wire, fiberoptic wires, bits]

  - wiring: cable, fiber optics cable
  - fiber optic cables are used when above 100 meters
  - sending electrical signals over the wire `bits`

- Layer 2 Data Link (MAC and LLC Physical addressing) [MAC address, frames]

  - hardware layer. ethernet card has a `MAC address` (Media Access Control Address).
  - modern networking usually defaults to ethernet cards. bits are turned to `frames`
  - `switch` logic resides here

- Layer 3 Network (Path determination and IP) [IP address, packets]

  - logical addressing layer. the `routing` layer
  - determine the address and path to get your data through the network
  - at this point we are sending `packets`, handled by routers and gateways
  - the logic of checking if router has the path to the subnet where the destination
    is

- Layer 4 Transport (End to end connections and reliability) [TCP/UDP/ICMP, Segments]

  - determines the underlying protocol (TCP/UDP/ICMP)
  - logic of destination port (like TCP/443) and assigning source ports
  - sends `segments`

- Layer 5 Session (Interhost Communication) [Sockets, data]

  - usually the logic of starting TLS sessions between client/host

- Layer 6 Presentation (Data representation and encryption) [TLS, Data]

  - serialization/deserialization of data from bits to a higher level language

- Layer 7 Application (Application and Network) [http-dns-ssh-data]

  - the actual logic in a route handler (server side) or an application typing
    in a url

- in real terms from user to server request:
  layer 7 Application - user enters url
  layer 6 Presentation - app language is serialized to bits
  layer 5 Session - start a TLS session over TCP
  layer 4 Transpot - destination port of TCP/443. assign an ephemeral port as source port
  layer 3 Network - the packet is stamped with the destination address
  layer 2 Data link - if destination IP is not in LAN, the packet is stamped with MAC of default gateway
  layer 1 physical - transit electrical pulses over the wire

  AFTER GETTING TO THE SERVER, go in reverse order to respond

- on the server (PC 2) side

  layer 1 physical - server receive bits
  layer 2 Data link - packet comes in on WAN interface from ISP. destination MAC is correct
  layer 3 Network - destination IP address is stamped with server's address
  layer 4 Transpot - TCP/IP stack receives a SYN packet on TCP/443
  layer 5 Session - initialize a TLS session with client with encrypted data
  layer 6 Presentation - de-serialize bits
  layer 7 Application - app processes the request and responds

## networking protocols

- `TCP/IP` is the main networking protocol. This is an umbrella term for
  protocols that include
  - `TCP` (reliable network transfers)
  - `UDP`(real time transfers)
  - `ICMP` Internet Control Message Protocol (test/diagnose the network by pinging)

## Network Devices

- Layer 2 Data link layer is where we deal with `switches`

  - a `switch` is a layer 2 device that uses frames and Mac addresses
  - a `switch` is where your things are physically plugged into
  - physical load balancers are also plugged into switches
  - switches forward `frames`
  - builds a table of Mac addresses
  - in a cloud setting, there are virtualized servers and `virtualized switches` (aka virtual LANS)
    - you can take a switch and divide its port up into multiple logical virtual switches
      called `virtual LANS`, or `VLANS`

- Layer 3 Network layer is where routing layer is, which is done by `router`

  - `router` is a layer 3 device which is a server with a ton of network interfaces.

  - ex. a computer that has two network cards. each card has a `map`
    of the network and routes the path to get the packet closer to the destination
  - the map is made with a `routing table` and `routing protocol` where each
    router communicates with `links` which `subnets` each router has.
    this entire process is called `dynamic routing`
  - dynamic routing is self healing, where if a link breaks, your packet can still
    each your destination
  - there is also the opposite approach of `static routing` where it says
    which exact router to send the packet
  - the first router from the origin computer is a `gateway`

- `dynamic routing` review (Layer 3 logic):
- find the subnet where the destination IP address is via router linking
- once the packet is in the subnet, broadcast an `ARP` message that says "who
  in this subnet has the MAC address xyz"? The device replies, and a path is made
- same logic happens on the trip back from PC2 to PC1, and that's when you have
  a bidirectional connection

## How network devices determain the path to the destination

- every Layer 3 IP packet has a `header` which contains the source address
  and the destination address
- `Routers` (also in layer 3) look at the destination and they forward it
  to their path
- in Layer 4 the top layer protocol is available (tcp/udp) which also has headers
  with a TTL (time to live) to avoid the packets traversing an infinite loop. -
  - every time a packet traverses a router, the TTL gets decremented by `1`
  - a packet which as a TTL of `10` will be dropped after traversing 10 routers
- the `DS field` tells the network if a certain path needs to be prioritized

## LAN (local area networking) and WAN (wide area networking)

- LANs are plugged into your switches that's local (house, campus, office)
  - switches are plugged into routers in your local area.
  - `availbility zone` would be the campus, house, coffee house, etc..
  - ex. an office building has computers plugged into switches, routers plugged
    into switches, a fiber optic connects to the two buildings
- ## WANs cover a larger distance. NY connecting to LA, cloud network
