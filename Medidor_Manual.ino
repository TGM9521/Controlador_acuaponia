// Autor: Tomás García
// Última fecha modificiación: 23-09-2019
// Estado: programar sensor tds
// programar pantalla
// Modelar el voltaje de lectura del arduino

#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <SoftwareSerial.h>

#define  DQ1  11
#define  PHPIN A0
#define  TDSPIN A1
#define  temhighalarm 30
#define  temlowalarm 15


void inicio();
void mostrar_valores();
void tomamuestras();
float get_mediaPH();
float get_mediaTDS();
float get_mediaTEM();



float PH[60];
float TDS[60];
float TEM[60];


DeviceAddress SensorT={0x28,0x17, 0xCC, 0x79, 0x97, 0x10, 0x03, 0xA4}; // DS18B20 1
OneWire Owire(DQ1);
DallasTemperature T_tanq(&Owire); // Sensor de temperatura ds18b20
LiquidCrystal_I2C lcd(0x27,16,2);

void setup()
{
  Serial.begin(9600);
  T_tanq.begin();
  lcd.init();
  pinMode(DQ1,INPUT);
  pinMode(PHPIN,INPUT);
  pinMode(TDSPIN,INPUT);
  lcd.backlight();
  lcd.blink();
  inicio();
}

void loop() 
{
  
  tomamuestras();
  mostrar_valores();
  
  
  
  if( T_tanq.isConnected(SensorT)==0)
  {
    //Indicar que no funciona el sensor de temperatura
  }
}

void inicio(){
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tomamuestras");
  lcd.setCursor(0,1);
  lcd.print("manual");
  delay(4000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Valores promedio");
  lcd.setCursor(0,1);
  lcd.print("intervalo: 2 min");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Tomando valores...");
  }
void tomamuestras(){
  float vol_ph=0;//voltaje medido del sensor de pH
  float vol_TDS=0; //voltaje medido del sensor de TDS

  for(int i=0; i<60 ;i++){
    vol_ph=(analogRead(PHPIN)*5.0/1024-0.11);
    vol_ph=(analogRead(TDSPIN)*5.0/1024);
    PH[i]=(vol_ph*(-5.7674)+21.425);
    TEM[i]=T_tanq.getTempC(SensorT);
    //TDS[i]=
    delay(1000);
    
    }
}
float get_mediaPH(){
  float media=0;
  float sum=0;
    for(int i=0; i<60;i++)
    {
      sum+=PH[i];
    }
   media=sum/(sizeof(PH)/sizeof(float));
   return media;
    
}
float get_mediaTDS(){
  float media=0;
  float sum=0;
    for(int i=0; i<60;i++)
    {
      sum+=TDS[i];
    }
   media=sum/(sizeof(TDS)/sizeof(float));
   return media;
    
}
float get_mediaTEM(){
  float media=0;
  float sum=0;
    for(int i=0; i<60;i++)
    {
      sum+=TEM[i];
    }
   media=sum/(sizeof(TEM)/sizeof(float));
   return media;
    
}
void mostrar_valores(){ 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PH:");
  lcd.print(get_mediaPH());
 
  lcd.print(" T:");
  lcd.print(get_mediaTEM());
  lcd.print("C");
  
  lcd.setCursor(0,1);
  lcd.print("TDS:");
  lcd.print(get_mediaTDS());
  lcd.print(" PPM");
  delay(5000);
}
