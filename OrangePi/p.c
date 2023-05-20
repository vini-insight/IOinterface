
// gcc p.c -o p -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt && chmod +x p
// sudo ./p
// rm p.c && nano p.c
// dip switch
// DPS 1 = PA6  WiringPi    2 pin
// DPS 2 = PA1  WiringPi    5 pin
// DPS 3 = PA0  WiringPi    7 pin
// DPS 4 = PA3  WiringPi    8 pin

#include <stdio.h>
#include <string.h>
#include <unistd.h>	// FOR sleep
#include <stdbool.h> // FOR bool
#include <pthread.h>
#include <time.h>
#include <math.h>
#include <lcd.h> // for LCD
#include <wiringPi.h> // for GPIOS
#include <wiringSerial.h> /* for UART || serial || RS232 */
//USE WIRINGPI PIN NUMBERS
#define LCD_RS  13               //Register select pin
#define LCD_E   18               //Enable Pin
#define LCD_D4  21               //Data pin 4
#define LCD_D5  24               //Data pin 5
#define LCD_D6  26               //Data pin 6
#define LCD_D7  27               //Data pin 7
// dip switch pins
char DIP1 = 2;               //dip switch 1
char DIP2 = 5;               //dip switch 2
char DIP3 = 7;               //dip switch 3
char DIP4 = 8;               //dip switch 4
// push buttons
char subButton = 19;
char selectButton = 23;
char addButton = 25;

bool monitor = true;
bool timeOut = false;

int fd;
int lcd;
int i = 0;
int allMonitors = 0;
int nodeMCU = 0;
int sensor = 0;
int soma = 0;
int sda = 9;
int sgc = 9;

char ca[10];
char int_str[100];
char stringANDint[201] = "soma = ";

//char *protocolCodes[] = {"ESP%d.Anal", "ESP%d.Dig.1", "ESP%d.Dig.2", "ESP%d.LEDon", "ESP%d.LEDoff", "ESP%d.voltar"};
char protocolCodes[] = {
0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00001000, 0b00001001,
0b00001010, 0b00001011, 0b00001100, 0b00001101, 0b00001110, 0b00001111, 0b00010000, 0b00010001, 0b00010010, 0b00010011,
0b00010100, 0b00010101, 0b00010110, 0b00010111, 0b00011000, 0b00011001, 0b00011010, 0b00011011, 0b00011100, 0b00011101,
0b00011110, 0b00011111, 0b00100000, 0b00100001, 0b00100010, 0b00100011, 0b00100100, 0b00100101, 0b00100110, 0b00100111,
0b00101000, 0b00101001, 0b00101010, 0b00101011, 0b00101100, 0b00101101, 0b00101110, 0b00101111, 0b00110000, 0b00110001,
0b00110010, 0b00110011, 0b00110100, 0b00110101, 0b00110110, 0b00110111, 0b00111000, 0b00111001, 0b00111010, 0b00111011,
0b00111100, 0b00111101, 0b00111110, 0b00111111
};

char toRequest[] = { 0b00100010, 0b00100011, 0b00100100, 0b00100101, 0b00100110, 0b00100111, 0b00101000, 0b00101001, 0b00101010 };
//						0		1		   2	    3		4	  			5		    		6					7			8				9					10
char *lcdOptions[] = {"Anal.", "Dig.1", "Dig.2", "LED on", "LED off", "Analog Monitor:", "Monitor Dig.1:", "Monitor Dig.2:", "ALL sensors", "node MCU status", " <-- Voltar"};

char *lcdAnswersL0[] = {"Analog Sensor:", "Sensor Dig.1:", "Sensor Dig.2:", "LED on", "LED off", "status"};
char *lcdAnswersL1[] = {"ADC=%d V=%0.3f", "bit %d PB", "bit %d PB", "LED bit %d", "LED bit %d", "OK"};

void bTOd();
int convert(int);
void delayButton();
void serialResponse();

char* intTOstring(char int_str[], int);
void displayMessage(char l0[], char l1[]);
void displayMessageIntegerPointer(char l0[], char l1[], int *ip);
void chooseESP();
void chooseSensor();


char* intTOstring(char int_str[], int v)
{
	sprintf(int_str, "%d", v);	
	return int_str;
}

