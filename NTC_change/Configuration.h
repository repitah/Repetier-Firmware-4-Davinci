/*
    This file is part of Repetier-Firmware.

    Repetier-Firmware is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Repetier-Firmware is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Repetier-Firmware.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// ################## EDIT THESE SETTINGS MANUALLY ################

#define DAVINCI 4// "0" if not DAVINCI, "1" For DAVINCI 1.0, "2" For DAVINCI 2.0 with 1 FAN, "3" For DAVINCI 2.0 with 2 FAN, 4 for AiO (WITH NO SCANNER SUPPORT)
#define MODEL  1//"0" for first generation (jumper JP1 to reset ) , "1" for new generation   (jumper J37 to reset)
#define REPURPOSE_FAN_TO_COOL_EXTRUSIONS 0 //Setting this to 1 will repurpose the main Extruder cooling fan to be controlled VIA M106/M107
                                           //Warning: for DaVinci 1.0 need to add a permanent fan with power supply to cool extruder

// ################ END MANUAL SETTINGS ##########################

//Version
#define VERSION_MAJOR "1"
#define VERSION_MINOR_YEAR "21"
#define VERSION_MINOR_MONTH "02"
#define VERSION_MINOR_DAY "08"
#define VERSION_BUILD "1"

//Davinci screen is not standard reprap it is WINSTAR 16x4
#if DAVINCI==0
#define WINSTAR_SCREEN 0
#else
#define WINSTAR_SCREEN 1
#endif

//Decouple Test feature, do not disable it unless you know what you are doing!!!
//if you have decouple issue it means you have hardware issue or bad air flow management!!!
//this feature is a safety feature, if you disable it is dangerous!!!
#define FEATURE_DECOUPLE_TEST 1
//this will hide on sd card no extension files and bin/hex/dat files to make navigation and selection easier
#define HIDE_BINARY_ON_SD 1
#define UI_AUTOLIGHTOFF_AFTER 1
#define ENABLE_CLEAN_DRIPBOX 1
#define ENABLE_CLEAN_NOZZLE 1
#define FEATURE_ENCODER 0
//ensure of some define if AiO
#if DAVINCI==4
//no drip box
#undef ENABLE_CLEAN_DRIPBOX
#define ENABLE_CLEAN_DRIPBOX 0
//it must be model 1
#undef MODEL
#define MODEL 1
#endif
//to enable communication using wifi module set to 1
#define ENABLE_WIFI 0
//define the wifi serial output
//on Davinci use Serial
//on RADDS use Serial1
#if ENABLE_WIFI
#if DAVINCI == 0
#define WIFI_SERIAL Serial1
#else
#define WIFI_SERIAL Serial
#endif
#endif
//if wifi is enabled serial need to slow down a little, this is a delay in ms after a '\n' so normaly after a command or a message
#define DELAY_BY_LINE 50
#if ENABLE_CLEAN_NOZZLE
  #if DAVINCI==0 
    #define CLEAN_X 20
    #define CLEAN_Y 20
  #endif
  #if DAVINCI==1 //cleaner of Davinci 1.0 is not in same position of 2.0 neither AiO
    #define CLEAN_X 20
    #define CLEAN_Y 20
  #endif
  #if DAVINCI==2 || DAVINCI==3
    #define CLEAN_X 0
    #define CLEAN_Y 30
  #endif
  #if DAVINCI==4
    #define CLEAN_X 35
    #define CLEAN_Y 55
  #endif
#endif
#define CASE_KEEP_LIGHT_DEFAULT_ON 1
#define CASE_FILAMENT_SENSOR_DEFAULT_ON 1
#define CASE_TOP_SENSOR_DEFAULT_ON 1
#define CASE_SOUND_DEFAULT_ON 1
#define CASE_WIFI_DEFAULT_ON 0
//default mode is advanced
#define CASE_DISPLAY_MODE_DEFAULT 1

//Laser and turntable
#if DAVINCI == 4
#define TURNTABLE_STEP_PER_MM 110
//table perimeter in mm for angle rotation as not direct drive for turntable
#define TURNTABLE_PERIMETER 616 
//P/360 => 616/360 = 1.711111
#define TURNTABLE_MM_PER_DEG 1.7111111 
#define TURNTABLE_DEFAULT_SPEED 10
#define TURNTABLE_MAX_SPEED 50
#define TURNTABLE_HOME_SPEED 25
#define TURNTABLE_INVERT_ENABLE 0
#define TURNTABLE_INVERT_DIR 1
#define TURNTABLE_STEP_PIN     22
#define TURNTABLE_DIR_PIN      13
#define TURNTABLE_ENABLE_PIN   26 
#define NUM_MOTOR_DRIVERS 1 
#define MOTOR_DRIVER_1(var) StepperDriver<TURNTABLE_STEP_PIN,TURNTABLE_DIR_PIN,TURNTABLE_ENABLE_PIN,TURNTABLE_INVERT_DIR,TURNTABLE_INVERT_ENABLE> var(TURNTABLE_STEP_PER_MM,TURNTABLE_DEFAULT_SPEED)
#endif


/* Some words on units:

From 0.80 onwards the units used are unified for easier configuration, watch out when transferring from older configs!

Speed is in mm/s
Acceleration in mm/s^2
Temperature is in degrees celsius


##########################################################################################
##                                        IMPORTANT                                     ##
##########################################################################################

For easy configuration, the default settings enable parameter storage in EEPROM.
This means, after the first upload many variables can only be changed using the special
M commands as described in the documentation. Changing these values in the configuration.h
file has no effect. Parameters overriden by EEPROM settings are calibration values, extruder
values except thermistor tables and some other parameter likely to change during usage
like advance steps or ops mode.
To override EEPROM settings with config settings, set EEPROM_MODE 0

*/


// BASIC SETTINGS: select your board type, thermistor type, axis scaling, and endstop configuration

/** Number of extruders. Maximum 6 extruders. */
#if DAVINCI==0
#define NUM_EXTRUDER 1
#endif
//1.0/1.0A/AiO have 1 extruder
#if DAVINCI==1 || DAVINCI==4
#define NUM_EXTRUDER 1
#endif
//2.0/2.0A have 2 extruders
#if DAVINCI==2 || DAVINCI==3
#define NUM_EXTRUDER 2
#endif

/** Set to 1 if all extruder motors go to 1 nozzle that mixes your colors. */
#define MIXING_EXTRUDER 0

//// The following define selects which electronics board you have. Please choose the one that matches your setup
// Arduino Due with RADDS       = 402
// Arduino Due with RAMPS-FD    = 403
// Arduino Due with RAMPS-FD V2 = 404
// Felix Printers for arm       = 405
// DAM&DICE DUE                 = 406
// Smart RAMPS for Due          = 408
// Ultratronics Board           = 409
// DUE3DOM                      = 410
// DUE3DOM MINI                 = 411
// Alligator Board rev1         = 500
// Alligator Board rev2         = 501
//DaVinci                              = 999

#if DAVINCI==0
#define MOTHERBOARD 402
#else
#define MOTHERBOARD 999
#endif

#include "pins.h"

// Override pin definitions from pins.h
//#define FAN_PIN   4  // Extruder 2 uses the default fan output, so move to an other pin
//#define EXTERNALSERIAL  use Arduino serial library instead of build in. Requires more ram, has only 63 byte input buffer.


/*
We can connect BlueTooth to serial converter module directly to boards with a free serial port. Of course could you also
use it to connect a second device like Raspberry PI internal connection. Just make sure only one port of the 2 supported
gets used, or you will get problems with checksums etc.
- On RADDS board use the 4 extension pins new blue fuse with 1 = Serial1
- 100 is programming port on due
- 101 is native port on due. Us eit to support both ports at the same time!
*/
#define BLUETOOTH_SERIAL   -1                      // Port number (1..3) - For RADDS use 1
#define BLUETOOTH_BAUD     115200                 // communication speed


// Uncomment the following line if you are using Arduino compatible firmware made for Arduino version earlier then 1.0
// If it is incompatible you will get compiler errors about write functions not being compatible!
//#define COMPAT_PRE1

/* Define the type of axis movements needed for your printer. The typical case
is a full cartesian system where x, y and z moves are handled by separate motors.

0 = full cartesian system, xyz have separate motors.
1 = z axis + xy H-gantry (x_motor = x+y, y_motor = x-y)
2 = z axis + xy H-gantry (x_motor = x+y, y_motor = y-x)
3 = Delta printers (Rostock, Kossel, RostockMax, Cerberus, etc)
4 = Tuga printer (Scott-Russell mechanism)
5 = Bipod system (not implemented)
8 = y axis + xz H-gantry (x_motor = x+z, z_motor = x-z)
9 = y axis + xz H-gantry (x_motor = x+z, z_motor = z-x)
Cases 1, 2, 8 and 9 cover all needed xy and xz H gantry systems. If you get results mirrored etc. you can swap motor connections for x and y.
If a motor turns in the wrong direction change INVERT_X_DIR or INVERT_Y_DIR.
*/
#define DRIVE_SYSTEM CARTESIAN

/* You can write some GCODE to be executed on startup. Use this e.g. to set some 
pins. Separate multiple GCODEs with \n
*/
//#define STARTUP_GCODE ""


/*Bed Coating menu
 */
#define UI_BED_COATING 1
 
// ##########################################################################################
// ##                               Calibration                                            ##
// ##########################################################################################

/** Drive settings for the Delta printers
*/
#if DRIVE_SYSTEM == DELTA
    // ***************************************************
    // *** These parameter are only for Delta printers ***
    // ***************************************************

/** \brief Delta drive type: 0 - belts and pulleys, 1 - filament drive */
#define DELTA_DRIVE_TYPE 0

#if DELTA_DRIVE_TYPE == 0
/** \brief Pitch in mm of drive belt. GT2 = 2mm */
#define BELT_PITCH 2
/** \brief Number of teeth on X, Y and Z tower pulleys */
#define PULLEY_TEETH 20
#define PULLEY_CIRCUMFERENCE (BELT_PITCH * PULLEY_TEETH)
#elif DELTA_DRIVE_TYPE == 1
/** \brief Filament pulley diameter in millimeters */
#define PULLEY_DIAMETER 10
#define PULLEY_CIRCUMFERENCE (PULLEY_DIAMETER * 3.1415927)
#endif

/** \brief Steps per rotation of stepper motor */
#define STEPS_PER_ROTATION 200

/** \brief Micro stepping rate of X, Y and Y tower stepper drivers */
#define MICRO_STEPS 16

// Calculations
#define AXIS_STEPS_PER_MM ((float)(MICRO_STEPS * STEPS_PER_ROTATION) / PULLEY_CIRCUMFERENCE)
#define XAXIS_STEPS_PER_MM AXIS_STEPS_PER_MM
#define YAXIS_STEPS_PER_MM AXIS_STEPS_PER_MM
#define ZAXIS_STEPS_PER_MM AXIS_STEPS_PER_MM
#else
// *******************************************************
// *** These parameter are for all other printer types ***
// *******************************************************

/** Drive settings for printers with cartesian drive systems */
/** \brief Number of steps for a 1mm move in x direction.
For xy gantry use 2*belt moved!
Overridden if EEPROM activated. */
#define XAXIS_STEPS_PER_MM 80
/** \brief Number of steps for a 1mm move in y direction.
For xy gantry use 2*belt moved!
Overridden if EEPROM activated.*/
#define YAXIS_STEPS_PER_MM 80
/** \brief Number of steps for a 1mm move in z direction  Overridden if EEPROM activated.*/
#define ZAXIS_STEPS_PER_MM 2560
#endif

// ##########################################################################################
// ##                           Extruder configuration                                     ##
// ##########################################################################################

// You can use either PWM (pulse width modulation) or PDM (pulse density modulation) for
// extruders or coolers. PDM will give more signal changes per second, so on average it gives
// the cleaner signal. The only advantage of PWM is giving signals at a fixed rate and never more
// then PWM.
#define PDM_FOR_EXTRUDER 1
#if REPURPOSE_FAN_TO_COOL_EXTRUSIONS
#define PDM_FOR_COOLER 0
#else
#define PDM_FOR_COOLER 1
#endif

// The firmware checks if the heater and sensor got decoupled, which is dangerous. Since it will never reach target
// temperature, the heater will stay on for every which can burn your printer or house.
// As an additional barrier to your smoke detectors (I hope you have one above your printer) we now
// do some more checks to detect if something got wrong.

