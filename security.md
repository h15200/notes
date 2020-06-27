# Security

## look for vulnerablilities in:

- request body
- request headers
- query strings
- route parameters
- 3rd party API responses (external services)

## Mass Assignment

An active record pattern is abused to modify data that should be private
If you set your req.body directly into a db.save, the user could just GUESS `isAdmin: true` and send it as a request.

AllowList and BlockList - fields that can be mass assigned vs not mass assigned.

BlockList example
create function now has a `delete req.body.isAdmin;` before creating user JUST IN CASE.

AllowList example
create function such that you manually take req.body.username, req.body.password ONLY from the front end.

AllowListing is better. More explicit, doubly enforced data selection

## Direct Object Reference

Indentifier is exposed to users

```
GET api.com/messages/13
DELETE api.com/messages/13
```

User id is not obfuscated

The user can now guess and try requests with id 14, 15, 16.

## Cookie poisoning

Modification/forgery of a cookie by an attacker to gain info about the user for IDENTITY THEFT.

Common way - Cross-Site-Scripting (see below)

## User Enumeration

Revealing who owns an account by exposing too much info in feedback and errors

- probing for a valid user
- analyzing error codes
- analyzing URLs and redirections
- Analyzing web page titles
- Friendly 404 error messages

## Types of attacks

### XSS (Cross-Site Scripting)

Emebed malicious code into a website that steals info, cookies, used for auth. Often js injection

Sub-categories

1. Reflected XSS - Pushing js script in by uri address queries
2. Persisted (stored) XSS - Not sent via a link but from a database or other infected data store.

Prevention - HTML entities should replace all special characters (&quot, &gt);

### SQL injection

Similar to cross-site-scripting but with SQL queries.
Scrub inputs - escape characters that have special maeaning, pattern-check/validate input to see if it conforms to a valid representation
Use an ORM, which scrubs for you

### CSRF (CORS)

Request Forgery - make a request from a malicious site that looks the same as a legitimate request from a user
Attacker may trick the user of a web app into executing action

same-origin-policy only allows javascript code from making requests against a different origin (domain) than the one from which it was served.

CORS is a technique for relaxing the same-origin policy to allow js to consume a REST API served from a different origin. Usually ONLY recommended for dev mode.

Express and other frameworks disallow CORS by default. Requests from other domains are rejected.

CSRF Tokens can be inserted into DOM that is validated on the server.

### Dos

Denial of Service

A user's website is shutdown for a ransom.

Types

Denial-of-service-attack (DoS)
make a machine or network resource unavailble to its users

Distributed denial-of-service (DDoS)
thousands or unique IP addresses are attacked

Requests are overloaded to make the server fail.

Prevention - limit on number of requests per timeframe.
Load balancing, scaling
