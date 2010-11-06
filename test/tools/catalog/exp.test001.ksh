Case 1: With no option:
<TableNames>
  <No tables exist></No tables exist>
</TableNames>
Case 2: With ? option:
Usage: catalog [-u username] [-p passwd] [-l] [-i] [-d] [-T table] [-I index] [-D <lock|trans|proc|chunk>]
       l -> list all table with field information
            list all Index information
       i -> reinitialize catalog tables. Drops all tables.
       d -> print db usage statistics
       T -> list table information
       I -> list index information
       D -> print debug information for system tables
Note: If multiple options are specified, last one will be considered.
Case 3: With wrong username :
Case 4: With wrong password :
Case 5: With correct user name  and password :
<TableNames>
  <No tables exist></No tables exist>
</TableNames>
