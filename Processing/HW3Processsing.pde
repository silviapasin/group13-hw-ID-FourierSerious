import oscP5.*;
import netP5.*;

OscP5 oscP5;
PFont myfont;
float anagx, anagy,filterCut;
int Xpos;
int Ypos;
int note;
int Score;
int shift = 24;
int wave;
int[] xPiano = {19, 36, 53, 68, 86, 119, 134, 152, 167, 185, 201, 218, 251, 268, 284, 300, 317, 350, 366, 383, 399, 416, 432, 450};
PImage bkgrn, ship, piano, laser,gameOver,enter;
boolean drawClick;
boolean drawBullet[];
boolean start;
int duration = 60;
int clickedFrame;
Bullet[] bullets = new Bullet[24];

void setup()
{
  size(469,932);
  noStroke();
  
  start = false;
  
  Xpos = 220;
  Ypos = 531; 
  
  drawBullet = new boolean[24];
  
  for (int i =0; i<bullets.length; i++)
  {
     bullets[i] = new Bullet(xPiano[i],i); 
  }
  
  
  bkgrn = loadImage("space.jpg");
  ship = loadImage("ship.png");
  ship.resize(40,70);
  piano = loadImage("piano.jpg");
  piano.resize(469,0);
  laser = loadImage("laser.png");
  gameOver = loadImage("gameover.png");
  enter = loadImage("enter.png");
  enter.resize(150,100);
  
  //band = loadImage("band.png");
  //cut = loadImage("cut.png");
  //filter = loadImage("filter.png");
  //high = loadImage("high.png");
  //low = loadImage("low.png");
  //osc = loadImage("osc.png");
  //saw = loadImage("saw.png");
  //score = loadImage("score.png");
  //white = loadImage("white.png");
  //sine = loadImage("sine.png");
  //square = loadImage("square.png");
  //triang = loadImage("triang.png");
  myfont = createFont("ARCADECLASSIC.TTF",24);
  
  //noStroke();
  //rectMode(CENTER);
  frameRate(60);
  Score = 0;
  /* start oscP5, listening for incoming messages at port 7563 */
  oscP5 = new OscP5(this,8674);
  //surface.setResizable(true);
 
}

void draw()
{
  
  drawBackground();
  //println (mouseX +"," + mouseY);
  
  image(ship, Xpos,  Ypos );
  image(piano,0,0);
  
  drawNote(note);
  
  for (int i =0; i<bullets.length; i++)
  {
     bullets[i].display(); 
  }
  
  if (isGameOver()){
    looping =  !looping;
    drawBackground();
    image(gameOver,width/2 - gameOver.width/2 , height/2 - gameOver.height/2 - 100);
    image(enter,width/2 - enter.width/2 , height/2 - enter.height/2 + 100);
    for(int i =0; i<bullets.length; i++){
      bullets[i].posY = 180; 
      Score = 0;
    }
  }
  
  if (!start){
    looping = !looping;
    drawBackground();
    //textFont(myfont);
    //stroke(153, 0, 255);
    fill(102, 102, 255);
    //fill(153, 0, 255);
    textSize(42);
    textAlign(CENTER);
    text("WELCOME \n TO \n POSTACCIO INVADERS",width/2 , height/2 - gameOver.height/2 - 100);
    image(enter,width/2 - enter.width/2 , height/2 - enter.height/2 + 100);
  }
}

void drawBackground(){
  textAlign(LEFT);
  background(0);
  image(bkgrn, 0,0);
  textFont(myfont);
  stroke(255);
  fill(153, 0, 255);
  textSize(22);
  
  text("SCORE", shift, bkgrn.height+shift);
  text("FILTER", 110+shift, bkgrn.height+shift);
  text("OSC", 230+shift, bkgrn.height+shift);
  text("CUTOFF", 340+shift, bkgrn.height+shift);
  
  fill(255,0,0);
  textSize(38);
  text(Score, 46, bkgrn.height+shift+45);
  
  textSize(14);
  text("Low pass", 120+shift, bkgrn.height+shift+20);
  text("Band pass", 120+shift, bkgrn.height+shift+40);
  text("High pass", 120+shift, bkgrn.height+shift+60);
  
  text("Sine", 240+shift, bkgrn.height+shift+20);
  text("Saw", 240+shift, bkgrn.height+shift+33);
  text("Square", 240+shift, bkgrn.height+shift+46);
  text("Triangule", 240+shift, bkgrn.height+shift+57);
  text("White Noise", 240+shift, bkgrn.height+shift+70);
  
  textSize(38);
  text(Score, 46, bkgrn.height+shift+45);
  
  textSize(28);
  text(int(filterCut), 350+shift, bkgrn.height+shift+45);
  
  drawSelector();
  
}

