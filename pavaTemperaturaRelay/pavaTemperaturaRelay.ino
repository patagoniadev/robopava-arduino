#include <OneWire.h>                
#include <DallasTemperature.h>

long inputTemperatura,tempActual;
char buf[50];
int pinRelay=3;
int pinTemp=2;
OneWire ourWire(pinTemp);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensorTemperatura(&ourWire); //Se declara una variable u objeto para nuestro sensor1

void setup()
{
 pinMode(pinRelay,OUTPUT) ;
 Serial.begin(115200);
 digitalWrite(pinRelay, HIGH);
 sensorTemperatura.begin();   //Se inicia el sensor 1
}

void loop(){
  inputTemperatura = 0;
  //Espero a leer una temperatura por puerto serial 
  Serial.println("Esperando iniciar <Presione una tecla>");
  while(inputTemperatura == 0){
      
    if (Serial.available()>0){
      inputTemperatura = Serial.parseInt();
      Serial.flush();
    }
    Serial.println(inputTemperatura,DEC);
    delay(500);
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


