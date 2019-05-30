#include "mbed.h"
#include "Grove_LCD_RGB_Backlight.h"
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
Grove_LCD_RGB_Backlight ecran(P0_27, P0_28);

//Vitesses PWM
const float VitesseMax = 1.0;
//const float vitesseDeceleration = 0.35;

int main()
{
    float ERR0 = 0;
//Strings pour printf des données
    /*    char nb1[10];
        char nb2[10];
        char nb3[10];
        char nb4[10];
        char nb5[10]; */
    float frein = 0.5;
    float Kp = 0.3;
    float Ti = 9;
    float Td = 10;
    float dt = 2;
    float I = 0.0;
    M1 = HIGH;
    M2 = HIGH;
    float Vitesse;
    while(1) {
        wait_ms(2);

        float ERR1 = (INTD - INTG);
        //Sens de rotation des moteurs
        float P = Kp * ERR1;//0.06
        I = I + (Ti*ERR1*dt/1000);//0.0036
        float D = Td * (ERR1 - ERR0)/dt;//0.3
        Vitesse = VitesseMax - frein * ERR1;
        float delta = P + I + D;
        ERR0 = ERR1;
        if((MILIEU - INTD) < 0) {
            E1.write(Vitesse + delta);
            E2.write(Vitesse);
        } else if((MILIEU - INTG) < 0) {
            E2.write(Vitesse + delta);
            E1.write(Vitesse);
        } else {
            E1.write(Vitesse);
            E2.write(Vitesse);
        }
    }
    /*float ERR1G = MILIEU - INTG;
    float ERR1D = MILIEU - INTD;
    //Sens de rotation des moteurs
    M1 = HIGH;
    M2 = HIGH;
    E2.write(vitesseNorm);
    E1.write(vitesseNorm);

    if(ERR1D > 0 && ERR1G > 0 && MILIEU - EXTD > 0 && MILIEU - EXTG > 0) { //Mileu sur la ligne
        E2.write(vitesseNorm);
        E1.write(vitesseNorm);
        ecran.setRGB(0x00,0xFF,0x00);
        ecran.setRGB(0x00,0x00,0x00);
        cpt = 0;
    } else if(ERR1D < 0) { //Leger decalage à droite du robot
        //roue gauche ralentie
        //E2.write(k+vitesseNorm); //roue droite vitesse normale
        if(cpt == 1) {
            k = k * k;
            E2.write(vitesseNorm+(k*(ERR1D)));
        }
        ecran.setRGB(0xFF,0x00,0x00);
        ecran.setRGB(0x00,0x00,0x00);
        cpt = 1;
    } else if(MILIEU - INTG < 0) { //Leger decalage à gauche du robot

        E2.write(vitesseNorm); //roue droite ralentie
        //E1.write(k+vitesseNorm); //roue gauche vitesse normale
        if(cpt == 2) {
            k = k*k;
            E1.write(vitesseNorm+(k*(ERR1G)));
        }
        ecran.setRGB(0x00,0x00,0xFF);
        ecran.setRGB(0x00,0x00,0x00);
        cpt = 2;
    }*/


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
