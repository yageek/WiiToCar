#include<cwiid.h> //Pour la définition de tout

extern int continuer;
extern int AccX;
extern int AccY;
extern int AccZ;
extern int bouton_2;
extern int bouton_1;
void cwiid_callback(cwiid_wiimote_t *wiimote, int mesg_count,
                    union cwiid_mesg mesg[], struct timespec *timestamp)

{
  int i;

   
    for (i=0; i < mesg_count; i++)
	{
		switch (mesg[i].type) {
		case CWIID_MESG_STATUS:
			printf("Status Report: battery=%d extension=",
                 mesg[i].status_mesg.battery);


			switch (mesg[i].status_mesg.ext_type) {
			case CWIID_EXT_NONE:
				printf("none");
				break;
			case CWIID_EXT_NUNCHUK:
				printf("Nunchuk");
				break;
			case CWIID_EXT_CLASSIC:
				printf("Classic Controller");
				break;
			default:
				printf("Unknown Extension");
				break;
			}
			printf("\n");
			break;
		case CWIID_MESG_BTN:
			printf("Button Report: %i\n", mesg[i].btn_mesg.buttons);
                        if(mesg[i].btn_mesg.buttons & CWIID_BTN_A) continuer = 0;
                        if(mesg[i].btn_mesg.buttons & CWIID_BTN_2) bouton_2 = 1; else bouton_2 = 0;
                        if(mesg[i].btn_mesg.buttons & CWIID_BTN_1) bouton_1 = 1; else bouton_1 = 0;
			break;
		case CWIID_MESG_ACC:
		/*	printf("Acc Report: x=%d, y=%d, z=%d\n",
                  mesg[i].acc_mesg.acc[CWIID_X],
			       mesg[i].acc_mesg.acc[CWIID_Y],
			       mesg[i].acc_mesg.acc[CWIID_Z]);*/
                        AccX = mesg[i].acc_mesg.acc[CWIID_X];
                        AccY = mesg[i].acc_mesg.acc[CWIID_Y];
                        AccZ = mesg[i].acc_mesg.acc[CWIID_Z];
        
			break;
		case CWIID_MESG_ERROR:
			if (cwiid_close(wiimote)) {
				fprintf(stderr, "Error on wiimote disconnect\n");
				
			}
			
			break;
		default:
			printf("Unknown Report");
			break;
		}

	}


}

