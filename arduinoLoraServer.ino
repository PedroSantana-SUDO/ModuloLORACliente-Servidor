#include <SPI.h>
#include <RH_RF95.h>

RH_RF95 rf95;

int led = 13; //Se usará este led para indicar que llegó un mensaje

void setup() 
{

  pinMode(led, OUTPUT);     
  Serial.begin(9600);
  while (!Serial) ; 
  if (!rf95.init())
    Serial.println("Fallo de inicialización");  
  //Los valores usados tras inicializar el dispositivo es frecuencia de 868MHz y 13dBm con un ancho de banda de 125kHz
}

void loop()
{
  if (rf95.available())
  {
    // Se espera que ya se tenga un mensaje en el buffer
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    if (rf95.recv(buf, &len))
    {
      digitalWrite(led, HIGH);
      Serial.print("Llegó un mensaje: ");
      Serial.println((char*)buf);
      
      // Envio de respuesta
      uint8_t data[] = "Mandando mensaje desde el servidor";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      Serial.println("Envío de respuesta");
       digitalWrite(led, LOW);
    }
    else
    {
      Serial.println("No se recibe nada");
    }
  }
}
