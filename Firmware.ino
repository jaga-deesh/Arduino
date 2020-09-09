
// Include Libraries
#include "Arduino.h"
#include "DHT.h"
#include "LiquidCrystal.h"
#include "Relay.h"


// Pin Definitions
#define DHT_PIN_DATA	2
#define LCD_PIN_RS	8
#define LCD_PIN_E	7
#define LCD_PIN_DB4	3
#define LCD_PIN_DB5	4
#define LCD_PIN_DB6	5
#define LCD_PIN_DB7	6
#define RELAYMODULE1_1_PIN_SIGNAL	9
#define RELAYMODULE2_2_PIN_SIGNAL	10
#define TEMP_LIMIT_UP 37.5
#define TEMP_LIMIT_LOW 37.3
#define HUMIDITY_UP 80.0
#define HUMIDITY_LOW 75.0


// Global variables and defines

// object initialization
DHT dht(DHT_PIN_DATA);
LiquidCrystal lcd(LCD_PIN_RS,LCD_PIN_E,LCD_PIN_DB4,LCD_PIN_DB5,LCD_PIN_DB6,LCD_PIN_DB7);
Relay relayModule1_1(RELAYMODULE1_1_PIN_SIGNAL);
Relay relayModule2_2(RELAYMODULE2_2_PIN_SIGNAL);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    dht.begin();
    // set up the LCD's number of columns and rows
    lcd.begin(16, 2);
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    float dhtHumidity =dht.readHumidity();
    float dhtTempC = dht.readTempC();
    lcd.setCursor(0, 0);
    lcd.print("Humidity:  ");lcd.print(dhtHumidity);
    lcd.setCursor(0, 1);
    lcd.print("Temp:  ");lcd.print(dhtTempC);
    delay(2000);

    //TEMPERATURE RELAY
    if(dhtTempC>=TEMP_LIMIT_UP){
       relayModule1_1.off();
    }
    else if(dhtTempC<TEMP_LIMIT_LOW){
      relayModule1_1.on();
    }

    //HUMIDITY RELAY
    if(dhtHumidity>=HUMIDITY_UP){
       relayModule1_1.off();
    }
    else if(dhtHumidity<HUMIDITY_LOW){
      relayModule1_1.on();
    }    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu(){
  return "1";
}
 /* char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(2) LCD 16x2"));
    Serial.println(F("(3) Relay Module #1"));
    Serial.println(F("(4) Relay Module #2"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing LCD 16x2"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Relay Module #1"));
    		else if(c == '4') 
    			Serial.println(F("Now Testing Relay Module #2"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
*/
