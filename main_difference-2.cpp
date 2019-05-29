#include "mbed.h"
#include "LCD.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        

#define HIGH 1
#define LOW 0

// Initialisation des pins


//MOTEUR DROIT
DigitalOut M2(P2_2);
PwmOut E2(P2_3);

//MOTEUR GAUCHE
DigitalOut M1(P2_4);
PwmOut E1(P2_5);    

//Liason série pour printf des mesures (putty)
Serial pc(USBTX, USBRX); 

//Tensions analogiques aux borne des Photoresistances
AnalogIn MILIEU(P0_23);
AnalogIn INTD(P0_24);
AnalogIn INTG(P0_25);
AnalogIn EXTD(P0_26);
AnalogIn EXTG(P1_30);
AnalogIn poten(A0);

//Vitesses PWM
float k = 20;
const float vitesseNorm = 0.8;
//const float vitesseDeceleration = 0.35;

int main()
{
 init_Driver();
//Strings pour printf des données
/*    char nb1[10];
    char nb2[10];
    char nb3[10];
    char nb4[10];
    char nb5[10]; */

    while(1) {
        
        //Sens de rotation des moteurs
        M1 = HIGH;
        M2 = HIGH;
        E2.write(vitesseNorm);
        E1.write(vitesseNorm);
        
        if(MILIEU - INTD > 0 && MILIEU - INTG > 0){ //Mileu sur la ligne 
            E2.write(vitesseNorm);
            E1.write(vitesseNorm);
            k = 0;
            color(0x00,0xFF,0x00,0x00);
            color(0x00,0x00,0x00,0x00);
        }
        else if(MILIEU - INTD < 0){ //Leger decalage à droite du robot
            E2.write(k*(MILIEU - INTD)); //roue gauche ralentie
            //E2.write(k+vitesseNorm); //roue droite vitesse normale
            E1.write(1-(k*(MILIEU - INTD)));
            k=k+1;
            color(0xFF,0x00,0x00,0x00);
            color(0x00,0x00,0x00,0x00);
            
        }
        else if(MILIEU - INTG < 0){ //Leger decalage à gauche du robot
            E1.write(k*(MILIEU - INTG)); //roue droite ralentie
            //E1.write(k+vitesseNorm); //roue gauche vitesse normale
            E2.write(1-(k*(MILIEU - INTG)));
            k=k+1;
            color(0x00,0x00,0xFF,0x00);
            color(0x00,0x00,0x00,0x00);
        }


//Printf des données par liason série
/*        sprintf(nb1,"MILIEU %f\r\n", MILIEU.read());
        pc.printf(nb1);
        sprintf(nb2,"INTD %f\r\n", INTD.read());
        pc.printf(nb2);
        sprintf(nb3,"INTG %f\r\n", INTG.read());
        pc.printf(nb3);
        sprintf(nb4,"EXTD %f\r\n", EXTD.read());
        pc.printf(nb4);
        sprintf(nb5,"EXTG %f\r\n", EXTG.read());
        pc.printf(nb5);*/
    }
}