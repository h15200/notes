# Contenful with Gatsby

Make a new space to fill your own content
Top tab content-model is the “class” like blog post
Content is an instance of the content-model

First test out the wiring by creating some instances on contentful

Gatsby plugin for contentful
`gatsby-source-contentful`

You need spaceID and accessToken
Go to contentful setting, api keys, example, and find the spaceID and Content Delivery Token and paste it into a dev.env file in VS Code

Then in `gatsby-config.js`, add the plugin with the options

11/8/19

    You may get an error in contentful plugin generated fragment.js file. If so, just delete the contents of that entire file and it should be ok.

To read the body of a contentful blog post, npm i `@contentful-rich-text-react-renderer`

To get the body in graphQL, make sure to also fetch the subdivision, json

```
import React from "react"
import { graphql } from "gatsby"
import { documentToReactComponents } from '@contentfulrich-text-react-renderer'

import Layout from "../components/layout"

export const query = graphql`query($slug: String!) { contentfulBlogPost(slug: {eq: $slug}) { title publishedDate(formatString: "MMMM Do, YYYY") body { json } } }`

const Blog = props => (
<Layout>

  <h1>{props.data.contentfulBlogPost.title}</h1>
  <p>{props.data.contentfulBlogPost.publishedDate}</p>
  {documentToReactComponents(props.data.contentfulBlogPost.body.json)}
</Layout>
)

export default Blog

```
