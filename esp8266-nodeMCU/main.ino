
# include <ESP8266WiFi.h>
# include <ESP8266mDNS.h>
# include <WiFiUdp.h>
# include <ArduinoOTA.h>

# ifndef STASSID
# define STASSID "INTELBRAS"
# define STAPSK  "Pbl-Sistemas-Digitais"
# endif

const char* ssid = STASSID; 
const char* password = STAPSK;
const char* host = "ESP-10.0.0.108";

int led_pin = LED_BUILTIN;

int buttonD0 = D0; // push button is connected
int buttonD1 = D1; // push button is connected
int temp0 = 0;   // temporary variable for reading the button pin status
int temp1 = 0;   // temporary variable for reading the button pin status

# define N_DIMMERS 3
int dimmer_pin[] = {14, 5, 15};

/* POTENCIOMETRO */
/* const int analogInPin = A0; */ // ESP8266 Analog Pin ADC0 = A0  
int analogInPin = A0;
int sensorValue = 0;  // value read from the pot
/* POTENCIOMETRO */
char arrb[]={0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100};      

char protocolCodes[] = {
0b00000000, 0b00000001, 0b00000010, 0b00000011, 0b00000100, 0b00000101, 0b00000110, 0b00000111, 0b00001000, 0b00001001,
0b00001010, 0b00001011, 0b00001100, 0b00001101, 0b00001110, 0b00001111, 0b00010000, 0b00010001, 0b00010010, 0b00010011,
0b00010100, 0b00010101, 0b00010110, 0b00010111, 0b00011000, 0b00011001, 0b00011010, 0b00011011, 0b00011100, 0b00011101,
0b00011110, 0b00011111, 0b00100000, 0b00100001, 0b00100010, 0b00100011, 0b00100100, 0b00100101, 0b00100110, 0b00100111,
0b00101000, 0b00101001, 0b00101010, 0b00101011, 0b00101100, 0b00101101, 0b00101110, 0b00101111, 0b00110000, 0b00110001,
0b00110010, 0b00110011, 0b00110100, 0b00110101, 0b00110110, 0b00110111, 0b00111000, 0b00111001, 0b00111010, 0b00111011,
0b00111100, 0b00111101, 0b00111110, 0b00111111
};
/*                    analogico   digital 1   digital 2
//      0 1    2      3   4   5       6     7     8
char *lcdOptions[] = {"Anal.", "Dig.1", "Dig.2", "LED on", "LED off", "Analog Monitor:", "Monitor Dig.1:", "Monitor Dig.2:", "ALL sensors", "node MCU status", " <-- Voltar"};
*/
char toRequest[] = { 0b00100010, 0b00100011, 0b00100100, 0b00100101, 0b00100110, 0b00100111, 0b00101000, 0b00101001, 0b00101010 };

void setup() {

  // pinMode(D0, INPUT);
  /* BaudRate */
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
  }
  /* switch off led */
  digitalWrite(led_pin, LOW);

  /* configure dimmers, and OTA server events */
  analogWriteRange(1000);
  analogWrite(led_pin, 990);

  for (int i = 0; i < N_DIMMERS; i++) {
    pinMode(dimmer_pin[i], OUTPUT);
    analogWrite(dimmer_pin[i], 50);
  }

  ArduinoOTA.setHostname(host);
  ArduinoOTA.onStart([]() { // switch off all the PWMs during upgrade
    for (int i = 0; i < N_DIMMERS; i++) {
      analogWrite(dimmer_pin[i], 0);
    }
    analogWrite(led_pin, 0);
  });

  ArduinoOTA.onEnd([]() { // do a fancy thing with our board led at end
    for (int i = 0; i < 30; i++) {
      analogWrite(led_pin, (i * 100) % 1001);
      delay(50);
    }
  });

  ArduinoOTA.onError([](ota_error_t error) {
    (void)error;
    ESP.restart();
  });

  /* setup the OTA server */
  ArduinoOTA.begin();

  /* switch on led */
  pinMode(led_pin, OUTPUT);
  pinMode(buttonD0, INPUT); // declare push button as input
  pinMode(buttonD1, INPUT); // declare push button as input
  /* pinMode(analogInPin, INPUT); */
}

void loop() {
  ArduinoOTA.handle();
  
  /* NÃO RETIRAR A FUNÇÃO DA LINHA ACIMA */  

  
  if(Serial.available() > 0) { /* CHECA SE ESTÁ RECEBENDO DADOS */
      /* pega valor de RX */
      //  char c = Serial.read();
      //  if(c == 0b1){        
      //String c = Serial.readString();
      String c="";
      char hex = Serial.read();
      if(hex == protocolCodes[1] ){
//        sensorValue = analogRead(analogInPin);
//        Serial.print("FUNFA"); /* ENVIA O VALOR DO POTENCIOMENTRO */
//        Serial.print(sensorValue, BIN); /* ENVIA O VALOR DO POTENCIOMENTRO */
          Serial.print(protocolCodes[33], BIN); 
      }
      
      if(hex == toRequest[0] ){
        sensorValue = analogRead(analogInPin);
        Serial.print(sensorValue, BIN); /* ENVIA O VALOR DO POTENCIOMENTRO */
      }
      if(hex == toRequest[1] ){
        temp0 = digitalRead(buttonD0);
        if (temp0 == HIGH) {
          Serial.print(1, BIN);
        }
        else {
          Serial.print(0, BIN);
        }
      }
      if(hex == toRequest[2] ){
        temp1 = digitalRead(buttonD1);       
        if (temp1 == HIGH) {
          Serial.print(1, BIN);
        }
        else {
          Serial.print(0, BIN);
        }
      }            
      if(hex == toRequest[3] ){
        digitalWrite(led_pin, LOW);
        Serial.print(1, BIN);
      }
      if(hex == toRequest[4] ){
        digitalWrite(led_pin, HIGH);
        Serial.print(0, BIN);
      }      
      if(hex == protocolCodes[0] ){
        //Serial.println(3, BIN); // envia resposta com número da ESP para saber que ela está ativa.
        Serial.println(3, BIN); // envia resposta com número da ESP para saber que ela está ativa.
      }
//      
//      if(c.equals("ESP3.Anal")){
//        sensorValue = analogRead(analogInPin);
//        Serial.print(sensorValue, BIN); /* ENVIA O VALOR DO POTENCIOMENTRO */
//      }
//      if(c.equals("ESP3.Dig.1")){
//        temp0 = digitalRead(buttonD0);
//        if (temp0 == HIGH) {
//          Serial.print(1, BIN);
//        }
//        else {
//          Serial.print(0, BIN);
//        }
//      }
//      if(c.equals("ESP3.Dig.2")){        
//        temp1 = digitalRead(buttonD1);
//        if (temp1 == HIGH) {
//          Serial.print(1, BIN);
//        }
//        else {
//          Serial.print(0, BIN);
//        }
//      }
//      if(c.equals("ESP3.LEDon")){
//        digitalWrite(led_pin, LOW);
//        Serial.print(1, BIN);
//      }
//      if(c.equals("ESP3.LEDoff")){
//        digitalWrite(led_pin, HIGH);
//        Serial.print(0, BIN);
//      }
  }
}
