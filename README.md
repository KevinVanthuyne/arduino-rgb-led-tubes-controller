# RGB LED Tubes Controller

**_DIY Stage Lights!_**

PlatformIO project using qn Arduino Mega to control a custom set of DIY RGB LED tubes used as stage lighting effects.

## Installation

Change the used `LiquidCrystal` library in `.pio/libdeps/LiquidMenu_ID671/src/LiquidMenu_Config.h` to `LiquidCrystal_I2C` by commenting

```c
#define LIQUIDMENU_LIBRARY LiquidCrystal_LIBRARY
#include <LiquidCrystal.h>
#define DisplayClass LiquidCrystal
```

and uncommenting

```c
// #define LIQUIDMENU_LIBRARY LiquidCrystal_I2C_LIBRARY
// #include <LiquidCrystal_I2C.h>
// #define DisplayClass LiquidCrystal_I2C
```

Build and upload the project to the Arduino using PlatformIO.
