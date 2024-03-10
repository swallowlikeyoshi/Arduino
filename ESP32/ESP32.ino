#define RED 0
#define GREEN 5
#define BLUE 6
#define WHITE 9

#include <math.h>

class Driver
{
private:
  int pin;
  bool isNMos;
  int bright;

public:
  Driver(int pin, bool isNtype, int bright)
  {
    this->pin = pin;
    this->isNMos = isNtype;
    this->bright = bright;
    setBrightness(bright);
  }

  void setBrightness(int bright)
  {
    this->bright = min(255, max(0, isNMos ? bright : (255 - bright)));
    ledcWrite(0, this->bright);
  }
};

Driver drivers[4] = { Driver(RED, true, 0), Driver(GREEN, false, 0), Driver(BLUE, false, 0), Driver(WHITE, true, 0) };
const double GAMMA = 2.2;
double bright = 0;

int gammaAdjust(double bright)
{
  return 255 * pow((bright / 255), GAMMA);
}

void setup()
{
  pinMode(RED, OUTPUT);
  // pinMode(GREEN, OUTPUT);
  // pinMode(BLUE, OUTPUT);
  // pinMode(WHITE, OUTPUT);
  ledcSetup(0, 20000, 8);
  ledcAttachPin(0, 0);   
  Serial.begin(115200);
}

void loop()
{
  if (bright > 1)
  {
    bright = 0;
  }

  for (int i = 0; i < 1; i++)
  {
    drivers[i].setBrightness(gammaAdjust(255 * sin(bright * PI)));
    // 비선형적 증감

    // driver[i].setBrightness(bright);
    // 선형적 증감
  }

  bright += 0.01;

  delay(1);
}