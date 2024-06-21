# PSQL

## Connecting
- to log in to a particular database, run `psql -d {DatabaseName}`
- if you just run `psql`,the prompt will show the current connected db 
`{CurrentConnectedDB}=>`  

## Meta commands (commands that start with `\`)
- `\l` list all databases 
- `\c {DatabaseName}` change connection to another database
- `\dt` list all tables in the current database
- `\d {TableName}` describe a table
- `\x` toggle expanded view (recommended)

## General SQL
- `SELECT * FROM {TableName} WHERE id="3234234";` 
    - don't forget single quotes around strings 
    - don't forget semicolon
    - if output is messed up, you probably forgot expand mode `\x`
