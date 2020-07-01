# Frontend

When a user tries to connect to a site and it takes too long, they will bounce, or leave.

You want to keep bounce rate as low as possible by optimizing performance.

## Solutions

1. Combine Files

- Minimize/uglify js and css requests, bundle css and js files (webpack and bundle.js)
- combine images into CSS sprite sheets (send one big sheet of multiple smaller logos, icons)

2. Compress

GZIP, brotli

- performs best on text assets like css, js, html
- all modern browsers support gzip compression and will automatically request it
- your server needs to be configured to enable gzip compression. Middleware like cookieParser
- some CDNs require special care to ensure that GZIP is enabled
- webpack can also use a plugin to use gzip

3. CDN (Content Delivery Network)

instead of one server making responses, there is a network of servers globally to balance the load.

4. Images

- images account for more than 60% of web page data
- learn how and when to use GIF, JPG, PNG, SVG - these are all algorithms that comporess image data
- Use SVGs to lighten the load for icons and non-photographic images
- use CSS or server support to deliver images sized to the screen
- use sprites

5. Videos

2 types STREAMING and PROGRESSIVE

- using streaming whenever possible
- use a CDN or similar service provider

User proper compression (or a service that provides optimization for you)

- adjust resolution, bitrate, format, etc..

5. Loading Content

Prefetching - load it now, apply it later. Occurs when you load content in the background

Lazy loading - only download when needed.

6. Caching

browser caching and server side caching
Browers and servers implement a cache for temporary storage of repeadly used data.

Control

Freshness - allows a cached item to be used without rechecking it on the origin server
Validation - is used to check whether a cached item is still good after it becomes stale
Invalidation - side effect of another request that passes through the cache.

## Cross Browser Compatibility

Each browser uses its own rendering engine to convert HTML, css, and js
use Polyfills to support bad browsers like IE
