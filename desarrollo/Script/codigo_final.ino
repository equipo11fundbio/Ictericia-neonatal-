#include <SPI.h>
#include <Wire.h>
#include <SD.h>    
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SSpin 8    
#define S0 9
#define S1 7
#define S2 2
#define S3 3
#define sensorSalida 5
int Rojo_Frec = 0;
int Verde_Frec = 0;
int Azul_Frec = 0;
int VALORSENSOR = 0;
File archivo;     // objeto archivo del tipo File
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
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
  Serial.println("Inicializando tarjeta ...");  // texto en ventana de monitor
    if (!SD.begin(SSpin)) {     // inicializacion de tarjeta SD
    Serial.println("fallo en inicializacion !");// si falla se muestra texto correspondiente y
    return;         // se sale del setup() para finalizar el programa
  }
  Serial.println("inicializacion correcta");  // texto de inicializacion correcta
  archivo = SD.open("datos.txt", FILE_WRITE); // apertura para lectura/escritura de archivo datos.txt

}
void loop(){
  if (archivo) {  
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Encendido");
    display.display(); 
    delay(3000);

    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Coloque el dispositivo en la zona interescapular");
    display.display(); 
    delay(4000);

                             // Configura el filtor ROJO para tomar lectura
    digitalWrite(S2,LOW);
    digitalWrite(S3,LOW);
    delay(100);
    Rojo_Frec= pulseIn(sensorSalida, LOW);
    archivo.print("Frecuencia_rojo");
    archivo.print(":");
    archivo.println(Rojo_Frec);
    Serial.print(" R= "); Serial.print(Rojo_Frec);
    delay(100);
                            // Configura el filtor VERDE para tomar lectura
    digitalWrite(S2,HIGH);
    digitalWrite(S3,HIGH);
    delay(100);
    Verde_Frec = pulseIn(sensorSalida, LOW);
    archivo.print("Frecuencia_verde");
    archivo.print(":");
    archivo.println(Verde_Frec);
    Serial.print(" V= "); Serial.print(Verde_Frec);
    delay(100);
                           // Configura el filtor AZUL para tomar lectura
    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
    delay(100);
    Azul_Frec = pulseIn(sensorSalida, LOW);
    archivo.print("Frecuencia_azul");
    archivo.print(":");
    archivo.println(Azul_Frec);
    Serial.print(" A= "); Serial.print(Azul_Frec);
    delay(100);
    Serial.println("*");
    delay(200); 

    VALORSENSOR = 42*(log(145*(pow(Verde_Frec,0.345)/Azul_Frec)));
    
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0,0);
    display.print("Concentración de bilirrubina hallado(mg/dl): "); display.println(VALORSENSOR);
    display.print("Rango de concentración de bilirrubina normal (mg/dl): Bilirrubina < 5 ");
    display.display(); 
    delay(10000);
    
    archivo.print("Concentración de bilirrubina hallado");
    archivo.print(":");
    archivo.println(VALORSENSOR);
    Serial.print("Concentración de bilirrubina hallado:"); Serial.print(VALORSENSOR); Serial.println("mg/dL");
    
    if(VALORSENSOR>5){
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.print("El paciente presenta Ictericia neonatal");
      display.display(); 
      delay(5000);
      archivo.println("El paciente presenta Ictericia neonatal");
      Serial.println("El paciente presenta Ictericia neonatal");
    } else{
    
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.print("El paciente no presenta Ictericia neonatal");
      display.display(); 
      delay(5000);
      archivo.println("El paciente no presenta Ictericia neonatal");
      Serial.println("El paciente no presenta Ictericia neonatal");
    }
    archivo.close();        // cierre de archivo
    Serial.println("escritura correcta"); // texto de escritura correcta en monitor serie
    
  } else {
    Serial.println("error en apertura de datos.txt"); // texto de falla en apertura de archivo
    
  }
  
  }
