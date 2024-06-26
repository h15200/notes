# Overview

SQL stands for Structured Query Language
Databases are usually SQL (postgress, mySQL) or NoSQL (MongoDB)

Databases are connected from the server and is just a big computer
In dev, databases might be stored on the same machine but it is best in production to separate server from db

SQL = Relational DB
NoSQL = Non relational

## Database types

- RDBMS (SQL)
  - suitable when data is related to each other with simple many-to-many relationships
  - generally the first pick as a first source of truth db
- NoSql
  - anything that's not SQL
  - K/V Store, Document Store, Column orientated store, Graph Store
  - document dbs are good when there are no relationships but the data is
    in a tree like structure
  - graph dbs are good when everything is related and has numerous m-t-m relationships
  - key-value db (uses a simple schema of k:v)
  - document model is a subset of key-value, but allows for more
    complex, nested data and a flexible schema

### Database Engine Types

another way to categorizing dbs

- generally, 2 main categories

1. log-structured storage engines (generally for nosql)

   - uses an append-only log structure to add data
   - `Sorted String Tables` (SS Tables) are used to sort all keys into various
     segments. Keys are compacted periodically to keep it in memory. Snapshots
     of the tables are saved to disk periodically for durability. data is appended
     and compacted
   - writes are generally fast, but reads are slower than page-oriented storage

2. page-oriented storage engines (for ex, B-tree and generally for sql)
   - used in most RDBMS
   - a `page` is a reference tree that holds data
   - data is not appended but is updated (mutated)
   - generally faster reads than Log structured merge

### History

- in the 80s, many databases were tree structures, organized by hierarchy.
  this proved difficult to represent m-t-m (many to many) relationships, which
  lead to the popularity of relational dbs

- for use cases that don't fit relational dbs (noSql), there are 2 main directions:
  - document (object) dbs used for when data comes in self-contained documents and
    relationships with one another are rare
  - graph model where anything is potentially related to everything

## SQL & Tables

ALL relational databses (SQL) are `ACID` Compliant

A relational database (SQL) `model` is defined as one or more `tables`.
Tables are constructed based on a strict `schema`

Table has columns. Columns DO NOT change as they are defined in a schema.
Columns are also known as `attributes` or `fields`

Table has rows. Rows are instances of new records and are added continuously.
Rows are also known as `records`

you cannot have a table INSIDE of a table but you can reference other tables through ids.

## key-value db

- A Key-Value store are stored WITHOUT nesting
- `Redis` is a prime representative of a key-value system db.

- The data does NOT persist if there is a power outage.
- Sensitive or valuable data is not used in a key-value store.
- many popular noSql dbs support both simple k-v as well as document models

## Document db

- technically, a subset of k-v databases
- NoSql dbs are easier to scale horizontally (sharding) because there is no
  need to preserve join logic

NoSQL are NOT ACID Compliant.
There are SOME ACID compliant qualities, but generally NOT completely ACID compliant.

Documents are written close to JSON.

Instead of tables like in SQL, you have a collection of documents.

- each document is like a JS object
- You have the ability to nest tables
- Built with an emphasis on SPEED.

- `MongoDb`, `DynamoDb`

NoSQL dbs are used in big data and real-time web applications. (e-commerce)
Motivations include simplicity of design, simpler horizontal scaling of clusters of machines, and finer control over availability.
Generally considered FASTER and more FLEXIBLE.
NoSQL's don't use schemas, so it's not as solid but more flexible.

THE MORE Acid compliant you make a NoSQL db, the less fast/flexible it will be.

## ACID compliance

Properties of db transactions intended to guarantee validity event in the event of errors, power failures, etc..

`A` Atomicity - Requires that a transaction be 'all or nothing'. If one part fails, the whole transaction fails and db state is unchanged

`C` Consistency - Any data written to the db will follow the schema and follow the guidelines (constraints, cascades, triggers, etc)

`I` Isolation - Concurrency control. Concurrent execution of transactions result in a state that would be obtained if they were run one after the other.

`D` Durability - Once a transaction is committed, the data will persist, even if there is a crash or power loss.

## SQL vs NoSQL

Since SQL databases are ACID compliant, it is more 'solid' in general.
Important database transactions like financial processes all use SQL.

NoSQL databases are not as solid but faster and more flexible BECAUSE it doesn't use a traditional schema. NoSQL lookups are fast because the data is formed as JSON (object lookup)

- sql enforces an `explicit` schema on write.
- not that noSql still has schemas, but it is `implicit`, handled on read

For HUGE apps, possible to use both an SQL and a NoSQL in one app.

## PostgreSQL

a relational database with emphasis on extensibility and standards-compliance
It is `ACID compliant`, supporting industry best practices as well as great documentation!

To see tables in the terminal, use `\d`

See more inside MYSQL.md

- Postgres also has support for json and jsonb (binary) semi-structured data, but
  any schema changes will require migrations so as a nosql db, it is not as robust
  or flexible as a "true" noSql like Mongo.

  - generally, when an ACID compliant relational db adapts characteristics
    of a noSql db like json, the main benefit is keeping ACID while having
    noSql like properties. If the main purpose is to use unstructured data
    and ACID compliance (strong consistency) is not a conern, it is better
    to use a "true" noSql

- It is possible to horizontally scale Postgres, but only by using 3rd party
  tools. It was originally meant as a monolothic model, allowing for only
  vertical scaling. In this way, something like Mongo which is meant for a
  distributed system with built in replication, sharding, self-healing out
  of the box.

## MongoDB

a non-relational database that is common in the JS stack.

A free open-source cross-platform document-oriented database.
uses JSON-like documents with dynamic schemas (flexible)

Features:

Indexing - any field can be indexed
Replication - stores data as a replica set of two or more copies
Load balancing - Mongo scales horizontally using sharding
Aggregation - MapReduce can be used for batch processing of data and aggregation operations.

## Redis

Prime example of a key-value store.
A data structure server
Holds its entire dataset in RAM, and syncs back to the disc every 2 seconds
Very fast because data is memcached but a power outage will destroy some data.

A good choice if you want a highly scalable data store shared by multiple processes or multiple applications.

## Schema

A schema is a map of what your data looks like.

In an SQL - defined the columns in your tables and the rules that data in rows must follow
In a NoSQL, defines the object

In a key-value, there is no schema at all.

## SQL relationships

One to One
One to Many
Many to Many

Linking model to model happens by establishing relationships through the creation of foreign keys

Often, ID fields are used for this but any common field can be used.

model Users id, name, email
model Houses id, name, user_id (which equals the Users id)

The id is the primary key for Users
The id is the primary key for Houses
The user_id is the FOREIGN key for Houses that links to Users.

## optimizing

### Indexing

- index on a field to speed up READ process
- often an easier solution than sharding, so look at this first

### Sharding

- A SINGLE database can be sharded to multiple servers to distribute load

## schema migration

- whenever a schema changes in a db (even nosql objects), you need to a `migration`
