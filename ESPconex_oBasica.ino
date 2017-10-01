
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>  
#include <TimerOne.h>  

#define DEBUG true
 
#define MAX_DEVICES     1 

 
SoftwareSerial esp8266(2,3);
 

int red =11;

int DataPin = 4;  //Ligar o pino 4 do Arduino ao DIN do modulo  
int ClockPin = 5; //Ligar o pino 5 do Arduino ao CLK do módulo  
int LoadPin = 6;  //Ligar o pino 6 do Arduinio ao pino CS/Load do módulo  
  
byte buffer[8];  


const byte font[][8] PROGMEM = {  
{B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000},   
{B00000100, B00000100, B00000100, B00000100, B00000100, B00000100, B00000000, B00000100},   
{B00001010, B00001010, B00001010, B00000000, B00000000, B00000000, B00000000, B00000000},   
{B00000000, B00001010, B00011111, B00001010, B00011111, B00001010, B00011111, B00001010},   
{B00000111, B00001100, B00010100, B00001100, B00000110, B00000101, B00000110, B00011100},   
{B00011001, B00011010, B00000010, B00000100, B00000100, B00001000, B00001011, B00010011},   
{B00000110, B00001010, B00010010, B00010100, B00001001, B00010110, B00010110, B00001001},   
{B00000100, B00000100, B00000100, B00000000, B00000000, B00000000, B00000000, B00000000},   
{B00000010, B00000100, B00001000, B00001000, B00001000, B00001000, B00000100, B00000010},   
{B00001000, B00000100, B00000010, B00000010, B00000010, B00000010, B00000100, B00001000},   
{B00010101, B00001110, B00011111, B00001110, B00010101, B00000000, B00000000, B00000000},   
{B00000000, B00000000, B00000100, B00000100, B00011111, B00000100, B00000100, B00000000},   
{B00000000, B00000000, B00000000, B00000000, B00000000, B00000110, B00000100, B00001000},   
{B00000000, B00000000, B00000000, B00000000, B00001110, B00000000, B00000000, B00000000},   
{B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000100},   
{B00000001, B00000010, B00000010, B00000100, B00000100, B00001000, B00001000, B00010000},   
{B00001110, B00010001, B00010011, B00010001, B00010101, B00010001, B00011001, B00001110},   
{B00000100, B00001100, B00010100, B00000100, B00000100, B00000100, B00000100, B00011111},   
{B00001110, B00010001, B00010001, B00000010, B00000100, B00001000, B00010000, B00011111},   
{B00001110, B00010001, B00000001, B00001110, B00000001, B00000001, B00010001, B00001110},   
{B00010000, B00010000, B00010100, B00010100, B00011111, B00000100, B00000100, B00000100},   
{B00011111, B00010000, B00010000, B00011110, B00000001, B00000001, B00000001, B00011110},   
{B00000111, B00001000, B00010000, B00011110, B00010001, B00010001, B00010001, B00001110},   
{B00011111, B00000001, B00000001, B00000001, B00000010, B00000100, B00001000, B00010000},   
{B00001110, B00010001, B00010001, B00001110, B00010001, B00010001, B00010001, B00001110},   
{B00001110, B00010001, B00010001, B00001111, B00000001, B00000001, B00000001, B00000001},   
{B00000000, B00000100, B00000100, B00000000, B00000000, B00000100, B00000100, B00000000},   
{B00000000, B00000100, B00000100, B00000000, B00000000, B00000100, B00000100, B00001000},   
{B00000001, B00000010, B00000100, B00001000, B00001000, B00000100, B00000010, B00000001},   
{B00000000, B00000000, B00000000, B00011110, B00000000, B00011110, B00000000, B00000000},   
{B00010000, B00001000, B00000100, B00000010, B00000010, B00000100, B00001000, B00010000},   
{B00001110, B00010001, B00010001, B00000010, B00000100, B00000100, B00000000, B00000100},   
{B00001110, B00010001, B00010001, B00010101, B00010101, B00010001, B00010001, B00011110},   
{B00001110, B00010001, B00010001, B00010001, B00011111, B00010001, B00010001, B00010001},   
{B00011110, B00010001, B00010001, B00011110, B00010001, B00010001, B00010001, B00011110},   
{B00000111, B00001000, B00010000, B00010000, B00010000, B00010000, B00001000, B00000111},   
{B00011100, B00010010, B00010001, B00010001, B00010001, B00010001, B00010010, B00011100},  
{B00011111, B00010000, B00010000, B00011110, B00010000, B00010000, B00010000, B00011111},   
{B00011111, B00010000, B00010000, B00011110, B00010000, B00010000, B00010000, B00010000},   
{B00001110, B00010001, B00010000, B00010000, B00010111, B00010001, B00010001, B00001110},   
{B00010001, B00010001, B00010001, B00011111, B00010001, B00010001, B00010001, B00010001},   
{B00011111, B00000100, B00000100, B00000100, B00000100, B00000100, B00000100, B00011111},   
{B00011111, B00000100, B00000100, B00000100, B00000100, B00000100, B00010100, B00001000},   
{B00010001, B00010010, B00010100, B00011000, B00010100, B00010010, B00010001, B00010001},   
{B00010000, B00010000, B00010000, B00010000, B00010000, B00010000, B00010000, B00011111},   
{B00010001, B00011011, B00011111, B00010101, B00010001, B00010001, B00010001, B00010001},   
{B00010001, B00011001, B00011001, B00010101, B00010101, B00010011, B00010011, B00010001},   
{B00001110, B00010001, B00010001, B00010001, B00010001, B00010001, B00010001, B00001110},   
{B00011110, B00010001, B00010001, B00011110, B00010000, B00010000, B00010000, B00010000},   
{B00001110, B00010001, B00010001, B00010001, B00010001, B00010101, B00010011, B00001111},   
{B00011110, B00010001, B00010001, B00011110, B00010100, B00010010, B00010001, B00010001},   
{B00001110, B00010001, B00010000, B00001000, B00000110, B00000001, B00010001, B00001110},   
{B00011111, B00000100, B00000100, B00000100, B00000100, B00000100, B00000100, B00000100},   
{B00010001, B00010001, B00010001, B00010001, B00010001, B00010001, B00010001, B00001110},   
{B00010001, B00010001, B00010001, B00010001, B00010001, B00010001, B00001010, B00000100},   
{B00010001, B00010001, B00010001, B00010001, B00010001, B00010101, B00010101, B00001010},   
{B00010001, B00010001, B00001010, B00000100, B00000100, B00001010, B00010001, B00010001},   
{B00010001, B00010001, B00001010, B00000100, B00000100, B00000100, B00000100, B00000100},   
{B00011111, B00000001, B00000010, B00000100, B00001000, B00010000, B00010000, B00011111},   
{B00001110, B00001000, B00001000, B00001000, B00001000, B00001000, B00001000, B00001110},   
{B00010000, B00001000, B00001000, B00000100, B00000100, B00000010, B00000010, B00000001},   
{B00001110, B00000010, B00000010, B00000010, B00000010, B00000010, B00000010, B00001110},   
{B00000100, B00001010, B00010001, B00000000, B00000000, B00000000, B00000000, B00000000},   
{B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00011111},   
{B00001000, B00000100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000},   
{B00000000, B00000000, B00000000, B00001110, B00010010, B00010010, B00010010, B00001111},   
{B00000000, B00010000, B00010000, B00010000, B00011100, B00010010, B00010010, B00011100},   
{B00000000, B00000000, B00000000, B00001110, B00010000, B00010000, B00010000, B00001110},   
{B00000000, B00000001, B00000001, B00000001, B00000111, B00001001, B00001001, B00000111},   
{B00000000, B00000000, B00000000, B00011100, B00010010, B00011110, B00010000, B00001110},   
{B00000000, B00000011, B00000100, B00000100, B00000110, B00000100, B00000100, B00000100},   
{B00000000, B00001110, B00001010, B00001010, B00001110, B00000010, B00000010, B00001100},   
{B00000000, B00010000, B00010000, B00010000, B00011100, B00010010, B00010010, B00010010},   
{B00000000, B00000000, B00000100, B00000000, B00000100, B00000100, B00000100, B00000100},   
{B00000000, B00000010, B00000000, B00000010, B00000010, B00000010, B00000010, B00001100},   
{B00000000, B00010000, B00010000, B00010100, B00011000, B00011000, B00010100, B00010000},   
{B00000000, B00010000, B00010000, B00010000, B00010000, B00010000, B00010000, B00001100},   
{B00000000, B00000000, B00000000, B00001010, B00010101, B00010001, B00010001, B00010001},   
{B00000000, B00000000, B00000000, B00010100, B00011010, B00010010, B00010010, B00010010},   
{B00000000, B00000000, B00000000, B00001100, B00010010, B00010010, B00010010, B00001100},   
{B00000000, B00011100, B00010010, B00010010, B00011100, B00010000, B00010000, B00010000},   
{B00000000, B00001110, B00010010, B00010010, B00001110, B00000010, B00000010, B00000001},   
{B00000000, B00000000, B00000000, B00001010, B00001100, B00001000, B00001000, B00001000},   
{B00000000, B00000000, B00001110, B00010000, B00001000, B00000100, B00000010, B00011110},   
{B00000000, B00010000, B00010000, B00011100, B00010000, B00010000, B00010000, B00001100},   
{B00000000, B00000000, B00000000, B00010010, B00010010, B00010010, B00010010, B00001100},   
{B00000000, B00000000, B00000000, B00010001, B00010001, B00010001, B00001010, B00000100},   
{B00000000, B00000000, B00000000, B00010001, B00010001, B00010001, B00010101, B00001010},   
{B00000000, B00000000, B00000000, B00010001, B00001010, B00000100, B00001010, B00010001},   
{B00000000, B00000000, B00010001, B00001010, B00000100, B00001000, B00001000, B00010000},   
{B00000000, B00000000, B00000000, B00011111, B00000010, B00000100, B00001000, B00011111},   
{B00000010, B00000100, B00000100, B00000100, B00001000, B00000100, B00000100, B00000010},   
{B00000100, B00000100, B00000100, B00000100, B00000100, B00000100, B00000100, B00000100},   
{B00001000, B00000100, B00000100, B00000100, B00000010, B00000100, B00000100, B00001000},   
{B00000000, B00000000, B00000000, B00001010, B00011110, B00010100, B00000000, B00000000}   
};  
   
