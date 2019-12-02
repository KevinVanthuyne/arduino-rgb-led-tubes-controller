#define MAIN_FILE

#include "main.h"

// input buttons config
#define BUTTON_DOWN 22
#define BUTTON_RIGHT 24
#define BUTTON_LEFT 26 // kleft
#define BUTTON_UP 28

bool lastButtonUpState = HIGH;
bool lastButtonRightState = HIGH;
bool lastButtonDownState = HIGH;
bool lastButtonLeftState = HIGH;
unsigned long lastDebounceMillis = 0;
unsigned long debounceTime = 100;

// mic config
#define MIC_PIN A1

// led tube config
#define TUBE_1_PIN 41
#define TUBE_2_PIN 43
#define TUBE_3_PIN 45
#define TUBE_4_PIN 47
#define TUBE_5_PIN 49
#define TUBE_6_PIN 51
#define PIXELS_PER_TUBE 58

byte pixelsPerTube = PIXELS_PER_TUBE;
CRGB leds1[PIXELS_PER_TUBE];
CRGB leds2[PIXELS_PER_TUBE];
CRGB leds3[PIXELS_PER_TUBE];
CRGB leds4[PIXELS_PER_TUBE];
CRGB leds5[PIXELS_PER_TUBE];
CRGB leds6[PIXELS_PER_TUBE];
CRGB *ledStrips[6] = {
    leds1,
    leds2,
    leds3,
    leds4,
    leds5,
    leds6};

// menu variables
LiquidCrystal_I2C lcd(0x27, 20, 4); // (I2C address, amount of characters, amount of lines)
LiquidMenu liquidMenu(lcd);
Navigation currentNavigation = NONE;

ProgramModeMenu programModeMenu;
AutoModeMenu autoModeMenu;

// mode variables
ProgramMode programMode;
AutoMode autoMode;
Mode *modes[2] = {&programMode, &autoMode};

int currentMode = 0;
int amountOfModes = 2;
int currentProgram = 1;
uint8_t programSpeed = 128; // ranges from 0 to 255

// programs
ColorCycleProgram colorCycleProgram = ColorCycleProgram();
ColorCycleSmoothProgram colorCycleSmoothProgram = ColorCycleSmoothProgram();
ColorSweepProgram colorSweepProgram = ColorSweepProgram();
ColorSweepInToOutProgram colorSweepInToOutProgram = ColorSweepInToOutProgram();
ColorSweepOutToInProgram colorSweepOutToInProgram = ColorSweepOutToInProgram();
ColorSweepInToOutToInProgram colorSweepInToOutToInProgram = ColorSweepInToOutToInProgram();
SparkleProgram sparkleProgram = SparkleProgram();
SparkleColorProgram sparkleColorProgram = SparkleColorProgram();
RainbowProgram rainbowProgram = RainbowProgram();
BreathingColorCycleSmoothProgram breathingColorCycleSmoothProgram = BreathingColorCycleSmoothProgram();
FadingScanlineProgram fadingScanlineProgram = FadingScanlineProgram();
StackerProgram stackerProgram = StackerProgram();
SingleColorSweepStartToEnd singleColorSweepStartToEnd = SingleColorSweepStartToEnd();
SingleColorSweepEndToStart singleColorSweepEndToStart = SingleColorSweepEndToStart();
SingleColorSweepBackAndForth singleColorSweepBackAndForth = SingleColorSweepBackAndForth();

Program *programs[15] = {
    &colorCycleProgram,
    &colorCycleSmoothProgram,
    &colorSweepProgram,
    &colorSweepInToOutProgram,
    &colorSweepOutToInProgram,
    &colorSweepInToOutToInProgram,
    &sparkleProgram,
    &sparkleColorProgram,
    &rainbowProgram,
    &breathingColorCycleSmoothProgram,
    &fadingScanlineProgram,
    &stackerProgram,
    &singleColorSweepStartToEnd,
    &singleColorSweepEndToStart,
    &singleColorSweepBackAndForth};

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  pinMode(MIC_PIN, INPUT);

  // initialize LCD (make sure to uncomment the LiquidCrystel_I2C part in the LiquidMenu_config.h)
  lcd.init();
  lcd.backlight();
  lcd.setCursor(3, 1);
  lcd.print("Starting up...");

  // initialize buttons
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT, INPUT_PULLUP);

  // set up led tubes
  FastLED.addLeds<WS2813, TUBE_1_PIN, GRB>(leds1, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2813, TUBE_2_PIN, GRB>(leds2, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2813, TUBE_3_PIN, GRB>(leds3, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2813, TUBE_4_PIN, GRB>(leds4, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2813, TUBE_5_PIN, GRB>(leds5, PIXELS_PER_TUBE);
  FastLED.addLeds<WS2813, TUBE_6_PIN, GRB>(leds6, PIXELS_PER_TUBE);
  FastLED.setBrightness(128);

  // setup menu's
  programModeMenu = ProgramModeMenu();
  autoModeMenu = AutoModeMenu();

  // setup LiquidMenu and Modes
  liquidMenu.init();
  programMode = ProgramMode(&programModeMenu);
  autoMode = AutoMode(&autoModeMenu);
  liquidMenu.update();
}

void loop()
{
  handleNavigation();
  modes[currentMode]->runIteration();
}

void handleNavigation()
{
  bool buttonUpReading = digitalRead(BUTTON_UP);
  bool buttonRightReading = digitalRead(BUTTON_RIGHT);
  bool buttonDownReading = digitalRead(BUTTON_DOWN);
  bool buttonLeftReading = digitalRead(BUTTON_LEFT);

  if (buttonUpReading != lastButtonUpState && (millis() - lastDebounceMillis) > debounceTime)
  {
    modes[currentMode]->menu->up();
    lastDebounceMillis = millis();
  }
  else if (buttonRightReading != lastButtonRightState && (millis() - lastDebounceMillis) > debounceTime)
  {
    modes[currentMode]->menu->right();
    lastDebounceMillis = millis();
  }
  else if (buttonDownReading != lastButtonDownState && (millis() - lastDebounceMillis) > debounceTime)
  {
    modes[currentMode]->menu->down();
    lastDebounceMillis = millis();
  }
  else if (buttonLeftReading != lastButtonLeftState && (millis() - lastDebounceMillis) > debounceTime)
  {
    modes[currentMode]->menu->left();
    lastDebounceMillis = millis();
  }

  lastButtonUpState = buttonUpReading;
  lastButtonRightState = buttonRightReading;
  lastButtonDownState = buttonDownReading;
  lastButtonLeftState = buttonLeftReading;
}
