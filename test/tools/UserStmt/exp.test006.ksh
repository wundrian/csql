Connecting User root
echo create user nihar password 'nihar123';
Statement Executed
echo alter user nihar set password 'papu123';
Statement Executed: Rows Affected = 0
Connecting User nihar using new Password
echo show users;
=============UserNames===================
   root 
   nihar 
=========================================
echo Disconnecting User nihar
quit;
Connecting User root
echo drop user nihar;
Statement Executed
echo show users;
=============UserNames===================
   root 
=========================================
Test Passed
