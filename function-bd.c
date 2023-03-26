/**
 * @file function-bd.c
*/

#include <stdio.h>
#include <string.h>
#include "struc.h"
#include <mysql/mysql.h>

/**
     @brief Créé un nouvel utilisateur dans la base de données.
     Cette fonction prend en paramètre un objet MYSQL représentant la connexion à la base de données et un objet User contenant les informations du nouvel utilisateur à créer.
     @param db Un objet MYSQL représentant la connexion à la base de données.
     @param user Un objet User contenant les informations du nouvel utilisateur à créer.
     @return Un pointeur vers un objet User représentant le nouvel utilisateur créé, ou NULL si une erreur s'est produite.
     Exemple d'utilisation :
     @code
     MYSQL *db = mysql_init(NULL);
     mysql_real_connect(db, "localhost", "user", "password", "database", 0, NULL, 0);
     User *user = malloc(sizeof(User));
     user->firstName = "John";
     user->lastName = "Doe";
     user->rule = "admin";
     user->email = "johndoe@example.com";
     user->password = "secret";
     User *newUser = createUser(db, user);
     @endcode
*/
User *createUser(MYSQL *db, User *user)
{
     MYSQL_RES *resultat = NULL;
     MYSQL_ROW champ;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into user (fist_name, last_name, rule, email, password) values(\"%s\", \"%s\", \"%s\",\"%s\", \"%s\")", user->firstName, user->lastName, user->rule, user->email, user->password);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     resultat = mysql_store_result(db);
     champ = mysql_fetch_row(resultat);
     user->id = atoi(champ[0]);
}

void listerEvent(MYSQL *db)
{
     char query[] = "SELECT * FROM event";
     if (mysql_query(db, query))
     {
          fprintf(stderr, "%s\n", mysql_error(db));
     }
     else
     {
          MYSQL_RES *resultat = mysql_store_result(db);

          if (resultat == NULL)
          {
               fprintf(stderr, "%s\n", mysql_error(db));
          }
          else
          {

               MYSQL_FIELD *champ;

               printf("%s\t", "label");
               printf("\n");
               printf("%s\t", "---------");
               printf("\n");

               MYSQL_ROW ligne;

               while ((ligne = mysql_fetch_row(resultat)))
               {
                    printf("%s\n", ligne[4]);
               }
               mysql_free_result(resultat);
          }
     }
}
/**

     @brief Récupère les plats associés à un événement en fonction de son label.
     Cette fonction effectue une requête SQL pour récupérer les plats associés à un événement
     en fonction de son label. Les résultats sont affichés à l'écran.
     @param db Un pointeur vers une structure de connexion à la base de données MySQL.
     @param eventLabel Le label de l'événement dont on souhaite récupérer les plats associés.
*/
void getPlatByEventLabel(MYSQL *db, char eventLabel[20])
{
     char query[1000];
     sprintf(query, "select plat.label from plat inner join event on plat.eve_id=event.id where event.label=\"%s\"", eventLabel);
     if (mysql_query(db, query))
     {
          fprintf(stderr, "%s\n", mysql_error(db));
     }
     else
     {
          MYSQL_RES *resultat = mysql_store_result(db);
          if (resultat == NULL)
          {
               fprintf(stderr, "%s\n", mysql_error(db));
          }
          else
          {
               printf("les plats associés à cette événement sont:");
               
               printf("\n");
               MYSQL_ROW ligne;
               while ((ligne = mysql_fetch_row(resultat)))
               {
                    printf("|%-30s|\n", ligne[0]);
               }
               mysql_free_result(resultat);
          }
     }
}
/**

     @brief Obtient les plats associés à un événement donné par son étiquette.

     @param db Un pointeur vers une connexion MySQL.

*/

Event *getEventByLabel(MYSQL *db, char *eventLabel)
{
     char query[100];
     sprintf(query, "SELECT * FROM event WHERE label='%s'", eventLabel);

     if (mysql_query(db, query))
     {
          fprintf(stderr, "%s\n", mysql_error(db));
          exit(1);
     }
     MYSQL_RES *resultat = mysql_store_result(db);

     if (!resultat)
     {
          fprintf(stderr, "%s\n", mysql_error(db));
          exit(1);
     }

     MYSQL_ROW champ = mysql_fetch_row(resultat);

     if (!champ)
     {
          printf("Aucun plat de ce nom %s\n", eventLabel);
          mysql_free_result(resultat);
          return NULL;
     }

     Event *event = malloc(sizeof(Event));

     sprintf(event->label, "%s", champ[4]);
     sprintf(event->lieu, "%s", champ[2]);
     sprintf(event->dateEvent, "%s", champ[3]);
     sprintf(event->type, "%s", champ[1]);
     event->id = atoi(champ[0]);
     mysql_free_result(resultat);
     return event;
}
/**
 * @brief Recherche un plat dans la base de données par son nom.
 * 
 * @param db un pointeur vers la connexion MySQL
 * @param platLabel le nom du plat recherché
 * 
 * @return un pointeur vers un objet Plat si le plat est trouvé, sinon NULL
 */

