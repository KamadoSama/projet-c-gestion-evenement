#include <mysql/mysql.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
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
    
    int choixMenu;
    char nouveauOuAncien[1];
    do{
        printf("\n");
        printf("1- Organiser un événment\n");
        printf("2- Participer à un événment\n");
        printf("3- Regader un film\n");
        printf("4- Gérer le cinéma\n");
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
                printf("%s",nouveauOuAncien);
                if(strcmp(nouveauOuAncien, "O") == 0){
                    User * user = saisieUser();
                    createUser(db, user);
                    Event * event = saisieEvent();
                    createEvent(db,event);
                    Plat* plat = saisiePlat();
                    createPlat(db,plat,event);
                    Place* place = saisiePlace(); 
                    createPlace(db,place,event);
                }else{
                    User * user = authenUser();
                    if(authentiferUser(db, user)){
                        Event * event = saisieEvent();
                        createEvent(db,event);
                        Plat* plat = saisiePlat();
                        createPlat(db,plat,event);
                        
                    }
                }
                break;
            }
            case 2:{
                char eventLabel[20];
                char platLabel[20];
                printf("êtes vous nouveau oui (O) ou Non (N):");
                scanf("%s",nouveauOuAncien);
                printf("%s",nouveauOuAncien);
                if(nouveauOuAncien == "O"){
                    User * user = saisieUser();
                    createUser(db, user);
                    
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
                        /* while(getchar() != '\n'); */
                        printf("ye");
                        User * user1 =  getUserByFirstName(db,user->firstName);
                        printf("ya");
                        Plat * plat = getPlatByLabel(db,platLabel);
                        printf("yo");
                        Place* place = saisiePlace(); 
                        Event * event = getEventByLabel(db, eventLabel);
                        createPlace(db,place,event);
                        createReservation(db, user1, place,plat);
                    }
                }
                break;
            }
        }
    }while(choixMenu !=0);
    
}