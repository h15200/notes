## Session

- refers to a way of maintaining user's interactions with a website, often
  in the context of authorization

## Cookies

- Cookies are stored on the browser.
- A small string (4 kb) stored in the browser.
- A cookie is defined on a DOMIAN. Each subdomain gets a separate directory
- session info and tokens are often stored in cookies

## Domain

- Each domain has its own `cookie storage`
- Browser can store 50 cookies per domain
- Browsers can store at least 3000 cookies total.
- technically, it is possible to split up a domain cookie into parts like
  domainCookieOne and domainCookieTwo, but is not good security practice

## cookie workflow

- First, the user sends a POST request to log in with some info on the request body
- Server checks the credentials, either:
  - The server sends a 'Set-Cookie' header in an HTTP response. The cookie has a name and a value.
  - If no good, send error back

```
HTTP/1. 0 200 OK
Set-Cookie: lu=234lkjsdflijadlkfj; Expires=Wed, 25 May 2020 12:15:30 GMT;
```

- multiple cookies are serialized as semicolon separated key-value pairs

- Cookies have built-in info like

  - Path
  - Max-Age
  - Expires
  - Secure
  - HttpOnly

- Once set, cookies are sent automatically inside the request header
- Once the Set-Cookie is sent to the user, it is now automatically sent with every HTTP request from the client to the (same) server.
  If authenticated, the user sends GET request to /profile

- Server checks the cookie, and either shows the user the restricted material OR redirect to log in.

## Cookie session id ssid

Used to add a buffer between something like 'user-id 1' to a hashed string
The server looks up a sessions table to find a match.
Coookies are sent using ssid, not raw data for security reasons

## Setup

If express, you need `const cookieParser = require('cookie-parser')`
and `app.use(cookieParser());`

To respond with a Set cookie,

`res.cookie('nameOfCookie', valueOfCookie, optionsObject)`
options object might look like

```
  {
maxAge: 360000,
httpOnly: true
}
```

res.cookie does NOT end the response cycle

## Cookie Obfuscation

Anybody can copy cookie session through the dev tools application cookies tab.

Since cookies can be accessed from anyone, it's best practice to make your cookies cryptographically secure, or at the very least with payloads that are hard to guess. It is best practice to OBFUSCATE cookies (make unclear).

Cookie names and values should be unclear on purpose

## Cookies can be set to persistent

Cookies can persist data through closing browsers if set that way

## Security

- Cross-Site Scripting (XSS)
- A hacker can inject a harmful `script` tag and manipulate javascript.
- You can easily access cookies by `document.cookie` if you DO NOT have httpOnly: true in the cookie setter.
- ALWAYS add httpOnly: true in the initial Set Cookie in the server for data that JS does not need.

## localStorage

- An alternative to cookies.
- Arbitrary key-value store for the browser (a mini-database)
- Can only use strings for both the key and value.
- Each domain has its own storage
- 5 MB available as opposed to 4KB for cookies

- Must be created, expired, and sent manually.
- Local storage will last forever unless you remove it.

- Can be used to hold state in a non-SPA that doesn't need to be sent to the server.

## Coookies vs localStorage

- If you don't need the info inside the server or the database and it's only used in the front end, better to use localStorage.
- If the server or the database needs the info, better to use cookies as the req.body will automatically send cookies back.

## Never store passwords as cleartext

- Cleartext or plaintext means not encrypted (humanly readable)
- Ciphertext is encrypted

- ALWAYS store passwords as ciphertext.

- Standard practice is to encrypt passwords stored in your database.

## Known hashing algorithms

MD-5
SHA-1
SHA-2
etc..

One can perform a dictionary attack utilizing a lookup table as follows:

1. Make a list of common dictionary words or common passwords
2. Make a lookup table thata precomputes hashes from all standard hashing algorithms
3. Go through the lookup table one-by-one, query the database for each hash.

IF a hacker figures out what the hashing algorithm was, he has access to the entire database.

## bcrypt

`npm i bcryptjs`

Bcrypt is a library that uses a one-way hashing algorithm with a salt.

typically bcrypt.genSalt is used, which takes in 2 args - a number of saltRounds and callback with an error and the salt. Take the async of that, then use the salt to use bcrypt.hash, which takes in 3 args - the cleartext password, salt, and callback

```
bcrypt.genSalt(saltRounds, (err, salt) => {
  bcrypt.hash(myPlaintextPassword, salt, (err, cipherText) => {
    // store cipherText in db
  })
})
```

Can be shortened to just bcrypt.hash with the plainText, saltRound, and a callback

```
bcrypt.hash('password', 10, (err, hash) => {
  // do stuff with hash if no err
})
```

## JWT

- tldr; Useful since it doesn't take server memory, but hard to revoke access
  since it's completely stateless. Not ideal to handle main sessions, but can
  be used for subcomponent access
- JSON Web Tokens
  - open standard that defines a compact and self-contained way for transmitting information between parties as a JSON object
- Sending a JWT within a request allows us to verify that a user is looged in WITHOUT having to look at a cookie sessions table.

- JWT's have 2 important parts. the PAYLOAD and the SIGNATURE

- The payload is usually user information stored as JSON object

- We can send a JWT as a cookie or as a token within the Authorization header.
- BEST practice is to send within the Authorization header.

- JWTs are used to send more sensitive information than cookies, but it still doesn't offer high security like bcrypt. Mostly used for quickly obtaining information about a looged-in user without going to the database

## OAuth

Auth stands for both Authentication and Authorization

Currently OAuth (2.0) is an authentication standard where we use a third-party site (Google/Facebook/Github, etc..) to authenticate.

The user provides teh user / pass to the third party site to log in

The first-party site doesn't ever get the user's username and password. The user gets an authorization code from the third party and the first party site simply checks the legitimacy of the authorization code.

If Auth checks out, the third party will send a token so the user has access within the scope of that request.

In terms of code,

1. set up Oauth through a 3rd party. Have a click trigger a GET request to the OAuth
2. User grants access, puts in authorization pass
3. Server will automatically get a request with the code in query string. Server checks that code against 3rd party
4. If good, server sends back a token to the User which grants access.
