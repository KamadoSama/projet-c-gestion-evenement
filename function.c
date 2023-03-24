#include "struc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
// Event * addPlatToEvent(Plat * plat, Event * event){
//     event->plat[event->nbrPlat] = plat;
//     event->nbrPlat++;
//     return event;
// }

Event * addPlaceToEvent(Place * place, Event * event){
    event->place[event->nbrPlace] = place;
    event->nbrPlace++;
    return event;
}

Event * addTicketToEvent(Ticket * ticket, Event * event){
    event->ticket[event->nbrTicket] = ticket;
    event->nbrTicket++;
    return event;
}

Session * addFilmToSession(Film * film, Session * session){
    session->film[session->nbrFilm] = film;
    session->nbrFilm++;
    return session;
}
Event * addSessionToEvent(Session * session, Event * event){
    event->session[event->nbrSession] = session;
    event->nbrSession++;
    return event;
}

// void deletePlatFromEvent(Plat * plat, Event * event) {
//     int i;
//     for (i = 0; i < event->nbrPlat; i++) {
//         if (event->plat[i] == plat) {
//             for (int j = i; j < event->nbrPlat - 1; j++) {
//                 event->plat[j] = event->plat[j + 1];
//             }
//             event->nbrPlat--;
//             event->plat[event->nbrPlat] = NULL;
//             break;
//         }
//     }
// }

void deletePlaceFromEvent(Place * place, Event * event) {
    int i;
    for (i = 0; i < event->nbrPlace; i++) {
        if (event->place[i] == place) {
            for (int j = i; j < event->nbrPlace - 1; j++) {
                event->place[j] = event->place[j + 1];
            }
            event->nbrPlace--;
            event->place[event->nbrPlace] = NULL;
            break;
        }
    }
}

void deleteTicketFromEvent(Ticket * ticket, Event * event) {
    int i;
    for (i = 0; i < event->nbrTicket; i++) {
        if (event->ticket[i] == ticket) {
            for (int j = i; j < event->nbrTicket - 1; j++) {
                event->ticket[j] = event->ticket[j + 1];
            }
            event->nbrTicket--;
            event->ticket[event->nbrTicket] = NULL;
            break;
        }
    }
}

void deleteSessionFromEvent(Session * session, Event * event) {
    int i;
    for (i = 0; i < event->nbrSession; i++) {
        if (event->session[i] == session) {
            for (int j = i; j < event->nbrSession - 1; j++) {
                event->session[j] = event->session[j + 1];
            }
            event->nbrSession--;
            event->session[event->nbrSession] = NULL;
            break;
        }
    }
}
void printUser(User* user) {
    printf("ID: %d\n", user->id);
    printf("Prénom: %s\n", user->firstName);
    printf("Nom: %s\n", user->lastName);
    printf("Rôle: %s\n", user->rule);
    printf("Email: %s\n", user->email);
    printf("Mot de passe: %s\n", user->password);
}

void printEvent(Event* event) {
    printf("ID: %d\n", event->id);
    printf("Type: %s\n", event->type);
    printf("Lieu: %s\n", event->lieu);
    printf("Label: %s\n", event->label);
    printf("Date de l'événement: %s\n", event->dateEvent);
    printf("Nombre de places: %d\n", event->nbrPlace);
    printf("Nombre de plats: %d\n", event->nbrPlat);
    printf("Nombre de sessions: %d\n", event->nbrSession);
}

void printSession(Session* session) {
    printf("ID: %d\n", session->id);
    printf("Nom: %s\n", session->name);
    printf("Date de la session: %s\n", session->dateSession);
    printf("Nombre de films: %d\n", session->nbrFilm);
}

void printFilm(Film* film) {
    printf("ID: %d\n", film->id);
    printf("Titre: %s\n", film->titre);
    printf("Description: %s\n", film->description);
    printf("Auteur: %s\n", film->auteur);
}

