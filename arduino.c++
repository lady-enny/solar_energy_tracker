#include <splash.h>

#include <DallasTemperature.h>

#include <OneWire.h>
#include <Adafruit_SSD1306.h>

const int oneWirePin = 2;

OneWire oneWire(oneWirePin);
DallasTemperature sensors(&oneWire);


float temperature = 0;
float power = 0;
float energy = 0;
unsigned long previousMillis = 0;


  // include the library code: 
#include <LiquidCrystal.h> //library for LCD 

// initialize the library with the numbers of the interface pins 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 

//Measuring Current Using ACS712 
int sensitivity = 185; // use 100 for 20A Module and 66 for 30A Module 
int adcvalue= 0; 
int offsetvoltage = 2500;  //Sensor Callibration
double Voltage = 0; //voltage measuring 
double ecurrent = 0;// Current measuring 


void setup() 
{
  lcd.begin(20, 4); // set up the LCD's number of columns and rows:
  lcd.setCursor(0,0);
  lcd.print("  SOLAR MONITORING             ");

  sensors.begin();
} 

void loop()
{ 
  // Measure The Votage ***********************************
  // read the input on analog pin A1:
  int sensorValue = analogRead(A1);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float vol = (sensorValue * 5.0) / 1023.0;

  float voltage = vol * 5;
  lcd.setCursor(0,1);
  lcd.print("  Voltage = ");
  lcd.print(voltage);
  lcd.print("V");

  // Measure The Current ***********************************
  adcvalue = analogRead(A0);//reading the value from the analog pin A0
  Voltage = (adcvalue / 1024.0) * 5000; // Gets you mV 
  ecurrent = ((Voltage - offsetvoltage) / sensitivity); 
  lcd.setCursor(0,2); 
  lcd.print("  Current = "); 
  lcd.print(ecurrent); 
  lcd.print("A"); //unit for the current to be measured 
  delay(2000); 

  power = voltage*ecurrent;
  lcd.setCursor(1,1);
  lcd.print("  Power =  ");
  lcd.print(power);
  lcd.print("W");


  unsigned long currentMillis = millis();
  energy = power*(currentMillis-previousMillis)/3600000;
  lcd.setCursor(1,2);
  lcd.print("  Energy =  ");
  lcd.print(energy);
  lcd.print("Wh");
  



  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  temperature = sensors.getTempFByIndex(0);
  lcd.setCursor(0,3);
  lcd.print("  Temp. = ");
  lcd.print(temperature);
  lcd.print("*C");
  delay(2000);
}

