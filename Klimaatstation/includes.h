#include "config.h"

#include "errorCodes.h"
#include "Arduino.h"
#include "roundAt.h"

#ifdef DOORPIN
  #include "door.h"
#endif
#ifdef DHTPIN
  #include "humidity.h"
#endif
#ifdef LIGHTPIN
  #include "lightintensity.h"
#endif
#ifdef MOTIONPIN
  #include "motion.h"
#endif
#ifdef TEMPPINLM35
  #include "temperature.h"
#endif
#ifdef TEMPPINDS18B20
  #include "temperature.h"
#endif
#ifdef SOUNDPIN
  #include "sound.h"
#endif
#ifdef DUSTPIN
  #include "dust.h"
#endif
#ifdef BATTERYINDICATORPIN
  #include "batteryIndicator.h"
#endif