Plat *getPlatByLabel(MYSQL *db, char *platLabel)
{
     char query[100];
     sprintf(query, "SELECT * FROM plat WHERE label='%s'", platLabel);

     if (mysql_query(db, query))
     {
          fprintf(stderr, "%s\n", mysql_error(db));
          exit(1);
     }

     MYSQL_RES *resultat = mysql_store_result(db);

     if (!resultat)
     {
          fprintf(stderr, "%s\n", mysql_error(db));
          exit(1);
     }

     MYSQL_ROW champ = mysql_fetch_row(resultat);

     if (!champ)
     {
          printf("Aucun plat de ce nom %s\n", platLabel);
          mysql_free_result(resultat);
          return NULL;
     }

     Plat *plat = malloc(sizeof(Plat));

     strcpy(plat->label, champ[1]);

     plat->id = atoi(champ[0]);
     mysql_free_result(resultat);

     return plat;
}

User *getUserByFirstEmail(MYSQL *db, char *email)
{
     char query[100];
     sprintf(query, "SELECT * FROM user WHERE email='%s'", email);

     if (mysql_query(db, query))
     {
          fprintf(stderr, "%s\n", mysql_error(db));
          exit(1);
     }

     MYSQL_RES *resultat = mysql_store_result(db);

     if (!resultat)
     {
          fprintf(stderr, "%s\n", mysql_error(db));
          exit(1);
     }

     MYSQL_ROW champ = mysql_fetch_row(resultat);

     if (!champ)
     {
          printf("Aucun utilisateur trouvé pour le nom d'utilisateur %s\n", email);
          mysql_free_result(resultat);
          return NULL;
     }

     User *user = malloc(sizeof(User));

     strcpy(user->firstName, champ[1]);
     strcpy(user->password, champ[5]);
     strcpy(user->lastName, champ[2]);
     strcpy(user->rule, champ[3]);
     strcpy(user->email, champ[4]);
     user->id = atoi(champ[0]);
     mysql_free_result(resultat);

     return user;
}

bool authentiferUser(MYSQL *db, User *user)
{
     MYSQL_RES *resultat = NULL;
     MYSQL_ROW champ;
     int i = 0;
     char query[1000];
     sprintf(query, "select * from user where email = \"%s\" and password = \"%s\" ", user->email, user->password);
     mysql_query(db, query);
     resultat = mysql_store_result(db);
     champ = mysql_fetch_row(resultat);
     if (mysql_num_rows(resultat) == 0)
     {
          printf("prenom ou mot de passe incorrêcte");
          // mysql_free_result(resultat);
          return false;
     }
     else
     {
          // mysql_free_result(resultat);
          printf("Authentification réussie.\n");
          return true;
     }
}
Event *createEvent(MYSQL *db, Event *event)
{
     MYSQL_RES *resultat = NULL;
     MYSQL_ROW champ;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into event(type, place, date_event, label) values(\"%s\", \"%s\", \"%s\",\"%s\")", event->type, event->lieu, event->dateEvent, event->label);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     resultat = mysql_store_result(db);
     champ = mysql_fetch_row(resultat);
     event->id = atoi(champ[0]);
     mysql_free_result(resultat);
}

