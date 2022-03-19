int gridSize = 100, gridNumber = 50;
int grid;
int[][] clr = new int[gridNumber+5][gridNumber+5];
float noiseVal, randomVal;

void setup()
{
  size(800, 800, P3D);
  smooth(2);
  grid = gridSize * gridNumber;
  for(int j = -5; j < gridNumber; j++)
  {
    for(int i = -5; i < gridNumber; i++)
    {
      clr[i+5][j+5] = (int)random(0, 63);
    }
  }
}

void draw()
{
  background(0);
  rotateX(PI/10.0);
  noStroke();
  for(int j = -5; j < gridNumber; j++)
  {
    for(int i = -5; i < gridNumber; i++)
    {
      fill(clr[i+5][j+5]);
      beginShape(TRIANGLE);
      noiseVal = noise(i*gridSize, (j*gridSize));
      vertex(i*gridSize, j*gridSize, map(noiseVal, 0, 1, -200, 200));
      noiseVal = noise(i*gridSize, ((1+j)*gridSize));
      vertex(i*gridSize, (1+j)*gridSize, map(noiseVal, 0, 1, -200, 200));
      noiseVal = noise((i+1)*gridSize, ((1+j)*gridSize));
      vertex((i+1)*gridSize, (1+j)*gridSize, map(noiseVal, 0, 1, -200, 200));
      endShape();
      beginShape(TRIANGLE);
      noiseVal = noise(i*gridSize, (j*gridSize));
      vertex(i*gridSize, j*gridSize, map(noiseVal, 0, 1, -200, 200));
      noiseVal = noise((i+1)*gridSize, (j*gridSize));
      vertex((i+1)*gridSize, j*gridSize, map(noiseVal, 0, 1, -200, 200));
      noiseVal = noise((i+1)*gridSize, ((1+j)*gridSize));
      vertex((i+1)*gridSize, (1+j)*gridSize, map(noiseVal, 0, 1, -200, 200));
      endShape();
    }
  }
}