int convert(int n) {
	int dec = 0, i = 0, rem;

	while (n!=0) {
	rem = n % 10;
	n /= 10;
	dec += rem * pow(2, i);
	++i;
	}

	return dec;
}

void delayButton()
{
	while(digitalRead(selectButton) != 0)
	{
		//printf ("\t");
	}
	delay(250); // para não selecionar de novo e repetir requisição
}

void displayMessage(char l0[], char l1[])
{
	lcdClear(lcd);
	lcdPosition(lcd, 0, 0); // para linha 0	// DEFINE A POSIÇÃO ( COLUNA, LINHA) NÃO ACEITA VALORES MAIORES QUE 1 NA LINHA, POIS SÓ TEM DUAS LINHAS
	// lcdPuts(lcd, msg);
	lcdPrintf(lcd, l0);
	lcdPosition(lcd, 0, 1); // para linha 1
	lcdPrintf(lcd, l1);// ***** RETIRAR COMENTÁRIO
	//printf(msg, nodeMCU); // ***** COMENTAR ESSE
}

void displayMessageIntegerPointer(char l0[], char l1[], int *ip)
{
	lcdClear(lcd);
	lcdPosition(lcd, 0, 0); // para linha 0 do LCD
	lcdPrintf(lcd, l0);
	lcdPosition(lcd, 0, 1); // para linha 1 do LCD
	lcdPrintf(lcd, l1, *ip);
}

void serialResponse()
{
	int iLocal = 0;
	char caLocal[10];			
	while(sda != 0) //while(sgc != -1 || sda != 0)
	{	//printf ("avail %d\n", serialDataAvail(fd));
		sgc = serialGetchar(fd);        	
		sda = serialDataAvail(fd);
		//printf ("sDA = %d\n", sda);
		//printf ("sGC = %d\n", sgc);
		printf ("%c", sgc);
		fflush (stdout) ;
		if(sgc != -1)
		{
			caLocal[iLocal] = (char) sgc;
			iLocal++;
		}
		else
		{      	
			printf ("\nTIMEOUT\n");
			timeOut = true;
			iLocal = 0;
			displayMessage("NAO responde", "(TIMEOUT)");
		}
	}
	printf ("\n");
	sda = 9;
	sgc = 9;
	printf ("\n");
	if(timeOut)
	{
		timeOut = false;
	}
	else
	{
		int integerValue;
		sscanf(caLocal, "%d", &integerValue);
		printf("VALOR INTEIRO É : %d\n", integerValue);
		//printf("VALOR convertido É : %d\n", convert(integerValue));				
		int part = convert(integerValue);
		float volts = part*3.3/1024;				
		printf("VALOR convertido É : %d\n", part);				
		printf ("\n");
		lcdClear(lcd);
		
		/* PARA LIHA 0 DO LCD */
		
		lcdPosition(lcd, 0, 0);
		
		if(sensor == 5) {
			lcdPrintf(lcd, lcdAnswersL0[0]);
		}
		else if(sensor == 6) {
			lcdPrintf(lcd, lcdAnswersL0[1]);
		}
		else if(sensor == 7) {
			lcdPrintf(lcd, lcdAnswersL0[2]);
		}
		else /*(sensor < 5)*/
		{
			lcdPrintf(lcd, lcdAnswersL0[sensor]);		    	
		}
		
		/* PARA LIHA 1 DO LCD */
		
		lcdPosition(lcd, 0, 1);
		if(sensor == 0 || sensor == 5)
		{
			if(part > 1023)
			{
				lcdPrintf(lcd, "READING ERROR");
			}
			else
				lcdPrintf(lcd, lcdAnswersL1[0], part, volts);
		}
		else if(sensor == 6 || sensor == 7)
			{lcdPrintf(lcd, lcdAnswersL1[1], integerValue);}
// 		else if(sensor == 7)
// 			{lcdPrintf(lcd, lcdAnswersL1[2], integerValue);}
		else if (sensor == 1 || sensor == 2)
			{lcdPrintf(lcd, lcdAnswersL1[sensor], integerValue);}
		else if (sensor == 3 || sensor == 4)
			{lcdPrintf(lcd, lcdAnswersL1[sensor], integerValue);}
		else if(sensor == 8) {
		    /* PARA LIHA 0 DO LCD */
    		lcdPosition(lcd, 0, 0);
    		
    		if(allMonitors == 0) {
    			lcdPrintf(lcd, lcdAnswersL0[0]);
    		}
    		if(allMonitors == 1) {
    			lcdPrintf(lcd, lcdAnswersL0[1]);
    		}
    		if(allMonitors == 2) {
    			lcdPrintf(lcd, lcdAnswersL0[2]);
    		}
    		
    		/* PARA LIHA 1 DO LCD */
		    lcdPosition(lcd, 0, 1);
    		
    		if(allMonitors == 0) {
    			if(part > 1023)
    			{
    				lcdPrintf(lcd, "READING ERROR");
    			}
    			else
    				lcdPrintf(lcd, lcdAnswersL1[0], part, volts);
    		}
    		if(allMonitors == 1) {
    			lcdPrintf(lcd, lcdAnswersL1[1], integerValue);
    		}
    		if(allMonitors == 2) {
    			lcdPrintf(lcd, lcdAnswersL1[2], integerValue);
    		}
		}
		else //if(sensor == 9)
		{
		    if(part == (int) protocolCodes[33])
		    {
		        printf("NODE OK");
				displayMessage(lcdAnswersL0[5], lcdAnswersL1[5]);
		    }
		    else
		    {
		        printf("E R R O");
				displayMessage("E R R O", "E R R O");
		    }
		    delay(1000);
		}
	}
	delay(1000);
}

