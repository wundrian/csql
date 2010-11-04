cacheverify -t t1

Number of Records:
-------------------+-------------------+-------------------+
  Data             |  In CSQL          |  In TargetDB      |
-------------------+-------------------+-------------------+
  No. Of Records   |  5                |  5                |
-------------------+-------------------+-------------------+
cacheverify -t t1 -p

Number of Records:
-------------------+-------------------+-------------------+
  Data             |  In CSQL          |  In TargetDB      |
-------------------+-------------------+-------------------+
  No. Of Records   |  5                |  5                |
-------------------+-------------------+-------------------+

Primary key field name is 'f4'

Missing Records: Marked by 'X'
-------------------+-------------------+-------------------+
  Primary Key      |  In CSQL          |  In Target DB     |
-------------------+-------------------+-------------------+
  No missing Records in either of the databases            |
-------------------+-------------------+-------------------+
cacheverify -t t1 -f

Number of Records:
-------------------+-------------------+-------------------+
  Data             |  In CSQL          |  In TargetDB      |
-------------------+-------------------+-------------------+
  No. Of Records   |  5                |  5                |
-------------------+-------------------+-------------------+

Primary key field name is 'f4'

Missing Records: Marked by 'X'
-------------------+-------------------+-------------------+
  Primary Key      |  In CSQL          |  In Target DB     |
-------------------+-------------------+-------------------+
  No missing Records in either of the databases            |
-------------------+-------------------+-------------------+

Inconsistent Records for the same key:
-------------------+-------------------+-------------------+-------------------+
  Primary Key      |  Field Name       |  In CSQL          |  In Trgt DB       |
-------------------+-------------------+-------------------+-------------------+
                  The data is consistent in both the databases                 |
-------------------+-------------------+-------------------+-------------------+
updating 2 records in csql through gateway
cacheverify -t t1 -f

Number of Records:
-------------------+-------------------+-------------------+
  Data             |  In CSQL          |  In TargetDB      |
-------------------+-------------------+-------------------+
  No. Of Records   |  5                |  5                |
-------------------+-------------------+-------------------+

Primary key field name is 'f4'

Missing Records: Marked by 'X'
-------------------+-------------------+-------------------+
  Primary Key      |  In CSQL          |  In Target DB     |
-------------------+-------------------+-------------------+
  No missing Records in either of the databases            |
-------------------+-------------------+-------------------+

Inconsistent Records for the same key:
-------------------+-------------------+-------------------+-------------------+
  Primary Key      |  Field Name       |  In CSQL          |  In Trgt DB       |
-------------------+-------------------+-------------------+-------------------+
                  The data is consistent in both the databases                 |
-------------------+-------------------+-------------------+-------------------+
deleting 2 records in csql through gateway
cacheverify -t t1 -p

Number of Records:
-------------------+-------------------+-------------------+
  Data             |  In CSQL          |  In TargetDB      |
-------------------+-------------------+-------------------+
  No. Of Records   |  3                |  3                |
-------------------+-------------------+-------------------+

Primary key field name is 'f4'

Missing Records: Marked by 'X'
-------------------+-------------------+-------------------+
  Primary Key      |  In CSQL          |  In Target DB     |
-------------------+-------------------+-------------------+
  No missing Records in either of the databases            |
-------------------+-------------------+-------------------+
updating 2 records in mysql
cacheverify -t t1 -f

Number of Records:
-------------------+-------------------+-------------------+
  Data             |  In CSQL          |  In TargetDB      |
-------------------+-------------------+-------------------+
  No. Of Records   |  3                |  3                |
-------------------+-------------------+-------------------+

Primary key field name is 'f4'

Missing Records: Marked by 'X'
-------------------+-------------------+-------------------+
  Primary Key      |  In CSQL          |  In Target DB     |
-------------------+-------------------+-------------------+
  No missing Records in either of the databases            |
-------------------+-------------------+-------------------+

Inconsistent Records for the same key:
-------------------+-------------------+-------------------+-------------------+
  Primary Key      |  Field Name       |  In CSQL          |  In Trgt DB       |
-------------------+-------------------+-------------------+-------------------+
  Govind           |  t1.f5            |  100.111000       |  150.000000       |
  Gopal            |  t1.f5            |  200.222000       |  150.000000       |
-------------------+-------------------+-------------------+-------------------+
deleting 2 records in mysql
cacheverify -t t1 -p

Number of Records:
-------------------+-------------------+-------------------+
  Data             |  In CSQL          |  In TargetDB      |
-------------------+-------------------+-------------------+
  No. Of Records   |  3                |  1                |
-------------------+-------------------+-------------------+

Primary key field name is 'f4'

Missing Records: Marked by 'X'
-------------------+-------------------+-------------------+
  Primary Key      |  In CSQL          |  In Target DB     |
-------------------+-------------------+-------------------+
  Govind           |                   |  X                |
  Gopal            |                   |  X                |
-------------------+-------------------+-------------------+
