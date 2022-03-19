class Player
{
  int timeOfDeath = 0;
  PVector position;
  Player(PVector iPosition)
  {
    position = iPosition;
  }
  
  void move()
  {
    if(keyPress[0])
    {
      if(position.y >= 0)
      {
        playerVelocity[0].y -= playerAcceleration;
        position.add(playerVelocity[0]);
      }
      else
      {
        playerVelocity[0].y = 0;
      }
    }
    else if(playerVelocity[0].y < 0)
    {
      if(position.y >= 0)
      {
        playerVelocity[0].y += playerAcceleration;
        position.add(playerVelocity[0]);
      }
      else
      {
        playerVelocity[0].y = 0;
      }
    }
    
    if(keyPress[1])
    {
      if(position.y  + playerSize <= height)
      {
        playerVelocity[1].y += playerAcceleration;
        position.add(playerVelocity[1]);
      }
      else
      {
        playerVelocity[1].y = 0;
      }
    }
    else if(playerVelocity[1].y > 0)
    {
      if(position.y  + playerSize <= height)
      {
        playerVelocity[1].y -= playerAcceleration;
        position.add(playerVelocity[1]);
      }
      else
      {
        playerVelocity[1].y = 0;
      }
    }
    
    if(keyPress[2])
    {
      if(position.x >= 0)
      {
        playerVelocity[2].x -= playerAcceleration;
        position.add(playerVelocity[2]);
      }
      else
      {
        playerVelocity[2].x = 0;
      }
    }
    else if(playerVelocity[2].x < 0)
    {
      if(position.x >= 0) 
      {
        playerVelocity[2].x += playerAcceleration;
        position.add(playerVelocity[2]);
      }
      else
      {
        playerVelocity[2].x = 0;
      }
    }
    
    if(keyPress[3])
    {
      if(position.x + playerSize<= width)
      {
        playerVelocity[3].x += playerAcceleration;
        position.add(playerVelocity[3]);
      }
      else
      {
        playerVelocity[3].x = 0;
      }
    }
    else if(playerVelocity[3].x > 0)
    {
      if(position.x + playerSize <= width)
      {
        playerVelocity[3].x -= playerAcceleration;
        position.add(playerVelocity[3]);
      }
      else
      {
        playerVelocity[3].x = 0;
      }
    }
  }
  
  void display()
  {
    fill(255);
    rect(position.x, position.y, playerSize, playerSize);
  }
}

class Bullet
{
  PVector position, velocity;
  Bullet(PVector iPosition, PVector iVelocity)
  {
    position = iPosition;
    velocity = iVelocity;
  }
  
  void move()
  {
    position.sub(velocity);
  }
  
  void display()
  {
    fill(255);
    rect(position.x, position.y, bulletSize, bulletSize);
  }
}

class Enemy
{
  int shotTime = 2*bulletsDelay, lifeTime = 0, timeOfDeath = 0;
  boolean dead = false;
  PVector position, velocity;
  
  Enemy(PVector iPosition, PVector iVelocity)
  {
    position = iPosition;
    velocity = iVelocity;
  }
  
  void move()
  {
    if(0 >= position.x || position.x+playerSize >= width)
    {
      velocity.x *= -1;
    }
    position.add(velocity);
  }
  
  void display()
  {
    fill(127);
    rect(position.x, position.y, playerSize, playerSize);
  }
}

class Effect
{
  int Color;
  PVector acceleration;
  PVector position, velocity;
  float particalesSize = random(1, playerSize);
  
  Effect(PVector initPosition, int iColor)
  {
    position = initPosition;
    velocity = new PVector(random(-2, 2), random(-2, 2));
    Color = iColor;
    //acceleration = new PVector(random(0, velocity.x), random(0, velocity.y));
  }
  
  void move()
  {
    if(velocity.x != 0 && velocity.y != 0)
    {
      //velocity.sub(acceleration);
      position.add(velocity);
    }
  }
  
  void display()
  {
    fill(Color -= 3);
    rect(position.x, position.y, (int)particalesSize, (int)particalesSize);
  }
}
