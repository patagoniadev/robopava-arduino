#include <SoftwareSerial.h>
#include <OneWire.h>                
#include <DallasTemperature.h>

long inputTemperatura,tempActual;
// Constantes
const int pinRelay=3;
const int pinTemp=2;
const int pinNodeMCU=12;

OneWire ourWire(pinTemp);                      //Se establece el pin 2  como bus OneWire
DallasTemperature sensorTemperatura(&ourWire); //Se declara una variable u objeto para el sensor de temperatura
SoftwareSerial serialNodeMcu(13,12);           //RX, TX nodemcu 

void setup()
{
 //configuración de pines 
 pinMode(pinNodeMCU,OUTPUT); 
 pinMode(pinRelay,OUTPUT) ;
 
 //inicialización de puertos seriales
 Serial.begin(115200);
 serialNodeMcu.begin(115200);
 
 //inicialización de sensores y actuador
 sensorTemperatura.begin();                   //Se inicia el sensor de temperatura
 digitalWrite(pinRelay, HIGH);                //iniciamos el relay en apagado
}


void loop()
{
  inputTemperatura = 0;
  Serial.println("Esperando conectar serial wifi");
  while(!serialNodeMcu){  
  }
  
  //Espero a leer una temperatura desde NodeMCU
  Serial.println("Esperando solicitud de calentar");
  while(inputTemperatura == 0){
    if (serialNodeMcu.available()>0){
     inputTemperatura = serialNodeMcu.parseInt();
     serialNodeMcu.flush();
     Serial.println("Temperatura recibida: ")
     Serial.println(inputTemperatura);
    }
    delay(500);
  }

  //Envio ok se leyo la temperatura 
  Serial.println("Listo");  
  
  //Enciendo la pava
  digitalWrite(pinRelay, LOW);
  
  //Sensar temperatura hasta alcanzar la temperatura deseada
  Serial.print("Calentando");
  while(tempActual < inputTemperatura){
    sensorTemperatura.requestTemperatures();            //Se envía el comando para leer la temperatura
    tempActual= sensorTemperatura.getTempCByIndex(0);   //Se obtiene la temperatura en ºC del sensor
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


