#include <OneWire.h>                
#include <DallasTemperature.h>
boolean flag;
long inputTiempo;
char buf[50];
int pinRelay=3;
int pinTemp=2;
OneWire ourWire(pinTemp);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors1(&ourWire); //Se declara una variable u objeto para nuestro sensor1

void setup()
{
 pinMode(pinRelay,OUTPUT) ;
 Serial.begin(9600);
 digitalWrite(pinRelay, HIGH);
 flag = true;
 inputTiempo = 0;
 sensors1.begin();   //Se inicia el sensor 1
}

void loop(){
  char iniciar='0';
  while(iniciar=='0'){
    Serial.println("Esperando iniciar <Presione 1>");
    delay(1000),
    iniciar = Serial.read();
  }
    sensors1.requestTemperatures();   //Se envía el comando para leer la temperatura
    float temp1= sensors1.getTempCByIndex(0); //Se obtiene la temperatura en ºC del sensor 1
    Serial.print("Temperatura 1 = ");
    Serial.print(temp1);
    Serial.println(" C");
    delay(10);
  if(flag) {
    Serial.println("Listo");  
    flag = false;
  }
  inputTiempo = Serial.parseInt() * 1000 * 60;
  if (inputTiempo > 0) {
    Serial.print("Comienza.");
    digitalWrite(pinRelay, LOW);
    ltoa(inputTiempo, buf, 10);  // 10 is the base value not the size - look up ltoa for avr
    Serial.print("Tiempo: ");
    Serial.print(buf);
    delay(inputTiempo);
    digitalWrite(pinRelay, HIGH);
    inputTiempo = 0;
    Serial.print("Termina.");
  }         
}


