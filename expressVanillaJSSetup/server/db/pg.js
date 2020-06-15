const { Pool } = require('pg');

const pool = new Pool({
  connectionString: ``,
});

// setup elephant sql instance, plug in the string

// Create tablename (
// _id serial primary key,
// text varchar Not Null
// created_at timestamp default current_timestamp,
// )

// export it

module.exports = {
  query: (text, params, cb) => {
    console.log('Executed query:', text);
    return pool.query(text, params, cb);
  },
};
