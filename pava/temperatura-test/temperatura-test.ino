#include <OneWire.h>                
#include <DallasTemperature.h>
 
OneWire ourWire1(2);                //Se establece el pin 2  como bus OneWire

DallasTemperature sensors1(&ourWire1); //Se declara una variable u objeto para nuestro sensor1

void setup() {
delay(500);
Serial.begin(9600);
sensors1.begin();   //Se inicia el sensor 1
}
 
void loop() {
sensors1.requestTemperatures();   //Se envía el comando para leer la temperatura
float temp1= sensors1.getTempCByIndex(0); //Se obtiene la temperatura en ºC del sensor 1

Serial.print("Temperatura 1 = ");
Serial.print(temp1);
Serial.println(" C");
delay(10);                     
}