void clearDisplay() 
{
    for (byte x=0; x<8; x++) 
    {  
       buffer[x] = B00000000;  
    }  
    screenUpdate();  
}  
  
void initMAX7219() 
{  
    pinMode(DataPin, OUTPUT);  
    pinMode(LoadPin, OUTPUT);  
    pinMode(ClockPin, OUTPUT);  
    clearDisplay();  
    writeData(B00001011, B00000111);   
    writeData(B00001001, B00000000);   
    writeData(B00001100, B00000001);   
    intensity(1);   
}  
   
void intensity(int intensity) 
{  
    writeData(B00001010, intensity);   
}  
   
void writeData(byte MSB, byte LSB) 
{  
    byte mask;  
    digitalWrite(LoadPin, LOW);   
      
    for (mask = B10000000; mask>0; mask >>= 1) 
    {   
        digitalWrite(ClockPin, LOW);  
        if (MSB & mask)
        {   
           digitalWrite(DataPin,HIGH);   
        }  
        else
        {   
           digitalWrite(DataPin,LOW);   
        }  
        digitalWrite(ClockPin, HIGH);   
    }  
      
    for (mask = B10000000; mask>0; mask >>= 1) 
    {   
        digitalWrite(ClockPin, LOW);  
        if (LSB & mask)
        {   
           digitalWrite(DataPin,HIGH);   
        }  
        else
        {   
            digitalWrite(DataPin,LOW);   
        }  
        digitalWrite(ClockPin, HIGH);   
    }  
    digitalWrite(LoadPin, HIGH);   
    digitalWrite(ClockPin, LOW);  
}  
   
