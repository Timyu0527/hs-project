import cassette.audiofiles.*;
import hypermedia.net.*;
import ketai.ui.*;
import oscP5.*;
import netP5.*;

SoundFile music;

UDP udp;

OscP5 oscP5;
NetAddress BroadcastLocation; 

int BroadcasrPort = 12001;
int ListeningPort = 12000;
int NTPport = 123; 

String NTPserver = "pool.ntp.org";
String Sposition = "/position";
String Stime = "/time";
String Splaytime = "/playtime";
String Stop = "/stop";
String Srecordkeys = "/recordkeys";

int recordkeys, keys = 5, m = 0, c = 0;
IntList pos, deltaTime;


long NTPdelta, playtime = 0;
long receive, transmit, Originate, Reference;
long localdelta, NTPtime;
int[] timedata = new int[32];
double[] timestamp = new double[2];
byte[] packetBuff = new byte[48];
int[] playtimedata = new int[13];

boolean temple = false, late = false;

void setup()
{
  fullScreen();
  orientation(LANDSCAPE);
  
  oscP5 = new OscP5(this,ListeningPort);
  
  music = new SoundFile(this, "Alan Walker - Alone.mp3");
  
  BroadcastLocation = new NetAddress("172.20.10.3", BroadcasrPort);
  
  timeSetup();
}


void draw()
{
  background(c);
  c = 0;
  NTPtime = System.currentTimeMillis() + localdelta;
  if(late && playtime - NTPtime <= 0) late = false;
  else if(temple && !late) display();
}
