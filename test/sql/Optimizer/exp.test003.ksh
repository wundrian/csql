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
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
Statement Executed: Rows Affected = 1
echo explain plan select * from t1;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 = 2;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f1 < 3;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f1 </FieldName1>
   <CompOp> LessThan </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f2 = 22;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f2 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f2 > 33;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f2 </FieldName1>
   <CompOp> GreaterThan </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f3 = 333;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f3 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f3 <> 333;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f3 </FieldName1>
   <CompOp> NotEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f4 = 4444;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f4 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f4 != 4444;
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f4 </FieldName1>
   <CompOp> NotEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f5 = 'CSQL3';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f5 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f5 <= 'CSQL3';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f5 </FieldName1>
   <CompOp> LessThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f6 = 'Lakshya3';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f6 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f6 >= 'Lakshya3';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f6 </FieldName1>
   <CompOp> GreaterThanEquals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f7 = '2003-11-12';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f7 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f7 > '2003-11-12';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f7 </FieldName1>
   <CompOp> GreaterThan </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f8 = '03:21:00';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> HashScan </ScanType>
   <PREDICATE>
   <FieldName1> f8 </FieldName1>
   <CompOp> Equals </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
echo explain plan select * from t1 where f8 < '03:21:00';
 <TABLE-NODE>
 <NAME> t1 </NAME>
 <ScanType> TableScan </ScanType>
   <PREDICATE>
   <FieldName1> f8 </FieldName1>
   <CompOp> LessThan </CompOp>
   <OperandPtr> VALUE </OperandPtr>
   </PREDICATE>
 </TABLE-NODE>
Statement Executed
