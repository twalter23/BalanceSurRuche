/*******************************Pin Mapping Definition*******************************/

#ifndef _DEFINE_H    // Put these two lines at the top of your file.
#define _DEFINE_H    // (Use a suitable name, usually based on the file name.)

//Threshold values for battery level
#define LOW_BATT_HYST_LOW_THRESHOLD_mV 3300 //mV
#define LOW_BATT_HYST_HIGH_THRESHOLD_mV 3800 //mV
//End of threshold values for battery level

//Others for battery
#define BATTERY_VOLTAGE_READ_FREQUENCY_ms 5000 //ms
#define ADC_CALIBRATION_GAIN 1.07 //Empirical (1,14)
//End of others for battery

//Pin Mapping for battery
#define LED_LOW_BAT_PIN 13//mcu > Low Battery LED dout pin
#define PIN_BATTERY_VOLTAGE_INPUT A0 //A0
//End of pin Mapping for battery

//Pin Mapping for 7 Segment
//Transistors (common cathode)
#define PIN_N_TRANSISTOR_1 2
#define PIN_N_TRANSISTOR_2 11
#define PIN_N_TRANSISTOR_3 12

#define PIN_SEGMENT_A 5
#define PIN_SEGMENT_B 10
#define PIN_SEGMENT_C 7
#define PIN_SEGMENT_D 6
#define PIN_SEGMENT_E 8
#define PIN_SEGMENT_F 9
#define PIN_SEGMENT_G 3
#define PIN_SEGMENT_H 4
//End of pin Mapping for 7 Segment

#endif // _HEADERFILE_H    // Put this line at the end of your file. (to avoid multiple define issue)
