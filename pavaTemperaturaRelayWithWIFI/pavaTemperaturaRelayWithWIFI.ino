#include <SoftwareSerial.h>
#include <OneWire.h>                
#include <DallasTemperature.h>

long inputTemperatura,tempActual;
char buf[50];
int pinRelay=3;
int pinTemp=2;
OneWire ourWire(pinTemp);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensorTemperatura(&ourWire); //Se declara una variable u objeto para nuestro sensor1
SoftwareSerial mySerial(13,12); // RX, TX nodemcu 
void setup()
{
 //config serial nodemcu 
 mySerial.begin(115200);
 pinMode(12,OUTPUT); 
 
 pinMode(pinRelay,OUTPUT) ;
 Serial.begin(115200);
 digitalWrite(pinRelay, HIGH);
 sensorTemperatura.begin();   //Se inicia el sensor 1
}

char mystr[10];
void loop(){
  inputTemperatura = 0;
  Serial.println("Esperando conectar serial wifi");
  while(!mySerial){  
  }
  //Espero a leer una temperatura por puerto serial 
  Serial.println("Esperando iniciar <Presione una tecla>");
  while(inputTemperatura == 0){
    // mySerial.readBytes(mystr,2); //Read the serial data and store in var
    // Serial.println(mystr);

    if (mySerial.available()>0){
     inputTemperatura = mySerial.parseInt();
     mySerial.flush();
    }
    delay(500);
    Serial.println(inputTemperatura);
    
  }
  //Envio ok se leyo la temperatura 
  Serial.print(inputTemperatura);
  Serial.println("Listo");  
  //Enciendo la pava
  digitalWrite(pinRelay, LOW);
  
  sensorTemperatura.requestTemperatures();   //Se envía el comando para leer la temperatura
  tempActual= sensorTemperatura.getTempCByIndex(0); //Se obtiene la temperatura en ºC del sensor
  Serial.print(tempActual);
  //sensar temperatura
    Serial.print("Calentando");
  while(tempActual < inputTemperatura){
    sensorTemperatura.requestTemperatures();   //Se envía el comando para leer la temperatura
    tempActual= sensorTemperatura.getTempCByIndex(0); //Se obtiene la temperatura en ºC del sensor
     Serial.print("Temperatura actual= ");
     Serial.print(tempActual);
     Serial.println(" C");
     delay(10);   
  }
  //Apago la pava
  digitalWrite(pinRelay,HIGH);
  //Envío finalizo
  Serial.println("Finalizo"); 
    
}


