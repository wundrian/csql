echo No Primary key -Test Case - 1,2,3
echo select * from t1;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
 </TABLE-NODE>
echo select * from t1 where f1=10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo select * from t1 where f1>10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> GreaterThan </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
Statement Executed
echo Primary key -Test Case - 4,5,6
echo select * from t1;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
 </TABLE-NODE>
echo select * from t1 where f1=10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo select * from t1 where f1>10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> GreaterThan </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
Statement Executed
echo Hash Index -Test Case - 7,8,9
echo select * from t1;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
 </TABLE-NODE>
echo select * from t1 where f2=10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f2 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo select * from t1 where f2>10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f2 </FieldName1>
   <CompOp> GreaterThan </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
Statement Executed
echo Tree Index -Test Case - 10,11,12
echo select * from t1;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
 </TABLE-NODE>
echo select * from t1 where f3=10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f3 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo select * from t1 where f2>10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f3 </FieldName1>
   <CompOp> GreaterThan </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
