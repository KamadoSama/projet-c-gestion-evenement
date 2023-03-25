#include <stdio.h>
#include <string.h>
#include "struc.h"
#include <mysql/mysql.h>

User *createUser(MYSQL *db, User *user)
{
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into user (fist_name, last_name, rule, email, password) values(\"%s\", \"%s\", \"%s\",\"%s\", \"%s\")", user->firstName, user->lastName, user->rule, user->email, user->password);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     result = mysql_store_result(db);
     row = mysql_fetch_row(result);
     user->id = atoi(row[0]);
}
void listerEvent(MYSQL *db)
{
    
     char query[] = "SELECT * FROM event";
    
     if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
     } else {
          MYSQL_RES *resultat = mysql_store_result(db);

          if (resultat == NULL) {
            fprintf(stderr, "%s\n", mysql_error(db));
          } else {
        
            MYSQL_FIELD *champ;
            
            printf("%s\t", "label");
            printf("\n");
            printf("%s\t", "---------");
            printf("\n");
           
            MYSQL_ROW ligne;
            
            while ((ligne = mysql_fetch_row(resultat))) {
               printf("%s\n",ligne[4]);
            }
            mysql_free_result(resultat);
        }
    }
}
void getPlatByEventLabel(MYSQL *db,char eventLabel[20]){
     char query[1000];
     sprintf(query, "select * from plat inner join event on plat.eve_id=event.id where event.label=\"%s\"", eventLabel);
     if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
     } else {
          MYSQL_RES *resultat = mysql_store_result(db);
          if (resultat == NULL) {
            fprintf(stderr, "%s\n", mysql_error(db));
          } else {
            MYSQL_FIELD *champ;
            while ((champ = mysql_fetch_field(resultat))) {
               printf("%s\t\t", champ->name);
            }
            printf("\n");            
            MYSQL_ROW ligne;
            while ((ligne = mysql_fetch_row(resultat))) {
               printf("%s\t\t%s\t\t%s\t\t%s\t\t%s\t%s\t\t%s\t%s\n", ligne[0], ligne[1], ligne[2], ligne[3],ligne[4],ligne[5],ligne[6],ligne[7]);
            }
            mysql_free_result(resultat);
        }
    }
}

Event * getEventByLabel(MYSQL *db,char *eventLabel){
    char query[100];
    sprintf(query, "SELECT * FROM event WHERE label='%s'", eventLabel);

    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
     }
    MYSQL_RES *result = mysql_store_result(db);

    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (!row) {
        printf("Aucun plat de ce nom %s\n", eventLabel);
        mysql_free_result(result);
        return NULL;
    }

    Event *event = malloc(sizeof(Event));

    sprintf(event->label, "%s" ,row[4]);
    sprintf(event->lieu, "%s",row[2]);
    sprintf(event->dateEvent,"%s", row[3]);
    sprintf(event->type,"%s", row[1]);
    event->id = atoi(row[0]);
    mysql_free_result(result);
    return event;
}
Plat * getPlatByLabel(MYSQL *db,char * platLabel){
    char query[100];
    sprintf(query, "SELECT * FROM plat WHERE label='%s'", platLabel);

    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    MYSQL_RES *result = mysql_store_result(db);

    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (!row) {
        printf("Aucun plat de ce nom %s\n", platLabel);
        mysql_free_result(result);
        return NULL;
    }

    Plat *plat = malloc(sizeof(Plat));

    strcpy(plat->label, row[1]);
    
    plat->id = atoi(row[0]);
    mysql_free_result(result);

    return plat;
}

User*getUserByFirstEmail(MYSQL *db, char *email) {
    char query[100];
    sprintf(query, "SELECT * FROM user WHERE email='%s'", email);

    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
     }

    MYSQL_RES *result = mysql_store_result(db);

    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
    }

    MYSQL_ROW row = mysql_fetch_row(result);

    if (!row) {
        printf("Aucun utilisateur trouvé pour le nom d'utilisateur %s\n", email);
        mysql_free_result(result);
        return NULL;
    }

    User *user = malloc(sizeof(User));

    strcpy(user->firstName, row[1]);
    strcpy(user->password, row[5]);
    strcpy(user->lastName, row[2]);
    strcpy(user->rule, row[3]);
    strcpy(user->email, row[4]);
     user->id = atoi(row[0]);
    mysql_free_result(result);

    return user;
}

bool authentiferUser(MYSQL *db, User *user)
{
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "select * from user where email = \"%s\" and password = \"%s\" ",user->email, user->password);
     mysql_query(db, query);
     result = mysql_store_result(db);
     row = mysql_fetch_row(result);
     if (mysql_num_rows(result) == 0){
          printf("prenom ou mot de passe incorrêcte");
          //mysql_free_result(result);
          return false;
     }else{
          //mysql_free_result(result);
          printf("Authentification réussie.\n");
          return true;
     }
    
}
Event *createEvent(MYSQL *db, Event *event)
{
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into event(type, place, date_event, label) values(\"%s\", \"%s\", \"%s\",\"%s\")", event->type, event->lieu, event->dateEvent, event->label);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     result = mysql_store_result(db);
     row = mysql_fetch_row(result);
     event->id = atoi(row[0]);
     mysql_free_result(result);
}

