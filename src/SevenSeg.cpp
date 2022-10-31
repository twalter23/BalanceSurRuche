#include "DEFINE.h"
#include "SevSeg.h"
#include "Battery.h"
#include "SevenSeg.h"
#include "Display.h"

void SevSegSetup()
{
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