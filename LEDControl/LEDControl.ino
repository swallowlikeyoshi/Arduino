#define RED 3
#define GREEN 5
#define BLUE 6
#define WHITE 9

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
    analogWrite(pin, this->bright);
  }
};

Driver drivers[4] = { Driver(RED, true, 0), Driver(GREEN, false, 0), Driver(BLUE, false, 0), Driver(WHITE, true, 0) };
const double GAMMA = 2.2;
int bright = 0;

int gammaAdjust(double bright)
{
  return 255 * pow((bright / 255), GAMMA);
}

void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(WHITE, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  if (bright > 255)
  {
    bright = 0;
  }

  for (int i = 0; i < 4; i++)
  {
    drivers[i].setBrightness(gammaAdjust(bright));
    // 비선형적 증감

    // driver[i].setBrightness(bright);
    // 선형적 증감
  }

  bright++;

  delay(10);
}
