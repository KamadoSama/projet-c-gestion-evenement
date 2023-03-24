#ifndef STRUC_H
#define STRUC_H
typedef struct user User;
typedef struct place Place;
typedef struct ticket Ticket;
typedef struct plat Plat;
typedef struct event Event;
typedef struct session Session;
typedef struct film Film;
typedef struct user{
    int id;
    char firstName[100];
    char lastName[100];
    char rule[100];
    char email[100];
    char password[100];
    Place** place;
    Ticket** ticket;
    Plat** plat;
} User;
typedef struct place{
    int id;
    int number;
    User* user;
    Event* event;
} Place;

typedef struct film{
    int id;
    char titre[100];
    char description[100];
    char auteur[100];
    Session* session;
} Film;

typedef struct ticket
{
    int id;
    int number;
    char dateTicket[100];
    User* user;
    Event * event;
} Ticket;

typedef struct event 
{
   int id;
   char type[100];
   char lieu[100];
   char label[100];
   char dateEvent[100];
   int nbrPlat;
   int nbrPlace;
   int nbrTicket;
   int nbrSession;
   Session** session;
   Place** place;
   Ticket** ticket;
   Plat **plat;
} Event;

typedef struct plat{
    int id;
    char label[100];
    User* user;
    Event *event;
} Plat;

typedef struct session
{
    int id;
    int nbrFilm;
    char name[100];
    char dateSession[100];
    Event * event;
    Film **film;
} Session;
#endif