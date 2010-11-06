echo create table t1(f1 int, f2 int);
Statement Executed
echo create index hashidxt1f1 on t1(f1) hash;
Statement Executed
echo create index hashidxt1f2 on t1(f2) hash;
Statement Executed
echo explain plan select a.f1,b.f1 from t1 a, t1 b where a.f1=b.f1;
 <JOIN-NODE>
 <TYPE> INNER_JOIN </TYPE>
 <PREDICATE>
 <FieldName1> a.f1 </FieldName1>
 <FieldName2> b.f1 </FieldName2>
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
   <NAME> t1 </NAME>
   <ScanType> TableScan </ScanType>
   </TABLE-NODE>
 </RIGHT>
 </JOIN-NODE>
Statement Executed