#if FEATURE_DECOUPLE_TEST
// If the temp. is on hold target, it may not sway more then this degrees celsius, or we mark
// sensor as defect.
#define DECOUPLING_TEST_MAX_HOLD_VARIANCE 15
// Minimum temp. rise we expect after the set duration of full heating is over.
// Always keep a good safety margin to get no false positives. If your period is e.g. 10 seconds
// because at startup you already need 7 seconds until heater starts to rise temp. for sensor
// then you have 3 seconds of increased heating to reach 1°„C.
#define DECOUPLING_TEST_MIN_TEMP_RISE 1
// Set to 1 if you want firmware to kill print on decouple
#define KILL_IF_SENSOR_DEFECT 1

#endif
// for each extruder, fan will stay on until extruder temperature is below this value
#define EXTRUDER_FAN_COOL_TEMP 50
// Retraction for sd pause over lcd
#define RETRACT_ON_PAUSE 2
// These commands get executed after storing position and going to park position.
#define PAUSE_START_COMMANDS "M117 SD Paused"
// These commands get executed before we go to stored position.
#define PAUSE_END_COMMANDS "M117 Printing ..."
/* Set to 1 if all extruders use the same heater block. Temp. control is then always
controlled by settings in extruder 0 definition. */
#define SHARED_EXTRUDER_HEATER 0
/* Speed in mm/s for extruder moves fom internal commands, e.g. switching extruder. */
#define EXTRUDER_SWITCH_XY_SPEED 100

#define EXT0_X_OFFSET 0
#define EXT0_Y_OFFSET 0
#define EXT0_Z_OFFSET 0
// for skeinforge 40 and later, steps to pull the plastic 1 mm inside the extruder, not out.  Overridden if EEPROM activated.
#define EXT0_STEPS_PER_MM 99 //425 // 825.698 //457
// What type of sensor is used?
// 1 is 100k thermistor (Epcos B57560G0107F000 - RepRap-Fab.org and many other)
// 2 is 200k thermistor
// 3 is mendel-parts thermistor (EPCOS G550)
// 4 is 10k thermistor
// 8 is ATC Semitec 104GT-2
// 13 is PT100 for E3D/Ultimaker
// 5 is userdefined thermistor table 0
// 6 is userdefined thermistor table 1
// 7 is userdefined thermistor table 2
// 12 is 100k RS thermistor 198-961
// 13 is PT100 for E3D/Ultimaker
// 14 is 100K NTC 3950
// 50 is userdefined thermistor table 0 for PTC thermistors
// 51 is userdefined thermistor table 0 for PTC thermistors
// 52 is userdefined thermistor table 0 for PTC thermistors
// 60 is AD8494, AD8495, AD8496 or AD8497 (5mV/degC and 1/4 the price of AD595 but only MSOT_08 package)
// 61 is AD8494, AD8495, AD8496 or AD8497 (5mV/degC and 1.25 Vref offset like Adafruit breakout)
// 97 Generic thermistor table 1
// 98 Generic thermistor table 2
// 99 Generic thermistor table 3
// 100 is AD595
// 101 is MAX6675
// 102 is MAX31855
#define EXT0_TEMPSENSOR_TYPE 5
// Analog input pin for reading temperatures or pin enabling SS for MAX6675
#define EXT0_TEMPSENSOR_PIN TEMP_0_PIN
// Which pin enables the heater
#define EXT0_HEATER_PIN HEATER_0_PIN
#define EXT0_STEP_PIN E0_STEP_PIN
#define EXT0_DIR_PIN E0_DIR_PIN
// set to false/true for normal / inverse direction
#if DAVINCI==0
#define EXT0_INVERSE false
#endif
#if DAVINCI==1 || DAVINCI==4
#define EXT0_INVERSE false
#endif
#if DAVINCI==2 || DAVINCI==3
#define EXT0_INVERSE true
#endif
#define EXT0_ENABLE_PIN E0_ENABLE_PIN
/* Set to 1 to mirror motor. Pins for mirrored motor are below */
#define EXT0_MIRROR_STEPPER 0
#define EXT0_STEP2_PIN E0_STEP_PIN
#define EXT0_DIR2_PIN E0_DIR_PIN
#define EXT0_INVERSE2 false
#define EXT0_ENABLE2_PIN E0_ENABLE_PIN

// For Inverting Stepper Enable Pins (Active Low) use 0, Non Inverting (Active High) use 1
#define EXT0_ENABLE_ON 0
// The following speed settings are for skeinforge 40+ where e is the
// length of filament pulled inside the heater. For repsnap or older
// skeinforge use higher values.
//  Overridden if EEPROM activated.
#define EXT0_MAX_FEEDRATE 50
// Feedrate from halted extruder in mm/s
//  Overridden if EEPROM activated.
#define EXT0_MAX_START_FEEDRATE 20
// Acceleration in mm/s^2
//  Overridden if EEPROM activated.
#define EXT0_MAX_ACCELERATION 5000
/** Type of heat manager for this extruder.
- 0 = Simply switch on/off if temperature is reached. Works always.
- 1 = PID Temperature control. Is better but needs good PID values. Defaults are a good start for most extruder.
- 3 = Dead-time control. PID_P becomes dead-time in seconds.
 Overridden if EEPROM activated.
*/
#define EXT0_HEAT_MANAGER 3
/** Wait x seconds, after reaching target temperature. Only used for M109.  Overridden if EEPROM activated. */
#define EXT0_WATCHPERIOD 1

/** \brief The maximum value, I-gain can contribute to the output.

A good value is slightly higher then the output needed for your temperature.
Values for starts:
130 => PLA for temperatures from 170-180 deg C
180 => ABS for temperatures around 240 deg C

The precise values may differ for different nozzle/resistor combination.
 Overridden if EEPROM activated.
*/
#define EXT0_PID_INTEGRAL_DRIVE_MAX 230
/** \brief lower value for integral part

The I state should converge to the exact heater output needed for the target temperature.
To prevent a long deviation from the target zone, this value limits the lower value.
A good start is 30 lower then the optimal value. You need to leave room for cooling.
 Overridden if EEPROM activated.
*/
#define EXT0_PID_INTEGRAL_DRIVE_MIN 40
/** P-gain.  Overridden if EEPROM activated. */
#define EXT0_PID_PGAIN_OR_DEAD_TIME   3
/** I-gain. Overridden if EEPROM activated.
*/
#define EXT0_PID_I   2
/** Dgain.  Overridden if EEPROM activated.*/
#define EXT0_PID_D 40
// maximum time the heater is can be switched on. Max = 255.  Overridden if EEPROM activated.
#define EXT0_PID_MAX 255
/** \brief Faktor for the advance algorithm. 0 disables the algorithm.  Overridden if EEPROM activated.
K is the factor for the quadratic term, which is normally disabled in newer versions. If you want to use
the quadratic factor make sure ENABLE_QUADRATIC_ADVANCE is defined.
L is the linear factor and seems to be working better then the quadratic dependency.
*/
#define EXT0_ADVANCE_K 0.0f
#define EXT0_ADVANCE_L 0.0f
/* Motor steps to remove backlash for advance algorithm. These are the steps
needed to move the motor cog in reverse direction until it hits the driving
cog. Direct drive extruder need 0. */
#define EXT0_ADVANCE_BACKLASH_STEPS 0
/** \brief Temperature to retract filament when extruder is heating up. Overridden if EEPROM activated.
*/
#define EXT0_WAIT_RETRACT_TEMP      150
/** \brief Units (mm/inches) to retract filament when extruder is heating up. Overridden if EEPROM activated. Set
to 0 to disable.
*/
#define EXT0_WAIT_RETRACT_UNITS     0

/** You can run any GCODE command on extruder deselect/select. Separate multiple commands with a new line \n.
That way you can execute some mechanical components needed for extruder selection or retract filament or whatever you need.
The codes are only executed for multiple extruder when changing the extruder. */
#define EXT0_SELECT_COMMANDS "M117 Extruder 1"
#define EXT0_DESELECT_COMMANDS ""
/** The extruder cooler is a fan to cool the extruder when it is heating. If you turn the extruder on, the fan goes on. */

#if DAVINCI==3
#define EXT0_EXTRUDER_COOLER_PIN ORIG_FAN2_PIN
#else
#define EXT0_EXTRUDER_COOLER_PIN ORIG_FAN_PIN
#endif
/** PWM speed for the cooler fan. 0=off 255=full speed */
#define EXT0_EXTRUDER_COOLER_SPEED 255
/** Time in ms between a heater action and test of success. Must be more then time between turning heater on and first temp. rise! */
#define EXT0_DECOUPLE_TEST_PERIOD 30000
/** Pin which toggles regualrly during extrusion allowing jam control. -1 = disabled */
#define EXT0_JAM_PIN -1
/** Pullup resistor for jam pin? */
#define EXT0_JAM_PULLUP false


// =========================== Configuration for second extruder ========================
#define EXT1_X_OFFSET -2852
#define EXT1_Y_OFFSET 12
#define EXT1_Z_OFFSET 0
// for skeinforge 40 and later, steps to pull the plasic 1 mm inside the extruder, not out.  Overridden if EEPROM activated.
#define EXT1_STEPS_PER_MM 99
// What type of sensor is used?
// 1 is 100k thermistor (Epcos B57560G0107F000 - RepRap-Fab.org and many other)
// 2 is 200k thermistor
// 3 is mendel-parts thermistor (EPCOS G550)
// 4 is 10k thermistor
// 5 is userdefined thermistor table 0
// 6 is userdefined thermistor table 1
// 7 is userdefined thermistor table 2
// 8 is ATC Semitec 104GT-2
// 50 is userdefined thermistor table 0 for PTC thermistors
// 51 is userdefined thermistor table 0 for PTC thermistors
// 52 is userdefined thermistor table 0 for PTC thermistors
// 60 is AD8494, AD8495, AD8496 or AD8497 (5mV/degC and 1/4 the price of AD595 but only MSOT_08 package)
// 61 is AD8494, AD8495, AD8496 or AD8497 (5mV/degC and 1.25 Vref offset like Adafruit breakout)
// 97 Generic thermistor table 1
// 98 Generic thermistor table 2
// 99 Generic thermistor table 3
// 100 is AD595
// 101 is MAX6675
#define EXT1_TEMPSENSOR_TYPE 6
// Analog input pin for reading temperatures or pin enabling SS for MAX6675
#define EXT1_TEMPSENSOR_PIN TEMP_2_PIN
// Which pin enables the heater
#define EXT1_HEATER_PIN HEATER_2_PIN
#define EXT1_STEP_PIN E1_STEP_PIN
#define EXT1_DIR_PIN E1_DIR_PIN
// set to false/true for normal/inverse direction
#define EXT1_INVERSE false
#define EXT1_ENABLE_PIN E1_ENABLE_PIN
// For Inverting Stepper Enable Pins (Active Low) use 0, Non Inverting (Active High) use 1
#define EXT1_ENABLE_ON false
/* Set to 1 to mirror motor. Pins for mirrored motor are below */
#define EXT1_MIRROR_STEPPER 0
#define EXT1_STEP2_PIN E0_STEP_PIN
#define EXT1_DIR2_PIN E0_DIR_PIN
#define EXT1_INVERSE2 false
#define EXT1_ENABLE2_PIN E0_ENABLE_PIN
// The following speed settings are for skeinforge 40+ where e is the
// length of filament pulled inside the heater. For repsnap or older
// skeinforge use higher values.
//  Overridden if EEPROM activated.
#define EXT1_MAX_FEEDRATE 50
// Feedrate from halted extruder in mm/s
//  Overridden if EEPROM activated.
#define EXT1_MAX_START_FEEDRATE 20
// Acceleration in mm/s^2
//  Overridden if EEPROM activated.
#define EXT1_MAX_ACCELERATION 5000
/** Type of heat manager for this extruder.
- 0 = Simply switch on/off if temperature is reached. Works always.
- 1 = PID Temperature control. Is better but needs good PID values. Defaults are a good start for most extruder.
 Overridden if EEPROM activated.
*/
#define EXT1_HEAT_MANAGER 3
/** Wait x seconds, after reaching target temperature. Only used for M109.  Overridden if EEPROM activated. */
#define EXT1_WATCHPERIOD 1

