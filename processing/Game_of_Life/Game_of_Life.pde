int cellSize = 20;
boolean play = false;
PVector initPressPosition;
ArrayList<ArrayList<Cell>> cells = new ArrayList<ArrayList<Cell>>();

void setup()
{
  //fullScreen();
  size(600, 600);
  frameRate(30);
  for(int i = -1; i < height/cellSize+1; i++)
  {
    cells.add(new ArrayList<Cell>());
    for(int j = -1; j < width/cellSize+1; j++)
    {
      cells.get(i+1).add(new Cell(cellSize, new PVector(j*cellSize, i*cellSize)));
    }
  }
}

void draw()
{
  background(0);
  if(play)
  {
    for(int i = 1; i < cells.size(); i++)
    {
      for(int j = 1; j < cells.get(i).size(); j++)
      {
        cells.get(i).get(j).around = 0; 
      }
    }
    normalRule();
    //factorialCupRule();
  }
  
  for(int i = 0; i < cells.size(); i++)
  {
    for(int j = 0; j < cells.get(i).size(); j++)
    {
      cells.get(i).get(j).display();
    }
  }
}

void keyPressed()
{
  play = (play) ? false : true;
}

void mousePressed()
{
  if(!play)
  {
    for(int i = 1; i < cells.size()-1; i++)
    {
      for(int j = 1; j < cells.get(i).size()-1; j++)
      {
        if(buttonPressed(cells.get(i).get(j).initPosition))
        {
          cells.get(i).get(j).isCell = (cells.get(i).get(j).isCell) ? false : true;
          initPressPosition = new PVector(j, i);
          
        }
      }
    }
  }
}

void mouseDragged()
{
  if(mousePressed)
  {
    for(int i = 1; i < cells.size()-1; i++)
    {
      for(int j = 1; j < cells.get(i).size()-1; j++)
      {
        if(buttonPressed(cells.get(i).get(j).initPosition) && cells.get((int)initPressPosition.y).get((int)initPressPosition.x).isCell)
        {
          cells.get(i).get(j).isCell = (!cells.get(i).get(j).isCell) ? true : true;
        }
        else if(buttonPressed(cells.get(i).get(j).initPosition) && !cells.get((int)initPressPosition.y).get((int)initPressPosition.x).isCell)
        {
          cells.get(i).get(j).isCell = (cells.get(i).get(j).isCell) ? false : false;
        }
      }
    }
  }
}

boolean buttonPressed(PVector position)
{
  if(mouseX > position.x && mouseY > position.y && mouseX < position.x + cellSize && mouseY < position.y + cellSize)
  {
    return true;
  }
  else 
  {
    return false;
  }
}
