tips:

- add `_document.ts` to integrate mui
- getServerSideProps can be used if a page needs to be rendered with data that changes a lot, but for most use cases just use client-side fetching for aiva stuff.
  - specifically, next has an `swr` component that abstracts data fetching on the client side
