#include "DEFINE.h"
#include "SevSeg.h"
  SevSeg sevseg; //Instantiate a seven segment object (global)

//----------------------------------------------------------------------------------------------------------------------------------------------//
void SevSegSetup()
{
  unsigned long ul_32Timer;
  const long ul_32Delay888 = 1000;//1000ms Delay constant
  const long ul_32DelayTiret = 1000;//1000ms Delay constant
  
  byte numDigits = 3;
  byte digitPins[] = {PIN_N_TRANSISTOR_1, PIN_N_TRANSISTOR_2, PIN_N_TRANSISTOR_3};
  byte segmentPins[] = {PIN_SEGMENT_A, PIN_SEGMENT_B, PIN_SEGMENT_C, PIN_SEGMENT_D, PIN_SEGMENT_E, PIN_SEGMENT_F, PIN_SEGMENT_G, PIN_SEGMENT_H};
  bool resistorsOnSegments = true; // 'false' means resistors are on digit pins, 'true' on segment
  byte hardwareConfig = N_TRANSISTORS; // See README.md for options
  bool updateWithDelays = false; // Default 'false' is Recommended
  bool leadingZeros = false; // Use 'true' if you'd like to keep the leading zeros
  bool disableDecPoint = false; // Use 'true' if your decimal point doesn't exist or isn't connected. Then, you only need to specify 7 segmentPins[]
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments,
  updateWithDelays, leadingZeros, disableDecPoint);
  sevseg.setNumber(888,1);
  sevseg.refreshDisplay();
  }
//----------------------------------------------------------------------------------------------------------------------------------------------//

/************************************************************************************************************************************************/
														//Battery related functions
/************************************************************************************************************************************************/
//----------------------------------------------------------------------------------------------------------------------------------------------//
void BatteryADCSetup()
{
  // put your setup code here, to run once:
  pinMode(LED_LOW_BAT_PIN, OUTPUT);
  analogReference(INTERNAL);//Depends of board type
  
}

 int ui_16GetBatVoltage()
  {
    unsigned int ui_16Batt_LVL_local;
    Serial.print("Valeur non mappé ");
    //Serial.println(analogRead(PIN_BATTERY_VOLTAGE_INPUT));
    ui_16Batt_LVL_local = ((map(analogRead(PIN_BATTERY_VOLTAGE_INPUT), 0, 1023, 0, 4200))*ADC_CALIBRATION_GAIN);
    Serial.print("Valeur mappé ");
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

//----------------------------------------------------------------------------------------------------------------------------------------------//

bool EnableOrNotDisplay()
  { 
    unsigned int ui_16BatteryVoltage;
    static bool sb_DisplayStatus=0;//Affichage désactivé au démarrage
    
    ui_16BatteryVoltage=ui_16GetBatVoltage();//Retourne la tension de la batterie en mV
    
    //Serial.println(ui_16BatteryVoltage);
    
    if(sb_DisplayStatus==1)//On est en haut de l'hystérésis (affichage allumé)
    {
      if(ui_16BatteryVoltage>LOW_BATT_HYST_LOW_THRESHOLD_mV)//On est au dessus du seuil de descente => On reste en haut
      {
        //sb_DisplayStatus=1;//Utile?
        SetDisplayOn();//Autorise l'affichage et désactive la LED Batterie faible
      }
      else//On est en dessous du seuil de descente => On descend
      {
        sb_DisplayStatus=0;//Changement de statut de l'affichage
        SetDisplayOff();
      }
    }else//On est en bas de l'hystérésis : b_DisplayStatus==0
    {
      if(ui_16BatteryVoltage>LOW_BATT_HYST_HIGH_THRESHOLD_mV)//On est au dessus du seuil de remontée => On remonte
      {
        sb_DisplayStatus=1;//Changement de statut de l'affichage
        SetDisplayOn();//Autorise l'affichage et désactive la LED Batterie faible
      }
      else//On est en dessous du seuil de remontée => On reste en bas
      { //sb_DisplayStatus=0;//Utile?
        SetDisplayOff();
      }
    }
    return sb_DisplayStatus;
  }
//----------------------------------------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------------------------------------//
  void SetDisplayOn()
  {
    //Active la commande de la base des transistors d'affichage
    /*digitalWrite(PIN_N_TRANSISTOR_1,HIGH);
    digitalWrite(PIN_N_TRANSISTOR_2,HIGH);
    digitalWrite(PIN_N_TRANSISTOR_3,HIGH);
    */
    //Désactive la LED batterie faible
    digitalWrite(LED_LOW_BAT_PIN, LOW);
  }

//----------------------------------------------------------------------------------------------------------------------------------------------//

//----------------------------------------------------------------------------------------------------------------------------------------------//
  void SetDisplayOff()
  {
    //Désactive la commande de la base des transistors d'affichage
    /*
    digitalWrite(PIN_N_TRANSISTOR_1,LOW);
    digitalWrite(PIN_N_TRANSISTOR_2,LOW);
    digitalWrite(PIN_N_TRANSISTOR_3,LOW);
    */
    //Active la LED batterie faible
    digitalWrite(LED_LOW_BAT_PIN, HIGH);
  }

//----------------------------------------------------------------------------------------------------------------------------------------------//


//----------------------------------------------------------------------------------------------------------------------------------------------//
int i16_Weight, i16_WeightMemo;
/************************************************************************************************************************************************/
//-------------setup------------//
void setup() {
	
  //Debug 
  Serial.begin(57600); // open the serial port at 9600 bps: 
  //Serial.println("1");

  //SevSeg Setup
  SevSegSetup();
  //Serial.println("2");
  
  //Battery
  BatteryADCSetup();
  //Serial.println("3");

  TestBatteryLevelWithDisplayOff();
}
/************************************************************************************************************************************************/

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
       Serial.println(i16_WeightMemo);
       sevseg.setNumber(i16_WeightMemo,1); // Displays Weight
       sevseg.refreshDisplay();
    }

}





