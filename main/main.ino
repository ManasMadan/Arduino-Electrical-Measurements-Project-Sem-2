/*
  Author : Manas Madan, Ayush Arora, Krish Gupta
*/

// Importing Required Header Files
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "DHT.h"

// PINS for Sensors
const int SOIL_MOISTURE_PIN = A1;
const int LDR_PIN = A0;
const int DHT_PIN = 8; // D8

// PINS for Grow Light
const int YELLOW_PIN = 11; // D11
const int RED_PIN = 12; // D12

const int WATER_PUMP_PIN = 10; // D10

// Contants
const int LDR_THRESHOLD = 500;
const int TIMES_WATER_THRESHOLD = 5;
const int SOIL_MOISTURE_THRESHOLD = 50;
const int TEMPERATURE_THRESHOLD = 30;
const int WATER_CYCLE_GAP = 3; // Enter Time in Hours

enum GROW_LIGHT_COLOR {YELLOW, RED};

// Declaring Objects
DHT dht;
LiquidCrystal_I2C lcd(0x27,16,2);

// Functions for Light
void turn_off_grow_lights(){
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(RED_PIN, LOW);
}

void turn_on_grow_lights(int color){
  if(color == 0){
    digitalWrite(YELLOW_PIN, HIGH);
    digitalWrite(RED_PIN, LOW);

  }else{
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);

  }
}

bool isEnoughLightTime(){
  return false;
}

// Functions for Water
int timesWateredToday(){
  return 0;
}

bool isEnoughGapBetweenWaterCycle(){
  return true;
}

void turn_off_water_pump(){
  digitalWrite(WATER_PUMP_PIN,LOW);
}

void turn_on_water_pump(){
  digitalWrite(WATER_PUMP_PIN,HIGH);
}

// Functions for LCD
void print_to_lcd(float moisture_percentage,float humidity_percentage,float temperature_celcius){
  lcd.setCursor(0,0);
  lcd.print("Moist Humid Temp");
  lcd.setCursor(0, 1);
  lcd.print(moisture_percentage);
  lcd.setCursor(6, 1);
  lcd.print(humidity_percentage);
  lcd.setCursor(12, 1);
  lcd.print(temperature_celcius);
}

void setup() {
  lcd.init();
  lcd.backlight();
  dht.setup(DHT_PIN); 

  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);

  turn_off_water_pump();
  turn_off_grow_lights();
}


// Declaring Variables
int ldr_value = 0;
float moisture_percentage = 0;
int soil_moisture_analog = 0;
float humidity_percentage = 0;	    
float temperature_celcius = 0;

void loop() {
  delay(dht.getMinimumSamplingPeriod());
  lcd.clear();
  enum GROW_LIGHT_COLOR color = RED;

  // Reading Sensor Inputs
  ldr_value = analogRead(LDR_PIN);
  soil_moisture_analog = analogRead(SOIL_MOISTURE_PIN);
  moisture_percentage = ( 100 - ( (soil_moisture_analog/1023.00) * 100 ) );
  humidity_percentage = dht.getHumidity();
  temperature_celcius = dht.getTemperature();

  print_to_lcd(moisture_percentage,humidity_percentage,temperature_celcius);
  if(dht.getStatusString() == "OK"){
    if(temperature_celcius <= TEMPERATURE_THRESHOLD){
      color = YELLOW;
    }
  }

  if(ldr_value <= LDR_THRESHOLD && !isEnoughLightTime()){
    turn_on_grow_lights(color);
  }else{
    turn_off_grow_lights();
  }

  if(moisture_percentage <= SOIL_MOISTURE_THRESHOLD && timesWateredToday() <= TIMES_WATER_THRESHOLD && isEnoughGapBetweenWaterCycle()){
    turn_on_water_pump();
  }else{
    turn_off_water_pump();
  }


  delay(1000);
}