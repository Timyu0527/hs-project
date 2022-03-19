int h, m;
int[] table = new int[(int)'X' + 1];
char[] RN = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
String ans;

void setup()
{
  size(600, 600);
  frameRate(60);
  table[(int)'I'] = 1;
  table[(int)'V'] = 5;
  table[(int)'X'] = 10;
  table[(int)'L'] = 50;
  table[(int)'C'] = 100;
  table[(int)'D'] = 500;
  table[(int)'M'] = 1000;
}

void draw()
{
  ans = ("");
  background(0);
  h = hour() * 100;
  m = minute();
  RNTime(h+m);
  stroke(255);
  strokeWeight(3);
  noFill();
  ellipse(width/2, height/2, 500, 500);
  textSize(60);
  textAlign(CENTER, CENTER);
  text(ans, width/2, height/2);
}

void RNTime(int c)
{
  for (int i = 6; i >= 0; i--)
  {
    if (c/table[(int)RN[i]] > 0 && c%table[(int)RN[i]] - c%(int)pow(10, floor(i/2)) != 4*pow(10, floor(i/2)))
    {
      if (floor(c/table[(int)RN[i]]) == 9 && i % 2 == 0)
      {
        ans += RN[i];
        ans += RN[i+2];
      } else if (floor(c/table[(int)RN[i]]) == 4)
      {
        ans += RN[i];
        ans += RN[i+1];
      } else
      {
        for (int j = 0; j < c/table[(int)RN[i]]; j++)
        {
          ans += RN[i];
        }
      }
      c %= table[(int)RN[i]];
    }
  }
}