void scroll(char myString[], int speed) 
{  
    byte firstChrRow, secondChrRow;  
    byte ledOutput;  
    byte chrPointer = 0;   
    byte Char1, Char2;   
    byte scrollBit = 0;  
    byte strLength = 0;  
    unsigned long time;  
    unsigned long counter;  
       
    while (myString[strLength]) {strLength++;}  
    counter = millis();  
    while (chrPointer < (strLength-1)) 
    {  
       time = millis();  
       if (time > (counter + speed)) 
       { 
          Char1 = myString[chrPointer];  
          Char2 = myString[chrPointer+1];  
          for (byte y= 0; y<8; y++) 
          {  
            firstChrRow = pgm_read_byte(&font[Char1 - 32][y]);  
            secondChrRow = (pgm_read_byte(&font[Char2 - 32][y])) << 1;  
            ledOutput = (firstChrRow << scrollBit) | (secondChrRow >> (8 - scrollBit) );  
            buffer[y] = ledOutput;  
          }  
            scrollBit++;   
            if (scrollBit > 6) 
            {   
              scrollBit = 0;  
              chrPointer++;  
            }  
            counter = millis();  
        }  
    }  
}  
   
void screenUpdate() 
{  
   for (byte row = 0; row < 8; row++) 
   { 
      writeData(row+1, buffer[row]);  
   }  
}  
    

 
 
 
 
