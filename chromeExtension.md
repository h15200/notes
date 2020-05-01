# example of a simple chrome extension using jquery and JS

In root dir, make main.js, manifest.json

Maniest should contain
Version Number
Description
logo/icon - MUST BE PNG files!
Link to main.js , for which site you want to use the extension for

```
{
"manifest_version": 2,
"name": "Focus",
"version": "1.0",
"description": "My first Chrome Extension to alter Youtube.com",
"content_scripts": [
{
"matches": ["https://www.youtube.com/*"],
"js": [“jquery.min.js”, "./main.js"]
 }
],
"icons": {
"16": "focusPatti.png",
"32": "focusPatti.png",
"48": "focusPatti.png",
"128": "focusPatti.png"
},
"browser_action" : {
"default_popup" : "popup/index.html"
}

}
```

Notice how jquery file is loaded into the same folder, and is under matches after main.js
Jquery must be loaded FIRST before main.js

Load directory (with main.js, manifest.json) onto chrome://extensions
