echo create table t1(f1 tinyint, f2 smallint, f3 int, f4 bigint, f5 char(10), f6 varchar(10), f7 date, f8 time, f9 float, f10 double, f11 timestamp);
Statement Executed
echo create index treetiny on t1(f1) tree;
Statement Executed
echo create index treesmall on t1(f2) tree;
Statement Executed
echo create index treeint on t1(f3) tree;
Statement Executed
echo create index treebig on t1(f4) tree;
Statement Executed
echo create index treechar on t1(f5) tree;
Statement Executed
echo create index treevarchar on t1(f6) tree;
Statement Executed
echo create index treedate on t1(f7) tree;
Statement Executed
echo create index treetime on t1(f8) tree;
Statement Executed
echo create index treefloat on t1(f9) tree;
Statement Executed
echo create index treedouble on t1(f10) tree;
Statement Executed
echo create index treetimestamp on t1(f11) tree;
Statement Executed
echo explain plan select * from t1;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 in (0,2,4);
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
 </TABLE-NODE>
echo explain plan select * from t1 where f1 between 2 and 4;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> GreaterThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   <Comp2Op> LessThanEquals </Comp2Op>
   <Operand2Ptr> VALUE </Operand2Ptr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f2 in (0,2,4);
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
 </TABLE-NODE>
echo explain plan select * from t1 where f2 between 2 and 4;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f2 </FieldName1>
   <CompOp> GreaterThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   <Comp2Op> LessThanEquals </Comp2Op>
   <Operand2Ptr> VALUE </Operand2Ptr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f3 in (1,2);
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
     <FieldName1> f3 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f3 between 1 and 4;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f3 </FieldName1>
   <CompOp> GreaterThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   <Comp2Op> LessThanEquals </Comp2Op>
   <Operand2Ptr> VALUE </Operand2Ptr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f4 in (1,2);
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
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
 </TABLE-NODE>
echo explain plan select * from t1 where f4 between 1 and 4;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f4 </FieldName1>
   <CompOp> GreaterThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   <Comp2Op> LessThanEquals </Comp2Op>
   <Operand2Ptr> VALUE </Operand2Ptr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f5 in ('1','2');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
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
 </TABLE-NODE>
echo explain plan select * from t1 where f5 like 'N%';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f5 </FieldName1>
   <CompOp> Like </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f5 like 'N_h';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f5 </FieldName1>
   <CompOp> Like </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f6 in ('1','2');
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
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f6 like 'N%';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f6 </FieldName1>
   <CompOp> Like </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f6 like 'N_h';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f6 </FieldName1>
   <CompOp> Like </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f7 in ('2003-11-12','2003-11-15');
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
     <FieldName1> f7 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f7 between '2003-11-12' and '2003-11-15';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f7 </FieldName1>
   <CompOp> GreaterThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   <Comp2Op> LessThanEquals </Comp2Op>
   <Operand2Ptr> VALUE </Operand2Ptr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f8 in ('03:21:00','03:21:08');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
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
 </TABLE-NODE>
echo explain plan select * from t1 where f8 between '03:21:00' and '03:21:08';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f8 </FieldName1>
   <CompOp> GreaterThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   <Comp2Op> LessThanEquals </Comp2Op>
   <Operand2Ptr> VALUE </Operand2Ptr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f9 in ('2.7','3.7');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f9 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f9 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f9 between '2.7' and '3.7';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f9 </FieldName1>
   <CompOp> GreaterThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   <Comp2Op> LessThanEquals </Comp2Op>
   <Operand2Ptr> VALUE </Operand2Ptr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f10 in ('2.7','3.7');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f10 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f10 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f10 between '2.7' and '3.7';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f10 </FieldName1>
   <CompOp> GreaterThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   <Comp2Op> LessThanEquals </Comp2Op>
   <Operand2Ptr> VALUE </Operand2Ptr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f11 in ('2003-11-12 01:01:01','2003-11-18 01:01:01');
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <LogOp> OR </LogOp>
   <PRED-LEFT>
     <PREDICATE>
     <FieldName1> f11 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-LEFT>
   <PRED-RIGHT>
     <PREDICATE>
     <FieldName1> f11 </FieldName1>
     <CompOp> Equals </CompOp>
     <OperandPtr> VALUE </OperandPtr>
     </PREDICATE>
   </PRED-RIGHT>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f11 between '2003-11-12 01:01:01' and '2003-11-18 01:01:01';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TreeScan </ScanType>
   <PREDICATE>
   <FieldName1> f11 </FieldName1>
   <CompOp> GreaterThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   <Comp2Op> LessThanEquals </Comp2Op>
   <Operand2Ptr> VALUE </Operand2Ptr>
   </PREDICATE>
 </TABLE-NODE>
Statement Executed
