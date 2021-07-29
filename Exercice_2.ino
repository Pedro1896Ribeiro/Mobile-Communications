#include <GSM.h>
#define PINNUMBER "9080"
//Declaracao de variaveis
int bits;
int valor_inicial;
int sentido;
int potencia;
int button = A3;
int act = LOW;
int ant = LOW;
int pin_analogico = A2;
int value;
GSM gsmAccess;
GSM_SMS sms;
char remoterNumber[20];
int n;
int time_delay = 1;
String str[20];

void setup () {
  Serial.begin(9600);

  Serial.print("Insira o numero de Bits entre 3 e 7: ");
  while (Serial.available()==0);
  bits = Serial.parseInt();
  if(bits < 3 || bits > 7){
    Serial.println("Valor inserido fora do intervalo. Valor por defeito: 5 bits. ");
    bits = 5;
    Serial.println(bits);
  }else{
   Serial.println(bits);
  }

  for(int i = 2; i < bits + 2; i++){
    pinMode(i, OUTPUT);
  }
   potencia = pow(2, bits);
   Serial.print("Insira o valor inicial da sequencia entre 0 e ");
   Serial.print(potencia);
   Serial.print(" : ");
   while (Serial.available()==0);
   valor_inicial = Serial.parseInt();
   if(valor_inicial < 0 || valor_inicial > potencia){
     Serial.println("Valor inserido fora do intervalo. Valor por defeito: 0");
     valor_inicial = 0;
     Serial.println(valor_inicial);
   }else{
     Serial.println(valor_inicial);
  }
   Serial.println("Introduza o sentido: Crescente = 0; Decrescente = 1;");
   while (Serial.available()==0);
   sentido = Serial.parseInt();
   if(sentido != 0 && sentido != 1){
     Serial.println("Sentido inserido incorreto. Valor por defeito: crescente");
     sentido = 0;
     Serial.println(sentido);
   }else{
      Serial.println(sentido);
   }

   boolean notConnected = true;
    while (notConnected) {
    if (gsmAccess.begin(PINNUMBER) == GSM_READY) {
      notConnected = false;
    } else {
      Serial.println("Not connected");
      delay(1000);
    }
  }

  Serial.println("GSM initialized");
  Serial.println("Waiting for messages");
  }

void loop() {

  char c;
 
  if (sms.available()){
    n = 0;
    Serial.println("Message received from:");
    sms.remoteNumber(remoterNumber, 20);
    Serial.println(remoterNumber);
    if(sms.peek()=='#')
    {
      Serial.println("Discarded SMS");
      sms.flush();
    }

    while(c=sms.read()){
      str[n] = c;
      n++;
    }
    Serial.println("\nEND OF MESSAGE");
    sms.flush();
    Serial.println("MESSAGE DELETED");
  }

  if(str[0] == "N" && str[1] == " "){
    for(int i = 2, temp = 0; str[i] == " " || i > 20; i++, temp++)
    if(temp == 1){
      if(str[2].toInt() > 0 && str[2].toInt() < potencia) 
      valor_inicial = str[2].toInt();
    }else if(temp == 2){
      temp = str[2].toInt() * 10 + str[3].toInt();
      if(temp > 0 && temp < potencia)
      valor_inicial = temp;
    }else if(temp <= 3){
      temp = str[2].toInt() * 100 + str[3].toInt() * 10 + str[4].toInt();
      if(temp > 0 && temp < potencia)
      valor_inicial = temp;
      }
    }
    if(str[0] == "A") sentido = 0;
    
    if(str[0] == "D") sentido = 1;
    
    if(str[0] == "S"){
      if(sentido == 1)sentido = 0;
      else sentido = 1;
    }
    
    if(str[0] == "B" && str[1]==" " && str[2].toInt() > 3 && str[2].toInt() < 7){
        bits = str[2].toInt();
        potencia = pow(2,bits);
    }
  
    if(str[0] == "T" && str[1]==" "){
      time_delay = 0;
      for(int i = 2, temp = 0; str[i] == " " || i > 20; i++, temp++)
      if(temp == 1) value = str[2].toInt();
      else if(temp == 2) value = str[2].toInt() * 10 + str[3].toInt();
      else if(temp == 3) value = str[2].toInt() * 100 + str[3].toInt() * 10 + str[4].toInt();
      else if(temp <= 4) value = str[2].toInt() * 1000 + str[3].toInt() * 100 + str[4].toInt() * 10 + str[5].toInt();
    }
    
    if(str[0] == "E") time_delay = 1;
    for(int i = 0; i<20; i++)str[i]=" ";
  
  if(valor_inicial >= potencia){
    sentido = 1;
  }
  if(valor_inicial <= 0){
    sentido = 0;
  }

  ant = act;
  act = digitalRead(button);
  if(act == HIGH && ant == LOW){
    if(sentido == 0) sentido = 1;
  else sentido = 0;
  }
  for(int i = 0; i < bits; i++){
    digitalWrite(i+2, bitRead(valor_inicial, i));
  }

  Serial.println(valor_inicial);
  Serial.println(valor_inicial, BIN);
  if(sentido == 0) valor_inicial++;
  else valor_inicial--;

  if(time_delay){
  value = analogRead(pin_analogico);
  value = map(value, 0, 1023, 0, 2000);
  }delay(value);
}
