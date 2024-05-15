#include "misc.h"

// Rounds a value at the given interval (like 0.5)
float roundAt(float value, float interval) {
  interval = interval * 100;
  int valuetwodigit = value * 100;
  int valuetwodigitDiff = valuetwodigit % 100;
  if (valuetwodigitDiff < (interval / 2)) {
    valuetwodigit -= valuetwodigitDiff;
  } else if (valuetwodigitDiff < interval * 1.5) {
    valuetwodigit -= valuetwodigitDiff;
    valuetwodigit += interval;
  } else {
    valuetwodigit -= valuetwodigitDiff;
    valuetwodigit += (interval * 2);
  }

  return valuetwodigit / 100.0;
}
