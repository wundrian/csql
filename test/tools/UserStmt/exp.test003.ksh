Connecting User root
echo create user lakshya password 'lakshya123';
Statement Executed
echo create user lakshyasolution password 'lakshya123';
Statement Executed
echo show users;
=============UserNames===================
   root 
   lakshya 
   lakshyasolution 
=========================================
echo Disconnecting root user
quit;
Connecting User lakshya
echo create user lakshyatraining password 'lakshya123';
Statement prepare failed with error -3
echo drop user lakshyasolution;
Statement prepare failed with error -3
echo Disconnecting user lakshya
quit;
Connecting User root
echo show users;
=============UserNames===================
   root 
   lakshya 
   lakshyasolution 
=========================================
echo drop user lakshyasolution;
Statement Executed
echo  user lakshya;
Statement Executed
echo show users;
=============UserNames===================
   root 
=========================================
Test Passed
