void Send()
{
  OscMessage MDtime = new OscMessage("/time");
  OscMessage Press = new OscMessage("/Press");
  OscMessage Red = new OscMessage("/Red");
  OscMessage Green = new OscMessage("/Green");
  OscMessage Blue = new OscMessage("/Blue");
  
  for(int i = 0; i < press.size(); i++)
  {
    Press.add(press.get(i));
  }
  for(int i = 0; i < LEDred.size(); i++)
  {
    Red.add(LEDred.get(i));
    Green.add(LEDgreen.get(i));
    Blue.add(LEDblue.get(i));
  }
  for(int i = 0; i < deltaTime.size(); i++)
  {
    MDtime.add(deltaTime.get(i));
  }
  MDtime.add(playtime);
  
  oscP5.send(Red, Netaddresslist);
  oscP5.send(Green, Netaddresslist);
  oscP5.send(Blue, Netaddresslist);
  oscP5.send(Press, Netaddresslist);
  oscP5.send(MDtime, Netaddresslist);
}

void oscEvent(OscMessage theOscMessage)
{
  if(theOscMessage.addrPattern().equals(ConnectPattern))
  {
    connect(theOscMessage.netAddress().address());
    OscMessage connected = new OscMessage("/connected");
    oscP5.send(connected, Netaddresslist);
  }
  
  if(theOscMessage.addrPattern().equals("/time"))
  {
    long Transmit, Receive = System.currentTimeMillis();
    int dealtime;
    OscMessage sync = new OscMessage("/sync");
    for(int i = 0; i < 13; i++)
    {
      sync.add((int)((Receive % power(10, i+1) - Receive % power(10, i)) / power(10, i)));
    }
    Transmit = System.currentTimeMillis();
    dealtime = (int)(Transmit - Receive);
    sync.add(dealtime);
    oscP5.send(sync, Netaddresslist);
    println("serverTime:" + Transmit);
  }
}

void connect(String theIPaddress)
{
   if (!Netaddresslist.contains(theIPaddress, BroadcastPort))
   {
     Netaddresslist.add(new NetAddress(theIPaddress, BroadcastPort));
     println("### adding "+theIPaddress+" to the list.");
   }
   else
   {
     println("### "+theIPaddress+" is already connected.");
   }
   println("### currently there are "+Netaddresslist.list().size()+" remote locations connected.");
}
