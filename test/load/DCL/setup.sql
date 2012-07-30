create table registry (uid char(15) not null,
passwd char(15),
email char(40),
address char(200),
phone char(15), PRIMARY KEY (uid));
create user mbickel password 'test';
grant all privileges on registry to mbickel;

insert into registry values ('1', 'abcdefg1234', 'xzy@example.com', 'Poststreetaddress 45a, Worthington', '0049 45678');
insert into registry values ('2', 'abcdefg1234', 'xzy@example.com', 'Poststreetaddress 45a, Worthington', '0049 45678');
insert into registry values ('3', 'abcdefg1234', 'xzy@example.com', 'Poststreetaddress 45a, Worthington', '0049 45678');
insert into registry values ('4', 'abcdefg1234', 'xzy@example.com', 'Poststreetaddress 45a, Worthington', '0049 45678');
insert into registry values ('5', 'abcdefg1234', 'xzy@example.com', 'Poststreetaddress 45a, Worthington', '0049 45678');
insert into registry values ('6', 'abcdefg1234', 'xzy@example.com', 'Poststreetaddress 45a, Worthington', '0049 45678');
insert into registry values ('7', 'abcdefg1234', 'xzy@example.com', 'Poststreetaddress 45a, Worthington', '0049 45678');

quit;
