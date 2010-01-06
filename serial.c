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
    struct termios options;
    unsigned char trame[4];


void LinkToCar(void *data){
    servo_avant = 0;
    servo_new = 2;
    unsigned char *ptr;
    while(1){

        usleep(1000);
       // printf("AccX :%i\n",AccX);
        printf("AccY :%i\n",AccY);
       // printf("AccZ :%i\n",AccZ);

        //on traite les données
        trame[0] = 0xBB;
        //trame[2] = 0x00;
        //trame[3] = 0x00;
        

        if((AccY >= 95) & (AccY<= 110)  ) servo_new = 0xF2; else if(AccY >= 111 & AccY <= 130) servo_new = 0xBC;
        else if( (AccY >= 130) & (AccY <= 140)) servo_new = 0x89; else servo_new = servo_avant;
        int i;
    
        if(servo_new != servo_avant){
            printf("Valeur changée : %x\n",servo_new );
            servo_avant = servo_new;
            trame[1]= servo_avant;
            trame[2] = 0x00;
            trame[3] = 0x00;
    
   
        ptr= trame;
        for (i=0; i<2;i++){
            
         int sended = write(srl_handle,ptr,1);
         usleep(100);
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