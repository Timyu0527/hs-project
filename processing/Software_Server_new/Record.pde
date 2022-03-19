void mousePressed()
{
  if(m == 0)
  {
    record.append(millis());
    if(k != 0)deltaTime.append(record.get(k) - record.get(k-1));
    k++;
  }
  if(mouseX >= width/3 * 2 && mouseX <= width && mouseY > height - height/6)
  { 
    NTP_send();
    music.stop();
    m = 1;
    L = 200;
  }
  else if(mouseX >= 0 && mouseX <= width/3 && mouseY > height - height/6) 
  {
    OscMessage stop = new OscMessage("/stop");
    oscP5.send(stop, Netaddresslist);
    record.clear();
    pos.clear();
    deltaTime.clear();
    k = 0;
    m = 0;
    R = 200;
  }
}

void mouseReleased()
{
  if(m == 0)
  {
    record.append(millis());
    deltaTime.append(record.get(k) - record.get(k-1));
    k++;
  }
  loop();
}

void Set()
{
  for(int i = 0; i < keys+1; i++)
  {
    keybroad[i] = width / keys * i;
  }
}

void display()
{
  noStroke();
  if(mousePressed && m == 0)
  { 
    if(mouseX >= width/3 && mouseX <= width/3 * 2&& mouseY > height - height/6) 
    {
      music.play();
      M = 200;
    }
    for(int i = 0; i < keys; i++)
    {
      if(mouseX < keybroad[i+1] && mouseX >= keybroad[i] && mouseY <= height - height/5)
      {
        fill(255);
        rect(keybroad[i], 0, width/keys, height - height/6);
        pos.append((int)(keybroad[i] / (float)(width / keys)));
        noLoop();
      }
    }
  }
  else
  {
    R = bottonColor;
    M = bottonColor;
    L = bottonColor;
  }
  fill(bottonColor, 0, 0, R);
  rect(0, height - height/6, width/3, height/6+100);
  
  fill(0, bottonColor, 0, M);
  rect(width/3, height - height/6, width/3, height/6);
  
  fill(0, 0, bottonColor, L);
  rect(width/3 * 2, height - height/6, width/3, height/6);
}

long power(long i, int j)
{
  long r = 1;
  for(int k = 0 ; k < j; k++)
  {
    r *= i;
  }
  return r;
}
