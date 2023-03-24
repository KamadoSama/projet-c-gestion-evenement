#ifndef FUNCTION_H
#define FUNCTION_H
#include "struc.h"
Event * addPlatToEvent(Plat * plat, Event * event);
Event * addPlaceToEvent(Place * place, Event * event);
Event * addTicketToEvent(Ticket * ticket, Event * event);
Session * addFilmToSession(Film * film, Session * session);
Event * addSessionToEvent(Session * session, Event * event);
void deletePlatFromEvent(Plat * plat, Event * event);
void deletePlaceFromEvent(Place * place, Event * event);
void deleteTicketFromEvent(Ticket * ticket, Event * event) ;
void deleteSessionFromEvent(Session * session, Event * event);
void printUser(User* user);
void printEvent(Event* event);
void printSession(Session* session) ;
void printFilm(Film* film);
#endif