#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <SPI.h>
#include <SD.h>


#define COL 128 
#define rom 64  
#define SSpin 10 

 Adafruit_SSD1306 display(COL, rom,&Wire);

 
int VALORSENSOR;

const int s0 = 1;
const int s1 = 6;
const int s2 = 2;
const int s3 = 3;
const int out = 5;



void setup() {
  
    Serial.begin (9600);
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    pinMode(s0, OUTPUT); 
    pinMode(s1, OUTPUT);
    pinMode(s2, OUTPUT);
    pinMode(s3, OUTPUT);
    pinMode(out, INPUT);
    
    digitalWrite(s0, HIGH);
   digitalWrite(s1, HIGH);
  
    Wire.begin();
    
    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    





    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0); 
    display.print("Encendido"); 
    
    display.setCursor(0, 14);
    display.print("Colocar el dispositivo en la frente para empezar");
    display.display();
    
    
    if(digitalRead(s3) == HIGH ){
      display.setCursor(0, 16);
      delay(100);
      display.print("...");
    }
    
      int AZUL = getAzul();
    delay(200);
    int VERDE = getVerde();
    delay(200);

    VALORSENSOR = 42*(log(145*(pow(VERDE,0.345)/AZUL)));
    
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Concentración de bilirrubina hallado(mg/dl): ");
    display.println(VALORSENSOR);
    display.setCursor(0, 16);
    display.print("Rango de concentración de bilirrubina normal (mg/dl): Bilirrubina < 5 ");
    
    
  
    display.setCursor(0, 30);
    
    if(VALORSENSOR>5){
      
      display.print("El paciente presenta Ictericia neonatal");
    } else
    {
    
      display.print("El paciente no presenta Ictericia neonatal");
    }
    display.display();

    String datastring = "" ;
    datastring =String(VALORSENSOR);
    File datafile= SD.open("datalog.txt",FILE_WRITE);

}

void loop() {
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
