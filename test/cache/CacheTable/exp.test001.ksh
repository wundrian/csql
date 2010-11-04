Usage: cachetable [ -U <username> ] [ -P <password> ]
                  [ -t <tblName> [-D] [ -c "condition" ]
                                 [-f "fieldListToCache"]
                                 [ -p <fieldName> [-F] ]
                                 [ -d <dsName>]
                  [ -l <dsName>|]
                                 [ -u [-s] ]
                                 [ -s | -r | -E ] ]
                  [ -S | -R ]

       U -> Username to connect with csql.
       P -> Password for above username.
       t -> Table name to be cached in csql from target db.
       D -> Enable direct access option to target database.
       c -> Conditional expression used in std SQL WHERE clause.
       f -> List of field names to be cached. Comma separated.
       p -> Not Null unique index field name for Bidirectional
            caching on which trigger needs to be run.
       d -> Cache the table from the specified DSN.
       l -> Retrieves all the cached tables from the specified DSN.
       F -> Forceful caching.
       s -> Load only the records from target db.
            Assumes table is already created in csql.
       u -> Unload the table. If used with -s option,
            removes only records and preserves the schema.
       r -> Reload the table. Get the latest image of table from target db.
       E -> Elevate table status from Replicated to Cached and Replicated.
       S -> Cache Description for cached tables.
       R -> Recover all cached tables from the target database.
