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
AnalogIn MILIEU(P0_26);
AnalogIn INTD(P0_24);
AnalogIn INTG(P0_25);
AnalogIn EXTD(P0_23);
AnalogIn EXTG(P1_30);
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
    float frein = 2.0;
    float Kp = 0.4;
    float Ti = 0.01;
    float Td = 0.8;
    float dt = 2;
    M1 = HIGH;
    M2 = HIGH;
    float Vitesse;
    float somme_ERR = 0;
    while(1) {
        wait_ms(dt);
        float ERR1 = (INTD - INTG);
        //Sens de rotation des moteurs
        somme_ERR += ERR1;
        float P = ERR1;
        float I = Ti * somme_ERR*dt;
        float D = Td * (ERR1 - ERR0)/dt;
        Vitesse = VitesseMax - frein * abs(ERR1);
        float delta = Kp*(P + I + D);
        delta = abs(delta);
        ERR0 = ERR1;
        if(ERR1 < -0.2) {
            E1.write(Vitesse - delta);
            E2.write(Vitesse + delta);
            ecran.setRGB(255, 0, 0);
        } else if(ERR1 > 0.1) {
            E2.write(Vitesse - delta);
            E1.write(Vitesse + delta);
            ecran.setRGB(0, 0, 255);
        } else {
            E1.write(Vitesse);
            E2.write(Vitesse);
            ecran.setRGB(0, 255, 0);
        }
        if(I > 0.1){
            I = 0.1;
        }
        if(I < -0.1){
            I = -0.1;
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
