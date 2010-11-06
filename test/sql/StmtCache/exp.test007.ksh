AFTER INSERT FREE
STATEMENT CACHE START 
 SQL=INSERT INTO t1 VALUES(?, 1234, 'CSQL'); hits=0 inuse=0
STATEMENT CACHE END
creating index
After create index 
STATEMENT CACHE START 
STATEMENT CACHE END
After second time prepare 
STATEMENT CACHE START 
 SQL=INSERT INTO t1 VALUES(?, 1234, 'CSQL'); hits=0 inuse=1
STATEMENT CACHE END
After reusing cached insert stmt
STATEMENT CACHE START 
 SQL=INSERT INTO t1 VALUES(?, 1234, 'CSQL'); hits=0 inuse=0
STATEMENT CACHE END
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	100	1234	CSQL	
	
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
---------------------------------------------------------
	t1.f1	t1.f2	t1.f3	
---------------------------------------------------------
	200	1234	CSQL	
	