void getFilmByDate(MYSQL *db, char *date)
{
     char query[1000];
     sprintf(query, "SELECT film.titre, film.description, film.auteur FROM film INNER JOIN session ON film.ses_id=session.id WHERE session.date_session=\"%s\"", date);
     if (mysql_query(db, query))
     {
          fprintf(stderr, "%s\n", mysql_error(db));
     }
     else
     {
          MYSQL_RES *resultat = mysql_store_result(db);
          if (resultat == NULL)
          {
               fprintf(stderr, "%s\n", mysql_error(db));
          }
          else
          {
               MYSQL_FIELD *field;
               int num_fields = mysql_num_fields(resultat);
               while ((field = mysql_fetch_field(resultat)))
               {
                    if (field->name != NULL && (strcmp(field->name, "titre") == 0 || strcmp(field->name, "description") == 0 || strcmp(field->name, "auteur") == 0))
                    {
                         printf("%-30s|", field->name); // ajout de la largeur de champ pour éviter le décalage
                    }
               }
               printf("\n");
               MYSQL_ROW champ;
               while ((champ = mysql_fetch_row(resultat)))
               {
                    printf("%-30s|%-30s|%-30s\n", champ[0], champ[1], champ[2]); // ajout de la largeur de champ pour éviter le décalage
               }
               mysql_free_result(resultat);
          }
     }
}
Session *getSessionByFilm(MYSQL *db, char *film)
{
     char query[1000];
     sprintf(query, "SELECT * FROM session INNER JOIN film ON film.ses_id=session.id WHERE film.titre=\"%s\"", film);

     if (mysql_query(db, query))
     {
          fprintf(stderr, "%s\n", mysql_error(db));
          exit(1);
     }
     MYSQL_RES *resultat = mysql_store_result(db);

     if (!resultat)
     {
          fprintf(stderr, "%s\n", mysql_error(db));
          exit(1);
     }

     MYSQL_ROW champ = mysql_fetch_row(resultat);

     if (!champ)
     {
          printf("Aucun film de ce titre%s\n", film);
          mysql_free_result(resultat);
          return NULL;
     }
     Session *session = malloc(sizeof(Session));
     sprintf(session->name, "%s", champ[1]);
     sprintf(session->dateSession, "%s", champ[2]);
     session->id = atoi(champ[0]);
     mysql_free_result(resultat);
     return session;
}

Ticket *createTicket(MYSQL *db, Ticket *ticket, Session *session, User *user)
{
     MYSQL_RES *resultat = NULL;
     MYSQL_ROW champ;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into ticket (use_id, ses_id, number, date_ticket) values(\"%d\", \"%d\", \"%d\",NOW())", user->id, session->id, ticket->number);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     resultat = mysql_store_result(db);
     champ = mysql_fetch_row(resultat);
     ticket->id = atoi(champ[0]);
     ticket->user = user;
     ticket->session = session;
     return ticket;
}

void createReservation(MYSQL *db, User *user, Place *place, Plat *plat)
{
     MYSQL_RES *resultat = NULL;
     MYSQL_ROW champ;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into reserver (use_id, place_id,plat_id) values(\"%d\", \"%d\",\"%d\")", user->id, place->id, plat->id);
     mysql_query(db, query);
}

/*  */
Plat *createPlat(MYSQL *db, Plat *plat, Event *event)
{
     MYSQL_RES *resultat = NULL;
     MYSQL_ROW champ;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into plat (eve_id, label) values(\"%d\", \"%s\")", event->id, plat->label);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     resultat = mysql_store_result(db);
     champ = mysql_fetch_row(resultat);
     plat->id = atoi(champ[0]);
     plat->event = event;
     return plat;
}

Place *createPlace(MYSQL *db, Place *place, Event *event)
{
     MYSQL_RES *resultat = NULL;
     MYSQL_ROW champ;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into place (eve_id, number) values(\"%d\", \"%d\")", event->id, place->number);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     resultat = mysql_store_result(db);
     champ = mysql_fetch_row(resultat);
     place->id = atoi(champ[0]);
     place->event = event;
     return place;
}

Session *createSession(MYSQL *db, Session *session)
{
     MYSQL_RES *resultat = NULL;
     MYSQL_ROW champ;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into session (name, date_session) values(\"%s\",\"%s\")", session->name, session->dateSession);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     resultat = mysql_store_result(db);
     champ = mysql_fetch_row(resultat);
     session->id = atoi(champ[0]);

     return session;
}

Film *createFilm(MYSQL *db, Film *film, Session *session)
{
     MYSQL_RES *resultat = NULL;
     MYSQL_ROW champ;
     int i = 0;
     char query[1000];
     sprintf(query, "insert into film (ses_id, titre, description, auteur) values(\"%d\", \"%s\",\"%s\", \"%s\")", session->id, film->titre, film->description, film->auteur);
     mysql_query(db, query);
     char query2[] = "select last_insert_id()";
     mysql_query(db, query2);
     resultat = mysql_store_result(db);
     champ = mysql_fetch_row(resultat);
     film->id = atoi(champ[0]);
     film->session = session;
     return film;
}
