/**
 * @file function-bd.h 
 * @brief le fichier qui contient les déclarations de toutes les fonctions
*/

#ifndef FUNCTION_BD_H
#define FUNCTION_BD_H
#include "struc.h"
#include <mysql/mysql.h>
/**
    @brief Crée un nouvel utilisateur dans la base de données.
    @param db Un pointeur vers la connexion de base de données.
    @param user Un pointeur vers l'utilisateur à créer.
    @return Un pointeur vers l'utilisateur créé.
*/
User* createUser(MYSQL * db,User * user);
/**
    @brief Crée un nouvel événement dans la base de données.
    @param db Un pointeur vers la connexion de base de données.
    @param event Un pointeur vers l'événement à créer.
    @param user Un pointeur vers l'utilisateur qui a créé l'événement.
    @return Un pointeur vers l'événement créé.
*/
Event*createEvent(MYSQL * db,Event * event,User * user);
/**
    @brief Crée un nouveau ticket dans la base de données.
    @param db Un pointeur vers la connexion de base de données.
    @param ticket Un pointeur vers le ticket à créer.
    @param session Un pointeur vers la session associée au ticket.
    @param user Un pointeur vers l'utilisateur qui achète le ticket.
    @return Un pointeur vers le ticket créé.
*/
Ticket *createTicket(MYSQL *db,Ticket *ticket, Session * session, User *user);
/**
    @brief Crée une nouvelle réservation dans la base de données.
    @param db Un pointeur vers la connexion de base de données.
    @param user Un pointeur vers l'utilisateur qui effectue la réservation.
    @param place Un pointeur vers la place réservée.
    @param plat Un pointeur vers le plat réservé.
*/
void createReservation(MYSQL * db, User * user, Place *  place, Plat * plat);
/**

    @brief Crée un nouveau plat dans la base de données.
    @param db Un pointeur vers la connexion de base de données.
    @param plat Un pointeur vers le plat à créer.
    @param event Un pointeur vers l'événement associé au plat.
    @return Un pointeur vers le plat créé.
*/
Plat * createPlat(MYSQL * db, Plat *  plat, Event * event);
/**
    @brief Crée une nouvelle place dans la base de données.
    @param db Un pointeur vers la connexion de base de données.
    @param place Un pointeur vers la place à créer.
    @param event Un pointeur vers l'événement associé à la place.
    @return Un pointeur vers la place créée.
*/
Place * createPlace(MYSQL * db, Place *  place, Event * event);
/**
    @brief Crée une nouvelle session dans la base de données.
    @param db Un pointeur vers la connexion de base de données.
    @param session Un pointeur vers la session à créer.
    @return Un pointeur vers la session créée.
*/
Session * createSession(MYSQL * db,Session * session);
/**
    @brief Crée un nouveau film dans la base de données.
    Cette fonction crée un nouveau film dans la base de données en utilisant les informations passées en paramètre.
    Si l'opération est réussie, la fonction renvoie le pointeur vers le film créé, sinon elle renvoie NULL.
    @param db Le pointeur vers la connexion à la base de données.
    @param film Le pointeur vers la structure du film à créer.
    @param session Le pointeur vers la structure de la session à laquelle ajouter le film.
    @return Le pointeur vers la structure du film créé, ou NULL si l'opération a échoué.
*/
Film * createFilm(MYSQL * db,Film * film,  Session *  session);
/**
    @brief Authentifie un utilisateur dans la base de données.
    Cette fonction vérifie si les informations d'authentification de l'utilisateur passées en paramètre correspondent à un utilisateur dans la base de données.
    Si l'utilisateur est authentifié, la fonction renvoie true, sinon elle renvoie false.
    @param db Le pointeur vers la connexion à la base de données.
    @param user Le pointeur vers la structure de l'utilisateur à authentifier.
    @return true si l'utilisateur est authentifié, false sinon.
*/
bool authentiferUser(MYSQL *db, User *user);
/**
    @brief Affiche la liste des événements dans la base de données.
    Cette fonction affiche la liste des événements stockés dans la base de données en utilisant le pointeur vers la connexion à la base de données passé en paramètre.
    @param db Le pointeur vers la connexion à la base de données.
*/
void listerEvent(MYSQL *db);
/**
    @brief Affiche la liste des plats associés à un événement donné.
    Cette fonction affiche la liste des plats associés à l'événement dont le label est passé en paramètre.
    @param db Le pointeur vers la connexion à la base de données.
    @param eventLabel Le label de l'événement dont on veut afficher les plats associés.
*/
void getPlatByEventLabel(MYSQL *db,char eventLabel[20]);
/**
    @brief Récupère un événement à partir de son libellé.
    @param db Pointeur vers la base de données.
    @param eventLabel Libellé de l'événement.
    @return Un pointeur vers l'événement correspondant, NULL si aucun événement n'a été trouvé.
*/
Event * getEventByLabel(MYSQL *db,char *eventLabel);
/**
    @brief Récupère un plat à partir de son libellé.
    @param db Pointeur vers la base de données.
    @param platLabel Libellé du plat.
    @return Un pointeur vers le plat correspondant, NULL si aucun plat n'a été trouvé.
*/
Plat * getPlatByLabel(MYSQL *db,char * platLabel);
/**
    @brief Récupère un utilisateur à partir de son adresse email.
    @param db Pointeur vers la base de données.
    @param email Adresse email de l'utilisateur.
    @return Un pointeur vers l'utilisateur correspondant, NULL si aucun utilisateur n'a été trouvé.
*/
User * getUserByFirstEmail(MYSQL *db,char * email);
/**
    @brief Récupère tous les films jouant à une certaine date.
    @param db Pointeur vers la base de données.
    @param date Date à laquelle les films doivent être joués (au format "YYYY-MM-DD").
*/
void getFilmByDate(MYSQL *db,char * date);
/**
    @brief Récupère la session d'un film donné.
    @param db Pointeur vers la base de données.
    @param film Titre du film.
    @return Un pointeur vers la session correspondante, NULL si aucune session n'a été trouvée.
*/
Session * getSessionByFilm(MYSQL *db,char *film);
#endif