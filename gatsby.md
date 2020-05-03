Go to github - gatsby-template - master - Click on Clone or Download - Download Zip
Unzip, rename dir from gatsby-template-master to the name of the project
Open with VSC, npm install, go to gitignore and uncomment the bottom files
Run npm start and make sure it works, check css and graphQL playground
Git init, set up NEW repo in github, git checkout -b dev, push to github and follow readme

## SET UP

npm i -g gatsby-cli

gatsby new . https://github.com/gatsbyjs/gatsby-starter-default

Set up eslint - code - setup - eslint - bottom browser version
Check to see it’s working on localhost:8000 after npm start (or npm run develop or gatsby develop). Src-pages-index.js change to rafce, label const as IndexPage (capitalized and Page for convention) and change content to test in browser.
Upgrade to graphql playground: .env
GATSBY_GRAPHQL_IDE=playground
npm i -D env-cmd
package.json - change script “develop” to env-cmd -f .env gatsby develop
Make github repo, connect repo in vscode, follow direction for master, make a dev branch <git checkout -b dev>, commit and push upstream also
npm i prop-types

## FILE/LAYOUT ORGANIZATION

    NO CAPS ON COMPONENTS OR PAGE FILES!!!! Especially “layout.js”. It will break the whole site and localhost will NOT load

Make all pages necessary. Create file in src-pages, rafce each one, name const AboutPage (but about.js) , enter placeholder, check each subdomain on browser
Make a components dir in src, add footer.js and header.js and layout.js
When making header/footer, use <Link> for internal links and <a> for external
Import footer and header into layout.js. Add props and render Header, props.children, Footer. This layout.js will be imported into each page.
When using props, use rafcp, npm i prop-types, import PropTypes from ‘prop-types’ and on the bottom before the export, Layout.propTypes = { children: PropTypes.element.isRequired } // prop must be a react element and must have one

## METADATA

- ANY reusable content should be only written once inside metadata in gatsby.config.js
  Site Title, site author, website address,

## Helmet/Head

Install the gatsby plug in for react helmet, and regular react-helmet
src/components/ make head.js

Import { Helmet } from ‘react-helmet’
Just return <Helmet title={whatever you want the page title to be} /> OR <Head><title>stuff</title></Head>
Then put it in every page by importing and placing on top

To get Home | Hideaki Aomori,

You need to query the site title from the metadata AND use props in individual pages.

So for example in About.js, <Head title=”About”>

Then in Head

