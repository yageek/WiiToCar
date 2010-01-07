/* 
 * File:   main.c
 * Author: yaya
 *
 * Created on 20 décembre 2009, 17:48
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cwiid.h>
#include <pthread.h>

#include "wiimote.h"
#include "serial.h"
/*
 * 
 */
//Thread pour la série
pthread_t *Serial;

//Bluetooth
bdaddr_t bluetooth_adress;
//Wiimote
cwiid_wiimote_t *wiimote;
//Calibration de la wiimote
struct acc_cal wm_cal;
//Valeurs à transmettres
int AccX;
int AccY;
int AccZ;
int bouton_2;
int bouton_1;
char temp;
int continuer;
int main(int argc, char** argv) {
    //Valeurs par défaut aux variables
    AccX = 0;
    AccY = 0;
    AccZ = 0;
    bouton_2 = 0;
    continuer = 1;
    bluetooth_adress = *BDADDR_ANY;
    Serial = NULL;
    printf("=== WiiToCar ===\n");

    printf("Ouverture du port série\n");
      if(openSerial()<0){
          printf("Port série introuvable\n");
          return(EXIT_FAILURE);
      }
    printf("Port Série ouvert\n");
    printf("Press 1+2 on the wiimote (Submit to begin looking for the wiimote)\n");
    scanf("%c",&temp);
    if((wiimote = cwiid_open(&bluetooth_adress,CWIID_FLAG_MESG_IFC)) == NULL){
        printf("Impossible de se connecter à la Wiimote\n");
    }
    else if(cwiid_set_mesg_callback(wiimote,&cwiid_callback)){
        printf("Pas possible d'assigner la function d'appel\n");

    }
    else if (cwiid_get_acc_cal(wiimote, CWIID_EXT_NONE, &wm_cal)) {
 printf("Erreur on calibration");
    } else {



        cwiid_set_rpt_mode(wiimote,CWIID_RPT_STATUS|CWIID_RPT_BTN|CWIID_RPT_ACC);


	cwiid_command(wiimote,CWIID_CMD_RUMBLE,1);
	usleep(1000000);
	cwiid_command(wiimote,CWIID_CMD_RUMBLE,0);
	cwiid_command(wiimote,CWIID_CMD_LED,CWIID_LED1_ON);

    }
    //Lancement du thread si le terminal à réussi à s'ouvrir
 
     pthread_create(&Serial,NULL,LinkToCar,NULL);
    
    
     while(continuer);
    //on tue le thread serial
    pthread_cancel(Serial);
    cwiid_close(wiimote);

    return (EXIT_SUCCESS);
}

