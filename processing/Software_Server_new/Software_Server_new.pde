import cassette.audiofiles.*; //<>//
import hypermedia.net.*;
import oscP5.*;
import netP5.*;

SoundFile music;

UDP udp;

OscP5 oscP5;
NetAddressList Netaddresslist = new NetAddressList();

OscMessage Mpos = new OscMessage("/position");
OscMessage MDtime = new OscMessage("/time");
OscMessage Mplaytime = new OscMessage("/playtime");
OscMessage Recordkeys = new OscMessage("/recordkeys");

int ListeningPort = 12001;
int BroadcastPort = 12000;
int NTPport = 123;

String ConnectPattern = "/server/connect";
String DisconnectPattern = "/server/disconnect";
String NTPserver = "pool.ntp.org";

int m = 0, k = 0, c = 0, bottonColor = 255;
int R = 255, M = 255, L = 255, keys = 5;
int[] keybroad = new int[keys+1];
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
  fullScreen();
  orientation(LANDSCAPE);
  
  record = new IntList();
  deltaTime = new IntList();
  pos = new IntList();
  
  oscP5 = new OscP5(this, ListeningPort);
  
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
