/*
 * File:   esp01.c
 * Author: 20187263
 *
 * Created on 5 de Outubro de 2021, 15:40
 */

#include <xc.h>
#include "eusart.h"
#include "wifi.h"

void wifi_init( long br)
{
    eusart.init(br);
//    wifi.mode(md);
}

void wifi_send( const char * msg )
{
    while( *msg )
    {
        while( eusart.txSTATUS() );
        eusart.tx( *msg );
        ++msg;
    }
}
//unsigned char indice = 0;
unsigned char wifi_receive( unsigned char * rcv )
{
    unsigned char d = 0;
    unsigned char indice = 0;
    while( d != '\n' )
    {
        if( eusart.rxSTATUS() )
        {
            d = eusart.rx();
//            if( (d >= 'A' && d <= 'Z') || (d >='a' && d <= 'z'))
//            {
                *(rcv+indice) = d;
                ++indice;
//            }
        }
    }
    return( indice );
}

void Wifi_mode(unsigned char d )
{
    if(d == 1) // modo de esta��o STA(cliente)
    {
        wifi_send("AT+CWMODE=1\r\n");
    }

    if(d == 2) // modo SoftAP(servidor)
    {
        wifi_send("AT+CWMODE=2\r\n");
    }
    if(d == 3) // ambos(cliente + servidor)
    {
        wifi_send("AT+CWMODE=3\r\n");
    }
    else // modo nulo
        wifi_send("AT+CWMODE=0\r\n");
}

const char SSID[]="automation";
const char PASS[]="12345678";

//void Wifi_connect(unsigned char SSID, unsigned char PASS )
//void Wifi_connect( const char * ssid, const char * pass )
void Wifi_connect( void )
{
//    unsigned char i = 10;
//    unsigned char str[40] = "AT+CWJAP=\"";
//    while( *ssid )
//    {
//        str[i] = *ssid;
//        ssid++;
//        i++;
//    }
//    str[i] = '"'; i++;
//    str[i] = ','; i++;
//    str[i] = '"'; i++;
//    while( *pass )
//    {
//        str[i] = *pass;
//        pass++;
//        i++;
//    }
//    str[i] = '"'; i++;
//    str[i] = '\r'; i++;
//    str[i] = '\n'; i++;
//    str[i] = 0;
//    wifi_send( str );
    wifi_send("AT+CWJAP=\"automation\",\"12345678\"\r\n");
   

}

void Wifi_state (void)
{
    wifi_send("AT+CWLAP\r\n");
}

void Wifi_ip( void )
{
    wifi_send("AT+CIFSR\r\n");
}

void Wifi_autoconnect( void )
{
    wifi_send("AT+CWAUTOCONN=0\r\n");
}