void getFilmByDate(MYSQL *db, char *date) {
    char query[1000];
    sprintf(query, "SELECT film.titre, film.description, film.auteur FROM film INNER JOIN session ON film.ses_id=session.id WHERE session.date_session=\"%s\"", date);
    if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
    } else {
        MYSQL_RES *result = mysql_store_result(db);
        if (result == NULL) {
            fprintf(stderr, "%s\n", mysql_error(db));
        } else {
            MYSQL_FIELD *field;
            int num_fields = mysql_num_fields(result);
            while ((field = mysql_fetch_field(result))) {
                if (field->name != NULL && (strcmp(field->name, "titre") == 0 || strcmp(field->name, "description") == 0 || strcmp(field->name, "auteur") == 0)) {
                    printf("%-30s|", field->name); //ajout de la largeur de champ pour éviter le décalage
                }
            }
            printf("\n");
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(result))) {
                printf("%-30s|%-30s|%-30s\n", row[0], row[1], row[2]); //ajout de la largeur de champ pour éviter le décalage
            }
            mysql_free_result(result);
        }
    }
}
Session * getSessionByFilm(MYSQL *db,char *film){
     char query[1000];
     sprintf(query, "SELECT * FROM session INNER JOIN film ON film.ses_id=session.id WHERE film.titre=\"%s\"", film);

     if (mysql_query(db, query)) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
     }
     MYSQL_RES *result = mysql_store_result(db);

     if (!result) {
        fprintf(stderr, "%s\n", mysql_error(db));
        exit(1);
     }

     MYSQL_ROW row = mysql_fetch_row(result);

     if (!row) {
        printf("Aucun film de ce titre%s\n", film);
        mysql_free_result(result);
        return NULL;
     }
     Session *session = malloc(sizeof(Session));
     sprintf(session->name, "%s" ,row[1]);
     sprintf(session->dateSession, "%s",row[2]);
     session->id = atoi(row[0]);
     mysql_free_result(result);
     return session;
}

Ticket *createTicket(MYSQL *db,Ticket *ticket, Session * session, User *user)
{
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into ticket (use_id, ses_id, number, date_ticket) values(\"%d\", \"%d\", \"%d\",NOW())", user->id, session->id, ticket->number);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     result = mysql_store_result(db);
     row = mysql_fetch_row(result);
     ticket->id = atoi(row[0]);
     ticket->user = user;
     ticket->session= session;
     return ticket;
}

void createReservation(MYSQL * db, User * user, Place *  place, Plat * plat){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into reserver (use_id, place_id,plat_id) values(\"%d\", \"%d\",\"%d\")", user->id, place->id,plat->id);
     mysql_query(db, query);
}

void createCommander(MYSQL * db, User * user, Plat * plat){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into commander (use_id, pla_id) values(\"%d\", \"%d\")", user->id, plat->id);
     mysql_query(db, query);
}

Plat * createPlat(MYSQL * db, Plat *  plat, Event * event){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into plat (eve_id, label) values(\"%d\", \"%s\")", event->id, plat->label);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     result = mysql_store_result(db);
     row = mysql_fetch_row(result);
     plat->id = atoi(row[0]);
     plat->event = event;
     return plat;
}

Place * createPlace(MYSQL * db, Place *  place, Event * event){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into place (eve_id, number) values(\"%d\", \"%d\")", event->id, place->number);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     result = mysql_store_result(db);
     row = mysql_fetch_row(result);
     place->id = atoi(row[0]);
     place->event = event;
     return place;
}

Session * createSession(MYSQL * db,Session * session){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into session (name, date_session) values(\"%s\",\"%s\")", session->name, session->dateSession);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     result = mysql_store_result(db);
     row = mysql_fetch_row(result);
     session->id = atoi(row[0]);
     
     return session;
}

Film * createFilm(MYSQL * db,Film * film,  Session *  session){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into film (ses_id, titre, description, auteur) values(\"%d\", \"%s\",\"%s\", \"%s\")", session->id, film->titre, film->description, film->auteur);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     result = mysql_store_result(db);
     row = mysql_fetch_row(result);
     film->id = atoi(row[0]);
     film->session = session;
     return film;
}

Event *updateEvent(MYSQL *db, Event *event)
{
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "update event set type=\"%s\", place=\"%s\", date_event=\"%s\", label=\"%s\" where id=%d", event->type, event->lieu, event->dateEvent, event->label, event->id);
     mysql_query(db, query);
     return event;
}

