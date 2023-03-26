#include "struc.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

User* saisieUser(){
    printf("Création de l'utilisateur\n");
    User *user = malloc(sizeof(User));
    
    printf("Prénom : ");
    scanf("%s", user->firstName);
    while(getchar() != '\n');
    
    printf("Nom : ");
    scanf("%s", user->lastName);
    while(getchar() != '\n');
    
    printf("Rôle : ");
    scanf("%s", user->rule);
    while(getchar() != '\n');
    
    printf("Email : ");
    scanf("%s", user->email);
    while(getchar() != '\n');
    
    printf("Mot de passe : ");
    scanf("%s", user->password);
    while(getchar() != '\n');
    
    user->id = -1; // initialisation de l'ID à -1    
    return user;
}
User* authenUser(){
    printf("Se connecter\n");
    User *user = malloc(sizeof(User));
    
    printf("email : ");
    scanf("%s", user->email);
    while(getchar() != '\n');
    
    printf("Mot de passe : ");
    scanf("%s", user->password);
    while(getchar() != '\n');
    
    user->id = -1; // initialisation de l'ID à -1    
    return user;
}

Event* saisieEvent() {
    printf("Création de l'événement\n");
    Event *event = malloc(sizeof(Event));
    
    printf("Type d'événement : ");
    scanf("%s", event->type);
    while(getchar() != '\n');
    
    printf("Lieu : ");
    scanf("%s", event->lieu);
    while(getchar() != '\n');
    
    printf("Label : ");
    scanf("%s", event->label);
    while(getchar() != '\n');
    
    printf("Date de l'événement(AAAA-MM-JJ) : ");
    scanf("%s", event->dateEvent);
    while(getchar() != '\n');
    
    event->id=-1;
    event->nbrPlat=0;
    return event;
}

Plat * saisiePlat(){
    printf("Choisir votre plat\n");
    Plat *plat = malloc(sizeof(Plat));
    printf("Label : ");
    scanf("%s", plat->label);
    while(getchar() != '\n');
    return plat;
}

Session *saisieSession(){
    printf("Création d'une session sous la forme (Heure debut - Heure fin) exemple 9h-12h \n");
    Session *session = malloc(sizeof(Session));
    printf("Nom : ");
    scanf("%s", session->name);
    printf("Date (format jj/mm/aaaa) : ");
    scanf("%s", session->dateSession);
    session->nbrFilm = 0;
    return session;
}

Film *saisieFilm(){
    printf("Création d'un film\n");
    Film *film = malloc(sizeof(Film));
    printf("Titre : ");
    scanf("%s", film->titre);
    printf("Description : ");
    scanf("%s", film->description);
    printf("Auteur : ");
    scanf("%s", film->auteur);
    film->session = NULL;
    return film;
}

Place *saisiePlace(){
    printf("Choisir votre place\n");
    Place *place = malloc(sizeof(Place));
    printf("Numéro : ");
    scanf("%d", &place->number);
    place->user = NULL;
    place->event = NULL;
    return place;
}

Ticket *saisieTicket(){
    printf("Création d'un ticket\n");
    Ticket *ticket = malloc(sizeof(Ticket));
    printf("Numéro : ");
    scanf("%d", &ticket->number); 
    ticket->user = NULL;
    ticket->session = NULL;
    return ticket;
}

