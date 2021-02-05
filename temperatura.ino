#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  mlx.begin();  
}

void loop() {
  Serial.print("Ambiente = "); Serial.print(mlx.readAmbientTempC()); Serial.print("*C");
  Serial.print(" Objeto= "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
  //Serial.println(mlx.readObjectTempC());
  delay(300);
}
