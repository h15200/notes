# Cheatsheet 

- once logged in, the prompt will likely be `{CurrentConnectedDB}=>`, set to 
the default db. If you're not sure, run `\l` to see a list of all dbs


- `\l` list all databases 
- `\c {DatabaseName}` change connection to another database
- `\dt` list all tables in the current database
- `\d {TableName}` describe a table
- `\x` toggle expanded view (recommended)
- `SELECT * FROM {TableName} WHERE id="3234234";` 
    - don't forget single quotes around strings 
    - don't forget semicolon
    - if output is messed up, you probably forgot expand mode `\x`
