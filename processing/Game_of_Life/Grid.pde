class Cell
{
  int size, around = 0;
  boolean isCell = false;
  PVector initPosition;
  
  Cell(int iSize, PVector iInitPosition)
  {
    size = iSize;
    initPosition = iInitPosition; //<>//
  }
  
  void pressed()
  {
    isCell = true;
  }
  
  void display()
  {
    if(isCell)
    {
      //fill(random(0, 255), random(0, 255), random(0, 255));
      fill(0);
    }
    else
    {
      fill(255);
    }
    rect(initPosition.x, initPosition.y, size, size);
  }
}
