/*
 * File:   main.c
 * Author: 20187263
 *
 * Created on 27 de Setembro de 2021, 13:10
 */

#include "config.h"
#include <xc.h>
#include "delay.h"
#include "ihm.h"
#include "eusart.h"
#include "wifi.h"
#include "fifo.h"

void hexadecimal( unsigned char * origem, unsigned char * destino )
{
    unsigned char aux;
    unsigned char meiobyte;

    while( *origem )
    {
        aux = *origem;

        meiobyte = (aux >> 4);

        if( meiobyte < 10 )
            *destino++ = meiobyte+'0';
        else
            *destino++ = meiobyte-10+'A';

        meiobyte = (aux & 0x0F);

        if( meiobyte < 10 )
            *destino++ = meiobyte+'0';
        else
            *destino++ = meiobyte-10+'A';
    
        origem++;
    }
    *destino = 0;
}

void main(void)
{
//    unsigned recebidos = 0;
//    unsigned char i = 0;
//    unsigned char tecla;

    const char string[]   = "OK";
    unsigned char vtr[33] = " ";
    unsigned char hex[40] = " ";
    unsigned char indice = 0;
    
    TRISAbits.TRISA4 = 1;

    delay(1000);
    lcd.init();
    keyboard.init();
    wifi_init(115200);
    delay(1000);

    
//    lcd.print("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ");
//    delay(1000);
    
    while( 1 )
    {
        if( !PORTAbits.RA4 )
        {
            lcd.clr();
            indice = 0;
            wifi.mode(1);
            while( !PORTAbits.RA4 )
                ;
        }

        if( lcd.B0() )
        {
            lcd.clr();
            indice = 0;
            wifi.state();
            while( lcd.B0() )
                ;
        }

        if( lcd.B1() )
        {
            lcd.clr();
            indice = 0;
            wifi.connect();
            while( lcd.B1() )
                ;
        }

        while( fifo_tam() )
        {
            unsigned char d = fifo_retirar();
            if( d >= 20 )
            {
                vtr[indice] = d;
                indice = ++indice % 32;
            }
            else if( d == '\r' )
            {
                vtr[indice] = "null";
                indice = ++indice % 32;
                vtr[indice] = "null";
                indice = ++indice % 32;
            }
            else if( d == '\n' )
            {
                vtr[indice] = "null";
                indice = ++indice % 32;
                vtr[indice] = "null";
                indice = ++indice % 32;
            }
        }
        lcd.printpos(0,0,vtr);

//        if(eusart.search_string(string,vtr))
//             lcd.printpos(1,0,"OK");
//        else
//             lcd.printpos(1,0,"FAIL");
//
    }
}
