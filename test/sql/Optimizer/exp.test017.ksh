echo create table t1(f1 int, f2 int, f3 varchar(20),f4 date);
Statement Executed
echo create index idx on t1(f3,f4,f2) hash;
Statement Executed
echo explain plan select * from t1 where f2 is null;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f2 </FieldName1>
   <CompOp> isNULL </CompOp>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f2 is not null;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f2 </FieldName1>
   <CompOp> isNULL </CompOp>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f2 is null and f3 is not null;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f2 </FieldName1>
     <CompOp> isNULL </CompOp>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f3 </FieldName1>
     <CompOp> isNULL </CompOp>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 is null or f2 is not null or f3 is null or f4 is not null;
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
         <CompOp> isNULL </CompOp>
         </PREDICATE>
       </PRED-LEFT>
       <PRED-RIGHT>
         <PREDICATE>
         <FieldName1> f2 </FieldName1>
         <CompOp> isNULL </CompOp>
         </PREDICATE>
       </PRED-RIGHT>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f3 </FieldName1>
       <CompOp> isNULL </CompOp>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f4 </FieldName1>
     <CompOp> isNULL </CompOp>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 is null and f2 is not null and f3 is null and f4 is not null;
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
       <LogOp> AND </LogOp>
       <PRED-LEFT>
         <PREDICATE>
         <FieldName1> f1 </FieldName1>
         <CompOp> isNULL </CompOp>
         </PREDICATE>
       </PRED-LEFT>
       <PRED-RIGHT>
         <PREDICATE>
         <FieldName1> f2 </FieldName1>
         <CompOp> isNULL </CompOp>
         </PREDICATE>
       </PRED-RIGHT>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f3 </FieldName1>
       <CompOp> isNULL </CompOp>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f4 </FieldName1>
     <CompOp> isNULL </CompOp>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
Statement Executed
