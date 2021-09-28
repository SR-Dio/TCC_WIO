#include <xc.h>
#include "delay.h"

//***************** Interface com PORTs/Pinos
#define LCD_BUS         LCDbits.BUS
#define LCD_EN          LCDbits.EN
#define LCD_RS          LCDbits.RS
#define LCD_B0          LCDbits.B0
#define LCD_B1          LCDbits.B1
#define LCD_ROWS        2
#define LCD_COLS        16
#define LCD_ADDRS       0x008

typedef union 
{
    struct 
    {
        unsigned char RS  :1;
        unsigned char EN  :1;
        unsigned char BUS :4;
        unsigned char B0  :1;
        unsigned char B1  :1;
    };
} LCDbits_t;

volatile LCDbits_t LCDbits __at(LCD_ADDRS);

//***************** Definicao de Comandos ao LCD 
#define LCD_CLEAR_DISPLAY           0x01

#define LCD_RETURN_HOME             0x02

#define LCD_ENTRY_MODE_SET          0x04
#define LCD_EMS_CURSOR_RIGHT        0x02
#define LCD_EMS_CURSOR_LEFT         0x00
#define LCD_EMS_SHIFT_DISPLAY       0x01

#define LCD_DISPLAY_CONTROL         0x08
#define LCD_DC_DISPLAY_ON           0x04
#define LCD_DC_DISPLAY_OFF          0x00
#define LCD_DC_CURSOR_ON            0x02
#define LCD_DC_CURSOR_OFF           0x00
#define LCD_DC_BLINK_ON             0x01
#define LCD_DC_BLINK_OFF            0x00

#define LCD_CURSOR_SHIFT            0x10
#define LCD_CS_LEFT                 0x00
#define LCD_CS_RIGHT                0x04

#define LCD_DISPLAY_SHIFT           0x10
#define LCD_DS_LEFT                 0x08
#define LCD_DS_RIGHt                0x0C

#define LCD_FUNCTION_SET            0x20
#define LCD_FS_DATA_LENGTH_8        0x10
#define LCD_FS_DATA_LENGTH_4        0x00
#define LCD_FS_LINE_NUMBER_1        0x00
#define LCD_FS_LINE_NUMBER_2        0x08
#define LCD_FS_DOTS_FORMAT_5x8      0x00
#define LCD_FS_DOTS_FORMAT_5x11     0x04

#define LCD_SET_CGRAM_ADDRS( adrs ) (0x40+(adrs & 0x3F))

#define LCD_SET_DDRAM_ADDRS( adrs ) (0x80+(adrs & 0x7F))
#define LCD_ADDR_LINE_0             0x00
#define LCD_ADDR_LINE_1             0x40

// Escreve um comando no display (Instruction Register)
void dispLCD_instReg( unsigned char i )
{
    LCD_RS = 0;
    LCD_BUS = (i>>4);

    LCD_EN = 0;
    if( i == LCD_CLEAR_DISPLAY || i == LCD_RETURN_HOME )
        __delay_ms( 2 );
    else
        __delay_us( 40 );
    LCD_EN = 1;
    

    if( (i & 0xF0) == (LCD_FUNCTION_SET | LCD_FS_DATA_LENGTH_4) )
    {
        LCD_RS = 0;
        LCD_BUS = i>>4;
        LCD_EN = 0;
        __delay_us( 40 );
        LCD_EN = 1;
    }

    LCD_RS = 0;
    LCD_BUS = i & 0x0F;
    LCD_EN = 0;
    if( i == LCD_CLEAR_DISPLAY || i == LCD_RETURN_HOME )
        __delay_ms( 2 );
    else
        __delay_us( 40 );
    LCD_EN = 1;
}

// Escreve um dado no display (Data Register))
void dispLCD_dataReg( unsigned char d )
{
    LCD_RS = 1;
    LCD_BUS = d >> 4;
    LCD_EN = 0;
    __delay_us( 40 );
    LCD_EN = 1;

    LCD_RS = 1;
    LCD_BUS = d & 0x0F;
    LCD_EN = 0;
    __delay_us( 40 );
    LCD_EN = 1;
}

// Posicionar o cursor na coordenada: linha e coluna 
void dispLCD_lincol( unsigned char lin, unsigned char col)
{
    dispLCD_instReg( LCD_SET_DDRAM_ADDRS( (LCD_ADDR_LINE_1 * lin) + (col + LCD_ADDR_LINE_0) ) );
}

// Inicializa os pinos conectados ao display
void dispLCD_init( void )
{
    delay(100);
    ANSELH = 0;
    TRISDbits.TRISD0 = 0;   // RS
    TRISDbits.TRISD1 = 0;   // EN
    TRISDbits.TRISD2 = 0;   // D4
    TRISDbits.TRISD3 = 0;   // D5
    TRISDbits.TRISD4 = 0;   // D6
    TRISDbits.TRISD5 = 0;   // D7
    
    delay(100);
    LCD_EN = 1;
    dispLCD_instReg( LCD_FUNCTION_SET|LCD_FS_DATA_LENGTH_4|LCD_FS_LINE_NUMBER_2);
    dispLCD_instReg( LCD_DISPLAY_CONTROL|LCD_DC_DISPLAY_ON|LCD_DC_CURSOR_OFF|LCD_DC_BLINK_OFF );
    dispLCD_instReg( LCD_CLEAR_DISPLAY );
    dispLCD_instReg( LCD_RETURN_HOME );
    delay(100);
}

// Escreve uma string no display
void dispLCD( unsigned char lin, unsigned char col, const char * str )
{
    dispLCD_lincol( lin, col );

    while( *str )
    {
        dispLCD_dataReg( *str );
        ++str;
    }
}
// Escreve uma string no display
void dispLCDstr( const char * str )
{
    dispLCD_lincol( 0, 0 );

    while( *str )
    {
        if( *str == '\n' )
        {
            dispLCD_lincol(1,0);
        }
        dispLCD_dataReg( *str );
        ++str;
    }
}

// Escreve um n�mero inteiro no display
void dispLCD_num(  unsigned char lin, unsigned char col,
                    int num, unsigned char tam )
{
    int div;
    unsigned char size;
    char sinal; // 0:+ 1:-
   
    sinal = num < 0;
    if( sinal )
        num = (~num) + 1;

    dispLCD_lincol(lin, col);
   
    div=10000;
    size = 5;
    while( div >= 1 )
    {
        if( num/div == 0 )
            --size;
        else
            break;
        div/=10;
    }

    while( tam > (size+sinal) && tam > 1 )
    {
        dispLCD_dataReg(' ');
        --tam;
    }  

    if( sinal )
        dispLCD_dataReg('-');
 
    do
    {
        dispLCD_dataReg( (unsigned char)(num / div) + '0' );
        num = num % div;
        div/=10;
    }
    while( div >= 1 );
}

// Apaga todos os caracteres no display
void dispLCD_clr( void )
{
    dispLCD_instReg(LCD_CLEAR_DISPLAY);
}


unsigned char dispLCD_B0( void )
{
    return( !LCD_B0 );
}

unsigned char dispLCD_B1( void )
{
    return( !LCD_B1 );
}
