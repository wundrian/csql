CREATE TABLE vikas (fld5 INT  NOT NULL , name1 CHAR (32));
CREATE INDEX vikas_idx1_Primary on vikas (  fld5  )  HASH  UNIQUE;
SET AUTOCOMMIT OFF;
INSERT INTO vikas VALUES(1, 'Lakshya1');
INSERT INTO vikas VALUES(2, 'Lakshya2');
INSERT INTO vikas VALUES(3, 'raksha3');
COMMIT;
INSERT INTO vikas VALUES(4, 'Lakshya4');
INSERT INTO vikas VALUES(5, 'Lakshya5');
INSERT INTO vikas VALUES(6, 'Lakshya6');
COMMIT;
INSERT INTO vikas VALUES(7, 'Lakshya7');
INSERT INTO vikas VALUES(8, 'Lakshya8');
INSERT INTO vikas VALUES(9, 'raksha9');
COMMIT;
INSERT INTO vikas VALUES(10, 'Lakshya10');
COMMIT;
