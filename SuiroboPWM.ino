#include "cmath"
#include <PS4Controller.h>

int In[4] = {17 ,16 ,22 ,0 };

int speedH = 255;
int speedM = 160;
int speedS = 0;
int speedL = 100;

void setup() {
  Serial.begin(115200);
  PS4.begin("80:f3:da:41:53:de");
  Serial.println("Ready.");
  
  for (int i = 0; i < 4; i++) {
    ledcSetup(i, 12800, 8);
    ledcAttachPin(In[i], i);
  }
}

void loop() {
  Serial.println("MD1");
  MD(PS4.LStickX(),PS4.RStickX());
  Serial.printf("Battery Level : %d\n", PS4.Battery());
  Serial.printf("Left Stick x at %d\n", PS4.LStickX());
  Serial.printf("Right Stick x at %d\n", PS4.RStickX());
  delay(50);
}

void MD(int left,int right){
    if(left > 20)
    {
      ledcWrite(0, left);
      ledcWrite(1, 0);
    }
    else if(left < 20)
    {
      ledcWrite(0, 0);
      ledcWrite(1, abs(left));
    }
    else{
      ledcWrite(0, 0);
      ledcWrite(1, 0);
    }
    if(right > 20)
    {
      ledcWrite(2, right);
      ledcWrite(3, 0);
    }
    else if(right < 20)
    {
      ledcWrite(2, 0);
      ledcWrite(3, abs(right));
    }
    else{
      ledcWrite(2, 0);
      ledcWrite(3, 0);
    }
    
}