void deleteEvent(MYSQL *db, Event * event){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     int i = 0;
     char query[1000];
     sprintf(query, "delete from event where id=%d", event->id);
     mysql_query(db, query);
} 

/* Plat ** getPlatByEventLabel(MYSQL *db, Event * event){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     unsigned int i = 0;
     unsigned int num_champs = 0;
     unsigned long *lengths;
     char query[1000];
     Plat **platTable = malloc(100 * sizeof(Plat*));
     sprintf(query, "select * from plat inner join event on plat.eve_id=event.id where event.label=%s", event->label);
     mysql_query(db, query);
     result = mysql_store_result(db);
     num_champs = mysql_num_fields(result);
     while ((row = mysql_fetch_row(result))){
          Plat * plat = malloc(100 * sizeof(Plat));
          lengths = mysql_fetch_lengths(result);
          sprintf(plat->label, "%s", row[2]);
          plat->id = atoi(row[0]);
          plat->event = event;
          platTable[i] = plat;
          i++;
      }
     return platTable;   
}
 
Session ** getSessionByEventId(MYSQL *db, Event * event){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     unsigned int i = 0;
     unsigned int num_champs = 0;
     unsigned long *lengths;
     char query[1000];
     Session **sessionTable =malloc(100 * sizeof(Session*));
     sprintf(query, "select * from session inner join event on session.eve_id=event.id where event.id=%d", event->id);
     mysql_query(db, query);
     result = mysql_store_result(db);
     num_champs = mysql_num_fields(result);
     while ((row = mysql_fetch_row(result))){
          Session * session = malloc(100 * sizeof(Session));
          lengths = mysql_fetch_lengths(result);
          sprintf(session->name, "%s", row[2]);
          sprintf(session->dateSession, "%s", row[3]);
          session->id = atoi(row[0]);
          // sessionTable[i]->film=getFilmBySessionId(db, session);
          session->event = event;
          sessionTable[i] = session;
          i++;
      }
     return sessionTable;   
}
Place ** getPlaceByEventId(MYSQL *db, Event * event){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     unsigned int i = 0;
     unsigned int num_champs = 0;
     unsigned long *lengths;
     char query[1000];
     Place **placeTable =malloc(100 * sizeof(Place*));
     sprintf(query, "select * from place inner join event on place.eve_id=event.id where event.id=%d", event->id);
     mysql_query(db, query);
     result = mysql_store_result(db);
     num_champs = mysql_num_fields(result);
     while ((row = mysql_fetch_row(result))){
          Place * place = malloc(100 * sizeof(Place));
          lengths = mysql_fetch_lengths(result);
          place->number= atoi(row[2]);
          place->id = atoi(row[0]);
          place->event = event;
          placeTable[i] = place;
          i++;
      }
     return placeTable;   
}*/
/*Ticket * getTicketByUserId(MYSQL *db, User * user, Event **event){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     unsigned int i = 0;
     unsigned int num_champs = 0;
     unsigned long *lengths;
     char query[1000];
     Ticket *ticketTable =malloc(100 * sizeof(Ticket));
     sprintf(query, "select * from ticket inner join user on ticket.use_id=user.id where user.id=%d", user->id);
     mysql_query(db, query);
     result = mysql_store_result(db);
     num_champs = mysql_num_fields(result);
     while ((row = mysql_fetch_row(result))){
          lengths = mysql_fetch_lengths(result);
          ticketTable[i].number= row[3];
          ticketTable[i].id = atoi(row[0]);
          sprintf(ticketTable[i].dateTicket, "%s", row[4]);
          ticketTable[i].user= user;
          for(int j =0; j <100; j++){
               if(event[j]!=NULL && event[j]->id==row[2]){
                    ticketTable[i].event= event[j];
                    break;
               }
          }
          i++;
      }
     return ticketTable;   
}

Film ** getFilmBySessionId(MYSQL *db, Session * session){
     MYSQL_RES *result = NULL;
     MYSQL_ROW row;
     unsigned int i = 0;
     unsigned int num_champs = 0;
     unsigned long *lengths;
     char query[1000];
     Film **filmTable =malloc(100 * sizeof(Film*));
     sprintf(query, "select * from film inner join session on film.ses_id=session.id where session.id=%d", session->id);
     mysql_query(db, query);
     result = mysql_store_result(db);
     num_champs = mysql_num_fields(result);
     while ((row = mysql_fetch_row(result))){
          Film * film;
          lengths = mysql_fetch_lengths(result);
          sprintf(film->titre, "%s", row[2]);
          sprintf(film->description, "%s", row[3]);
          sprintf(film->auteur, "%s", row[4]);
          film->id = atoi(row[0]);
          film->session = session;
          filmTable[i] = film;
          i++;
      }
     return filmTable;   
}*/

