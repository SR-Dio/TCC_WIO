/*
 * File:   serialIO.c
 * Author: curtaeletronica
 *
 * Created on 30 de Setembro de 2019, 19:36
 */

#ifndef SERIALIO_H
#define	SERIALIO_H

void serialIO_init( unsigned char * ptrIn, unsigned char * ptrOut, unsigned char length );
void serialIO_scan( void );

#endif	/* SERIALIO_H */
