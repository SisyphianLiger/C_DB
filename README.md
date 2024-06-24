# Setting up DB in C

# What is this Project?
Writing DB's have become popular recently, and building 
things is perhaps the best way to learn. I am in the process
of writing a database with database functionality used in 
CRUD applications, i.e. Create a user, read a user, delete 
a user, and update a user. 

# Objectives
1. Create a File with DB CLI ( Completed )
    - Allow for updating/deleting/adding
    - Create Help flag to assist Users
    - Use MakeFile to Test Functionality
    - Establish File Structure

2. Networking ( In Progress )
    - Add Networking Functionality for little or big endianess
    - Establish a Server - Client Relation
    - ...

3. Multi-Threading ( In Progress )
    - Allow for Multi-Threaded DS
    - Implement Multi-Threded DB Access 

4. Further Components ( In Progess )
    - Create a B+ Tree DS for the DB
    - Add additional functionality 
    - Allow for remote access ( Networking Stage )
    - Allow for multiple Structs


# Current State
The DB can be run with the following command

```
Make 
```
This may lead to some preloaded testing I am doing in Make.


Once compiled the user is able to use the -h flag to see the options 
currently available:

```
./bin/out -h
```


When accessing the db it is important to use the -f flag followed by 
the db file. This command for example, lists all the names of the users
in the database.
```
./bin/out -f mydb.db -l
```


# Continuing
I am currently in progress to adding network capabilities to this DB.
A DB tutorial once this db is online will be listed when the network 
code exists.



