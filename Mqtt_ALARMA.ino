#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "config.h"  // Sustituir con datos de vuestra red
#include "MQTT.hpp"
#include "ESP8266_Utils.hpp"
#include "ESP8266_Utils_MQTT.hpp"

const int buzzer = 5;  // Buzzer pin
const int pirPin = 2;  // Buzzer pin


void setup(void)
{
	// Inicializa el sensor PIR como entrada y el buzzer como salida
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

	ConnectWiFi_STA(true);

	InitMqtt();
  

}

int encender = 0;
int apagar = 0;
int movimiento = 0;

void loop()
{
  HandleMqtt();
  
  encender = obtener_alarma();
  apagar = obtener_alarmaDesactivar();

  // Lee el valor del sensor PIR

  // Si se detecta movimiento, enciende el LED
  if(encender == 1){    
    int pirValue = digitalRead(pirPin);
    if (pirValue == HIGH && apagar == 0) {
        movimiento += 1;
        Serial.println("Movimiento detectado");
        PublisMqttMovimiento(movimiento);
        digitalWrite(buzzer, HIGH);
        delay(1000);

    } else if(pirValue == HIGH && apagar == 1) {
      movimiento += 1;    
      Serial.println("Movimiento detectado");
      PublisMqttMovimiento(movimiento);
      digitalWrite(buzzer, LOW);
      delay(1000);
    }else{
      Serial.println("Movimiento no detectado");
      digitalWrite(buzzer, LOW);
      delay(1000);
    }
  }else{
    //Serial.println("Alarma apagada");
    digitalWrite(buzzer, LOW);

  }

  
}




