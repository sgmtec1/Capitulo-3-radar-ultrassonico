//Open Source
 #include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA
 LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
 
 #include <Servo.h> 
 #include <NewPing.h>

 #define TRIGGER_PIN  10
 #define ECHO_PIN    11
 #define MAX_distancia 40  // distancia máxima 

 NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_distancia); /* NewPing configuração de pinos e distancia máxima. */

 int distancia;
 Servo myServo;

 void setup() {
  Serial.begin(9600); // liga comunição serial
  myServo.attach(12);  //motor servo pino 12
  lcd.begin (16,2); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY
  lcd.setBacklight(HIGH); //LIGA O BACKLIGHT (LUZ DE FUNDO)
}

 void loop() {
    lcd.setCursor(0,0); //SETA A POSIÇÃO DO CURSOR
    lcd.print("  RADAR SONAR   ");
    lcd.setCursor(0,1); //SETA A POSIÇÃO DO CURSOR
    lcd.print(" DETECTA OBJETOS"); // Star Wars
  /* faz rotacionar o servo motroe de 15º à 160º graus. */
  for(int i = 15; i <= 160; i++){  
    myServo.write(i);
    delay(30);

    /* chama a função que calcula a sistância medida pelo sensor ultrasônico para cada grau. */
    distancia = calcularPING();

    Serial.print(i);         /* Envia o atual grau na porta serial. */
    Serial.print(",");       /* Envia carácter adicional à direita préximo ao valor anterior necessário mais tarde na IDE Processing  */ 
    Serial.print(distancia);  /* Envia o valor da distância na porta serial. */ 
    Serial.print(".");       /* Envia carácter à direita próximo ao valor anterior necessário mais tarde na IDE processing.*/ 

  }

  /* Repete as linha anteriores de 160º a 15º graus. */
  for(int i = 160; i > 15; i--){
    myServo.write(i);
    delay(30);
    
    distancia = calcularPING();
    
    Serial.print(i);
    Serial.print(",");
    Serial.print(distancia);
    Serial.print(".");
    
  }

}

/**
 * calcularPING - Função pa calcular a distácia medida pelo sensor ultrasônico..
 */
 int calcularPING(){ 
  unsigned int uS = sonar.ping();  /* Envia ping, retorna ping tempo em microseconds (uS). */
  distancia = uS / US_ROUNDTRIP_CM; /* Converte oing tempo para distancia em cm e retorana resultado. */
  return distancia;
}
