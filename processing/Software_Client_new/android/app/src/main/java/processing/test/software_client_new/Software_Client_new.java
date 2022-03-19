package processing.test.software_client_new;

import processing.core.*; 
import processing.data.*; 
import processing.event.*; 
import processing.opengl.*; 

import cassette.audiofiles.*; 
import hypermedia.net.*; 
import ketai.ui.*; 
import oscP5.*; 
import netP5.*; 

import java.util.HashMap; 
import java.util.ArrayList; 
import java.io.File; 
import java.io.BufferedReader; 
import java.io.PrintWriter; 
import java.io.InputStream; 
import java.io.OutputStream; 
import java.io.IOException; 

public class Software_Client_new extends PApplet {







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

int recordkeys, keys = 5, m = 0, c = 255;
IntList pos, deltaTime;


long NTPdelta, playtime = 0;
long receive, transmit, Originate, Reference;
long localdelta, NTPtime;
int[] timedata = new int[32];
double[] timestamp = new double[2];
byte[] packetBuff = new byte[48];
int[] playtimedata = new int[13];

boolean temple = false, late = false;

public void setup()
{
  
  orientation(LANDSCAPE);
  
  oscP5 = new OscP5(this,ListeningPort);
  
  music = new SoundFile(this, "Alan Walker - Alone.mp3");
  
  BroadcastLocation = new NetAddress("172.20.10.3", BroadcasrPort);
  
  timeSetup();
}


public void draw()
{
  background(c);
  c = 255;
  NTPtime = System.currentTimeMillis() + localdelta;
  if(late && playtime - NTPtime <= 0) late = false;
  else if(temple && !late) display();
}
public void timeSetup()
{
  udp = new UDP(this, 8888);
  udp.listen(true);
 
  for(int i = 0; i < 48; i++) packetBuff[i] = 0; // fill packetBuff with 0's 
 
  packetBuff[0] = PApplet.parseByte(227);   // LI, Version, Mode
  packetBuff[1] = 0;           // Stratum, or type of clock
  packetBuff[2] = 6;           // Polling Interval
  packetBuff[3] = PApplet.parseByte(236);   // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuff[12] = 49;
  packetBuff[13] = 78;
  packetBuff[14] = 49;
  packetBuff[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
}

public void NTP_send()
{
  udp.send(packetBuff, NTPserver, NTPport); 
  Originate = System.currentTimeMillis(); 
}

public void receive(byte[] data)  // <-- default handler
{
  Reference = System.currentTimeMillis(); 
  timestamp[0] = 0;
  timestamp[1] = 0;
  println("The NTP time has been received.");
  
  
  for(int i = 32; i < 48; i++)
  {
     timedata[i-32] = unbinary(binary(data[i]));
  }
  
  for(int i = 0; i < 2; i++)
  {
    for(int j = 0; j < 6; j++)
    {
      timestamp[i] += (double)timedata[8*i+j] * (double)pow(2, 8*(3-j));
    }
  }
  
  for(int j = 0; j < 2; j++)
  {
    timestamp[j] -= 28800; 
    for(int i = 0; i < 2; i++)
    {
      timestamp[j] -= 1104480000;
    }
  }
  
  receive = (long)(timestamp[0] * 1000);
  transmit = (long)(timestamp[1] * 1000);
  NTPdelta = ((Reference - Originate) - (transmit - receive))/2;
  localdelta = transmit + NTPdelta - Reference;
  NTPtime = System.currentTimeMillis() + localdelta;
}
public void keyPressed()
{
  switch(key)
  {
    case 'c':
      OscMessage conMes = new OscMessage("/server/connect");
      oscP5.send(conMes, BroadcastLocation);
      break;
    case 'd':
      OscMessage discMes = new OscMessage("/server/disconnect");
      oscP5.send(discMes, BroadcastLocation);
      break;
    case 's':
       temple = false;
       deltaTime.clear();
       pos.clear();
       music.stop();
       break;
  }
}

public void mousePressed()
{ 
  KetaiKeyboard.toggle(this);
}

public void oscEvent(OscMessage theOscMessage)
{
  if(theOscMessage.addrPattern().equals(Srecordkeys))
  {
    recordkeys = theOscMessage.get(0).intValue();
    pos = new IntList();
    deltaTime = new IntList();
    c = 0; 
  }
  if(theOscMessage.addrPattern().equals(Stop))
  {
    temple = false;
    deltaTime.clear();
    pos.clear();
    c = 0;
  }
  if(theOscMessage.addrPattern().equals(Stime))
  {
    for(int i = 0; i < recordkeys-1; i++)
    {
      deltaTime.append(theOscMessage.get(i).intValue());
    }
    println(deltaTime);
  }
  if(theOscMessage.addrPattern().equals(Sposition))
  {
    for(int i = 0; i < recordkeys/2; i++)
    {
      pos.append(theOscMessage.get(i).intValue());
    }
    println(pos);
  }
  if(theOscMessage.addrPattern().equals(Splaytime)) 
  {
    for(int i = 0 ; i < 13; i++)
    {
      playtimedata[i] = theOscMessage.get(i).intValue();
    }
    for(int i = 0; i < 13; i++)
    {
      playtime = playtime + (long)playtimedata[i] * power(10, i); 
    }
  }
  if(deltaTime.size() == recordkeys-1 && pos.size() == recordkeys/2 && playtime != 0) 
  {
    NTP_send();
    temple = true;
    late = true;
    c = 0;
    println("The data has been received.");
    delay(100);
  } 
}
public void display()
{
  int n;
  NTPtime = System.currentTimeMillis() + localdelta;
  noStroke();
  fill(0);
  if(m >= recordkeys)
  {
    playtime += 2000;
    m = 0;
  }
  if(m == 0) n = 1;
  else n = 0;
  if(NTPtime >= playtime && m >= 2)
  {
    music.play();
  }
  if(m >= 2 && m%2 == 0 && NTPtime < playtime + (long)deltaTime.get(m) && NTPtime >= playtime)
  {
    rect(pos.get(m/2)*width/keys, 0, width/keys, height);
  }
  if(NTPtime > playtime + (long)deltaTime.get(m))
  {
    playtime += (long)deltaTime.get(m);
    println(m);
    m++;
  }
 }
 
 public long power(long i, int j)
{
  long r = 1;
  for(int k = 0; k < j; k++)
  {
    r *= i;
  }
  return r;
}
  public void settings() {  fullScreen(); }
}
