// ライブラリのインクルード
#include "cmath"
#include <PS4Controller.h>
#include <Arduino.h>
#include <ESP32Servo.h>
// ピンの定義
int In[4] = {17, 16, 4, 0};
int Servopin = 13;
// 速度の定義
int speedH = 255;
int speedM = 160;
int speedS = 0;
int speedL = 100;
int servomin = 500;  // サーボの最小値
int servomax = 2400; // サーボの最大値
// 初期設定
Servo myServo1;

void setup()
{
  Serial.begin(115200);           // シリアル通信
  PS4.begin("80:f3:da:41:53:de"); // コントローラーのMACアドレスを指定
  Serial.println("Ready.");
  // サーボの設定
  myServo1.attach(Servopin, servomin, servomax); // サーボ1をピン27に接続
  // PWMの設定
  ledcSetup(2, 12800, 8);  // チャンネル1、周波数12.8kHz、分解能8ビット
  ledcSetup(3, 12800, 8);  // チャンネル2
  ledcSetup(5, 12800, 8);  // チャンネル3
  ledcSetup(6, 12800, 8);  // チャンネル4
  ledcAttachPin(In[0], 2); // ピン17をチャンネル1に接続
  ledcAttachPin(In[1], 3); // ピン16をチャンネル2に接続
  ledcAttachPin(In[2], 5); // ピン22をチャンネル3に接続
  ledcAttachPin(In[3], 6); // ピン0をチャンネル4に接続
  // for (int i = 2; i < 6; i++)
  // {
  //   ledcSetup(i, 12800, 8);
  //   ledcAttachPin(In[i], i);
  // }
}
void loop()
{
  Serial.println("MD1");
  MD1(PS4.LStickY(), PS4.RStickY()); // MD1の制御
  MD2(PS4.L2Value());              // Servoの制御
  Serialprint();
  delay(50);
}
void Serialprint()
{
  Serial.printf("Battery Level : %d\n", PS4.Battery());
  Serial.printf("Left Stick y at %d\n", PS4.LStickY());
  Serial.printf("Right Stick y at %d\n", PS4.RStickY());
  Serial.printf("L2 button at %d\n", PS4.L2Value());
  Serial.printf("R2 button at %d\n", PS4.R2Value());
}
// 1モーター制御関数
void MD1(int left, int right)
{
  if (left > 20)
  {
    ledcWrite(2, left);
    ledcWrite(3, 0);
  }
  else if (left < -20)
  {
    ledcWrite(2, 0);
    ledcWrite(3, abs(left));
    Serial.printf("%d\n", left);
  }
  else
  {
    ledcWrite(2, 0);
    ledcWrite(3, 0);
  }
  if (right > 20)
  {
    ledcWrite(5, right);
    ledcWrite(6, 0);
  }
  else if (right < -20)
  {
    ledcWrite(5, 0);
    ledcWrite(6, abs(right));
  }
  else
  {
    ledcWrite(5, 0);
    ledcWrite(6, 0);
  }
}

void MD2(int left)
{
  int pos1 = 120;
  int pos2 = 1;
  if (left > 200)
  {
    myServo1.write(pos2); // サーボ1を180度に設定
    Serial.printf("Servo1 Position: %d\n", pos1);
  }
  else
  {
    myServo1.write(pos1); // サーボ1を0度に設定
    Serial.printf("Servo1 Position: %d\n", pos2);
  }
}

// シリアル出力で情報表示自由にOFF可能
