void mousePressed()
{
  if(m == 0)
  {
    record.append(millis());
    if(k != 0) deltaTime.append(record.get(k) - record.get(k-1));
    press.append(1);
    k++;
  }
}

void mouseReleased()
{
  if(m == 0)
  {
    record.append(millis());
    deltaTime.append(record.get(k) - record.get(k-1));
    press.append(0);
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
  if(m == 0)
  { 
    for(int i = 0; i < keys; i++)
    {
      if(mouseX < keybroad[i+1] && mouseX >= keybroad[i] && mouseY <= height && mousePressed)
      {
        int R = int(random(0, 255)), G = int(random(0, 255)), B = int(random(0, 255));
        fill(R, G, B);
        rect(keybroad[i], 0, width/keys, height);
        noLoop();
        LEDred.append((int)map(R, 0, 255, 0, 1023));
        LEDgreen.append((int)map(G, 0, 255, 0, 1023));
        LEDblue.append((int)map(B, 0, 255, 0, 1023));
      }
    }
  }
}
long power(int i, int j)
{
  long r = 1;
  for(int k = 0 ; k < j; k++)
  {
    r *= i;
  }
  return r;
}
