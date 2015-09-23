// Ansteuerung eines HD44780 kompatiblen LCD im 4-Bit-Interfacemodus
// Die Pinbelegung ist �ber defines in KS0066.h einstellbar

#include <avr/io.h>
#include "KS0066.h"
#include <util/delay.h>

////////////////////////////////////////////////////////////////////////////////
// Erzeugt einen Enable-Puls
static void lcd_enable( void )
{
    LCD_PORT |= (1<<LCD_EN);     // Enable auf 1 setzen
    _delay_us( LCD_ENABLE_US );  // kurze Pause
    LCD_PORT &= ~(1<<LCD_EN);    // Enable auf 0 setzen
}

////////////////////////////////////////////////////////////////////////////////
// Sendet eine 4-bit Ausgabeoperation an das LCD
static void lcd_out( uint8_t data )
{
    data &= 0xF0;                       // obere 4 Bit maskieren

    LCD_PORT &= ~(0xF0>>(4-LCD_DB));    // Maske l�schen
    LCD_PORT |= (data>>(4-LCD_DB));     // Bits setzen
    lcd_enable();
}

////////////////////////////////////////////////////////////////////////////////
// Initialisierung: muss ganz am Anfang des Programms aufgerufen werden.
// Die verschiednen Einstellungen sind im KS0066U.pdf Datenblatt auf
// Seite 26 und 27 ersichtlich.
void lcd_init( void )
{
    // verwendete Pins auf Ausgang schalten
    uint8_t pins = (0x0F << LCD_DB) |           // 4 Datenleitungen
                   (1<<LCD_RS) |                // R/S Leitung
                   (1<<LCD_EN);                 // Enable Leitung
    LCD_DDR |= pins;

    // initial alle Ausg�nge auf Null
    LCD_PORT &= ~pins;

    // warten auf die Bereitschaft des LCD
    _delay_ms( LCD_BOOTUP_MS );

    // Soft-Reset muss 3mal hintereinander gesendet werden zur Initialisierung
    lcd_out( LCD_SOFT_RESET );
    _delay_ms( LCD_SOFT_RESET_MS1 );
    lcd_enable();
    _delay_ms( LCD_SOFT_RESET_MS2 );
    lcd_enable();
    _delay_ms( LCD_SOFT_RESET_MS3 );

    //          ||||4-bit Modus aktivieren lcd_out schreibt nur obere 4 Bit!!
	lcd_out ( 0b00100000 );
    _delay_us( LCD_ENABLE_US );

    // 4-bit Modus /    ||2 Zeilen / 5x8
	lcd_command ( 0b00101000 );

    //                   |||Display ein / Cursor aus / Blinken aus
 	lcd_command ( 0b00001100 );

	// Display Clear oder command 0b0000000001
	lcd_clear();

    //                    ||Cursor inkrement / kein Scrollen
	lcd_command ( 0b00000110 );


}

////////////////////////////////////////////////////////////////////////////////
// Sendet ein Datenbyte an das LCD
void lcd_data( uint8_t data )
{
    LCD_PORT |= (1<<LCD_RS);    // RS auf 1 setzen
    lcd_out( data );            // zuerst die oberen,
    lcd_out( data<<4 );         // dann die unteren 4 Bit senden

    _delay_us( LCD_WRITEDATA_US );
}

////////////////////////////////////////////////////////////////////////////////
// Sendet einen Befehl an das LCD
void lcd_command( uint8_t data )
{
    LCD_PORT &= ~(1<<LCD_RS);    // RS auf 0 setzen

    lcd_out( data );             // zuerst die oberen,
    lcd_out( data<<4 );           // dann die unteren 4 Bit senden

    _delay_us( LCD_COMMAND_US );
}

////////////////////////////////////////////////////////////////////////////////
// Sendet den Befehl zur L�schung des Displays
void lcd_clear( void )
{
    lcd_command( LCD_CLEAR_DISPLAY );
    _delay_ms( LCD_CLEAR_DISPLAY_MS );
}

////////////////////////////////////////////////////////////////////////////////
// Sendet den Befehl: Cursor Home
void lcd_home( void )
{
    lcd_command( LCD_CURSOR_HOME );
    _delay_ms( LCD_CURSOR_HOME_MS );
}