/** \brief The maximum value, I-gain can contribute to the output.

A good value is slightly higher then the output needed for your temperature.
Values for starts:
130 => PLA for temperatures from 170-180 deg C
180 => ABS for temperatures around 240 deg C

The precise values may differ for different nozzle/resistor combination.
 Overridden if EEPROM activated.
*/
#define EXT1_PID_INTEGRAL_DRIVE_MAX 230
/** \brief lower value for integral part

The I state should converge to the exact heater output needed for the target temperature.
To prevent a long deviation from the target zone, this value limits the lower value.
A good start is 30 lower then the optimal value. You need to leave room for cooling.
 Overridden if EEPROM activated.
*/
#define EXT1_PID_INTEGRAL_DRIVE_MIN 40
/** P-gain.  Overridden if EEPROM activated. */
#define EXT1_PID_PGAIN_OR_DEAD_TIME   3
/** I-gain.  Overridden if EEPROM activated.
*/
#define EXT1_PID_I   2
/** D-gain.  Overridden if EEPROM activated.*/
#define EXT1_PID_D 40
// maximum time the heater is can be switched on. Max = 255.  Overridden if EEPROM activated.
#define EXT1_PID_MAX 255
/** \brief Faktor for the advance algorithm. 0 disables the algorithm.  Overridden if EEPROM activated.
K is the factor for the quadratic term, which is normally disabled in newer versions. If you want to use
the quadratic factor make sure ENABLE_QUADRATIC_ADVANCE is defined.
L is the linear factor and seems to be working better then the quadratic dependency.
*/
#define EXT1_ADVANCE_K 0.0f
#define EXT1_ADVANCE_L 0.0f
/* Motor steps to remove backlash for advance algorithm. These are the steps
needed to move the motor cog in reverse direction until it hits the driving
cog. Direct drive extruder need 0. */
#define EXT1_ADVANCE_BACKLASH_STEPS 0

#define EXT1_WAIT_RETRACT_TEMP  150
#define EXT1_WAIT_RETRACT_UNITS 0
#define EXT1_SELECT_COMMANDS "M117 Extruder 2"
#define EXT1_DESELECT_COMMANDS ""
/** The extruder cooler is a fan to cool the extruder when it is heating. If you turn the extruder on, the fan goes on. */
#if DAVINCI==0
#define EXT1_EXTRUDER_COOLER_PIN ORIG_FAN_PIN
#endif
#if DAVINCI==1 || DAVINCI==4
#define EXT1_EXTRUDER_COOLER_PIN -1
#endif
#if DAVINCI==2
#define EXT1_EXTRUDER_COOLER_PIN ORIG_FAN_PIN
#endif
#if DAVINCI==3
#define EXT1_EXTRUDER_COOLER_PIN ORIG_FAN_PIN
#endif

/** PWM speed for the cooler fan. 0=off 255=full speed */
#define EXT1_EXTRUDER_COOLER_SPEED 255
/** Time in ms between a heater action and test of success. Must be more then time between turning heater on and first temp. rise! */
#define EXT1_DECOUPLE_TEST_PERIOD 30000
/** Pin which toggles regularly during extrusion allowing jam control. -1 = disabled */
#define EXT1_JAM_PIN -1
/** Pull-up resistor for jam pin? */
#define EXT1_JAM_PULLUP false

/** If enabled you can select the distance your filament gets retracted during a
M140 command, after a given temperature is reached. */
#define RETRACT_DURING_HEATUP true

/** Allow retraction with G10/G11 removing requirement for retraction setting in slicer. Also allows filament change if lcd is configured. */
#define FEATURE_RETRACTION 1
/** auto-retract converts pure extrusion moves into retractions. Beware that 
 simple extrusion e.g. over Repetier-Host will then not work! */
#define AUTORETRACT_ENABLED 0
#define RETRACTION_LENGTH 3
#define RETRACTION_LONG_LENGTH 13
#define RETRACTION_SPEED 40
#define RETRACTION_Z_LIFT 0
#define RETRACTION_UNDO_EXTRA_LENGTH 0
#define RETRACTION_UNDO_EXTRA_LONG_LENGTH 0
#define RETRACTION_UNDO_SPEED 20

/**
If you have a lcd display, you can do a filament switch with M600.
It will change the current extruders filament and temperature must already be high enough.
*/
#define FILAMENTCHANGE_X_POS 0
#define FILAMENTCHANGE_Y_POS 0
#define FILAMENTCHANGE_Z_ADD 1
/** Does a homing procedure after a filament change. This is good in case
you moved the extruder while changing filament during print.
0 = no homing, 1 = xy homing, 2 = xyz homing
*/
#define FILAMENTCHANGE_REHOME 1
/** Will first retract short distance, go to change position and then retract longretract.
Retractions speeds are taken from RETRACTION_SPEED and RETRACTION_UNDO_SPEED
*/
#define FILAMENTCHANGE_SHORTRETRACT 30
#define FILAMENTCHANGE_LONGRETRACT 30

/* Define how we detect jam/out of filament
   1 = Distance between signal changes increase
   2 = signal gets high
   3 = signal gets low
   
   2 and 3 are not jam detections, but only out of filament detection by a switch
   that changes the signal! 
*/
#define JAM_METHOD 1
// Steps normally needed for a full signal cycle.
#define JAM_STEPS 220
// Steps for reducing speed. Must be higher then JAM_STEPS
#define JAM_SLOWDOWN_STEPS 380
// New speed multiplier which gets set when slowdown is reached.
#define JAM_SLOWDOWN_TO 70
// Last fallback. If we slip this much, we want to pause.
#define JAM_ERROR_STEPS 430
/** To prevent signal bouncing, only consider changes if we are this much steps
 away from last signal change. */ 
#define JAM_MIN_STEPS 10
/*
Determine what should be done if a jam is detected
0 : Nothing, just mark extruder as jammed.
1 : Jam/out of filament dialog and block communication.
2 : Message to host/server otherwise continue and mark extruder jammed
*/
#define JAM_ACTION 1

/** PID control only works target temperature +/- PID_CONTROL_RANGE.
If you get much overshoot at the first temperature set, because the heater is going full power too long, you
need to increase this value. For one 6.8 Ohm heater 10 is ok. With two 6.8 Ohm heater use 15.
*/
#define PID_CONTROL_RANGE 20

/** Prevent extrusions longer then x mm for one command. This is especially important if you abort a print. Then the
extrusion position might be at any value like 23344. If you then have an G1 E-2 it will roll back 23 meter! */
#define EXTRUDE_MAXLENGTH 100
/** Skip wait, if the extruder temperature is already within x degrees. Only fixed numbers, 0 = off */
#define SKIP_M109_IF_WITHIN 2

/** \brief Set PID scaling

PID values assume a usable range from 0-255. This can be further limited to EXT0_PID_MAX by to methods.
Set the value to 0: Normal computation, just clip output to EXT0_PID_MAX if computed value is too high.
Set value to 1: Scale PID by EXT0_PID_MAX/256 and then clip to EXT0_PID_MAX.
If your EXT0_PID_MAX is low, you should prefer the second method.
*/
#define SCALE_PID_TO_MAX 0

#define HEATER_PWM_SPEED 1 // How fast ist pwm signal 0 = 15.25Hz, 1 = 30.51Hz, 2 = 61.03Hz, 3 = 122.06Hz

/** Temperature range for target temperature to hold in M109 command. 5 means +/-5 degC

Uncomment define to force the temperature into the range for given watch period.
*/
//#define TEMP_HYSTERESIS 5

/** Userdefined thermistor table

There are many different thermistors, which can be combined with different resistors. This result
in unpredictable number of tables. As a resolution, the user can define one table here, that can
be used as type 5 for thermistor type in extruder/heated bed definition. Make sure, the number of entries
matches the value in NUM_TEMPS_USERTHERMISTOR0. If you span definition over multiple lines, make sure to end
each line, except the last, with a backslash. The table format is {{adc1,temp1},{adc2,temp2}...} with
increasing adc values. For more informations, read
http://hydraraptor.blogspot.com/2007/10/measuring-temperature-easy-way.html

If you have a sprinter temperature table, you have to multiply the first value with 4 and the second with 8.
This firmware works with increased precision, so the value reads go from 0 to 4095 and the temperature is
temperature*8.

If you have a PTC thermistor instead of a NTC thermistor, keep the adc values increasing and use thermistor types 50-52 instead of 5-7!
*/
/** Number of entries in the user thermistor table 0. Set to 0 to disable it. */

#if MODEL==0
  #define NUM_TEMPS_USERTHERMISTOR0 33
  #define USER_THERMISTORTABLE0 {{96,2400},{99,2320},{113,2240},{132,2160},{155,2080},{180,2000},{211,1920},{247,1840},{293,1760},{350,1680},{421,1600},{508,1520},{611,1440},{732,1360},{871,1280},{1024,1200},{1192,1120},{1369,1040},{1552,960},{1737,880},{1900,800},{2070,720},{2219,640},{2361,560},{2478,480},{2565,400},{2628,320},{2673,240},{2710,160},{2746,80},{2783,0},{2824,-80},{2864,-160}}  
#else
  #define NUM_TEMPS_USERTHERMISTOR0 28
  #define USER_THERMISTORTABLE0 {{294, 2560},{375, 2400},{461, 2272},{526, 2184},{601, 2104},{674, 2048},{811, 1928},{925, 1848},{1071, 1768},{1219, 1696},{1445, 1584},{1673, 1496},{1902, 1416},{2187, 1312},{2454, 1224},{2672, 1152},{3000, 1048},{3196, 968},{3439, 864},{3583, 784},{3736, 680},{3899, 536},{3960, 448},{4024, 336},{4067, 192},{4079, 156},{4100, 0},{4120, -160}}
#endif

/* 
 *  Temperature Sensor for bed  
 */
/** Number of entries in the user thermistor table 1. Set to 0 to disable it. */
//#define NUM_TEMPS_USERTHERMISTOR1 0

//#define NUM_TEMPS_USERTHERMISTOR1 19
//#define USER_THERMISTORTABLE1 {{628,1280},{859,1200},{1113,1120},{1382,1040},{1660,960},{1938,880},{2211,800},{2473,720},{2718,640},{2945,560},{3148,480},{3328,400},{3482,320},{3613,240},{3722,160},{3815,80},{3895,0},{3972,-80},{4055,-160}}
/* New TC for bed */
#define NUM_TEMPS_USERTHERMISTOR1 19
#define USER_THERMISTORTABLE1 {{191,1280},{234,1200},{289,1120},{359,1040},{450,960},{566,880},{715,800},{903,720},{1138,640},{1425,560},{1760,480},{2134,400},{2525,320},{2904,240},{3242,160},{3520,80},{3730,0},{3876,-80},{3972,-160}}


  // Custom table for DaVinci 1.0 with ATC semitec 104GT-2 thermistor and parallel R1=10kohm,
  // series R2=4.7kohm with resistor values taken from http://www.atcsemitec.co.uk/gt-2-glass-thermistors.html.
  // Table is computed with included Dv10-E3Dv6-ThermistorTable.py.
  // Turn on by setting EXT0_TEMPSENSOR_TYPE to 7 above. 
  //#define NUM_TEMPS_USERTHERMISTOR2 33
  //#define USER_THERMISTORTABLE2 {{69,2400},{79,2320},{91,2240},{105,2160},{123,2080},{144,2000},{169,1920},{200,1840},{237,1760},{282,1680},{337,1600},{403,1520},{484,1440},{581,1360},{696,1280},{832,1200},{989,1120},{1165,1040},{1359,960},{1563,880},{1769,800},{1968,720},{2150,640},{2308,560},{2440,480},{2544,400},{2622,320},{2678,240},{2718,160},{2744,80},{2761,0},{2772,-80},{2779,-160}}
/** Number of entries in the user thermistor table 2. Set to 0 to disable it. */
#define NUM_TEMPS_USERTHERMISTOR2 0


/** If defined, creates a thermistor table at startup.

If you don't feel like computing the table on your own, you can use this generic method. It is
a simple approximation which may be not as accurate as a good table computed from the reference
values in the datasheet. You can increase precision if you use a temperature/resistance for
R0/T0, which is near your operating temperature. This will reduce precision for lower temperatures,
which are not really important. The resistors must fit the following schematic:
@code
VREF ---- R2 ---+--- Termistor ---+-- GND
                |                 |
                +------ R1 -------+
                |                 |
                +---- Capacitor --+
                |
                V measured
@endcode

If you don't have R1, set it to 0.
The capacitor is for reducing noise from long thermistor cable. If you don't have one, it's OK.

If you need the generic table, uncomment the following define.
*/
//#define USE_GENERIC_THERMISTORTABLE_1

