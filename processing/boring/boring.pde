int gridSize = 20, gridNumber = 100;
int grid;
float position = 0, move = 10;
float step = 0.002;
float noiseVal;

void setup()
{
  fullScreen(P3D);
  frameRate(60);
  //size(800, 800, P3D);
  smooth(2);
  grid = gridSize * gridNumber;
}

void draw()
{
  background(0);
  translate((width - grid)/2, gridSize*gridNumber/2, -2000);
  rotateX(PI/2.0);
  noFill();
  //lights();
  stroke(255);
  for(int j = 0; j < gridNumber; j++)
  {
    beginShape(TRIANGLE_STRIP);
    for(int i = 0; i < gridNumber; i++)
    {
      noiseVal = noise(i*gridSize*step, (position+j*gridSize)*step);
      vertex(i*gridSize, j*gridSize, map(noiseVal, 0, 1, -1000, 0));
      noiseVal = noise(i*gridSize*step, (position+(1+j)*gridSize)*step);
      vertex(i*gridSize, (1+j)*gridSize, map(noiseVal, 0, 1, -1000, 0));
    }
    endShape();
  }
  position -= move;
}
