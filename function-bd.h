#ifndef FUNCTION_BD_H
#define FUNCTION_BD_H
#include "struc.h"
#include <mysql/mysql.h>
User* createUser(MYSQL * db,User * user);
Event*createEvent(MYSQL * db,Event * event);
Ticket *createTicket(MYSQL *db,Ticket *ticket, Session * session, User *user);
void createReservation(MYSQL * db, User * user, Place *  place, Plat * plat);
Plat * createPlat(MYSQL * db, Plat *  plat, Event * event);
Place * createPlace(MYSQL * db, Place *  place, Event * event);
Session * createSession(MYSQL * db,Session * session);
Film * createFilm(MYSQL * db,Film * film,  Session *  session);
Event *updateEvent(MYSQL *db, Event *event);
void deleteEvent(MYSQL *db, Event * event);
bool authentiferUser(MYSQL *db, User *user);
void listerEvent(MYSQL *db);
void getPlatByEventLabel(MYSQL *db,char eventLabel[20]);
Event * getEventByLabel(MYSQL *db,char *eventLabel);
Plat * getPlatByLabel(MYSQL *db,char * platLabel);
User * getUserByFirstEmail(MYSQL *db,char * email);
void getFilmByDate(MYSQL *db,char * date);
Session * getSessionByFilm(MYSQL *db,char *film);
#endif