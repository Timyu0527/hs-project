#include <ListLib.h>
#include <BigNumber.h>
#include <ArduinoOSC.h>

const char* ssid = "SyncPhoney";
const char* pwd = "16040512";

OscWiFi osc;
const char* host = "192.168.99.192";
const int recv_port = 12000;
const int send_port = 12001;

BigNumber Reference(0);
BigNumber Originate(0);
BigNumber localTime(0);
BigNumber dealTime(0);
BigNumber localdelta(0);
BigNumber serverTime(0);
BigNumber playTime(0);
BigNumber playTimeRh(0);

int LEDRpin = 5;
int LEDGpin = 4;
int LEDBpin = 0;

bool Connected = false, Synced = false;

List<int> deltaTime, LEDred, LEDgreen, LEDblue, Press;

BigNumber power(BigNumber i, BigNumber j)
{
  BigNumber r = 1;
  for(int k = 0 ; k < j; k++)
  {
    r *= i;
  }
  return r;
}

void setup()
{
  pinMode(LEDRpin, OUTPUT);
  pinMode(LEDGpin, OUTPUT);
  pinMode(LEDBpin, OUTPUT);

  analogWrite(LEDRpin, 0);
  analogWrite(LEDGpin, 0);
  analogWrite(LEDBpin, 0);
  
  BigNumber::begin(14);
  Serial.begin(115200);
  
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("WiFi connected, IP = "); 
  Serial.println(WiFi.localIP());

  osc.begin(recv_port);

  osc.subscribe("/connected", [](OscMessage& msg)
  {
    Connected = true;
    Serial.println("Connected!");
    if(!Synced)
    {
      OscMessage timeSync(host, send_port, "/time");
      osc.send(timeSync);
    }
  });

  osc.subscribe("/sync", [](OscMessage& msg)
  {
    Synced = true;
    Reference = millis();
    localdelta = ((Reference - Originate) - (BigNumber)msg.arg<int>(13))/(BigNumber)2;
    for(int i = 0; i < 13; i++)
    {
      serverTime += (BigNumber)msg.arg<int>(i)*power(10, i);
    }
    Serial.println("Synced!");
    dealTime = millis() - Reference;
    localTime = serverTime + localdelta + dealTime;
  });

  osc.subscribe("/Red", [](OscMessage& msg)
  {
    for(int i = 0; i < msg.size(); i++)
    {
      LEDred.Add(msg.arg<int>(i));
    }
    Serial.println("Red received!");
  });
  osc.subscribe("/Green", [](OscMessage& msg)
  {
    for(int i = 0; i < msg.size(); i++)
    {
      LEDgreen.Add(msg.arg<int>(i));
    }
    Serial.println("Green received!");
  });
  osc.subscribe("/Blue", [](OscMessage& msg)
  {
    for(int i = 0; i < msg.size(); i++)
    {
      LEDblue.Add(msg.arg<int>(i));
    }
    Serial.println("Blue received!");
  });

  osc.subscribe("/Press", [](OscMessage& msg)
  {
    for(int i = 0; i < msg.size(); i++)
    {
      Press.Add(msg.arg<int>(i));
    }
    Serial.println("Press received!");
  });

  osc.subscribe("/time", [](OscMessage& msg)
  {
    playTime = localTime + (BigNumber)msg.arg<int>(msg.size()-1);
    playTimeRh = playTime;
    for(int i = 0; i < msg.size(); i++)
    {
      deltaTime.Add(msg.arg<int>(i));
    }
    Serial.println("Data received!");
  });
}

void loop()
{
  int index = 0;
  
  osc.parse();
  dealTime = millis() - Reference;
  localTime = serverTime + localdelta + dealTime;  
  if(!Connected)
  {
    OscMessage serverConnect(host, send_port, "/server/connect");
    osc.send(serverConnect);
  }
  if(playTime <= localTime && playTime != 0)
  {
    for(int i = 0; i < Press.Count(); i++)
    {
      if(i < Press.Count()-1)
      {
        if(Press[i])
        {
          analogWrite(LEDRpin, LEDred[index]);
          analogWrite(LEDGpin, LEDgreen[index]);
          analogWrite(LEDBpin, LEDblue[index]);
          while(playTimeRh <= localTime && localTime <= playTimeRh + (BigNumber)deltaTime[i])
          {
            dealTime = millis() - Reference;
            localTime = serverTime + localdelta + dealTime;
            delay(0);
          }
          index++;
        }
        else
        {
          analogWrite(LEDRpin, 0);
          analogWrite(LEDGpin, 0);
          analogWrite(LEDBpin, 0);
          while(playTimeRh <= localTime && localTime <= playTimeRh + (BigNumber)deltaTime[i])
          {
            dealTime = millis() - Reference;
            localTime = serverTime + localdelta + dealTime;
            delay(0);
          }
        }
        playTimeRh += (BigNumber)deltaTime[i];
      }
    }
   }
}
