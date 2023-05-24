
/* COMANDOS DO CONSOLE PARA COMPILAR E EXECUTAR	*/

// gcc p.c -o p -lwiringPi -lwiringPiDev -lpthread -lm -lcrypt -lrt && chmod +x p
// sudo ./p

// rm p.c && nano p.c
/* COMANDOS DO CONSOLE PARA COMPILAR E EXECUTAR	*/

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
char espnode = 0b00000001;
char analog = 0b00100010;
char dig1 = 0b00100011;
char dig2 = 0b00100100;
char ledON = 0b00100101;
char ledOFF = 0b00100110;
char okStatus = 0b00100001;
char request = 0b00100001;
char responseCode = 0b00111111;
char allNodesMCU = 0b00111111;

// push buttons
char subButton = 19;
char selectButton = 23;
char addButton = 25;

bool monitor = true;
bool timeOut = false;
bool enviarParaTodos = false;
int fd;
int lcd;
int i = 0;
int allMonitors = 0;

int mainMenu = 0;
int nodeMCU = 1;
int oldNodeMCU = 0;
int sensor = 0;
int soma = 0;
int sda = 9;
int sgc = 9;
int part = -1;
float volts = -1.0;

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
//						0		1		   2	    3		4	  			5		    		6					78				9					10
// char *lcdOptions[] = {"Anal.", "Dig.1", "Dig.2", "LED on", "LED off", "Analog Monitor:", "Monitor Dig.1:", "Monitor Dig.2:", "ALL sensors", "node MCU status", " <-- Voltar"};
char *lcdOptions[] = {"Anal.", "Dig.1", "Dig.2", "LED on", "LED off", "Analog Monitor:", "Monitor Dig.1:", "Monitor Dig.2:", "ALL sensors", " <-- Voltar"};
char *lcdMainOptions[] = {"Escolher ESP:", "BROADCAST", " <-- Voltar", "node MCU status"};

char *lcdAnswersL0[] = {"Analog Sensor:", "Sensor Dig.1:", "Sensor Dig.2:", "LED on", "LED off", "status"};
char *lcdAnswersL1[] = {"ADC=%d V=%0.3f", "bit %d PB", "bit %d PB", "LED bit %d", "LED bit %d", "OK"};

int allNodesBroadcast[32];
int broadcastIndex = 0;

/* INICIO definição das funções (PRTÓTIPOS)	*/
void bTOd();
int convert(int);
void delayButton();
void serialResponseBroadcast();
void respostaSerial();
void serialResponse();
char* intTOstring(char int_str[], int);
void displayMessage(char l0[], char l1[]);
void displayMessageIntegerPointer(char l0[], char l1[], int *ip);
void chooseOptions();
void chooseESP();
void chooseSensor();
/* FIM definição das funções (PRTÓTIPOS)	*/

char* intTOstring(char int_str[], int v)
{
	sprintf(int_str, "%d", v);	
	return int_str;
}

int convert(int n) {	// CONVERTE BINARIO EM DECIMAL
	int dec = 0, i = 0, rem;

	while (n!=0) {
	rem = n % 10;
	n /= 10;
	dec += rem * pow(2, i);
	++i;
	}

	return dec;
}

void delayButton()	// enquanto não pressionar o botão não sai do laço
{
	while(digitalRead(selectButton) != 0)
	{
		//printf ("\t");
	}
	delay(250); // para não selecionar de novo e repetir requisição
}

void displayMessage(char l0[], char l1[])	// configura o LCD para exibir texto necessário
{
	lcdClear(lcd);
	lcdPosition(lcd, 0, 0); // para linha 0	// DEFINE A POSIÇÃO ( COLUNA, LINHA) NÃO ACEITA VALORES MAIORES QUE 1 NA LINHA, POIS SÓ TEM DUAS LINHAS
	// lcdPuts(lcd, msg);
	lcdPrintf(lcd, l0);
	lcdPosition(lcd, 0, 1); // para linha 1
	lcdPrintf(lcd, l1);
}

void displayMessageIntegerPointer(char l0[], char l1[], int *ip)	// configura o LCD para exibir texto necessário E concatena com valor inteiro
{
	lcdClear(lcd);
	lcdPosition(lcd, 0, 0); // para linha 0 do LCD
	lcdPrintf(lcd, l0);
	lcdPosition(lcd, 0, 1); // para linha 1 do LCD
	lcdPrintf(lcd, l1, *ip);
}

