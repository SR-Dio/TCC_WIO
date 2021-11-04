/* 
 * File:   wifi.h
 * Author: 20187263
 *
 * Created on 5 de Outubro de 2021, 15:42
 */

#ifndef WIFI_H
#define	WIFI_H

void wifi_init( long br );
void wifi_send( const char * msg );
unsigned char wifi_receive( unsigned char * rcv );
void Wifi_mode(unsigned char d );
//void Wifi_connect(unsigned char *SSID, unsigned char *PASS );
void Wifi_connect(void);
void Wifi_ip( void );
void Wifi_autoconnect( void );
void Wifi_state (void);


struct
{
    void (*init)( long br );
    void (*send)( const char * msg );
    unsigned char (*receive)( unsigned char * rcv );
    void (*mode)(unsigned char d );
    void (*connect)(void);
    void (*ip)( void );
    void (*autoconnect)( void );
    void (*state) (void);
}wifi = {wifi_init, wifi_send, wifi_receive, Wifi_mode, Wifi_connect, Wifi_ip, Wifi_autoconnect,Wifi_state };

#endif	/* WIFI_H */