void chooseSensor()
{
	while(1)
	{
		displayMessage("Escolha Opcao:", lcdOptions[sensor]); // ***** RETIRAR COMENTÁRIO
		if (digitalRead(selectButton) == 0)
		{
			delay(250);
			while(digitalRead(selectButton) == 0) // Returns the value read at the given pin. It will be HIGH or LOW (0 or 1). SE NÃO LARGAR O BOTÃO
			{	//delay(500);
				printf ("solta o botão! \n");
			}
			if(sensor == 10)
				break; // <-- VOLTAR		
			else if(sensor == 5) {
				while (digitalRead(selectButton) == 1)
				{
				    serialPutchar(fd, toRequest[0]);
				    serialResponse();
				}	// se não funcionar colocar o subButton
				displayMessage("monitoring OFF", "back to the menu");
				delay(1000);
			}
			else if(sensor == 6) {
				while (digitalRead(selectButton) == 1)
				{
				    serialPutchar(fd, toRequest[1]);
					serialResponse();
				}	// se não funcionar colocar o subButton
				displayMessage("monitoring OFF", "back to the menu");
				delay(1000);
			}		      
			else if(sensor == 7) {
				while (digitalRead(selectButton) == 1)
				{
				    serialPutchar(fd, toRequest[2]);
					serialResponse();
				}	// se não funcionar colocar o subButton
				displayMessage("monitoring OFF", "back to the menu");
				delay(1000);
			}
			else if(sensor == 8) {
				displayMessage("mostraremos 1", "sensor por seg.");
                delay(1000);
			    while (digitalRead(selectButton) == 1)
				{
				    serialPutchar(fd, toRequest[allMonitors]);
				    serialResponse();
					allMonitors++;
					if(allMonitors > 2)
					    allMonitors = 0;
				}	// se não funcionar colocar o subButton
				displayMessage("monitoring OFF", "back to the menu");
				delay(1000);
			}
			else if(sensor == 9) {
			    displayMessage("enviando ...", "requisicao ...");
			    serialPutchar(fd, protocolCodes[nodeMCU]);
			    printf ("\n%d\n", protocolCodes[nodeMCU]);
				serialResponse();
				delayButton();
			}
			else {
				displayMessage("enviando ...", "requisicao ...");
				printf ("\n%d\n", toRequest[sensor]);
				serialPutchar(fd, toRequest[sensor]);
				serialResponse();
				delayButton();
			}
		}
		if (digitalRead(addButton) == 0)
		{
			sensor++;
			delay(100);
			displayMessage("Escolha Opcao:", lcdOptions[sensor]); // ***** RETIRAR COMENTÁRIO
		}
		if (digitalRead(subButton) == 0)
		{
			sensor--;
			delay(100);
			displayMessage("Escolha Opcao:", lcdOptions[sensor]); // ***** RETIRAR COMENTÁRIO
		}
		delay(250); // PRECISA
	}
}