void setup()
{
   

  
  //um pequeno delay no arduino
  //para evitar que envie comandos antes do esp8266 dar o start
  delay(100);
  //Seta ambas seriais para a velocidade de 9600
  Serial.begin(9600);
  //(em alguns casos a velocidade do seu esp8266 pode estar diferente desta)
  esp8266.begin(9600);
 
  //declara os pinos como saida
  pinMode(red,OUTPUT);
  digitalWrite(red,LOW);
 
 
   delay(2000);
   //liga o led azul para informar o inicio dos comandos AT
  digitalWrite(red,HIGH);
 
 
 
 
 
 
  //Envia o comandos AT
 
  // reseta o modulo
  sendData("AT+RST\r\n",2000,DEBUG);
  // configure as access point e estação (ambos)
  sendData("AT+CWMODE=3\r\n",1000,DEBUG);
  //conecta ao roteador com a senha  
  //(esta configuração deve ser feita, pois o seu roteador tem nome diferente do meu e senha)
  //sendData("AT+CWJAP=\"TAESP\",\"34740901\"r\n",10000,DEBUG);
  sendData("AT+CWJAP=\"TAESP\",\"34740901\"r\n",10000,DEBUG);
  //Retorna o IP ao qual está conectado e o IP de Station
  sendData("AT+CIFSR\r\n",1000,DEBUG);
  //Habilita multiplas conexões
  sendData("AT+CIPMUX=1\r\n",1000,DEBUG);
  //Habilita ao servidor a porta 80
  sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG);
 
  //desliga o led azul ao finalizar os comandos
  digitalWrite(red,LOW);
  //liga o led verde para indicar que podera enviar os comandos
  //via brownser
 


 delay(1000);
 initMAX7219();  
 Timer1.initialize(1000);       
 Timer1.attachInterrupt(screenUpdate); 
   
 
}
 
void loop()
{
 
 
 
 
  //verifica se o esp8266 esta enviando mensagem e esta disponivel
  if(esp8266.available())
  {
 
   
    if(esp8266.find("+IPD,"))
    {
     
 
 
     delay(1000);
     //recupera apenas comando ASCII
     int connectionId = esp8266.read()-48;
         
     //avança o cursor até a palavra  "pin="    
     esp8266.find("pin=");
     
     //armazena o primeiro numero.. Ex: Se for pino 13 armazenara 1 e logo em seguida multiplica por 10 para o calculo do pino  
     int pinNumber = (esp8266.read()-48)*10;
     //armazena o segundo numero e soma com o primeiro...  Ex : Se o numero for 13 a soma sera 10 + 3 que resultara no pino ao qual foi enviado pela pagina Web
     pinNumber += (esp8266.read()-48);
     //armazena o terceiro dado que correponde ao status do led '1' para ligado e '0' para desligado
     int statusLed =(esp8266.read()-48);
     
     //Escreve o satus com o metodo digital Write
     //Ex se recebeu 121
     //o pino 12 sera ligado
     //digitalWrite(12, 1);

     
     digitalWrite(pinNumber, statusLed);
 
     // finaliza o comando no esp8266
     String closeCommand = "AT+CIPCLOSE=";
     closeCommand+=connectionId;
     closeCommand+="\r\n";
     
     //Encerra a conexao
     sendData(closeCommand,1000,DEBUG);
     
    
   
    }
    
   
  }
}
 
 
 //Metodo que envia os comandos para o esp8266
String sendData(String command, const int timeout, boolean debug)
{
    //variavel de resposta do esp8266
    String response = "";
   
    // send a leitura dos caracteres para o esp8266
    esp8266.println(command);
   
    long int time = millis();
   
    while( (time+timeout) > millis())
    {
      while(esp8266.available())
      {
       
 
        //Concatena caracter por caractere recebido do modulo esp8266
        char c = esp8266.read();
        response+=c;
      }  
    }
   
    //debug de resposta do esp8266
    if(debug)
    {
      //Imprime o que o esp8266 enviou para o arduino
      Serial.println("Arduino : " + response);
    }
   
    return response;
}
