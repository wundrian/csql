echo create table t1(f1 int, f2 int);
Statement Executed
echo create index hashidxt1f1 on t1(f1) hash;
Statement Executed
echo create index hashidxt1f2 on t1(f2) hash;
Statement Executed
echo create table t2(f1 int, f2 int);
Statement Executed
echo create index hashidxt2f1 on t2(f1) hash;
Statement Executed
echo create index hashidxt2f2 on t2(f2) hash;
Statement Executed
echo explain plan select * from t1,t2;
 <JOIN-NODE>
 <TYPE> INNER_JOIN </TYPE>
 <LEFT>
   <TABLE-NODE>
   <NAME> t1 </NAME>
   <ScanType> TableScan </ScanType>
   </TABLE-NODE>
 </LEFT>
 <RIGHT>
   <TABLE-NODE>
   <NAME> t2 </NAME>
   <ScanType> TableScan </ScanType>
   </TABLE-NODE>
 </RIGHT>
 </JOIN-NODE>
echo explain plan select * from t1 left join t2 on t1.f1=t2.f1;
 <JOIN-NODE>
 <TYPE> LEFT_JOIN </TYPE>
 <PREDICATE>
 <FieldName1> t1.f1 </FieldName1>
 <FieldName2> t2.f1 </FieldName2>
 <CompOp> Equals </CompOp>
 </PREDICATE>
 <LEFT>
   <TABLE-NODE>
   <NAME> t1 </NAME>
   <ScanType> TableScan </ScanType>
   </TABLE-NODE>
 </LEFT>
 <RIGHT>
   <TABLE-NODE>
   <NAME> t2 </NAME>
   <ScanType> TableScan </ScanType>
   </TABLE-NODE>
 </RIGHT>
 </JOIN-NODE>
echo explain plan select * from t1 left join t2 on t1.f1<=t2.f1;
 <JOIN-NODE>
 <TYPE> LEFT_JOIN </TYPE>
 <PREDICATE>
 <FieldName1> t1.f1 </FieldName1>
 <FieldName2> t2.f1 </FieldName2>
 <CompOp> LessThanEquals </CompOp>
 </PREDICATE>
 <LEFT>
   <TABLE-NODE>
   <NAME> t1 </NAME>
   <ScanType> TableScan </ScanType>
   </TABLE-NODE>
 </LEFT>
 <RIGHT>
   <TABLE-NODE>
   <NAME> t2 </NAME>
   <ScanType> TableScan </ScanType>
   </TABLE-NODE>
 </RIGHT>
 </JOIN-NODE>
echo explain plan select * from t1 left join t2 on t1.f1!=t2.f1;
 <JOIN-NODE>
 <TYPE> LEFT_JOIN </TYPE>
 <PREDICATE>
 <FieldName1> t1.f1 </FieldName1>
 <FieldName2> t2.f1 </FieldName2>
 <CompOp> NotEquals </CompOp>
 </PREDICATE>
 <LEFT>
   <TABLE-NODE>
   <NAME> t1 </NAME>
   <ScanType> TableScan </ScanType>
   </TABLE-NODE>
 </LEFT>
 <RIGHT>
   <TABLE-NODE>
   <NAME> t2 </NAME>
   <ScanType> TableScan </ScanType>
   </TABLE-NODE>
 </RIGHT>
 </JOIN-NODE>
Statement Executed
Statement Executed