void chooseESP()
{
	while(1)
	{
		displayMessageIntegerPointer("Escolher ESP:", "node MCU = %d", &nodeMCU); // ***** RETIRAR COMENTÁRIO
		//readKey();
		
		if (digitalRead(selectButton) == 0)
		{
			delay(250);
			while(digitalRead(selectButton) == 0) // Returns the value read at the given pin. It will be HIGH or LOW (0 or 1). SE NÃO LARGAR O BOTÃO
			{	//delay(500);
				printf ("solta o botão! \n");
			}
			chooseSensor();
		}
		if (digitalRead(addButton) == 0)
		{
			nodeMCU++;
			delay(100);
			displayMessageIntegerPointer("Escolher ESP:", "node MCU = %d", &nodeMCU); // ***** RETIRAR COMENTÁRIO
		}
		if (digitalRead(subButton) == 0)
		{
			nodeMCU--;
			delay(100);
			displayMessageIntegerPointer("Escolher ESP:", "node MCU = %d", &nodeMCU); // ***** RETIRAR COMENTÁRIO
		}
		delay(100);
	}
}

int main()
{
	if (wiringPiSetup() < 0) return 1;
	if((fd = serialOpen("/dev/ttyS3",115200)) < 0) return 1;
	pinMode(subButton,INPUT);// Sets the pin as input.
	pinMode(selectButton,INPUT);// Sets the pin as input.
	pinMode(addButton,INPUT);// Sets the pin as input.
	pullUpDnControl(subButton, PUD_UP); // Sets the Pull-up mode for the pin.
	pullUpDnControl(selectButton, PUD_UP); // Sets the Pull-up mode for the pin.
	pullUpDnControl(addButton, PUD_UP); // Sets the Pull-up mode for the pin.
	pinMode(DIP1,INPUT);// Sets the pin as input.
	pinMode(DIP2,INPUT);// Sets the pin as input.
	pinMode(DIP3,INPUT);// Sets the pin as input.
	pinMode(DIP4,INPUT);// Sets the pin as input.
	lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0); // (ROWS, COLUMNS, BIT MODE, LCD_RS, LCD_E, LCD_D0, LCD_D1, LCD_D2, LCD_D3, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
	printf("ligado\n");
	printf("\n");
	chooseESP();
	serialClose(fd);
	
// 	while(1)
// 	{
// 	    if(digitalRead(DIP4) == 1)
//     	{
//     	   // printf("HIGH\n");
//     	   printf("ligado\n");
//     	   printf("\n");
//     	   chooseESP();
//     	}
//     	else
//     	{
//     	    printf("DESLIGADO\n");
//     	   // printf("LOW\n");
//     	   serialClose(fd);
//     	}
// 	}
	return 0;
}

void bTOd()
{
	int integerValue;
	sscanf(ca, "%d", &integerValue);
	printf("VALOR INTEIRO É : %d\n", integerValue);
	printf("VALOR convertido É : %d\n", convert(integerValue));
	for (i = 0; i < 10; i++) {
		ca[i]=0;
	}
}

/*	protocol Codes	*/ 

// REQUISIÇÕES

// 0b00000000   ALL ESPs (all node MCUs) enviar mensagem para todas.
// 0b00000001   ESP01
// 0b00000010	ESP02
// 0b00000011	ESP03
// 0b00000100	ESP04
// 0b00000101	ESP05
// 0b00000110	ESP06
// 0b00000111	ESP07
// 0b00001000	ESP08
// 0b00001001	ESP09
// 0b00001010	ESP10
// 0b00001011	ESP11
// 0b00001100	ESP12
// 0b00001101	ESP13
// 0b00001110	ESP14
// 0b00001111	ESP15
// 0b00010000	ESP16
// 0b00010001	ESP17
// 0b00010010	ESP18
// 0b00010011	ESP19
// 0b00010100	ESP20
// 0b00010101	ESP21
// 0b00010110	ESP22
// 0b00010111	ESP23
// 0b00011000	ESP24
// 0b00011001	ESP25
// 0b00011010	ESP26
// 0b00011011	ESP27
// 0b00011100	ESP28
// 0b00011101	ESP29
// 0b00011110	ESP30
// 0b00011111	ESP31
// 0b00100000   ESP32

// RESPOSTAS

