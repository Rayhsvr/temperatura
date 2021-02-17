#include <TM1637Display.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

// SCL -A5
// SDA - A4

#define CLK 2
#define DIO 3
#define ZOOM 5
int ECHO = 10;
int TRIG = 9;
int distancia;
float temperatura;
float ajusTemp=5; // Ajuste de Temperatura
int entero;
float decimales;

/***   Function declaration   ***/
//bqBAT
long TP_init(int trigger_pin, int echo_pin);
long Distance(int trigger_pin, int echo_pin);


//Declaración del objeto del sensor de temperatura

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

// Declaración del objeto Display

TM1637Display display(CLK,DIO);

void setup() {

  pinMode( ECHO , INPUT );
  pinMode( TRIG , OUTPUT );
  pinMode( ZOOM , OUTPUT );
  
  Serial.begin(9600);
  mlx.begin();  

  display.setBrightness(5);
}

void loop() {
    distancia=Distance(TRIG,ECHO);
  if (distancia >= 0.3 && distancia <= 5) {
    temperatura=mlx.readObjectTempC()+ajusTemp;
    entero = (int) temperatura;
    decimales = temperatura - entero;
    // Serial.print("Ambiente = "); Serial.print(mlx.readAmbientTempC()); Serial.print("*C");
    Serial.print(" Objeto= "); Serial.print(temperatura); Serial.print(", "); Serial.print(decimales); Serial.println("*C");
    //Serial.println(mlx.readObjectTempC());
//    display.setBrightness(5);
    if (temperatura <= 37.5) {
      tone(ZOOM,800,300);
    }
    else {
      tone(ZOOM,200,100);
      delay(200);
      tone(ZOOM,200,300);
    }
    display.showNumberDecEx(temperatura,0b01000000,false,2,0);
    display.showNumberDec(decimales*100,false,2,2);
    delay(1500);
    display.clear();
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
