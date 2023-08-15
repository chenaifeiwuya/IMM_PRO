SELECT * FROM IMMSQL.t_user;
use IMMSQL;
#为用户信息表添加约束
describe IMMSQL.t_user;
alter table t_user alter column t_feeling set default '这个人很懒，什么也没写';
alter table t_user modify column t_name char(20) not null;
alter table t_user add password char(12) not null;

#创建好友表
use IMMSQL;
describe IMMSQL.t_friend;
create table t_friend(
idA int not null,
idB int not null,
foreign key(idA) references t_user(id),
foreign key(idB) references t_user(id)
);

alter table t_user change tel  tel char(11) not null;
alter table t_user change name  name char(20) not null;
alter table t_user change t_icon  icon varchar(50);
alter table t_user change feeling  feeling varchar(50) default "这个人太懒了，什么也没写。";
SHOW VARIABLES LIKE 'character_set_database';

insert into t_user (tel,password,name) values("18845621867","mmm959825","尘埃飞舞呀");

update t_user set feeling = '这个人太懒了，什么也没留下' where id=2;


#创建群聊数据库
create table t_group(
	groupId int primary key AUTO_INCREMENT,
    groupName varchar(50) not null unique,
    grouper int,
    foreign key(grouper) references t_user(id)
);