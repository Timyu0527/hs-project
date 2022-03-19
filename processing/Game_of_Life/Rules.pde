void normalRule()
{
  int dead = 4, respawn = 3, stable = 2;
  for(int i = 1; i < cells.size()-1; i++)
  {
    for(int j = 1; j < cells.get(i).size()-1; j++)
    {
      for(int h = -1; h <= 1; h++)
      {
        for(int k = -1; k <= 1; k++)
        {
          if((h != 0 || k != 0) && cells.get(i+h).get(j+k).isCell)
          {
            cells.get(i).get(j).around++;
          }
        }
      }
    }
  }  
  
  for(int i = 1; i < cells.size()-1; i++)
  {
    for(int j = 1; j < cells.get(i).size()-1; j++)
    {
      if(cells.get(i).get(j).around >= dead && cells.get(i).get(j).isCell) cells.get(i).get(j).isCell = false;
      else if(cells.get(i).get(j).around == respawn && !cells.get(i).get(j).isCell) cells.get(i).get(j).isCell = true;
      else if(cells.get(i).get(j).around < stable && cells.get(i).get(j).isCell) cells.get(i).get(j).isCell = false;
    }
  }
}

void factorialCupRule()
{
  int dead = 3, respawn = 2;
  for(int i = 1; i < cells.size()-1; i++)
  {
    for(int j = 1; j < cells.get(i).size()-1; j++)
    {
      for(int h = -1; h <= 1; h++)
      {
        for(int k = -1; k <= 1; k++)
        {
          if((h == 0 || k == 0) && cells.get(i+h).get(j+k).isCell)
          {
            cells.get(i).get(j).around++;
          }
        }
      }
      if(cells.get(i).get(j).isCell) cells.get(i).get(j).around--;
    }
  }
  for(int i = 1; i < cells.size()-1; i++)
  {
    for(int j = 1; j < cells.get(i).size()-1; j++)
    {
      if((cells.get(i).get(j).around >= dead) && cells.get(i).get(j).isCell) cells.get(i).get(j).isCell = false;
      if(cells.get(i).get(j).around <= respawn && cells.get(i).get(j).around != 0 && !cells.get(i).get(j).isCell) cells.get(i).get(j).isCell = true;
    }
  }
}
