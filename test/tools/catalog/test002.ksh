#!/bin/sh
# Test Case
# check options l, i, d, T, I with empty database
# check options D with trans, lock and non existing structure name
# check behaviour when multiple options are given together

echo "Case 1: With l option:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -l
if [ $? -ne 0 ]
then
   exit 1;
fi

echo "Case 2: With i option:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -i
if [ $? -ne 0 ]
then
   exit 2;
fi

echo "Case 3: With d option:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d
if [ $? -ne 0 ]
then
   exit 3;
fi

echo "Case 4: With nonexisting tablename on -T option :" 
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -T t1 2>/tmp/tmptstlog
if [ $? -eq 0 ]
then
   exit 4;
fi

echo "Case 5: With nonexisting indexname on -I option :" 
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -I idx1 2>/tmp/tmptstlog
if [ $? -eq 0 ]
then
   exit 5;
fi

echo "Case 6: With trans on D option:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D trans
if [ $? -ne 0 ]
then
   exit 6;
fi
echo "Case 7: With lock on D option:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D lock
if [ $? -ne 0 ]
then
   exit 7;
fi
echo "Case 8: With nonexisting structure on D option:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -D notexist
if [ $? -eq 0 ]
then
   exit 8;
fi
echo "Case 9: With two options:"
$CSQL_INSTALL_ROOT/bin/catalog -u root -p manager -d -l
if [ $? -ne 0 ]
then
   exit 9;
fi
exit 0
