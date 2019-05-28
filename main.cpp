#include "Grove_LCD_RGB_Backlight.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                #include "mbed.h"


// # Product name: L298N motor driver module DF-MD v1.3
// # Product SKU : DRI0002
// # Version     : 1.0

// # Description:
// # The sketch for using the motor driver L298N
// # Run with the PWM mode

// # Connection:
// #        M1 pin  -> Digital pin 6
// #        E1 pin  -> Digital pin 7
// #        M2 pin  -> Digital pin 4
// #        E2 pin  -> Digital pin 5
// #        Motor Power Supply -> Centor blue screw connector(5.08mm 3p connector)
// #        Motor A  ->  Screw terminal close to E1 driver pin
// #        Motor B  ->  Screw terminal close to E2 driver pin
// #
// # Note: You should connect the GND pin from the DF-MD v1.3 to your MCU controller. They should share the GND pins.
// #

#define HIGH 1
#define LOW 0


// Initialisation des pins
DigitalOut M1(D6);
PwmOut E1(D7);    //GAUCHE
DigitalOut M2(D4);
PwmOut E2(D5);    //DROITE
Grove_LCD_RGB_Backlight screen(P0_27, P0_28);
Serial pc(USBTX, USBRX);
AnalogIn MILIEU(P0_23);
AnalogIn INTD(P0_24);
AnalogIn INTG(P0_25);
AnalogIn EXTD(P0_26);
AnalogIn EXTG(P1_30);
DigitalIn IR(D2);
/*const float seuilMILIEU = 0.64;
const float seuilINTD = 0.8;
const float seuilINTG = 0.53;
const float seuilEXTD = 0.65;
const float seuilEXTG = 0.70;
const float vitesseMax = 0.6;
const float vitesseDeceleration1 = 0.55;*/
/*const float vitesseDeceleration2 = 0.2;*/

int main()
{
    //float f;
    char nb1[10];
    char nb2[10];
    char nb3[10];
    char nb4[10];
    char nb5[10]; 


    /*for(int i = 0; i < 1000; i++){//Changement de couleur avec un compteur
        n = sprintf(str,"%d", i);
        write_cmd(0xC0); sauter une ligne
        print_LCD_String(str);
        if(i % 2 == 0) color(0x00, 0xF0, 0x00);
        else color(0x00, 0x00, 0xF0);
        wait(1);
    }*/

    while(1) {
/*        M1 = HIGH;
        M2 = HIGH;
        if(MILIEU > seuilMILIEU){
            E2.write(vitesseMax);
            E1.write(vitesseMax);
        }
        if(INTD > seuilINTD){
            E2.write(vitesseDeceleration1);
        }
        if(INTG > seuilINTG){
            E1.write(vitesseDeceleration1);
        }
        if(EXTD > seuilEXTD){
            E1.write(0.70);
        }
        if(EXTG > seuilEXTG){
            E2.write(0.70);
        } */

        sprintf(nb1,"MILIEU %f\r\n", MILIEU.read());
        pc.printf(nb1);
        sprintf(nb2,"INTD %f\r\n", INTD.read());
        pc.printf(nb2);
        sprintf(nb3,"INTG %f\r\n", INTG.read());
        pc.printf(nb3);
        sprintf(nb4,"EXTD %f\r\n", EXTD.read());
        pc.printf(nb4);
        sprintf(nb5,"EXTG %f\r\n", EXTG.read());
        pc.printf(nb5);
    }



}

