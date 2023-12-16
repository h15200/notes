# Frontend concepts

## Debounce, Throttle, Rate limit

- FE usually prvents ui from repeated action like submitting
  - debounce: if the btn is clicked 10 times a second, only allow the last one as
    each click will reset if the previous click was within n seconds
  - throttle: if the btn is clicked 1o times a second, only allow the first
    and wait n seconds
- BE uses Rate limiting and returns 429 for all reqs that got past the FE
  - token bucket or sliding time window

## cookies, localStorage, sessionStorage

- cookies

  - the oldest method
  - capacity of 4KB
  - is scoped by web domain
  - has expiredAt timestamp
  - persists when the browser is closed
  - can possibly persist for a long time, so not good for sensitive data
  - gets passed to reqs (unique)
  - is not stored in the BE, only the browser

- sessionStorage

  - cap of 5MB
  - is scoped by TAB
  - used to store short term data like login credentials
  - automatically deletes when the browser is closed
  - good for short term data that is more sensitive than the other 2 methods
  - data is not sent to BE

- localStorage

  - latest browser storage feature
  - cap of 10MB
  - scoped by domain
  - stored in browser AND OS
  - persists the longest, so good for preferences and user settings
  - no expiredAt.
  - data is not sent to BE
