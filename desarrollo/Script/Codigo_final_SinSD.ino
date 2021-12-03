#include <SPI.h>
#include <Wire.h>    
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
#define S0 9
#define S1 7
#define S2 2
#define S3 3
#define sensorSalida 5
int Rojo_Frec = 0;
int Verde_Frec = 0;
int Azul_Frec = 0;
int VALORSENSOR = 0;

Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorSalida, INPUT);
  
                           // Configura la escala de Frecuencia en 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);
  
}
void loop(){
   
   
   display.clearDisplay();
   display.setTextSize(1);
   display.setCursor(32,16);
   display.print("Encendido");
   display.display(); 
   delay(3000);


   display.clearDisplay();
   display.setTextSize(1);
   display.setCursor(0,8);
   display.print("Coloque el dispositivo en la zona interescapular");
   display.display(); 
   delay(4000);

                             // Configura el filtor ROJO para tomar lectura
   digitalWrite(S2,LOW);
   digitalWrite(S3,LOW);
   delay(100);
   Rojo_Frec= pulseIn(sensorSalida, LOW);
  
   Serial.print(" R= "); Serial.print(Rojo_Frec);
   delay(100);
                            // Configura el filtor VERDE para tomar lectura
   digitalWrite(S2,HIGH);
   digitalWrite(S3,HIGH);
   delay(100);
   Verde_Frec = pulseIn(sensorSalida, LOW);
   
   Serial.print(" V= "); Serial.print(Verde_Frec);
   delay(100);
                           // Configura el filtor AZUL para tomar lectura
   digitalWrite(S2,LOW);
   digitalWrite(S3,HIGH);
   delay(100);
   Azul_Frec = pulseIn(sensorSalida, LOW);
   
   Serial.print(" A= "); Serial.println(Azul_Frec);
   delay(100);
   

   VALORSENSOR = 42*(log(145*(pow(Verde_Frec,0.345)/Azul_Frec)));
    
    
   display.clearDisplay();
   display.setTextSize(1);
   display.setCursor(0,0);
   display.print("Concentración de bilirrubina hallado(mg/dl): "); 
   display.println(VALORSENSOR);
   display.print("Rango de concentración de bilirrubina anormal (mg/dl): 5 < Bilirrubina < 12");
   display.display(); 
   delay(12000);
   
   
   Serial.print("Concentración de bilirrubina hallado:"); Serial.print(VALORSENSOR); Serial.println("mg/dL");
    
   if(VALORSENSOR>5 && VALORSENSOR<12){
     display.clearDisplay();
     display.setTextSize(1);
     display.setCursor(0,8);
     display.print("El paciente presenta Ictericia neonatal");
     display.display(); 
     delay(5000);
     
     Serial.println("El paciente presenta Ictericia neonatal");
   } else{
    
     display.clearDisplay();
     display.setTextSize(1);
     display.setCursor(0,8);
     display.print("El paciente no presenta Ictericia neonatal");
     display.display(); 
     delay(5000);
     
     Serial.println("El paciente no presenta Ictericia neonatal");
    }
  
   Serial.println("Escritura correcta"); // texto de escritura correcta en monitor serie
    
  
  }
