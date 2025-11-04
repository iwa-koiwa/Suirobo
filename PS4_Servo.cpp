// ライブラリのインクルード
#include "cmath"
#include <PS4Controller.h>
#include <Arduino.h>
#include <ESP32Servo.h>
// ピンの定義
int In[8] = {17, 16, 22, 0, 25, 26, 15, 14};
int Servopin[2] = {27, 14};
// 速度の定義
int speedH = 255;
int speedM = 160;
int speedS = 0;
int speedL = 100;
int servomin = 500;  // サーボの最小値
int servomax = 2400; // サーボの最大値
// 初期設定
Servo myServo1;
Servo myServo2;

void setup()
{
  Serial.begin(115200);           // シリアル通信
  PS4.begin("A0:FA:9C:2B:D4:DD"); // コントローラーのMACアドレスを指定
  Serial.println("Ready.");
  // サーボの設定
  myServo1.setPeriodHertz(50);                      // Standard 50hz servo
  myServo2.setPeriodHertz(50);                      // Standard 50hz servo
  myServo1.attach(Servopin[0], servomin, servomax); // サーボ1をピン27に接続
  myServo2.attach(Servopin[1], servomin, servomax); // サーボ2をピン14に接続
  // PWMの設定
  for (int i = 0; i < 8; i++)
  {
    ledcSetup(i, 12800, 8);
    ledcAttachPin(In[i], i);
  }
}

void loop()
{
  Serial.println("MD1");
  MD1(PS4.LStickY(), PS4.RStickY()); // MD1の制御
  MD2(PS4.L2Value(), PS4.R2Value()); // MD2の制御
  Serial.printf("Battery Level : %d\n", PS4.Battery());
  Serial.printf("Left Stick y at %d\n", PS4.LStickY());
  Serial.printf("Right Stick y at %d\n", PS4.RStickY());
  Serial.printf("L2 button at %d\n", PS4.L2Value());
  Serial.printf("R2 button at %d\n", PS4.R2Value());
  delay(50);
}
// 1モーター制御関数
void MD1(int left, int right)
{
  if (left > 20)
  {
    ledcWrite(0, left);
    ledcWrite(1, 0);
  }
  else if (left < -20)
  {
    ledcWrite(0, 0);
    ledcWrite(1, abs(left));
    Serial.printf("%d\n", left);
  }
  else
  {
    ledcWrite(0, 0);
    ledcWrite(1, 0);
  }
  if (right > 20)
  {
    ledcWrite(2, right);
    ledcWrite(3, 0);
  }
  else if (right < -20)
  {
    ledcWrite(2, 0);
    ledcWrite(3, abs(right));
  }
  else
  {
    ledcWrite(2, 0);
    ledcWrite(3, 0);
  }
}
// 2モーター制御関数
void MD2(int left, int right)
{
  if (left > 200)
  {
    myServo1.write(180); // サーボ1を180度に設定
  }
  else if (140 > left > 200)
  {
    myServo1.write(90); // サーボ1を0度に設定
  }
  else
  {
    myServo1.write(0); // サーボ1を0度に設定
  }
  if (right > 200)
  {
    myServo2.write(180); // サーボ2を180度に設定
  }
  else if (140 > right > 200)
  {
    myServo2.write(90); // サーボ2を90度に設定
  }
  else
  {
    myServo2.write(0); // サーボ2を0度に設定
  }
}
