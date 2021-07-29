//Declaracao de variaveis
float num1;
float num2;
float soma;
float subtracao1;
float subtracao2;
float mult;
float divisao1;
float divisao2;
float potencia1;
float potencia2;

void setup() {
  Serial.begin(9600);
}

float getNumber() {
  while (Serial.available() == 0);
  return Serial.parseFloat();
  
}

void loop() {

  Serial.print("Primeiro numero: ");
  num1 = getNumber();
  Serial.println(num1);
  Serial.print("Segundo numero: ");
  num2 = getNumber();
  Serial.println(num2);
  Serial.println("-----------------------------------");

  Serial.println("Soma:");
  Serial.print(num1);
  Serial.print(" + ");
  Serial.print(num2);
  Serial.print(" = ");
  soma = num1 + num2;
  Serial.print(soma);
  Serial.println("\n-----------------------------------");

  Serial.println("Subtracao:");
  //primeiro valor pelo segundo
  Serial.print(num1);
  Serial.print(" - ");
  Serial.print(num2);
  Serial.print(" = ");
  subtracao1 = num1 - num2;
  Serial.println(subtracao1);
  //segundo valor pelo primeiro
  Serial.print(num2);
  Serial.print(" - ");
  Serial.print(num1);
  Serial.print(" = ");
  subtracao2 = num2 - num1;
  Serial.print(subtracao2);
  Serial.println("\n-----------------------------------");

  Serial.println("Multiplicacao:");
  Serial.print(num1);
  Serial.print(" * ");
  Serial.print(num2);
  Serial.print(" = ");
  mult = (long)num1 * (long)num2;
  Serial.print(mult);
  Serial.println("\n-----------------------------------");

  Serial.println("Divisao:");
  //primeiro valor pelo segundo
  Serial.print(num1);
  Serial.print(" / ");
  Serial.print(num2);
  Serial.print(" = ");
  divisao1 = (float)num1 / (float)num2;
  Serial.println(divisao1);
  //segundo valor pelo primeiro
  Serial.print(num2);
  Serial.print(" / ");
  Serial.print(num1);
  Serial.print(" = ");
  divisao2 = (float)num2 / (float)num1;
  Serial.print(divisao2);
  Serial.println("\n-----------------------------------");

  Serial.println("Potencia:");
  //primeiro valor pelo segundo
  Serial.print(num1);
  Serial.print(" ^ ");
  Serial.print(num2);
  Serial.print(" = ");
  if (pow(num1, num2) > 4251713792.00){
    Serial.print("Resultado encontra-se fora do valor de gama.\n");
  }else{
  potencia1 = (float)pow(num1, num2);
  Serial.println(potencia1);}
  //segundo valor pelo primeiro
  Serial.print(num2);
  Serial.print(" ^ ");
  Serial.print(num1);
  Serial.print(" = ");
  if (pow(num2, num1) > 4251713792.00){
    Serial.print("Resultado encontra-se fora do valor de gama.\n");
  }else{
  potencia2 = (float)pow(num2, num1);
  Serial.print(potencia2);}
  Serial.println("\n-----------------------------------");

  Serial.println("\n-----------------------------------");

  }