/* Some examples for different thermistors:

EPCOS B57560G104+ : R0 = 100000  T0 = 25  Beta = 4036
EPCOS 100K Thermistor (B57560G1104F) :  R0 = 100000  T0 = 25  Beta = 4092
ATC Semitec 104GT-2 : R0 = 100000  T0 = 25  Beta = 4267
Honeywell 100K Thermistor (135-104LAG-J01)  : R0 = 100000  T0 = 25  Beta = 3974

*/

/** Reference Temperature */
#define GENERIC_THERM1_T0 25
/** Resistance at reference temperature */
#define GENERIC_THERM1_R0 100000
/** Beta value of thermistor

You can use the beta from the datasheet or compute it yourself.
See http://reprap.org/wiki/MeasuringThermistorBeta for more details.
*/
#define GENERIC_THERM1_BETA 4036
/** Start temperature for generated thermistor table */
#define GENERIC_THERM1_MIN_TEMP -20
/** End Temperature for generated thermistor table */
#define GENERIC_THERM1_MAX_TEMP 300
#define GENERIC_THERM1_R1 0
#define GENERIC_THERM1_R2 4700

// The same for table 2 and 3 if needed

// #define USE_GENERIC_THERMISTORTABLE_2
#define GENERIC_THERM2_R0 100000
#define GENERIC_THERM2_T0 25
#define GENERIC_THERM2_BETA 3950
#define GENERIC_THERM2_MIN_TEMP -20
#define GENERIC_THERM2_MAX_TEMP 300
#define GENERIC_THERM2_R1 0
#define GENERIC_THERM2_R2 4700

//#define USE_GENERIC_THERMISTORTABLE_3
#define GENERIC_THERM3_T0 170
#define GENERIC_THERM3_R0 1042.7
#define GENERIC_THERM3_BETA 4036
#define GENERIC_THERM3_MIN_TEMP -20
#define GENERIC_THERM3_MAX_TEMP 300
#define GENERIC_THERM3_R1 0
#define GENERIC_THERM3_R2 4700

/** Supply voltage to ADC, can be changed by setting ANALOG_REF below to different value. */
#define GENERIC_THERM_VREF 5
/** Number of entries in generated table. One entry takes 4 bytes. Higher number of entries increase computation time too.
Value is used for all generic tables created. */
#define GENERIC_THERM_NUM_ENTRIES 33

// uncomment the following line for MAX6675 support.
//#define SUPPORT_MAX6675
// uncomment the following line for MAX31855 support.
//#define SUPPORT_MAX31855

// ############# Heated bed configuration ########################

/** \brief Set true if you have a heated bed conected to your board, false if not */
#define HAVE_HEATED_BED true

#define HEATED_BED_MAX_TEMP 130
/** Skip M190 wait, if heated bed is already within x degrees. Fixed numbers only, 0 = off. */
#define SKIP_M190_IF_WITHIN 5

// Select type of your heated bed. It's the same as for EXT0_TEMPSENSOR_TYPE
// set to 0 if you don't have a heated bed
#define HEATED_BED_SENSOR_TYPE 6
/** Analog pin of analog sensor to read temperature of heated bed.  */
#define HEATED_BED_SENSOR_PIN TEMP_1_PIN
/** \brief Pin to enable heater for bed. */
#define HEATED_BED_HEATER_PIN HEATER_1_PIN
// How often the temperature of the heated bed is set (msec)
#define HEATED_BED_SET_INTERVAL 5000

/**
Heat manager for heated bed:
0 = Bang Bang, fast update
1 = PID controlled
2 = Bang Bang, limited check every HEATED_BED_SET_INTERVAL. Use this with relay-driven beds to save life time
3 = dead time control
*/
#define HEATED_BED_HEAT_MANAGER 2
/** \brief The maximum value, I-gain can contribute to the output.
The precise values may differ for different nozzle/resistor combination.
 Overridden if EEPROM activated.
*/
#define HEATED_BED_PID_INTEGRAL_DRIVE_MAX 255
/** \brief lower value for integral part

The I state should converge to the exact heater output needed for the target temperature.
To prevent a long deviation from the target zone, this value limits the lower value.
A good start is 30 lower then the optimal value. You need to leave room for cooling.
 Overridden if EEPROM activated.
*/
#define HEATED_BED_PID_INTEGRAL_DRIVE_MIN 80
/** P-gain.  Overridden if EEPROM activated. */
#define HEATED_BED_PID_PGAIN_OR_DEAD_TIME   196
/** I-gain  Overridden if EEPROM activated.*/
#define HEATED_BED_PID_IGAIN   33.0
/** Dgain.  Overridden if EEPROM activated.*/
#define HEATED_BED_PID_DGAIN 290
// maximum time the heater can be switched on. Max = 255.  Overridden if EEPROM activated.
#define HEATED_BED_PID_MAX 255
// Time to see a temp. change when fully heating. Consider that beds at higher temp. need longer to rise and cold
// beds need some time to get the temp. to the sensor. Time is in milliseconds!
#define HEATED_BED_DECOUPLE_TEST_PERIOD 300000

// When temperature exceeds max temp, your heater will be switched off.
// This feature exists to protect your hotend from overheating accidentally, but *NOT* from thermistor short/failure!
#define MAXTEMP 270

/** Extreme values to detect defect thermistors. */
#define MIN_DEFECT_TEMPERATURE -10
#define MAX_DEFECT_TEMPERATURE 290

// ##########################################################################################
// ##                             Laser configuration                                      ##
// ##########################################################################################

/*
If the firmware is in laser mode, it can control a laser output to cut or engrave materials.
Please use this feature only if you know about safety and required protection. Lasers are
dangerous and can hurt or make you blind!!!

The default laser driver only supports laser on and off. Here you control the intensity with
your feedrate. For exchangeable diode lasers this is normally enough. If you need more control
you can set the intensity in a range 0-255 with a custom extension to the driver. See driver.h
and comments on how to extend the functions non invasive with our event system.

If you have a laser - powder system you will like your E override. If moves contain a 
increasing extruder position it will laser that move. With this trick you can
use existing FDM slicers to laser the output. Laser width is extrusion width.

Other tools may use M3 and M5 to enable/disable laser. Here G1/G2/G3 moves have laser enabled
and G0 moves have it disables.

In any case, laser only enables while moving. At the end of a move it gets
automatically disabled. 
*/

#define SUPPORT_LASER 0 // set 1 to enable laser support
#define LASER_PIN -1    // set to pin enabling laser
#define LASER_ON_HIGH 1 // Set 0 if low signal enables laser

// ##########################################################################################
// ##                              CNC configuration                                       ##
// ##########################################################################################

/*
If the firmware is in CNC mode, it can control a mill with M3/M4/M5. It works 
similar to laser mode, but mill keeps enabled during G0 moves and it allows
setting rpm (only with event extension that supports this) and milling direction.
It also can add a delay to wait for spindle to run on full speed.
*/

#define SUPPORT_CNC 0 // Set 1 for CNC support
#define CNC_WAIT_ON_ENABLE 300 // wait x milliseconds after enabling
#define CNC_WAIT_ON_DISABLE 0 // delay in milliseconds after disabling spindle. May be required for direction changes.
#define CNC_ENABLE_PIN -1 // Pin to enable mill
#define CNC_ENABLE_WITH 1 // Set 0 if low enables spindle
#define CNC_DIRECTION_PIN -1 // Set to pin if direction control is possible
#define CNC_DIRECTION_CW 1 // Set signal required for clockwise rotation


/* Select the default mode when the printer gets enables. Possible values are
PRINTER_MODE_FFF 0
PRINTER_MODE_LASER 1
PRINTER_MODE_CNC 2
*/
#define DEFAULT_PRINTER_MODE PRINTER_MODE_FFF

// ##########################################################################################
// ##                            Endstop configuration                                     ##
// ##########################################################################################

/* By default all endstops are pulled up to HIGH. You need a pull-up if you
use a mechanical endstop connected with GND. Set value to false for no pull-up
on this endstop.
*/
#define ENDSTOP_PULLUP_X_MIN false
#define ENDSTOP_PULLUP_Y_MIN false
#define ENDSTOP_PULLUP_Z_MIN false
#define ENDSTOP_PULLUP_X_MAX true
#define ENDSTOP_PULLUP_Y_MAX true
#define ENDSTOP_PULLUP_Z_MAX true

// Set to true to invert the logic of the endstops
#define ENDSTOP_X_MIN_INVERTING false
#define ENDSTOP_Y_MIN_INVERTING false
#define ENDSTOP_Z_MIN_INVERTING false
#define ENDSTOP_X_MAX_INVERTING true
#define ENDSTOP_Y_MAX_INVERTING true
#define ENDSTOP_Z_MAX_INVERTING true

// Set the values true where you have a hardware endstop. The Pin number is taken from pins.h.

#define MIN_HARDWARE_ENDSTOP_X true
#define MIN_HARDWARE_ENDSTOP_Y true
#define MIN_HARDWARE_ENDSTOP_Z true
#define MAX_HARDWARE_ENDSTOP_X false
#define MAX_HARDWARE_ENDSTOP_Y false
#define MAX_HARDWARE_ENDSTOP_Z false

//If your axes are only moving in one direction, make sure the endstops are connected properly.
//If your axes move in one direction ONLY when the endstops are triggered, set ENDSTOPS_INVERTING to true here



//// ADVANCED SETTINGS - to tweak parameters

// For Inverting Stepper Enable Pins (Active Low) use 0, Non Inverting (Active High) use 1
#define X_ENABLE_ON 0
#define Y_ENABLE_ON 0
#define Z_ENABLE_ON 0

// Disables axis when it's not being used.
#define DISABLE_X false
#define DISABLE_Y false
#define DISABLE_Z false
#define DISABLE_E false
/* If you want to keep z motor running on stepper timeout, remove comments below.
  This may be useful if your z bed moves when motors are disabled. Will still
  turn z off when heaters get also disabled. 
*/
//#define PREVENT_Z_DISABLE_ON_STEPPER_TIMEOUT

// Inverting axis direction
#define INVERT_X_DIR true
#define INVERT_Y_DIR false
#define INVERT_Z_DIR true

//// ENDSTOP SETTINGS:
// Sets direction of endstops when homing; 1=MAX, -1=MIN
#define X_HOME_DIR -1
#define Y_HOME_DIR -1
#define Z_HOME_DIR -1

// Delta robot radius endstop
#define max_software_endstop_r true

//If true, axis won't move to coordinates less than zero.
#define min_software_endstop_x false
#define min_software_endstop_y false
#define min_software_endstop_z false

//If true, axis won't move to coordinates greater than the defined lengths below.
#define max_software_endstop_x true
#define max_software_endstop_y true
#define max_software_endstop_z true

// If during homing the endstop is reached, ho many mm should the printer move back for the second try
#define ENDSTOP_X_BACK_MOVE 5
#define ENDSTOP_Y_BACK_MOVE 5
#define ENDSTOP_Z_BACK_MOVE 2

// For higher precision you can reduce the speed for the second test on the endstop
// during homing operation. The homing speed is divided by the value. 1 = same speed, 2 = half speed
#define ENDSTOP_X_RETEST_REDUCTION_FACTOR 3
#define ENDSTOP_Y_RETEST_REDUCTION_FACTOR 3
//Davinci Specific, bad noise if set to 3
#define ENDSTOP_Z_RETEST_REDUCTION_FACTOR 4

// When you have several endstops in one circuit you need to disable it after homing by moving a
// small amount back. This is also the case with H-belt systems.

#if DAVINCI==0
#define ENDSTOP_X_BACK_ON_HOME 0
#define ENDSTOP_Y_BACK_ON_HOME 0
#define ENDSTOP_Z_BACK_ON_HOME 0
#endif 

#if DAVINCI==1 || DAVINCI==4
#define ENDSTOP_X_BACK_ON_HOME 0
#define ENDSTOP_Y_BACK_ON_HOME 0
#define ENDSTOP_Z_BACK_ON_HOME 0
#endif 

#if DAVINCI==2 || DAVINCI==3
#define ENDSTOP_X_BACK_ON_HOME 0
//to avoid to hit plate when homing
#define ENDSTOP_Y_BACK_ON_HOME 7
#define ENDSTOP_Z_BACK_ON_HOME 0
#endif


// You can disable endstop checking for print moves. This is needed, if you get sometimes
// false signals from your endstops. If your endstops don't give false signals, you
// can set it on for safety.
//Davinci, specific : Home sensors are easy to get noise an make print to lift, especially on 1.0A/2.0A, so disable it as no need to check home position all the time
#define ALWAYS_CHECK_ENDSTOPS 0

