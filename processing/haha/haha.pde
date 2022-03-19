int particalesNumber, bulletsDelayFix;
int bulletsDelay = 10, playerSize = 30, bulletSize = 5, particalesColor = 180;
int currentTime = 0, enemyRespawnTime = 30, explosionTime = 60;
float playerAcceleration = 1.0, particalesDisplayTime = 10.0;
boolean fire = false, firstShot = true, GG = false;
boolean[] keyPress = new boolean[4];
PVector playerInitPosition, bulletVelocity, enemyVelocity, enemyPosition, particalesVelocity;
PVector[] playerVelocity = new PVector[4];
ArrayList<Enemy> enemies = new ArrayList<Enemy>();
ArrayList<Bullet> bullets = new ArrayList<Bullet>();
ArrayList<ArrayList<Effect>> particales = new ArrayList<ArrayList<Effect>>();
Player player;

void setup()
{
  size(660, 660);
  frameRate(30);
  for(int i = 0; i < 4; i++)
  {
    keyPress[i] = false;
    playerVelocity[i] = new PVector(0, 0);
  }
  bulletVelocity = new PVector(0, 20);
  playerInitPosition = new PVector(height/2, width - playerSize);
  player = new Player(playerInitPosition);
  particales.add(new ArrayList<Effect>());
}

void draw()
{
  background(0);
  noStroke();
  fill(255);
  textSize(20);
  textAlign(LEFT, TOP);
  text(millis()/1000, 0, 0);
  //Player display
  if(!GG)
  {
    player.move();
    player.display();
    if(fire)
    {
      if(currentTime % bulletsDelay == 0)
      {
        bullets.add(new Bullet(new PVector(player.position.x+playerSize/2, player.position.y), bulletVelocity));
      }
    }
    if(keyPressed && key == 'l' && firstShot)
    {
      bullets.add(new Bullet(new PVector(player.position.x+playerSize/2, player.position.y), bulletVelocity));
      firstShot = false;
    }
  }
  
  //Enemies respawn
  if(currentTime % enemyRespawnTime == 0)
  {
    enemyPosition = new PVector(random(0, width - playerSize), -playerSize);
    enemyVelocity = new PVector(random(-20, 20), random(-10, 10));
    enemies.add(new Enemy(new PVector(enemyPosition.x, enemyPosition.y), new PVector(enemyVelocity.x, enemyVelocity.y)));
    particales.add(new ArrayList<Effect>());
    currentTime = 0;
  }
  currentTime++;
  
  //Enemies display
  if(enemies.size() != 0)
  {
    for(int i = 0; i < enemies.size(); i++)
    {
      enemies.get(i).move();
      enemies.get(i).display();
    }
  }
  if(enemies.size() != 0 && enemies.get(0).position.y >= height)
  {
        enemies.remove(0);
  }
  
  //Bullets display
  for(int i = 0; i < bullets.size(); i++)
  {
    bullets.get(i).move();
    if(bullets.get(0).position.y <= 0)
    {
      bullets.remove(0);
    }
  }
  for(int i = 0; i < bullets.size(); i++)
  {
    bullets.get(i).display();
  }
  
  //Enemies dead
  if(enemies.size() != 0 && bullets.size() != 0)
  {
    for(int i = 0; i < enemies.size() && enemies.size() != 0; i++)
    {
      if(enemies.get(i).dead)
      {
        if(enemies.get(i).timeOfDeath >= particalesDisplayTime)
        {
          enemies.remove(i);
          particales.remove(i+1);
        }
        else
        {
          for(int j = 0; j < particales.get(i+1).size(); j++)
          {
            particales.get(i+1).get(j).move();
            particales.get(i+1).get(j).display();
          }
          enemies.get(i).timeOfDeath++;
        }
      }
      else
      {
        for(int j = 0; j < bullets.size() && bullets.size() != 0; j++)
        {
          if(enemies.size() != 0 && bullets.size() != 0 && enemyDead(bullets.get(j).position, enemies.get(i).position))
          {
            bullets.remove(j);
            enemies.get(i).dead = true;
            for(int k = 0; k < particalesNumber; k++)
            {
              particales.get(i+1).add(new Effect(new PVector(enemies.get(i).position.x, enemies.get(i).position.y), particalesColor));
            }
            if(i == enemies.size() && i != 0) i--;
          }
        } 
      }
    }
  }
  
  //Player dead
  for(int i = 0; i < enemies.size(); i++)
  {
    if(playerDead(player.position, enemies.get(i).position))
    {
      GG = true;
      fire = false;
      particalesNumber = (int)random(10, 20);
      for(int j = 0; j < particalesNumber; j++)
      {
        particales.get(0).add(new Effect(new PVector(player.position.x, player.position.y), particalesColor));
      }
    }
  }
  if(GG && player.timeOfDeath != explosionTime)
  {
    for(int i = 0; i < particalesNumber; i++)
    {
      for(int j = 0; j < particales.get(0).size(); j++)
      {
        particales.get(0).get(j).move();
        particales.get(0).get(j).display();
      }
    }
    player.position = new PVector(-100, -100);
    player.timeOfDeath++;
  }
  else if(player.timeOfDeath == explosionTime)
  {
    particales.remove(0);
    player.timeOfDeath++;
  }
}

boolean enemyDead(PVector bulletsPosition, PVector enemyPosition)
{
  if(enemyPosition.x < bulletsPosition.x + bulletSize
  && enemyPosition.x + playerSize > bulletsPosition.x 
  && enemyPosition.y < bulletsPosition.y + bulletSize
  && enemyPosition.y + playerSize > bulletsPosition.y)
  {
    return true;
  }
  else return false;
}

boolean playerDead(PVector playerPosition, PVector enemyPosition)
{
  if(enemyPosition.x < playerPosition.x + playerSize
  && enemyPosition.x + playerSize > playerPosition.x 
  && enemyPosition.y < playerPosition.y + playerSize
  && enemyPosition.y + playerSize > playerPosition.y)
  {
    return true;
  }
  else return false;
}

void keyPressed()
{
  if(!GG)
  {
    if(key == 'w')
    {
      keyPress[0] = true;
    }
    if(key == 's')
    {
    keyPress[1] = true;
    }
    if(key == 'a')
    {
      keyPress[2] = true;
    }
    if(key == 'd')
    {
      keyPress[3] = true;
    }
    if(key == 'l')
    {
      fire = true;
    }
  }
}

void keyReleased()
{
  if(!GG)
  {
    if(key == 'w')
    {
      keyPress[0] = false;
    }
    if(key == 's')
    {  
      keyPress[1] = false;
    }
    if(key == 'a')
    {
      keyPress[2] = false;
    }
    if(key == 'd')
    {
      keyPress[3] = false;
    }
    if(key == 'l')
    {
      fire = false;
      firstShot = true;
    }
  }
}
