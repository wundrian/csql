Statement Executed
Statement Executed
echo Multiple predicates Test Cases - 1,2,3
echo select * from t1 where f1=10 and f3=20;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f1 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f3 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo select * from t1 where f2>10 and f3=20;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f1 </FieldName1>
     <CompOp> GreaterThan </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f3 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo select * from t1 where f3=20 and f1 >10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f3 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f1 </FieldName1>
     <CompOp> GreaterThan </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo Disjunctive Queries Test case - 4,5,6,7,8
echo select * from t1 where f1!=10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> NotEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo select * from t1 where f2!=10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f2 </FieldName1>
   <CompOp> NotEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo select * from t1 where f1=10 or f3=20;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f1 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f3 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo select * from t1 where f2>10 or f3=20;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f2 </FieldName1>
     <CompOp> GreaterThan </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f3 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo select * from t1 where f3=20 or f2 >10;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f3 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f2 </FieldName1>
     <CompOp> GreaterThan </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