// maximum positions in mm - only fixed numbers!
// For delta robot Z_MAX_LENGTH is the maximum travel of the towers and should be set to the distance between the hotend
// and the platform when the printer is at its home position.
// If EEPROM is enabled these values will be overridden with the values in the EEPROM
#if DAVINCI==0
#define X_MAX_LENGTH 237 - ENDSTOP_X_BACK_ON_HOME
#define Y_MAX_LENGTH 217 - ENDSTOP_Y_BACK_ON_HOME
#define Z_MAX_LENGTH 190 - ENDSTOP_Z_BACK_ON_HOME
#endif

#if DAVINCI==1
#if MODEL==0
#define Y_MAX_LENGTH 217 - ENDSTOP_Y_BACK_ON_HOME
#else
#define Y_MAX_LENGTH 215 - ENDSTOP_Y_BACK_ON_HOME
#endif
#define X_MAX_LENGTH 237 - ENDSTOP_X_BACK_ON_HOME
#define Z_MAX_LENGTH 200 - ENDSTOP_Z_BACK_ON_HOME
#endif

#if DAVINCI==2 || DAVINCI==3
#define X_MAX_LENGTH 199 - ENDSTOP_X_BACK_ON_HOME
#define Y_MAX_LENGTH 211 - ENDSTOP_Y_BACK_ON_HOME
#define Z_MAX_LENGTH 200 - ENDSTOP_Z_BACK_ON_HOME
#endif

#if DAVINCI==4
#define X_MAX_LENGTH 223.60 - ENDSTOP_X_BACK_ON_HOME
#define Y_MAX_LENGTH 220.60 - ENDSTOP_Y_BACK_ON_HOME
#define Z_MAX_LENGTH 190 - ENDSTOP_Z_BACK_ON_HOME
#endif

// Coordinates for the minimum axis. Can also be negative if you want to have the bed start at 0 and the printer can go to the left side
// of the bed. Maximum coordinate is given by adding the above X_MAX_LENGTH values.
#if DAVINCI==1
#define X_MIN_POS -33
#define Y_MIN_POS -12
#define Z_MIN_POS 0
#endif

#if DAVINCI==2 || DAVINCI==3
#define X_MIN_POS 0
#define Y_MIN_POS 0
#define Z_MIN_POS 0
#endif

#if DAVINCI==4
#define X_MIN_POS -14.60
#define Y_MIN_POS -12.60
#define Z_MIN_POS 0
#endif

#if DAVINCI==0
#define X_MIN_POS 0
#define Y_MIN_POS 0
#define Z_MIN_POS 0
#endif

//Unload Position
#if DAVINCI==0 
#define UNLOAD_POS_E0_X 0
#define UNLOAD_POS_E0_Y 0
#define UNLOAD_POS_E1_X 0
#define UNLOAD_POS_E1_Y 0
#endif
#if DAVINCI==1 //cleaner of Davinci 1.0 is not in same position of 2.0 neither AiO
#if MODEL == 0
    #define UNLOAD_POS_E0_X X_MIN_POS
    #define UNLOAD_POS_E0_Y Y_MIN_POS
    #define UNLOAD_POS_E1_X X_MIN_POS
    #define UNLOAD_POS_E1_Y Y_MIN_POS
#else
    #define UNLOAD_POS_E0_X X_MIN_POS
    #define UNLOAD_POS_E0_Y Y_MIN_POS
    #define UNLOAD_POS_E1_X X_MIN_POS
    #define UNLOAD_POS_E1_Y Y_MIN_POS
#endif
#endif
#if DAVINCI==2 || DAVINCI==3
#if MODEL == 0
    #define UNLOAD_POS_E0_X 199
    #define UNLOAD_POS_E0_Y Y_MIN_POS
    #define UNLOAD_POS_E1_X X_MIN_POS
    #define UNLOAD_POS_E1_Y Y_MIN_POS
#else
    #define UNLOAD_POS_E0_X 195
    #define UNLOAD_POS_E0_Y Y_MIN_POS+27
    #define UNLOAD_POS_E1_X X_MIN_POS
    #define UNLOAD_POS_E1_Y Y_MIN_POS+27
#endif
#endif
#if DAVINCI==4
#define UNLOAD_POS_E0_X 0
#define UNLOAD_POS_E0_Y 0
#endif



// ##########################################################################################
// ##                           Movement settings                                          ##
// ##########################################################################################

// Microstep setting (Only functional when stepper driver microstep pins are connected to MCU. Currently only works for RAMBO boards
#define MICROSTEP_MODES {8,8,8,8,8} // [1,2,4,8,16]

// Motor Current setting (Only functional when motor driver current ref pins are connected to a digital trimpot on supported boards)
#if MOTHERBOARD==301
//#define MOTOR_CURRENT {135,135,135,135,135} // Values 0-255 (RAMBO 135 = ~0.75A, 185 = ~1A)
#define MOTOR_CURRENT_PERCENT {53,53,53,53,53}
#elif MOTHERBOARD==12
//#define MOTOR_CURRENT {35713,35713,35713,35713,35713} // Values 0-65535 (3D Master 35713 = ~1A)
#define MOTOR_CURRENT_PERCENT {55,55,55,55,55}
#elif (MOTHERBOARD==500) || (MOTHERBOARD==501) // Alligator boards
//#define MOTOR_CURRENT {130,130,130,110,110,110,110} // expired method
#define MOTOR_CURRENT_PERCENT {51,51,51,44,44,44,44}
#endif

/** \brief Number of segments to generate for delta conversions per second of move
*/
#define DELTA_SEGMENTS_PER_SECOND_PRINT 600 // Move accurate setting for print moves
#define DELTA_SEGMENTS_PER_SECOND_MOVE 600 // Less accurate setting for other moves

// Delta settings
#if DRIVE_SYSTEM == DELTA
/** \brief Delta rod length (mm)
*/
#define DELTA_DIAGONAL_ROD 345 // mm


/*  =========== Parameter essential for delta calibration ===================

            C, Y-Axis
            |                        |___| CARRIAGE_HORIZONTAL_OFFSET (recommend set it to 0)
            |                        |   \------------------------------------------
            |_________ X-axis        |    \                                        |
           / \                       |     \  DELTA_DIAGONAL_ROD (length)    Each move this Rod Height
          /   \                             \                                 is calculated
         /     \                             \    Carriage is at printer center!   |
         A      B                             \_____/--------------------------------
                                              |--| END_EFFECTOR_HORIZONTAL_OFFSET (recommend set it to 0)
                                         |----| ROD_RADIUS (Horizontal rod pivot to pivot measure)
                                     |-----------| PRINTER_RADIUS (recommend set it to ROD_RADIUS)

    Column angles are measured from X-axis counterclockwise
    "Standard" positions: alpha_A = 210, alpha_B = 330, alpha_C = 90
*/

/** \brief column positions - change only to correct build imperfections! */
#define DELTA_ALPHA_A 210
#define DELTA_ALPHA_B 330
#define DELTA_ALPHA_C 90

/** Correct radius by this value for each column. Perfect builds have 0 everywhere. */
#define DELTA_RADIUS_CORRECTION_A 0
#define DELTA_RADIUS_CORRECTION_B 0
#define DELTA_RADIUS_CORRECTION_C 0

/** Correction of the default diagonal size. Value gets added.*/
#define DELTA_DIAGONAL_CORRECTION_A 0
#define DELTA_DIAGONAL_CORRECTION_B 0
#define DELTA_DIAGONAL_CORRECTION_C 0

/** Max. radius (mm) the printer should be able to reach. */
#define DELTA_MAX_RADIUS 200

// Margin (mm) to avoid above tower minimum (xMin xMinsteps)
// If your printer can put its carriage low enough the rod is horizontal without hitting the floor
// set this to zero. Otherwise, measure how high the carriage is from horizontal rod
// Also, movement speeds are 10x to 20x cartesian speeds at tower bottom.
// You may need to leave a few mm for safety.
// Hitting floor at high speed can damage your printer (motors, drives, etc)
// THIS MAY NEED UPDATING IF THE HOT END HEIGHT CHANGES!
#define DELTA_FLOOR_SAFETY_MARGIN_MM 15

/** \brief Horizontal offset of the universal joints on the end effector (moving platform).
*/
#define END_EFFECTOR_HORIZONTAL_OFFSET 0

/** \brief Horizontal offset of the universal joints on the vertical carriages.
*/
#define CARRIAGE_HORIZONTAL_OFFSET 0

/** \brief Printer radius in mm,
  measured from the center of the print area to the vertical smooth tower.
  Alternately set this to the pivot to pivot horizontal rod distance, when head is at (0,0)
*/
#define PRINTER_RADIUS 265.25

/* ========== END Delta calibration data ==============*/

/** When true the delta will home to z max when reset/powered over cord. That way you start with well defined coordinates.
If you don't do it, make sure to home first before your first move.
*/
#define DELTA_HOME_ON_POWER 0

/** To allow software correction of misaligned endstops, you can set the correction in steps here. If you have EEPROM enabled
you can also change the values online and autoleveling will store the results here. */
#define DELTA_X_ENDSTOP_OFFSET_STEPS 0
#define DELTA_Y_ENDSTOP_OFFSET_STEPS 0
#define DELTA_Z_ENDSTOP_OFFSET_STEPS 0

#endif
// ========== Tuga special settings =============
#if DRIVE_SYSTEM==TUGA
/* Radius of the long arm in mm. */
#define DELTA_DIAGONAL_ROD 240
#endif

/** \brief Number of delta moves in each line. Moves that exceed this figure will be split into multiple lines.
Increasing this figure can use a lot of memory since 7 bytes * size of line buffer * MAX_SELTA_SEGMENTS_PER_LINE
will be allocated for the delta buffer.
PrintLine PrintLine::lines[PRINTLINE_CACHE_SIZE (default 16?)];
Printline is about 200 bytes + 7 * DELTASEGMENTS_PER_PRINTLINE
or 16 * (200 + (7*22=154) = 354) = 5664 bytes! !1
min is 5 * (200 + (7*10=70) =270) = 1350
 This leaves ~1K free RAM on an Arduino which has only 8k
Mega. Used only for nonlinear systems like delta or tuga. */
#define DELTASEGMENTS_PER_PRINTLINE 22

/** After x seconds of inactivity, the stepper motors are disabled.
    Set to 0 to leave them enabled.
    This helps cooling the Stepper motors between two print jobs.
    Overridden if EEPROM activated.
*/
#define STEPPER_INACTIVE_TIME 360
/** After x seconds of inactivity, the system will go down as far it can.
    It will at least disable all stepper motors and heaters. If the board has
    a power pin, it will be disabled, too.
    Set value to 0 for disabled.
    Overridden if EEPROM activated.
*/
#define MAX_INACTIVE_TIME 0L
/** Maximum feedrate, the system allows. Higher feedrates are reduced to these values.
    The axis order in all axis related arrays is X, Y, Z
     Overridden if EEPROM activated.
    */
#define MAX_FEEDRATE_X 200
#define MAX_FEEDRATE_Y 200
#define MAX_FEEDRATE_Z 5

/** Home position speed in mm/s. Overridden if EEPROM activated. */
#define HOMING_FEEDRATE_X 40
#define HOMING_FEEDRATE_Y 40
#define HOMING_FEEDRATE_Z 4

/** Set order of axis homing. Use HOME_ORDER_XYZ and replace XYZ with your order. 
 * If you measure Z with your extruder tip you need a hot extruder to get right measurement. In this
 * case set HOME_ORDER_ZXYTZ and also define ZHOME_HEAT_HEIGHT and ZHOME_MIN_TEMPERATURE. It will do
 * first a z home to get some reference, then raise to ZHOME_HEAT_HEIGHT do xy homing and then after
 * heating to minimum ZHOME_MIN_TEMPERATURE will z home again for correct height.   
 * */
#define HOMING_ORDER HOME_ORDER_XYZ
// Used for homing order HOME_ORDER_ZXYTZ
#define ZHOME_MIN_TEMPERATURE 0
// needs to heat all extruders (1) or only current extruder (0)
#define ZHOME_HEAT_ALL 1 
// Z-height for heating extruder during homing
#define ZHOME_HEAT_HEIGHT 20
// If your bed might bend while probing, because your sensor is the extruder tip
// you can define a predefined x,y position so beding is always the same and
// can be compensated. Set coordinate to 999999 to ignore positions and just
// use the position you are at.
#define ZHOME_X_POS IGNORE_COORDINATE
#define ZHOME_Y_POS IGNORE_COORDINATE

