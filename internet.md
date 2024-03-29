# How internet works

## When you enter a domain name in a browser

1. browser checks the local cache for DNS record (in memory). if available, fetch that info in memory
2. if not, look in the global database
3. find ip adddress
4. go to ip address via routers

GETTING to a page to find html file by itself is a GET request.
Getting the CSS/js specified in that html file are also GET requests

## Mental models

- the tcp/ip model has 4 layers

  1. Link - method of connection via wire or wireless
  2. InternetWork - the ways to "hop" to the right server
  3. Transport - once the server is reached, means of ack and connecting
  4. Application - the logic of the server

- OSI (Open Systems Interconnection) model thinks of the same thing in 7 layers
  1. Physical - attribute of wired, wireless, fiber optics, other connections
  2. Data Link - logic of how the various physical layer cooperates with each other
  3. Network - like the InternetWork layer of TCP/IP, deals with global assignment of routable addresses
  4. Transport - manages packet loss and reconnection
  5. Session - establishing connections between apps with ports
  6. Presentation - how data is represented and encoded for transmission
  7. Application - the actual applications of transfering data

## terminal commands

### % ns look up domainName

will return the ip address

### traceroute ? ( i think)

will return all the hops to routers that it takes to get to that ip from this ip address

## web scraping

- from the server side, make requests to html, then look specifically for certain anchor tags, then recursively continue

## wire protocol

- since various languages have their own implementation of data structures, the network data needs to be standardized

- 2 common ones are

  1. json (javascript object notation)
  2. xml (extensible markup language)
     - looks like html, but for arbitrary key-value data
     - both `xml` and `html` are based on `sgml` (standard generalized markup language) which has angled brackets, and `attributes` inside
     - XML has various schemas which outline what is valid
     - various entities have made XML schemas. The W3C spec is called `XSD`

- the act of turning language specific structures into a wire protocol is called `serialization`
- when you receive data from a server over the wire, the act of turning that back into what your language can understand is called `de-deserialization`
