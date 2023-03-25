#include <mysql/mysql.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stddef.h>
#include <python3.10/Python.h>
#include "struc.h"
#include "saisie.h"
#include "function-bd.h"
int main(void){
    MYSQL *db = mysql_init(NULL);

    if (db==NULL){
        fprintf(stderr,"%s\n",mysql_error(db));
        exit(1);
    }

    if(mysql_real_connect(db, "localhost", "zeus", "8716taho", "event", 0, NULL, 0)==NULL){
        fprintf(stderr, "%s\n", mysql_error(db));
        mysql_close(db);
        exit(1);
    }
    printf("Bd connecté\n");
    char film[50];
    int choixMenu;
    char nouveauOuAncien[1];
    char saisirPlusieurPlat[1];
    char saisirPlusieurFilm[1];
    do{
        printf("\n");
        printf("1- Organiser un événment\n");
        printf("2- Participer à un événment\n");
        printf("3- Gérer le cinéma\n");
        printf("4- Regader un film\n");
        printf("5- Voir les statistiques\n");
        printf("0- Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choixMenu);
        printf("\n");
        while(getchar() != '\n');
        switch (choixMenu){
            case 1:{
                printf("êtes vous nouveau oui (O) ou Non (N):");
                scanf("%s",nouveauOuAncien);
                
                if(strcmp(nouveauOuAncien, "O") == 0){
                    User * user = saisieUser();
                    createUser(db, user);
                    Event * event = saisieEvent();
                    createEvent(db,event);
                    Plat* plat = saisiePlat();
                    createPlat(db,plat,event);
                    do{
                        printf("Voulez vous créer un autre plat Oui(O) Non (N):");
                        scanf("%s", saisirPlusieurPlat);
                        while(getchar() != '\n');
                        Plat* plat = saisiePlat();
                        createPlat(db,plat,event);
                    }while(strcmp(saisirPlusieurPlat, "O") == 0);
                  
                }else{
                    User * user = authenUser();
                    if(authentiferUser(db, user)){
                        Event * event = saisieEvent();
                        createEvent(db,event);
                        Plat* plat = saisiePlat();
                        createPlat(db,plat,event);
                        do{
                            printf("Voulez vous créer un autre plat Oui(O) Non (N):");
                            scanf("%s", saisirPlusieurPlat);
                            while(getchar() != '\n');
                            Plat* plat = saisiePlat();
                            createPlat(db,plat,event);
                        }while(strcmp(saisirPlusieurPlat, "O") == 0);
                        
                    }
                }
                break;
            }
            case 2:{
                char eventLabel[20];
                char platLabel[20];
                printf("êtes vous nouveau oui (O) ou Non (N):");
                scanf("%s",nouveauOuAncien);
                if(strcmp(nouveauOuAncien, "O") == 0){
                    User * user = saisieUser();
                    createUser(db, user);
                    listerEvent(db);
                    printf("Choisir un event:");
                    scanf("%s",eventLabel);
                    while(getchar() != '\n');
                    getPlatByEventLabel(db, eventLabel);
                    printf("Choisir un plat:");
                    scanf("%s",platLabel);    
                    Plat * plat = getPlatByLabel(db,platLabel);
                    Place* place = saisiePlace(); 
                    Event * event = getEventByLabel(db, eventLabel);
                    createPlace(db,place,event);
                    createReservation(db, user, place,plat);
                }else{
                    User * user = authenUser();
                    if(authentiferUser(db, user)){
                        listerEvent(db);
                        printf("Choisir un event:");
                        scanf("%s",eventLabel);
                        while(getchar() != '\n');
                        getPlatByEventLabel(db, eventLabel);
                        printf("Choisir un plat:");
                        scanf("%s",platLabel);    
                        User * user1 =  getUserByFirstEmail(db,user->email);
                        Plat * plat = getPlatByLabel(db,platLabel);
                        Place* place = saisiePlace(); 
                        Event * event = getEventByLabel(db, eventLabel);
                        createPlace(db,place,event);
                        createReservation(db, user1, place,plat);
                    }
                }
                break;
            }
            case 3 :{ 
                printf("êtes vous nouveau oui (O) ou Non (N):");
                scanf("%s",nouveauOuAncien);    
                if(strcmp(nouveauOuAncien, "O") == 0){
                    User * user = saisieUser();
                    createUser(db, user);
                    Film * film = saisieFilm();
                    Session * session = saisieSession();
                    createSession(db,session);
                    createFilm(db, film,session);
                    int i = 0;
                    printf("Voulez vous créer un autre Film Oui(O) Non (N):");
                    scanf("%s", saisirPlusieurPlat);
                    while((strcmp(saisirPlusieurPlat, "O") == 0) || i<=3){
                        Film * film = saisieFilm();
                        Session * session = saisieSession();
                        createSession(db,session);
                        createFilm(db, film,session);
                        i++;
                        printf("Voulez vous créer un autre Film Oui(O) Non (N):");
                        scanf("%s", saisirPlusieurPlat);
                        while(getchar() != '\n');
                    };
                        
                }else{
                    User * user = authenUser();
                    if(authentiferUser(db, user)){
                        Film * film = saisieFilm();
                        Session * session = saisieSession();
                        createSession(db,session);
                        createFilm(db, film,session);
                        int i = 0;
                        printf("Voulez vous créer un autre Film Oui(O) Non (N):");
                        scanf("%s", saisirPlusieurFilm);
                        while((strcmp(saisirPlusieurFilm, "O") == 0) && i<=3){ 
                            while(getchar() != '\n');
                            Film * film = saisieFilm();
                            Session * session = saisieSession();
                            createSession(db,session);
                            createFilm(db, film,session);
                            i++;
                            printf("Voulez vous créer un autre Film Oui(O) Non (N):");
                            scanf("%s", saisirPlusieurFilm);
                        }
                    }
                }
                break;
            }    
            case 4 :{
                    
                printf("êtes vous nouveau oui (O) ou Non (N):");
                scanf("%s",nouveauOuAncien);     
                if(strcmp(nouveauOuAncien, "O") == 0){
                    User * user = saisieUser();
                    createUser(db, user);
                    time_t t = time(NULL);
                    struct tm tm = *localtime(&t);
                    char date[20];
                    sprintf(date, "%04d-%02d-%02d 00:00:00", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
                    printf("Date d'aujourd'hui : %s\n", date);
                    getFilmByDate(db,date);
                    printf("Choisir un film:");
                    scanf("%s",film);
                    while(getchar() != '\n');
                    User * user1 =  getUserByFirstEmail(db,user->email);
                    Session * session = getSessionByFilm(db,film); 
                    Ticket * ticket = saisieTicket();
                    createTicket(db,ticket,session,user1);                                          
                }else{
                    User * user = authenUser();
                    if(authentiferUser(db, user)){
                        time_t t = time(NULL);
                        struct tm tm = *localtime(&t);
                        char date[20];
                        sprintf(date, "%04d-%02d-%02d 00:00:00", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
                        printf("Date d'aujourd'hui : %s\n", date);
                        getFilmByDate(db,date);
                        printf("Choisir un film:");
                        scanf("%s",film);
                        while(getchar() != '\n');
                        User * user1 =  getUserByFirstEmail(db,user->email);
                        Session * session = getSessionByFilm(db,film); 
                        Ticket * ticket = saisieTicket();
                        createTicket(db,ticket,session,user1);
                    }
                }
                break;
            }
            case 5:{
                Py_Initialize();
                FILE* fp = fopen("test_py.py", "r");
                PyRun_SimpleFile(fp, "test_py.py");
                fclose(fp);
                Py_Finalize();
                break;
            }
            break;
            
        }
    }while(choixMenu !=0);
    
}
