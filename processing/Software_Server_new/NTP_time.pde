void timeSetup()
{
  udp = new UDP(this, 8888);
  udp.listen(true);
 
  for(int i = 0; i < 48; i++) packetBuff[i] = 0; // fill packetBuff with 0's 
 
  packetBuff[0] = byte(227);   // LI, Version, Mode
  packetBuff[1] = 0;           // Stratum, or type of clock
  packetBuff[2] = 6;           // Polling Interval
  packetBuff[3] = byte(236);   // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuff[12] = 49;
  packetBuff[13] = 78;
  packetBuff[14] = 49;
  packetBuff[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
}

void NTP_send()
{
  udp.send(packetBuff, NTPserver, NTPport); 
  Originate = System.currentTimeMillis(); 
}

void receive(byte[] data)
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
  
  Receive = (long)(timestamp[0] * 1000);
  Transmit = (long)(timestamp[1] * 1000);
  NTPdelta = ((Reference - Originate) - (Transmit - Receive))/2;
  localdelta = Transmit + NTPdelta - Reference;
  NTPtime = System.currentTimeMillis() + localdelta;
  playtime = NTPtime + delaytime;
  
  for(int i = 0; i < 13; i++)
  {
    playtimedata[i] = (int)((playtime % power(10, i+1) - playtime % power(10, i)) / power(10, i));
  }
  
  osc_Send();
}
