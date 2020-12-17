/*==============================================================*/
/* DBMS name:      MySQL 5.0                                    */
/* Created on:     2018/7/30 14:34:58                           */
/*==============================================================*/


drop table if exists t_ammeter;

drop table if exists t_class;

drop table if exists t_class_teacher;

drop table if exists t_dorrm;

drop table if exists t_id;

drop table if exists t_student;

drop table if exists t_teacher;

/*==============================================================*/
/* Table: t_ammeter                                             */
/*==============================================================*/
create table t_ammeter
(
   id                   int,
   left_count           decimal(3,2)
);

/*==============================================================*/
/* Table: t_class                                               */
/*==============================================================*/
create table t_class
(
   id                   int not null,
   cname                varchar(200),
   loc                  varchar(200),
   t_id                 int not null,
   primary key (id),
   unique key UNQ_CLASS_TID (t_id)
);

/*==============================================================*/
/* Table: t_class_teacher                                       */
/*==============================================================*/
create table t_class_teacher
(
   id                   int not null,
   name                 varchar(200),
   primary key (id)
);

/*==============================================================*/
/* Table: t_dorrm                                               */
/*==============================================================*/
create table t_dorrm
(
   id                   int not null,
   loc                  varchar(200),
   primary key (id)
);

/*==============================================================*/
/* Table: t_id                                                  */
/*==============================================================*/
create table t_id
(
   id                   int not null,
   t_id                 int,
   c_id                 int,
   primary key (id)
);

/*==============================================================*/
/* Table: t_student                                             */
/*==============================================================*/
create table t_student
(
   id                   int not null,
   name                 varchar(200),
   dorm_id              int,
   class_id             int,
   primary key (id)
);

/*==============================================================*/
/* Table: t_teacher                                             */
/*==============================================================*/
create table t_teacher
(
   id                   int not null,
   name                 varchar(200),
   teach                varchar(200),
   primary key (id)
);

alter table t_ammeter add constraint FK_Reference_7 foreign key (id)
      references t_dorrm (id) on delete restrict on update restrict;

alter table t_class add constraint FK_Reference_1 foreign key (t_id)
      references t_class_teacher (id) on delete restrict on update restrict;

alter table t_id add constraint FK_Reference_3 foreign key (t_id)
      references t_teacher (id) on delete restrict on update restrict;

alter table t_id add constraint FK_Reference_4 foreign key (c_id)
      references t_class (id) on delete restrict on update restrict;

alter table t_student add constraint FK_Reference_5 foreign key (dorm_id)
      references t_dorrm (id) on delete restrict on update restrict;

alter table t_student add constraint FK_Reference_6 foreign key (class_id)
      references t_class (id) on delete restrict on update restrict;

