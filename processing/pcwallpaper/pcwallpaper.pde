void setup()
{
  size(600, 600);
}

void draw()
{
  loadPixels();
  for(int i = 0; i < width; i++)
  {
    for(int j = 0; j < height; j++)
    {
      int index = i + j * width;
      pixels[index] = color(255, 255, 255);
    }
  }
  update
}