void serialResponseBroadcast()	// espera a resposta da mensagem de BROADCAST
{
	int iLocal = 0;
	char caLocal[10];
	printf ("aqui 1\n");
	while(sda != 0)
	{
		sgc = serialGetchar(fd);        	
		printf ("char %c\n", sgc);
		sda = serialDataAvail(fd);
		printf ("AVAIL %d\n", sda);
		// printf ("%c", sgc);
		fflush (stdout);
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
	printf ("aqui 2\n");
	printf ("\n");
	sda = 9;
	sgc = 9;
	if(timeOut)
	{
		timeOut = false;
	}
	else
	{
		int integerValue;
		sscanf(caLocal, "%d", &integerValue);
		printf("broad cast VALOR INTEIRO É : %d\n", integerValue);
		part = convert(integerValue);
		printf("broad cast VALOR convertido É : %d\n", part);
		if(enviarParaTodos)
		    allNodesBroadcast[broadcastIndex] = part;
		broadcastIndex++;
	}
}

void serialResponse()	// espera a resposta serial da UART
{
	int iLocal = 0;
	char caLocal[10];
	printf ("aqui 1\n");
	while(sda != 0)
	{
		sgc = serialGetchar(fd);        	
		printf ("char %c\n", sgc);
		sda = serialDataAvail(fd);
		printf ("AVAIL %d\n", sda);
		// printf ("%c", sgc);
		fflush (stdout);
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
	printf ("aqui 2\n");
	printf ("\n");
	sda = 9;
	sgc = 9;
	if(timeOut)
	{
		timeOut = false;
	}
	else
	{
		int integerValue;
		sscanf(caLocal, "%d", &integerValue);
		printf("VALOR INTEIRO É : %d\n", integerValue);
		part = convert(integerValue);
		printf("VALOR convertido É : %d\n", part);
	}
}

void respostaSerial()	// exibe mensagems no display LCD de acordo com as opções escolhidas no Menu
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
		fflush (stdout);
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
		// int part = convert(integerValue);
		// float volts = part*3.3/1024;
		part = convert(integerValue);
		volts = part*3.3/1024;
		printf ("teste volts = %f\n", volts);
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
		printf ("\n");
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
	printf ("\n");
}

void chooseSensor()	// permite escolher sensores, Monitoramento e outras opções exibidas na linha 1 do LCD
{
    printf("Escolher SENSOR:\n");
	while(1)
	{
		displayMessage("Escolha Opcao:", lcdOptions[sensor]);
		if (digitalRead(selectButton) == 0)
		{
			delay(250);
			while(digitalRead(selectButton) == 0) // SE NÃO LARGAR O BOTÃO
			{	//delay(500);
				printf ("solta o botão! \n");
			}
			// if(sensor == 10)
			if(sensor == 9)
			{
				oldNodeMCU = nodeMCU;
				nodeMCU = 0; // FAZ VOLTAR AO INICIO
				break; // <-- VOLTAR	// SAI DO LAÇO ATUAL	
			}
			else if(sensor == 5) {
				while (digitalRead(selectButton) == 1)
				{
				    serialPutchar(fd, toRequest[0]);
				    respostaSerial();
				}	// se não funcionar colocar o subButton
				displayMessage("monitoring OFF", "back to the menu");
				delay(1000);
			}
			else if(sensor == 6) {
				while (digitalRead(selectButton) == 1)
				{
				    serialPutchar(fd, toRequest[1]);
					respostaSerial();
				}	// se não funcionar colocar o subButton
				displayMessage("monitoring OFF", "back to the menu");
				delay(1000);
			}		      
			else if(sensor == 7) {
				while (digitalRead(selectButton) == 1)
				{
				    serialPutchar(fd, toRequest[2]);
					respostaSerial();
				}	// se não funcionar colocar o subButton
				displayMessage("monitoring OFF", "back to the menu");
				delay(1000);
			}
			else if(sensor == 8) {
				displayMessage("mostraremos 1", "sensor por seg.");
                delay(1000);
			    while (digitalRead(selectButton) == 1)
				{
				    delay(2000);
				    serialPutchar(fd, toRequest[allMonitors]);
				    respostaSerial();
					allMonitors++;
					if(allMonitors > 2)
					    allMonitors = 0;
				}	// se não funcionar colocar o subButton
				displayMessage("monitoring OFF", "back to the menu");
				delay(1000);
			}
			// else if(sensor == 9) {
			//     displayMessage("enviando ...", "requisicao ...");
			//     serialPutchar(fd, protocolCodes[nodeMCU]);
			//     printf ("\n%d\n", protocolCodes[nodeMCU]);
			// 	respostaSerial();
			// 	delayButton();
			// }
			else {
				displayMessage("enviando ...", "requisicao ...");
				printf ("\n%d\n", toRequest[sensor]);
				serialPutchar(fd, toRequest[sensor]);
				respostaSerial();
				delayButton();
			}
		}
		if (digitalRead(addButton) == 0)
		{
			sensor++;
			if(sensor > 9) sensor = 0;
			delay(100);
		}
		if (digitalRead(subButton) == 0)
		{
			sensor--;
			if(sensor < 0) sensor = 9;
			delay(100);
		}
		delay(250); // PRECISA
		if(digitalRead(DIP4) == 0)
		{
    	    printf("DESLIGADO\n");
    	    mainMenu = 0;
            nodeMCU = 1;
            oldNodeMCU = 0;
            sensor = 0;
            chooseOptions();
    	    lcdClear(lcd);
    	    break;
		}
	}
}

void chooseESP()	// permite escolher node na linha 1 do LCD
{
    printf("Escolher ESP:\n");
	while(1)
	{
		if(nodeMCU == 0)
		{
			nodeMCU = oldNodeMCU; // devolve valor coerente para ESP
			break;	// PARA VOLTAR AO MENU ANTERIOR		
		}
		displayMessageIntegerPointer("Escolher ESP:", "node MCU = %d", &nodeMCU);
		if (digitalRead(selectButton) == 0)
		{
			delay(250);
			while(digitalRead(selectButton) == 0) // SE NÃO LARGAR O BOTÃO
			{	//delay(500);
				// printf ("solta o botão! \n");
			}
			displayMessage(lcdMainOptions[3], "pedir status");
			serialPutchar(fd, protocolCodes[nodeMCU]);
			serialResponse();
			printf("part = %d\n", part);
			if(part == okStatus)
			{
				printf("AÇÔÔÔÔÔÔ !\n");
				displayMessage(lcdAnswersL0[5], lcdAnswersL1[5]);
				chooseSensor();
			}
			else
			{
				printf("não açô\n");
				displayMessage("NAO responde", "(TIMEOUT)");
				delayButton();
			}
		}
		if (digitalRead(addButton) == 0)
		{
			nodeMCU++;
			if(nodeMCU > 32) nodeMCU = 1;
			delay(100);
		}
		if (digitalRead(subButton) == 0)
		{
			nodeMCU--;
			if(nodeMCU < 1) nodeMCU = 32;
			delay(100);
		}
		if(digitalRead(DIP4) == 0)
		{
    	    printf("DESLIGADO\n");
    	    mainMenu = 0;
            nodeMCU = 1;
            oldNodeMCU = 0;
            sensor = 0;
            chooseOptions();
    	    lcdClear(lcd);
    	    break;
		}
		delay(100);
	}
}

void chooseOptions()	// ESCOLHER NODE OU ENVIAR MENSAGEM PARA TODAS AS NODES
{
    printf("Escolher Opcao:\n");
	while(1)
	{
		displayMessage("Escolher Opcao:", lcdMainOptions[mainMenu]);
		if (digitalRead(selectButton) == 0)
		{
			delay(250);
			while(digitalRead(selectButton) == 0) // SE NÃO LARGAR O BOTÃO
			{	//delay(500);
				printf ("solta o botão! \n");
			}
			if(mainMenu == 0)	// ESCOLHER NODE
			{
			    chooseESP();
			}
			if(mainMenu == 1)	// BROADCAST
			{
				enviarParaTodos = true;
				displayMessage(lcdMainOptions[1], "enviar...");
				serialPutchar(fd, allNodesMCU);
				printf ("ENVIOU! \n");
				serialResponseBroadcast();
				printf ("PAROU ! \n");
				displayMessage("TOTAL", intTOstring(int_str, broadcastIndex));
				delayButton();
				enviarParaTodos = false;
				broadcastIndex = 0;
			}
		}
		if (digitalRead(addButton) == 0)
		{
			mainMenu++;
			if(mainMenu > 1) mainMenu = 0;
			delay(100);
		}
		if (digitalRead(subButton) == 0)
		{
			mainMenu--;
			if(mainMenu < 0) mainMenu = 1;
			delay(100);
		}
		if(digitalRead(DIP4) == 0)
		{
    	    printf("DESLIGADO\n");
    	    lcdClear(lcd);
    	    mainMenu = 0;
            nodeMCU = 1;
            oldNodeMCU = 0;
            sensor = 0;
    	    break;
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
// 	printf("ligado\n");
// 	chooseOptions();
// 	serialClose(fd);
	
	while(1) // ENQUANTO O DIP SWITCH NÃO ESTIVER LIGADO NADA ACONTECE. SE ESTIVER DESLIGADO TUDO PARA DE FUNCIONAR
	{
	    if(digitalRead(DIP4) == 1)
    	{
    	   printf("ligado\n");
    	   printf("\n");
    	   chooseOptions(); // ESCOLHER NODE OU ENVIAR MENSAGEM PARA TODAS AS NODES
    	}
    	else
    	{
    	    printf("DESLIGADO\n");
    	    lcdClear(lcd);
    	    mainMenu = 0;
            nodeMCU = 1;
            oldNodeMCU = 0;
            sensor = 0;
    	    lcdClear(lcd);
    	}
	}
	serialClose(fd);
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

