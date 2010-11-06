echo create table t1(f1 char, f2 char, f3 char, f4 char);
Statement Executed
echo create index hashcharf1f2f3 on t1(f2,f3,f1) hash;
Statement Executed
echo explain plan select * from t1;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 = 'a';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 = 'a' and f2='a';
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
     <FieldName1> f2 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 = 'a' and f2='a' and f3='a';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
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
       <FieldName1> f2 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
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
echo explain plan select * from t1 where f1 = 'a' or f2='a' or f3='a';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
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
       <FieldName1> f2 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
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
echo explain plan select * from t1 where f1 = 'a' and f2='a' or f3='a';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
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
       <FieldName1> f2 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
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
echo explain plan select * from t1 where f1 = 'a' and f2='a' and not(f3='a');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
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
       <FieldName1> f2 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <LogOp> NOT </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <FieldName1> f3 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-LEFT>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 in('a','a','a') and f2='a' and not(f3='a');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <LogOp> AND </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <LogOp> OR </LogOp>
       <PRED-LEFT>
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
           <FieldName1> f1 </FieldName1>
           <CompOp> Equals </CompOp>
           <OperandPtr> VALUE </OperandPtr>
           </PREDICATE>
         </PRED-RIGHT>
         </PREDICATE>
       </PRED-LEFT>
       <PRED-RIGHT>
         <PREDICATE>
         <FieldName1> f1 </FieldName1>
         <CompOp> Equals </CompOp>
         <OperandPtr> VALUE </OperandPtr>
         </PREDICATE>
       </PRED-RIGHT>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f2 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <LogOp> NOT </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <FieldName1> f3 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-LEFT>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 in('a','b','c') and f2 like 'a%' and not(f3='d');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <LogOp> AND </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <LogOp> OR </LogOp>
       <PRED-LEFT>
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
           <FieldName1> f1 </FieldName1>
           <CompOp> Equals </CompOp>
           <OperandPtr> VALUE </OperandPtr>
           </PREDICATE>
         </PRED-RIGHT>
         </PREDICATE>
       </PRED-LEFT>
       <PRED-RIGHT>
         <PREDICATE>
         <FieldName1> f1 </FieldName1>
         <CompOp> Equals </CompOp>
         <OperandPtr> VALUE </OperandPtr>
         </PREDICATE>
       </PRED-RIGHT>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f2 </FieldName1>
       <CompOp> Like </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <LogOp> NOT </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <FieldName1> f3 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-LEFT>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 in('b','c','a') or f2 like 'a%' or not(f3='d');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <LogOp> OR </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <LogOp> OR </LogOp>
       <PRED-LEFT>
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
           <FieldName1> f1 </FieldName1>
           <CompOp> Equals </CompOp>
           <OperandPtr> VALUE </OperandPtr>
           </PREDICATE>
         </PRED-RIGHT>
         </PREDICATE>
       </PRED-LEFT>
       <PRED-RIGHT>
         <PREDICATE>
         <FieldName1> f1 </FieldName1>
         <CompOp> Equals </CompOp>
         <OperandPtr> VALUE </OperandPtr>
         </PREDICATE>
       </PRED-RIGHT>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f2 </FieldName1>
       <CompOp> Like </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <LogOp> NOT </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <FieldName1> f3 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-LEFT>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 in('a','c','b') or f2 like 'a%' and not(f3='d');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <LogOp> OR </LogOp>
     <PRED-LEFT>
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
         <FieldName1> f1 </FieldName1>
         <CompOp> Equals </CompOp>
         <OperandPtr> VALUE </OperandPtr>
         </PREDICATE>
       </PRED-RIGHT>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f1 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <LogOp> AND </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <FieldName1> f2 </FieldName1>
       <CompOp> Like </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <LogOp> NOT </LogOp>
       <PRED-LEFT>
         <PREDICATE>
         <FieldName1> f3 </FieldName1>
         <CompOp> Equals </CompOp>
         <OperandPtr> VALUE </OperandPtr>
         </PREDICATE>
       </PRED-LEFT>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
Statement Executed
