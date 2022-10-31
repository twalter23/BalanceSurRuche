#include "DEFINE.h"
#include "SevSeg.h"
#include "Battery.h"
#include "SevenSeg.h"
#include "Display.h"

SevSeg sevseg; //Instantiate a seven segment object (global)

int i16_Weight, i16_WeightMemo;

//-------------setup------------//
void setup() {
	
  //Debug 
  Serial.begin(57600); // open the serial port at 57600 bps: 
  //Serial.println("1");

  //SevSeg Setup
  SevSegSetup();
  //Serial.println("2");
  
  //Battery
  BatteryADCSetup();
  //Serial.println("3");

  TestBatteryLevelWithDisplayOff();
}

//-------------loop------------//
void loop() {
static bool b_TimerSetup=0, sb_DisplayEnabled;
static unsigned long ul_32Timer; 
static long sl_32Timer;


  if(b_TimerSetup==0)//Initialisation of Timer
  {
    sl_32Timer=(millis()-BATTERY_VOLTAGE_READ_FREQUENCY_ms);//get time for timer
    ul_32Timer=millis();
    i16_WeightMemo = 0;
    b_TimerSetup=1;//Set initialisation to done
    //Serial.println(1);
  }
  
  if(millis()>(sl_32Timer+BATTERY_VOLTAGE_READ_FREQUENCY_ms))//Time to read battery level
  {
    sl_32Timer=millis();//reset timer
    // CheckVoltageLevel(ReadVoltage(1000,ui16_WeightMemo,1));//ReadBatVoltage
	  sb_DisplayEnabled=EnableOrNotDisplay();
  }

    if (Serial.available() >= 2) // There are at least 2 bytes to read
    {
       i16_Weight = 0;
       i16_Weight = (Serial.read() << 8);   // read high byte and shift it over
       i16_Weight |= Serial.read();   // read low byte
       i16_WeightMemo=i16_Weight;
    }
	
    if(i16_WeightMemo>=1000)
    {
        i16_WeightMemo-=1000;//Weight is superior to 100kg
	  }

    if (sb_DisplayEnabled==0)//Eteint
    {
    digitalWrite(PIN_N_TRANSISTOR_1,LOW);
    digitalWrite(PIN_N_TRANSISTOR_2,LOW);
    digitalWrite(PIN_N_TRANSISTOR_3,LOW);
    }

    else//allumé
    {
       //Serial.println(i16_WeightMemo);
       sevseg.setNumber(i16_WeightMemo,1); // Displays Weight
       sevseg.refreshDisplay();
    }

}





