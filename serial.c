#include<unistd.h>
#include<termios.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
extern int AccX;
extern int AccY;
extern int AccZ;
  int srl_handle;
 unsigned char servo_avant;
  unsigned char servo_new;
  unsigned char trame_avant[4];
    struct termios options;
    unsigned char trame[4];
    extern int bouton_2;
    extern int bouton_1;


void LinkToCar(void *data){
    servo_avant = 0;
    servo_new = 2;
    unsigned char *ptr;
    int k;
    for (k=0;k< 4;k++){
        trame_avant[k] = 0x01;
        
    }
        while(1){

        usleep(10000);
        printf("AccX :%i\n",AccX);
        //printf("AccY :%i\n",AccY);
       // printf("AccZ :%i\n",AccZ);

        //on traite les données
        trame[0] = 0xBB;
       
        
        //Axe Y
        if((AccY >= 95) & (AccY<= 110)  ) trame[1] = 0xF2; else if(AccY >= 111 & AccY <= 130)  trame[1] = 0xBC;
        else if( (AccY >= 130) & (AccY <= 140))  trame[1] = 0x89;
        
        //bouton _2

        if(bouton_2 == 1){
            if (AccX > 120 ) {
                trame[2] = 0x01;
                trame[3] = 80 ;
            }
            if (AccX > 130 ) {
                trame[2] = 0x01;
                trame[3] = 100 ;
            }if (AccX > 140 ) {
                trame[2] = 0x01;
                trame[3] = 125 ;

            } else if(AccX < 118) {
                trame[2] = 0x02;
                trame[3] = 70;
            }



        } else{

            trame[2] = 0x00;
            trame[3] = 0x00;
        }

        //Bouton_2
       /* if(bouton_2 == 1 & bouton_1 == 0) trame[2] = 0x01;
        else  if(bouton_2 == 0 & bouton_1 == 1) trame[2] = 0x02;
        else trame[2] = 0x00;
         * */
        int i;
        if(strcmp(trame,trame_avant)!=0){
            printf("Valeur changée : %x\n",trame[1] );
            memcpy(trame_avant,trame,sizeof(trame));
          
    
   
        ptr= trame;
        for (i=0; i<4;i++){
            
         int sended = write(srl_handle,ptr,1);
         usleep(10000);
         ptr++;
         if (sended > 0) printf("Envoie OK !\n"); else printf("Erreur\n");

        }
        }
        printf("Trame envoyée :\n");
        
    }
    
}

int openSerial(){
srl_handle = open("/dev/rfcomm4", O_RDWR | O_NOCTTY | O_NDELAY);
	if(srl_handle<0)
	{
		perror("serial port open");
                return -1;
	}else {

	tcgetattr(srl_handle, &options);
      //fcntl(srl_handle, F_SETFL, 0);
cfsetospeed(&options, B9600);

	/*Set no parity*/
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CRTSCTS;
	options.c_cflag |= CS8;
options.c_iflag |= (IXON | IXOFF | IXANY);
	/*Set raw output*/
	options.c_oflag &= ~OPOST;
  tcflush(srl_handle, TCIFLUSH);
	tcsetattr(srl_handle, TCSANOW, &options);
    
}
}
void closeSerial(){

    close(srl_handle);


    
}