// Diretivas de pré-processamento
#include <Arduino.h>
#include <TinyGPS++.h>

// Instância de objetos
TinyGPSPlus gps;
HardwareSerial interfaceSerial(2);

// Funções
void displayInfo()
{

  gps.satellites.isValid() ? 
  Serial.printf("Satélites: %d\n", gps.satellites.value()) : 
  Serial.printf("Não foi possível detectar satélites!\n");

  gps.hdop.isValid() ? 
  Serial.printf("Qualidade HDOP: %.2f\n", gps.hdop.hdop() / 100) : 
  Serial.printf("Não foi possível medir o HDOP\n");

  gps.location.isValid() ?
  Serial.printf("Latitude: %.6f\nLongitude: %.6f\n", gps.location.lat(), gps.location.lng()):
  Serial.printf("Ainda não foi detectado uma localização!\n");

  gps.date.isValid() ?
  Serial.printf("Data: %02d/%02d/%02d\n", gps.date.day(), gps.date.month(), gps.date.year()):
  Serial.println("Não foi possível detectar a data atual!");

  gps.time.isValid() ?
  Serial.printf("Horário: %02d:%02d:%02d\n", gps.time.hour() - 3, gps.time.minute(), gps.time.second()):
  Serial.println("Não foi possível detectar a hora atual!");

  Serial.printf("\n");
}

void setup()
{
  Serial.begin(115200);
  interfaceSerial.begin(9600, SERIAL_8N1, 16, 17);
}

void loop()
{
  while (interfaceSerial.available() > 0)
    if (gps.encode(interfaceSerial.read()))
      displayInfo();

}
