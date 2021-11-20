/*
low apagado 
*/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <SPI.h>
#include <SD.h>
#define COL 128 
#define rom 64  


 Adafruit_SSD1306 oled(COL, rom);


 
int VALORSENSOR;

int SENSOR;

const int s0 = 4;
const int s1 = 5;
const int s2 = 6;
const int s3 = 7;
const int out = 8
const int ssD =13;


void setup() {
  
    Serial.begin (9600);
    pinMode(s0; OUTPUT); 
     pinMode(s1; OUTPUT);
    pinMode(s2; OUTPUT);
    pinMode(s3; OUTPUT);
    pinMode(out; INPUT);
    
    digitalWrite(s0, HIGH);
   digitalWrite(s1, HIGH);
  
  
    Wire.begin();
    oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    
  
    
}

void loop() {
    
    oled.clearDisplay();
    oled.setCursor(0, 0); 
    oled.print("Encendido"); 
    
    oled.setCursor(0, 14);
    oled.print("Colocar el dispositivo en la frente para empezar");
    
    
    
    if(digitalRead(s3) = HIGH ){
      oled.setCursor(0, 16);
      delay(100);
      oled.print("...");
    }
    
      int AZUL = getAzul();
    delay(200);
    int VERDE = getVerde();
    delay(200);

    VALORSENSOR = 42*(log(145*(pow(VERDE,0.345)/AZUL);
    
    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.print("Concentración de bilirrubina hallado(mg/dl): ");
    oled.println(VALORSENSOR);
    oled.setCursor(0, 16);
    oled.print("Rango de concentración de bilirrubina normal (mg/dl): Bilirrubina < 5 ");
    
    
    
  
    oled.setCursor(0, 30);
    
    if(VALORSENSOR>5){
      
      oled.print("El paciente presenta Ictericia neonatal");
    } else
    {
    
      oled.print("El paciente no presenta Ictericia neonatal");
    }
    
    string datastring = ""
    datastring +=String(VALORSENSOR);
    File datafile= SD.open("datalog.txt",FILE_WRITE);
  
    
}

int getAzul(){
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  int AZUL = pulseIn(out, LOW);
  return AZUL;
}

int getVerde(){
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  int VERDE = pulseIn(out, LOW);
  return VERDE;
}