/* If you have a backlash in both z-directions, you can use this. For most printer, the bed will be pushed down by it's
own weight, so this is nearly never needed. */
#define ENABLE_BACKLASH_COMPENSATION 0
#define Z_BACKLASH 0
#define X_BACKLASH 0
#define Y_BACKLASH 0

/** Comment this to disable ramp acceleration */
#define RAMP_ACCELERATION 1

/** If your stepper needs a longer high signal then given, you can add a delay here.
The delay is realized as a simple loop wasting time, which is not available for other
computations. So make it as low as possible. For the most common drivers no delay is needed, as the
included delay is already enough.
*/
#define STEPPER_HIGH_DELAY 0

/** If your driver needs some additional delay between setting direction and first step signal,
 you can set this here. There are some commands between direction and signal, but some drivers
 might be even slower or you are using a fast Arduino board with slow driver. Normally 0 works.
 If you get skewed print, you might try 1 microsecond here.
 */
#define DIRECTION_DELAY 0

/** The firmware can only handle 16000Hz interrupt frequency cleanly. If you need higher speeds
a faster solution is needed, and this is to double/quadruple the steps in one interrupt call.
This is like reducing your 1/16th microstepping to 1/8 or 1/4. It is much cheaper then 1 or 3
additional stepper interrupts with all it's overhead. As a result you can go as high as
40000Hz.
*/
#define STEP_DOUBLER_FREQUENCY 80000
/** If you need frequencies off more then 30000 you definitely need to enable this. If you have only 1/8 stepping
enabling this may cause to stall your moves when 20000Hz is reached.
*/
#define ALLOW_QUADSTEPPING 1
/** If you reach STEP_DOUBLER_FREQUENCY the firmware will do 2 or 4 steps with nearly no delay. That can be too fast
for some printers causing an early stall.

*/
#define DOUBLE_STEP_DELAY 1 // time in microseconds

/** If the firmware is busy, it will send a busy signal to host signaling that
 everything is fine and it only takes a bit longer to finish. That way the 
 host can keep timeout short so in case of communication errors the resulting
 blobs are much smaller. Set to 0 to disable it. */
#define KEEP_ALIVE_INTERVAL 2000

//// Acceleration settings

/** \brief X, Y, Z max acceleration in mm/s^2 for printing moves or retracts. Make sure your printer can go that high!
 Overridden if EEPROM activated.
*/
#define MAX_ACCELERATION_UNITS_PER_SQ_SECOND_X 1000
#define MAX_ACCELERATION_UNITS_PER_SQ_SECOND_Y 1000
#define MAX_ACCELERATION_UNITS_PER_SQ_SECOND_Z 100

/** \brief X, Y, Z max acceleration in mm/s^2 for travel moves.  Overridden if EEPROM activated.*/
#define MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_X 1000
#define MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_Y 1000
#define MAX_TRAVEL_ACCELERATION_UNITS_PER_SQ_SECOND_Z 150

/** If you print on a moving bed, it can become more shaky the higher and bigger
 your print gets. Therefore it might be helpfull to reduce acceleration with
 increasing print height. You can define here how acceleration should change.
 You set ACCELERATION_FACTOR_TOP to the factor in percent for the top position
 of your printer. Acceleration will then be modified linear over height.
 INTERPOLATE_ACCELERATION_WITH_Z sets, which accelerations get changed:
 0 = do not interpolate at all
 1 = interpolate x and y acceleration
 2 = interpolate z acceleration
 3 = interpolate x,y and z acceleration
  */
#define INTERPOLATE_ACCELERATION_WITH_Z 0
#define ACCELERATION_FACTOR_TOP 100

/** \brief Maximum allowable jerk.

Caution: This is no real jerk in a physical meaning.

The jerk determines your start speed and the maximum speed at the join of two segments.
Its unit is mm/s. If the printer is standing still, the start speed is jerk/2. At the
join of two segments, the speed difference is limited to the jerk value.

Examples:
For all examples jerk is assumed as 40.

Segment 1: vx = 50, vy = 0
Segment 2: vx = 0, vy = 50
v_diff = sqrt((50-0)^2+(0-50)^2) = 70.71
v_diff > jerk => vx_1 = vy_2 = jerk/v_diff*vx_1 = 40/70.71*50 = 28.3 mm/s at the join

Segment 1: vx = 50, vy = 0
Segment 2: vx = 35.36, vy = 35.36
v_diff = sqrt((50-35.36)^2+(0-35.36)^2) = 38.27 < jerk
Corner can be printed with full speed of 50 mm/s

Overridden if EEPROM activated.
*/
#define MAX_JERK 20.0
#define MAX_ZJERK 0.3

/** \brief Number of moves we can cache in advance.

This number of moves can be cached in advance. If you wan't to cache more, increase this. Especially on
many very short moves the cache may go empty. The minimum value is 5.
*/
#define PRINTLINE_CACHE_SIZE 32

/** \brief Low filled cache size.

If the cache contains less then MOVE_CACHE_LOW segments, the time per segment is limited to LOW_TICKS_PER_MOVE clock cycles.
If a move would be shorter, the feedrate will be reduced. This should prevent buffer underflows. Set this to 0 if you
don't care about empty buffers during print.
*/
#define MOVE_CACHE_LOW 14
/** \brief Cycles per move, if move cache is low.

This value must be high enough, that the buffer has time to fill up. The problem only occurs at the beginning of a print or
if you are printing many very short segments at high speed. Higher delays here allow higher values in PATH_PLANNER_CHECK_SEGMENTS.
*/
#define LOW_TICKS_PER_MOVE 250000

// ##########################################################################################
// ##                           Extruder control                                           ##
// ##########################################################################################


/* \brief Minimum temperature for extruder operation

This is a safety value. If your extruder temperature is below this temperature, no
extruder steps are executed. This is to prevent your extruder to move unless the filament
is at least molten. After having some complains that the extruder does not work, I leave
it 0 as default.
*/

#define MIN_EXTRUDER_TEMP 170

/** \brief Enable advance algorithm.

Without a correct adjusted advance algorithm, you get blobs at points, where acceleration changes. The
effect increases with speed and acceleration difference. Using the advance method decreases this effect.
For more informations, read the wiki.
*/
#define USE_ADVANCE 1

/** \brief enables quadratic component.

Set 1 to allow, 0 disallow a quadratic advance dependency. Linear is the dominant value, so no real need
to activate the quadratic term. Only adds lots of computations and storage usage. */
#define ENABLE_QUADRATIC_ADVANCE 0


// ##########################################################################################
// ##                           Communication configuration                                ##
// ##########################################################################################

//// AD595 THERMOCOUPLE SUPPORT UNTESTED... USE WITH CAUTION!!!!

/** \brief Communication speed.

- 250000 : Fastes with errorrate of 0% with 16 or 32 MHz - update wiring_serial.c in your board files. See boards/readme.txt
- 115200 : Fast, but may produce communication errors on quite regular basis, Error rate -3,5%
- 76800 : Best setting for Arduino with 16 MHz, Error rate 0,2% page 198 AVR1284 Manual. Result: Faster communication then 115200
- 57600 : Should produce nearly no errors, on my gen 6 it's faster than 115200 because there are no errors slowing down the connection
- 38600

 Overridden if EEPROM activated.
*/
//#define BAUDRATE 76800
#define BAUDRATE 230400
//#define BAUDRATE 250000

/**
Some boards like Gen7 have a power on pin, to enable the ATX power supply. If this is defined,
the power will be turned on without the need to call M80 if initially started.
*/
#define ENABLE_POWER_ON_STARTUP 1

/**
If you use an ATX power supply you need the power pin to work non inverting. For some special
boards you might need to make it inverting.
*/
#define POWER_INVERTING 0
/** What shall the printer do, when it receives an M112 emergency stop signal?
 0 = Disable heaters/motors, wait forever until someone presses reset.
 1 = restart by resetting the AVR controller. The USB connection will not reset if managed by a different chip!
*/
#define KILL_METHOD 1

/** Appends the line number after every ok send, to acknowledge the received command. Uncomment for plain ok ACK if your host has problems with this */
#define ACK_WITH_LINENUMBER 1       
/** Communication errors can swallow part of the ok, which tells the host software to send
the next command. Not receiving it will cause your printer to stop. Sending this string every
second, if our queue is empty should prevent this. Comment it, if you don't wan't this feature. */
#define WAITING_IDENTIFIER "wait"
//Davinci Specific
#define RESET_IDENTIFIER "start"

/** \brief Sets time for echo debug

You can set M111 1 which enables ECHO of commands sent. This define specifies the position,
when it will be executed. In the original FiveD software, echo is done after receiving the
command. With checksum you know, how it looks from the sending string. With this define
uncommented, you will see the last command executed. To be more specific: It is written after
execution. This helps tracking errors, because there may be 8 or more commands in the queue
and it is elsewise difficult to know, what your reprap is currently doing.
*/
#define ECHO_ON_EXECUTE 1

/** \brief EEPROM storage mode

Set the EEPROM_MODE to 0 if you always want to use the settings in this configuration file. If not,
set it to a value not stored in the first EEPROM-byte used. If you later want to overwrite your current
EEPROM settings with configuration defaults, just select an other value. On the first call to epr_init()
it will detect a mismatch of the first byte and copy default values into EEPROM. If the first byte
matches, the stored values are used to overwrite the settings.

IMPORTANT: With mode <>0 some changes in Configuration.h are not set any more, as they are
           taken from the EEPROM.
*/
#define EEPROM_MODE 1


/**************** duplicate motor driver ***************

If you have an unused extruder stepper free, you could use it to drive the second z motor
instead of driving both with a single stepper. The same works for the other axis if needed.
*/

#define FEATURE_TWO_XSTEPPER 0
#define X2_STEP_PIN   E1_STEP_PIN
#define X2_DIR_PIN    E1_DIR_PIN
#define X2_ENABLE_PIN E1_ENABLE_PIN

#define FEATURE_TWO_YSTEPPER 0
#define Y2_STEP_PIN   E1_STEP_PIN
#define Y2_DIR_PIN    E1_DIR_PIN
#define Y2_ENABLE_PIN E1_ENABLE_PIN

#define FEATURE_TWO_ZSTEPPER 0
#define Z2_STEP_PIN   E1_STEP_PIN
#define Z2_DIR_PIN    E1_DIR_PIN
#define Z2_ENABLE_PIN E1_ENABLE_PIN

#define FEATURE_THREE_ZSTEPPER 0
#define Z3_STEP_PIN   E2_STEP_PIN
#define Z3_DIR_PIN    E2_DIR_PIN
#define Z3_ENABLE_PIN E2_ENABLE_PIN

/* Ditto printing allows 2 extruders to do the same action. This effectively allows
to print an object two times at the speed of one. Works only with dual extruder setup.
*/
#define FEATURE_DITTO_PRINTING 0

/* Servos

If you need to control servos, enable this feature. You can control up to 4 servos.
Control the servos with
M340 P<servoId> S<pulseInUS>
servoID = 0..3
Servos are controlled by a pulse width normally between 500 and 2500 with 1500ms in center position. 0 turns servo off.

WARNING: Servos can draw a considerable amount of current. Make sure your system can handle this or you may risk your hardware!
*/

#define FEATURE_SERVO 0
// Servo pins on a RAMPS board are 11,6,5,4
#define SERVO0_PIN 11
#define SERVO1_PIN 6
#define SERVO2_PIN 5
#define SERVO3_PIN 4
/* for set servo(s) at designed neutral position at power-up. Values < 500 mean no start position */
#define SERVO0_NEUTRAL_POS  1300
#define SERVO1_NEUTRAL_POS  -1
#define SERVO2_NEUTRAL_POS  -1
#define SERVO3_NEUTRAL_POS  -1
/** Set to servo number +1 to control that servo in ui menu. 0 disables ui control. */
#define UI_SERVO_CONTROL 0
/** Some fans won't start for low values, but would run if started with higher power at the beginning.
This defines the full power duration before returning to set value. Time is in milliseconds */
#define FAN_KICKSTART_TIME  200



/* A watchdog resets the printer, if a signal is not send within predefined time limits. That way we can be sure that the board
is always running and is not hung up for some unknown reason. 

IMPORTANT: The ARM processors need a special board definition to work properly. 
See: AdditionalArduinoFiles: README.txt on how to install them. 
*/
#define FEATURE_WATCHDOG 1

