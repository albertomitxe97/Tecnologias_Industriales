#include <Arduino_APDS9960.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include<Servo.h>

Servo servomotor1;
Servo servomotor2;
uint16_t total_r, total_g, total_b, total_c;
//Limites de cada color
uint16_t black_limit_values[] = {0, 200, 0, 200, 0, 200};
uint16_t yellow_limit_values[] = {167, 220, 183, 251, 77, 102};
uint16_t green_limit_values[] = {55, 70, 115, 175, 47, 67};
uint16_t orange_limit_values[] = {140, 170, 70, 100, 40, 70};
uint16_t red_limit_values[] = {90, 140, 50, 100, 70, 125};
uint16_t purple_limit_values[] = {0, 30, 0, 35, 0, 35};
int grado=0;
float sum;
// setup RGB sensor
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);
  
void setup() {
Serial.begin(9600);
while (!Serial) {};
Serial.println("Red,Green,Blue");
servomotor1.attach(4);//Configuración salidas servo
servomotor2.attach(5);
}

void loop() { 
  servomotor1.write(0); //Servo 1 a 0
  delay(1000);
  servomotor1.write(90); //Servo 1 posición lectura
  delay(500);
  // wait for proximity and color sensor data
  if (tcs.begin()) {    //check if sensor found
    Serial.println("Found sensor");
    // Obtención de datos RGB
    tcs.getRawData(&total_r, &total_g, &total_b, &total_c);
    Serial.print(total_r);
    Serial.print(',');
    Serial.print(total_g);
    Serial.print(',');
    Serial.print(total_b);
    Serial.println();
    delay (2000);
   }
 //Clasificación de color en función del RGB
    if ((total_r >= yellow_limit_values[0]) &&   //check for yellow
           (total_r < yellow_limit_values[1]) &&
           (total_g >= yellow_limit_values[2]) &&
           (total_g < yellow_limit_values[3]) &&
           (total_b >= yellow_limit_values[4]) &&
           (total_b < yellow_limit_values[5]))
    {Serial.print("Amarillo");
    grado=10;
    }
    else if ((total_r >= green_limit_values[0]) &&   //check for green
           (total_r < green_limit_values[1]) &&
           (total_g >= green_limit_values[2]) &&
           (total_g < green_limit_values[3]) &&
           (total_b >= green_limit_values[4]) &&
           (total_b < green_limit_values[5]))
    {Serial.print("Verde");
    grado=46;}
    else if ((total_r >= orange_limit_values[0]) &&   //check for orange
           (total_r < orange_limit_values[1]) &&
           (total_g >= orange_limit_values[2]) &&
           (total_g < orange_limit_values[3]) &&
           (total_b >= orange_limit_values[4]) &&
           (total_b < orange_limit_values[5]))
    {Serial.print("Naranja");
    grado=82;}
    else if ((total_r >= red_limit_values[0]) &&   //check for red
           (total_r < red_limit_values[1]) &&
           (total_g >= red_limit_values[2]) &&
           (total_g < red_limit_values[3]) &&
           (total_b >= red_limit_values[4]) &&
           (total_b < red_limit_values[5]))
    {Serial.print("Rojo");
    grado=118;}
    else if ((total_r >= purple_limit_values[0]) &&   //check for purple
           (total_r < purple_limit_values[1]) &&
           (total_g >= purple_limit_values[2]) &&
           (total_g < purple_limit_values[3]) &&
           (total_b >= purple_limit_values[4]) &&
           (total_b < purple_limit_values[5]))
    {Serial.print("Morado");
    grado=154;}
    else
    {Serial.print("No identificado");
    grado=10;}
    Serial.println();
    servomotor2.write(grado); // Giro posicionador
    delay (500);
    servomotor1.write(180); // Deposición Skittles
    delay(1000);
  }
