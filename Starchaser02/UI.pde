/*  UI-related functions */

int[] yrangeMin = new int[3];
int[] yrangeMax = new int[3];
int[] xrangeMin = new int[3];
int[] xrangeMax = new int[3];

void mousePressed()
{
       for(int i =0;i<3;i++){
        yrangeMin[i] = 500+315*i;
        yrangeMax[i] = yrangeMin[i]+200;
        xrangeMin[i] = 120+315*i;
        xrangeMax[i] = xrangeMin[i]+200;
        //println(xrangeMax[i]);
        //println(xrangeMin[i]);
        println(yrangeMax[i]);
        println(yrangeMin[i]);
  }
 //////keyboard button -- toggle virtual keyboard
  if (mouseY <= 50 && mouseX > 0 && mouseX < width/3)
    KetaiKeyboard.toggle(this);
  else if (mouseY <= 50 && mouseX > width/3 && mouseX < 2*(width/3)) //config button
  {
    isConfiguring=true;
      if(mouseY <1670 && mouseY>1820&&mouseX>170&&mouseX<320){
        if (bt.getDiscoveredDeviceNames().size() > 0)
          klist = new KetaiList(this, bt.getDiscoveredDeviceNames());
        else if (bt.getPairedDeviceNames().size() > 0)
          klist = new KetaiList(this, bt.getPairedDeviceNames());
    }
      else if(mouseY <1670 && mouseY>1820&&mouseX>170&&mouseX<320){
          bt.discoverDevices();
      }
  }
    //else if((mouseY <1015 && mouseY>815&&mouseX>435&&mouseX<635)||(mouseY <1015 && mouseY>815&&mouseX>220&&mouseX<470)||(mouseY<1015&&mouseY>815&&mouseX>850&&mouseX<110)){
       else if(
       (mouseY<yrangeMax[0] && mouseY>yrangeMin[0]&&mouseX>xrangeMin[0]&&mouseX<xrangeMax[0])||
       (mouseY<yrangeMax[0] && mouseY>yrangeMin[0]&&mouseX>xrangeMin[1]&&mouseX<xrangeMax[1])||
       (mouseY<yrangeMax[0] && mouseY>yrangeMin[0]&&mouseX>xrangeMin[2]&&mouseX<xrangeMax[2])||
       (mouseY<yrangeMax[1] && mouseY>yrangeMin[1]&&mouseX>xrangeMin[0]&&mouseX<xrangeMax[0])||
       (mouseY<yrangeMax[1] && mouseY>yrangeMin[1]&&mouseX>xrangeMin[1]&&mouseX<xrangeMax[1])||
       (mouseY<yrangeMax[1] && mouseY>yrangeMin[1]&&mouseX>xrangeMin[2]&&mouseX<xrangeMax[2])||
       (mouseY<yrangeMax[2] && mouseY>yrangeMin[2]&&mouseX>xrangeMin[0]&&mouseX<xrangeMax[0])||
       (mouseY<yrangeMax[2] && mouseY>yrangeMin[2]&&mouseX>xrangeMin[1]&&mouseX<xrangeMax[1])||
       (mouseY<yrangeMax[2] && mouseY>yrangeMin[2]&&mouseX>xrangeMin[2]&&mouseX<xrangeMax[2])
    ){
      if(isConfiguring){
      background(117,136,192);
      isConfiguring=false;
          }
        }
      }

void mouseDragged()
{
  if (isConfiguring)
    return;
 }

public void keyPressed() {
  if (key =='c')
  {
    //If we have not discovered any devices, try prior paired devices
    if (bt.getDiscoveredDeviceNames().size() > 0)
      klist = new KetaiList(this, bt.getDiscoveredDeviceNames());
    else if (bt.getPairedDeviceNames().size() > 0)
      klist = new KetaiList(this, bt.getPairedDeviceNames());
  }
  else if (key == 'd')
  {
    bt.discoverDevices();
  }
  else if (key == 'x')
    bt.stop();
  else if (key == 'b')
  {
    bt.makeDiscoverable();
  }
  else if (key == 's')
  {
    bt.start();
  }
  else if(key == 'a'){
  byte acX = byte(accelerometerX/1);
  byte[] data = {acX};
  bt.broadcast(data);
  }
}


void drawUI1()
{
  //Draw top shelf UI buttons

  pushStyle();
  fill(235,127,115);
  noStroke();
  rect(0, 0, width, 200);
  fill(255);
  for(int i = 0; i<3;i++){
    for(int j = 0;j<3;j++){
  ellipse(220+(250+65)*j,600+(250+65)*i,250,250);
    }
  }
  stroke(255);
  noFill();
  ellipse(220,1600,100,100);
  ellipse(220,1600,80,80);
  ellipse(220,1720,100,100);
  ellipse(220,1720,80,80);
  ellipse(220,1840,100,100);
  ellipse(220,1840,80,80);
  image(beak, 120, 500);
  image(chan, 435, 500);
  image(chen, 750, 500);
  image(du, 120, 815);
  image(lay, 435, 815);
  image(sehun, 750, 815);
  image(kai, 120, 1130);
  image(suho, 435, 1130);
  image(xiumin,750, 1130);

  fill(255);
  textFont(font,100);
  text("connect",width/2-160,130);
  textSize(50);
  text("D",205,1620);
  text("C",205,1740);
  text("I",215,1860);
  popStyle();
  
}

void onKetaiListSelection(KetaiList klist)
{
  String selection = klist.getSelection();
  bt.connectToDeviceByName(selection);

  //dispose of list for now
  klist = null;
}

void onAccelerometerEvent(float x, float y, float z)
{
  accelerometerX = x;
  accelerometerY = y;
  accelerometerZ = z;
  
}