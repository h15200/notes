# MongoDB

## Installation and setup;

Mongodb.com

Download community (free) version
Select Os X , TGZ

Install

RENAME the unzipped folder to “mongodb”
Move to the user folder
Make another dir “mongodb-data”

Go to vscode terminal, and

/Users/hideaki/mongodb/bin/mongod --dbpath=/Users/hideaki/mongodb-data
KEEP THIS CONNECTION OPEN to connect to a GUI like Robo 3T

Open Robo 3T, name the server, and connect to mongodb

Make sure it mounts, if not, look for typos and correct path.

Most likely will be port=27017

In the js file,

const mongodb = require(‘mongodb’)
const MongoClient = mongodb.MongoClient

const connectionURL = ‘mongodb://127.0.0.1:27012’
const databaseName = whatever

MongoClient.connect(connectionURL, {
useNewUrlParser: true
}, (error, client) => {
If (error) {
return <error handling>
}
// make db
const db = client.db(databaseName)
// make collection and start inserting data
db.collection(‘users’).insertOne({
Whatever: ‘whatever’,
Whatever2: ‘whatever’
})

})

The above is easier on mongoose as it’s only mongoose.connect

Gotchas:

    To read data by _id, make sure you use {_id: new ObjectID(‘<idstring>’)

Remember .find and .findOne are different syntax.

Must have callback to find ONe query
findOne ( {query}, (error, result) => { stuff} )

NO callback but must chain a method and THEN use the callback (error, result)
.find( {query}).toArray( (error, result) => {
etc..
