import netP5.*;
import oscP5.*;

OscP5 oscP5;
NetAddressList Netaddresslist = new NetAddressList();

int ListeningPort = 12001;
int BroadcastPort = 12000;

int m = 0, k = 0, keys = 1;
int[] keybroad = new int[keys+1];
int playtime = 10000;
IntList record = new IntList();
IntList deltaTime = new IntList();
IntList LEDred = new IntList();
IntList LEDgreen = new IntList();
IntList LEDblue = new IntList();
IntList press = new IntList();

String ConnectPattern = "/server/connect";

void setup()
{
  size(500, 400);
  oscP5 = new OscP5(this, ListeningPort);
  
  Set();
}

void draw()
{
  background(0);
  if(m == 0) display();
}

void keyPressed()
{
  if(key == 's')
  {
     Send();
     m = 1;
  }
  else if(key == 'c') println(deltaTime);
}
