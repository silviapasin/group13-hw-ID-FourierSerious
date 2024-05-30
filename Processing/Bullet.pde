class Bullet{
  int posX;
  int posY;
  int on;
  
  Bullet(int x, int midi)
  {
    posX = x;
    posY = 180;
    on = midi;
  }
  
  void move(){
    posY += 15;
  }
  
  void display(){
    if(drawBullet[on])
  {
    move();
    image(laser, posX, posY, 10, 30);
    if(posY > height - 110)
    {
      drawBullet[on] = false;
      posY = 180;
      Score ++;
    }
  }  
  }
}
