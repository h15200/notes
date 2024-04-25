# Networking

- networking is simply connecting systems so they can talk to each other
- can be thought of as a road to the next system
- determines the best path to get to your destination

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
  - sending `bits`
- Layer 2 Data Link (MAC and LLC Physical addressing) [MAC address, frames]
  - hardware layer. ethernet card has a `MAC address` (Media Access Control Address).
  - modern networking usually defaults to ethernet cards. Sends `frames`
- Layer 3 Network (Path determination and IP) [IP address, packets]
  - logical addressing layer. the `routing` layer
  - determine the address and path to get your data through the network
  - at this point we are sending `packets`
- Layer 4 Transport (End to end connections and reliability) [TCP/UDP/ICMP, Segments]
  - determines the underlying protocol (TCP/UDP/ICMP)
  - sends `segments`
- Layer 5 Session (Interhost Communication) [Sockets, data]
- Layer 6 Presentation (Data representation and encryption) [TLS, Data]
- Layer 7 Application (Application and Network) [http-dns-ssh-data]

## networking protocols

- `TCP/IP` is the main networking protocol. This is an umbrella term for
  protocols that include
  - `TCP` (reliable network transfers)
  - `UDP`(real time transfers)
  - `ICMP` Internet Control Message Protocol (test/diagnose the network by pinging)

## Network Devices

- `router` is a server with a lot of network interfaces

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
