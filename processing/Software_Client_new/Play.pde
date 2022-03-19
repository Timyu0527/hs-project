void display()
{
  NTPtime = System.currentTimeMillis() + localdelta;
  noStroke();
  fill(255);
  if(m >= recordkeys) music.stop();
  if(NTPtime >= playtime)
  {
    music.play();
  }
  if(m >= 1 && m%2 == 1 && NTPtime < playtime + (long)deltaTime.get(m) && NTPtime >= playtime)
  {
    rect(pos.get(m/2)*width/keys, 0, width/keys, height);
  }
  if(NTPtime > playtime + (long)deltaTime.get(m))
  {
    playtime += (long)deltaTime.get(m);
    m++;
  }
 }
 
 long power(long i, int j)
{
  long r = 1;
  for(int k = 0; k < j; k++)
  {
    r *= i;
  }
  return r;
}
