import cassette.audiofiles.*;
import hypermedia.net.*;

SoundFile music;

UDP udp;

int NTPport = 123;

String NTPserver = "pool.ntp.org";

int m = 0, k = 0, c = 0, buttonColor = 255;
int R = 255, M = 255, L = 255, keys = 5;
int[] keybroad = new int[keys+1];
byte[] DeltaTime, Pos;
IntList record, deltaTime, pos; 

long playtime, NTPtime, delaytime = 10000;
long Receive, Transmit, Originate, Reference;
long NTPdelta, localdelta;
int[] timedata = new int[32];
int[] playtimedata = new int[13];
double[] timestamp = new double[2];
byte[] packetBuff = new byte[48];

void setup()
{
  size(500, 400);
  
  record = new IntList();
  deltaTime = new IntList();
  pos = new IntList();
  
  udp = new UDP(this, 8888);
  udp.listen(true);
  
  music = new SoundFile(this, "Alan Walker - Alone.mp3");
  
  timeSetup();
  Set();
}

void draw()
{
  background(c);
  c = 0;
  display();
}
