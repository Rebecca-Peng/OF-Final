/**
 * <p>Ketai Library for Android: http://KetaiProject.org</p>
 *
 * <p>KetaiBluetooth wraps the Android Bluetooth RFCOMM Features:
 * <ul>
 * <li>Enables Bluetooth for sketch through android</li>
 * <li>Provides list of available Devices</li>
 * <li>Enables Discovery</li>
 * <li>Allows writing data to device</li>
 * </ul>
 * <p>Updated: 2012-05-18 Daniel Sauter/j.duran</p>
 */

//required for BT enabling on startup
import ketai.sensors.*;
import android.content.Intent;
import android.os.Bundle;

import ketai.net.bluetooth.*;
import ketai.ui.*;
import ketai.net.*;

import oscP5.*;

KetaiSensor sensor;
float accelerometerX, accelerometerY, accelerometerZ;

KetaiBluetooth bt;
String info = "";
KetaiList klist;
PVector remoteMouse = new PVector();

ArrayList<String> devicesDiscovered = new ArrayList();
boolean isConfiguring = true;
String UIText;
PImage beak;
PImage chan;
PImage chen;
PImage du;
PImage kai;
PImage xiumin;
PImage suho;
PImage lay;
PImage sehun;

PFont font;
//********************************************************************
// The following code is required to enable bluetooth at startup.
//********************************************************************
void onCreate(Bundle savedInstanceState) {
  super.onCreate(savedInstanceState);
  bt = new KetaiBluetooth(this);
}

void onActivityResult(int requestCode, int resultCode, Intent data) {
  bt.onActivityResult(requestCode, resultCode, data);
}

//********************************************************************

void setup()
{ 
  fullScreen(P3D);
  background(117,136,192);
  beak = loadImage("beakhy.png");
  chan = loadImage("chan.png");
  chen = loadImage("chen.png");
  du = loadImage("do.png");
  kai = loadImage("kai.png");
  lay = loadImage("lay.png");
  sehun = loadImage("sehun.png");
  suho = loadImage("suho.png");
  xiumin = loadImage("xiumin.png");
  font = loadFont("Futura-Medium-48.vlw");
  stroke(255);
  textSize(24);
  
  sensor = new KetaiSensor(this);
  sensor.start();

  //start listening for BT connections
  bt.start();

}

void draw()
{
  if (isConfiguring)
  {
    ArrayList<String> names;
    background(117,136,192);
    //based on last key pressed lets display
    //  appropriately
    if (key == 'i')
      info = getBluetoothInformation();
    else
    {
      if (key == 'p')
      {
        info = "Paired Devices:\n";
        names = bt.getPairedDeviceNames();
      }
      else
      {
        info = "Discovered Devices:\n";
        names = bt.getDiscoveredDeviceNames();
      }

      for (int i=0; i < names.size(); i++)
      {
        info += "["+i+"] "+names.get(i).toString() + "\n";
      }
    }
    fill(255);
    textFont(font,30);
    text(info, 415, 1600);
    drawUI1();
  }
  
  else
  {
    //background(117,136,192,accelerometerX*2);
    float x = map(accelerometerX,10,-10,0,255);
    background(x,x,0);
    textSize(50);
    //text(accelerometerX,width/2,height/2);
    byte acX = byte(accelerometerX/1*2);
    byte[] data = {acX};
    bt.broadcast(data);
  }
}


//Call back method to manage data received
void onBluetoothDataEvent(String who, byte[] data)
{
  if (isConfiguring)
    return;

  //KetaiOSCMessage is the same as OscMessage
  //   but allows construction by byte array
  info += data;

}

String getBluetoothInformation()
{
  String btInfo = "Server Running: ";
  btInfo += bt.isStarted() + "\n";
  btInfo += "Discovering: " + bt.isDiscovering() + "\n";
  btInfo += "Device Discoverable: "+bt.isDiscoverable() + "\n";
  btInfo += "\nConnected Devices: \n";

  ArrayList<String> devices = bt.getConnectedDeviceNames();
  for (String device: devices)
  {
    btInfo+= device+"\n";
  }

  return btInfo;
}