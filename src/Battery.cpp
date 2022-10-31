#include "DEFINE.h"
#include "SevSeg.h"
#include "Battery.h"
#include "SevenSeg.h"
#include "Display.h"


void BatteryADCSetup()
{
  // put your setup code here, to run once:
  pinMode(LED_LOW_BAT_PIN, OUTPUT);
  analogReference(INTERNAL);//Depends of board type, for nano it is 1.1V
}

/**/

int ui_16GetBatVoltage()
{
unsigned int ui_16Batt_LVL_local;
//Serial.print("Valeur non mappé ");
//Serial.println(analogRead(PIN_BATTERY_VOLTAGE_INPUT));

ui_16Batt_LVL_local = ((map(analogRead(PIN_BATTERY_VOLTAGE_INPUT), 0, 1023, 0, 4200))*ADC_CALIBRATION_GAIN);
//Serial.print("Valeur mappé ");

//Serial.println(ui_16Batt_LVL_local);

return ui_16Batt_LVL_local;
}

void TestBatteryLevelWithDisplayOff()
{
  digitalWrite(PIN_N_TRANSISTOR_1,LOW);//On éteint l'afficheur pour le test de la batterie au démarrage
  digitalWrite(PIN_N_TRANSISTOR_2,LOW);
  digitalWrite(PIN_N_TRANSISTOR_3,LOW);
  EnableOrNotDisplay();
}