#include "config.h"
#include "ad.h"

_FBS(BSS_NO_BOOT_CODE & BWRP_WRPROTECT_OFF);

_FGS(GWRP_OFF & GCP_OFF);

_FOSCSEL(FNOSC_FRC & IESO_OFF);

_FOSC(FCKSM_CSECMD & POSCMD_NONE & OSCIOFNC_ON & IOL1WAY_OFF);

_FWDT(FWDTEN_OFF);

_FPOR(FPWRT_PWR128 & PWMPIN_ON & HPOL_ON & LPOL_ON & ALTI2C_OFF);

_FICD(ICS_PGD1 & JTAGEN_OFF);

#define BAUDRATE 38400
#define FCY 39613750

int enable = 0;
int leer = 0;
int salida = 0;

void avanzarPaso();
void leerCuadrado();
int dato = 0;
int A = 0;
int primer_bucle = 1;


int main(void){
    InicializarReloj();
    RemapeaPerifericos();
    InicializarUART();
    AD1PCFGL=0xFFFF;

    // Configuración de pines
    PORTB = 0x0800;    // pone a 0 los bits de salida y a 1 los de entrada
    TRISB = 0x007F;    // Configura RB10, 11, 12, 13, 14, 15 como salidas y el resto como entradas

    // Configuración del timer
    TMR1 = 0;      // timer a 0
    PR1 = 0x00FF;     //  cuenta  hasta 15625 (con pre-escalado a 3 son 100ms)
    IFS0bits.T1IF = 0;    // interrupt flag   a 0
               // pre-escalado a 3 y ON

    init_ad(0x3F);	    //activa interrupcion

    while(1){
        while(A!=0)
        {
            if (primer_bucle)//Bucle para controlar inicio
            {
                T1CON = 0x8030;
                IEC0bits.T1IE = 1;
                primer_bucle = 0;
            }
        }
    }
    return  0;  // Devuelve 0
}

void __attribute__((interrupt, no_auto_psv))_T1Interrupt(void)
{
    IFS0bits.T1IF=0;    //	se baja el flag del timer

    static int contador = 0;
    static int contador2 = 0;
    static int cuadrados = 0;

    int a;
    Int b;
    if(contador2<=500){ //Se generan 2 pwm uno para cada motor con el fin de calibrar el robot
        a = 9;
        b = 10;
    }else{
        a = 16;
        b = 16;
    }

    contador++;
    contador2++;
    if(contador2==1)
        leerCuadrado();



    if(contador==(b)){
        PORTB|=0x0200;
    }
    if(contador==(a)){
        PORTB|=0x0400;
    }
    if(contador==16){
        contador=0;
        PORTB&=(~0x0600);
    }
    if(contador2==1000&&cuadrados<(A-1))//Avanza los cuadrados deseados
    {
        contador2=0;
        cuadrados++;
    }
}

void avanzarPaso(){         // FUNCION - avanzar un bloque
    enable = 1;
}

void leerCuadrado(){         // FUNCION - leer dato (blanco = 0, negro = 1)

    dato = get_ad(5); //Llamada a la función del convertidor analógico-digital para leer dato

    if(dato>400){ //Detecta blanco
            salida = 0;
            PORTB&=(~0x8000)//Enciende led cuando detecta blanco;
        }else{// detecta negro
            salida = 1;
            PORTB|=(0x8000);//Apaga led cuando detecta negro
        }
    U1TXREG = salida; //Guardamos la nueva salida en el registro de trasmisión
    IFS0bits.U1TXIF = 1; //Salta el flag de transmisión
}

void InicializarUART(void) {
TRISB |= 0x20;	// Configura RX como entrada
TRISB &= 0xFFEF;	// Configura TX como salida
U1BRG = (FCY/BAUDRATE)/16 - 1; // Configura velocidad de comunicación
U1MODEbits.STSEL = 0; // Configura 1 bit de stop
	U1MODEbits.PDSEL = 0; // Configura 8 bits sin paridad
	U1MODEbits.ABAUD = 0;
	U1MODEbits.UARTEN = 1; // Pone en marcha el módulo
	U1STAbits.UTXISEL1 = 1; // Activa interrupción
	U1STAbits.URXISEL = 0; // Salta la interrupción de recepción en cuanto hay un dato disponible
	U1STAbits.UTXEN = 1; // Habilita el transmisor de	la UART
	IFS0bits.U1TXIF = 0; // Baja el flag de la	interrupción de la transmisión
	IFS0bits.U1RXIF = 0; // Baja el flag de la  interrupción de la recepción
	IEC0bits.U1TXIE = 1; // Habilita interrupción de la transmisión
	IEC0bits.U1RXIE = 1; // Habilita interrupción de la recepción
}


Void __attribute__((interrupt,no_auto_psv)) _U1TXInterrupt(void) {
                IFS0bits.U1TXIF = 0; // Borrar la bandera de la interrupción



 }


Void __attribute__((interrupt,no_auto_psv)) _U1RXInterrupt(void){
IFS0bits.U1RXIF = 0; // Borrar la bandera de la interrupción
	A = U1RXREG; //Recibo el tamaño
}
