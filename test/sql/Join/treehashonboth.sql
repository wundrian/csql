create index idx1 on t1(f1) tree;
create index idx2 on t2(f1) tree;
create index idx3 on t1(f2) hash;
create index idx4 on t2(f2) hash;
