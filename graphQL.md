## setting up a graphQL server

// if you want to use import/export default module,

Babel @babel/cli @babel/core @babel/preset-env @babel-node
.babelrc put the env
Script - start : “nodemon --exec babel-node src/index.js -e js,graphql”

File structure inside src
Type def inside scheema.graphql // NO backticks or quotes
resolvers folder
Resolvers - all resolvers should use arg (parent, args, ctx, info) and all scheema models should use db.Model

Separate files for each root directory such as ‘Query.js’, ‘Mutation.js’, and any other custom types

Since they are models, use Capital file names

Each file should contain just one const variable assigned to an object of methods

Db
index.js

In index.js

import { GraphQLServer } from 'graphql-yoga'
import db from './db'
import Query from './resolvers/Query'
import Mutation from './resolvers/Mutation'
import User from './resolvers/User'
import Post from './resolvers/Post'
import Comment from './resolvers/Comment'

const server = new GraphQLServer({
typeDefs: './src/scheema.graphql',
resolvers: {
Query,
Mutation,
User,
Post,
Comment
} ,
context: {
db
}
})

server.start(()=> {
console.log('server is up')
})

## GraphQL playground functions as the Postman for REST apis

3 Main Apis
Query - request
Mutation - change
Subscription - watch (uses socket to monitor changes)

GraphQL is self documenting, so you’ll know if the data exists or not before you make the request! You need to define every api yourself in the typeDefs and resolvers, so everything is customized.

    In src/scheema.graphql

    input - grouping of scalar (basic, built-in like Int, String!) properties to use in args
    type - custom types must be defined to be used if built on scalar properties
    enum - Only ONE out of list of possibilities


    type Query {
      users(query: String): [User!]!    // gets an array (only) of User(only)
    }
    // etc.. more queries

    type Mutation {
    createUser(data: CreateUserInput!): User!    //
    }
    // etc.. more mutations

    type Subscription {
    post: PostSubscriptionPayload
    }

    input CreateUserInput{
    title: String!
    age: Int    // no ! means null is ok
    }

    type User {
    Id: ID!
    name: String!
    email: String!
    age: int
    }

    enum MutationType {   // custom set of possibilities
    CREATED
    UPDATED
    DELETED
    }

    type PostSubscriptionPayload {
    Mutation: MutationType!    // using enum in a custom type
    data: post!
    }

## Gotchas:

Import { GraphQLServer, Pubsub } from ‘graphql-yoga’

const pubsub = Pubsub()

const server = newGraphQLSever({
typeDefs: ‘./src/scheema.graphql’,
resolvers: {
Imported resolvers: Imported resolvers
etc..
},
context: {
db,
pubsub

}
})

## In the query, make sure args are called like this. DOUBLE QUOTES ONLY!

    Query {

greeting(name: “Patti”)
}

To Query an item from an array of a custom type:

In typedef
` type Query {
users(query: String!): [User

Use ctx (context) to have access to the schema from anywhere in the file structure
import db into the index, then pass it in to context when you make new GraphQLServer

Unlike queires and mutations, you need to import {pubsub} for Subscription. for the resolver, the property is NOT a method, but an object for subscription. Return value must go through pubsub.asyncIterator which takes in ONE arg, which is a string, channel name

pubsub.publish needs to be called every time data changes. It takes in the channel string and an object for the changing value
