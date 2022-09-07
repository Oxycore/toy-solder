#ifndef __BOOTSTRAP_H__
#define __BOOTSTRAP_H__

#include <LiquidCrystal_I2C.h>

const int stbTemp      =   150;
const int minTemp      =   27;
const int maxTemp      =   500;

/*
namespace bootstrap 
{
    int pwm_value       = 0;
    int sensor_raw      = 0;
    int counter         = 0;
    int presetTemp      = 0;

    float currentTemp   = 0.0;
}
*/

enum class t_STATE {
    BOOT    = 0,
    START,
    HEATC,
    SETUP,
    SLEEP,
    STDBY,
    SYNTAX
};



class kernel {
private:
    bool booted     =   false;
    LiquidCrystal_I2C *_view;
    t_STATE _state;

public:
    kernel(LiquidCrystal_I2C *view);
    ~kernel();

    void boot();

    void start();

    void handle();

    void terminate(char **command);
    void terminate();
};


void init_gpio();



#endif //!eoif __BOOTSTRAP_H__
