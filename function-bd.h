#ifndef FUNCTION_BD_H
#define FUNCTION_BD_H
#include "struc.h"
#include <mysql/mysql.h>
User* createUser(MYSQL * db,User * user);
Event*createEvent(MYSQL * db,Event * event);
User *getUsers(MYSQL *db);
Ticket *createTicket(MYSQL *db,Ticket *ticket, Event * event, User *user);
void createReservation(MYSQL * db, User * user, Place *  place, Plat * plat);
void createCommander(MYSQL * db, User * user, Plat * plat);
Plat * createPlat(MYSQL * db, Plat *  plat, Event * event);
Place * createPlace(MYSQL * db, Place *  place, Event * event);
Session * createSession(MYSQL * db,Session * session,  Event *  event);
Film * createFilm(MYSQL * db,Film * film,  Session *  session);
Event *updateEvent(MYSQL *db, Event *event);
void deleteEvent(MYSQL *db, Event * event);
//Plat ** getPlatByEventId(MYSQL *db, Event * event);
//Session ** getSessionByEventId(MYSQL *db, Event * event);
//Place ** getPlaceByEventId(MYSQL *db, Event * event);
Ticket * getTicketByUserId(MYSQL *db, User * user, Event **event);
Event * getEvents(MYSQL *db);
Film ** getFilmBySessionId(MYSQL *db, Session * session);
bool *authentiferUser(MYSQL *db, User *user);
void listerEvent(MYSQL *db);
void getPlatByEventLabel(MYSQL *db,char eventLabel[20]);
Event * getEventByLabel(MYSQL *db,char *eventLabel);
Plat * getPlatByLabel(MYSQL *db,char * platLabel);
User * getUserByFirstName(MYSQL *db,char * first_name);
#endif