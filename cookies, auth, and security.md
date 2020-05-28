# Cookies

Cookies are stored on the browser.
A small string (4 kb) stored in the browser.
A cookie is defined on a DOMIAN.

## Domain

Each domain has its own `cookie storage`
Browser can store 50 cookies per domain
Browsers can store at least 3000 cookies total.

## How to start

The server sends a 'Set-Cookie' header in an HTTP response. The cookie has a name and a value.

The response might look like

```
HTTP/1. 0 200 OK
Set-Cookie: lu=234lkjsdflijadlkfj; Expires=Wed, 25 May 2020 12:15:30 GMT;
```

multiple cookies are serialized as semicolon separated key-value pairs

Cookies have built-in info like
Path
Max-Age
Expires
Secure
HttpOnly

## Once set, cookies are sent automatically inside the request header

Once the Set-Cookie is sent to the user, it is now automatically sent with every HTTP request from the client to the (same) server.

AJAX calls include the cookie

## application to auth

Log in / Profile

First, the user sends a POST request to log in with some info on the request body

- Server checks the credentials, either sends an 200 with a SET-COOKIE or a 401 with denial

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

Cross-Site Scripting (XSS)
A hacker can inject a harmful <script/> tag and manipulate javascript.

You can easily access cookies by `document.cookie` if you DO NOT have httpOnly: true in the cookie setter.

ALWAYS add httpOnly: true in the initial Set Cookie in the server for data that JS does not need.

## localStorage

An alternative to cookies.
Arbitrary key-value store for the browser (a mini-database)
Can only use strings for both the key and value.
Each domain has its own storage
5 MB available as opposed to 4KB for cookies

methods:

localStorage.set(key, value);

## Coookies vs localStorage

If you don't need the info inside the server or the database and it's only used in the front end, better to use localStorage.

If the server or the database needs the info, better to use cookies as the req.body will automatically send cookies back.