const Head = {{ title }} => {

Graphql query for title of site
return <Helmet title={`${title} | ${data.metadata.title}`}

## FAVICON

Use Helmet JUST for the page favicon, but even better to get:

Gatsby-plugin-favicon

And make a logo that is 1500 by 1500px called “favicon.png” and drop it directly in the src folder. https://favicon.io/

## links

When making header/footer, use <Link> for internal links and <a> for external
If using `target="_blank"`, `rel="noopener noreferrer`

## image ASSETS - USE jpeg 2000! Can export with preview on macs

## STYLE - SASS

npm i gatsby-plugin-sass node-sass
Make a styles dir in src - use 7 in 1 architecture! See css setup doc

Go to gatsby-config.js, plugins: [ ‘gatsby-plugin-sass’] // now .scss files can be used
Make a test color variable in index.scss, import it in layout.js and test the connection for GLOBAL styles
Make html for big screen, but start css for small screen
For component specific styles, use css modules
For dropdown menu, you can use opacity 0 and pointer-events none
activeClassName={whatever.class} // for highlighting current <Link>
Use 15px-25 for p text, line spacing of 120-150% em, 45-90 chars per line
JUST put global tag stylings inside layout.module.scss. All pages are under that, then components. Style in that hierarchical order!

## CSS MODULES

Inside footer.module.scss, only use class selectors .nav { color: green }
In footer.js, import footerStyles from ‘./footer.module.scss
Then in the element render, add className ={footerStyles.nav}

- className in css like .nav-page in jsx === .navPage

  CSS MODULES FILE STRUCTZURE

  In main.scss import all files except modules
  In any modules.scss file, import main, then in the corresponding component.js, import the module like footerStyles

## LAYOUT.JS

On main div, add className=”container”
Make another div that contains everything BUT the <Footer /> className=”main”
In index.scss
.container {
display: flex;
flex-direction: column;
min-height: 100vh;
}
.main {
Flex-grow: 1; }

    		404 PAGE

    In src/pages make 404.js
    Make a react component NotFound
    h1 page not found (maybe a red background)
    Then <p><Link to=’/’>Head Home</Link></p>
    Still have a header and footer

## GOOGLE FONTS

DON’T USE helmet

https://www.gatsbyjs.org/packages/gatsby-plugin-prefetch-google-fonts/
And import directly into gatsby config

## FONT AWESOME

npm i @fortawesome/fontawesome-svg-core @fortawesome/react-fontawesome
Then depending on if you need a fab \* or fas icon, npm i @fortawesome/free-brands-svg-icons OR @fortawesome/free-solid-svg-icons
Fab = free-brands-svg-icons and Fas = free-solid-svg-icons

    	import { FontAwesomeIcon } from ‘@fortawesome/react-fontawesome’
    	import { faInstagram, faSpotify } from ‘@fortawesome/free-brands-svg-icons’

    NOTICE the camelcase for react

Now you can use :
<FontAwesomeIcon icon={faInstagram} size=”2x” />
Always change the size in the html and not css. SVGs are made of paths (lines) so you can’t change the size with rems or ems on the font itself. Use the container anchor tag to modify padding and margins

    OR just use font-size in css on the icon

## SVG

download gastby-plugin-react-svg

plugins: [
{
resolve: "gatsby-plugin-react-svg",
options: {
rule: {
include: /images/ // Or wherever the dir is with svgs
}
}
}
];

Then in html, import Key from ‘./path/images/key.svg’

<Key />

Now you can style it as an svg in css with properties like fill

Fill can now cascade from parent color with fill:currentColor;
Very useful as it will also inherit hover effects

## DYNAMIC DATA

Using the export const query = graphql`` at the end of the file is ONLY for page levels.
For components, must use { useStaticQuery } INSIDE the component function!

    Simple way is to use siteMetadata key-value pair inside gatsby.config.js.
    md files are probably preferable to write in

    Use 2 plugins - gatsby-source-filesystem and gatsby-transformer-remark
    Follow instructions on gatsby page to install plugins

Gatsby-source-filesystem already installed and set up for images, but not markdown

    In gatsby-config.js, set up gatsby-source-filesystem plugin as an object with options


    With name and path, so for images, something like:

    {
      resolve: `gatsby-source-filesystem`,
      options: {
        path: `${__dirname}/src/images`,
        name: 'images'
      }
    },

GATSBY IMAGES
USE styleImg in HTML to override the actual image for objectFit, objectPosition!

    Another alternative is to use a nested img tag inside the gatsby-img and override the initial inline css by adding !important.

gatsbyImg {

Img{ object-fit: contain !important;

}

install gatsby-source-filesystem, gatsby-image, gatsby-plugin-sharp, gatsby-transformer-sharp
Format config as above, add the other 2 plugins as plain strings

In playground, query under file(relativePath: “nameOfImgFile”){
childImageSharp {
Fixed or fluid {
Anything here - to make sure it works

Then in react, import { Img } from ‘gatsby-’image’ and query the same but at the end, use a fragment

```
query {
imageOne: file(relativePath: { eq: "one.jpg" }) {
childImageSharp {
fluid(maxWidth: 1000) {
...GatsbyImageSharpFluid
      }
    }
  }
}
```

The general SIZE of image can be set to the width: , but not height like regular img elements.

For fluid, always have a max-width so the image is not stretched beyond a certain pixel with fragment ...GatsbyImageSharpFluid.

## USING AS BACKGROUND IMAGE

Use gatsby plugin background image.

backgroundImage must be used on that component or page level. Use static query and graphql to query the picture, then use fluid inside <BackgroundImage> stuff inside </BackgroundImage>

To use regular html image tags, you must import the image first on top as a variable and then use src={picture1}

Same for video as well, but you can only import mp4 files in gatsby so just rename any mov files as .mp4

This is useful because it takes care of responsive images in terms of a fluid resolution based on screen and density (1k or 2k screens)

Good to always use gatsby images because of density. 2k screens will use twice as many pixels and different screen sizes mean different resolutions.

Generally a great idea to use sharp-fluid and use images that are around the max pixels you’ll need (so whatever pixels you end up needing x 2) as the maximum

## YOUTUBE

    Use iframes and always use encryption, but also add a query at the end of the src ?rel=0

loading=”lazy”

IMPORTANT!! USE THIS as an attribute inside iframe element to create a WRAPPER outside the youtube. Get img with format https://img.youtube.com/vi/<URLofyoutubeVideo>/hqdefault.jpg

srcDoc="<style>\*{padding:0;margin:0;overflow:hidden}html,body{height:100%}img,span{position:absolute;width:100%;top:0;bottom:0;margin:auto}span{height:1.5em;text-align:center;font:48px/1.5 sans-serif;color:white;text-shadow:0 0 0.5em black}</style><a href=https://www.youtube-nocookie.com/embed/PLACEHOLDER-YOUTUBE-URL?rel=0><img src=https://img.youtube.com/vi/PLACEHOLDER-YOUTUBE-URL/hqdefault.jpg alt='SAME AS TITLE ATTRIBUTE'><span>▶</span></a>"

## GATSBY IMAGES AND GRID

I DON’T KNOW WHY but align-items (to ANYTHING) will fix cropping problems!

HTML IMG => GATSBY IMG

Wrap gatsby IMG with a div
The stylings on the original html img tag should now be on the container div

If using target=”\_blank”, also add rel=”noopener noreferrer”

## CONTENT FOR CLIENTS!

Using contentful/wordpress,
Connecting to a CMS (Contentful)
To manage the head, use react-helmet and gatsby-plugin-react-helmet

## DEPLOYMENT

    Push repo to github,
    Sign into netlify
    Select the repo to install netlify on

Click on advanced to set environment variables
No need to include graphql playground, but contentful/CMS stuff should be there

If you want to change an existing post via contentful, make the changes in contentful and go to netlify, deploy, and select “clear cache and redeploy”

If you make changes in vscode, all you need to do is push to the repo and Netlify will trigger a new build.

## DYNAMICALLY CREATING PAGES (md files)

Make a page template
Generate slug per blog-md-file
Create new page with information from mdFile

Make an md file with title, author, date, and path in the front matter

---

author: "Hideaki"
title: "Intro"
date: "3-1-2010"
path: "/intro"

---

Install gatsyb-source-filesystem and gatsby-transformer-remark and add it to gatsby-config
Make sure the dir is named for remark plugin. In the example below, I have a dir named “posts” in the src folder that contains all md files

{
resolve: `gatsby-source-filesystem`,
options: {
path: `${__dirname}/src/posts`,
name: `markdown-pages`,
},
},

Create template page format for the dynamically generated pages:
import React from "react"
import { graphql } from "gatsby"
export default function Template({
data, // this prop will be injected by the GraphQL query below.
}) {
const { markdownRemark } = data // data.markdownRemark holds your post data
const { frontmatter, html } = markdownRemark
return (

   <div className="blog-post-container">
     <div className="blog-post">
       <h1>{frontmatter.title}</h1>
       <h2>{frontmatter.date}</h2>
       <div
         className="blog-post-content"
         dangerouslySetInnerHTML={{ __html: html }}
       />
     </div>
   </div>
 )
}
export const pageQuery = graphql`
 query($path: String!) {
   markdownRemark(frontmatter: { path: { eq: $path } }) {
     html
     frontmatter {
       date
       path
       title
     }
   }
 }
`

Notice \$path - this will be plugged in with the createPage api in the next section.

Generate slug
First make a gatsby-node.js file in the root

Then:

const path = require(`path`)

exports.createPages = async ({ actions, graphql, reporter }) => {
const { createPage } = actions

const blogPostTemplate = path.resolve(`src/templates/blogTemplate.js`)

const result = await graphql(`{ allMarkdownRemark( sort: { order: DESC, fields: [frontmatter___date] } limit: 1000 ) { edges { node { frontmatter { path } } } } }`)

// Handle errors
if (result.errors) {
reporter.panicOnBuild(`Error while running GraphQL query.`)
return
}

result.data.allMarkdownRemark.edges.forEach(({ node }) => {
createPage({
path: node.frontmatter.path,
component: blogPostTemplate,
context: {}, // additional data can be passed via context
})
})
}

Now node will use the frontmatter path to create a new page for every md file that is created. If an md file is deleted, the link will be deleted but the domain will exist out there (I think?)

## CONNECTING TO Contentful

In contentful, make a new project (delete one if necessary)
Make content model

     Text for title and slug (path)
     Date published
     Author
    Rtf for content

Then go to the content tab and publish a blog.

Npm i gatsby-source-contentful

In gatsby-config, plugin the contentful spaceId and accessToken found in contentful-setting-apiKeys

Add to gatsby-config but THROUGH .env and env-cmd package!!

## FINISHING TOUCHES

    Run Lighthouse
    	Run audit in incognito mode on the netlify build, not local host
    	To add lang=”en”, use gatsby-plugin-html-attributes
    	Add meta description to head.js component
    	Follow gatsby recommendation for PWA section
    	For accessibility just follow lighthouse suggestions
    	Add google-analytics-plugin, set up account in google analytics

Ask for feedback from devs

## CLIENT GITHUB

Have them set up a github (no to the option of github pages, yes for hosting repos)
Get their password, log in from your computer and have them send the verification code
Make a PUBLIC repo, go to repo setting and add collaborator h15200
From local vs code
git remote set-url origin <newClientGithubUrl>
// should create dev and master fetch and pull if you check git remote -v
Git push
// should push to dev branch in new github
git checkout master
git push
Git checkout dev
// should push the initial commit to master

    Pull request from client dev => master

SIGN OUT OF both github and netlify from YOU. Sign into the client’s both.
In netlify, connect to the client github.

Make sure API keys, env, node_modules are inside .gitignore

To WORK on a client project from the past:
Find client github, select clone and just select the url of the DEV branch  
 Open VSCODE, open terminal and git clone <url> desktop/<nameOfDir>
Open folder in vscode
Npm install
Use Gatsby develop instead of npm run (to bypass lacking env file)
Git push (as usual) after adding and committing

## DOMAIN

General rules:
Use an A record if you manage which IP addresses are assigned to a particular machine, or if the IP are fixed (this is the most common case).
Use a CNAME record if you want to alias one name to another name, and you don’t need other records (such as MX records for emails) for the same name.
Use an ALIAS record if you’re trying to alias the root domain (apex zone), or if you need other records for the same name.
Use the URL record if you want the name to redirect (change address) instead of resolving to a destination.

### Connect Domain to netlify -

Go to netlify, go to website, then under domain, add custom domain (actual name of site)
Look for nameRecord and copy

Then pick the current hosting or domain registry company and:

### GoDaddy

Add A record in DNS record
Go to the domain company, change namerecord to what netlify offers
Check to see the new domain is live
NAMECHEAP

ADVANCED DNS, then change the placeholder to the namerecord that netlify spits out

### InMotion

    Under the domain plan - DNS zone editor - bottom of screen add a record

After checking to see site is connected,

## HTTPS certificate

## BEFORE DELETING ORIGINAL VSCODE FILE:

Copy anything inside .gitignore including:
Api keys
Secrets
Env files
Eslint

Put it in a folder inside google drive.

Now after git clone from repo, you can use those files if necessary to test in dev

## gatsby css / scss

## IMAGES

For gatsby, use the Img component after getting gatsby-image, gatsby-plugin-filesystem, gatsby-plugin-sharp, gatsby-transform-sharp.
See Gatsby setup file for more details, but to use traditional methods, wrap all images in a container, used fluid sharp and resize the container to resize the image

always use gatsby images because of density. 2k screens will use twice as many pixels and different screen sizes mean different resolutions.

Generally a great idea to use sharp-fluid and use images that are around the max pixels you’ll need (so whatever pixels you end up needing x 2) as the maximum

## BACKGROUND-VIDEO

For gatsby, declare as variable on top import videoOne from ‘./src/video/whatever.mp4’
(Only mp4 support, so convert MOV files by renaming extension to .mp4)
Then src={videoOne}

Use container width = 100%, height 100%, position absolute to cover the parent (don’t forget position: relative on parent)

Then the actual movie inside that container should be width 100%,, height 100%, object-fit: cover, object-position: whatever

OBJECT-FIT must be used with a specified HEIGHT!

Similar to background-images

COVERING A CONTAINER WITH AN IMAGE WITHOUT background-image

The easiest way to set an image to a container to use pure CSS and background-image.

If you want to use html tags instead,

.img {
Height: 100%;
Width: 100%;
Object-fit: cover
}
