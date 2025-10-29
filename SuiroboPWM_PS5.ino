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
  ps5.begin("80:f3:da:41:53:de"); // コントローラーのMACアドレスを指定
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
  MD1(ps5.LStickX(), ps5.RStickX()); // MD1の制御
  MD2(ps5.L2(), ps5.R2());           // MD2の制御
  Serial.printf("Battery Level : %d\n", ps5.Battery());
  Serial.printf("Left Stick x at %d\n", ps5.LStickX());
  Serial.printf("Right Stick x at %d\n", ps5.RStickX());
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
  if (left > 20)
  {
    ledcWrite(4, left + 127);
    ledcWrite(5, 0);
  }
  else if (left < 20)
  {
    ledcWrite(4, 0);
    ledcWrite(5, abs(left) + 127);
  }
  else
  {
    ledcWrite(4, 0);
    ledcWrite(5, 0);
  }
  if (right > 20)
  {
    ledcWrite(6, right + 127);
    ledcWrite(7, 0);
  }
  else if (right < 20)
  {
    ledcWrite(6, 0);
    ledcWrite(7, abs(right) + 127);
  }
  else
  {
    ledcWrite(6, 0);
    ledcWrite(7, 0);
  }
}
