# Google Map Api

## Setting up the APi to your project

1. to https://console.developers.google.com

2. Enable Google maps support inside the project

- Make a new project
- Once its finished, click on top left three bars, APIs and Services - library
- Maps JavaScript API - press enable

3. Generate an API key

- click on top left three bars - APIs and Services - Credentials - Create credential - Api key

4. Add the google maps script tag to HTML file

https://maps.googleapis.com/maps/api/js?key= `THEAPIKEYHERE`

- in the root html file, ABOVE any js script
  `<script src="https://maps.googleapis.com/maps/api/js?key="></script>`

Load the server, and see if you can type in the dev console, google and see a map prop on the object. If so, it's good to go

## Rendering the Map

When you use a script tag inside index.html, that data is available on a global scope, which is why typing "google' into the dev console on the browser will show the object.

If you are using TS, you may need a type definition file for the library you imported through script.

@types/googlemaps

If it still does not recognize google as a namespace, then add this to the top of the file!

`/// <reference types="@types/googlemaps" />`
