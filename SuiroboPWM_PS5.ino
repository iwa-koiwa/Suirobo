#include <ps5.h>
#include <ps5Controller.h>
#include <ps5_int.h>

// ライブラリのインクルード
#include "cmath"
#include <ps5Controller.h>
// ピンの定義
int In[8] = {17, 16, 22, 0, 25, 26, 15, 14};
// 速度の定義
int speedH = 255;
int speedM = 160;
int speedS = 0;
int speedL = 100;
// 初期設定
void setup()
{
  Serial.begin(115200);           // シリアル通信
  ps5.begin("A0:FA:9C:2B:D4:DD"); // コントローラーのMACアドレスを指定
  Serial.println("Ready.");
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
  MD1(ps5.LStickY(), ps5.RStickY()); // MD1の制御
  MD2(ps5.L2Value(), ps5.R2Value()); // MD2の制御
  // Serial.printf("Battery Level : %d\n", ps5.Battery());
  // Serial.printf("Left Stick y at %d\n", ps5.LStickY());
  Serial.printf("Right Stick y at %d\n", ps5.RStickY());
  Serial.printf("L2 button at %d\n", ps5.L2Value());
  Serial.printf("R2 button at %d\n", ps5.R2Value());
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
    Serial.printf("%d\n",left);
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
    ledcWrite(4, left + 127);
    ledcWrite(5, 0);
  }
  else if (140 > left > 200)
  {
    ledcWrite(4, 0);
    ledcWrite(5, abs(left) + 127);
  }
  else
  {
    ledcWrite(4, 0);
    ledcWrite(5, 0);
  }
  if (right > 200)
  {
    ledcWrite(6, right + 127);
    ledcWrite(7, 0);
  }
  else if (140 > right > 200)
  {
    ledcWrite(6, 0);
    ledcWrite(7, abs(right) + 127);
    Serial.printf("go");
  }
  else
  {
    ledcWrite(6, 0);
    ledcWrite(7, 0);
  }
}

