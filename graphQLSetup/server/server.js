const path = require('path');
const express = require('express');
const expressGraphQL = require('express-graphql'); // middleware to initialize graphQL spec
const {
  GraphQLSchema,
  GraphQLObjectType,
  GraphQLString,
  GraphQLList,
  GraphQLInt,
  GraphQLNonNull,
  graphqlSync,
  GraphQLInputObjectType,
} = require('graphql');
const app = express();

app.use('/assets', express.static(path.resolve(__dirname, '../client/assets')));

app.get('/', (req, res) => {
  return res
    .status(200)
    .sendFile(path.resolve(__dirname, '../client/index.html'));
});

// dummy database. Can be Mongo or Postgres or anything
const books = [
  { id: 1, name: 'Harry Potter and the Chamber of Secrets', authorId: 1 },
  { id: 2, name: 'The Fellowship of the Ring', authorId: 2 },
];

const authors = [
  { id: 1, name: 'J. K. Rowling' },
  { id: 2, name: 'J. R. R. Tolkien' },
];

// make custom types to use inside root

const BookType = new GraphQLObjectType({
  name: 'Book',
  fields: () => ({
    id: { type: GraphQLNonNull(GraphQLInt) },
    name: { type: GraphQLNonNull(GraphQLString) },
    authorId: { type: GraphQLNonNull(GraphQLInt) },
    // makes relational query possible
    author: {
      type: AuthorType,
      // resolve takes in parent data, in this case books
      resolve: (book) => {
        // hardcoded from the two arrays above for now
        return authors.find((parent) => parent.id === book.authorId);
      },
    },
  }),
});

const AuthorType = new GraphQLObjectType({
  name: 'Author',
  description: 'Author of a book',
  fields: () => ({
    id: {
      type: GraphQLNonNull(GraphQLInt),
    },
    name: {
      type: GraphQLNonNull(GraphQLString),
    },
    books: {
      type: GraphQLList(BookType),
      resolve: (parent) => books.filter((book) => book.id === parent.id),
    },
  }),
});

// make Root

const RootQueryType = new GraphQLObjectType({
  name: 'Query',
  description: 'Root Query', // shows up in graphiql
  fields: () => ({
    books: {
      type: new GraphQLList(BookType),
      description: 'List of all books',
      resolve: () => books,
    },
    authors: {
      type: new GraphQLList(AuthorType),
      description: 'List of All Authors',
      resolve: () => authors,
    },
    // query a single book
    book: {
      type: BookType,
      description: 'A single book',
      // single book query takes in one arg, id
      args: {
        id: { type: GraphQLInt },
      },
      resolve: (parent, args) => books.find((book) => book.id === args.id),
    },
    author: {
      type: AuthorType,
      description: 'A single author',
      args: {
        id: { type: GraphQLInt },
      },
      resolve: (parent, args) =>
        authors.find((author) => author.id === args.id),
    },
  }),
});

// for POST, PUT, DELETE equivalent in GraphQL
// use mutation

const schema = new GraphQLSchema({
  query: RootQueryType,
});

app.use(
  '/graphql',
  expressGraphQL({
    graphiql: true,
    schema,
  })
);

app.listen(3000, () => console.log('listening on port 3000'));
