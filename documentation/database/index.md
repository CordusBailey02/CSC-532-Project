# Database Documentation

Ben Meister <br>
David Jara <br>
Cordus Bailey <br>

# Database Scheme

The database uses MYSQL and is setup to have a table for:
    USER information - username, email, ...
    CATEGORY information
    POST information - username, category, content
    REPORT information - user reporting, user reported, ...
    ACCOUNT PASSWORD information - username, password as SHA

# Server Side to Database

For each request sent from the client, the server determines what needs to be done and calls the correct MYSQL Stored Procedure handled by mysql_database_query. The result of the query is handled and the approriate response is sent to the client.

# mysql_database_query

Connection to the MYSQL database is established for every query using the connection_init function. The queryname is checked to create the correct call function string. mysql_query is called to send the query to the database to run a stored procedure. From there the resulting data, handled as a char ***, is set to the returned MYSQL_RES type by inserting row by row. Should there not be any returned data (INSERT, UPDATE, DELETE, ...), the pointer is set to NULL.

# ERROR HANDELING

There are 5 error possibilities:
SUCCESS - Everything worked correctly.
CONNECTION_ERROR - The MYSQL connection was interrupted or never established.
INEXISTENT_QUERY - The query the server is attempting to run is not established in the database file. Check to see if the query name was spelled correctly.
INSUFFICIENT_PARAMETERS - The attempted query is expecting more parameters. 
QUERY_ERROR - The query returned an error when calling the stored procedure. Parameter types might be wrong or the query string has incorrect syntax.