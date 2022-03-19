#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

char ssid[] = "SyncPhoney";  //  your network SSID (name)
char pass[] = "16040512";       // your network password

//Your UTC Time Zone Differance  Taiwan +8:00
char HH = 8;
char MM = 00;

unsigned long t0 = 0;
unsigned long t3 = 0;
unsigned long difference0 = 0;
float difference1 = 0;
float difference2 = 0;
float difference3 = 0;

unsigned int localPort = 2390;      // local port to listen for UDP packets

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server

IPAddress timeServerIP; // time.nist.gov NTP server address

const char* ntpServerName = "0.us.pool.ntp.org";

const int NTPpacket_SIZE = 48;
byte NTPpacket[NTPpacket_SIZE]; 
bool NTPproof = false;

const int sizee_SIZE = 1;
byte sizee[sizee_SIZE];
bool sizeproof = false;

int Rhythmpacket_SIZE;
//byte Rhythmpacket[];
bool Rhythmproof = false;

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;


//=======================================================================
//     向 NTP 請求 封包
//=======================================================================
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(NTPpacket, 0, NTPpacket_SIZE);
  
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  NTPpacket[0] = 0b11100011;   // LI, Version, Mode
  NTPpacket[1] = 0;     // Stratum, or type of clock
  NTPpacket[2] = 6;     // Polling Interval
  NTPpacket[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  NTPpacket[12]  = 49;
  NTPpacket[13]  = 0x4E;
  NTPpacket[14]  = 49;
  NTPpacket[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(NTPpacket, NTPpacket_SIZE);
  udp.endPacket();
}

//=======================================================================
//     取得 NTP server 的 時間
//=======================================================================
void NTPserverTime()
{
  char hours, minutes, seconds;
  //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP); 
  
  t0 = micros();
  sendNTPpacket(timeServerIP);
  //delayMicroseconds(1);
  
  while(!NTPproof){
    delay(10);
    int cb = udp.parsePacket();
    if (!cb) {
      Serial.println("no time packet");
    }
    else {
      t3 = micros();
      difference0 = t3 - t0;
      difference1 = difference0;
 
      Serial.print("packet received, length=");
      Serial.println(cb);

      udp.read(NTPpacket, NTPpacket_SIZE);

      /*
      unsigned long t1a = word(NTPpacket[32], NTPpacket[33]);
      unsigned long t1b = word(NTPpacket[34], NTPpacket[35]);
      unsigned long t1ab = t1a << 16 | t1b;
      */

      unsigned long t1c = word(NTPpacket[36], NTPpacket[37]);
      float t1cc = t1c;
      float t1ccc = (t1cc / 65536);
      
      unsigned long t2a = word(NTPpacket[40], NTPpacket[41]);
      unsigned long t2b = word(NTPpacket[42], NTPpacket[43]);
      unsigned long t2ab = t2a << 16 | t2b;

      unsigned long t2c = word(NTPpacket[44], NTPpacket[45]);
      float t2cc = t2c;
      float t2ccc = (t2cc / 65536);

      difference2 = t2ccc - t1ccc;
      if(difference2 < 0){
        difference2 = difference2 + 1;
      }
      difference1 = ( difference1 / 1000000 );
      difference3 = (( difference2 - difference1 ) / 2 );
      Serial.print("delay:");
      Serial.println(difference3,10);
    
      Serial.print("Unix time = ");
      const unsigned long seventyYears = 2208988800UL;
      unsigned long epoch = t2ab - seventyYears;
      Serial.println(epoch);


      // print the hour, minute and second:
      minutes = ((epoch % 3600) / 60);
      minutes = minutes + MM; 
    
      hours = (epoch  % 86400L) / 3600;    
      if(minutes > 59)
      {      
       hours = hours + HH + 1; 
       minutes = minutes - 60;
      }
      else
      {
        hours = hours + HH;
     }
    
     Serial.print("The UTC time is ");
    
      Serial.print(hours,DEC);
      Serial.print(':');

      if ( minutes < 10 ) {
        Serial.print('0');
      }    
      Serial.print(minutes,DEC);
      Serial.print(':');
    
      seconds = (epoch % 60);
      unsigned long milliseconds = ( ( t2ccc + difference3 ) * 10000000000 );
      if ( seconds < 10 ) {
        Serial.print('0');
      }
      Serial.print(seconds,DEC);
      Serial.print(".");
      Serial.println(milliseconds,DEC);

      NTPproof = true;
    }
    
  }
  
}

//=======================================================================
//                   Size.U.D.P
//=======================================================================
void sizeudp()
{
  while(!sizeproof){
    delay(1000);
    int cs = udp.parsePacket();
    if (!cs){
      Serial.println("no Size packet");
    }
    else {
      udp.read(sizee, sizee_SIZE);
      Rhythmpacket_SIZE = sizee[0];
      Serial.println(Rhythmpacket_SIZE);
      
      sizeproof = true;
    }
  }
  
}
//=======================================================================
//                   Rhythm.U.D.P
//=======================================================================
void rhythmudp()
{
  int Rhythmpacket[Rhythmpacket_SIZE];
  char Temppacket[0];
  for(int i=0; i<Rhythmpacket_SIZE; i++){
      int cp = udp.parsePacket();
      if (cp) {
        udp.read(Temppacket, 1);
        //Rhythmpacket[i] = Temppacket[0].toInt();
        Serial.println(Temppacket);
      }
    }
  
  /*for(int i=1; i<Rhythmpacket_SIZE-1; i++){
    digitalWrite(2, LOW);
    delay(Rhythmpacket[i]);
    digitalWrite(2, HIGH);
    delay(Rhythmpacket[i+1]);
  }*/
}
//=======================================================================
//                     SETUP
//=======================================================================
void setup()
{
  pinMode(2, OUTPUT);
  digitalWrite(2, 0);
  
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Starting UDP");
  udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());

  delay(1000);

  sizeudp();
  delay(100);
  rhythmudp();
  delay(100);
  //NTPserverTime();
  
}

//=======================================================================
//                        LOOP
//=======================================================================
void loop()
{

}
//=======================================================================