/* Z-Probing */

/* After homing the z position is corrected to compensate
for a bed coating. Since you can change coatings the value is stored in
EEPROM if enabled, so you can switch between different coatings without needing
to recalibrate z.
*/
#define Z_PROBE_Z_OFFSET 0 // offset to coating form real bed level
/* How is z min measured
 0 = trigger is height of real bed neglecting coating
 1 = trigger is current coating

 For mode 1 the current coating thickness is added to measured z probe distances.
 That way the real bed is always the reference height. For inductive sensors
 or z min endstops the coating has no effect on the result, so you should use mode 0.
*/
#define Z_PROBE_Z_OFFSET_MODE 0

#if DAVINCI > 0
#define FEATURE_Z_PROBE true
#define Z_PROBE_PIN 117
#else
#define FEATURE_Z_PROBE false
#define Z_PROBE_PIN -1
#endif
#define Z_PROBE_PULLUP 1
#define Z_PROBE_ON_HIGH 0
#define Z_PROBE_X_OFFSET 0
#define Z_PROBE_Y_OFFSET 0
#define Z_PROBE_BED_DISTANCE 5.0 // Higher than max bed level distance error in mm

// Waits for a signal to start. Valid signals are probe hit and ok button.
// This is needful if you have the probe trigger by hand.
#define Z_PROBE_WAIT_BEFORE_TEST 0
/** Speed of z-axis in mm/s when probing */
#define Z_PROBE_SPEED 1
#define Z_PROBE_XY_SPEED 30
#define Z_PROBE_SWITCHING_DISTANCE 5 // Distance to safely switch off probe after it was activated
#define Z_PROBE_REPETITIONS 1 // Repetitions for probing at one point. 
/** The height is the difference between activated probe position and nozzle height. */
#if MODEL==0
#define Z_PROBE_HEIGHT 0.28
#else
#define Z_PROBE_HEIGHT 0.54
#endif
/** These scripts are run before resp. after the z-probe is done. Add here code to activate/deactivate probe if needed. */
#define Z_PROBE_START_SCRIPT ""
#define Z_PROBE_FINISHED_SCRIPT ""
/** Set 1 if you need a hot extruder for good probe results. Normally only required if nozzle is probe. */
#define Z_PROBE_REQUIRES_HEATING 0
/** Minimum extruder temperature for probing. If it is lower, it will be increased to that value. */
#define Z_PROBE_MIN_TEMPERATURE 150
/*
Define how we measure the bed rotation. 
All methods need at least 3 points to define the bed rotation correctly. The quality we get comes
from the selection of the right points and method.

BED_LEVELING_METHOD 0
This method measures at the 3 probe points and creates a plane through these points. If you have
a really planar bed this gives the optimum result. The 3 points must not be in one line and have
a long distance to increase numerical stability.

BED_LEVELING_METHOD 1
This measures a grid. Probe point 1 is the origin and points 2 and 3 span a grid. We measure
BED_LEVELING_GRID_SIZE points in each direction and compute a regression plane through all
points. This gives a good overall plane if you have small bumps measuring inaccuracies.

BED_LEVELING_METHOD 2
Bending correcting 4 point measurement. This is for cantilevered beds that have the rotation axis
not at the side but inside the bed. Here we can assume no bending on the axis and a symmetric
bending to both sides of the axis. So probe points 2 and 3 build the symmetric axis and
point 1 is mirrored to 1m across the axis. Using the symmetry we then remove the bending
from 1 and use that as plane.
*/
#define BED_LEVELING_METHOD 0
/* How to correct rotation.
0 = software side
1 = motorized modification of 2 from 3 fixture points.
*/
#define BED_CORRECTION_METHOD 0
// Grid size for grid based plane measurement
#define BED_LEVELING_GRID_SIZE 4
// Repetitions for motorized bed leveling
#define BED_LEVELING_REPETITIONS 5
/* These are the motor positions relative to bed origin. Only needed for
motorized bed leveling */
#define BED_MOTOR_1_X 0
#define BED_MOTOR_1_Y 0
#define BED_MOTOR_2_X 200
#define BED_MOTOR_2_Y 0
#define BED_MOTOR_3_X 100
#define BED_MOTOR_3_Y 200

/* Autoleveling allows it to z-probe 3 points to compute the inclination and compensates the error for the print.
   This feature requires a working z-probe and you should have z-endstop at the top not at the bottom.
   The same 3 points are used for the G29 command.
*/
#define FEATURE_AUTOLEVEL true
#if DAVINCI==1
#define Z_PROBE_X1 -7
#define Z_PROBE_Y1 -10
#define Z_PROBE_X2 -7
#define Z_PROBE_X3 179
#if MODEL==0
#define Z_PROBE_Y2 205
#define Z_PROBE_Y3 205
#else
#define Z_PROBE_Y2 203
#define Z_PROBE_Y3 203
#endif
//Manual bed leveling
#define MANUAL_LEVEL_X1 100
#define MANUAL_LEVEL_Y1 190
#define MANUAL_LEVEL_X2 100
#define MANUAL_LEVEL_Y2 10
#define MANUAL_LEVEL_X3 10
#define MANUAL_LEVEL_Y3  100
#define MANUAL_LEVEL_X4  190
#define MANUAL_LEVEL_Y4  100
#endif

#if DAVINCI==2 || DAVINCI==3
#define Z_PROBE_X1 36
#define Z_PROBE_Y1 -7
#define Z_PROBE_X2 36
#define Z_PROBE_Y2 203
#define Z_PROBE_X3 171
#define Z_PROBE_Y3 203
//Manual bed leveling
#define MANUAL_LEVEL_X1 100
#define MANUAL_LEVEL_Y1  180
#define MANUAL_LEVEL_X2 100
#define MANUAL_LEVEL_Y2 10
#define MANUAL_LEVEL_X3 50
#define MANUAL_LEVEL_Y3 95
#define MANUAL_LEVEL_X4  150
#define MANUAL_LEVEL_Y4  95
#endif

#if DAVINCI==4
#define Z_PROBE_X1 -3
#define Z_PROBE_Y1 -7
#define Z_PROBE_X2 -3
#define Z_PROBE_Y2 204
#define Z_PROBE_X3 184
#define Z_PROBE_Y3 204
//Manual bed leveling
#define MANUAL_LEVEL_X1 100
#define MANUAL_LEVEL_Y1 190
#define MANUAL_LEVEL_X2 100
#define MANUAL_LEVEL_Y2 10
#define MANUAL_LEVEL_X3 10
#define MANUAL_LEVEL_Y3  100
#define MANUAL_LEVEL_X4  190
#define MANUAL_LEVEL_Y4  100
#endif

#if DAVINCI==0
#define Z_PROBE_X1 36
#define Z_PROBE_Y1 -7
#define Z_PROBE_X2 36
#define Z_PROBE_Y2 203
#define Z_PROBE_X3 171
#define Z_PROBE_Y3 203
//Manual bed leveling
#define MANUAL_LEVEL_X1 100
#define MANUAL_LEVEL_Y1  180
#define MANUAL_LEVEL_X2 100
#define MANUAL_LEVEL_Y2 10
#define MANUAL_LEVEL_X3 50
#define MANUAL_LEVEL_Y3 95
#define MANUAL_LEVEL_X4  150
#define MANUAL_LEVEL_Y4  95
#endif
/* Bending correction adds a value to a measured z-probe value. This may be
  required when the z probe needs some force to trigger and this bends the
  bed down. Currently the correction values A/B/C correspond to z probe
  positions 1/2/3. In later versions a bending correction algorithm might be
  introduced to give it other meanings.*/
#define BENDING_CORRECTION_A 0
#define BENDING_CORRECTION_B 0
#define BENDING_CORRECTION_C 0

/* DISTORTION_CORRECTION compensates the distortion caused by mechanical imprecisions of nonlinear (i.e. DELTA) printers
 * assumes that the floor is plain (i.e. glass plate)
 *     and that it is perpendicular to the towers
 *     and that the (0,0) is in center
 * requires z-probe
 * G29 measures the Z offset in matrix NxN points (due to nature of the delta printer, the corners are extrapolated instead of measured)
 * and compensate the distortion
 * more points means better compensation, but consumes more memory and takes more time
 * DISTORTION_CORRECTION_R is the distance of last row or column from center
 */

#define DISTORTION_CORRECTION         0
#define DISTORTION_CORRECTION_POINTS  5
/* For delta printers you simply define the measured radius around origin */
#define DISTORTION_CORRECTION_R       80
/* For all others you define the correction rectangle by setting the min/max coordinates. Make sure the the probe can reach all points! */
#define DISTORTION_XMIN 10
#define DISTORTION_YMIN 10
#define DISTORTION_XMAX 190
#define DISTORTION_YMAX 190

/** Uses EEPROM instead of ram. Allows bigger matrix (up to 22x22) without any ram cost.
  Especially on arm based systems with cached EEPROM it is good, on AVR it has a small
  performance penalty.
*/
#define DISTORTION_PERMANENT          1
/** Correction computation is not a cheap operation and changes are only small. So it
is not necessary to update it for every sub-line computed. For example lets take DELTA_SEGMENTS_PER_SECOND_PRINT = 150
and fastest print speed 100 mm/s. So we have a maximum segment length of 100/150 = 0.66 mm.
Now lats say our point field is 200 x 200 mm with 9 x 9 points. So between 2 points we have
200 / (9-1) = 25 mm. So we need at least 25 / 0.66 = 37 lines to move to the next measuring
point. So updating correction every 15 calls gives us at least 2 updates between the
measured points.
NOTE: Explicit z changes will always trigger an update!
*/
#define DISTORTION_UPDATE_FREQUENCY   15
/** z distortion degrades to 0 from this height on. You should start after the first layer to get
best bonding with surface. */
#define DISTORTION_START_DEGRADE 0.5
/** z distortion correction gets down to 0 at this height. */
#define DISTORTION_END_HEIGHT 1.5

/* If your printer is not exactly square but is more like a parallelogram, you can
use this to compensate the effect of printing squares like parallelograms. Set the
parameter to then tangens of the deviation from 90° when you print a square object.
E.g. if you angle is 91° enter tan(1) = 0.017. If error doubles you have the wrong sign.
Always hard to say since the other angle is 89° in this case!
*/
#define FEATURE_AXISCOMP 0
#define AXISCOMP_TANXY 0
#define AXISCOMP_TANYZ 0
#define AXISCOMP_TANXZ 0

/** \brief Experimental calibration utility for delta printers
 * Change 1 to 0 to disable
*/
#define FEATURE_SOFTWARE_LEVELING 0

/* Babystepping allows to change z height during print without changing official z height */
#define FEATURE_BABYSTEPPING 0
/* If you have a threaded rod, you want a higher multiplicator to see an effect. Limit value to 50 or you get easily overflows.*/
#define BABYSTEP_MULTIPLICATOR 1

/* Define a pin to turn light on/off */
#define CASE_LIGHTS_PIN LIGHT_PIN
#define CASE_LIGHT_DEFAULT_ON 1
#define CASE_BADGE_LIGHT_DEFAULT_ON 1

/** Set to false to disable SD support: */
#ifndef SDSUPPORT  // Some boards have sd support on board. These define the values already in pins.h
#define SDSUPPORT 1
// Uncomment to enable or change card detection pin. With card detection the card is mounted on insertion.
#define SDCARDDETECT SDCARDDETECT
// Change to true if you get a inserted message on removal.
#define SDCARDDETECTINVERTED false
#endif
/** Show extended directory including file length. Don't use this with Pronterface! */
#define SD_EXTENDED_DIR 1
/** The GCODEs in this line get executed, when you stop a SD print before it was ended.
Separate commands by \n */
#define SD_RUN_ON_STOP "G28 XY\nM84"
/** Disable motors and heaters when print was stopped. */
#define SD_STOP_HEATER_AND_MOTORS_ON_STOP 1
// If you want support for G2/G3 arc commands set to true, otherwise false.
#define ARC_SUPPORT 1

/** You can store the current position with M401 and go back to it with M402.
   This works only if feature is set to true. */
#define FEATURE_MEMORY_POSITION 1

/** If a checksum is sent, all future commands must also contain a checksum. Increases reliability especially for binary protocol. */
#define FEATURE_CHECKSUM_FORCED 0

