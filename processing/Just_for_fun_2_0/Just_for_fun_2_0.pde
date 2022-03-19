int block_size = 50, map_size = 10, block_position;
int[][] map = new int[map_size][map_size];

void setup()
{
  size(800, 800, P3D);
  for(int i = 0 ;i < map_size; i++)
  {
    for(int j = 0; j < map_size; j++)
    {
      map[i][j] = block_size*(int)random(0, 10);
    }
  }
}

void draw()
{
  background(0);
  translate(width/4, height/1.5, 0);
  rotateX(-PI/2);
  //rotateY(PI/2);
  for(int i = 0; i < block_size * map_size; i += block_size)
  {
    for(int j = 0; j < block_size * map_size; j += block_size)
    {
      translate(block_size, 0, 50);
      fill(255);
      box(block_size);
    }
    translate(-map_size*block_size, block_size, -500);
  }
}