void oscEvent(OscMessage theOscMessage) {
  if (theOscMessage.checkAddrPattern("/joystick/x") == true) {

  anagx = theOscMessage.get(0).floatValue();
  Xpos = int(map(anagx, 0, 0.84, 0, width - 30));
  //theOscMessage.print();
  //print("\n" + Xpos);
  }
  
  if (theOscMessage.checkAddrPattern("/joystick/y") == true) {

  anagy = theOscMessage.get(0).floatValue();
  Ypos = int(map(anagy, 0, 0.84, height - 70 - 100, 300));
  filterCut = 65 * pow(10, anagx / 0.922053);
  //print("\n" + Ypos);
  }
  
  if (theOscMessage.checkAddrPattern("/wave") == true) {
    wave = theOscMessage.get(0).intValue();
    print(wave);
  }
  
  if (theOscMessage.checkAddrPattern("/key") == true) {
    
    clickedFrame = frameCount;
    for(int i=0; i<24; i++){
      if(theOscMessage.get(0).intValue() == i){
        note = i;
        drawBullet[i] = true;
        drawClick = true;
      }
    }
    
  }
  
}

void drawSelector()
{
  if(anagy < 0.3){
    fill(255);
    triangle(125, bkgrn.height+35, 135, bkgrn.height+40, 125, bkgrn.height+45);
  }
  if(0.3 < anagy && anagy < 0.6){
    fill(255);
    triangle(125, bkgrn.height+55, 135, bkgrn.height+60, 125, bkgrn.height+65);
  }
  if(anagy > 0.6){
    fill(255);
    triangle(125, bkgrn.height+75, 135, bkgrn.height+80, 125, bkgrn.height+85);
  }
  if(wave == 0){
    fill(255);
    triangle(245, bkgrn.height+34, 255, bkgrn.height+39, 245, bkgrn.height+44);
  }
  if(wave == 1){
    fill(255);
    triangle(245, bkgrn.height+34+13, 255, bkgrn.height+39+13, 245, bkgrn.height+44+13);
  }
  if(wave == 2){
    fill(255);
    triangle(245, bkgrn.height+34+26, 255, bkgrn.height+39+26, 245, bkgrn.height+26+44);
  }
  if(wave == 3){
    fill(255);
    triangle(245, bkgrn.height+34+39, 255, bkgrn.height+39+39, 245, bkgrn.height+39+44);
  }
  if(wave == 4){
    fill(255);
    triangle(245, bkgrn.height+34+39+13, 255, bkgrn.height+39+39+13, 245, bkgrn.height+39+13+44);
  }
  
}


void drawNote(int midi)
{

  if(drawClick){
    if(midi == 0 || midi == 2 || midi == 4 || midi == 5 || midi == 7 || midi == 9 || midi == 11 || midi == 12 || midi == 14 || midi == 16 || midi == 17 || midi == 19 || midi == 21 || midi == 23){
      stroke(255,0,0);
      fill(0);
      circle(xPiano[midi], 140, 20);
    }
    else{
      stroke(255,0,0);
      fill(255);
      circle(xPiano[midi], 100, 18);
    }
    if(frameCount > clickedFrame + duration){
     drawClick = false; 
    }
  }
}

void keyPressed()
{
  //clickedFrame = frameCount;
  //if(key == 'a'){
  //  note = 0;
  //  drawBullet[0] = true;
  //  drawClick = true;
  //}
  //if(key == 's'){
  //  note = 1;
  //  drawBullet[1] = true;
  //  drawClick = true;
  //}
  //if(key == 'd'){
  //  note = 2;
  //  drawBullet[2] = true;
  //  drawClick = true;
  //}
  //if(key == 'f'){
  //  note = 3;
  //  drawBullet[3] = true;
  //  drawClick = true;
  //}
  //if(key == 'g'){
  //  note = 4;
  //  drawBullet[4] = true;
  //  drawClick = true;
  //}
  //if(key == 'l'){
  //  note = 13;
  //  drawBullet[6] = true;
  //  drawClick = true;
  //}
  if(key == 'p'){
    looping =  !looping;
  }
  if(key == ENTER){
     for (int i=0 ; i< bullets.length ; i++){
       drawBullet[i] = false;  
     }
     drawClick = false;
     start = true;
     looping = !looping;
  }
}

boolean isGameOver()
{
  int shipGridX = ceil(float(Xpos)/width*24);
  int shipGridY = ceil(float(Ypos)/height*18);
  for(int i = 0; i< bullets.length; i++){
    int bulletGridX = ceil(float(bullets[i].posX)/width*24)-1;
    int bulletGridY = ceil(float(bullets[i].posY)/height*18)-1;
    //print("shipx: " + shipGridX);
    //print("\n bulletx: " + bulletGridX);
    if(shipGridX == bulletGridX && shipGridY == bulletGridY){
      return true;
    }
  }
  return false;
}
