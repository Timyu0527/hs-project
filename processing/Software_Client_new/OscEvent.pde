void keyPressed()
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

void mousePressed()
{ 
  KetaiKeyboard.toggle(this);
}

void oscEvent(OscMessage theOscMessage)
{
  if(theOscMessage.addrPattern().equals(Srecordkeys))
  {
    recordkeys = theOscMessage.get(0).intValue();
    pos = new IntList();
    deltaTime = new IntList();
  }
  if(theOscMessage.addrPattern().equals(Stop))
  {
    temple = false;
    deltaTime.clear();
    pos.clear();
  }
  if(theOscMessage.addrPattern().equals(Stime))
  {
    for(int i = 0; i < recordkeys; i++)
    {
      deltaTime.append(theOscMessage.get(i).intValue());
    }
  }
  if(theOscMessage.addrPattern().equals(Sposition))
  {
    for(int i = 0; i < recordkeys/2; i++)
    {
      pos.append(theOscMessage.get(i).intValue());
    }
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
  if(deltaTime.size() == recordkeys && pos.size() == recordkeys/2 && playtime != 0) 
  {
    NTP_send();
    temple = true;
    late = true;
    c = 255;
    println("The data has been received.");
    delay(100);
  } 
}
