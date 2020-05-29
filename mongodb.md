# MongoDB

MongoDB is a document-oriented, NON-relational db

Everything is stored as JSON (a JS object)
Built with an emphasis on speed
NOT equipped to handle complex relationships like SQL
Instead of tables, you have a collection of documents

- each document is a js object
- have ability to store array and object data types
- ability to nest

Duplicate data is ok.

## Mongoose

Wrapper library that sits on top of Mongo to provide structure.

Mongoose syntax

findOne - returns null or an object
findMany - returns an empty array (still truthy) or an array of data

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

```
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
```

The above is easier on mongoose as it’s only mongoose.connect

Gotchas:

    To read data by _id, make sure you use {_id: new ObjectID(‘<idstring>’)

Remember .find and .findOne are different syntax.

Error handling

1. callbacks (err, data)

2. .then.catch

3. async try catch block

## Mongoose queries does NOT return a promise natively

must chain .exec() to uses .catch and async.

EXCEPTION is Model.create() which natively returns a promise
