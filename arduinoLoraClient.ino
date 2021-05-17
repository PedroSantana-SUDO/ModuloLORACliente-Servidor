#include <SPI.h>
#include <RH_RF95.h>


RH_RF95 rf95;

void setup()
{
  Serial.begin(9600);
  while (!Serial) ; 
  if (!rf95.init())
    Serial.println("Fallo de inicialización");
}

void loop()
{
  Serial.println("Mandando mensaje desde el cliente");
  uint8_t data[] = "Mensaje del cliente"; //Mensaje que se va a enviar al servidor
  rf95.send(data, sizeof(data));
  rf95.waitPacketSent();
  // Se espera una respuesta
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);
  if (rf95.waitAvailableTimeout(3000))
  {
    //Si se recibe respuesta antes de los tres segundos:
    if (rf95.recv(buf, &len))
    {
      Serial.print("¡Obtuve respuesta!: ");
      Serial.println((char*)buf);
    }
    //Si no se recibe respuesta despues de los tres segundos:
    else
    {
      Serial.println("¡No obtuve respuesta! ");
    }
  }
  else
  {
    Serial.println("No se detecto un servidor");
  }
  delay(400);
}