// char *lcdOptions[] = {"Anal.", "Dig.1", "Dig.2", "LED on", "LED off", "Analog Monitor:", "Monitor Dig.1:", "Monitor Dig.2:", "ALL sensors", "node MCU status", " <-- Voltar"};

// 0b00100001   resposta node MCU ok (status de funcionamento da unidade)
// 0b00100010	Analog Sensor
// 0b00100011   Digital sensor 1
// 0b00100100	Digital sensor 2
// 0b00100101	LED on
// 0b00100110	LED off
// 0b00100111	Analog Sensor Monitoring
// 0b00101000	Analog Sensor 1 Monitoring
// 0b00101001	Analog Sensor 2 Monitoring
// 0b00101010	ALL sensors Monitoring
// 0b00101011
// 0b00101100
// 0b00101101
// 0b00101110
// 0b00101111
// 0b00110000
// 0b00110001
// 0b00110010
// 0b00110011
// 0b00110100
// 0b00110101
// 0b00110110
// 0b00110111
// 0b00111000
// 0b00111001
// 0b00111010
// 0b00111011
// 0b00111100
// 0b00111101
// 0b00111110
// 0b00111111







	
/* ==================================================================================== */
/*                                      O QUE FATA FAZER                                */
/* ==================================================================================== */

// Mecanismo de controle de status de funcionamento das unidades; (concatecar 'ESPxy' em cada unidade para identificar)

// Os comandos serão compostos por palavras de 8 bits (ver tabelas a seguir);

// A informação medida deve ter a maior precisão possível;

// As requisições do SBC podem ser direcionadas para uma unidade específica ou a todas;

// As solicitações e as respostas deverão ser exibidas no display LCD.

// 0x21 Acendimento do led da NodeMCU

// rever mensagems de resposta do display para botões pois tem duas variaveis com ldcPrint recedendo no paraetro quando quero potenciometro

/* ==================================================================================== */

// how to create threads using c language?
// https://www.electronicwings.com/raspberry-pi/raspberry-pi-uart-communication-using-python-and-c
// https://www.onlinegdb.com/online_c_compiler#
// https://www.includehelp.com/articles/threading-in-c-programming-language-with-gcc-linux.aspx
// https://wokwi.com/projects/new/pi-pico-w-sdk
// http://wiringpi.com/reference/serial-library/
// https://projects.drogon.net/raspberry-pi/wiringpi/serial-library/
// https://forum.odroid.com/viewtopic.php?t=33538
// https://forums.raspberrypi.com/viewtopic.php?t=213224
// http://abyz.me.uk/rpi/pigpio/piscope.html
// https://randomnerdtutorials.com/esp8266-adc-reading-analog-values-with-nodemcu/
// https://portal.vidadesilicio.com.br/lendo-um-potenciometro-com-o-esp8266-nodemcu/
// https://panoramablog.space/blog/arduino-como-melhorar-a-precisao-da-entrada-analogica/
// https://reference.arduino.cc/reference/pt/language/functions/analog-io/analogread/
// https://cdn.arduino.cc/reference/pt/language/functions/zero-due-mkr-family/analogreadresolution/

//https://docs.arduino.cc/learn/microcontrollers/analog-input

// void pressButton() {
// 	  while(1)
// 	    {
// 	      if (digitalRead(selectButton) == 0)
// 	      {
// 		// printf ("selectButton PRESS\n");
// 		delay(100);
// 		while(digitalRead(selectButton) == 0) // Returns the value read at the given pin. It will be HIGH or LOW (0 or 1). SE NÃO LARGAR O BOTÃO
// 		{
// 		  //delay(500);
// 		  printf ("solta o botão! \n");
// 		}
// 		protocoll = true;
// 		break;
// 	      }
// 	      delay(100);
// 	    }
// 	}

//https://www.includehelp.com/c/working-with-hexadecimal-values-in-c-programming-language.aspx
//https://www.includehelp.com/c/working-with-hexadecimal-values-in-c-programming-language.aspx
//https://www.includehelp.com/c/working-with-hexadecimal-values-in-c-programming-language.aspx
//https://www.geeksforgeeks.org/format-specifiers-in-c/
//https://www.geeksforgeeks.org/format-specifiers-in-c/
//https://www.geeksforgeeks.org/format-specifiers-in-c/



