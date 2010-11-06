Connecting User root
echo create user nihar password 'nihar123';
Statement Executed
echo create user lakshya password 'lakshya123';
Statement Executed
Connecting User nihar
echo show users;
=============UserNames===================
   root 
   nihar 
   lakshya 
=========================================
echo alter user lakshya set password 'lakshya321';
Statement prepare failed with error -3
echo Disconnecting User nihar
quit;
Connecting User root
echo drop user nihar;
Statement Executed
echo drop user lakshya;
Statement Executed
echo show users;
=============UserNames===================
   root 
=========================================
Test Passed
