Go to root project directory on terminal of vscode

Make sure ssh is connected
heroku keys:add

    	ADD NEW PROJECT TO HEROKU

Make a new heroku project
heroku create <name of app>

    	CHECK JSON SCRIPT

If you haven’t already, in package.json, add under scripts “start”: “node src/app.js” (or whatever the main app js is)

    	CHECK PORT

Go to top where const app = express() and under it,
const port = process.env.PORT || 3000

// UPDATE!

    No, set anything that deals with env in a ‘config’ dir in a file named ‘dev.env’
     PORT=3000

Then use env-cmd as a DEV dependency (npm i env-cmd --save-dev)
And use it to use variables in code before pushing to git or anywhere public.

For git, make a .gitignore file and add the dev.env file.
For heroku, use command

    heroku config:set key=value 2ndkey=value 3rdkey=value (etc..)
    (can reverse with heroku config:unset)

When saving mongoDBurl from atlas, the string should be between single quotes and after mongodb.net/<THIS IS THE PROJECT NAME>?retryWrite=true’ // usually good to include retryWrite-true

In the bottom where you set the port,

In app.js, go to the end where you (probably) developed on a local host
app.listen(port, () => {
console.log(`listening on port ${port}`)
})

    	CHECK ANY fetch() that is fetching from local host

If any url has the words ‘localhost’ in the url, , instead use absolute path starting with /

For nodemon, install as a dev dependency by
npm i nodemon --save-dev

And add a script somethin like
“dev” : “nodemon src/app.js -e js,hbs”

npm run dev WILL work but dev dependency install won’t run globally via nodemon src/app.js

git push heroku master
To finish deployment to heroku
