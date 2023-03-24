/*==============================================================*/ 

/* nom de sgbd : sybase sql anywhere 11 */ 

/* date de cr�ation : 10/03/2023 15:38:54 */ 

/*==============================================================*/ 

 
 

/*==============================================================*/ 

/* table : commander */ 

/*==============================================================*/ 

create table commander  

( 

use_id integer not null, 

pla_id integer not null, 

constraint pk_commander primary key clustered (use_id, pla_id) 

); 

 
 
 

/*==============================================================*/ 

/* table : event */ 

/*==============================================================*/ 

create table event  

( 

id integer not null auto_increment, 

type char(255) null, 

place char(255) null, 

date_event timestamp null, 

label char(255) null, 

constraint pk_event primary key (id) 

); 

 
 

/*==============================================================*/ 

/* table : film */ 

/*==============================================================*/ 

create table film  

( 

ses_id integer null, 

id integer  auto_increment, 

titre char(255) null, 

description char(255) null, 

auteur char(255) null,
constraint pk_event primary key (id)

); 

 
 

/*==============================================================*/ 

/* table : place */ 

/*==============================================================*/ 

create table place  

( 

id integer not null auto_increment, 

eve_id integer null, 

number integer null, 

constraint pk_place primary key (id) 

); 

 
 
 

/*==============================================================*/ 

/* table : plat */ 

/*==============================================================*/ 

create table plat  

( 

id integer not null auto_increment, 

eve_id integer null, 

number integer null, 

constraint pk_plat primary key (id) 

); 

 
 
 
 
 
 

/*==============================================================*/ 

/* table : reserver */ 

/*==============================================================*/ 

create table reserver  

( 

use_id integer not null auto_increment, 

pla_id integer not null, 

constraint pk_reserver primary key clustered (use_id, pla_id) 

); 

 
 
 
 
 

/*==============================================================*/ 

/* table : session */ 

/*==============================================================*/ 

create table session 

( 

id integer not null auto_increment, 

eve_id integer null, 

name char(255) null, 

date_session char(255) null, 

constraint pk_session primary key (id) 

); 

 
 
 

/*==============================================================*/ 

/* table : ticket */ 

/*==============================================================*/ 

create table ticket  

( 

id integer not null auto_increment, 

use_id integer null, 

eve_id integer null, 

number integer null, 

date_ticket integer null, 

constraint pk_ticket primary key (id) 

); 

 
 
 

/*==============================================================*/ 

/* table : user */ 

/*==============================================================*/ 

create table user 

( 

id integer not null auto_increment, 

fist_name char(255) null, 

last_name char(255) null, 

rule char(255) null, 

email char(255) null, 

password char(255) null, 

constraint pk_user primary key (id) 

); 

 
 

alter table commander 

add constraint fk_commande_relation__user foreign key (use_id) 

references user (id) 

on update restrict 

on delete restrict; 

 
 

alter table commander 

add constraint fk_commande_relation__plat foreign key (pla_id) 

references plat (id) 

on update restrict 

on delete restrict; 

 
 

alter table film 

add constraint fk_film_relation__session foreign key (ses_id) 

references session (id) 

on update restrict 

on delete restrict; 

 
 

alter table place 

add constraint fk_place_relation__event foreign key (eve_id) 

references event (id) 

on update restrict 

on delete restrict; 

 
 

alter table plat 

add constraint fk_plat_relation__event foreign key (eve_id) 

references event (id) 

on update restrict 

on delete restrict; 

 
 

alter table reserver 

add constraint fk_reserver_relation__user foreign key (use_id) 

references user (id) 

on update restrict 

on delete restrict; 

 
 

alter table reserver 

add constraint fk_reserver_relation__place foreign key (pla_id) 

references place (id) 

on update restrict 

on delete restrict; 

 
 

alter table session 

add constraint fk_session_relation__event foreign key (eve_id) 

references event (id) 

on update restrict 

on delete restrict; 

 
 

alter table ticket 

add constraint fk_ticket_relation__user foreign key (use_id) 

references user (id) 

on update restrict 

on delete restrict; 

 
 

alter table ticket 

add constraint fk_ticket_relation__event foreign key (eve_id) 

references event (id) 

on update restrict 

on delete restrict; 

 
 
 

 
 

 