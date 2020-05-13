# How internet works

## When you enter a domain name in a browser

1. browser checks the local cache for DNS record (in memory). if available, fetch that info in memory
2. if not, look in the global database
3. find ip adddress
4. go to ip address via routers

GETTING to a page to find html file by itself is a GET request.
Getting the CSS/js specified in that html file are also GET requests

## Terminal

### % ns look up domainName

will return the ip address

### traceroute ? ( i think)

will return all the hops to routers that it takes to get to that ip from this ip address
