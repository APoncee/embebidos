// Autores: Adrian Ponce - Miguel Freire
// Paralelo 104

/* ----------------------------LIBRERIAS-----------------------------------*/
#include <Arduino.h>
#include <Wire.h>              
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>


/*-----------------MOTOR---------------------------------------------------*/

int motor1Pin1 = 4; 
int motor1Pin2 = 5; 
int enable1Pin = 13; 
int potenciometro;
// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;

/*---------------------LCD INFORMACION -------------------------------------*/


#define COLUMS 16
#define ROWS   2
#define PAGE   ((COLUMS) * (ROWS))
#define SENSOR_PIN 23 // ESP32 pin GIOP23 QUE SE CONECTA CON EL MODULO DS18B20 sensor's DQ pin
OneWire oneWire(SENSOR_PIN);
DallasTemperature DS18B20(&oneWire);

float tempC;
float tempF;


/*------------------------------------------------*/ 
LiquidCrystal_I2C lcd(PCF8574_ADDR_A21_A11_A01, 4, 5, 6, 16, 11, 12, 13, 14, POSITIVE);


/*--------------------------------------------------------------------------------------------------------------------------*/


void setup() {

  DS18B20.begin(); 
  Serial.begin(115200);

  while (lcd.begin(COLUMS, ROWS) != 1) //colums - 20, rows - 4
  {
       
  }
  lcd.print(F("Paralelo 104"));
  lcd.setCursor(0,1);
  lcd.print(F("CAMARONERA..."));
  delay(5000);

  lcd.clear();



  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  
  
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel);

  //Serial.begin(115200);
  Serial.print("Testing DC Motor...");
}

void loop() {
  
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH); 
  delay(2000);
/*
  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000); */

 /* // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  delay(1000);

  // Move DC motor forward with increasing speed
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);*/
  lcd.setCursor(3,0);	//columna - fila
  
  while (dutyCycle <= 255){
    lcd.print("Temperatura: PH:");
    DS18B20.requestTemperatures(); 
    potenciometro=analogRead(33);
  tempC = DS18B20.getTempCByIndex(0); 
  

 
  lcd.setCursor(0,1);
  lcd.print(tempC);
  lcd.print("oC");
  lcd.setCursor(13,1);
  lcd.print(potenciometro*0.00342298);
  delay(800);
  lcd.clear();
    ledcWrite(pwmChannel, dutyCycle);   
    Serial.print("Forward with duty cycle: ");
    Serial.println(dutyCycle);
    dutyCycle = dutyCycle ;
  }
  dutyCycle = 200;
}