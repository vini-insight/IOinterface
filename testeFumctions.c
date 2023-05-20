
/* ======================================================================================================================================================================== */
/*                                      INICIO DAS FUNÇÕES DE TESTE (REMOVER QUANDO TESTAR NA ORANGE PI)                                                                    */
/* ======================================================================================================================================================================== */
#define INPUT 0
#define PUD_UP 1

char key = ' ';
int numbeOFchars = 0;

void clearKey();
void readKey();
int digitalRead(char);
void delay(int);
void uart();
void serialPrintf(int, char msg[]);
// bool serialDataAvail(int);
// char serialGetchar(int);
int serialDataAvail(int);
int serialGetchar(int);
void lcdPosition(int, int, int);
void lcdPrintf(int, char msg[], int);
void lcdClear(int);
int wiringPiSetup();
int serialOpen();
void pinMode(char, int);
void pullUpDnControl(char, int);
int lcdInit(int, int, int, int, int, int, int, int, int, int, int, int, int);
void serialClose(int);

// char subButton = 19;
// char selectButton = 23;
// char addButton = 25;

void clearKey()
{
    key = ' ';
}

void readKey()
{
  scanf("%c", &key);
  while(key != 87 && key != 119 && key != 65 && key != 97 && key != 68 && key != 100)
  {
    scanf("%c", &key);
  }
}

int digitalRead(char b)
{
  // sleep(1);
  if(b == selectButton && (key == 87 || key == 119)) // W
  {
    return 0;
  }
  else if(b == addButton && (key == 68 || key == 100)) // D
  {
    return 0;
  }
  else if(b == subButton && (key == 65 || key == 97)) // A
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

void delay(int t)
{
  usleep(t); // Halting the execution for  Microseconds (10 seconds)
}

void uart()
{

  if(numbeOFchars == 0)
    numbeOFchars = 10;
}
void serialPrintf(int fd, char msg[])
{
  printf("%c", msg);
  printf("\n");
  printf("%d", msg);
  printf("\n");
  uart();
}

// bool serialDataAvail(int fd)
int serialDataAvail(int fd)
{
  if(numbeOFchars > -1)
    return numbeOFchars;
  else
    return -1;
}
// char serialGetchar(int fd)
int serialGetchar(int fd)
{
  numbeOFchars--;
  srand(time(0));
  int num = rand();
  if(num % 2 == 0)
      return (char) 48;
  else
      return (char) 49;
}
void lcdPosition(int lcd, int c, int l)
{
  // FAZ NADA
}

void lcdPrintf(int lcd, char msg[], int nodeMCU)
{
  printf(msg, nodeMCU);
}
void lcdClear(int lcd)
{
  // FAZ NADA
}
int wiringPiSetup()
{
  return 2;
}
int serialOpen()
{
  return 2;
}
void pinMode(char b, int i)
{
  // FAZ NADA
}
void pullUpDnControl(char b, int i)
{
  // FAZ NADA
}
int lcdInit(int l, int c, int m, int rs, int e, int d4, int d5, int d6, int d7, int w, int x, int y, int z)
{
  // FAZ NADA
}
void serialClose(int fd)
{
  // 
}
/* ======================================================================================================================================================================== */
/*                                      FIM DAS FUNÇÕES DE TESTE (REMOVER QUANDO TESTAR NA ORANGE PI)                                                                       */
/* ======================================================================================================================================================================== */
