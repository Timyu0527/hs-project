void osc_Send()
{
  if(deltaTime.size() >= 2)
  {
    deltaTime.remove(0);
    deltaTime.remove(deltaTime.size()-1);
  }
  Recordkeys.add(record.size()-3);
  for(int i = 0; i < deltaTime.size(); i++)
  {
    MDtime.add(deltaTime.get(i));
  }
  for(int i = 0 ; i < pos.size(); i++)
  {
    Mpos.add(pos.get(i));
  }
  for(int i = 0; i < 13; i++)
  {
    Mplaytime.add(playtimedata[i]);
  }

  oscP5.send(Recordkeys, Netaddresslist);
  oscP5.send(Mpos, Netaddresslist);
  oscP5.send(MDtime, Netaddresslist);
  oscP5.send(Mplaytime, Netaddresslist);
  println("The data has been sent.");
}

void oscEvent(OscMessage theOscMessage)
{
  if(theOscMessage.addrPattern().equals(ConnectPattern))
  {
    connect(theOscMessage.netAddress().address());
  }
  else if(theOscMessage.addrPattern().equals(DisconnectPattern))
  {
    disconnect(theOscMessage.netAddress().address());
  }
  else
  {
    oscP5.send(theOscMessage, Netaddresslist);
  }
}

void connect(String theIPaddress)
{
   if (!Netaddresslist.contains(theIPaddress, BroadcastPort))
   {
     Netaddresslist.add(theIPaddress, BroadcastPort);
     println("### adding "+theIPaddress+" to the list.");
     c = 255;
     delay(100);
   }
   else
   {
     println("### "+theIPaddress+" is already connected.");
   }
   println("### currently there are "+Netaddresslist.list().size()+" remote locations connected.");
}

void disconnect(String theIPaddress)
{
  if (Netaddresslist.contains(theIPaddress, BroadcastPort))
  {
    Netaddresslist.remove(theIPaddress, BroadcastPort);
    println("### removing "+theIPaddress+" from the list.");
  }
  else
  {
    println("### "+theIPaddress+" is not connected.");
  }
    println("### currently there are "+Netaddresslist.list().size());
}
