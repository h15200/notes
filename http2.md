# http/2 protocol

A binary protocol, making the framing much easier
Each frame associates with a "stream", which is an independent, bi-directional sequence exchanged between the client and server within an http2 connection.
Each stream has a priority (weight) used to tell the peer which streams to consider most important in case there are resource restrains

https://kinsta.com/learn/what-is-http2/

https://http2-explained.haxx.se/en/part5

## the reason why chrome and firefox will not allow http/2 connections with http (as opposed to https)

SPDY is the google technology that http/2 is built on

```
5.2. http2 for https://
A lot of focus of http2 has been to make it behave properly over TLS. SPDY requires TLS and there's been a strong push for making TLS mandatory for http2, but it didn't get consensus so http2 shipped with TLS as optional. However, two prominent implementers have stated clearly that they will only implement http2 over TLS: the Mozilla Firefox lead and the Google Chrome lead, two of today's leading web browsers.
Reasons for choosing TLS-only include respect for user's privacy and early measurements showing that the new protocols have a higher success rate when done with TLS. This is because of the widespread assumption that anything that goes over port 80 is HTTP 1.1, which makes some middle-boxes interfere with or destroy traffic when any other protocols are used on that port.
The subject of mandatory TLS has caused much hand-wringing and agitated voices in mailing lists and meetings – is it good or is it evil? It is a highly controversial topic – be aware of this when you throw this question in the face of an HTTPbis participant!
Similarly, there's been a fierce and long-running debate about whether http2 should dictate a list of ciphers that should be mandatory when using TLS, or if it should perhaps blacklist a set, or if it shouldn't require anything at all from the TLS “layer” but leave that to the TLS working group. The spec ended up specifying that TLS should be at least version 1.2 and there are cipher suite restrictions.
```
