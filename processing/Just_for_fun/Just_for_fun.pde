int now = 0;
PVector force;
PVector position, velocity, acceleration, size, zero;
boolean show = false, shoot = false;
ArrayList<Ball> balls = new ArrayList<Ball>();

void setup()
{
  size(800, 600);
  frameRate(60);
  zero = new PVector(0, 0);
}

void draw()
{
  background(0, 0, 0, 100);
  if(show)
  {
    for(int i = 0; i < now; i++)
    {
      balls.get(i).collision();
      balls.get(i).display();
      balls.get(i).remove_0();
    }
  }
  if(shoot)
  {
    fill(255);
    noStroke();
    ellipse(position.x, position.y, size.x, size.y);
    stroke(200, 0, 0);
    strokeWeight(5);
    line(position.x, position.y, mouseX, mouseY);
  }
  
}

void mousePressed()
{
  position = new PVector(mouseX,mouseY);
  size = new PVector(60, 60);
  shoot = true;
}

void mouseReleased()
{
  force = new PVector(mouseX, mouseY);
  velocity = new PVector((position.x-force.x), (position.y-force.y));
  if(velocity.x > 0)
  {
    acceleration = new PVector(-0.02, 0.3);
  }
  else
  {
    acceleration = new PVector(0.02, 0.3);
  }
  balls.add(new Ball(position, velocity, acceleration, 255));
  now++;
  if(!show) show = true;
  shoot = false;
}

class Ball
{
  float ball_color;
  PVector ball_position, ball_velocity, ball_acceleration;
  
  Ball(PVector iball_position, PVector iball_velocity, PVector iball_acceleration, int iball_color)
  {
    ball_position = iball_position;
    ball_velocity = iball_velocity;
    ball_acceleration = iball_acceleration;
    ball_color = iball_color;
  }
  
  void collision()
  {
    if(ball_position.y >= height - (size.y/2))
    {
      ball_position.y = height - (size.y/2);
      ball_velocity.y = -ball_velocity.y * 0.7;
    }
    else if(ball_position.y <= size.y/2)
    {
      ball_position.y = size.y/2;
      ball_velocity.y = -ball_velocity.y;
    }
    if(ball_velocity.x * ball_acceleration.x >= 0 && ball_position.y >= height - (size.y/2))
    {
      ball_velocity.x = zero.x;
    }
    if(abs(ball_velocity.y) <= 0.4 && (ball_position.y >= height - (size.x/2)))
    {
      ball_velocity = zero; 
    }
    if(ball_velocity.x * ball_acceleration.x < 0 || ball_position.y < height - (size.y/2))
    {
      ball_velocity.add(ball_acceleration);
      ball_position.add(ball_velocity);
    }
    if(ball_position.x >= width - (size.x/2))
    {
      ball_position.x = width - (size.x/2);
      ball_velocity.x = -ball_velocity.x * 0.7;
      ball_acceleration.x *= -1;
    }
    else if(ball_position.x <= (size.x/2))
    {
      ball_position.x = size.x/2;
      ball_velocity.x = -ball_velocity.x * 0.7;
      ball_acceleration.x *= -1;
    }
    if(ball_velocity == zero && ball_position.y == height - (size.y/2))
    {  
      ball_color -= 2;
    }
  }
  
  void remove_0()
  {
    if(ball_color <= 0)
    {
      balls.remove(0);
      now--;
    }
  }
  
  void display()
  {
    noStroke();
    fill(ball_color);
    ellipse(ball_position.x, ball_position.y, size.x, size.y);
  }
}
