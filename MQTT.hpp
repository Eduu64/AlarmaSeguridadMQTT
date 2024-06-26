const char* MQTT_BROKER_ADRESS = "192.168.1.114";
//const char* MQTT_BROKER_ADRESS = "10.34.181.200";
const uint16_t MQTT_PORT = 1883;
const char* MQTT_CLIENT_NAME = "ESP8266Client_1";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void SuscribeMqtt()
{
  mqttClient.subscribe("PT/ALARMA",1);
  mqttClient.subscribe("PT/ALARMADESACTIVAR",1);

}

String payload;
int encendido = 0;
int desactivar = 0;


void PublisMqttMovimiento(int data)
{
	payload = "";
	payload = String(data);
	mqttClient.publish("PT/ALARMAMOVIMIENTO", (char*)payload.c_str());
}


String content = "";
void OnMqttReceived(char* topic, byte* payload, unsigned int length) 
{
	Serial.print("Received on ");
	Serial.print(topic);
	Serial.print(": ");
  String canal(topic);
	content = "";	
	for (size_t i = 0; i < length; i++) {
		content.concat((char)payload[i]);
	}

  if(canal.equals("PT/ALARMA")){

    encendido = content.toInt();

  }

  if(canal.equals("PT/ALARMADESACTIVAR")){

    desactivar = content.toInt();

  }

	Serial.print(content);
	Serial.println();
}

  int obtener_alarma(){
    return encendido;
}

  int obtener_alarmaDesactivar(){
    return desactivar;
}


