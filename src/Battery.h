#ifndef _BATTERY_H    // Put these two lines at the top of your file.
#define _BATTERY_H    // (Use a suitable name, usually based on the file name.)


void BatteryADCSetup(void);
int ui_16GetBatVoltage(void);
void TestBatteryLevelWithDisplayOff(void);



#endif // _HEADERFILE_H    // Put this line at the end of your file. (to avoid multiple define issue)