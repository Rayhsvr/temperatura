#include <Wire.h>
#include <Adafruit_MLX90614.h>

// SCL -A5
// SDA - A4


int ECHO = 10;
int TRIG = 9;
int distancia;

/***   Function declaration   ***/
//bqBAT
long TP_init(int trigger_pin, int echo_pin);
long Distance(int trigger_pin, int echo_pin);


//Declaración del objeto del sensor de temperatura

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {

  pinMode( ECHO , INPUT );
  pinMode( TRIG , OUTPUT );
  
  Serial.begin(9600);
  mlx.begin();  
}

void loop() {
    distancia=Distance(TRIG,ECHO);
  if (distancia <= 5) {
    // Serial.print("Ambiente = "); Serial.print(mlx.readAmbientTempC()); Serial.print("*C");
    Serial.print(" Objeto= "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
    //Serial.println(mlx.readObjectTempC());
    delay(300);
  }
}

/***   Function definition   ***/
//bqBAT
long TP_init(int trigger_pin, int echo_pin)
{
//  digitalWrite(trigger_pin, LOW);
//  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(1);
  digitalWrite(trigger_pin, LOW);
  long microseconds = pulseIn(echo_pin ,HIGH);
  return microseconds;
}

long Distance(int trigger_pin, int echo_pin)
{
  long microseconds = TP_init(trigger_pin, echo_pin);
  long distance;
  distance = microseconds/58.2;
/*  if (distance == 0){
    distance = 999;
  } */
  return distance;
}
