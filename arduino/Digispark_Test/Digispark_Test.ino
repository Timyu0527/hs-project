#include "DigiKeyboard.h"

void setup(){}

void loop()
{
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.sendKeyStroke(KEY_S, MOD_GUI_LEFT);
  DigiKeyboard.delay(50);
  DigiKeyboard.print("https://www.youtube.com/watch?v=Su_fB9Rk_ks");
  DigiKeyboard.sendKeyStroke(KEY_ENTER);
  for(;;){}
}