/** Should support for fan control be compiled in. If you enable this make sure
the FAN pin is not the same as for your second extruder. RAMPS e.g. has FAN_PIN in 9 which
is also used for the heater if you have 2 extruders connected. */
#if REPURPOSE_FAN_TO_COOL_EXTRUSIONS == 1
#define FEATURE_FAN_CONTROL 1
#define FAN_PIN ORIG_FAN_PIN
  #if DAVINCI == 2 || DAVINCI == 3
      #undef EXT0_EXTRUDER_COOLER_PIN
      #define EXT0_EXTRUDER_COOLER_PIN ORIG_FAN2_PIN
      #define EXT1_EXTRUDER_COOLER_PIN ORIG_FAN2_PIN
  #else //DaVinci 1.0
        #undef EXT0_EXTRUDER_COOLER_PIN
        #define EXT0_EXTRUDER_COOLER_PIN -1 //Warning need to add a permanent fan with power supply to cool extruder
  #endif
#else
  #undef  FAN_PIN
  #define FAN_PIN -1
  #define FEATURE_FAN_CONTROL 0
#endif

/* You can have a second fan controlled by adding P1 to M106/M107 command. */ 
#define FEATURE_FAN2_CONTROL 0
//#define FAN2_PIN ORIG_FAN2_PIN

/* By setting FAN_BOARD_PIN to a pin number you get a board cooler. That fan 
goes on as soon as moves occur. Mainly to prevent overheating of stepper drivers. */
//#undef FAN_BOARD_PIN
//#define FAN_BOARD_PIN ORIG_FAN_PIN
/** Speed of board fan when on. 0 = off, 255 = max */
#define BOARD_FAN_SPEED 255

/* You can have one additional fan controlled by a temperature. You can set
   set at which temperature it should turn on and at which it should reach max. speed.
*/
#define FAN_THERMO_PIN -1
#define FAN_THERMO_MIN_PWM 128
#define FAN_THERMO_MAX_PWM 255
#define FAN_THERMO_MIN_TEMP 45
#define FAN_THERMO_MAX_TEMP 60
// Analog pin number or channel for due boards
#define FAN_THERMO_THERMISTOR_PIN -1
#define FAN_THERMO_THERMISTOR_TYPE 1


/** Adds support for ESP8266 Duet web interface, PanelDue and probably some other things. 
 * This essentially adds command M36/M408 and extends M20.
 * Since it requires some memory do not enable it unless you have such a display!
 *  */
#define FEATURE_JSON 0

/** For displays and keys there are too many permutations to handle them all in once.
For the most common available combinations you can set the controller type here, so
you don't need to configure uicong.h at all. Controller settings > 1 disable usage
of uiconfig.h

0 or NO_CONTROLLER = no display
1 or UICONFIG_CONTROLLER = Manual definition of display and keys parameter in uiconfig.h

The following settings override uiconfig.h!
2 or CONTROLLER_SMARTRAMPS = Smartcontroller from reprapdiscount on a RAMPS or RUMBA board
3 or CONTROLLER_ADAFRUIT = Adafruit RGB controller
4 or CONTROLLER_FOLTYN = Foltyn 3DMaster with display attached
5 or CONTROLLER_VIKI = ViKi LCD - Check pin configuration in ui.h for feature controller 5!!! sd card disabled by default!
6 or CONTROLLER_MEGATRONIC = ReprapWorld Keypad / LCD, predefined pins for Megatronics v2.0 and RAMPS 1.4. Please check if you have used the defined pin layout in ui.h.
7 or CONTROLLER_RADDS = RADDS Extension Port
8 or CONTROLLER_PIBOT20X4 = PiBot Display/Controller extension with 20x4 character display
9 or CONTROLLER_PIBOT16X2 = PiBot Display/Controller extension with 16x2 character display
10 or CONTROLLER_GADGETS3D_SHIELD = Gadgets3D shield on RAMPS 1.4, see http://reprap.org/wiki/RAMPS_1.3/1.4_GADGETS3D_Shield_with_Panel
11 or CONTROLLER_REPRAPDISCOUNT_GLCD = RepRapDiscount Full Graphic Smart Controller
12 or CONTROLLER_FELIX = FELIXPrinters Controller
13 or CONTROLLER_RAMBO = SeeMeCNC Display on Rambo (ORION)
14 or CONTROLLER_OPENHARDWARE_LCD2004 = OpenHardware.co.za LCD2004 V2014
15 or CONTROLLER_SANGUINOLOLU_PANELOLU2 = Sanguinololu + Panelolu2
17 or CONTROLLER_MIREGLI 17
18 or CONTROLLER_GATE_3NOVATICA Gate Controller from 3Novatica
19 or CONTROLLER_SPARKLCD Sparkcube LCD on RADDS
20 or CONTROLLER_BAM_DICE_DUE  DAM&DICE Due LCD Display
21 or CONTROLLER_VIKI2 Panucatt Viki2 graphic lcd 
24 or CONTROLLER_ZONESTAR = Zonestar P802M with LCD 20x4 and 5 ADC button keypad
405 or CONTROLLER_FELIX_DUE Felix LCD für due based board
*/
#if DAVINCI==0
#define FEATURE_CONTROLLER CONTROLLER_RADDS
#else
#define FEATURE_CONTROLLER UICONFIG_CONTROLLER
#endif

/* You can have one keypad connected via single analog pin as seen on
 some printers with Melzi V2.0 board, 20x4 LCD and 5 buttons keypad. This must be
 the analog pin number! */
#define ADC_KEYPAD_PIN -1

/**
Select the languages to use. On first startup user can select
the language from a menu with activated languages. In Configuration->Language
the language can be switched any time. */
#define LANGUAGE_EN_ACTIVE 1 // English
#define LANGUAGE_DE_ACTIVE 1 // German
#define LANGUAGE_NL_ACTIVE 1 // Dutch
#define LANGUAGE_PT_ACTIVE 0 // Brazilian portuguese
#define LANGUAGE_IT_ACTIVE 1 // Italian
#define LANGUAGE_ES_ACTIVE 0 // Spanish
#define LANGUAGE_FI_ACTIVE 0 // Finnish
#define LANGUAGE_SE_ACTIVE 0 // Swedish
#define LANGUAGE_FR_ACTIVE 1 // French
#define LANGUAGE_CZ_ACTIVE 0 // Czech
#define LANGUAGE_PL_ACTIVE 0 // Polish
#define LANGUAGE_TR_ACTIVE 0 // Turkish
#define LANGUAGE_JP_ACTIVE 1 // Japanese

/* Some displays loose their settings from time to time. Try uncommenting the 
auto-repair function if this is the case. It is not supported for all display
types. It creates a minimal flicker from time to time and also slows down
computations, so do not enable it if your display works stable!
*/
//#define TRY_AUTOREPAIR_LCD_ERRORS

// This is line 2 of the status display at startup. Change to your like.
#if DAVINCI==0
#define UI_PRINTER_NAME    "  My Printer "
#define DAVINCI_TYPE "0"
#endif
#if DAVINCI==1
#define UI_PRINTER_NAME    "  Da Vinci 1.0"
#define DAVINCI_TYPE "1"
#endif
#if DAVINCI==2
#define UI_PRINTER_NAME    "  Da Vinci 2.0"
#define DAVINCI_TYPE "2"
#endif
#if DAVINCI==3
#define UI_PRINTER_NAME    "  Da Vinci 2.0"
#define DAVINCI_TYPE "3"
#endif
#if DAVINCI==4
#define UI_PRINTER_NAME    "  Da Vinci AiO"
#define DAVINCI_TYPE "4"
#endif

#define UI_PRINTER_COMPANY "By XYZ Printing"

#if MODEL == 0 || DAVINCI==0
#define MODEL_TYPE " "
#else
#define MODEL_TYPE  "A"
#endif

/** Animate switches between menus etc. */
#define UI_ANIMATION 0

/** How many ms should a single page be shown, until it is switched to the next one.*/
#define UI_PAGES_DURATION 4000

/** Delay of start screen in milliseconds */
#define UI_START_SCREEN_DELAY 2000
/** Uncomment if you don't want automatic page switching. You can still switch the
info pages with next/previous button/click-encoder */
#define UI_DISABLE_AUTO_PAGESWITCH 1

/** Time to return to info menu if x milliseconds no key was pressed. Set to 0 to disable it. */
#define UI_AUTORETURN_TO_MENU_AFTER 30000

#define FEATURE_UI_KEYS 0

/* Normally cou want a next/previous actions with every click of your encoder.
Unfortunately, the encoder have a different count of phase changes between clicks.
Select an encoder speed from 0 = fastest to 2 = slowest that results in one menu move per click.
*/
#define UI_ENCODER_SPEED 2

// Set to 1 to reverse encoder direction
#define UI_REVERSE_ENCODER 0

/* There are 2 ways to change positions. You can move by increments of 1/0.1 mm resulting in more menu entries
and requiring many turns on your encode. The alternative is to enable speed dependent positioning. It will change
the move distance depending on the speed you turn the encoder. That way you can move very fast and very slow in the
same setting.

*/
#define UI_SPEEDDEPENDENT_POSITIONING 0

/** If set to 1 faster turning the wheel makes larger jumps. Helps for faster navigation. */
#define UI_DYNAMIC_ENCODER_SPEED 1          // enable dynamic rotary encoder speed

/** \brief bounce time of keys in milliseconds */
#define UI_KEY_BOUNCETIME 10

/** \brief First time in ms until repeat of action. */
#define UI_KEY_FIRST_REPEAT 500
/** \brief Reduction of repeat time until next execution. */
#define UI_KEY_REDUCE_REPEAT 50
/** \brief Lowest repeat time. */
#define UI_KEY_MIN_REPEAT 50

#define FEATURE_BEEPER 1
/**
Beeper sound definitions for short beeps during key actions
and longer beeps for important actions.
Parameter is delay in microseconds and the second is the number of repetitions.
Values must be in range 1..255
*/
#define BEEPER_SHORT_SEQUENCE 2,2
#define BEEPER_LONG_SEQUENCE 8,8

// ###############################################################################
// ##                         Values for menu settings                          ##
// ###############################################################################

// Values used for preheat
#define UI_SET_PRESET_HEATED_BED_TEMP_PLA 60
#define UI_SET_PRESET_EXTRUDER_TEMP_PLA   180
#define UI_SET_PRESET_HEATED_BED_TEMP_ABS 90
#define UI_SET_PRESET_EXTRUDER_TEMP_ABS   230

//Davinci specific
// Loading / Unloading Filament value
#define UI_SET_PRESET_LOADING_FEEDRATE  2 
#define UI_SET_PRESET_UNLOADING_FEEDRATE  4
#define UI_SET_PRESET_UNLOAD_LOAD_DISTANCE  60 

// Extreme values
#define UI_SET_MIN_HEATED_BED_TEMP  30
#define UI_SET_MAX_HEATED_BED_TEMP 130
#define UI_SET_MIN_EXTRUDER_TEMP   160
#define UI_SET_MAX_EXTRUDER_TEMP   270
#define UI_SET_EXTRUDER_FEEDRATE 2 // mm/sec
#define UI_SET_EXTRUDER_RETRACT_DISTANCE 3 // mm

/*
#define USER_KEY1_PIN     UI_DISPLAY_D5_PIN      // D5 to display (not used for graphics controller), change to other pin if you use character LCD !
#define USER_KEY1_ACTION  UI_ACTION_FAN_SUSPEND
#define USER_KEY2_PIN     UI_DISPLAY_D6_PIN      // D6 to display (not used for graphics controller)...
#define USER_KEY2_ACTION  UI_ACTION_SD_PRI_PAU_CONT
#define USER_KEY3_PIN     UI_DISPLAY_D7_PIN      // D7 to display (not used for graphics controller)...
#define USER_KEY3_ACTION  UI_ACTION_LIGHTS_ONOFF
#define USER_KEY4_PIN     -1
#define USER_KEY4_ACTION  UI_ACTION_DUMMY
*/

// ####### Advanced stuff for very special function #########

//#define NUM_MOTOR_DRIVERS 0
// #define MOTOR_DRIVER_x StepperDriver<int stepPin, int dirPin, int enablePin,bool invertDir, bool invertEnable>(float stepsPerMM,float speed)
//#define MOTOR_DRIVER_1(var) StepperDriver<E1_STEP_PIN, E1_DIR_PIN, E1_ENABLE_PIN, false, false> var(100.0f,5.0f)

/*
  You can expand firmware functionality with events and you own event handler.
  Read Events.h for more informations. To activate, uncomment the following define.
*/
//#define CUSTOM_EVENTS

#endif
