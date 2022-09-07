#include "config.h"
#include "bootstrap.h"

#include <Utilities.h>
#include <RotaryEncoder.h>
#include <OneButton.h>

RotaryEncoder   *encoder    = nullptr;

#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

kernel          *ucKernel    =   nullptr;


uint16_t presetTemp =   120;

int _dutycycle  =   50;


void setup() 
{
    Serial.begin(115200);
    Serial.println("toySolder init");

    init_gpio();

    lcd.backlight();
    lcd.begin();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("the Iron Solder");
    lcd.setCursor(9, 1);
    lcd.print("v1.7.11");
    delay(1200);


    encoder = new RotaryEncoder(PIN_ENCA, PIN_ENCB, RotaryEncoder::LatchMode::TWO03);


    ucKernel = new kernel(&lcd);

    ucKernel->boot();


    loadConfig();

         /**
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("PRESET T : ");  
    lcd.setCursor(0, 0);
    lcd.print("ACTUAL T : "); 
*/


    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Duty cycle: ");

    lcd.setCursor(3, 0);
    lcd.print("pwmController v1.0");

    encoder->setPosition(_dutycycle);

    ucKernel->start();
}


volatile int _standby = 0;
unsigned long tInterval, tStandby;
void loop() 
{	
    static int lastpos = 0;

    encoder->tick();

    int _pos = (int) encoder->getPosition();
    if (ROTARYMIN > _pos) {
        _pos   = ROTARYMIN;        
        encoder->setPosition(_pos);
    }
    else if (ROTARYMAX < _pos) {
        _pos   = ROTARYMAX;        
        encoder->setPosition(_pos);
    }

    if (lastpos != _pos) {        
        _dutycycle  = _pos;
        presetTemp  = _pos;

        lastpos     = _pos;
    }

    
    analogWrite(PIN_CONTROL, _dutycycle);




    ucKernel->handle();    
    ucKernel->terminate();




    /**
     * @brief Sensor Data collector
     * 
     *    int sensor_raw = analogRead(PIN_SENSOR);
     * 
     *     
     * @brief Average of Temp Sensor and Knob
     * 
     * 
     * @brief Iron Soldering PWM Controller
     * 
     * 
     * @brief Display data on Lcd
     * 
     */
    if (doEvery(&tInterval, 255)) {   
        lcd.setCursor(11, 1);

        if (_dutycycle == ROTARYMAX) {
            lcd.print(" MAX ");
        }
        else  if (_dutycycle < 9) {
            lcd.print(" 00");
        }
        else if (_dutycycle < 100) {
            lcd.print(" 0");
        }
        else if (_dutycycle >= 100) {
            lcd.print(" ");
        }        
        else {
            lcd.print(" 000");
        }

        lcd.print(_dutycycle);
    }


    if (doEvery(&tStandby, 1000)) {
        _standby++;

        if (_standby > (TIME2STANDBY*60)) {
            Serial.println(" toggle to standby.");
        }
        else if (_standby > (TIME2SLEEP*60)) {            
            Serial.println(" toggle to sleep.");
        }
    }
}


void loadConfig()
{
    uint16_t _id = (EEPROM.read(0) << 8) | EEPROM.read(1);

    if( _id == HKID_EEPROM ) {

    }
    else {
        EEPROM.update(0, HKID_EEPROM >> 8);
        EEPROM.update(1, HKID_EEPROM & 0xff);
        updateConfig();
    }
}

void updateConfig()
{

}



void drawHeatController() 
{
    if (presetTemp < 180) {
        lcd.setCursor(10, 1);       
        lcd.print("OFF  ");
    }
    else {            
        lcd.setCursor(10, 1);       
        lcd.print(presetTemp); 
        lcd.print((char)223);
        lcd.print("C ");
    }

    lcd.setCursor(10, 0);       lcd.print("COOL ");                     //lcd.print((char)223);lcd.print("C ");
}