////////////////////////////////////////////////////////////////////////////////
// Setzt den Cursor in Spalte x (0..15) Zeile y (1..4)

void lcd_setcursor( uint8_t x, uint8_t y )
{
    uint8_t data;

    switch (y)
    {
        case 1:    // 1. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE1 + x;
            break;

        case 2:    // 2. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE2 + x;
            break;

        case 3:    // 3. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE3 + x;
            break;

        case 4:    // 4. Zeile
            data = LCD_SET_DDADR + LCD_DDADR_LINE4 + x;
            break;

        default:
            return;                                   // f�r den Fall einer falschen Zeile
    }

    lcd_command( data );
}

////////////////////////////////////////////////////////////////////////////////
// Schreibt einen String auf das LCD

void lcd_string( const char *data )
{
    while( *data != '\0' )
        lcd_data( *data++ );
}

////////////////////////////////////////////////////////////////////////////////
// Schreibt ein Zeichen in den Character Generator RAM

void lcd_generatechar( uint8_t code, const uint8_t *data )
{
    // Startposition des Zeichens einstellen
    lcd_command( LCD_SET_CGADR | (code<<3) );
 	uint8_t i;
    // Bitmuster �bertragen
    for ( i=0; i<8; i++ )
    {
        lcd_data( data[i] );
    }
}

void lcd_WriteInt8(char zahl) {
	char hunderter;
	char zehner;
	char einer;
	char showZero = 0;

	if (zahl < 0) {
		zahl = -zahl;
		lcd_data('-');
	}

	if (zahl >= 100 || showZero == 1) {
		hunderter = zahl / 100;
		zahl = zahl % 100;
		lcd_data('0' + hunderter);
	}

	if (zahl >= 10) {
		zehner = zahl / 10;
		zahl = zahl % 10;
		lcd_data('0' + zehner);
		showZero = 1;
	}

	einer = zahl;
	lcd_data('0' + einer);
}

void lcd_WriteInt16(short zahl) {
	char zehntausender;
	char tausender;
	char hunderter;
	char zehner;
	char einer;
	char showZero = 0;

	if (zahl < 0) {
		zahl = -zahl;
		lcd_data('-');
	}

	if (zahl >= 10000) {
		zehntausender = zahl / 10000;
		zahl = zahl % 10000;
		lcd_data('0' + zehntausender);
		showZero = 1;
	}

	if (zahl >= 1000 || showZero == 1) {
		tausender = zahl / 1000;
		zahl = zahl % 1000;
		lcd_data('0' + tausender);
		showZero = 1;
	}

	if (zahl >= 100 || showZero == 1) {
		hunderter = zahl / 100;
		zahl = zahl % 100;
		lcd_data('0' + hunderter);
		showZero = 1;
	}

	if (zahl >= 10 || showZero == 1) {
		zehner = zahl / 10;
		zahl = zahl % 10;
		lcd_data('0' + zehner);
		showZero = 1;
	}

	einer = zahl;
	lcd_data('0' + einer);
}

void lcd_WriteFloat(float zahl2){
	long zahl = (long)(zahl2 * 100);
	char zehntausender;
	char tausender;
	char hunderter;
	char zehner;
	char einer;
	char showZero = 0;

	if (zahl < 0) {
		zahl = -zahl;
		lcd_data('-');
	}

	if (zahl >= 10000) {
		zehntausender = zahl / 10000;
		zahl = zahl % 10000;
		lcd_data('0' + zehntausender);
		showZero = 1;
	}

	if (zahl >= 1000 || showZero == 1) {
		tausender = zahl / 1000;
		zahl = zahl % 1000;
		lcd_data('0' + tausender);
		showZero = 1;
	}

	showZero = 1;
	if (zahl >= 100 || showZero == 1) {
		hunderter = zahl / 100;
		zahl = zahl % 100;
		lcd_data('0' + hunderter);
		showZero = 1;
	}

	lcd_data('.');

	if (zahl >= 10 || showZero == 1) {
		zehner = zahl / 10;
		zahl = zahl % 10;
		lcd_data('0' + zehner);
		showZero = 1;
	}

	einer = zahl;
	lcd_data('0' + einer);
}

void lcd_WriteNumArray(unsigned char val[], char length){
	for(int i=0;i<length;i++){
			lcd_data('0'+ val[i]);
		}
}

