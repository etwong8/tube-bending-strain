# Strain Gauge Cantilever Tube Bending

At-home project to learn strain gauge data acquisition end-to-end: bonding, wiring, calibration,
and live strain/load readout on a cantilevered steel tube. Built as prep work for measuring
suspension loads on the Offroad Illini Baja SAE vehicle.

## Hardware

- Strain gauges (quarter/full Wheatstone bridge, 350 Ω nominal arms)
- HX711 load cell amplifier
- Teensy 4.1 microcontroller
- Laptop (serial readout)

See slideshow (`Summer_Strain_Gauge_Project.pdf`) for wiring diagram and system overview.

## Files

| File | Purpose |
|---|---|
| `calibration.ino` | Streams raw HX711 counts over serial while known weights are hung. Used to build a linear regression of counts vs. weight and derive an empirical counts-per-unit calibration factor. Adapted from a [Random Nerd Tutorials](https://randomnerdtutorials.com/arduino-load-cell-hx711/) example (used with permission). |
| `measure.ino` | Live measurement program. Tares on startup, then streams counts, microstrain, and weight using the calibration constants in `StrainConfig.h`. |
| `StrainConfig.h` | Shared config: pin assignments, tube/gauge geometry, material properties, and the empirical calibration factors (`COUNTS_PER_MICROSTRAIN`, `COUNTS_PER_LB`) produced by `calibration.ino`. |

## Workflow

1. Wire the bridge to the HX711 and the HX711 to the Teensy per the wiring diagram.
2. Flash `calibration.ino` and record counts readouts for a series of known hung weights.
3. Run a linear regression on (weight, counts) to get counts/lb, and on (calculated microstrain,
   counts) to get counts/microstrain.
4. Enter both values into `StrainConfig.h`.
5. Flash `measure.ino` to get live strain and weight readout.

## Notes

- **Modified delays:** The tare/load delays in `calibration.ino` (`delay(10000)` /
  `delay(20000)`) were lengthened from the original tutorial to give more time to remove and hang
  weights by hand without rushing the reading.
- **`StrainConfig.h` changes require reopening the sketch:** Because it's included with
  `<StrainConfig.h>` (library-style include) rather than `"StrainConfig.h"`, the Arduino IDE
  caches it. After editing calibration factors or constants in the header, close and reopen
  `calibration.ino` / `measure.ino` before recompiling, or the changes may not take effect.
- Calibration should be performed and recorded in one sitting where possible — see the strain gauge
  project write-up (linked slideshow) for why this matters (temperature drift, connection
  movement, etc.).

## Acknowledgments

- Calibration sketch structure adapted from Rui Santos / Random Nerd Tutorials, used with
  permission.
- Thanks to Tim Hunter (Wolf Star Technologies) and Patrick Orr / Spartan Racing Baja for their
  help and equipment access during this project.
