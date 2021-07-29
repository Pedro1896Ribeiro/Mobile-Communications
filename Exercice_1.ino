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
  }

void loop() {
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

  value = analogRead(pin_analogico);
  value = map(value, 0, 1023, 0, 2000);
  delay(value);
}
