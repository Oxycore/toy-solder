#ifndef CONFIG_H_PCH
#define CONFIG_H_PCH

#ifndef Arduino_h
#include <Arduino.h>
#endif

#define PIN_ENCA        2       // Encoder Phase A
#define PIN_ENCB        3       // Encoder Phase B
#define PIN_ENCSW_      4       // Encoder Switch

#define PIN_CONTROL     10       // PWM Output
#define PIN_HEATING     12       // LED Output
#define PIN_PWROK       13       // LED Output
#define PIN_BREAK       11

#define PIN_SENSOR      A0
#define PIN_VINADC      A1

#define HKID_EEPROM     0xE420



#define ROTARYMAX       254
#define ROTARYMIN       0


#define TIME2SLEEP      5
#define TIME2STANDBY    15

#endif
