#include <Arduino.h>
#include <LiquidCrystal_I2C.h>


#include "bootstrap.h"
#include "config.h"



void init_gpio()
{
    pinMode(PIN_ENCA,       INPUT_PULLUP);
    pinMode(PIN_ENCB,       INPUT_PULLUP);
    pinMode(PIN_ENCSW_,     INPUT);

    pinMode(PIN_HEATING,    OUTPUT);
    pinMode(PIN_PWROK,      OUTPUT);
    pinMode(PIN_BREAK,      OUTPUT);

    digitalWrite(PIN_BREAK,     HIGH);
    digitalWrite(PIN_HEATING,   HIGH);
    digitalWrite(PIN_PWROK,     LOW);

}



kernel::kernel(LiquidCrystal_I2C* view)
{
    _view = view;
}

kernel::~kernel()
{}


void kernel::boot()
{
    if (this->booted == false) {
        this->_state = t_STATE::START;

        this->booted = true;
    }


}

void kernel::handle()
{
    switch (this->_state)
    {
    case t_STATE::BOOT:     
        //Serial.println("boot");   
        break;

    case t_STATE::START:
        this->_state = t_STATE::HEATC;
        break;

    case t_STATE::HEATC:
        Serial.println("HEATING");
        break;

    case t_STATE::SETUP:
        break;

    case t_STATE::SLEEP:
        break;

    case t_STATE::STDBY:
        break;

    case t_STATE::SYNTAX:
        break;
    
    default:
        break;
    }
}


void kernel::start()
{
    _state = t_STATE::START;
}


void kernel::terminate(char **command)
{
}

void kernel::terminate()
{
    this->_view->setCursor(0, 0);
    this->_view->print("  -> terminated");
}
