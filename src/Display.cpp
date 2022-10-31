#include "DEFINE.h"
#include "SevSeg.h"
#include "Battery.h"
#include "SevenSeg.h"
#include "Display.h"

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