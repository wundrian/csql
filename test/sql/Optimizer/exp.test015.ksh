echo create table t1(f1 time, f2 time, f3 time, f4 time);
Statement Executed
echo create index hashtimef1f2f3 on t1(f2,f3,f1) hash;
Statement Executed
echo explain plan select * from t1;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 = '03:03:03';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03';
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
echo explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03' and f3='03:03:03';
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
echo explain plan select * from t1 where f1 = '03:03:03' or f2='03:03:03' or f3='03:03:03';
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
echo explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03' or f3='03:03:03';
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
echo explain plan select * from t1 where f1 = '03:03:03' and f2='03:03:03' and not(f3='03:03:03');
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
echo explain plan select * from t1 where f1 in('03:03:03','03:03:03','03:03:03') and f2='03:03:03' and not(f3='03:03:03');
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
echo explain plan select * from t1 where f1 in('03:03:03','05:05:05','06:06:06') and (f2 between '03:03:03' and '03:03:03') and not(f3='03:03:03');
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
       <CompOp> GreaterThanEquals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       <Comp2Op> LessThanEquals </Comp2Op>
       <Operand2Ptr> VALUE </Operand2Ptr>
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
echo explain plan select * from t1 where f1 in('05:05:05','06:06:06','03:03:03') or (f2 between '03:03:03' and '03:03:03') or not(f3='03:03:03');
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
       <CompOp> GreaterThanEquals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       <Comp2Op> LessThanEquals </Comp2Op>
       <Operand2Ptr> VALUE </Operand2Ptr>
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
echo explain plan select * from t1 where f1 in('03:03:03','06:06:06','05:05:05') or (f2 between '03:03:03' and '03:03:03') and not(f3='03:03:03');
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
       <CompOp> GreaterThanEquals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       <Comp2Op> LessThanEquals </Comp2Op>
       <Operand2Ptr> VALUE </Operand2Ptr>
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
