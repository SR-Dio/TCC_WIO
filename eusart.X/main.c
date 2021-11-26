/*
 * File:   main.c
 * Author: 20187263
 *
 * Created on 27 de Setembro de 2021, 13:10
 */

//    wifi_send("AT+CWSAP=\"WIO\",\"23456789\",1,2,4,0\r\n");
//    delay(2000);
//
//    lcd.clr();
//    indice = 0;
//    fifo_filtro();
//    lcd.printpos(0,0,vtr);
//    delay(3000);
//
//    wifi_send("AT+CIPMUX=1\r\n");
//    delay(2000);
//
//    lcd.clr();
//    indice = 0;
//    fifo_filtro();
//    lcd.printpos(0,0,vtr);
//    delay(3000);

#include "config.h"
#include <xc.h>
#include "delay.h"
#include "ihm.h"
#include "eusart.h"
#include "wifi.h"
#include "fifo.h"

void main(void)
{
    lcd.init();
    wifi_init(115200);
    delay(3000);

    lcd.clr();
    indice = 0;
    wifi.mode(1);

    fifo_filtro();
    lcd.printpos(0,0,vtr);
    delay(3000);

    wifi.connect("TCC","87654321");

    lcd.clr();
    indice = 0;
    fifo_filtro();
    lcd.printpos(0,0,vtr);
    delay(3000);

    wifi.send("AT+CIPSTART=\"TCP\",\"192.168.4.1\",333\r\n"); 
    delay(2000);

    lcd.clr();
    indice = 0;
    fifo_filtro();
    lcd.printpos(0,0,vtr);
    delay(3000);

    wifi.send("AT+CIPSEND=4\r\n"); 
    delay(500);
    wifi.send("LUCA\r\n"); 
    delay(2000);

    lcd.clr();
    indice = 0;
    fifo_filtro();
    lcd.printpos(0,0,vtr);
    delay(3000);

    lcd.clr();
    indice = 0;
    wifi.send("AT+CLOSE\r\n"); 

//        while(1)
//        {
//            lcd.clr();
//            indice = 0;
//            fifo_filtro();
//            lcd.printpos(0,0,vtr);
//            delay(5000);
//        }
}
//    while( 1 )
//    {
//        switch(estado)
//        {
//            case 0: 
//                    indice = 0;
//                    lcd.clr();
//                    wifi_send("AT+CIPCLOSE\r\n"); 
//                    delay(3000);
//
//                    estado=15;
//                    break;
//            case 1: 
//                    wifi.mode(1);
//                    delay(2000);
//                    estado = 2;
//                    break;
//            case 2:  
//                    indice = 0;
//                    lcd.clr();
//                    fifo_filtro();
//                    lcd.printpos(0,0,vtr);
//                    delay(3000);
//                    
////                    wifi.config_servidor();
////                    delay(1000);
//                    
//                    estado = 8;
//                    break;
//            case 8:  
//                    wifi.connect("WIO","98765432");
//                    delay(2000);
//
//                    lcd.clr();
//                    indice = 0;
//                    fifo_filtro();
//                    lcd.printpos(0,0,vtr);
//                    delay(3000);
//
//                    estado = 15;
//                    break;
//            case 10:  
//                    wifi.send("AT+PING=\"192.168.4.1\"\r\n"); 
//                    delay(1000);
//
//                    lcd.clr();
//                    indice = 0;
//                    fifo_filtro();
//                    lcd.printpos(0,0,vtr);
//                    delay(3000);
//                    
//                    estado = 15;
//                    break;
//            case 15:  
//
//                    wifi.send("AT+CIPSTART=\"TCP\",\"192.168.4.1\",333\r\n");
//                    delay(2000);
//                    
//                    lcd.clr();
//                    indice = 0;
//                    fifo_filtro();
//                    lcd.printpos(0,0,vtr);
//                    delay(3000);
//
//                    estado = 18;
//                    break;
//            case 18:  
//                    wifi.send("AT+CIPSEND=4\r\n");
//                    wifi.send("LUCA\r\n");
//                    delay(1500);
//                    
//                    estado = 20;
//                    break;
//            case 20:  
//                    lcd.clr();
//                    indice = 0;
//                    fifo_filtro();
//                    lcd.printpos(0,0,vtr);
//                    delay(5000);
//
//                    estado = 0;
//                    break;
//            case 21:  
//                    break;
//            case 22:  
//                    break;
//        }
//    }
    
    
    
    
//        if( !PORTAbits.RA4 )
//        {
//            lcd.clr();
//            indice = 0;
//            wifi.send("AT+RESTORE\r\n");
////            wifi_send("AT+CIPSTART=\"TCP\",\"192.168.4.1\",\"333\"\r\n"); 
////            fifo_filtro();
////            lcd.printpos(0,0,vtr);
////            delay(3000);
////            indice = 0;
////            lcd.clr();
////
////            wifi_send("AT+CIPSEND=8\r\n");
////            fifo_filtro();
////            lcd.printpos(0,0,vtr);
////            delay(3000);
////            indice = 0;
////            lcd.clr();
////
////            wifi_send("ABCDEFGH"); 
////            fifo_filtro();
////            lcd.printpos(0,0,vtr);
////            delay(3000);
////            indice = 0;
////            lcd.clr();
////
////            wifi_send("AT+CIPCLOSE\r\n"); 
////            while( !PORTAbits.RA4 )
////                ;
//        }
//
//        if( lcd.B0() )
//        {
//            lcd.clr();
//            indice = 0;
//            wifi.mode(2);
//            fifo_filtro();
//            lcd.printpos(0,0,vtr);
//            delay(3000);
//
//            lcd.clr();
//            indice = 0;
//            wifi.config_servidor();
//            fifo_filtro();
//            lcd.printpos(0,0,vtr);
//            delay(3000);
//
//            while( lcd.B0() )
//                ;
//        }
//
//        if( lcd.B1() ) 
//        {
//            lcd.clr();
//            indice = 0;
//            wifi.mode(1);
//            fifo_filtro();
//            lcd.printpos(0,0,vtr);
//            delay(3000);
//
//            lcd.clr();
//            indice = 0;
//            wifi.connect("WIRELESS","********");
//            fifo_filtro();
//            lcd.printpos(0,0,vtr);
//            delay(3000);
//
//            lcd.clr();
//            indice = 0;
//            wifi.cipsend(5,"lucas");
//
//            while( lcd.B1() )
//
//                ;
//        }
//
//        fifo_filtro();
//        lcd.printpos(0,0,vtr);
////        lcd.printpos(1,0,d);
//    }
