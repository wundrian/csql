echo create table t1(f1 tinyint, f2 smallint, f3 int, f4 bigint, f5 char(10), f6 varchar(10), f7 date, f8 time);
Statement Executed
echo create index hashtiny on t1(f1) hash;
Statement Executed
echo create index hashsmall on t1(f2) hash;
Statement Executed
echo create index hashint on t1(f3) hash;
Statement Executed
echo create index hashbig on t1(f4) hash;
Statement Executed
echo create index hashchar on t1(f5) hash;
Statement Executed
echo create index hashvarchar on t1(f6) hash;
Statement Executed
echo create index hashdate on t1(f7) hash;
Statement Executed
echo create index hashtime on t1(f8) hash;
Statement Executed
echo explain plan select * from t1;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 = 2 and f1 in (0,2,4) ;
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
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 = 3 or (f1  between 2 and 4);
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
     <FieldName1> f1 </FieldName1>
     <CompOp> GreaterThanEquals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     <Comp2Op> LessThanEquals </Comp2Op>
     <Operand2Ptr> VALUE </Operand2Ptr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f2 in (0,2,4) and f2 = 2;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
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
         <FieldName1> f2 </FieldName1>
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
       <FieldName1> f2 </FieldName1>
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
 </TABLE-NODE>
echo explain plan select * from t1 where (f2 between 2 and 4) or f2 = 2;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
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
     <FieldName1> f2 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f3 = 2 or f3 in (1,2) ;
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
       <FieldName1> f3 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f3 = 2 and f3 between 1 and 4;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
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
     <FieldName1> f3 </FieldName1>
     <CompOp> GreaterThanEquals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     <Comp2Op> LessThanEquals </Comp2Op>
     <Operand2Ptr> VALUE </Operand2Ptr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f4 in (1,2) or f4 = 2;
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
       <FieldName1> f4 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f4 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f4 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where (f4 between 1 and 4) and f4 = 2;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f4 </FieldName1>
     <CompOp> GreaterThanEquals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     <Comp2Op> LessThanEquals </Comp2Op>
     <Operand2Ptr> VALUE </Operand2Ptr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f4 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f5 in ('1','2') and f5 = '1';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <LogOp> OR </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <FieldName1> f5 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f5 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f5 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f5 like 'N%' or f5 = 'NP';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f5 </FieldName1>
     <CompOp> Like </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f5 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f5 like 'N_h' and f6 = 'Nihar';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f5 </FieldName1>
     <CompOp> Like </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f6 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f6 = '1' or f6 in ('1','2');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f6 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <LogOp> OR </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <FieldName1> f6 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f6 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f6 = 'NP' or f6 like 'N%';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f6 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f6 </FieldName1>
     <CompOp> Like </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f6 like 'N_h' and f6 = 'NIHAR';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f6 </FieldName1>
     <CompOp> Like </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f6 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f7 = '2003-11-12' or f7 in ('2003-11-12','2003-11-15');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f7 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <LogOp> OR </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <FieldName1> f7 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f7 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f7 = '2003-11-15' and (f7 between '2003-11-12' and '2003-11-15');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f7 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f7 </FieldName1>
     <CompOp> GreaterThanEquals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     <Comp2Op> LessThanEquals </Comp2Op>
     <Operand2Ptr> VALUE </Operand2Ptr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f8 in ('03:21:00','03:21:08') and f8 = '03:21:08';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> AND </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <LogOp> OR </LogOp>
     <PRED-LEFT>
       <PREDICATE>
       <FieldName1> f8 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-LEFT>
     <PRED-RIGHT>
       <PREDICATE>
       <FieldName1> f8 </FieldName1>
       <CompOp> Equals </CompOp>
       <OperandPtr> VALUE </OperandPtr>
       </PREDICATE>
     </PRED-RIGHT>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f8 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where (f8 between '03:21:00' and '03:21:08') or f8='03:21:00';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f8 </FieldName1>
     <CompOp> GreaterThanEquals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     <Comp2Op> LessThanEquals </Comp2Op>
     <Operand2Ptr> VALUE </Operand2Ptr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f8 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
Statement Executed
