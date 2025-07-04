/**
 * Marlin 3D Printer Firmware
 * Copyright (C) 2016, 2017 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (C) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/**
 * About Marlin
 *
 * This firmware is a mashup between Sprinter and grbl.
 *  - https://github.com/kliment/Sprinter
 *  - https://github.com/simen/grbl/tree
 */

/**
 * -----------------
 * G-Codes in Marlin
 * -----------------
 *
 * Helpful G-code references:
 *  - http://linuxcnc.org/handbook/gcode/g-code.html
 *  - http://objects.reprap.org/wiki/Mendel_User_Manual:_RepRapGCodes
 *
 * Help to document Marlin's G-codes online:
 *  - http://reprap.org/wiki/G-code
 *  - https://github.com/MarlinFirmware/MarlinDocumentation
 *
 * -----------------
 *
 * "G" Codes
 *
 * G0   -> G1
 * G1   - Coordinated Movement X Y Z E
 * G2   - CW ARC
 * G3   - CCW ARC
 * G4   - Dwell S<seconds> or P<milliseconds>
 * G5   - Cubic B-spline with XYZE destination and IJPQ offsets
 * G10  - Retract filament according to settings of M207
 * G11  - Retract recover filament according to settings of M208
 * G12  - Clean tool
 * G17  - Select Plane XY (Requires CNC_WORKSPACE_PLANES)
 * G18  - Select Plane ZX (Requires CNC_WORKSPACE_PLANES)
 * G19  - Select Plane YZ (Requires CNC_WORKSPACE_PLANES)
 * G20  - Set input units to inches
 * G21  - Set input units to millimeters
 * G26  - Mesh Validation Pattern (Requires UBL_G26_MESH_VALIDATION)
 * G27  - Park Nozzle (Requires NOZZLE_PARK_FEATURE)
 * G28  - Home one or more axes
 * G29  - Detailed Z probe, probes the bed at 3 or more points.  Will fail if you haven't homed yet.
 * G30  - Single Z probe, probes bed at X Y location (defaults to current XY location)
 * G31  - Dock sled (Z_PROBE_SLED only)
 * G32  - Undock sled (Z_PROBE_SLED only)
 * G33  - Delta Auto-Calibration (Requires DELTA_AUTO_CALIBRATION)
 * G38  - Probe target - similar to G28 except it uses the Z_MIN_PROBE for all three axes
 * G42  - Coordinated move to a mesh point (Requires AUTO_BED_LEVELING_UBL)
 * G90  - Use Absolute Coordinates
 * G91  - Use Relative Coordinates
 * G92  - Set current position to coordinates given
 *
 * "M" Codes
 *
 * M0   - Unconditional stop - Wait for user to press a button on the LCD (Only if ULTRA_LCD is enabled)
 * M1   -> M0
 * M3   - Turn laser/spindle on, set spindle/laser speed/power, set rotation to clockwise
 * M4   - Turn laser/spindle on, set spindle/laser speed/power, set rotation to counter-clockwise
 * M5   - Turn laser/spindle off
 * M17  - Enable/Power all stepper motors
 * M18  - Disable all stepper motors; same as M84
 * M20  - List SD card. (Requires SDSUPPORT)
 * M21  - Init SD card. (Requires SDSUPPORT)
 * M22  - Release SD card. (Requires SDSUPPORT)
 * M23  - Select SD file: "M23 /path/file.gco". (Requires SDSUPPORT)
 * M24  - Start/resume SD print. (Requires SDSUPPORT)
 * M25  - Pause SD print. (Requires SDSUPPORT)
 * M26  - Set SD position in bytes: "M26 S12345". (Requires SDSUPPORT)
 * M27  - Report SD print status. (Requires SDSUPPORT)
 * M28  - Start SD write: "M28 /path/file.gco". (Requires SDSUPPORT)
 * M29  - Stop SD write. (Requires SDSUPPORT)
 * M30  - Delete file from SD: "M30 /path/file.gco"
 * M31  - Report time since last M109 or SD card start to serial.
 * M32  - Select file and start SD print: "M32 [S<bytepos>] !/path/file.gco#". (Requires SDSUPPORT)
 *        Use P to run other files as sub-programs: "M32 P !filename#"
 *        The '#' is necessary when calling from within sd files, as it stops buffer prereading
 * M33  - Get the longname version of a path. (Requires LONG_FILENAME_HOST_SUPPORT)
 * M34  - Set SD Card sorting options. (Requires SDCARD_SORT_ALPHA)
 * M42  - Change pin status via gcode: M42 P<pin> S<value>. LED pin assumed if P is omitted.
 * M43  - Display pin status, watch pins for changes, watch endstops & toggle LED, Z servo probe test, toggle pins
 * M48  - Measure Z Probe repeatability: M48 P<points> X<pos> Y<pos> V<level> E<engage> L<legs>. (Requires Z_MIN_PROBE_REPEATABILITY_TEST)
 * M75  - Start the print job timer.
 * M76  - Pause the print job timer.
 * M77  - Stop the print job timer.
 * M78  - Show statistical information about the print jobs. (Requires PRINTCOUNTER)
 * M80  - Turn on Power Supply. (Requires POWER_SUPPLY > 0)
 * M81  - Turn off Power Supply. (Requires POWER_SUPPLY > 0)
 * M82  - Set E codes absolute (default).
 * M83  - Set E codes relative while in Absolute (G90) mode.
 * M84  - Disable steppers until next move, or use S<seconds> to specify an idle
 *        duration after which steppers should turn off. S0 disables the timeout.
 * M85  - Set inactivity shutdown timer with parameter S<seconds>. To disable set zero (default)
 * M92  - Set planner.axis_steps_per_mm for one or more axes.
 * M100 - Watch Free Memory (for debugging) (Requires M100_FREE_MEMORY_WATCHER)
 * M104 - Set extruder target temp.
 * M105 - Report current temperatures.
 * M106 - Fan on.
 * M107 - Fan off.
 * M108 - Break out of heating loops (M109, M190, M303). With no controller, breaks out of M0/M1. (Requires EMERGENCY_PARSER)
 * M109 - Sxxx Wait for extruder current temp to reach target temp. Waits only when heating
 *        Rxxx Wait for extruder current temp to reach target temp. Waits when heating and cooling
 *        If AUTOTEMP is enabled, S<mintemp> B<maxtemp> F<factor>. Exit autotemp by any M109 without F
 * M110 - Set the current line number. (Used by host printing)
 * M111 - Set debug flags: "M111 S<flagbits>". See flag bits defined in enum.h.
 * M112 - Emergency stop.
 * M113 - Get or set the timeout interval for Host Keepalive "busy" messages. (Requires HOST_KEEPALIVE_FEATURE)
 * M114 - Report current position.
 * M115 - Report capabilities. (Extended capabilities requires EXTENDED_CAPABILITIES_REPORT)
 * M117 - Display a message on the controller screen. (Requires an LCD)
 * M118 - Display a message in the host console.
 * M119 - Report endstops status.
 * M120 - Enable endstops detection.
 * M121 - Disable endstops detection.
 * M125 - Save current position and move to filament change position. (Requires PARK_HEAD_ON_PAUSE)
 * M126 - Solenoid Air Valve Open. (Requires BARICUDA)
 * M127 - Solenoid Air Valve Closed. (Requires BARICUDA)
 * M128 - EtoP Open. (Requires BARICUDA)
 * M129 - EtoP Closed. (Requires BARICUDA)
 * M140 - Set bed target temp. S<temp>
 * M145 - Set heatup values for materials on the LCD. H<hotend> B<bed> F<fan speed> for S<material> (0=PLA, 1=ABS)
 * M149 - Set temperature units. (Requires TEMPERATURE_UNITS_SUPPORT)
 * M150 - Set Status LED Color as R<red> U<green> B<blue>. Values 0-255. (Requires BLINKM, RGB_LED, RGBW_LED, or PCA9632)
 * M155 - Auto-report temperatures with interval of S<seconds>. (Requires AUTO_REPORT_TEMPERATURES)
 * M163 - Set a single proportion for a mixing extruder. (Requires MIXING_EXTRUDER)
 * M164 - Save the mix as a virtual extruder. (Requires MIXING_EXTRUDER and MIXING_VIRTUAL_TOOLS)
 * M165 - Set the proportions for a mixing extruder. Use parameters ABCDHI to set the mixing factors. (Requires MIXING_EXTRUDER)
 * M190 - Sxxx Wait for bed current temp to reach target temp. ** Waits only when heating! **
 *        Rxxx Wait for bed current temp to reach target temp. ** Waits for heating or cooling. **
 * M200 - Set filament diameter, D<diameter>, setting E axis units to cubic. (Use S0 to revert to linear units.)
 * M201 - Set max acceleration in units/s^2 for print moves: "M201 X<accel> Y<accel> Z<accel> E<accel>"
 * M202 - Set max acceleration in units/s^2 for travel moves: "M202 X<accel> Y<accel> Z<accel> E<accel>" ** UNUSED IN MARLIN! **
 * M203 - Set maximum feedrate: "M203 X<fr> Y<fr> Z<fr> E<fr>" in units/sec.
 * M204 - Set default acceleration in units/sec^2: P<printing> R<extruder_only> T<travel>
 * M205 - Set advanced settings. Current units apply:
            S<print> T<travel> minimum speeds
            B<minimum segment time>
            X<max X jerk>, Y<max Y jerk>, Z<max Z jerk>, E<max E jerk>
 * M206 - Set additional homing offset. (Disabled by NO_WORKSPACE_OFFSETS or DELTA)
 * M207 - Set Retract Length: S<length>, Feedrate: F<units/min>, and Z lift: Z<distance>. (Requires FWRETRACT)
 * M208 - Set Recover (unretract) Additional (!) Length: S<length> and Feedrate: F<units/min>. (Requires FWRETRACT)
 * M209 - Turn Automatic Retract Detection on/off: S<0|1> (For slicers that don't support G10/11). (Requires FWRETRACT)
          Every normal extrude-only move will be classified as retract depending on the direction.
 * M211 - Enable, Disable, and/or Report software endstops: S<0|1> (Requires MIN_SOFTWARE_ENDSTOPS or MAX_SOFTWARE_ENDSTOPS)
 * M218 - Set a tool offset: "M218 T<index> X<offset> Y<offset>". (Requires 2 or more extruders)
 * M220 - Set Feedrate Percentage: "M220 S<percent>" (i.e., "FR" on the LCD)
 * M221 - Set Flow Percentage: "M221 S<percent>"
 * M226 - Wait until a pin is in a given state: "M226 P<pin> S<state>"
 * M240 - Trigger a camera to take a photograph. (Requires CHDK or PHOTOGRAPH_PIN)
 * M250 - Set LCD contrast: "M250 C<contrast>" (0-63). (Requires LCD support)
 * M260 - i2c Send Data (Requires EXPERIMENTAL_I2CBUS)
 * M261 - i2c Request Data (Requires EXPERIMENTAL_I2CBUS)
 * M280 - Set servo position absolute: "M280 P<index> S<angle|µs>". (Requires servos)
 * M300 - Play beep sound S<frequency Hz> P<duration ms>
 * M301 - Set PID parameters P I and D. (Requires PIDTEMP)
 * M302 - Allow cold extrudes, or set the minimum extrude S<temperature>. (Requires PREVENT_COLD_EXTRUSION)
 * M303 - PID relay autotune S<temperature> sets the target temperature. Default 150C. (Requires PIDTEMP)
 * M304 - Set bed PID parameters P I and D. (Requires PIDTEMPBED)
 * M350 - Set microstepping mode. (Requires digital microstepping pins.)
 * M351 - Toggle MS1 MS2 pins directly. (Requires digital microstepping pins.)
 * M355 - Set Case Light on/off and set brightness. (Requires CASE_LIGHT_PIN)
 * M380 - Activate solenoid on active extruder. (Requires EXT_SOLENOID)
 * M381 - Disable all solenoids. (Requires EXT_SOLENOID)
 * M400 - Finish all moves.
 * M401 - Lower Z probe. (Requires a probe)
 * M402 - Raise Z probe. (Requires a probe)
 * M404 - Display or set the Nominal Filament Width: "W<diameter>". (Requires FILAMENT_WIDTH_SENSOR)
 * M405 - Enable Filament Sensor flow control. "M405 D<delay_cm>". (Requires FILAMENT_WIDTH_SENSOR)
 * M406 - Disable Filament Sensor flow control. (Requires FILAMENT_WIDTH_SENSOR)
 * M407 - Display measured filament diameter in millimeters. (Requires FILAMENT_WIDTH_SENSOR)
 * M410 - Quickstop. Abort all planned moves.
 * M420 - Enable/Disable Leveling (with current values) S1=enable S0=disable (Requires MESH_BED_LEVELING or ABL)
 * M421 - Set a single Z coordinate in the Mesh Leveling grid. X<units> Y<units> Z<units> (Requires MESH_BED_LEVELING or AUTO_BED_LEVELING_UBL)
 * M428 - Set the home_offset based on the current_position. Nearest edge applies. (Disabled by NO_WORKSPACE_OFFSETS or DELTA)
 * M500 - Store parameters in EEPROM. (Requires EEPROM_SETTINGS)
 * M501 - Restore parameters from EEPROM. (Requires EEPROM_SETTINGS)
 * M502 - Revert to the default "factory settings". ** Does not write them to EEPROM! **
 * M503 - Print the current settings (in memory): "M503 S<verbose>". S0 specifies compact output.
 * M540 - Enable/disable SD card abort on endstop hit: "M540 S<state>". (Requires ABORT_ON_ENDSTOP_HIT_FEATURE_ENABLED)
 * M600 - Pause for filament change: "M600 X<pos> Y<pos> Z<raise> E<first_retract> L<later_retract>". (Requires ADVANCED_PAUSE_FEATURE)
 * M665 - Set delta configurations: "M665 L<diagonal rod> R<delta radius> S<segments/s> A<rod A trim mm> B<rod B trim mm> C<rod C trim mm> I<tower A trim angle> J<tower B trim angle> K<tower C trim angle>" (Requires DELTA)
 * M666 - Set delta endstop adjustment. (Requires DELTA)
 * M605 - Set dual x-carriage movement mode: "M605 S<mode> [X<x_offset>] [R<temp_offset>]". (Requires DUAL_X_CARRIAGE)
 * M851 - Set Z probe's Z offset in current units. (Negative = below the nozzle.)
 * M860 - Report the position of position encoder modules.
 * M861 - Report the status of position encoder modules.
 * M862 - Perform an axis continuity test for position encoder modules.
 * M863 - Perform steps-per-mm calibration for position encoder modules.
 * M864 - Change position encoder module I2C address.
 * M865 - Check position encoder module firmware version.
 * M866 - Report or reset position encoder module error count.
 * M867 - Enable/disable or toggle error correction for position encoder modules.
 * M868 - Report or set position encoder module error correction threshold.
 * M869 - Report position encoder module error.
 * M900 - Get and/or Set advance K factor and WH/D ratio. (Requires LIN_ADVANCE)
 * M906 - Set or get motor current in milliamps using axis codes X, Y, Z, E. Report values if no axis codes given. (Requires HAVE_TMC2130)
 * M907 - Set digital trimpot motor current using axis codes. (Requires a board with digital trimpots)
 * M908 - Control digital trimpot directly. (Requires DAC_STEPPER_CURRENT or DIGIPOTSS_PIN)
 * M909 - Print digipot/DAC current value. (Requires DAC_STEPPER_CURRENT)
 * M910 - Commit digipot/DAC value to external EEPROM via I2C. (Requires DAC_STEPPER_CURRENT)
 * M911 - Report stepper driver overtemperature pre-warn condition. (Requires HAVE_TMC2130)
 * M912 - Clear stepper driver overtemperature pre-warn condition flag. (Requires HAVE_TMC2130)
 * M913 - Set HYBRID_THRESHOLD speed. (Requires HYBRID_THRESHOLD)
 * M914 - Set SENSORLESS_HOMING sensitivity. (Requires SENSORLESS_HOMING)
 *
 * M360 - SCARA calibration: Move to cal-position ThetaA (0 deg calibration)
 * M361 - SCARA calibration: Move to cal-position ThetaB (90 deg calibration - steps per degree)
 * M362 - SCARA calibration: Move to cal-position PsiA (0 deg calibration)
 * M363 - SCARA calibration: Move to cal-position PsiB (90 deg calibration - steps per degree)
 * M364 - SCARA calibration: Move to cal-position PSIC (90 deg to Theta calibration position)
 *
 * ************ Custom codes - This can change to suit future G-code regulations
 * M928 - Start SD logging: "M928 filename.gco". Stop with M29. (Requires SDSUPPORT)
 * M999 - Restart after being stopped by error
 *
 * "T" Codes
 *
 * T0-T3 - Select an extruder (tool) by index: "T<n> F<units/min>"
 *
 */

#include "Marlin.h"

#include "ultralcd.h"
#include "planner.h"
#include "stepper.h"
#include "endstops.h"
#include "temperature.h"
#include "cardreader.h"
#include "configuration_store.h"
#include "language.h"
#include "pins_arduino.h"
#include "math.h"
#include "nozzle.h"
#include "duration_t.h"
#include "types.h"
#include "gcode.h"

#if HAS_ABL
  #include "vector_3.h"
  #if ENABLED(AUTO_BED_LEVELING_LINEAR)
    #include "qr_solve.h"
  #endif
#elif ENABLED(MESH_BED_LEVELING)
  #include "mesh_bed_leveling.h"
#endif

#if ENABLED(BEZIER_CURVE_SUPPORT)
  #include "planner_bezier.h"
#endif

#if HAS_BUZZER && DISABLED(LCD_USE_I2C_BUZZER)
  #include "buzzer.h"
#endif

#if ENABLED(USE_WATCHDOG)
  #include "watchdog.h"
#endif

#if ENABLED(BLINKM)
  #include "blinkm.h"
  #include "Wire.h"
#endif

#if ENABLED(PCA9632)
  #include "pca9632.h"
#endif

#if HAS_SERVOS
  #include "servo.h"
#endif

#if HAS_DIGIPOTSS
  #include <SPI.h>
#endif

#if ENABLED(DAC_STEPPER_CURRENT)
  #include "stepper_dac.h"
#endif

#if ENABLED(EXPERIMENTAL_I2CBUS)
  #include "twibus.h"
#endif

#if ENABLED(I2C_POSITION_ENCODERS)
  #include "I2CPositionEncoder.h"
#endif

#if ENABLED(ENDSTOP_INTERRUPTS_FEATURE)
  #include "endstop_interrupts.h"
#endif

#if ENABLED(M100_FREE_MEMORY_WATCHER)
  void gcode_M100();
  void M100_dump_routine(const char * const title, const char *start, const char *end);
#endif

#if ENABLED(SDSUPPORT)
  CardReader card;
#endif

#if ENABLED(EXPERIMENTAL_I2CBUS)
  TWIBus i2c;
#endif

#if ENABLED(G38_PROBE_TARGET)
  bool G38_move = false,
       G38_endstop_hit = false;
#endif

#if ENABLED(AUTO_BED_LEVELING_UBL)
  #include "ubl.h"
  extern bool defer_return_to_status;
  unified_bed_leveling ubl;
  #define UBL_MESH_VALID !( ( ubl.z_values[0][0] == ubl.z_values[0][1] && ubl.z_values[0][1] == ubl.z_values[0][2] \
                           && ubl.z_values[1][0] == ubl.z_values[1][1] && ubl.z_values[1][1] == ubl.z_values[1][2] \
                           && ubl.z_values[2][0] == ubl.z_values[2][1] && ubl.z_values[2][1] == ubl.z_values[2][2] \
                           && ubl.z_values[0][0] == 0 && ubl.z_values[1][0] == 0 && ubl.z_values[2][0] == 0 )  \
                           || isnan(ubl.z_values[0][0]))
#endif
int16_t HT;
bool Running = true;

uint8_t marlin_debug_flags = DEBUG_NONE;

/**
 * Cartesian Current Position
 *   Used to track the logical position as moves are queued.
 *   Used by 'line_to_current_position' to do a move after changing it.
 *   Used by 'SYNC_PLAN_POSITION_KINEMATIC' to update 'planner.position'.
 */
float current_position[XYZE] = { 0.0 };

/**
 * Cartesian Destination
 *   A temporary position, usually applied to 'current_position'.
 *   Set with 'gcode_get_destination' or 'set_destination_to_current'.
 *   'line_to_destination' sets 'current_position' to 'destination'.
 */
float destination[XYZE] = { 0.0 };

/**
 * axis_homed
 *   Flags that each linear axis was homed.
 *   XYZ on cartesian, ABC on delta, ABZ on SCARA.
 *
 * axis_known_position
 *   Flags that the position is known in each linear axis. Set when homed.
 *   Cleared whenever a stepper powers off, potentially losing its position.
 */
bool axis_homed[XYZ] = { false }, axis_known_position[XYZ] = { false };

/**
 * GCode line number handling. Hosts may opt to include line numbers when
 * sending commands to Marlin, and lines will be checked for sequentiality.
 * M110 N<int> sets the current line number.
 */
static long gcode_N, gcode_LastN, Stopped_gcode_LastN = 0;

/**
 * GCode Command Queue
 * A simple ring buffer of BUFSIZE command strings.
 *
 * Commands are copied into this buffer by the command injectors
 * (immediate, serial, sd card) and they are processed sequentially by
 * the main loop. The process_next_command function parses the next
 * command and hands off execution to individual handler functions.
 */
uint8_t commands_in_queue = 0; // Count of commands in the queue
static uint8_t cmd_queue_index_r = 0, // Ring buffer read position
               cmd_queue_index_w = 0; // Ring buffer write position
#if ENABLED(M100_FREE_MEMORY_WATCHER)
  char command_queue[BUFSIZE][MAX_CMD_SIZE];  // Necessary so M100 Free Memory Dumper can show us the commands and any corruption
#else                                         // This can be collapsed back to the way it was soon.
static char command_queue[BUFSIZE][MAX_CMD_SIZE];
#endif

/**
 * Next Injected Command pointer. NULL if no commands are being injected.
 * Used by Marlin internally to ensure that commands initiated from within
 * are enqueued ahead of any pending serial or sd card commands.
 */
static const char *injected_commands_P = NULL;

#if ENABLED(TEMPERATURE_UNITS_SUPPORT)
  TempUnit input_temp_units = TEMPUNIT_C;
#endif

/**
 * Feed rates are often configured with mm/m
 * but the planner and stepper like mm/s units.
 */
static const float homing_feedrate_mm_s[] PROGMEM = {
  #if ENABLED(DELTA)
    MMM_TO_MMS(HOMING_FEEDRATE_Z), MMM_TO_MMS(HOMING_FEEDRATE_Z),
  #else
    MMM_TO_MMS(HOMING_FEEDRATE_XY), MMM_TO_MMS(HOMING_FEEDRATE_XY),
  #endif
  MMM_TO_MMS(HOMING_FEEDRATE_Z), 0
};
FORCE_INLINE float homing_feedrate(const AxisEnum a) { return pgm_read_float(&homing_feedrate_mm_s[a]); }

float feedrate_mm_s = MMM_TO_MMS(1500.0);
static float saved_feedrate_mm_s;
int16_t feedrate_percentage = 100, saved_feedrate_percentage,
    flow_percentage[EXTRUDERS] = ARRAY_BY_EXTRUDERS1(100);

bool axis_relative_modes[] = AXIS_RELATIVE_MODES,
     volumetric_enabled =
        #if ENABLED(VOLUMETRIC_DEFAULT_ON)
          true
        #else
          false
        #endif
      ;
float filament_size[EXTRUDERS] = ARRAY_BY_EXTRUDERS1(DEFAULT_NOMINAL_FILAMENT_DIA),
      volumetric_multiplier[EXTRUDERS] = ARRAY_BY_EXTRUDERS1(1.0);

#if HAS_WORKSPACE_OFFSET
  #if HAS_POSITION_SHIFT
    // The distance that XYZ has been offset by G92. Reset by G28.
    float position_shift[XYZ] = { 0 };
  #endif
  #if HAS_HOME_OFFSET
    // This offset is added to the configured home position.
    // Set by M206, M428, or menu item. Saved to EEPROM.
    float home_offset[XYZ] = { 0 };
  #endif
  #if HAS_HOME_OFFSET && HAS_POSITION_SHIFT
    // The above two are combined to save on computes
    float workspace_offset[XYZ] = { 0 };
  #endif
#endif

// Software Endstops are based on the configured limits.
#if HAS_SOFTWARE_ENDSTOPS
  bool soft_endstops_enabled = true;
#endif
float soft_endstop_min[XYZ] = { X_MIN_POS, Y_MIN_POS, Z_MIN_POS },
      soft_endstop_max[XYZ] = { X_MAX_POS, Y_MAX_POS, Z_MAX_POS };

#if FAN_COUNT > 0
  int16_t fanSpeeds[FAN_COUNT] = { 0 };
  #if ENABLED(PROBING_FANS_OFF)
    bool fans_paused = false;
    int16_t paused_fanSpeeds[FAN_COUNT] = { 0 };
  #endif
#endif

// The active extruder (tool). Set with T<extruder> command.
uint8_t active_extruder = 0;

// Relative Mode. Enable with G91, disable with G90.
static bool relative_mode = false;

// For M109 and M190, this flag may be cleared (by M108) to exit the wait loop
volatile bool wait_for_heatup = true;

// For M0/M1, this flag may be cleared (by M108) to exit the wait-for-user loop
#if HAS_RESUME_CONTINUE
  volatile bool wait_for_user = false;
#endif

const char axis_codes[XYZE] = { 'X', 'Y', 'Z', 'E' };

// Number of characters read in the current line of serial input
static int serial_count = 0;

// Inactivity shutdown
millis_t previous_cmd_ms = 0;
static millis_t max_inactive_time = 0;
static millis_t stepper_inactive_time = (DEFAULT_STEPPER_DEACTIVE_TIME) * 1000UL;

// Print Job Timer
#if ENABLED(PRINTCOUNTER)
  PrintCounter print_job_timer = PrintCounter();
#else
  Stopwatch print_job_timer = Stopwatch();
#endif

// Buzzer - I2C on the LCD or a BEEPER_PIN
#if ENABLED(LCD_USE_I2C_BUZZER)
  #define BUZZ(d,f) lcd_buzz(d, f)
#elif PIN_EXISTS(BEEPER)
  Buzzer buzzer;
  #define BUZZ(d,f) buzzer.tone(d, f)
#else
  #define BUZZ(d,f) NOOP
#endif

static uint8_t target_extruder;

#if HAS_BED_PROBE
  float zprobe_zoffset = Z_PROBE_OFFSET_FROM_EXTRUDER;
#endif

#if HAS_ABL
  float xy_probe_feedrate_mm_s = MMM_TO_MMS(XY_PROBE_SPEED);
  #define XY_PROBE_FEEDRATE_MM_S xy_probe_feedrate_mm_s
#elif defined(XY_PROBE_SPEED)
  #define XY_PROBE_FEEDRATE_MM_S MMM_TO_MMS(XY_PROBE_SPEED)
#else
  #define XY_PROBE_FEEDRATE_MM_S PLANNER_XY_FEEDRATE()
#endif

#if ENABLED(AUTO_BED_LEVELING_BILINEAR)
  #if ENABLED(DELTA)
    #define ADJUST_DELTA(V) \
      if (planner.abl_enabled) { \
        const float zadj = bilinear_z_offset(V); \
        delta[A_AXIS] += zadj; \
        delta[B_AXIS] += zadj; \
        delta[C_AXIS] += zadj; \
      }
  #else
    #define ADJUST_DELTA(V) if (planner.abl_enabled) { delta[Z_AXIS] += bilinear_z_offset(V); }
  #endif
#elif IS_KINEMATIC
  #define ADJUST_DELTA(V) NOOP
#endif

#if ENABLED(Z_DUAL_ENDSTOPS)
  float z_endstop_adj =
    #ifdef Z_DUAL_ENDSTOPS_ADJUSTMENT
      Z_DUAL_ENDSTOPS_ADJUSTMENT
    #else
      0
    #endif
  ;
#endif

// Extruder offsets
#if HOTENDS > 1
  float hotend_offset[XYZ][HOTENDS];
#endif

#if HAS_Z_SERVO_ENDSTOP
  const int z_servo_angle[2] = Z_SERVO_ANGLES;
#endif

#if ENABLED(BARICUDA)
  int baricuda_valve_pressure = 0;
  int baricuda_e_to_p_pressure = 0;
#endif

#if ENABLED(FWRETRACT)

  bool autoretract_enabled = false;
  bool retracted[EXTRUDERS] = { false };
  bool retracted_swap[EXTRUDERS] = { false };

  float retract_length = RETRACT_LENGTH;
  float retract_length_swap = RETRACT_LENGTH_SWAP;
  float retract_feedrate_mm_s = RETRACT_FEEDRATE;
  float retract_zlift = RETRACT_ZLIFT;
  float retract_recover_length = RETRACT_RECOVER_LENGTH;
  float retract_recover_length_swap = RETRACT_RECOVER_LENGTH_SWAP;
  float retract_recover_feedrate_mm_s = RETRACT_RECOVER_FEEDRATE;

#endif // FWRETRACT

#if HAS_POWER_SWITCH
  bool powersupply_on =
    #if ENABLED(PS_DEFAULT_OFF)
      false
    #else
      true
    #endif
  ;
#endif

#if ENABLED(DELTA)

  float delta[ABC],
        endstop_adj[ABC] = { 0 };

  // These values are loaded or reset at boot time when setup() calls
  // settings.load(), which calls recalc_delta_settings().
  float delta_radius,
        delta_tower_angle_trim[2],
        delta_tower[ABC][2],
        delta_diagonal_rod,
        delta_calibration_radius,
        delta_diagonal_rod_2_tower[ABC],
        delta_segments_per_second,
        delta_clip_start_height = Z_MAX_POS;

  float delta_safe_distance_from_top();

#endif

#if ENABLED(AUTO_BED_LEVELING_BILINEAR)
  int bilinear_grid_spacing[2], bilinear_start[2];
  float bilinear_grid_factor[2],
        z_values[GRID_MAX_POINTS_X][GRID_MAX_POINTS_Y];
#endif

#if IS_SCARA
  // Float constants for SCARA calculations
  const float L1 = SCARA_LINKAGE_1, L2 = SCARA_LINKAGE_2,
              L1_2 = sq(float(L1)), L1_2_2 = 2.0 * L1_2,
              L2_2 = sq(float(L2));

  float delta_segments_per_second = SCARA_SEGMENTS_PER_SECOND,
        delta[ABC];
#endif

float cartes[XYZ] = { 0 };

#if ENABLED(FILAMENT_WIDTH_SENSOR)
  bool filament_sensor = false;                                 // M405 turns on filament sensor control. M406 turns it off.
  float filament_width_nominal = DEFAULT_NOMINAL_FILAMENT_DIA,  // Nominal filament width. Change with M404.
        filament_width_meas = DEFAULT_MEASURED_FILAMENT_DIA;    // Measured filament diameter
  uint8_t meas_delay_cm = MEASUREMENT_DELAY_CM,                 // Distance delay setting
          measurement_delay[MAX_MEASUREMENT_DELAY + 1];         // Ring buffer to delayed measurement. Store extruder factor after subtracting 100
  int8_t filwidth_delay_index[2] = { 0, -1 };                   // Indexes into ring buffer
#endif

#if ENABLED(FILAMENT_RUNOUT_SENSOR)
  static bool filament_ran_out = false;
#endif

#if ENABLED(ADVANCED_PAUSE_FEATURE)
  AdvancedPauseMenuResponse advanced_pause_menu_response;
#endif

#if ENABLED(MIXING_EXTRUDER)
  float mixing_factor[MIXING_STEPPERS]; // Reciprocal of mix proportion. 0.0 = off, otherwise >= 1.0.
  #if MIXING_VIRTUAL_TOOLS > 1
    float mixing_virtual_tool_mix[MIXING_VIRTUAL_TOOLS][MIXING_STEPPERS];
  #endif
#endif

static bool send_ok[BUFSIZE];

#if HAS_SERVOS
  Servo servo[NUM_SERVOS];
  #define MOVE_SERVO(I, P) servo[I].move(P)
  #if HAS_Z_SERVO_ENDSTOP
    #define DEPLOY_Z_SERVO() MOVE_SERVO(Z_ENDSTOP_SERVO_NR, z_servo_angle[0])
    #define STOW_Z_SERVO() MOVE_SERVO(Z_ENDSTOP_SERVO_NR, z_servo_angle[1])
  #endif
#endif

#ifdef CHDK
  millis_t chdkHigh = 0;
  bool chdkActive = false;
#endif

#ifdef AUTOMATIC_CURRENT_CONTROL
  bool auto_current_control = 0;
#endif

#if ENABLED(PID_EXTRUSION_SCALING)
  int lpq_len = 20;
#endif

#if ENABLED(HOST_KEEPALIVE_FEATURE)
  MarlinBusyState busy_state = NOT_BUSY;
  static millis_t next_busy_signal_ms = 0;
  uint8_t host_keepalive_interval = DEFAULT_KEEPALIVE_INTERVAL;
#else
  #define host_keepalive() NOOP
#endif

#if ENABLED(I2C_POSITION_ENCODERS)
  I2CPositionEncodersMgr I2CPEM;
  uint8_t blockBufferIndexRef = 0;
  millis_t lastUpdateMillis;
#endif

#if ENABLED(CNC_WORKSPACE_PLANES)
  static WorkspacePlane workspace_plane = PLANE_XY;
#endif

FORCE_INLINE float pgm_read_any(const float *p) { return pgm_read_float_near(p); }
FORCE_INLINE signed char pgm_read_any(const signed char *p) { return pgm_read_byte_near(p); }

#define XYZ_CONSTS_FROM_CONFIG(type, array, CONFIG) \
  static const PROGMEM type array##_P[XYZ] = { X_##CONFIG, Y_##CONFIG, Z_##CONFIG }; \
  static inline type array(AxisEnum axis) { return pgm_read_any(&array##_P[axis]); } \
  typedef void __void_##CONFIG##__

XYZ_CONSTS_FROM_CONFIG(float, base_min_pos,   MIN_POS);
XYZ_CONSTS_FROM_CONFIG(float, base_max_pos,   MAX_POS);
XYZ_CONSTS_FROM_CONFIG(float, base_home_pos,  HOME_POS);
XYZ_CONSTS_FROM_CONFIG(float, max_length,     MAX_LENGTH);
XYZ_CONSTS_FROM_CONFIG(float, home_bump_mm,   HOME_BUMP_MM);
XYZ_CONSTS_FROM_CONFIG(signed char, home_dir, HOME_DIR);

/**
 * ***************************************************************************
 * ******************************** FUNCTIONS ********************************
 * ***************************************************************************
 */

void stop();

void get_available_commands();
void process_next_command();
void prepare_move_to_destination();

void get_cartesian_from_steppers();
void set_current_from_steppers_for_axis(const AxisEnum axis);

#if ENABLED(ARC_SUPPORT)
  void plan_arc(float target[XYZE], float* offset, uint8_t clockwise);
#endif

#if ENABLED(BEZIER_CURVE_SUPPORT)
  void plan_cubic_move(const float offset[4]);
#endif

void tool_change(const uint8_t tmp_extruder, const float fr_mm_s=0.0, bool no_move=false);
void report_current_position();
void report_current_position_detail();

#if ENABLED(DEBUG_LEVELING_FEATURE)
  void print_xyz(const char* prefix, const char* suffix, const float x, const float y, const float z) {
    serialprintPGM(prefix);
    SERIAL_CHAR('(');
    SERIAL_ECHO(x);
    SERIAL_ECHOPAIR(", ", y);
    SERIAL_ECHOPAIR(", ", z);
    SERIAL_CHAR(')');
    if (suffix) serialprintPGM(suffix); else SERIAL_EOL();
  }

  void print_xyz(const char* prefix, const char* suffix, const float xyz[]) {
    print_xyz(prefix, suffix, xyz[X_AXIS], xyz[Y_AXIS], xyz[Z_AXIS]);
  }

  #if HAS_ABL
    void print_xyz(const char* prefix, const char* suffix, const vector_3 &xyz) {
      print_xyz(prefix, suffix, xyz.x, xyz.y, xyz.z);
    }
  #endif

  #define DEBUG_POS(SUFFIX,VAR) do { \
    print_xyz(PSTR("  " STRINGIFY(VAR) "="), PSTR(" : " SUFFIX "\n"), VAR); }while(0)
#endif

/**
 * sync_plan_position
 *
 * Set the planner/stepper positions directly from current_position with
 * no kinematic translation. Used for homing axes and cartesian/core syncing.
 */
void sync_plan_position() {
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) DEBUG_POS("sync_plan_position", current_position);
  #endif
  planner.set_position_mm(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS], current_position[E_AXIS]);
}
inline void sync_plan_position_e() { planner.set_e_position_mm(current_position[E_AXIS]); }

#if IS_KINEMATIC

  inline void sync_plan_position_kinematic() {
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS("sync_plan_position_kinematic", current_position);
    #endif
    planner.set_position_mm_kinematic(current_position);
  }
  #define SYNC_PLAN_POSITION_KINEMATIC() sync_plan_position_kinematic()

#else

  #define SYNC_PLAN_POSITION_KINEMATIC() sync_plan_position()

#endif

#if ENABLED(SDSUPPORT)
  #include "SdFatUtil.h"
  int freeMemory() { return SdFatUtil::FreeRam(); }
#else
extern "C" {
  extern char __bss_end;
  extern char __heap_start;
  extern void* __brkval;

  int freeMemory() {
    int free_memory;
    if ((int)__brkval == 0)
      free_memory = ((int)&free_memory) - ((int)&__bss_end);
    else
      free_memory = ((int)&free_memory) - ((int)__brkval);
    return free_memory;
  }
}
#endif // !SDSUPPORT

#if ENABLED(DIGIPOT_I2C)
  extern void digipot_i2c_set_current(uint8_t channel, float current);
  extern void digipot_i2c_init();
#endif

/**
 * Inject the next "immediate" command, when possible, onto the front of the queue.
 * Return true if any immediate commands remain to inject.
 */
static bool drain_injected_commands_P() {
  if (injected_commands_P != NULL) {
    size_t i = 0;
    char c, cmd[30];
    strncpy_P(cmd, injected_commands_P, sizeof(cmd) - 1);
    cmd[sizeof(cmd) - 1] = '\0';
    while ((c = cmd[i]) && c != '\n') i++; // find the end of this gcode command
    cmd[i] = '\0';
    if (enqueue_and_echo_command(cmd))     // success?
      injected_commands_P = c ? injected_commands_P + i + 1 : NULL; // next command or done
  }
  return (injected_commands_P != NULL);    // return whether any more remain
}

/**
 * Record one or many commands to run from program memory.
 * Aborts the current queue, if any.
 * Note: drain_injected_commands_P() must be called repeatedly to drain the commands afterwards
 */
void enqueue_and_echo_commands_P(const char * const pgcode) {
  injected_commands_P = pgcode;
  drain_injected_commands_P(); // first command executed asap (when possible)
}

/**
 * Clear the Marlin command queue
 */
void clear_command_queue() {
  cmd_queue_index_r = cmd_queue_index_w;
  commands_in_queue = 0;
}

/**
 * Once a new command is in the ring buffer, call this to commit it
 */
inline void _commit_command(bool say_ok) {
  send_ok[cmd_queue_index_w] = say_ok;
  if (++cmd_queue_index_w >= BUFSIZE) cmd_queue_index_w = 0;
  commands_in_queue++;
}

/**
 * Copy a command from RAM into the main command buffer.
 * Return true if the command was successfully added.
 * Return false for a full buffer, or if the 'command' is a comment.
 */
inline bool _enqueuecommand(const char* cmd, bool say_ok=false) {
  if (*cmd == ';' || commands_in_queue >= BUFSIZE) return false;
  strcpy(command_queue[cmd_queue_index_w], cmd);
  _commit_command(say_ok);
  return true;
}

/**
 * Enqueue with Serial Echo
 */
bool enqueue_and_echo_command(const char* cmd, bool say_ok/*=false*/) {
  if (_enqueuecommand(cmd, say_ok)) {
    SERIAL_ECHO_START();
    SERIAL_ECHOPAIR(MSG_ENQUEUEING, cmd);
    SERIAL_CHAR('"');
    SERIAL_EOL();
    return true;
  }
  return false;
}

void setup_killpin() {
  #if HAS_KILL
    SET_INPUT_PULLUP(KILL_PIN);
  #endif
}

#if ENABLED(FILAMENT_RUNOUT_SENSOR)

  void setup_filrunoutpin() {
    #if ENABLED(ENDSTOPPULLUP_FIL_RUNOUT)
      SET_INPUT_PULLUP(FIL_RUNOUT_PIN);
    #else
      SET_INPUT(FIL_RUNOUT_PIN);
    #endif
  }

#endif

void setup_powerhold() {
  #if HAS_SUICIDE
    OUT_WRITE(SUICIDE_PIN, HIGH);
  #endif
  #if HAS_POWER_SWITCH
    #if ENABLED(PS_DEFAULT_OFF)
      OUT_WRITE(PS_ON_PIN, PS_ON_ASLEEP);
    #else
      OUT_WRITE(PS_ON_PIN, PS_ON_AWAKE);
    #endif
  #endif
}

void suicide() {
  #if HAS_SUICIDE
    OUT_WRITE(SUICIDE_PIN, LOW);
  #endif
}

void servo_init() {
  #if NUM_SERVOS >= 1 && HAS_SERVO_0
    servo[0].attach(SERVO0_PIN);
    servo[0].detach(); // Just set up the pin. We don't have a position yet. Don't move to a random position.
  #endif
  #if NUM_SERVOS >= 2 && HAS_SERVO_1
    servo[1].attach(SERVO1_PIN);
    servo[1].detach();
  #endif
  #if NUM_SERVOS >= 3 && HAS_SERVO_2
    servo[2].attach(SERVO2_PIN);
    servo[2].detach();
  #endif
  #if NUM_SERVOS >= 4 && HAS_SERVO_3
    servo[3].attach(SERVO3_PIN);
    servo[3].detach();
  #endif

  #if HAS_Z_SERVO_ENDSTOP
    /**
     * Set position of Z Servo Endstop
     *
     * The servo might be deployed and positioned too low to stow
     * when starting up the machine or rebooting the board.
     * There's no way to know where the nozzle is positioned until
     * homing has been done - no homing with z-probe without init!
     *
     */
    STOW_Z_SERVO();
  #endif
}

/**
 * Stepper Reset (RigidBoard, et.al.)
 */
#if HAS_STEPPER_RESET
  void disableStepperDrivers() {
    OUT_WRITE(STEPPER_RESET_PIN, LOW);  // drive it down to hold in reset motor driver chips
  }
  void enableStepperDrivers() { SET_INPUT(STEPPER_RESET_PIN); }  // set to input, which allows it to be pulled high by pullups
#endif

#if ENABLED(EXPERIMENTAL_I2CBUS) && I2C_SLAVE_ADDRESS > 0

  void i2c_on_receive(int bytes) { // just echo all bytes received to serial
    i2c.receive(bytes);
  }

  void i2c_on_request() {          // just send dummy data for now
    i2c.reply("Hello World!\n");
  }

#endif

#if HAS_COLOR_LEDS

  void set_led_color(
    const uint8_t r, const uint8_t g, const uint8_t b
      #if ENABLED(RGBW_LED)
        , const uint8_t w=0
      #endif
  ) {

    #if ENABLED(BLINKM)

      // This variant uses i2c to send the RGB components to the device.
      SendColors(r, g, b);

    #endif

    #if ENABLED(RGB_LED) || ENABLED(RGBW_LED)

      // This variant uses 3 separate pins for the RGB components.
      // If the pins can do PWM then their intensity will be set.
      WRITE(RGB_LED_R_PIN, r ? HIGH : LOW);
      WRITE(RGB_LED_G_PIN, g ? HIGH : LOW);
      WRITE(RGB_LED_B_PIN, b ? HIGH : LOW);
      analogWrite(RGB_LED_R_PIN, r);
      analogWrite(RGB_LED_G_PIN, g);
      analogWrite(RGB_LED_B_PIN, b);

      #if ENABLED(RGBW_LED)
        WRITE(RGB_LED_W_PIN, w ? HIGH : LOW);
        analogWrite(RGB_LED_W_PIN, w);
      #endif

    #endif

    #if ENABLED(PCA9632)
      // Update I2C LED driver
      PCA9632_SetColor(r, g, b);
    #endif
  }

#endif // HAS_COLOR_LEDS

void gcode_line_error(const char* err, bool doFlush = true) {
  SERIAL_ERROR_START();
  serialprintPGM(err);
  SERIAL_ERRORLN(gcode_LastN);
  //Serial.println(gcode_N);
  if (doFlush) FlushSerialRequestResend();
  serial_count = 0;
}

/**
 * Get all commands waiting on the serial port and queue them.
 * Exit when the buffer is full or when no more characters are
 * left on the serial port.
 */
inline void get_serial_commands() {
  static char serial_line_buffer[MAX_CMD_SIZE];
  static bool serial_comment_mode = false;

  // If the command buffer is empty for too long,
  // send "wait" to indicate Marlin is still waiting.
  #if defined(NO_TIMEOUTS) && NO_TIMEOUTS > 0
    static millis_t last_command_time = 0;
    const millis_t ms = millis();
    if (commands_in_queue == 0 && !MYSERIAL.available() && ELAPSED(ms, last_command_time + NO_TIMEOUTS)) {
      SERIAL_ECHOLNPGM(MSG_WAIT);
      last_command_time = ms;
    }
  #endif

  /**
   * Loop while serial characters are incoming and the queue is not full
   */
  while (commands_in_queue < BUFSIZE && MYSERIAL.available() > 0) {

    char serial_char = MYSERIAL.read();

    /**
     * If the character ends the line
     */
    if (serial_char == '\n' || serial_char == '\r') {

      serial_comment_mode = false; // end of line == end of comment

      if (!serial_count) continue; // skip empty lines

      serial_line_buffer[serial_count] = 0; // terminate string
      serial_count = 0; //reset buffer

      char* command = serial_line_buffer;

      while (*command == ' ') command++; // skip any leading spaces
      char *npos = (*command == 'N') ? command : NULL, // Require the N parameter to start the line
           *apos = strchr(command, '*');

      if (npos) {

        bool M110 = strstr_P(command, PSTR("M110")) != NULL;

        if (M110) {
          char* n2pos = strchr(command + 4, 'N');
          if (n2pos) npos = n2pos;
        }

        gcode_N = strtol(npos + 1, NULL, 10);

        if (gcode_N != gcode_LastN + 1 && !M110) {
          gcode_line_error(PSTR(MSG_ERR_LINE_NO));
          return;
        }

        if (apos) {
          byte checksum = 0, count = 0;
          while (command[count] != '*') checksum ^= command[count++];

          if (strtol(apos + 1, NULL, 10) != checksum) {
            gcode_line_error(PSTR(MSG_ERR_CHECKSUM_MISMATCH));
            return;
          }
          // if no errors, continue parsing
        }
        else {
          gcode_line_error(PSTR(MSG_ERR_NO_CHECKSUM));
          return;
        }

        gcode_LastN = gcode_N;
        // if no errors, continue parsing
      }
      else if (apos) { // No '*' without 'N'
        gcode_line_error(PSTR(MSG_ERR_NO_LINENUMBER_WITH_CHECKSUM), false);
        return;
      }

      // Movement commands alert when stopped
      if (IsStopped()) {
        char* gpos = strchr(command, 'G');
        if (gpos) {
          const int codenum = strtol(gpos + 1, NULL, 10);
          switch (codenum) {
            case 0:
            case 1:
            case 2:
            case 3:
              SERIAL_ERRORLNPGM(MSG_ERR_STOPPED);
              LCD_MESSAGEPGM(MSG_STOPPED);
              break;
          }
        }
      }

      #if DISABLED(EMERGENCY_PARSER)
        // If command was e-stop process now
        if (strcmp(command, "M108") == 0) {
          wait_for_heatup = false;
          #if ENABLED(ULTIPANEL)
            wait_for_user = false;
          #endif
        }
        if (strcmp(command, "M112") == 0) kill(PSTR(MSG_KILLED));
        if (strcmp(command, "M410") == 0) { quickstop_stepper(); }
      #endif

      #if defined(NO_TIMEOUTS) && NO_TIMEOUTS > 0
        last_command_time = ms;
      #endif

      // Add the command to the queue
      _enqueuecommand(serial_line_buffer, true);
    }
    else if (serial_count >= MAX_CMD_SIZE - 1) {
      // Keep fetching, but ignore normal characters beyond the max length
      // The command will be injected when EOL is reached
    }
    else if (serial_char == '\\') {  // Handle escapes
      if (MYSERIAL.available() > 0) {
        // if we have one more character, copy it over
        serial_char = MYSERIAL.read();
        if (!serial_comment_mode) serial_line_buffer[serial_count++] = serial_char;
      }
      // otherwise do nothing
    }
    else { // it's not a newline, carriage return or escape char
      if (serial_char == ';') serial_comment_mode = true;
      if (!serial_comment_mode) serial_line_buffer[serial_count++] = serial_char;
    }

  } // queue has space, serial has data
}

#if ENABLED(SDSUPPORT)

  /**
   * Get commands from the SD Card until the command buffer is full
   * or until the end of the file is reached. The special character '#'
   * can also interrupt buffering.
   */
  inline void get_sdcard_commands() {
    static bool stop_buffering = false,
                sd_comment_mode = false;

    if (!card.sdprinting) return;

    /**
     * '#' stops reading from SD to the buffer prematurely, so procedural
     * macro calls are possible. If it occurs, stop_buffering is triggered
     * and the buffer is run dry; this character _can_ occur in serial com
     * due to checksums, however, no checksums are used in SD printing.
     */

    if (commands_in_queue == 0) stop_buffering = false;

    uint16_t sd_count = 0;
    bool card_eof = card.eof();
    while (commands_in_queue < BUFSIZE && !card_eof && !stop_buffering) {
      const int16_t n = card.get();
      char sd_char = (char)n;
      card_eof = card.eof();
      if (card_eof || n == -1
          || sd_char == '\n' || sd_char == '\r'
          || ((sd_char == '#' || sd_char == ':') && !sd_comment_mode)
      ) {
        if (card_eof) {
          SERIAL_PROTOCOLLNPGM(MSG_FILE_PRINTED);
          card.printingHasFinished();
          #if ENABLED(PRINTER_EVENT_LEDS)
            LCD_MESSAGEPGM(MSG_INFO_COMPLETED_PRINTS);
            set_led_color(0, 255, 0); // Green
            #if HAS_RESUME_CONTINUE
              enqueue_and_echo_commands_P(PSTR("M0")); // end of the queue!
            #else
              safe_delay(1000);
            #endif
            set_led_color(0, 0, 0);   // OFF
          #endif
          card.checkautostart(true);
        }
        else if (n == -1) {
          SERIAL_ERROR_START();
          SERIAL_ECHOLNPGM(MSG_SD_ERR_READ);
        }
        if (sd_char == '#') stop_buffering = true;

        sd_comment_mode = false; // for new command

        if (!sd_count) continue; // skip empty lines (and comment lines)

        command_queue[cmd_queue_index_w][sd_count] = '\0'; // terminate string
        sd_count = 0; // clear sd line buffer

        _commit_command(false);
      }
      else if (sd_count >= MAX_CMD_SIZE - 1) {
        /**
         * Keep fetching, but ignore normal characters beyond the max length
         * The command will be injected when EOL is reached
         */
      }
      else {
        if (sd_char == ';') sd_comment_mode = true;
        if (!sd_comment_mode) command_queue[cmd_queue_index_w][sd_count++] = sd_char;
      }
    }
  }

#endif // SDSUPPORT

/**
 * Add to the circular command queue the next command from:
 *  - The command-injection queue (injected_commands_P)
 *  - The active serial input (usually USB)
 *  - The SD card file being actively printed
 */
void get_available_commands() {

  // if any immediate commands remain, don't get other commands yet
  if (drain_injected_commands_P()) return;

  get_serial_commands();

  #if ENABLED(SDSUPPORT)
    get_sdcard_commands();
  #endif
}

/**
 * Set target_extruder from the T parameter or the active_extruder
 *
 * Returns TRUE if the target is invalid
 */
bool get_target_extruder_from_command(const uint16_t code) {
  if (parser.seenval('T')) {
    const int8_t e = parser.value_byte();
    if (e >= EXTRUDERS) {
      SERIAL_ECHO_START();
      SERIAL_CHAR('M');
      SERIAL_ECHO(code);
      SERIAL_ECHOLNPAIR(" " MSG_INVALID_EXTRUDER " ", e);
      return true;
    }
    target_extruder = e;
  }
  else
    target_extruder = active_extruder;

  return false;
}

#if ENABLED(DUAL_X_CARRIAGE) || ENABLED(DUAL_NOZZLE_DUPLICATION_MODE)
  bool extruder_duplication_enabled = false; // Used in Dual X mode 2
#endif

#if ENABLED(DUAL_X_CARRIAGE)

  static DualXMode dual_x_carriage_mode = DEFAULT_DUAL_X_CARRIAGE_MODE;

  static float x_home_pos(const int extruder) {
    if (extruder == 0)
      return LOGICAL_X_POSITION(base_home_pos(X_AXIS));
    else
      /**
       * In dual carriage mode the extruder offset provides an override of the
       * second X-carriage position when homed - otherwise X2_HOME_POS is used.
       * This allows soft recalibration of the second extruder home position
       * without firmware reflash (through the M218 command).
       */
      return LOGICAL_X_POSITION(hotend_offset[X_AXIS][1] > 0 ? hotend_offset[X_AXIS][1] : X2_HOME_POS);
  }

  static int x_home_dir(const int extruder) { return extruder ? X2_HOME_DIR : X_HOME_DIR; }

  static float inactive_extruder_x_pos = X2_MAX_POS; // used in mode 0 & 1
  static bool active_extruder_parked = false;        // used in mode 1 & 2
  static float raised_parked_position[XYZE];         // used in mode 1
  static millis_t delayed_move_time = 0;             // used in mode 1
  static float duplicate_extruder_x_offset = DEFAULT_DUPLICATION_X_OFFSET; // used in mode 2
  static int16_t duplicate_extruder_temp_offset = 0; // used in mode 2

#endif // DUAL_X_CARRIAGE

#if HAS_WORKSPACE_OFFSET || ENABLED(DUAL_X_CARRIAGE)

  /**
   * Software endstops can be used to monitor the open end of
   * an axis that has a hardware endstop on the other end. Or
   * they can prevent axes from moving past endstops and grinding.
   *
   * To keep doing their job as the coordinate system changes,
   * the software endstop positions must be refreshed to remain
   * at the same positions relative to the machine.
   */
  void update_software_endstops(const AxisEnum axis) {
    const float offs = 0.0
      #if HAS_HOME_OFFSET
        + home_offset[axis]
      #endif
      #if HAS_POSITION_SHIFT
        + position_shift[axis]
      #endif
    ;

    #if HAS_HOME_OFFSET && HAS_POSITION_SHIFT
      workspace_offset[axis] = offs;
    #endif

    #if ENABLED(DUAL_X_CARRIAGE)
      if (axis == X_AXIS) {

        // In Dual X mode hotend_offset[X] is T1's home position
        float dual_max_x = max(hotend_offset[X_AXIS][1], X2_MAX_POS);

        if (active_extruder != 0) {
          // T1 can move from X2_MIN_POS to X2_MAX_POS or X2 home position (whichever is larger)
          soft_endstop_min[X_AXIS] = X2_MIN_POS + offs;
          soft_endstop_max[X_AXIS] = dual_max_x + offs;
        }
        else if (dual_x_carriage_mode == DXC_DUPLICATION_MODE) {
          // In Duplication Mode, T0 can move as far left as X_MIN_POS
          // but not so far to the right that T1 would move past the end
          soft_endstop_min[X_AXIS] = base_min_pos(X_AXIS) + offs;
          soft_endstop_max[X_AXIS] = min(base_max_pos(X_AXIS), dual_max_x - duplicate_extruder_x_offset) + offs;
        }
        else {
          // In other modes, T0 can move from X_MIN_POS to X_MAX_POS
          soft_endstop_min[axis] = base_min_pos(axis) + offs;
          soft_endstop_max[axis] = base_max_pos(axis) + offs;
        }
      }
    #else
      soft_endstop_min[axis] = base_min_pos(axis) + offs;
      soft_endstop_max[axis] = base_max_pos(axis) + offs;
    #endif

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPAIR("For ", axis_codes[axis]);
        #if HAS_HOME_OFFSET
          SERIAL_ECHOPAIR(" axis:\n home_offset = ", home_offset[axis]);
        #endif
        #if HAS_POSITION_SHIFT
          SERIAL_ECHOPAIR("\n position_shift = ", position_shift[axis]);
        #endif
        SERIAL_ECHOPAIR("\n soft_endstop_min = ", soft_endstop_min[axis]);
        SERIAL_ECHOLNPAIR("\n soft_endstop_max = ", soft_endstop_max[axis]);
      }
    #endif

    #if ENABLED(DELTA)
      if (axis == Z_AXIS)
        delta_clip_start_height = soft_endstop_max[axis] - delta_safe_distance_from_top();
    #endif
  }

#endif // HAS_WORKSPACE_OFFSET || DUAL_X_CARRIAGE

#if HAS_M206_COMMAND
  /**
   * Change the home offset for an axis, update the current
   * position and the software endstops to retain the same
   * relative distance to the new home.
   *
   * Since this changes the current_position, code should
   * call sync_plan_position soon after this.
   */
  static void set_home_offset(const AxisEnum axis, const float v) {
    current_position[axis] += v - home_offset[axis];
    home_offset[axis] = v;
    update_software_endstops(axis);
  }
#endif // HAS_M206_COMMAND

/**
 * Set an axis' current position to its home position (after homing).
 *
 * For Core and Cartesian robots this applies one-to-one when an
 * individual axis has been homed.
 *
 * DELTA should wait until all homing is done before setting the XYZ
 * current_position to home, because homing is a single operation.
 * In the case where the axis positions are already known and previously
 * homed, DELTA could home to X or Y individually by moving either one
 * to the center. However, homing Z always homes XY and Z.
 *
 * SCARA should wait until all XY homing is done before setting the XY
 * current_position to home, because neither X nor Y is at home until
 * both are at home. Z can however be homed individually.
 *
 * Callers must sync the planner position after calling this!
 */
static void set_axis_is_at_home(const AxisEnum axis) {
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      SERIAL_ECHOPAIR(">>> set_axis_is_at_home(", axis_codes[axis]);
      SERIAL_CHAR(')');
      SERIAL_EOL();
    }
  #endif

  axis_known_position[axis] = axis_homed[axis] = true;

  #if HAS_POSITION_SHIFT
    position_shift[axis] = 0;
    update_software_endstops(axis);
  #endif

  #if ENABLED(DUAL_X_CARRIAGE)
    if (axis == X_AXIS && (active_extruder == 1 || dual_x_carriage_mode == DXC_DUPLICATION_MODE)) {
      current_position[X_AXIS] = x_home_pos(active_extruder);
      return;
    }
  #endif

  #if ENABLED(MORGAN_SCARA)

    /**
     * Morgan SCARA homes XY at the same time
     */
    if (axis == X_AXIS || axis == Y_AXIS) {

      float homeposition[XYZ];
      LOOP_XYZ(i) homeposition[i] = LOGICAL_POSITION(base_home_pos((AxisEnum)i), i);

      // SERIAL_ECHOPAIR("homeposition X:", homeposition[X_AXIS]);
      // SERIAL_ECHOLNPAIR(" Y:", homeposition[Y_AXIS]);

      /**
       * Get Home position SCARA arm angles using inverse kinematics,
       * and calculate homing offset using forward kinematics
       */
      inverse_kinematics(homeposition);
      forward_kinematics_SCARA(delta[A_AXIS], delta[B_AXIS]);

      // SERIAL_ECHOPAIR("Cartesian X:", cartes[X_AXIS]);
      // SERIAL_ECHOLNPAIR(" Y:", cartes[Y_AXIS]);

      current_position[axis] = LOGICAL_POSITION(cartes[axis], axis);

      /**
       * SCARA home positions are based on configuration since the actual
       * limits are determined by the inverse kinematic transform.
       */
      soft_endstop_min[axis] = base_min_pos(axis); // + (cartes[axis] - base_home_pos(axis));
      soft_endstop_max[axis] = base_max_pos(axis); // + (cartes[axis] - base_home_pos(axis));
    }
    else
  #endif
  {
    current_position[axis] = LOGICAL_POSITION(base_home_pos(axis), axis);
  }

  /**
   * Z Probe Z Homing? Account for the probe's Z offset.
   */
  #if HAS_BED_PROBE && Z_HOME_DIR < 0
    if (axis == Z_AXIS) {
      #if HOMING_Z_WITH_PROBE

        current_position[Z_AXIS] -= zprobe_zoffset;

        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) {
            SERIAL_ECHOLNPGM("*** Z HOMED WITH PROBE (Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN) ***");
            SERIAL_ECHOLNPAIR("> zprobe_zoffset = ", zprobe_zoffset);
          }
        #endif

      #elif ENABLED(DEBUG_LEVELING_FEATURE)

        if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("*** Z HOMED TO ENDSTOP (Z_MIN_PROBE_ENDSTOP) ***");

      #endif
    }
  #endif

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      #if HAS_HOME_OFFSET
        SERIAL_ECHOPAIR("> home_offset[", axis_codes[axis]);
        SERIAL_ECHOLNPAIR("] = ", home_offset[axis]);
      #endif
      DEBUG_POS("", current_position);
      SERIAL_ECHOPAIR("<<< set_axis_is_at_home(", axis_codes[axis]);
      SERIAL_CHAR(')');
      SERIAL_EOL();
    }
  #endif

  #if ENABLED(I2C_POSITION_ENCODERS)
    I2CPEM.homed(axis);
  #endif
}

/**
 * Some planner shorthand inline functions
 */
inline float get_homing_bump_feedrate(const AxisEnum axis) {
  static const uint8_t homing_bump_divisor[] PROGMEM = HOMING_BUMP_DIVISOR;
  uint8_t hbd = pgm_read_byte(&homing_bump_divisor[axis]);
  if (hbd < 1) {
    hbd = 10;
    SERIAL_ECHO_START();
    SERIAL_ECHOLNPGM("Warning: Homing Bump Divisor < 1");
  }
  return homing_feedrate(axis) / hbd;
}

/**
 * Move the planner to the current position from wherever it last moved
 * (or from wherever it has been told it is located).
 */
inline void line_to_current_position() {
  planner.buffer_line(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS], current_position[E_AXIS], feedrate_mm_s, active_extruder);
}

/**
 * Move the planner to the position stored in the destination array, which is
 * used by G0/G1/G2/G3/G5 and many other functions to set a destination.
 */
inline void line_to_destination(const float fr_mm_s) {
  planner.buffer_line(destination[X_AXIS], destination[Y_AXIS], destination[Z_AXIS], destination[E_AXIS], fr_mm_s, active_extruder);
}
inline void line_to_destination() { line_to_destination(feedrate_mm_s); }

inline void set_current_to_destination() { COPY(current_position, destination); }
inline void set_destination_to_current() { COPY(destination, current_position); }

#if IS_KINEMATIC
  /**
   * Calculate delta, start a line, and set current_position to destination
   */
  void prepare_uninterpolated_move_to_destination(const float fr_mm_s=0.0) {
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS("prepare_uninterpolated_move_to_destination", destination);
    #endif

    refresh_cmd_timeout();

    #if UBL_DELTA
      // ubl segmented line will do z-only moves in single segment
      ubl.prepare_segmented_line_to(destination, MMS_SCALED(fr_mm_s ? fr_mm_s : feedrate_mm_s));
    #else
      if ( current_position[X_AXIS] == destination[X_AXIS]
        && current_position[Y_AXIS] == destination[Y_AXIS]
        && current_position[Z_AXIS] == destination[Z_AXIS]
        && current_position[E_AXIS] == destination[E_AXIS]
      ) return;

      planner.buffer_line_kinematic(destination, MMS_SCALED(fr_mm_s ? fr_mm_s : feedrate_mm_s), active_extruder);
    #endif

    set_current_to_destination();
  }
#endif // IS_KINEMATIC

/**
 *  Plan a move to (X, Y, Z) and set the current_position
 *  The final current_position may not be the one that was requested
 */
void do_blocking_move_to(const float &lx, const float &ly, const float &lz, const float &fr_mm_s/*=0.0*/) {
  const float old_feedrate_mm_s = feedrate_mm_s;

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) print_xyz(PSTR(">>> do_blocking_move_to"), NULL, lx, ly, lz);
  #endif

  #if ENABLED(DELTA)

    if (!position_is_reachable_xy(lx, ly)) return;

    feedrate_mm_s = fr_mm_s ? fr_mm_s : XY_PROBE_FEEDRATE_MM_S;

    set_destination_to_current();          // sync destination at the start

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS("set_destination_to_current", destination);
    #endif

    // when in the danger zone
    if (current_position[Z_AXIS] > delta_clip_start_height) {
      if (lz > delta_clip_start_height) {   // staying in the danger zone
        destination[X_AXIS] = lx;           // move directly (uninterpolated)
        destination[Y_AXIS] = ly;
        destination[Z_AXIS] = lz;
        prepare_uninterpolated_move_to_destination(); // set_current_to_destination
        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) DEBUG_POS("danger zone move", current_position);
        #endif
        return;
      }
      else {
        destination[Z_AXIS] = delta_clip_start_height;
        prepare_uninterpolated_move_to_destination(); // set_current_to_destination
        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) DEBUG_POS("zone border move", current_position);
        #endif
      }
    }

    if (lz > current_position[Z_AXIS]) {    // raising?
      destination[Z_AXIS] = lz;
      prepare_uninterpolated_move_to_destination();   // set_current_to_destination
      #if ENABLED(DEBUG_LEVELING_FEATURE)
        if (DEBUGGING(LEVELING)) DEBUG_POS("z raise move", current_position);
      #endif
    }

    destination[X_AXIS] = lx;
    destination[Y_AXIS] = ly;
    prepare_move_to_destination();         // set_current_to_destination
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS("xy move", current_position);
    #endif

    if (lz < current_position[Z_AXIS]) {    // lowering?
      destination[Z_AXIS] = lz;
      prepare_uninterpolated_move_to_destination();   // set_current_to_destination
      #if ENABLED(DEBUG_LEVELING_FEATURE)
        if (DEBUGGING(LEVELING)) DEBUG_POS("z lower move", current_position);
      #endif
    }

  #elif IS_SCARA

    if (!position_is_reachable_xy(lx, ly)) return;

    set_destination_to_current();

    // If Z needs to raise, do it before moving XY
    if (destination[Z_AXIS] < lz) {
      destination[Z_AXIS] = lz;
      prepare_uninterpolated_move_to_destination(fr_mm_s ? fr_mm_s : homing_feedrate(Z_AXIS));
    }

    destination[X_AXIS] = lx;
    destination[Y_AXIS] = ly;
    prepare_uninterpolated_move_to_destination(fr_mm_s ? fr_mm_s : XY_PROBE_FEEDRATE_MM_S);

    // If Z needs to lower, do it after moving XY
    if (destination[Z_AXIS] > lz) {
      destination[Z_AXIS] = lz;
      prepare_uninterpolated_move_to_destination(fr_mm_s ? fr_mm_s : homing_feedrate(Z_AXIS));
    }

  #else

    // If Z needs to raise, do it before moving XY
    if (current_position[Z_AXIS] < lz) {
      feedrate_mm_s = fr_mm_s ? fr_mm_s : homing_feedrate(Z_AXIS);
      current_position[Z_AXIS] = lz;
      line_to_current_position();
    }

    feedrate_mm_s = fr_mm_s ? fr_mm_s : XY_PROBE_FEEDRATE_MM_S;
    current_position[X_AXIS] = lx;
    current_position[Y_AXIS] = ly;
    line_to_current_position();

    // If Z needs to lower, do it after moving XY
    if (current_position[Z_AXIS] > lz) {
      feedrate_mm_s = fr_mm_s ? fr_mm_s : homing_feedrate(Z_AXIS);
      current_position[Z_AXIS] = lz;
      line_to_current_position();
    }

  #endif

  stepper.synchronize();

  feedrate_mm_s = old_feedrate_mm_s;

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("<<< do_blocking_move_to");
  #endif
}
void do_blocking_move_to_x(const float &lx, const float &fr_mm_s/*=0.0*/) {
  do_blocking_move_to(lx, current_position[Y_AXIS], current_position[Z_AXIS], fr_mm_s);
}
void do_blocking_move_to_z(const float &lz, const float &fr_mm_s/*=0.0*/) {
  do_blocking_move_to(current_position[X_AXIS], current_position[Y_AXIS], lz, fr_mm_s);
}
void do_blocking_move_to_xy(const float &lx, const float &ly, const float &fr_mm_s/*=0.0*/) {
  do_blocking_move_to(lx, ly, current_position[Z_AXIS], fr_mm_s);
}

//
// Prepare to do endstop or probe moves
// with custom feedrates.
//
//  - Save current feedrates
//  - Reset the rate multiplier
//  - Reset the command timeout
//  - Enable the endstops (for endstop moves)
//
static void setup_for_endstop_or_probe_move() {
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) DEBUG_POS("setup_for_endstop_or_probe_move", current_position);
  #endif
  saved_feedrate_mm_s = feedrate_mm_s;
  saved_feedrate_percentage = feedrate_percentage;
  feedrate_percentage = 100;
  refresh_cmd_timeout();
}

static void clean_up_after_endstop_or_probe_move() {
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) DEBUG_POS("clean_up_after_endstop_or_probe_move", current_position);
  #endif
  feedrate_mm_s = saved_feedrate_mm_s;
  feedrate_percentage = saved_feedrate_percentage;
  refresh_cmd_timeout();
}

#if HAS_BED_PROBE
  /**
   * Raise Z to a minimum height to make room for a probe to move
   */
  inline void do_probe_raise(const float z_raise) {
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPAIR("do_probe_raise(", z_raise);
        SERIAL_CHAR(')');
        SERIAL_EOL();
      }
    #endif

    float z_dest = LOGICAL_Z_POSITION(z_raise);
    if (zprobe_zoffset < 0) z_dest -= zprobe_zoffset;

    #if ENABLED(DELTA)
      z_dest -= home_offset[Z_AXIS]; // Account for delta height adjustment
    #endif

    if (z_dest > current_position[Z_AXIS])
      do_blocking_move_to_z(z_dest);
  }

#endif // HAS_BED_PROBE

#if HAS_PROBING_PROCEDURE || HOTENDS > 1 || ENABLED(Z_PROBE_ALLEN_KEY) || ENABLED(Z_PROBE_SLED) || ENABLED(NOZZLE_CLEAN_FEATURE) || ENABLED(NOZZLE_PARK_FEATURE) || ENABLED(DELTA_AUTO_CALIBRATION)

  bool axis_unhomed_error(const bool x/*=true*/, const bool y/*=true*/, const bool z/*=true*/) {
    #if ENABLED(HOME_AFTER_DEACTIVATE)
      const bool xx = x && !axis_known_position[X_AXIS],
                 yy = y && !axis_known_position[Y_AXIS],
                 zz = z && !axis_known_position[Z_AXIS];
    #else
      const bool xx = x && !axis_homed[X_AXIS],
                 yy = y && !axis_homed[Y_AXIS],
                 zz = z && !axis_homed[Z_AXIS];
    #endif
    if (xx || yy || zz) {
      SERIAL_ECHO_START();
      SERIAL_ECHOPGM(MSG_HOME " ");
      if (xx) SERIAL_ECHOPGM(MSG_X);
      if (yy) SERIAL_ECHOPGM(MSG_Y);
      if (zz) SERIAL_ECHOPGM(MSG_Z);
      SERIAL_ECHOLNPGM(" " MSG_FIRST);

      #if ENABLED(ULTRA_LCD)
        lcd_status_printf_P(0, PSTR(MSG_HOME " %s%s%s " MSG_FIRST), xx ? MSG_X : "", yy ? MSG_Y : "", zz ? MSG_Z : "");
      #endif
      return true;
    }
    return false;
  }

#endif

#if ENABLED(Z_PROBE_SLED)

  #ifndef SLED_DOCKING_OFFSET
    #define SLED_DOCKING_OFFSET 0
  #endif

  /**
   * Method to dock/undock a sled designed by Charles Bell.
   *
   * stow[in]     If false, move to MAX_X and engage the solenoid
   *              If true, move to MAX_X and release the solenoid
   */
  static void dock_sled(bool stow) {
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPAIR("dock_sled(", stow);
        SERIAL_CHAR(')');
        SERIAL_EOL();
      }
    #endif

    // Dock sled a bit closer to ensure proper capturing
    do_blocking_move_to_x(X_MAX_POS + SLED_DOCKING_OFFSET - ((stow) ? 1 : 0));

    #if HAS_SOLENOID_1 && DISABLED(EXT_SOLENOID)
      WRITE(SOL1_PIN, !stow); // switch solenoid
    #endif
  }

#elif ENABLED(Z_PROBE_ALLEN_KEY)

  FORCE_INLINE void do_blocking_move_to(const float logical[XYZ], const float &fr_mm_s) {
    do_blocking_move_to(logical[X_AXIS], logical[Y_AXIS], logical[Z_AXIS], fr_mm_s);
  }

  void run_deploy_moves_script() {
    #if defined(Z_PROBE_ALLEN_KEY_DEPLOY_1_X) || defined(Z_PROBE_ALLEN_KEY_DEPLOY_1_Y) || defined(Z_PROBE_ALLEN_KEY_DEPLOY_1_Z)
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_1_X
        #define Z_PROBE_ALLEN_KEY_DEPLOY_1_X current_position[X_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_1_Y
        #define Z_PROBE_ALLEN_KEY_DEPLOY_1_Y current_position[Y_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_1_Z
        #define Z_PROBE_ALLEN_KEY_DEPLOY_1_Z current_position[Z_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_1_FEEDRATE
        #define Z_PROBE_ALLEN_KEY_DEPLOY_1_FEEDRATE 0.0
      #endif
      const float deploy_1[] = { Z_PROBE_ALLEN_KEY_DEPLOY_1_X, Z_PROBE_ALLEN_KEY_DEPLOY_1_Y, Z_PROBE_ALLEN_KEY_DEPLOY_1_Z };
      do_blocking_move_to(deploy_1, MMM_TO_MMS(Z_PROBE_ALLEN_KEY_DEPLOY_1_FEEDRATE));
    #endif
    #if defined(Z_PROBE_ALLEN_KEY_DEPLOY_2_X) || defined(Z_PROBE_ALLEN_KEY_DEPLOY_2_Y) || defined(Z_PROBE_ALLEN_KEY_DEPLOY_2_Z)
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_2_X
        #define Z_PROBE_ALLEN_KEY_DEPLOY_2_X current_position[X_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_2_Y
        #define Z_PROBE_ALLEN_KEY_DEPLOY_2_Y current_position[Y_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_2_Z
        #define Z_PROBE_ALLEN_KEY_DEPLOY_2_Z current_position[Z_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_2_FEEDRATE
        #define Z_PROBE_ALLEN_KEY_DEPLOY_2_FEEDRATE 0.0
      #endif
      const float deploy_2[] = { Z_PROBE_ALLEN_KEY_DEPLOY_2_X, Z_PROBE_ALLEN_KEY_DEPLOY_2_Y, Z_PROBE_ALLEN_KEY_DEPLOY_2_Z };
      do_blocking_move_to(deploy_2, MMM_TO_MMS(Z_PROBE_ALLEN_KEY_DEPLOY_2_FEEDRATE));
    #endif
    #if defined(Z_PROBE_ALLEN_KEY_DEPLOY_3_X) || defined(Z_PROBE_ALLEN_KEY_DEPLOY_3_Y) || defined(Z_PROBE_ALLEN_KEY_DEPLOY_3_Z)
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_3_X
        #define Z_PROBE_ALLEN_KEY_DEPLOY_3_X current_position[X_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_3_Y
        #define Z_PROBE_ALLEN_KEY_DEPLOY_3_Y current_position[Y_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_3_Z
        #define Z_PROBE_ALLEN_KEY_DEPLOY_3_Z current_position[Z_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_3_FEEDRATE
        #define Z_PROBE_ALLEN_KEY_DEPLOY_3_FEEDRATE 0.0
      #endif
      const float deploy_3[] = { Z_PROBE_ALLEN_KEY_DEPLOY_3_X, Z_PROBE_ALLEN_KEY_DEPLOY_3_Y, Z_PROBE_ALLEN_KEY_DEPLOY_3_Z };
      do_blocking_move_to(deploy_3, MMM_TO_MMS(Z_PROBE_ALLEN_KEY_DEPLOY_3_FEEDRATE));
    #endif
    #if defined(Z_PROBE_ALLEN_KEY_DEPLOY_4_X) || defined(Z_PROBE_ALLEN_KEY_DEPLOY_4_Y) || defined(Z_PROBE_ALLEN_KEY_DEPLOY_4_Z)
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_4_X
        #define Z_PROBE_ALLEN_KEY_DEPLOY_4_X current_position[X_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_4_Y
        #define Z_PROBE_ALLEN_KEY_DEPLOY_4_Y current_position[Y_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_4_Z
        #define Z_PROBE_ALLEN_KEY_DEPLOY_4_Z current_position[Z_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_4_FEEDRATE
        #define Z_PROBE_ALLEN_KEY_DEPLOY_4_FEEDRATE 0.0
      #endif
      const float deploy_4[] = { Z_PROBE_ALLEN_KEY_DEPLOY_4_X, Z_PROBE_ALLEN_KEY_DEPLOY_4_Y, Z_PROBE_ALLEN_KEY_DEPLOY_4_Z };
      do_blocking_move_to(deploy_4, MMM_TO_MMS(Z_PROBE_ALLEN_KEY_DEPLOY_4_FEEDRATE));
    #endif
    #if defined(Z_PROBE_ALLEN_KEY_DEPLOY_5_X) || defined(Z_PROBE_ALLEN_KEY_DEPLOY_5_Y) || defined(Z_PROBE_ALLEN_KEY_DEPLOY_5_Z)
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_5_X
        #define Z_PROBE_ALLEN_KEY_DEPLOY_5_X current_position[X_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_5_Y
        #define Z_PROBE_ALLEN_KEY_DEPLOY_5_Y current_position[Y_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_5_Z
        #define Z_PROBE_ALLEN_KEY_DEPLOY_5_Z current_position[Z_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_DEPLOY_5_FEEDRATE
        #define Z_PROBE_ALLEN_KEY_DEPLOY_5_FEEDRATE 0.0
      #endif
      const float deploy_5[] = { Z_PROBE_ALLEN_KEY_DEPLOY_5_X, Z_PROBE_ALLEN_KEY_DEPLOY_5_Y, Z_PROBE_ALLEN_KEY_DEPLOY_5_Z };
      do_blocking_move_to(deploy_5, MMM_TO_MMS(Z_PROBE_ALLEN_KEY_DEPLOY_5_FEEDRATE));
    #endif
  }

  void run_stow_moves_script() {
    #if defined(Z_PROBE_ALLEN_KEY_STOW_1_X) || defined(Z_PROBE_ALLEN_KEY_STOW_1_Y) || defined(Z_PROBE_ALLEN_KEY_STOW_1_Z)
      #ifndef Z_PROBE_ALLEN_KEY_STOW_1_X
        #define Z_PROBE_ALLEN_KEY_STOW_1_X current_position[X_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_1_Y
        #define Z_PROBE_ALLEN_KEY_STOW_1_Y current_position[Y_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_1_Z
        #define Z_PROBE_ALLEN_KEY_STOW_1_Z current_position[Z_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_1_FEEDRATE
        #define Z_PROBE_ALLEN_KEY_STOW_1_FEEDRATE 0.0
      #endif
      const float stow_1[] = { Z_PROBE_ALLEN_KEY_STOW_1_X, Z_PROBE_ALLEN_KEY_STOW_1_Y, Z_PROBE_ALLEN_KEY_STOW_1_Z };
      do_blocking_move_to(stow_1, MMM_TO_MMS(Z_PROBE_ALLEN_KEY_STOW_1_FEEDRATE));
    #endif
    #if defined(Z_PROBE_ALLEN_KEY_STOW_2_X) || defined(Z_PROBE_ALLEN_KEY_STOW_2_Y) || defined(Z_PROBE_ALLEN_KEY_STOW_2_Z)
      #ifndef Z_PROBE_ALLEN_KEY_STOW_2_X
        #define Z_PROBE_ALLEN_KEY_STOW_2_X current_position[X_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_2_Y
        #define Z_PROBE_ALLEN_KEY_STOW_2_Y current_position[Y_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_2_Z
        #define Z_PROBE_ALLEN_KEY_STOW_2_Z current_position[Z_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_2_FEEDRATE
        #define Z_PROBE_ALLEN_KEY_STOW_2_FEEDRATE 0.0
      #endif
      const float stow_2[] = { Z_PROBE_ALLEN_KEY_STOW_2_X, Z_PROBE_ALLEN_KEY_STOW_2_Y, Z_PROBE_ALLEN_KEY_STOW_2_Z };
      do_blocking_move_to(stow_2, MMM_TO_MMS(Z_PROBE_ALLEN_KEY_STOW_2_FEEDRATE));
    #endif
    #if defined(Z_PROBE_ALLEN_KEY_STOW_3_X) || defined(Z_PROBE_ALLEN_KEY_STOW_3_Y) || defined(Z_PROBE_ALLEN_KEY_STOW_3_Z)
      #ifndef Z_PROBE_ALLEN_KEY_STOW_3_X
        #define Z_PROBE_ALLEN_KEY_STOW_3_X current_position[X_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_3_Y
        #define Z_PROBE_ALLEN_KEY_STOW_3_Y current_position[Y_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_3_Z
        #define Z_PROBE_ALLEN_KEY_STOW_3_Z current_position[Z_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_3_FEEDRATE
        #define Z_PROBE_ALLEN_KEY_STOW_3_FEEDRATE 0.0
      #endif
      const float stow_3[] = { Z_PROBE_ALLEN_KEY_STOW_3_X, Z_PROBE_ALLEN_KEY_STOW_3_Y, Z_PROBE_ALLEN_KEY_STOW_3_Z };
      do_blocking_move_to(stow_3, MMM_TO_MMS(Z_PROBE_ALLEN_KEY_STOW_3_FEEDRATE));
    #endif
    #if defined(Z_PROBE_ALLEN_KEY_STOW_4_X) || defined(Z_PROBE_ALLEN_KEY_STOW_4_Y) || defined(Z_PROBE_ALLEN_KEY_STOW_4_Z)
      #ifndef Z_PROBE_ALLEN_KEY_STOW_4_X
        #define Z_PROBE_ALLEN_KEY_STOW_4_X current_position[X_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_4_Y
        #define Z_PROBE_ALLEN_KEY_STOW_4_Y current_position[Y_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_4_Z
        #define Z_PROBE_ALLEN_KEY_STOW_4_Z current_position[Z_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_4_FEEDRATE
        #define Z_PROBE_ALLEN_KEY_STOW_4_FEEDRATE 0.0
      #endif
      const float stow_4[] = { Z_PROBE_ALLEN_KEY_STOW_4_X, Z_PROBE_ALLEN_KEY_STOW_4_Y, Z_PROBE_ALLEN_KEY_STOW_4_Z };
      do_blocking_move_to(stow_4, MMM_TO_MMS(Z_PROBE_ALLEN_KEY_STOW_4_FEEDRATE));
    #endif
    #if defined(Z_PROBE_ALLEN_KEY_STOW_5_X) || defined(Z_PROBE_ALLEN_KEY_STOW_5_Y) || defined(Z_PROBE_ALLEN_KEY_STOW_5_Z)
      #ifndef Z_PROBE_ALLEN_KEY_STOW_5_X
        #define Z_PROBE_ALLEN_KEY_STOW_5_X current_position[X_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_5_Y
        #define Z_PROBE_ALLEN_KEY_STOW_5_Y current_position[Y_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_5_Z
        #define Z_PROBE_ALLEN_KEY_STOW_5_Z current_position[Z_AXIS]
      #endif
      #ifndef Z_PROBE_ALLEN_KEY_STOW_5_FEEDRATE
        #define Z_PROBE_ALLEN_KEY_STOW_5_FEEDRATE 0.0
      #endif
      const float stow_5[] = { Z_PROBE_ALLEN_KEY_STOW_5_X, Z_PROBE_ALLEN_KEY_STOW_5_Y, Z_PROBE_ALLEN_KEY_STOW_5_Z };
      do_blocking_move_to(stow_5, MMM_TO_MMS(Z_PROBE_ALLEN_KEY_STOW_5_FEEDRATE));
    #endif
  }

#endif

#if ENABLED(PROBING_FANS_OFF)

  void fans_pause(const bool p) {
    if (p != fans_paused) {
      fans_paused = p;
      if (p)
        for (uint8_t x = 0; x < FAN_COUNT; x++) {
          paused_fanSpeeds[x] = fanSpeeds[x];
          fanSpeeds[x] = 0;
        }
      else
        for (uint8_t x = 0; x < FAN_COUNT; x++)
          fanSpeeds[x] = paused_fanSpeeds[x];
    }
  }

#endif // PROBING_FANS_OFF

#if HAS_BED_PROBE

  // TRIGGERED_WHEN_STOWED_TEST can easily be extended to servo probes, ... if needed.
  #if ENABLED(PROBE_IS_TRIGGERED_WHEN_STOWED_TEST)
    #if ENABLED(Z_MIN_PROBE_ENDSTOP)
      #define _TRIGGERED_WHEN_STOWED_TEST (READ(Z_MIN_PROBE_PIN) != Z_MIN_PROBE_ENDSTOP_INVERTING)
    #else
      #define _TRIGGERED_WHEN_STOWED_TEST (READ(Z_MIN_PIN) != Z_MIN_ENDSTOP_INVERTING)
    #endif
  #endif

  #if QUIET_PROBING
    void probing_pause(const bool p) {
      #if ENABLED(PROBING_HEATERS_OFF)
        thermalManager.pause(p);
      #endif
      #if ENABLED(PROBING_FANS_OFF)
        fans_pause(p);
      #endif
      if (p) safe_delay(25);
    }
  #endif // QUIET_PROBING

  #if ENABLED(BLTOUCH)

    void bltouch_command(int angle) {
      servo[Z_ENDSTOP_SERVO_NR].move(angle);  // Give the BL-Touch the command and wait
      safe_delay(BLTOUCH_DELAY);
    }

    void set_bltouch_deployed(const bool deploy) {
      if (deploy && TEST_BLTOUCH()) {      // If BL-Touch says it's triggered
        bltouch_command(BLTOUCH_RESET);    //  try to reset it.
        bltouch_command(BLTOUCH_DEPLOY);   // Also needs to deploy and stow to
        bltouch_command(BLTOUCH_STOW);     //  clear the triggered condition.
        safe_delay(1500);                  // Wait for internal self-test to complete.
                                           //  (Measured completion time was 0.65 seconds
                                           //   after reset, deploy, and stow sequence)
        if (TEST_BLTOUCH()) {              // If it still claims to be triggered...
          SERIAL_ERROR_START();
          SERIAL_ERRORLNPGM(MSG_STOP_BLTOUCH);
          stop();                          // punt!
        }
      }

      bltouch_command(deploy ? BLTOUCH_DEPLOY : BLTOUCH_STOW);

      #if ENABLED(DEBUG_LEVELING_FEATURE)
        if (DEBUGGING(LEVELING)) {
          SERIAL_ECHOPAIR("set_bltouch_deployed(", deploy);
          SERIAL_CHAR(')');
          SERIAL_EOL();
        }
      #endif
    }

  #endif // BLTOUCH

  // returns false for ok and true for failure
  bool set_probe_deployed(bool deploy) {

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        DEBUG_POS("set_probe_deployed", current_position);
        SERIAL_ECHOLNPAIR("deploy: ", deploy);
      }
    #endif

    if (endstops.z_probe_enabled == deploy) return false;

    // Make room for probe
    do_probe_raise(_Z_CLEARANCE_DEPLOY_PROBE);

    // When deploying make sure BLTOUCH is not already triggered
    #if ENABLED(BLTOUCH)
      if (deploy && TEST_BLTOUCH()) {      // If BL-Touch says it's triggered
        bltouch_command(BLTOUCH_RESET);    // try to reset it.
        bltouch_command(BLTOUCH_DEPLOY);   // Also needs to deploy and stow to
        bltouch_command(BLTOUCH_STOW);     // clear the triggered condition.
        safe_delay(1500);                  // wait for internal self test to complete
                                           //   measured completion time was 0.65 seconds
                                           //   after reset, deploy & stow sequence
        if (TEST_BLTOUCH()) {              // If it still claims to be triggered...
          SERIAL_ERROR_START();
          SERIAL_ERRORLNPGM(MSG_STOP_BLTOUCH);
          stop();                          // punt!
          return true;
        }
      }
    #elif ENABLED(Z_PROBE_SLED) || ENABLED(Z_PROBE_ALLEN_KEY)
      #if ENABLED(Z_PROBE_SLED)
        #define _AUE_ARGS true, false, false
      #else
        #define _AUE_ARGS
      #endif
      if (axis_unhomed_error(_AUE_ARGS)) {
        SERIAL_ERROR_START();
        SERIAL_ERRORLNPGM(MSG_STOP_UNHOMED);
        stop();
        return true;
      }
    #endif

    const float oldXpos = current_position[X_AXIS],
                oldYpos = current_position[Y_AXIS];

    #ifdef _TRIGGERED_WHEN_STOWED_TEST

      // If endstop is already false, the Z probe is deployed
      if (_TRIGGERED_WHEN_STOWED_TEST == deploy) {     // closed after the probe specific actions.
                                                       // Would a goto be less ugly?
        //while (!_TRIGGERED_WHEN_STOWED_TEST) idle(); // would offer the opportunity
                                                       // for a triggered when stowed manual probe.

        if (!deploy) endstops.enable_z_probe(false); // Switch off triggered when stowed probes early
                                                     // otherwise an Allen-Key probe can't be stowed.
    #endif

        #if ENABLED(SOLENOID_PROBE)

          #if HAS_SOLENOID_1
            WRITE(SOL1_PIN, deploy);
          #endif

        #elif ENABLED(Z_PROBE_SLED)

          dock_sled(!deploy);

        #elif HAS_Z_SERVO_ENDSTOP && DISABLED(BLTOUCH)

          servo[Z_ENDSTOP_SERVO_NR].move(z_servo_angle[deploy ? 0 : 1]);

        #elif ENABLED(Z_PROBE_ALLEN_KEY)

          deploy ? run_deploy_moves_script() : run_stow_moves_script();

        #endif

    #ifdef _TRIGGERED_WHEN_STOWED_TEST
      } // _TRIGGERED_WHEN_STOWED_TEST == deploy

      if (_TRIGGERED_WHEN_STOWED_TEST == deploy) { // State hasn't changed?

        if (IsRunning()) {
          SERIAL_ERROR_START();
          SERIAL_ERRORLNPGM("Z-Probe failed");
          LCD_ALERTMESSAGEPGM("Err: ZPROBE");
        }
        stop();
        return true;

      } // _TRIGGERED_WHEN_STOWED_TEST == deploy

    #endif

    do_blocking_move_to(oldXpos, oldYpos, current_position[Z_AXIS]); // return to position before deploy
    endstops.enable_z_probe(deploy);
    return false;
  }

  static void do_probe_move(float z, float fr_mm_m) {
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS(">>> do_probe_move", current_position);
    #endif

    // Deploy BLTouch at the start of any probe
    #if ENABLED(BLTOUCH)
      set_bltouch_deployed(true);
    #endif

    #if QUIET_PROBING
      probing_pause(true);
    #endif

    // Move down until probe triggered
    do_blocking_move_to_z(LOGICAL_Z_POSITION(z), MMM_TO_MMS(fr_mm_m));

    #if QUIET_PROBING
      probing_pause(false);
    #endif

    // Retract BLTouch immediately after a probe
    #if ENABLED(BLTOUCH)
      set_bltouch_deployed(false);
    #endif

    // Clear endstop flags
    endstops.hit_on_purpose();

    // Get Z where the steppers were interrupted
    set_current_from_steppers_for_axis(Z_AXIS);

    // Tell the planner where we actually are
    SYNC_PLAN_POSITION_KINEMATIC();

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS("<<< do_probe_move", current_position);
    #endif
  }

  // Do a single Z probe and return with current_position[Z_AXIS]
  // at the height where the probe triggered.
  static float run_z_probe() {

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS(">>> run_z_probe", current_position);
    #endif

    // Prevent stepper_inactive_time from running out and EXTRUDER_RUNOUT_PREVENT from extruding
    refresh_cmd_timeout();

    #if ENABLED(PROBE_DOUBLE_TOUCH)

      // Do a first probe at the fast speed
      do_probe_move(-(Z_MAX_LENGTH) - 10, Z_PROBE_SPEED_FAST);

      #if ENABLED(DEBUG_LEVELING_FEATURE)
        float first_probe_z = current_position[Z_AXIS];
        if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPAIR("1st Probe Z:", first_probe_z);
      #endif

      // move up by the bump distance
      do_blocking_move_to_z(current_position[Z_AXIS] + home_bump_mm(Z_AXIS), MMM_TO_MMS(Z_PROBE_SPEED_FAST));

    #else

      // If the nozzle is above the travel height then
      // move down quickly before doing the slow probe
      float z = LOGICAL_Z_POSITION(Z_CLEARANCE_BETWEEN_PROBES);
      if (zprobe_zoffset < 0) z -= zprobe_zoffset;

      #if ENABLED(DELTA)
        z -= home_offset[Z_AXIS]; // Account for delta height adjustment
      #endif

      if (z < current_position[Z_AXIS])
        do_blocking_move_to_z(z, MMM_TO_MMS(Z_PROBE_SPEED_FAST));

    #endif

    // move down slowly to find bed
    do_probe_move(-(Z_MAX_LENGTH) - 10, Z_PROBE_SPEED_SLOW);

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS("<<< run_z_probe", current_position);
    #endif

    // Debug: compare probe heights
    #if ENABLED(PROBE_DOUBLE_TOUCH) && ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPAIR("2nd Probe Z:", current_position[Z_AXIS]);
        SERIAL_ECHOLNPAIR(" Discrepancy:", first_probe_z - current_position[Z_AXIS]);
      }
    #endif
    return RAW_CURRENT_POSITION(Z) + zprobe_zoffset
      #if ENABLED(DELTA)
        + home_offset[Z_AXIS] // Account for delta height adjustment
      #endif
    ;
  }

  /**
   * - Move to the given XY
   * - Deploy the probe, if not already deployed
   * - Probe the bed, get the Z position
   * - Depending on the 'stow' flag
   *   - Stow the probe, or
   *   - Raise to the BETWEEN height
   * - Return the probed Z position
   */
  float probe_pt(const float &lx, const float &ly, const bool stow, const uint8_t verbose_level, const bool printable=true) {
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPAIR(">>> probe_pt(", lx);
        SERIAL_ECHOPAIR(", ", ly);
        SERIAL_ECHOPAIR(", ", stow ? "" : "no ");
        SERIAL_ECHOLNPGM("stow)");
        DEBUG_POS("", current_position);
      }
    #endif

    const float nx = lx - (X_PROBE_OFFSET_FROM_EXTRUDER), ny = ly - (Y_PROBE_OFFSET_FROM_EXTRUDER);

    if (printable)
      if (!position_is_reachable_by_probe_xy(lx, ly)) return NAN;
    else
      if (!position_is_reachable_xy(nx, ny)) return NAN;

    const float old_feedrate_mm_s = feedrate_mm_s;

    #if ENABLED(DELTA)
      if (current_position[Z_AXIS] > delta_clip_start_height)
        do_blocking_move_to_z(delta_clip_start_height);
    #endif

    // Ensure a minimum height before moving the probe
    do_probe_raise(Z_CLEARANCE_BETWEEN_PROBES);

    feedrate_mm_s = XY_PROBE_FEEDRATE_MM_S;

    // Move the probe to the given XY
    do_blocking_move_to_xy(nx, ny);

    if (DEPLOY_PROBE()) return NAN;

    const float measured_z = run_z_probe();

    if (!stow)
      do_probe_raise(Z_CLEARANCE_BETWEEN_PROBES);
    else
      if (STOW_PROBE()) return NAN;

    if (verbose_level > 2) {
      SERIAL_PROTOCOLPGM("Bed X: ");
      SERIAL_PROTOCOL_F(lx, 3);
      SERIAL_PROTOCOLPGM(" Y: ");
      SERIAL_PROTOCOL_F(ly, 3);
      SERIAL_PROTOCOLPGM(" Z: ");
      SERIAL_PROTOCOL_F(measured_z, 3);
      SERIAL_EOL();
    }

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("<<< probe_pt");
    #endif

    feedrate_mm_s = old_feedrate_mm_s;

    return measured_z;
  }

#endif // HAS_BED_PROBE

#if HAS_LEVELING

  bool leveling_is_valid() {
    return
      #if ENABLED(MESH_BED_LEVELING)
        mbl.has_mesh()
      #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)
        !!bilinear_grid_spacing[X_AXIS]
      #elif ENABLED(AUTO_BED_LEVELING_UBL)
        true
      #else // 3POINT, LINEAR
        true
      #endif
    ;
  }

  bool leveling_is_active() {
    return
      #if ENABLED(MESH_BED_LEVELING)
        mbl.active()
      #elif ENABLED(AUTO_BED_LEVELING_UBL)
        ubl.state.active
      #else
        planner.abl_enabled
      #endif
    ;
  }

  /**
   * Turn bed leveling on or off, fixing the current
   * position as-needed.
   *
   * Disable: Current position = physical position
   *  Enable: Current position = "unleveled" physical position
   */
  void set_bed_leveling_enabled(const bool enable/*=true*/) {

    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
      const bool can_change = (!enable || leveling_is_valid());
    #else
      constexpr bool can_change = true;
    #endif

    if (can_change && enable != leveling_is_active()) {

      #if ENABLED(MESH_BED_LEVELING)

        if (!enable)
          planner.apply_leveling(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS]);

        const bool enabling = enable && leveling_is_valid();
        mbl.set_active(enabling);
        if (enabling) planner.unapply_leveling(current_position);

      #elif ENABLED(AUTO_BED_LEVELING_UBL)
        #if PLANNER_LEVELING
          if (ubl.state.active) {                       // leveling from on to off
            // change unleveled current_position to physical current_position without moving steppers.
            planner.apply_leveling(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS]);
            ubl.state.active = false;                   // disable only AFTER calling apply_leveling
          }
          else {                                        // leveling from off to on
            ubl.state.active = true;                    // enable BEFORE calling unapply_leveling, otherwise ignored
            // change physical current_position to unleveled current_position without moving steppers.
            planner.unapply_leveling(current_position);
          }
        #else
          ubl.state.active = enable;                    // just flip the bit, current_position will be wrong until next move.
        #endif

      #else // ABL

        #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
          // Force bilinear_z_offset to re-calculate next time
          const float reset[XYZ] = { -9999.999, -9999.999, 0 };
          (void)bilinear_z_offset(reset);
        #endif

        // Enable or disable leveling compensation in the planner
        planner.abl_enabled = enable;

        if (!enable)
          // When disabling just get the current position from the steppers.
          // This will yield the smallest error when first converted back to steps.
          set_current_from_steppers_for_axis(
            #if ABL_PLANAR
              ALL_AXES
            #else
              Z_AXIS
            #endif
          );
        else
          // When enabling, remove compensation from the current position,
          // so compensation will give the right stepper counts.
          planner.unapply_leveling(current_position);

      #endif // ABL
    }
  }

  #if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)

    void set_z_fade_height(const float zfh) {

      const bool level_active = leveling_is_active();

      #if ENABLED(AUTO_BED_LEVELING_UBL)

        if (level_active)
          set_bed_leveling_enabled(false);  // turn off before changing fade height for proper apply/unapply leveling to maintain current_position
        planner.z_fade_height = zfh;
        planner.inverse_z_fade_height = RECIPROCAL(zfh);
        if (level_active)
          set_bed_leveling_enabled(true);  // turn back on after changing fade height

      #else

        planner.z_fade_height = zfh;
        planner.inverse_z_fade_height = RECIPROCAL(zfh);

        if (level_active) {
          set_current_from_steppers_for_axis(
            #if ABL_PLANAR
              ALL_AXES
            #else
              Z_AXIS
            #endif
          );
        }
      #endif
    }

  #endif // LEVELING_FADE_HEIGHT

  /**
   * Reset calibration results to zero.
   */
  void reset_bed_level() {
    set_bed_leveling_enabled(false);
    #if ENABLED(MESH_BED_LEVELING)
      if (leveling_is_valid()) {
        mbl.reset();
        mbl.set_has_mesh(false);
      }
    #else
      #if ENABLED(DEBUG_LEVELING_FEATURE)
        if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("reset_bed_level");
      #endif
      #if ABL_PLANAR
        planner.bed_level_matrix.set_to_identity();
      #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)
        bilinear_start[X_AXIS] = bilinear_start[Y_AXIS] =
        bilinear_grid_spacing[X_AXIS] = bilinear_grid_spacing[Y_AXIS] = 0;
        for (uint8_t x = 0; x < GRID_MAX_POINTS_X; x++)
          for (uint8_t y = 0; y < GRID_MAX_POINTS_Y; y++)
            z_values[x][y] = NAN;
      #elif ENABLED(AUTO_BED_LEVELING_UBL)
        ubl.reset();
      #endif
    #endif
  }

#endif // HAS_LEVELING

#if ENABLED(AUTO_BED_LEVELING_BILINEAR) || ENABLED(MESH_BED_LEVELING)

  /**
   * Enable to produce output in JSON format suitable
   * for SCAD or JavaScript mesh visualizers.
   *
   * Visualize meshes in OpenSCAD using the included script.
   *
   *   buildroot/shared/scripts/MarlinMesh.scad
   */
  //#define SCAD_MESH_OUTPUT

  /**
   * Print calibration results for plotting or manual frame adjustment.
   */
  static void print_2d_array(const uint8_t sx, const uint8_t sy, const uint8_t precision, float (*fn)(const uint8_t, const uint8_t)) {
    #ifndef SCAD_MESH_OUTPUT
      for (uint8_t x = 0; x < sx; x++) {
        for (uint8_t i = 0; i < precision + 2 + (x < 10 ? 1 : 0); i++)
          SERIAL_PROTOCOLCHAR(' ');
        SERIAL_PROTOCOL((int)x);
      }
      SERIAL_EOL();
    #endif
    #ifdef SCAD_MESH_OUTPUT
      SERIAL_PROTOCOLLNPGM("measured_z = ["); // open 2D array
    #endif
    for (uint8_t y = 0; y < sy; y++) {
      #ifdef SCAD_MESH_OUTPUT
        SERIAL_PROTOCOLPGM(" [");           // open sub-array
      #else
        if (y < 10) SERIAL_PROTOCOLCHAR(' ');
        SERIAL_PROTOCOL((int)y);
      #endif
      for (uint8_t x = 0; x < sx; x++) {
        SERIAL_PROTOCOLCHAR(' ');
        const float offset = fn(x, y);
        if (!isnan(offset)) {
          if (offset >= 0) SERIAL_PROTOCOLCHAR('+');
          SERIAL_PROTOCOL_F(offset, precision);
        }
        else {
          #ifdef SCAD_MESH_OUTPUT
            for (uint8_t i = 3; i < precision + 3; i++)
              SERIAL_PROTOCOLCHAR(' ');
            SERIAL_PROTOCOLPGM("NAN");
          #else
            for (uint8_t i = 0; i < precision + 3; i++)
              SERIAL_PROTOCOLCHAR(i ? '=' : ' ');
          #endif
        }
        #ifdef SCAD_MESH_OUTPUT
          if (x < sx - 1) SERIAL_PROTOCOLCHAR(',');
        #endif
      }
      #ifdef SCAD_MESH_OUTPUT
        SERIAL_PROTOCOLCHAR(' ');
        SERIAL_PROTOCOLCHAR(']');                     // close sub-array
        if (y < sy - 1) SERIAL_PROTOCOLCHAR(',');
      #endif
      SERIAL_EOL();
    }
    #ifdef SCAD_MESH_OUTPUT
      SERIAL_PROTOCOLPGM("];");                       // close 2D array
    #endif
    SERIAL_EOL();
  }

#endif

#if ENABLED(AUTO_BED_LEVELING_BILINEAR)

  /**
   * Extrapolate a single point from its neighbors
   */
  static void extrapolate_one_point(const uint8_t x, const uint8_t y, const int8_t xdir, const int8_t ydir) {
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOPGM("Extrapolate [");
        if (x < 10) SERIAL_CHAR(' ');
        SERIAL_ECHO((int)x);
        SERIAL_CHAR(xdir ? (xdir > 0 ? '+' : '-') : ' ');
        SERIAL_CHAR(' ');
        if (y < 10) SERIAL_CHAR(' ');
        SERIAL_ECHO((int)y);
        SERIAL_CHAR(ydir ? (ydir > 0 ? '+' : '-') : ' ');
        SERIAL_CHAR(']');
      }
    #endif
    if (!isnan(z_values[x][y])) {
      #if ENABLED(DEBUG_LEVELING_FEATURE)
        if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM(" (done)");
      #endif
      return;  // Don't overwrite good values.
    }
    SERIAL_EOL();

    // Get X neighbors, Y neighbors, and XY neighbors
    const uint8_t x1 = x + xdir, y1 = y + ydir, x2 = x1 + xdir, y2 = y1 + ydir;
    float a1 = z_values[x1][y ], a2 = z_values[x2][y ],
          b1 = z_values[x ][y1], b2 = z_values[x ][y2],
          c1 = z_values[x1][y1], c2 = z_values[x2][y2];

    // Treat far unprobed points as zero, near as equal to far
    if (isnan(a2)) a2 = 0.0; if (isnan(a1)) a1 = a2;
    if (isnan(b2)) b2 = 0.0; if (isnan(b1)) b1 = b2;
    if (isnan(c2)) c2 = 0.0; if (isnan(c1)) c1 = c2;

    const float a = 2 * a1 - a2, b = 2 * b1 - b2, c = 2 * c1 - c2;

    // Take the average instead of the median
    z_values[x][y] = (a + b + c) / 3.0;

    // Median is robust (ignores outliers).
    // z_values[x][y] = (a < b) ? ((b < c) ? b : (c < a) ? a : c)
    //                                : ((c < b) ? b : (a < c) ? a : c);
  }

  //Enable this if your SCARA uses 180° of total area
  //#define EXTRAPOLATE_FROM_EDGE

  #if ENABLED(EXTRAPOLATE_FROM_EDGE)
    #if GRID_MAX_POINTS_X < GRID_MAX_POINTS_Y
      #define HALF_IN_X
    #elif GRID_MAX_POINTS_Y < GRID_MAX_POINTS_X
      #define HALF_IN_Y
    #endif
  #endif

  /**
   * Fill in the unprobed points (corners of circular print surface)
   * using linear extrapolation, away from the center.
   */
  static void extrapolate_unprobed_bed_level() {
    #ifdef HALF_IN_X
      constexpr uint8_t ctrx2 = 0, xlen = GRID_MAX_POINTS_X - 1;
    #else
      constexpr uint8_t ctrx1 = (GRID_MAX_POINTS_X - 1) / 2, // left-of-center
                        ctrx2 = (GRID_MAX_POINTS_X) / 2,     // right-of-center
                        xlen = ctrx1;
    #endif

    #ifdef HALF_IN_Y
      constexpr uint8_t ctry2 = 0, ylen = GRID_MAX_POINTS_Y - 1;
    #else
      constexpr uint8_t ctry1 = (GRID_MAX_POINTS_Y - 1) / 2, // top-of-center
                        ctry2 = (GRID_MAX_POINTS_Y) / 2,     // bottom-of-center
                        ylen = ctry1;
    #endif

    for (uint8_t xo = 0; xo <= xlen; xo++)
      for (uint8_t yo = 0; yo <= ylen; yo++) {
        uint8_t x2 = ctrx2 + xo, y2 = ctry2 + yo;
        #ifndef HALF_IN_X
          const uint8_t x1 = ctrx1 - xo;
        #endif
        #ifndef HALF_IN_Y
          const uint8_t y1 = ctry1 - yo;
          #ifndef HALF_IN_X
            extrapolate_one_point(x1, y1, +1, +1);   //  left-below + +
          #endif
          extrapolate_one_point(x2, y1, -1, +1);     // right-below - +
        #endif
        #ifndef HALF_IN_X
          extrapolate_one_point(x1, y2, +1, -1);     //  left-above + -
        #endif
        extrapolate_one_point(x2, y2, -1, -1);       // right-above - -
      }

  }

  static void print_bilinear_leveling_grid() {
    SERIAL_ECHOLNPGM("Bilinear Leveling Grid:");
    print_2d_array(GRID_MAX_POINTS_X, GRID_MAX_POINTS_Y, 3,
      [](const uint8_t ix, const uint8_t iy) { return z_values[ix][iy]; }
    );
  }

  #if ENABLED(ABL_BILINEAR_SUBDIVISION)

    #define ABL_GRID_POINTS_VIRT_X (GRID_MAX_POINTS_X - 1) * (BILINEAR_SUBDIVISIONS) + 1
    #define ABL_GRID_POINTS_VIRT_Y (GRID_MAX_POINTS_Y - 1) * (BILINEAR_SUBDIVISIONS) + 1
    #define ABL_TEMP_POINTS_X (GRID_MAX_POINTS_X + 2)
    #define ABL_TEMP_POINTS_Y (GRID_MAX_POINTS_Y + 2)
    float z_values_virt[ABL_GRID_POINTS_VIRT_X][ABL_GRID_POINTS_VIRT_Y];
    int bilinear_grid_spacing_virt[2] = { 0 };
    float bilinear_grid_factor_virt[2] = { 0 };

    static void bed_level_virt_print() {
      SERIAL_ECHOLNPGM("Subdivided with CATMULL ROM Leveling Grid:");
      print_2d_array(ABL_GRID_POINTS_VIRT_X, ABL_GRID_POINTS_VIRT_Y, 5,
        [](const uint8_t ix, const uint8_t iy) { return z_values_virt[ix][iy]; }
      );
    }

    #define LINEAR_EXTRAPOLATION(E, I) ((E) * 2 - (I))
    float bed_level_virt_coord(const uint8_t x, const uint8_t y) {
      uint8_t ep = 0, ip = 1;
      if (!x || x == ABL_TEMP_POINTS_X - 1) {
        if (x) {
          ep = GRID_MAX_POINTS_X - 1;
          ip = GRID_MAX_POINTS_X - 2;
        }
        if (WITHIN(y, 1, ABL_TEMP_POINTS_Y - 2))
          return LINEAR_EXTRAPOLATION(
            z_values[ep][y - 1],
            z_values[ip][y - 1]
          );
        else
          return LINEAR_EXTRAPOLATION(
            bed_level_virt_coord(ep + 1, y),
            bed_level_virt_coord(ip + 1, y)
          );
      }
      if (!y || y == ABL_TEMP_POINTS_Y - 1) {
        if (y) {
          ep = GRID_MAX_POINTS_Y - 1;
          ip = GRID_MAX_POINTS_Y - 2;
        }
        if (WITHIN(x, 1, ABL_TEMP_POINTS_X - 2))
          return LINEAR_EXTRAPOLATION(
            z_values[x - 1][ep],
            z_values[x - 1][ip]
          );
        else
          return LINEAR_EXTRAPOLATION(
            bed_level_virt_coord(x, ep + 1),
            bed_level_virt_coord(x, ip + 1)
          );
      }
      return z_values[x - 1][y - 1];
    }

    static float bed_level_virt_cmr(const float p[4], const uint8_t i, const float t) {
      return (
          p[i-1] * -t * sq(1 - t)
        + p[i]   * (2 - 5 * sq(t) + 3 * t * sq(t))
        + p[i+1] * t * (1 + 4 * t - 3 * sq(t))
        - p[i+2] * sq(t) * (1 - t)
      ) * 0.5;
    }

    static float bed_level_virt_2cmr(const uint8_t x, const uint8_t y, const float &tx, const float &ty) {
      float row[4], column[4];
      for (uint8_t i = 0; i < 4; i++) {
        for (uint8_t j = 0; j < 4; j++) {
          column[j] = bed_level_virt_coord(i + x - 1, j + y - 1);
        }
        row[i] = bed_level_virt_cmr(column, 1, ty);
      }
      return bed_level_virt_cmr(row, 1, tx);
    }

    void bed_level_virt_interpolate() {
      bilinear_grid_spacing_virt[X_AXIS] = bilinear_grid_spacing[X_AXIS] / (BILINEAR_SUBDIVISIONS);
      bilinear_grid_spacing_virt[Y_AXIS] = bilinear_grid_spacing[Y_AXIS] / (BILINEAR_SUBDIVISIONS);
      bilinear_grid_factor_virt[X_AXIS] = RECIPROCAL(bilinear_grid_spacing_virt[X_AXIS]);
      bilinear_grid_factor_virt[Y_AXIS] = RECIPROCAL(bilinear_grid_spacing_virt[Y_AXIS]);
      for (uint8_t y = 0; y < GRID_MAX_POINTS_Y; y++)
        for (uint8_t x = 0; x < GRID_MAX_POINTS_X; x++)
          for (uint8_t ty = 0; ty < BILINEAR_SUBDIVISIONS; ty++)
            for (uint8_t tx = 0; tx < BILINEAR_SUBDIVISIONS; tx++) {
              if ((ty && y == GRID_MAX_POINTS_Y - 1) || (tx && x == GRID_MAX_POINTS_X - 1))
                continue;
              z_values_virt[x * (BILINEAR_SUBDIVISIONS) + tx][y * (BILINEAR_SUBDIVISIONS) + ty] =
                bed_level_virt_2cmr(
                  x + 1,
                  y + 1,
                  (float)tx / (BILINEAR_SUBDIVISIONS),
                  (float)ty / (BILINEAR_SUBDIVISIONS)
                );
            }
    }
  #endif // ABL_BILINEAR_SUBDIVISION

  // Refresh after other values have been updated
  void refresh_bed_level() {
    bilinear_grid_factor[X_AXIS] = RECIPROCAL(bilinear_grid_spacing[X_AXIS]);
    bilinear_grid_factor[Y_AXIS] = RECIPROCAL(bilinear_grid_spacing[Y_AXIS]);
    #if ENABLED(ABL_BILINEAR_SUBDIVISION)
      bed_level_virt_interpolate();
    #endif
  }

#endif // AUTO_BED_LEVELING_BILINEAR

/**
 * Home an individual linear axis
 */
static void do_homing_move(const AxisEnum axis, const float distance, const float fr_mm_s=0.0) {

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      SERIAL_ECHOPAIR(">>> do_homing_move(", axis_codes[axis]);
      SERIAL_ECHOPAIR(", ", distance);
      SERIAL_ECHOPAIR(", ", fr_mm_s);
      SERIAL_CHAR(')');
      SERIAL_EOL();
    }
  #endif

  #if HOMING_Z_WITH_PROBE && ENABLED(BLTOUCH)
    const bool deploy_bltouch = (axis == Z_AXIS && distance < 0);
    if (deploy_bltouch) set_bltouch_deployed(true);
  #endif

  #if QUIET_PROBING
    if (axis == Z_AXIS) probing_pause(true);
  #endif

  // Tell the planner we're at Z=0
  current_position[axis] = 0;

  #if IS_SCARA
    SYNC_PLAN_POSITION_KINEMATIC();
    current_position[axis] = distance;
    inverse_kinematics(current_position);
    planner.buffer_line(delta[A_AXIS], delta[B_AXIS], delta[C_AXIS], current_position[E_AXIS], fr_mm_s ? fr_mm_s : homing_feedrate(axis), active_extruder);
  #else
    sync_plan_position();
    current_position[axis] = distance;
    planner.buffer_line(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS], current_position[E_AXIS], fr_mm_s ? fr_mm_s : homing_feedrate(axis), active_extruder);
  #endif

  stepper.synchronize();

  #if QUIET_PROBING
    if (axis == Z_AXIS) probing_pause(false);
  #endif

  #if HOMING_Z_WITH_PROBE && ENABLED(BLTOUCH)
    if (deploy_bltouch) set_bltouch_deployed(false);
  #endif

  endstops.hit_on_purpose();

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      SERIAL_ECHOPAIR("<<< do_homing_move(", axis_codes[axis]);
      SERIAL_CHAR(')');
      SERIAL_EOL();
    }
  #endif
}

/**
 * TMC2130 specific sensorless homing using stallGuard2.
 * stallGuard2 only works when in spreadCycle mode.
 * spreadCycle and stealthChop are mutually exclusive.
 */
#if ENABLED(SENSORLESS_HOMING)
  void tmc2130_sensorless_homing(TMC2130Stepper &st, bool enable=true) {
    #if ENABLED(STEALTHCHOP)
      if (enable) {
        st.coolstep_min_speed(1024UL * 1024UL - 1UL);
        st.stealthChop(0);
      }
      else {
        st.coolstep_min_speed(0);
        st.stealthChop(1);
      }
    #endif

    st.diag1_stall(enable ? 1 : 0);
  }
#endif

/**
 * Home an individual "raw axis" to its endstop.
 * This applies to XYZ on Cartesian and Core robots, and
 * to the individual ABC steppers on DELTA and SCARA.
 *
 * At the end of the procedure the axis is marked as
 * homed and the current position of that axis is updated.
 * Kinematic robots should wait till all axes are homed
 * before updating the current position.
 */

#define HOMEAXIS(LETTER) homeaxis(LETTER##_AXIS)

static void homeaxis(const AxisEnum axis) {

  #if IS_SCARA
    // Only Z homing (with probe) is permitted
    if (axis != Z_AXIS) { BUZZ(100, 880); return; }
  #else
    #define CAN_HOME(A) \
      (axis == A##_AXIS && ((A##_MIN_PIN > -1 && A##_HOME_DIR < 0) || (A##_MAX_PIN > -1 && A##_HOME_DIR > 0)))
    if (!CAN_HOME(X) && !CAN_HOME(Y) && !CAN_HOME(Z)) return;
  #endif

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      SERIAL_ECHOPAIR(">>> homeaxis(", axis_codes[axis]);
      SERIAL_CHAR(')');
      SERIAL_EOL();
    }
  #endif

  const int axis_home_dir =
    #if ENABLED(DUAL_X_CARRIAGE)
      (axis == X_AXIS) ? x_home_dir(active_extruder) :
    #endif
    home_dir(axis);

  // Homing Z towards the bed? Deploy the Z probe or endstop.
  #if HOMING_Z_WITH_PROBE
    if (axis == Z_AXIS && DEPLOY_PROBE()) return;
  #endif

  // Set a flag for Z motor locking
  #if ENABLED(Z_DUAL_ENDSTOPS)
    if (axis == Z_AXIS) stepper.set_homing_flag(true);
  #endif

  // Disable stealthChop if used. Enable diag1 pin on driver.
  #if ENABLED(SENSORLESS_HOMING)
    #if ENABLED(X_IS_TMC2130)
      if (axis == X_AXIS) tmc2130_sensorless_homing(stepperX);
    #endif
    #if ENABLED(Y_IS_TMC2130)
      if (axis == Y_AXIS) tmc2130_sensorless_homing(stepperY);
    #endif
  #endif

  // Fast move towards endstop until triggered
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("Home 1 Fast:");
  #endif
  do_homing_move(axis, 1.5 * max_length(axis) * axis_home_dir);

  // When homing Z with probe respect probe clearance
  const float bump = axis_home_dir * (
    #if HOMING_Z_WITH_PROBE
      (axis == Z_AXIS) ? max(Z_CLEARANCE_BETWEEN_PROBES, home_bump_mm(Z_AXIS)) :
    #endif
    home_bump_mm(axis)
  );

  // If a second homing move is configured...
  if (bump) {
    // Move away from the endstop by the axis HOME_BUMP_MM
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("Move Away:");
    #endif
    do_homing_move(axis, -bump);

    // Slow move towards endstop until triggered
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("Home 2 Slow:");
    #endif
    do_homing_move(axis, 2 * bump, get_homing_bump_feedrate(axis));
  }

  #if ENABLED(Z_DUAL_ENDSTOPS)
    if (axis == Z_AXIS) {
      float adj = FABS(z_endstop_adj);
      bool lockZ1;
      if (axis_home_dir > 0) {
        adj = -adj;
        lockZ1 = (z_endstop_adj > 0);
      }
      else
        lockZ1 = (z_endstop_adj < 0);

      if (lockZ1) stepper.set_z_lock(true); else stepper.set_z2_lock(true);

      // Move to the adjusted endstop height
      do_homing_move(axis, adj);

      if (lockZ1) stepper.set_z_lock(false); else stepper.set_z2_lock(false);
      stepper.set_homing_flag(false);
    } // Z_AXIS
  #endif

  #if IS_SCARA

    set_axis_is_at_home(axis);
    SYNC_PLAN_POSITION_KINEMATIC();

  #elif ENABLED(DELTA)

    // Delta has already moved all three towers up in G28
    // so here it re-homes each tower in turn.
    // Delta homing treats the axes as normal linear axes.

    // retrace by the amount specified in endstop_adj + additional 0.1mm in order to have minimum steps
    if (endstop_adj[axis] * Z_HOME_DIR <= 0) {
      #if ENABLED(DEBUG_LEVELING_FEATURE)
        if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("endstop_adj:");
      #endif
      do_homing_move(axis, endstop_adj[axis] - 0.1);
    }

  #else

    // For cartesian/core machines,
    // set the axis to its home position
    set_axis_is_at_home(axis);
    sync_plan_position();

    destination[axis] = current_position[axis];

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS("> AFTER set_axis_is_at_home", current_position);
    #endif

  #endif

  // Re-enable stealthChop if used. Disable diag1 pin on driver.
  #if ENABLED(SENSORLESS_HOMING)
    #if ENABLED(X_IS_TMC2130)
      if (axis == X_AXIS) tmc2130_sensorless_homing(stepperX, false);
    #endif
    #if ENABLED(Y_IS_TMC2130)
      if (axis == Y_AXIS) tmc2130_sensorless_homing(stepperY, false);
    #endif
  #endif

  // Put away the Z probe
  #if HOMING_Z_WITH_PROBE
    if (axis == Z_AXIS && STOW_PROBE()) return;
  #endif

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      SERIAL_ECHOPAIR("<<< homeaxis(", axis_codes[axis]);
      SERIAL_CHAR(')');
      SERIAL_EOL();
    }
  #endif
} // homeaxis()

#if ENABLED(FWRETRACT)

  void retract(const bool retracting, const bool swapping = false) {

    static float hop_height;

    if (retracting == retracted[active_extruder]) return;

    const float old_feedrate_mm_s = feedrate_mm_s;

    set_destination_to_current();

    if (retracting) {

      feedrate_mm_s = retract_feedrate_mm_s;
      current_position[E_AXIS] += (swapping ? retract_length_swap : retract_length) / volumetric_multiplier[active_extruder];
      sync_plan_position_e();
      prepare_move_to_destination();

      if (retract_zlift > 0.01) {
        hop_height = current_position[Z_AXIS];
        // Pretend current position is lower
        current_position[Z_AXIS] -= retract_zlift;
        SYNC_PLAN_POSITION_KINEMATIC();
        // Raise up to the old current_position
        prepare_move_to_destination();
      }
    }
    else {

      // If the height hasn't been lowered, undo the Z hop
      if (retract_zlift > 0.01 && hop_height <= current_position[Z_AXIS]) {
        // Pretend current position is higher. Z will lower on the next move
        current_position[Z_AXIS] += retract_zlift;
        SYNC_PLAN_POSITION_KINEMATIC();
        // Lower Z
        prepare_move_to_destination();
      }

      feedrate_mm_s = retract_recover_feedrate_mm_s;
      const float move_e = swapping ? retract_length_swap + retract_recover_length_swap : retract_length + retract_recover_length;
      current_position[E_AXIS] -= move_e / volumetric_multiplier[active_extruder];
      sync_plan_position_e();

      // Recover E
      prepare_move_to_destination();
    }

    feedrate_mm_s = old_feedrate_mm_s;
    retracted[active_extruder] = retracting;

  } // retract()

#endif // FWRETRACT

#if ENABLED(MIXING_EXTRUDER)

  void normalize_mix() {
    float mix_total = 0.0;
    for (uint8_t i = 0; i < MIXING_STEPPERS; i++) mix_total += RECIPROCAL(mixing_factor[i]);
    // Scale all values if they don't add up to ~1.0
    if (!NEAR(mix_total, 1.0)) {
      SERIAL_PROTOCOLLNPGM("Warning: Mix factors must add up to 1.0. Scaling.");
      for (uint8_t i = 0; i < MIXING_STEPPERS; i++) mixing_factor[i] *= mix_total;
    }
  }

  #if ENABLED(DIRECT_MIXING_IN_G1)
    // Get mixing parameters from the GCode
    // The total "must" be 1.0 (but it will be normalized)
    // If no mix factors are given, the old mix is preserved
    void gcode_get_mix() {
      const char* mixing_codes = "ABCDHI";
      byte mix_bits = 0;
      for (uint8_t i = 0; i < MIXING_STEPPERS; i++) {
        if (parser.seenval(mixing_codes[i])) {
          SBI(mix_bits, i);
          float v = parser.value_float();
          NOLESS(v, 0.0);
          mixing_factor[i] = RECIPROCAL(v);
        }
      }
      // If any mixing factors were included, clear the rest
      // If none were included, preserve the last mix
      if (mix_bits) {
        for (uint8_t i = 0; i < MIXING_STEPPERS; i++)
          if (!TEST(mix_bits, i)) mixing_factor[i] = 0.0;
        normalize_mix();
      }
    }
  #endif

#endif

/**
 * ***************************************************************************
 * ***************************** G-CODE HANDLING *****************************
 * ***************************************************************************
 */

/**
 * Set XYZE destination and feedrate from the current GCode command
 *
 *  - Set destination from included axis codes
 *  - Set to current for missing axis codes
 *  - Set the feedrate, if included
 */
void gcode_get_destination() {
  LOOP_XYZE(i) {
    if (parser.seen(axis_codes[i]))
      destination[i] = parser.value_axis_units((AxisEnum)i) + (axis_relative_modes[i] || relative_mode ? current_position[i] : 0);
    else
      destination[i] = current_position[i];
  }

  if (parser.linearval('F') > 0.0)
    feedrate_mm_s = MMM_TO_MMS(parser.value_feedrate());

  #if ENABLED(PRINTCOUNTER)
    if (!DEBUGGING(DRYRUN))
      print_job_timer.incFilamentUsed(destination[E_AXIS] - current_position[E_AXIS]);
  #endif

  // Get ABCDHI mixing factors
  #if ENABLED(MIXING_EXTRUDER) && ENABLED(DIRECT_MIXING_IN_G1)
    gcode_get_mix();
  #endif
}

#if ENABLED(HOST_KEEPALIVE_FEATURE)

  /**
   * Output a "busy" message at regular intervals
   * while the machine is not accepting commands.
   */
  void host_keepalive() {
    const millis_t ms = millis();
    if (host_keepalive_interval && busy_state != NOT_BUSY) {
      if (PENDING(ms, next_busy_signal_ms)) return;
      switch (busy_state) {
        case IN_HANDLER:
        case IN_PROCESS:
          SERIAL_ECHO_START();
          SERIAL_ECHOLNPGM(MSG_BUSY_PROCESSING);
          break;
        case PAUSED_FOR_USER:
          SERIAL_ECHO_START();
          SERIAL_ECHOLNPGM(MSG_BUSY_PAUSED_FOR_USER);
          break;
        case PAUSED_FOR_INPUT:
          SERIAL_ECHO_START();
          SERIAL_ECHOLNPGM(MSG_BUSY_PAUSED_FOR_INPUT);
          break;
        default:
          break;
      }
    }
    next_busy_signal_ms = ms + host_keepalive_interval * 1000UL;
  }

#endif // HOST_KEEPALIVE_FEATURE


/**************************************************
 ***************** GCode Handlers *****************
 **************************************************/

/**
 * G0, G1: Coordinated movement of X Y Z E axes
 */
inline void gcode_G0_G1(
  #if IS_SCARA
    bool fast_move=false
  #endif
) {
  if (IsRunning()) {
    gcode_get_destination(); // For X Y Z E F

    #if ENABLED(FWRETRACT)

      if (autoretract_enabled && !(parser.seen('X') || parser.seen('Y') || parser.seen('Z')) && parser.seen('E')) {
        const float echange = destination[E_AXIS] - current_position[E_AXIS];
        // Is this move an attempt to retract or recover?
        if ((echange < -MIN_RETRACT && !retracted[active_extruder]) || (echange > MIN_RETRACT && retracted[active_extruder])) {
          current_position[E_AXIS] = destination[E_AXIS]; // hide the slicer-generated retract/recover from calculations
          sync_plan_position_e();  // AND from the planner
          retract(!retracted[active_extruder]);
          return;
        }
      }

    #endif // FWRETRACT

    #if IS_SCARA
      fast_move ? prepare_uninterpolated_move_to_destination() : prepare_move_to_destination();
    #else
      prepare_move_to_destination();
    #endif
  }
}

/**
 * G2: Clockwise Arc
 * G3: Counterclockwise Arc
 *
 * This command has two forms: IJ-form and R-form.
 *
 *  - I specifies an X offset. J specifies a Y offset.
 *    At least one of the IJ parameters is required.
 *    X and Y can be omitted to do a complete circle.
 *    The given XY is not error-checked. The arc ends
 *     based on the angle of the destination.
 *    Mixing I or J with R will throw an error.
 *
 *  - R specifies the radius. X or Y is required.
 *    Omitting both X and Y will throw an error.
 *    X or Y must differ from the current XY.
 *    Mixing R with I or J will throw an error.
 *
 *  - P specifies the number of full circles to do
 *    before the specified arc move.
 *
 *  Examples:
 *
 *    G2 I10           ; CW circle centered at X+10
 *    G3 X20 Y12 R14   ; CCW circle with r=14 ending at X20 Y12
 */
#if ENABLED(ARC_SUPPORT)

  inline void gcode_G2_G3(bool clockwise) {
    if (IsRunning()) {

      #if ENABLED(SF_ARC_FIX)
        const bool relative_mode_backup = relative_mode;
        relative_mode = true;
      #endif

      gcode_get_destination();

      #if ENABLED(SF_ARC_FIX)
        relative_mode = relative_mode_backup;
      #endif

      float arc_offset[2] = { 0.0, 0.0 };
      if (parser.seenval('R')) {
        const float r = parser.value_linear_units(),
                    p1 = current_position[X_AXIS], q1 = current_position[Y_AXIS],
                    p2 = destination[X_AXIS], q2 = destination[Y_AXIS];
        if (r && (p2 != p1 || q2 != q1)) {
          const float e = clockwise ^ (r < 0) ? -1 : 1,           // clockwise -1/1, counterclockwise 1/-1
                      dx = p2 - p1, dy = q2 - q1,                 // X and Y differences
                      d = HYPOT(dx, dy),                          // Linear distance between the points
                      h = SQRT(sq(r) - sq(d * 0.5)),              // Distance to the arc pivot-point
                      mx = (p1 + p2) * 0.5, my = (q1 + q2) * 0.5, // Point between the two points
                      sx = -dy / d, sy = dx / d,                  // Slope of the perpendicular bisector
                      cx = mx + e * h * sx, cy = my + e * h * sy; // Pivot-point of the arc
          arc_offset[0] = cx - p1;
          arc_offset[1] = cy - q1;
        }
      }
      else {
        if (parser.seenval('I')) arc_offset[0] = parser.value_linear_units();
        if (parser.seenval('J')) arc_offset[1] = parser.value_linear_units();
      }

      if (arc_offset[0] || arc_offset[1]) {

        #if ENABLED(ARC_P_CIRCLES)
          // P indicates number of circles to do
          int8_t circles_to_do = parser.byteval('P');
          if (!WITHIN(circles_to_do, 0, 100)) {
            SERIAL_ERROR_START();
            SERIAL_ERRORLNPGM(MSG_ERR_ARC_ARGS);
          }
          while (circles_to_do--)
            plan_arc(current_position, arc_offset, clockwise);
        #endif

        // Send the arc to the planner
        plan_arc(destination, arc_offset, clockwise);
        refresh_cmd_timeout();
      }
      else {
        // Bad arguments
        SERIAL_ERROR_START();
        SERIAL_ERRORLNPGM(MSG_ERR_ARC_ARGS);
      }
    }
  }

#endif // ARC_SUPPORT

/**
 * G4: Dwell S<seconds> or P<milliseconds>
 */
inline void gcode_G4() {
  millis_t dwell_ms = 0;

  if (parser.seenval('P')) dwell_ms = parser.value_millis(); // milliseconds to wait
  if (parser.seenval('S')) dwell_ms = parser.value_millis_from_seconds(); // seconds to wait

  stepper.synchronize();
  refresh_cmd_timeout();
  dwell_ms += previous_cmd_ms;  // keep track of when we started waiting

  if (!lcd_hasstatus()) LCD_MESSAGEPGM(MSG_DWELL);

  while (PENDING(millis(), dwell_ms)) idle();
}

#if ENABLED(BEZIER_CURVE_SUPPORT)

  /**
   * Parameters interpreted according to:
   * http://linuxcnc.org/docs/2.6/html/gcode/gcode.html#sec:G5-Cubic-Spline
   * However I, J omission is not supported at this point; all
   * parameters can be omitted and default to zero.
   */

  /**
   * G5: Cubic B-spline
   */
  inline void gcode_G5() {
    if (IsRunning()) {

      gcode_get_destination();

      const float offset[] = {
        parser.linearval('I'),
        parser.linearval('J'),
        parser.linearval('P'),
        parser.linearval('Q')
      };

      plan_cubic_move(offset);
    }
  }

#endif // BEZIER_CURVE_SUPPORT

#if ENABLED(FWRETRACT)

  /**
   * G10 - Retract filament according to settings of M207
   * G11 - Recover filament according to settings of M208
   */
  inline void gcode_G10_G11(bool doRetract=false) {
    #if EXTRUDERS > 1
      if (doRetract)
        retracted_swap[active_extruder] = parser.boolval('S'); // checks for swap retract argument
    #endif
    retract(doRetract
     #if EXTRUDERS > 1
      , retracted_swap[active_extruder]
     #endif
    );
  }

#endif // FWRETRACT

#if ENABLED(NOZZLE_CLEAN_FEATURE)
  /**
   * G12: Clean the nozzle
   */
  inline void gcode_G12() {
    // Don't allow nozzle cleaning without homing first
    if (axis_unhomed_error()) return;

    const uint8_t pattern = parser.ushortval('P', 0),
                  strokes = parser.ushortval('S', NOZZLE_CLEAN_STROKES),
                  objects = parser.ushortval('T', NOZZLE_CLEAN_TRIANGLES);
    const float radius = parser.floatval('R', NOZZLE_CLEAN_CIRCLE_RADIUS);

    Nozzle::clean(pattern, strokes, radius, objects);
  }
#endif

#if ENABLED(CNC_WORKSPACE_PLANES)

  void report_workspace_plane() {
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM("Workspace Plane ");
    serialprintPGM(workspace_plane == PLANE_YZ ? PSTR("YZ\n") : workspace_plane == PLANE_ZX ? PSTR("ZX\n") : PSTR("XY\n"));
  }

  /**
   * G17: Select Plane XY
   * G18: Select Plane ZX
   * G19: Select Plane YZ
   */
  inline void gcode_G17() { workspace_plane = PLANE_XY; }
  inline void gcode_G18() { workspace_plane = PLANE_ZX; }
  inline void gcode_G19() { workspace_plane = PLANE_YZ; }

#endif // CNC_WORKSPACE_PLANES

#if ENABLED(INCH_MODE_SUPPORT)
  /**
   * G20: Set input mode to inches
   */
  inline void gcode_G20() { parser.set_input_linear_units(LINEARUNIT_INCH); }

  /**
   * G21: Set input mode to millimeters
   */
  inline void gcode_G21() { parser.set_input_linear_units(LINEARUNIT_MM); }
#endif

#if ENABLED(NOZZLE_PARK_FEATURE)
  /**
   * G27: Park the nozzle
   */
  inline void gcode_G27() {
    // Don't allow nozzle parking without homing first
    if (axis_unhomed_error()) return;
    Nozzle::park(parser.ushortval('P'));
  }
#endif // NOZZLE_PARK_FEATURE

#if ENABLED(QUICK_HOME)

  static void quick_home_xy() {

    // Pretend the current position is 0,0
    current_position[X_AXIS] = current_position[Y_AXIS] = 0.0;
    sync_plan_position();

    const int x_axis_home_dir =
      #if ENABLED(DUAL_X_CARRIAGE)
        x_home_dir(active_extruder)
      #else
        home_dir(X_AXIS)
      #endif
    ;

    const float mlx = max_length(X_AXIS),
                mly = max_length(Y_AXIS),
                mlratio = mlx > mly ? mly / mlx : mlx / mly,
                fr_mm_s = min(homing_feedrate(X_AXIS), homing_feedrate(Y_AXIS)) * SQRT(sq(mlratio) + 1.0);

    do_blocking_move_to_xy(1.5 * mlx * x_axis_home_dir, 1.5 * mly * home_dir(Y_AXIS), fr_mm_s);
    endstops.hit_on_purpose(); // clear endstop hit flags
    current_position[X_AXIS] = current_position[Y_AXIS] = 0.0;
  }

#endif // QUICK_HOME

#if ENABLED(DEBUG_LEVELING_FEATURE)

  void log_machine_info() {
    SERIAL_ECHOPGM("Machine Type: ");
    #if ENABLED(DELTA)
      SERIAL_ECHOLNPGM("Delta");
    #elif IS_SCARA
      SERIAL_ECHOLNPGM("SCARA");
    #elif IS_CORE
      SERIAL_ECHOLNPGM("Core");
    #else
      SERIAL_ECHOLNPGM("Cartesian");
    #endif

    SERIAL_ECHOPGM("Probe: ");
    #if ENABLED(PROBE_MANUALLY)
      SERIAL_ECHOLNPGM("PROBE_MANUALLY");
    #elif ENABLED(FIX_MOUNTED_PROBE)
      SERIAL_ECHOLNPGM("FIX_MOUNTED_PROBE");
    #elif ENABLED(BLTOUCH)
      SERIAL_ECHOLNPGM("BLTOUCH");
    #elif HAS_Z_SERVO_ENDSTOP
      SERIAL_ECHOLNPGM("SERVO PROBE");
    #elif ENABLED(Z_PROBE_SLED)
      SERIAL_ECHOLNPGM("Z_PROBE_SLED");
    #elif ENABLED(Z_PROBE_ALLEN_KEY)
      SERIAL_ECHOLNPGM("Z_PROBE_ALLEN_KEY");
    #else
      SERIAL_ECHOLNPGM("NONE");
    #endif

    #if HAS_BED_PROBE
      SERIAL_ECHOPAIR("Probe Offset X:", X_PROBE_OFFSET_FROM_EXTRUDER);
      SERIAL_ECHOPAIR(" Y:", Y_PROBE_OFFSET_FROM_EXTRUDER);
      SERIAL_ECHOPAIR(" Z:", zprobe_zoffset);
      #if X_PROBE_OFFSET_FROM_EXTRUDER > 0
        SERIAL_ECHOPGM(" (Right");
      #elif X_PROBE_OFFSET_FROM_EXTRUDER < 0
        SERIAL_ECHOPGM(" (Left");
      #elif Y_PROBE_OFFSET_FROM_EXTRUDER != 0
        SERIAL_ECHOPGM(" (Middle");
      #else
        SERIAL_ECHOPGM(" (Aligned With");
      #endif
      #if Y_PROBE_OFFSET_FROM_EXTRUDER > 0
        SERIAL_ECHOPGM("-Back");
      #elif Y_PROBE_OFFSET_FROM_EXTRUDER < 0
        SERIAL_ECHOPGM("-Front");
      #elif X_PROBE_OFFSET_FROM_EXTRUDER != 0
        SERIAL_ECHOPGM("-Center");
      #endif
      if (zprobe_zoffset < 0)
        SERIAL_ECHOPGM(" & Below");
      else if (zprobe_zoffset > 0)
        SERIAL_ECHOPGM(" & Above");
      else
        SERIAL_ECHOPGM(" & Same Z as");
      SERIAL_ECHOLNPGM(" Nozzle)");
    #endif

    #if HAS_ABL
      SERIAL_ECHOPGM("Auto Bed Leveling: ");
      #if ENABLED(AUTO_BED_LEVELING_LINEAR)
        SERIAL_ECHOPGM("LINEAR");
      #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)
        SERIAL_ECHOPGM("BILINEAR");
      #elif ENABLED(AUTO_BED_LEVELING_3POINT)
        SERIAL_ECHOPGM("3POINT");
      #elif ENABLED(AUTO_BED_LEVELING_UBL)
        SERIAL_ECHOPGM("UBL");
      #endif
      if (leveling_is_active()) {
        SERIAL_ECHOLNPGM(" (enabled)");
        #if ABL_PLANAR
          const float diff[XYZ] = {
            stepper.get_axis_position_mm(X_AXIS) - current_position[X_AXIS],
            stepper.get_axis_position_mm(Y_AXIS) - current_position[Y_AXIS],
            stepper.get_axis_position_mm(Z_AXIS) - current_position[Z_AXIS]
          };
          SERIAL_ECHOPGM("ABL Adjustment X");
          if (diff[X_AXIS] > 0) SERIAL_CHAR('+');
          SERIAL_ECHO(diff[X_AXIS]);
          SERIAL_ECHOPGM(" Y");
          if (diff[Y_AXIS] > 0) SERIAL_CHAR('+');
          SERIAL_ECHO(diff[Y_AXIS]);
          SERIAL_ECHOPGM(" Z");
          if (diff[Z_AXIS] > 0) SERIAL_CHAR('+');
          SERIAL_ECHO(diff[Z_AXIS]);
        #elif ENABLED(AUTO_BED_LEVELING_UBL)
          SERIAL_ECHOPAIR("UBL Adjustment Z", stepper.get_axis_position_mm(Z_AXIS) - current_position[Z_AXIS]);
        #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)
          SERIAL_ECHOPAIR("ABL Adjustment Z", bilinear_z_offset(current_position));
        #endif
      }
      else
        SERIAL_ECHOLNPGM(" (disabled)");

      SERIAL_EOL();

    #elif ENABLED(MESH_BED_LEVELING)

      SERIAL_ECHOPGM("Mesh Bed Leveling");
      if (leveling_is_active()) {
        float lz = current_position[Z_AXIS];
        planner.apply_leveling(current_position[X_AXIS], current_position[Y_AXIS], lz);
        SERIAL_ECHOLNPGM(" (enabled)");
        SERIAL_ECHOPAIR("MBL Adjustment Z", lz);
      }
      else
        SERIAL_ECHOPGM(" (disabled)");

      SERIAL_EOL();

    #endif // MESH_BED_LEVELING
  }

#endif // DEBUG_LEVELING_FEATURE

#if ENABLED(DELTA)

  /**
   * A delta can only safely home all axes at the same time
   * This is like quick_home_xy() but for 3 towers.
   */
  inline void home_delta() {
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS(">>> home_delta", current_position);
    #endif
    // Init the current position of all carriages to 0,0,0
    ZERO(current_position);
    sync_plan_position();

    // Move all carriages together linearly until an endstop is hit.
    current_position[X_AXIS] = current_position[Y_AXIS] = current_position[Z_AXIS] = (Z_MAX_LENGTH + 10);
    feedrate_mm_s = homing_feedrate(X_AXIS);
    line_to_current_position();
    stepper.synchronize();
    endstops.hit_on_purpose(); // clear endstop hit flags

    // At least one carriage has reached the top.
    // Now re-home each carriage separately.
    HOMEAXIS(A);
    HOMEAXIS(B);
    HOMEAXIS(C);

    // Set all carriages to their home positions
    // Do this here all at once for Delta, because
    // XYZ isn't ABC. Applying this per-tower would
    // give the impression that they are the same.
    LOOP_XYZ(i) set_axis_is_at_home((AxisEnum)i);

    SYNC_PLAN_POSITION_KINEMATIC();

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS("<<< home_delta", current_position);
    #endif
  }

#endif // DELTA

#if ENABLED(Z_SAFE_HOMING)

  inline void home_z_safely() {

    // Disallow Z homing if X or Y are unknown
    if (!axis_known_position[X_AXIS] || !axis_known_position[Y_AXIS]) {
      LCD_MESSAGEPGM(MSG_ERR_Z_HOMING);
      SERIAL_ECHO_START();
      SERIAL_ECHOLNPGM(MSG_ERR_Z_HOMING);
      return;
    }

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("Z_SAFE_HOMING >>>");
    #endif

    SYNC_PLAN_POSITION_KINEMATIC();

    /**
     * Move the Z probe (or just the nozzle) to the safe homing point
     */
    destination[X_AXIS] = LOGICAL_X_POSITION(Z_SAFE_HOMING_X_POINT);
    destination[Y_AXIS] = LOGICAL_Y_POSITION(Z_SAFE_HOMING_Y_POINT);
    destination[Z_AXIS] = current_position[Z_AXIS]; // Z is already at the right height

    #if HOMING_Z_WITH_PROBE
      destination[X_AXIS] -= X_PROBE_OFFSET_FROM_EXTRUDER;
      destination[Y_AXIS] -= Y_PROBE_OFFSET_FROM_EXTRUDER;
    #endif

    if (position_is_reachable_xy(destination[X_AXIS], destination[Y_AXIS])) {

      #if ENABLED(DEBUG_LEVELING_FEATURE)
        if (DEBUGGING(LEVELING)) DEBUG_POS("Z_SAFE_HOMING", destination);
      #endif

      // This causes the carriage on Dual X to unpark
      #if ENABLED(DUAL_X_CARRIAGE)
        active_extruder_parked = false;
      #endif

      do_blocking_move_to_xy(destination[X_AXIS], destination[Y_AXIS]);
      HOMEAXIS(Z);
    }
    else {
      LCD_MESSAGEPGM(MSG_ZPROBE_OUT);
      SERIAL_ECHO_START();
      SERIAL_ECHOLNPGM(MSG_ZPROBE_OUT);
    }

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("<<< Z_SAFE_HOMING");
    #endif
  }

#endif // Z_SAFE_HOMING

#if ENABLED(PROBE_MANUALLY)
  bool g29_in_progress = false;
#else
  constexpr bool g29_in_progress = false;
#endif

/**
 * G28: Home all axes according to settings
 *
 * Parameters
 *
 *  None  Home to all axes with no parameters.
 *        With QUICK_HOME enabled XY will home together, then Z.
 *
 * Cartesian parameters
 *
 *  X   Home to the X endstop
 *  Y   Home to the Y endstop
 *  Z   Home to the Z endstop
 *
 */
inline void gcode_G28(const bool always_home_all) {

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      SERIAL_ECHOLNPGM(">>> gcode_G28");
      log_machine_info();
    }
  #endif

  // Wait for planner moves to finish!
  stepper.synchronize();

  // Cancel the active G29 session
  #if ENABLED(PROBE_MANUALLY)
    g29_in_progress = false;
  #endif

  // Disable the leveling matrix before homing
  #if HAS_LEVELING
    #if ENABLED(AUTO_BED_LEVELING_UBL)
      const bool ubl_state_at_entry = leveling_is_active();
    #endif
    set_bed_leveling_enabled(false);
  #endif

  #if ENABLED(CNC_WORKSPACE_PLANES)
    workspace_plane = PLANE_XY;
  #endif

  // Always home with tool 0 active
  #if HOTENDS > 1
    const uint8_t old_tool_index = active_extruder;
    tool_change(0, 0, true);
  #endif

  #if ENABLED(DUAL_X_CARRIAGE) || ENABLED(DUAL_NOZZLE_DUPLICATION_MODE)
    extruder_duplication_enabled = false;
  #endif

  setup_for_endstop_or_probe_move();
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("> endstops.enable(true)");
  #endif
  endstops.enable(true); // Enable endstops for next homing move

  #if ENABLED(DELTA)

    home_delta();
    UNUSED(always_home_all);

  #else // NOT DELTA

    const bool homeX = always_home_all || parser.seen('X'),
               homeY = always_home_all || parser.seen('Y'),
               homeZ = always_home_all || parser.seen('Z'),
               home_all = (!homeX && !homeY && !homeZ) || (homeX && homeY && homeZ);

    set_destination_to_current();

    #if Z_HOME_DIR > 0  // If homing away from BED do Z first

      if (home_all || homeZ) {
        HOMEAXIS(Z);
        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) DEBUG_POS("> HOMEAXIS(Z)", current_position);
        #endif
      }

    #else

      if (home_all || homeX || homeY) {
        // Raise Z before homing any other axes and z is not already high enough (never lower z)
        destination[Z_AXIS] = LOGICAL_Z_POSITION(Z_HOMING_HEIGHT);
        if (destination[Z_AXIS] > current_position[Z_AXIS]) {

          #if ENABLED(DEBUG_LEVELING_FEATURE)
            if (DEBUGGING(LEVELING))
              SERIAL_ECHOLNPAIR("Raise Z (before homing) to ", destination[Z_AXIS]);
          #endif

          do_blocking_move_to_z(destination[Z_AXIS]);
        }
      }

    #endif

    #if ENABLED(QUICK_HOME)

      if (home_all || (homeX && homeY)) quick_home_xy();

    #endif

    #if ENABLED(HOME_Y_BEFORE_X)

      // Home Y
      if (home_all || homeY) {
        HOMEAXIS(Y);
        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) DEBUG_POS("> homeY", current_position);
        #endif
      }

    #endif

    // Home X
    if (home_all || homeX) {

      #if ENABLED(DUAL_X_CARRIAGE)

        // Always home the 2nd (right) extruder first
        active_extruder = 1;
        HOMEAXIS(X);

        // Remember this extruder's position for later tool change
        inactive_extruder_x_pos = RAW_X_POSITION(current_position[X_AXIS]);

        // Home the 1st (left) extruder
        active_extruder = 0;
        HOMEAXIS(X);

        // Consider the active extruder to be parked
        COPY(raised_parked_position, current_position);
        delayed_move_time = 0;
        active_extruder_parked = true;

      #else

        HOMEAXIS(X);

      #endif

      #if ENABLED(DEBUG_LEVELING_FEATURE)
        if (DEBUGGING(LEVELING)) DEBUG_POS("> homeX", current_position);
      #endif
    }

    #if DISABLED(HOME_Y_BEFORE_X)
      // Home Y
      if (home_all || homeY) {
        HOMEAXIS(Y);
        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) DEBUG_POS("> homeY", current_position);
        #endif
      }
    #endif

    // Home Z last if homing towards the bed
    #if Z_HOME_DIR < 0
      if (home_all || homeZ) {
        #if ENABLED(Z_SAFE_HOMING)
          home_z_safely();
        #else
          HOMEAXIS(Z);
        #endif
        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) DEBUG_POS("> (home_all || homeZ) > final", current_position);
        #endif
      } // home_all || homeZ
    #endif // Z_HOME_DIR < 0

    SYNC_PLAN_POSITION_KINEMATIC();

  #endif // !DELTA (gcode_G28)

  endstops.not_homing();

  #if ENABLED(DELTA) && ENABLED(DELTA_HOME_TO_SAFE_ZONE)
    // move to a height where we can use the full xy-area
    do_blocking_move_to_z(delta_clip_start_height);
  #endif

  #if ENABLED(AUTO_BED_LEVELING_UBL)
    set_bed_leveling_enabled(ubl_state_at_entry);
  #endif

  clean_up_after_endstop_or_probe_move();

  // Restore the active tool after homing
  #if HOTENDS > 1
    tool_change(old_tool_index, 0, true);
  #endif

  lcd_refresh();

  report_current_position();

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("<<< gcode_G28");
  #endif
} // G28

void home_all_axes() { gcode_G28(true); }

#if HAS_PROBING_PROCEDURE

  void out_of_range_error(const char* p_edge) {
    SERIAL_PROTOCOLPGM("?Probe ");
    serialprintPGM(p_edge);
    SERIAL_PROTOCOLLNPGM(" position out of range.");
  }

#endif

#if ENABLED(MESH_BED_LEVELING) || ENABLED(PROBE_MANUALLY)

  #if ENABLED(PROBE_MANUALLY) && ENABLED(LCD_BED_LEVELING)
    extern bool lcd_wait_for_move;
  #endif

  inline void _manual_goto_xy(const float &x, const float &y) {
    const float old_feedrate_mm_s = feedrate_mm_s;

    #if MANUAL_PROBE_HEIGHT > 0
      feedrate_mm_s = homing_feedrate(Z_AXIS);
      current_position[Z_AXIS] = LOGICAL_Z_POSITION(Z_MIN_POS) + MANUAL_PROBE_HEIGHT;
      line_to_current_position();
    #endif

    feedrate_mm_s = MMM_TO_MMS(XY_PROBE_SPEED);
    current_position[X_AXIS] = LOGICAL_X_POSITION(x);
    current_position[Y_AXIS] = LOGICAL_Y_POSITION(y);
    line_to_current_position();

    #if MANUAL_PROBE_HEIGHT > 0
      feedrate_mm_s = homing_feedrate(Z_AXIS);
      current_position[Z_AXIS] = LOGICAL_Z_POSITION(Z_MIN_POS); // just slightly over the bed
      line_to_current_position();
    #endif

    feedrate_mm_s = old_feedrate_mm_s;
    stepper.synchronize();

    #if ENABLED(PROBE_MANUALLY) && ENABLED(LCD_BED_LEVELING)
      lcd_wait_for_move = false;
    #endif
  }

#endif

#if ENABLED(MESH_BED_LEVELING)

  // Save 130 bytes with non-duplication of PSTR
  void echo_not_entered() { SERIAL_PROTOCOLLNPGM(" not entered."); }

  void mbl_mesh_report() {
    SERIAL_PROTOCOLLNPGM("Num X,Y: " STRINGIFY(GRID_MAX_POINTS_X) "," STRINGIFY(GRID_MAX_POINTS_Y));
    SERIAL_PROTOCOLPGM("Z offset: "); SERIAL_PROTOCOL_F(mbl.z_offset, 5);
    SERIAL_PROTOCOLLNPGM("\nMeasured points:");
    print_2d_array(GRID_MAX_POINTS_X, GRID_MAX_POINTS_Y, 5,
      [](const uint8_t ix, const uint8_t iy) { return mbl.z_values[ix][iy]; }
    );
  }

  void mesh_probing_done() {
    mbl.set_has_mesh(true);
    home_all_axes();
    set_bed_leveling_enabled(true);
    #if ENABLED(MESH_G28_REST_ORIGIN)
      current_position[Z_AXIS] = LOGICAL_Z_POSITION(Z_MIN_POS);
      set_destination_to_current();
      line_to_destination(homing_feedrate(Z_AXIS));
      stepper.synchronize();
    #endif
  }

  /**
   * G29: Mesh-based Z probe, probes a grid and produces a
   *      mesh to compensate for variable bed height
   *
   * Parameters With MESH_BED_LEVELING:
   *
   *  S0              Produce a mesh report
   *  S1              Start probing mesh points
   *  S2              Probe the next mesh point
   *  S3 Xn Yn Zn.nn  Manually modify a single point
   *  S4 Zn.nn        Set z offset. Positive away from bed, negative closer to bed.
   *  S5              Reset and disable mesh
   *
   * The S0 report the points as below
   *
   *  +----> X-axis  1-n
   *  |
   *  |
   *  v Y-axis  1-n
   *
   */
  inline void gcode_G29() {

    static int mbl_probe_index = -1;
    #if HAS_SOFTWARE_ENDSTOPS
      static bool enable_soft_endstops;
    #endif

    const MeshLevelingState state = (MeshLevelingState)parser.byteval('S', (int8_t)MeshReport);
    if (!WITHIN(state, 0, 5)) {
      SERIAL_PROTOCOLLNPGM("S out of range (0-5).");
      return;
    }

    int8_t px, py;

    switch (state) {
      case MeshReport:
        if (leveling_is_valid()) {
          SERIAL_PROTOCOLLNPAIR("State: ", leveling_is_active() ? MSG_ON : MSG_OFF);
          mbl_mesh_report();
        }
        else
          SERIAL_PROTOCOLLNPGM("Mesh bed leveling has no data.");
        break;

      case MeshStart:
        mbl.reset();
        mbl_probe_index = 0;
        enqueue_and_echo_commands_P(PSTR("G28\nG29 S2"));
        break;

      case MeshNext:
        if (mbl_probe_index < 0) {
          SERIAL_PROTOCOLLNPGM("Start mesh probing with \"G29 S1\" first.");
          return;
        }
        // For each G29 S2...
        if (mbl_probe_index == 0) {
          #if HAS_SOFTWARE_ENDSTOPS
            // For the initial G29 S2 save software endstop state
            enable_soft_endstops = soft_endstops_enabled;
          #endif
        }
        else {
          // For G29 S2 after adjusting Z.
          mbl.set_zigzag_z(mbl_probe_index - 1, current_position[Z_AXIS]);
          #if HAS_SOFTWARE_ENDSTOPS
            soft_endstops_enabled = enable_soft_endstops;
          #endif
        }
        // If there's another point to sample, move there with optional lift.
        if (mbl_probe_index < GRID_MAX_POINTS) {
          mbl.zigzag(mbl_probe_index, px, py);
          _manual_goto_xy(mbl.index_to_xpos[px], mbl.index_to_ypos[py]);

          #if HAS_SOFTWARE_ENDSTOPS
            // Disable software endstops to allow manual adjustment
            // If G29 is not completed, they will not be re-enabled
            soft_endstops_enabled = false;
          #endif

          mbl_probe_index++;
        }
        else {
          // One last "return to the bed" (as originally coded) at completion
          current_position[Z_AXIS] = LOGICAL_Z_POSITION(Z_MIN_POS) + MANUAL_PROBE_HEIGHT;
          line_to_current_position();
          stepper.synchronize();

          // After recording the last point, activate home and activate
          mbl_probe_index = -1;
          SERIAL_PROTOCOLLNPGM("Mesh probing done.");
          BUZZ(100, 659);
          BUZZ(100, 698);
          mesh_probing_done();
        }
        break;

      case MeshSet:
        if (parser.seenval('X')) {
          px = parser.value_int() - 1;
          if (!WITHIN(px, 0, GRID_MAX_POINTS_X - 1)) {
            SERIAL_PROTOCOLLNPGM("X out of range (1-" STRINGIFY(GRID_MAX_POINTS_X) ").");
            return;
          }
        }
        else {
          SERIAL_CHAR('X'); echo_not_entered();
          return;
        }

        if (parser.seenval('Y')) {
          py = parser.value_int() - 1;
          if (!WITHIN(py, 0, GRID_MAX_POINTS_Y - 1)) {
            SERIAL_PROTOCOLLNPGM("Y out of range (1-" STRINGIFY(GRID_MAX_POINTS_Y) ").");
            return;
          }
        }
        else {
          SERIAL_CHAR('Y'); echo_not_entered();
          return;
        }

        if (parser.seenval('Z')) {
          mbl.z_values[px][py] = parser.value_linear_units();
        }
        else {
          SERIAL_CHAR('Z'); echo_not_entered();
          return;
        }
        break;

      case MeshSetZOffset:
        if (parser.seenval('Z')) {
          mbl.z_offset = parser.value_linear_units();
        }
        else {
          SERIAL_CHAR('Z'); echo_not_entered();
          return;
        }
        break;

      case MeshReset:
        reset_bed_level();
        break;

    } // switch(state)

    report_current_position();
  }

#elif HAS_ABL && DISABLED(AUTO_BED_LEVELING_UBL)

  #if ABL_GRID
    #if ENABLED(PROBE_Y_FIRST)
      #define PR_OUTER_VAR xCount
      #define PR_OUTER_END abl_grid_points_x
      #define PR_INNER_VAR yCount
      #define PR_INNER_END abl_grid_points_y
    #else
      #define PR_OUTER_VAR yCount
      #define PR_OUTER_END abl_grid_points_y
      #define PR_INNER_VAR xCount
      #define PR_INNER_END abl_grid_points_x
    #endif
  #endif

  /**
   * G29: Detailed Z probe, probes the bed at 3 or more points.
   *      Will fail if the printer has not been homed with G28.
   *
   * Enhanced G29 Auto Bed Leveling Probe Routine
   *
   *  D  Dry-Run mode. Just evaluate the bed Topology - Don't apply
   *     or alter the bed level data. Useful to check the topology
   *     after a first run of G29.
   *
   *  J  Jettison current bed leveling data
   *
   *  V  Set the verbose level (0-4). Example: "G29 V3"
   *
   * Parameters With LINEAR leveling only:
   *
   *  P  Set the size of the grid that will be probed (P x P points).
   *     Example: "G29 P4"
   *
   *  X  Set the X size of the grid that will be probed (X x Y points).
   *     Example: "G29 X7 Y5"
   *
   *  Y  Set the Y size of the grid that will be probed (X x Y points).
   *
   *  T  Generate a Bed Topology Report. Example: "G29 P5 T" for a detailed report.
   *     This is useful for manual bed leveling and finding flaws in the bed (to
   *     assist with part placement).
   *     Not supported by non-linear delta printer bed leveling.
   *
   * Parameters With LINEAR and BILINEAR leveling only:
   *
   *  S  Set the XY travel speed between probe points (in units/min)
   *
   *  F  Set the Front limit of the probing grid
   *  B  Set the Back limit of the probing grid
   *  L  Set the Left limit of the probing grid
   *  R  Set the Right limit of the probing grid
   *
   * Parameters with DEBUG_LEVELING_FEATURE only:
   *
   *  C  Make a totally fake grid with no actual probing.
   *     For use in testing when no probing is possible.
   *
   * Parameters with BILINEAR leveling only:
   *
   *  Z  Supply an additional Z probe offset
   *
   * Extra parameters with PROBE_MANUALLY:
   *
   *  To do manual probing simply repeat G29 until the procedure is complete.
   *  The first G29 accepts parameters. 'G29 Q' for status, 'G29 A' to abort.
   *
   *  Q  Query leveling and G29 state
   *
   *  A  Abort current leveling procedure
   *
   * Extra parameters with BILINEAR only:
   *
   *  W  Write a mesh point. (If G29 is idle.)
   *  I  X index for mesh point
   *  J  Y index for mesh point
   *  X  X for mesh point, overrides I
   *  Y  Y for mesh point, overrides J
   *  Z  Z for mesh point. Otherwise, raw current Z.
   *
   * Without PROBE_MANUALLY:
   *
   *  E  By default G29 will engage the Z probe, test the bed, then disengage.
   *     Include "E" to engage/disengage the Z probe for each sample.
   *     There's no extra effect if you have a fixed Z probe.
   *
   */
  inline void gcode_G29() {

    // G29 Q is also available if debugging
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      const bool query = parser.seen('Q');
      const uint8_t old_debug_flags = marlin_debug_flags;
      if (query) marlin_debug_flags |= DEBUG_LEVELING;
      if (DEBUGGING(LEVELING)) {
        DEBUG_POS(">>> gcode_G29", current_position);
        log_machine_info();
      }
      marlin_debug_flags = old_debug_flags;
      #if DISABLED(PROBE_MANUALLY)
        if (query) return;
      #endif
    #endif

    #if ENABLED(PROBE_MANUALLY)
      const bool seenA = parser.seen('A'), seenQ = parser.seen('Q'), no_action = seenA || seenQ;
    #endif

    #if ENABLED(DEBUG_LEVELING_FEATURE) && DISABLED(PROBE_MANUALLY)
      const bool faux = parser.boolval('C');
    #elif ENABLED(PROBE_MANUALLY)
      const bool faux = no_action;
    #else
      bool constexpr faux = false;
    #endif

    // Don't allow auto-leveling without homing first
    if (axis_unhomed_error()) return;

    // Define local vars 'static' for manual probing, 'auto' otherwise
    #if ENABLED(PROBE_MANUALLY)
      #define ABL_VAR static
    #else
      #define ABL_VAR
    #endif

    ABL_VAR int verbose_level;
    ABL_VAR float xProbe, yProbe, measured_z;
    ABL_VAR bool dryrun, abl_should_enable;

    #if ENABLED(PROBE_MANUALLY) || ENABLED(AUTO_BED_LEVELING_LINEAR)
      ABL_VAR int abl_probe_index;
    #endif

    #if HAS_SOFTWARE_ENDSTOPS && ENABLED(PROBE_MANUALLY)
      ABL_VAR bool enable_soft_endstops = true;
    #endif

    #if ABL_GRID

      #if ENABLED(PROBE_MANUALLY)
        ABL_VAR uint8_t PR_OUTER_VAR;
        ABL_VAR  int8_t PR_INNER_VAR;
      #endif

      ABL_VAR int left_probe_bed_position, right_probe_bed_position, front_probe_bed_position, back_probe_bed_position;
      ABL_VAR float xGridSpacing, yGridSpacing;

      #if ENABLED(AUTO_BED_LEVELING_LINEAR)
        ABL_VAR uint8_t abl_grid_points_x = GRID_MAX_POINTS_X,
                        abl_grid_points_y = GRID_MAX_POINTS_Y;
        ABL_VAR bool do_topography_map;
      #else // Bilinear
        uint8_t constexpr abl_grid_points_x = GRID_MAX_POINTS_X,
                          abl_grid_points_y = GRID_MAX_POINTS_Y;
      #endif

      #if ENABLED(AUTO_BED_LEVELING_LINEAR) || ENABLED(PROBE_MANUALLY)
        #if ENABLED(AUTO_BED_LEVELING_LINEAR)
          ABL_VAR int abl2;
        #else // Bilinear
          int constexpr abl2 = GRID_MAX_POINTS;
        #endif
      #endif

      #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

        ABL_VAR float zoffset;

      #elif ENABLED(AUTO_BED_LEVELING_LINEAR)

        ABL_VAR int indexIntoAB[GRID_MAX_POINTS_X][GRID_MAX_POINTS_Y];

        ABL_VAR float eqnAMatrix[GRID_MAX_POINTS * 3], // "A" matrix of the linear system of equations
                     eqnBVector[GRID_MAX_POINTS],     // "B" vector of Z points
                     mean;
      #endif

    #elif ENABLED(AUTO_BED_LEVELING_3POINT)

      int constexpr abl2 = 3;

      // Probe at 3 arbitrary points
      ABL_VAR vector_3 points[3] = {
        vector_3(ABL_PROBE_PT_1_X, ABL_PROBE_PT_1_Y, 0),
        vector_3(ABL_PROBE_PT_2_X, ABL_PROBE_PT_2_Y, 0),
        vector_3(ABL_PROBE_PT_3_X, ABL_PROBE_PT_3_Y, 0)
      };

    #endif // AUTO_BED_LEVELING_3POINT

    /**
     * On the initial G29 fetch command parameters.
     */
    if (!g29_in_progress) {

      #if ENABLED(PROBE_MANUALLY) || ENABLED(AUTO_BED_LEVELING_LINEAR)
        abl_probe_index = -1;
      #endif

      abl_should_enable = leveling_is_active();

      #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

        if (parser.seen('W')) {
          if (!leveling_is_valid()) {
            SERIAL_ERROR_START();
            SERIAL_ERRORLNPGM("No bilinear grid");
            return;
          }

          const float z = parser.floatval('Z', RAW_CURRENT_POSITION(Z));
          if (!WITHIN(z, -10, 10)) {
            SERIAL_ERROR_START();
            SERIAL_ERRORLNPGM("Bad Z value");
            return;
          }

          const float x = parser.floatval('X', NAN),
                      y = parser.floatval('Y', NAN);
          int8_t i = parser.byteval('I', -1),
                 j = parser.byteval('J', -1);

          if (!isnan(x) && !isnan(y)) {
            // Get nearest i / j from x / y
            i = (x - LOGICAL_X_POSITION(bilinear_start[X_AXIS]) + 0.5 * xGridSpacing) / xGridSpacing;
            j = (y - LOGICAL_Y_POSITION(bilinear_start[Y_AXIS]) + 0.5 * yGridSpacing) / yGridSpacing;
            i = constrain(i, 0, GRID_MAX_POINTS_X - 1);
            j = constrain(j, 0, GRID_MAX_POINTS_Y - 1);
          }
          if (WITHIN(i, 0, GRID_MAX_POINTS_X - 1) && WITHIN(j, 0, GRID_MAX_POINTS_Y)) {
            set_bed_leveling_enabled(false);
            z_values[i][j] = z;
            #if ENABLED(ABL_BILINEAR_SUBDIVISION)
              bed_level_virt_interpolate();
            #endif
            set_bed_leveling_enabled(abl_should_enable);
          }
          return;
        } // parser.seen('W')

      #endif

      #if HAS_LEVELING

        // Jettison bed leveling data
        if (parser.seen('J')) {
          reset_bed_level();
          return;
        }

      #endif

      verbose_level = parser.intval('V');
      if (!WITHIN(verbose_level, 0, 4)) {
        SERIAL_PROTOCOLLNPGM("?(V)erbose level is implausible (0-4).");
        return;
      }

      dryrun = parser.boolval('D')
        #if ENABLED(PROBE_MANUALLY)
          || no_action
        #endif
      ;

      #if ENABLED(AUTO_BED_LEVELING_LINEAR)

        do_topography_map = verbose_level > 2 || parser.boolval('T');

        // X and Y specify points in each direction, overriding the default
        // These values may be saved with the completed mesh
        abl_grid_points_x = parser.intval('X', GRID_MAX_POINTS_X);
        abl_grid_points_y = parser.intval('Y', GRID_MAX_POINTS_Y);
        if (parser.seenval('P')) abl_grid_points_x = abl_grid_points_y = parser.value_int();

        if (abl_grid_points_x < 2 || abl_grid_points_y < 2) {
          SERIAL_PROTOCOLLNPGM("?Number of probe points is implausible (2 minimum).");
          return;
        }

        abl2 = abl_grid_points_x * abl_grid_points_y;

      #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

        zoffset = parser.linearval('Z');

      #endif

      #if ABL_GRID

        xy_probe_feedrate_mm_s = MMM_TO_MMS(parser.linearval('S', XY_PROBE_SPEED));

        left_probe_bed_position = (int)parser.linearval('L', LOGICAL_X_POSITION(LEFT_PROBE_BED_POSITION));
        right_probe_bed_position = (int)parser.linearval('R', LOGICAL_X_POSITION(RIGHT_PROBE_BED_POSITION));
        front_probe_bed_position = (int)parser.linearval('F', LOGICAL_Y_POSITION(FRONT_PROBE_BED_POSITION));
        back_probe_bed_position = (int)parser.linearval('B', LOGICAL_Y_POSITION(BACK_PROBE_BED_POSITION));

        const bool left_out_l = left_probe_bed_position < LOGICAL_X_POSITION(MIN_PROBE_X),
                   left_out = left_out_l || left_probe_bed_position > right_probe_bed_position - (MIN_PROBE_EDGE),
                   right_out_r = right_probe_bed_position > LOGICAL_X_POSITION(MAX_PROBE_X),
                   right_out = right_out_r || right_probe_bed_position < left_probe_bed_position + MIN_PROBE_EDGE,
                   front_out_f = front_probe_bed_position < LOGICAL_Y_POSITION(MIN_PROBE_Y),
                   front_out = front_out_f || front_probe_bed_position > back_probe_bed_position - (MIN_PROBE_EDGE),
                   back_out_b = back_probe_bed_position > LOGICAL_Y_POSITION(MAX_PROBE_Y),
                   back_out = back_out_b || back_probe_bed_position < front_probe_bed_position + MIN_PROBE_EDGE;

        if (left_out || right_out || front_out || back_out) {
          if (left_out) {
            out_of_range_error(PSTR("(L)eft"));
            left_probe_bed_position = left_out_l ? LOGICAL_X_POSITION(MIN_PROBE_X) : right_probe_bed_position - (MIN_PROBE_EDGE);
          }
          if (right_out) {
            out_of_range_error(PSTR("(R)ight"));
            right_probe_bed_position = right_out_r ? LOGICAL_Y_POSITION(MAX_PROBE_X) : left_probe_bed_position + MIN_PROBE_EDGE;
          }
          if (front_out) {
            out_of_range_error(PSTR("(F)ront"));
            front_probe_bed_position = front_out_f ? LOGICAL_Y_POSITION(MIN_PROBE_Y) : back_probe_bed_position - (MIN_PROBE_EDGE);
          }
          if (back_out) {
            out_of_range_error(PSTR("(B)ack"));
            back_probe_bed_position = back_out_b ? LOGICAL_Y_POSITION(MAX_PROBE_Y) : front_probe_bed_position + MIN_PROBE_EDGE;
          }
          return;
        }

        // probe at the points of a lattice grid
        xGridSpacing = (right_probe_bed_position - left_probe_bed_position) / (abl_grid_points_x - 1);
        yGridSpacing = (back_probe_bed_position - front_probe_bed_position) / (abl_grid_points_y - 1);

      #endif // ABL_GRID

      if (verbose_level > 0) {
        SERIAL_PROTOCOLLNPGM("G29 Auto Bed Leveling");
        if (dryrun) SERIAL_PROTOCOLLNPGM("Running in DRY-RUN mode");
      }

      stepper.synchronize();

      // Disable auto bed leveling during G29
      planner.abl_enabled = false;

      if (!dryrun) {
        // Re-orient the current position without leveling
        // based on where the steppers are positioned.
        set_current_from_steppers_for_axis(ALL_AXES);

        // Sync the planner to where the steppers stopped
        SYNC_PLAN_POSITION_KINEMATIC();
      }

      if (!faux) setup_for_endstop_or_probe_move();

      //xProbe = yProbe = measured_z = 0;

      #if HAS_BED_PROBE
        // Deploy the probe. Probe will raise if needed.
        if (DEPLOY_PROBE()) {
          planner.abl_enabled = abl_should_enable;
          return;
        }
      #endif

      #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

        if ( xGridSpacing != bilinear_grid_spacing[X_AXIS]
          || yGridSpacing != bilinear_grid_spacing[Y_AXIS]
          || left_probe_bed_position != LOGICAL_X_POSITION(bilinear_start[X_AXIS])
          || front_probe_bed_position != LOGICAL_Y_POSITION(bilinear_start[Y_AXIS])
        ) {
          if (dryrun) {
            // Before reset bed level, re-enable to correct the position
            planner.abl_enabled = abl_should_enable;
          }
          // Reset grid to 0.0 or "not probed". (Also disables ABL)
          reset_bed_level();

          // Initialize a grid with the given dimensions
          bilinear_grid_spacing[X_AXIS] = xGridSpacing;
          bilinear_grid_spacing[Y_AXIS] = yGridSpacing;
          bilinear_start[X_AXIS] = RAW_X_POSITION(left_probe_bed_position);
          bilinear_start[Y_AXIS] = RAW_Y_POSITION(front_probe_bed_position);

          // Can't re-enable (on error) until the new grid is written
          abl_should_enable = false;
        }

      #elif ENABLED(AUTO_BED_LEVELING_LINEAR)

        mean = 0.0;

      #endif // AUTO_BED_LEVELING_LINEAR

      #if ENABLED(AUTO_BED_LEVELING_3POINT)

        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("> 3-point Leveling");
        #endif

        // Probe at 3 arbitrary points
        points[0].z = points[1].z = points[2].z = 0;

      #endif // AUTO_BED_LEVELING_3POINT

    } // !g29_in_progress

    #if ENABLED(PROBE_MANUALLY)

      // For manual probing, get the next index to probe now.
      // On the first probe this will be incremented to 0.
      if (!no_action) {
        ++abl_probe_index;
        g29_in_progress = true;
      }

      // Abort current G29 procedure, go back to idle state
      if (seenA && g29_in_progress) {
        SERIAL_PROTOCOLLNPGM("Manual G29 aborted");
        #if HAS_SOFTWARE_ENDSTOPS
          soft_endstops_enabled = enable_soft_endstops;
        #endif
        planner.abl_enabled = abl_should_enable;
        g29_in_progress = false;
        #if ENABLED(LCD_BED_LEVELING)
          lcd_wait_for_move = false;
        #endif
      }

      // Query G29 status
      if (verbose_level || seenQ) {
        SERIAL_PROTOCOLPGM("Manual G29 ");
        if (g29_in_progress) {
          SERIAL_PROTOCOLPAIR("point ", min(abl_probe_index + 1, abl2));
          SERIAL_PROTOCOLLNPAIR(" of ", abl2);
        }
        else
          SERIAL_PROTOCOLLNPGM("idle");
      }

      if (no_action) return;

      if (abl_probe_index == 0) {
        // For the initial G29 save software endstop state
        #if HAS_SOFTWARE_ENDSTOPS
          enable_soft_endstops = soft_endstops_enabled;
        #endif
      }
      else {
        // For G29 after adjusting Z.
        // Save the previous Z before going to the next point
        measured_z = current_position[Z_AXIS];

        #if ENABLED(AUTO_BED_LEVELING_LINEAR)

          mean += measured_z;
          eqnBVector[abl_probe_index] = measured_z;
          eqnAMatrix[abl_probe_index + 0 * abl2] = xProbe;
          eqnAMatrix[abl_probe_index + 1 * abl2] = yProbe;
          eqnAMatrix[abl_probe_index + 2 * abl2] = 1;

        #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

          z_values[xCount][yCount] = measured_z + zoffset;

          #if ENABLED(DEBUG_LEVELING_FEATURE)
            if (DEBUGGING(LEVELING)) {
              SERIAL_PROTOCOLPAIR("Save X", xCount);
              SERIAL_PROTOCOLPAIR(" Y", yCount);
              SERIAL_PROTOCOLLNPAIR(" Z", measured_z + zoffset);
            }
          #endif

        #elif ENABLED(AUTO_BED_LEVELING_3POINT)

          points[abl_probe_index].z = measured_z;

        #endif
      }

      //
      // If there's another point to sample, move there with optional lift.
      //

      #if ABL_GRID

        // Skip any unreachable points
        while (abl_probe_index < abl2) {

          // Set xCount, yCount based on abl_probe_index, with zig-zag
          PR_OUTER_VAR = abl_probe_index / PR_INNER_END;
          PR_INNER_VAR = abl_probe_index - (PR_OUTER_VAR * PR_INNER_END);

          // Probe in reverse order for every other row/column
          bool zig = (PR_OUTER_VAR & 1); // != ((PR_OUTER_END) & 1);

          if (zig) PR_INNER_VAR = (PR_INNER_END - 1) - PR_INNER_VAR;

          const float xBase = xCount * xGridSpacing + left_probe_bed_position,
                      yBase = yCount * yGridSpacing + front_probe_bed_position;

          xProbe = FLOOR(xBase + (xBase < 0 ? 0 : 0.5));
          yProbe = FLOOR(yBase + (yBase < 0 ? 0 : 0.5));

          #if ENABLED(AUTO_BED_LEVELING_LINEAR)
            indexIntoAB[xCount][yCount] = abl_probe_index;
          #endif

          // Keep looping till a reachable point is found
          if (position_is_reachable_xy(xProbe, yProbe)) break;
          ++abl_probe_index;
        }

        // Is there a next point to move to?
        if (abl_probe_index < abl2) {
          _manual_goto_xy(xProbe, yProbe); // Can be used here too!
          #if HAS_SOFTWARE_ENDSTOPS
            // Disable software endstops to allow manual adjustment
            // If G29 is not completed, they will not be re-enabled
            soft_endstops_enabled = false;
          #endif
          return;
        }
        else {

          // Leveling done! Fall through to G29 finishing code below

          SERIAL_PROTOCOLLNPGM("Grid probing done.");

          // Re-enable software endstops, if needed
          #if HAS_SOFTWARE_ENDSTOPS
            soft_endstops_enabled = enable_soft_endstops;
          #endif
        }

      #elif ENABLED(AUTO_BED_LEVELING_3POINT)

        // Probe at 3 arbitrary points
        if (abl_probe_index < 3) {
          xProbe = LOGICAL_X_POSITION(points[abl_probe_index].x);
          yProbe = LOGICAL_Y_POSITION(points[abl_probe_index].y);
          #if HAS_SOFTWARE_ENDSTOPS
            // Disable software endstops to allow manual adjustment
            // If G29 is not completed, they will not be re-enabled
            soft_endstops_enabled = false;
          #endif
          return;
        }
        else {

          SERIAL_PROTOCOLLNPGM("3-point probing done.");

          // Re-enable software endstops, if needed
          #if HAS_SOFTWARE_ENDSTOPS
            soft_endstops_enabled = enable_soft_endstops;
          #endif

          if (!dryrun) {
            vector_3 planeNormal = vector_3::cross(points[0] - points[1], points[2] - points[1]).get_normal();
            if (planeNormal.z < 0) {
              planeNormal.x *= -1;
              planeNormal.y *= -1;
              planeNormal.z *= -1;
            }
            planner.bed_level_matrix = matrix_3x3::create_look_at(planeNormal);

            // Can't re-enable (on error) until the new grid is written
            abl_should_enable = false;
          }

        }

      #endif // AUTO_BED_LEVELING_3POINT

    #else // !PROBE_MANUALLY

      const bool stow_probe_after_each = parser.boolval('E');

      #if ABL_GRID

        bool zig = PR_OUTER_END & 1;  // Always end at RIGHT and BACK_PROBE_BED_POSITION

        // Outer loop is Y with PROBE_Y_FIRST disabled
        for (uint8_t PR_OUTER_VAR = 0; PR_OUTER_VAR < PR_OUTER_END; PR_OUTER_VAR++) {

          int8_t inStart, inStop, inInc;

          if (zig) { // away from origin
            inStart = 0;
            inStop = PR_INNER_END;
            inInc = 1;
          }
          else {     // towards origin
            inStart = PR_INNER_END - 1;
            inStop = -1;
            inInc = -1;
          }

          zig ^= true; // zag

          // Inner loop is Y with PROBE_Y_FIRST enabled
          for (int8_t PR_INNER_VAR = inStart; PR_INNER_VAR != inStop; PR_INNER_VAR += inInc) {

            float xBase = left_probe_bed_position + xGridSpacing * xCount,
                  yBase = front_probe_bed_position + yGridSpacing * yCount;

            xProbe = FLOOR(xBase + (xBase < 0 ? 0 : 0.5));
            yProbe = FLOOR(yBase + (yBase < 0 ? 0 : 0.5));

            #if ENABLED(AUTO_BED_LEVELING_LINEAR)
              indexIntoAB[xCount][yCount] = ++abl_probe_index; // 0...
            #endif

            #if IS_KINEMATIC
              // Avoid probing outside the round or hexagonal area
              if (!position_is_reachable_by_probe_xy(xProbe, yProbe)) continue;
            #endif

            measured_z = faux ? 0.001 * random(-100, 101) : probe_pt(xProbe, yProbe, stow_probe_after_each, verbose_level);

            if (isnan(measured_z)) {
              planner.abl_enabled = abl_should_enable;
              return;
            }

            #if ENABLED(AUTO_BED_LEVELING_LINEAR)

              mean += measured_z;
              eqnBVector[abl_probe_index] = measured_z;
              eqnAMatrix[abl_probe_index + 0 * abl2] = xProbe;
              eqnAMatrix[abl_probe_index + 1 * abl2] = yProbe;
              eqnAMatrix[abl_probe_index + 2 * abl2] = 1;

            #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

              z_values[xCount][yCount] = measured_z + zoffset;

            #endif

            abl_should_enable = false;
            idle();

          } // inner
        } // outer

      #elif ENABLED(AUTO_BED_LEVELING_3POINT)

        // Probe at 3 arbitrary points

        for (uint8_t i = 0; i < 3; ++i) {
          // Retain the last probe position
          xProbe = LOGICAL_X_POSITION(points[i].x);
          yProbe = LOGICAL_Y_POSITION(points[i].y);
          measured_z = faux ? 0.001 * random(-100, 101) : probe_pt(xProbe, yProbe, stow_probe_after_each, verbose_level);
          if (isnan(measured_z)) {
            planner.abl_enabled = abl_should_enable;
            return;
          }
          points[i].z = measured_z;
        }

        if (!dryrun) {
          vector_3 planeNormal = vector_3::cross(points[0] - points[1], points[2] - points[1]).get_normal();
          if (planeNormal.z < 0) {
            planeNormal.x *= -1;
            planeNormal.y *= -1;
            planeNormal.z *= -1;
          }
          planner.bed_level_matrix = matrix_3x3::create_look_at(planeNormal);

          // Can't re-enable (on error) until the new grid is written
          abl_should_enable = false;
        }

      #endif // AUTO_BED_LEVELING_3POINT

      // Raise to _Z_CLEARANCE_DEPLOY_PROBE. Stow the probe.
      if (STOW_PROBE()) {
        planner.abl_enabled = abl_should_enable;
        return;
      }

    #endif // !PROBE_MANUALLY

    //
    // G29 Finishing Code
    //
    // Unless this is a dry run, auto bed leveling will
    // definitely be enabled after this point.
    //
    // If code above wants to continue leveling, it should
    // return or loop before this point.
    //

    // Restore state after probing
    if (!faux) clean_up_after_endstop_or_probe_move();

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) DEBUG_POS("> probing complete", current_position);
    #endif

    #if ENABLED(PROBE_MANUALLY)
      g29_in_progress = false;
      #if ENABLED(LCD_BED_LEVELING)
        lcd_wait_for_move = false;
      #endif
    #endif

    // Calculate leveling, print reports, correct the position
    #if ENABLED(AUTO_BED_LEVELING_BILINEAR)

      if (!dryrun) extrapolate_unprobed_bed_level();
      print_bilinear_leveling_grid();

      refresh_bed_level();

      #if ENABLED(ABL_BILINEAR_SUBDIVISION)
        bed_level_virt_print();
      #endif

    #elif ENABLED(AUTO_BED_LEVELING_LINEAR)

      // For LINEAR leveling calculate matrix, print reports, correct the position

      /**
       * solve the plane equation ax + by + d = z
       * A is the matrix with rows [x y 1] for all the probed points
       * B is the vector of the Z positions
       * the normal vector to the plane is formed by the coefficients of the
       * plane equation in the standard form, which is Vx*x+Vy*y+Vz*z+d = 0
       * so Vx = -a Vy = -b Vz = 1 (we want the vector facing towards positive Z
       */
      float plane_equation_coefficients[3];
      qr_solve(plane_equation_coefficients, abl2, 3, eqnAMatrix, eqnBVector);

      mean /= abl2;

      if (verbose_level) {
        SERIAL_PROTOCOLPGM("Eqn coefficients: a: ");
        SERIAL_PROTOCOL_F(plane_equation_coefficients[0], 8);
        SERIAL_PROTOCOLPGM(" b: ");
        SERIAL_PROTOCOL_F(plane_equation_coefficients[1], 8);
        SERIAL_PROTOCOLPGM(" d: ");
        SERIAL_PROTOCOL_F(plane_equation_coefficients[2], 8);
        SERIAL_EOL();
        if (verbose_level > 2) {
          SERIAL_PROTOCOLPGM("Mean of sampled points: ");
          SERIAL_PROTOCOL_F(mean, 8);
          SERIAL_EOL();
        }
      }

      // Create the matrix but don't correct the position yet
      if (!dryrun) {
        planner.bed_level_matrix = matrix_3x3::create_look_at(
          vector_3(-plane_equation_coefficients[0], -plane_equation_coefficients[1], 1)
        );
      }

      // Show the Topography map if enabled
      if (do_topography_map) {

        SERIAL_PROTOCOLLNPGM("\nBed Height Topography:\n"
                               "   +--- BACK --+\n"
                               "   |           |\n"
                               " L |    (+)    | R\n"
                               " E |           | I\n"
                               " F | (-) N (+) | G\n"
                               " T |           | H\n"
                               "   |    (-)    | T\n"
                               "   |           |\n"
                               "   O-- FRONT --+\n"
                               " (0,0)");

        float min_diff = 999;

        for (int8_t yy = abl_grid_points_y - 1; yy >= 0; yy--) {
          for (uint8_t xx = 0; xx < abl_grid_points_x; xx++) {
            int ind = indexIntoAB[xx][yy];
            float diff = eqnBVector[ind] - mean,
                  x_tmp = eqnAMatrix[ind + 0 * abl2],
                  y_tmp = eqnAMatrix[ind + 1 * abl2],
                  z_tmp = 0;

            apply_rotation_xyz(planner.bed_level_matrix, x_tmp, y_tmp, z_tmp);

            NOMORE(min_diff, eqnBVector[ind] - z_tmp);

            if (diff >= 0.0)
              SERIAL_PROTOCOLPGM(" +");   // Include + for column alignment
            else
              SERIAL_PROTOCOLCHAR(' ');
            SERIAL_PROTOCOL_F(diff, 5);
          } // xx
          SERIAL_EOL();
        } // yy
        SERIAL_EOL();

        if (verbose_level > 3) {
          SERIAL_PROTOCOLLNPGM("\nCorrected Bed Height vs. Bed Topology:");

          for (int8_t yy = abl_grid_points_y - 1; yy >= 0; yy--) {
            for (uint8_t xx = 0; xx < abl_grid_points_x; xx++) {
              int ind = indexIntoAB[xx][yy];
              float x_tmp = eqnAMatrix[ind + 0 * abl2],
                    y_tmp = eqnAMatrix[ind + 1 * abl2],
                    z_tmp = 0;

              apply_rotation_xyz(planner.bed_level_matrix, x_tmp, y_tmp, z_tmp);

              float diff = eqnBVector[ind] - z_tmp - min_diff;
              if (diff >= 0.0)
                SERIAL_PROTOCOLPGM(" +");
              // Include + for column alignment
              else
                SERIAL_PROTOCOLCHAR(' ');
              SERIAL_PROTOCOL_F(diff, 5);
            } // xx
            SERIAL_EOL();
          } // yy
          SERIAL_EOL();
        }
      } //do_topography_map

    #endif // AUTO_BED_LEVELING_LINEAR

    #if ABL_PLANAR

      // For LINEAR and 3POINT leveling correct the current position

      if (verbose_level > 0)
        planner.bed_level_matrix.debug(PSTR("\n\nBed Level Correction Matrix:"));

      if (!dryrun) {
        //
        // Correct the current XYZ position based on the tilted plane.
        //

        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) DEBUG_POS("G29 uncorrected XYZ", current_position);
        #endif

        float converted[XYZ];
        COPY(converted, current_position);

        planner.abl_enabled = true;
        planner.unapply_leveling(converted); // use conversion machinery
        planner.abl_enabled = false;

        // Use the last measured distance to the bed, if possible
        if ( NEAR(current_position[X_AXIS], xProbe - (X_PROBE_OFFSET_FROM_EXTRUDER))
          && NEAR(current_position[Y_AXIS], yProbe - (Y_PROBE_OFFSET_FROM_EXTRUDER))
        ) {
          const float simple_z = current_position[Z_AXIS] - measured_z;
          #if ENABLED(DEBUG_LEVELING_FEATURE)
            if (DEBUGGING(LEVELING)) {
              SERIAL_ECHOPAIR("Z from Probe:", simple_z);
              SERIAL_ECHOPAIR("  Matrix:", converted[Z_AXIS]);
              SERIAL_ECHOLNPAIR("  Discrepancy:", simple_z - converted[Z_AXIS]);
            }
          #endif
          converted[Z_AXIS] = simple_z;
        }

        // The rotated XY and corrected Z are now current_position
        COPY(current_position, converted);

        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) DEBUG_POS("G29 corrected XYZ", current_position);
        #endif
      }

    #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

      if (!dryrun) {
        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPAIR("G29 uncorrected Z:", current_position[Z_AXIS]);
        #endif

        // Unapply the offset because it is going to be immediately applied
        // and cause compensation movement in Z
        current_position[Z_AXIS] -= bilinear_z_offset(current_position);

        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPAIR(" corrected Z:", current_position[Z_AXIS]);
        #endif
      }

    #endif // ABL_PLANAR

    #ifdef Z_PROBE_END_SCRIPT
      #if ENABLED(DEBUG_LEVELING_FEATURE)
        if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPAIR("Z Probe End Script: ", Z_PROBE_END_SCRIPT);
      #endif
      enqueue_and_echo_commands_P(PSTR(Z_PROBE_END_SCRIPT));
      stepper.synchronize();
    #endif

    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("<<< gcode_G29");
    #endif

    report_current_position();

    KEEPALIVE_STATE(IN_HANDLER);

    // Auto Bed Leveling is complete! Enable if possible.
    planner.abl_enabled = dryrun ? abl_should_enable : true;

    if (planner.abl_enabled)
      SYNC_PLAN_POSITION_KINEMATIC();
  }

#endif // HAS_ABL && !AUTO_BED_LEVELING_UBL

#if HAS_BED_PROBE

  /**
   * G30: Do a single Z probe at the current XY
   *
   * Parameters:
   *
   *   X   Probe X position (default current X)
   *   Y   Probe Y position (default current Y)
   *   S0  Leave the probe deployed
   */
  inline void gcode_G30() {
    const float xpos = parser.linearval('X', current_position[X_AXIS] + X_PROBE_OFFSET_FROM_EXTRUDER),
                ypos = parser.linearval('Y', current_position[Y_AXIS] + Y_PROBE_OFFSET_FROM_EXTRUDER);

    if (!position_is_reachable_by_probe_xy(xpos, ypos)) return;

    // Disable leveling so the planner won't mess with us
    #if HAS_LEVELING
      set_bed_leveling_enabled(false);
    #endif

    setup_for_endstop_or_probe_move();

    const float measured_z = probe_pt(xpos, ypos, parser.boolval('S', true), 1);

    if (!isnan(measured_z)) {
      SERIAL_PROTOCOLPAIR("Bed X: ", FIXFLOAT(xpos));
      SERIAL_PROTOCOLPAIR(" Y: ", FIXFLOAT(ypos));
      SERIAL_PROTOCOLLNPAIR(" Z: ", FIXFLOAT(measured_z));
    }

    clean_up_after_endstop_or_probe_move();

    report_current_position();
  }

  #if ENABLED(Z_PROBE_SLED)

    /**
     * G31: Deploy the Z probe
     */
    inline void gcode_G31() { DEPLOY_PROBE(); }

    /**
     * G32: Stow the Z probe
     */
    inline void gcode_G32() { STOW_PROBE(); }

  #endif // Z_PROBE_SLED

#endif // HAS_BED_PROBE

#if PROBE_SELECTED

  #if ENABLED(DELTA_AUTO_CALIBRATION)
    /**
     * G33 - Delta '1-4-7-point' Auto-Calibration
     *       Calibrate height, endstops, delta radius, and tower angles.
     *
     * Parameters:
     *
     *   Pn  Number of probe points:
     *
     *      P1     Probe center and set height only.
     *      P2     Probe center and towers. Set height, endstops, and delta radius.
     *      P3     Probe all positions: center, towers and opposite towers. Set all.
     *      P4-P7  Probe all positions at different locations and average them.
     *
     *   T0  Don't calibrate tower angle corrections
     *
     *   Cn.nn Calibration precision; when omitted calibrates to maximum precision
     *
     *   Fn  Force to run at least n iterations and takes the best result
     *
     *   Vn  Verbose level:
     *
     *      V0  Dry-run mode. Report settings and probe results. No calibration.
     *      V1  Report settings
     *      V2  Report settings and probe results
     *
     *   E   Engage the probe for each point
     */

    void print_signed_float(const char * const prefix, const float &f) {
      SERIAL_PROTOCOLPGM("  ");
      serialprintPGM(prefix);
      SERIAL_PROTOCOLCHAR(':');
      if (f >= 0) SERIAL_CHAR('+');
      SERIAL_PROTOCOL_F(f, 2);
    }

    inline void gcode_G33() {

      const int8_t probe_points = parser.intval('P', DELTA_CALIBRATION_DEFAULT_POINTS);
      if (!WITHIN(probe_points, 1, 7)) {
        SERIAL_PROTOCOLLNPGM("?(P)oints is implausible (1 to 7).");
        return;
      }

      const int8_t verbose_level = parser.byteval('V', 1);
      if (!WITHIN(verbose_level, 0, 2)) {
        SERIAL_PROTOCOLLNPGM("?(V)erbose level is implausible (0-2).");
        return;
      }

      const float calibration_precision = parser.floatval('C');
      if (calibration_precision < 0) {
        SERIAL_PROTOCOLLNPGM("?(C)alibration precision is implausible (>0).");
        return;
      }

      const int8_t force_iterations = parser.intval('F', 0);
      if (!WITHIN(force_iterations, 0, 30)) {
        SERIAL_PROTOCOLLNPGM("?(F)orce iteration is implausible (0-30).");
        return;
      }

      const bool towers_set           = parser.boolval('T', true),
                 stow_after_each      = parser.boolval('E'),
                 _1p_calibration      = probe_points == 1,
                 _4p_calibration      = probe_points == 2,
                 _4p_towers_points    = _4p_calibration && towers_set,
                 _4p_opposite_points  = _4p_calibration && !towers_set,
                 _7p_calibration      = probe_points >= 3,
                 _7p_half_circle      = probe_points == 3,
                 _7p_double_circle    = probe_points == 5,
                 _7p_triple_circle    = probe_points == 6,
                 _7p_quadruple_circle = probe_points == 7,
                 _7p_multi_circle     = _7p_double_circle || _7p_triple_circle || _7p_quadruple_circle,
                 _7p_intermed_points  = _7p_calibration && !_7p_half_circle;
      const static char save_message[] PROGMEM = "Save with M500 and/or copy to Configuration.h";
      const float dx = (X_PROBE_OFFSET_FROM_EXTRUDER),
                  dy = (Y_PROBE_OFFSET_FROM_EXTRUDER);
      int8_t iterations = 0;
      float test_precision,
            zero_std_dev = (verbose_level ? 999.0 : 0.0), // 0.0 in dry-run mode : forced end
            zero_std_dev_old = zero_std_dev,
            zero_std_dev_min = zero_std_dev,
            e_old[XYZ] = {
              endstop_adj[A_AXIS],
              endstop_adj[B_AXIS],
              endstop_adj[C_AXIS]
            },
            dr_old = delta_radius,
            zh_old = home_offset[Z_AXIS],
            alpha_old = delta_tower_angle_trim[A_AXIS],
            beta_old = delta_tower_angle_trim[B_AXIS];

      if (!_1p_calibration) {  // test if the outer radius is reachable
        const float circles = (_7p_quadruple_circle ? 1.5 :
                               _7p_triple_circle    ? 1.0 :
                               _7p_double_circle    ? 0.5 : 0),
                    r = (1 + circles * 0.1) * delta_calibration_radius;
        for (uint8_t axis = 1; axis < 13; ++axis) {
          const float a = RADIANS(180 + 30 * axis);
          if (!position_is_reachable_xy(cos(a) * r, sin(a) * r)) {
            SERIAL_PROTOCOLLNPGM("?(M665 B)ed radius is implausible.");
            return;
          }
        }
      }
      SERIAL_PROTOCOLLNPGM("G33 Auto Calibrate");

      stepper.synchronize();
      #if HAS_LEVELING
        reset_bed_level(); // After calibration bed-level data is no longer valid
      #endif
      #if HOTENDS > 1
        const uint8_t old_tool_index = active_extruder;
        tool_change(0, 0, true);
      #endif
      setup_for_endstop_or_probe_move();
      DEPLOY_PROBE();
      endstops.enable(true);
      home_delta();
      endstops.not_homing();

      // print settings

      SERIAL_PROTOCOLPGM("Checking... AC");
      if (verbose_level == 0) SERIAL_PROTOCOLPGM(" (DRY-RUN)");
      SERIAL_EOL();
      LCD_MESSAGEPGM("Checking... AC"); // TODO: Make translatable string

      SERIAL_PROTOCOLPAIR(".Height:", DELTA_HEIGHT + home_offset[Z_AXIS]);
      if (!_1p_calibration) {
        print_signed_float(PSTR("  Ex"), endstop_adj[A_AXIS]);
        print_signed_float(PSTR("Ey"), endstop_adj[B_AXIS]);
        print_signed_float(PSTR("Ez"), endstop_adj[C_AXIS]);
        SERIAL_PROTOCOLPAIR("    Radius:", delta_radius);
      }
      SERIAL_EOL();
      if (_7p_calibration && towers_set) {
        SERIAL_PROTOCOLPGM(".Tower angle :  ");
        print_signed_float(PSTR("Tx"), delta_tower_angle_trim[A_AXIS]);
        print_signed_float(PSTR("Ty"), delta_tower_angle_trim[B_AXIS]);
        SERIAL_PROTOCOLPGM("  Tz:+0.00");
        SERIAL_EOL();
      }

      #if DISABLED(PROBE_MANUALLY)
        home_offset[Z_AXIS] -= probe_pt(dx, dy, stow_after_each, 1, false); // 1st probe to set height
      #endif
      
      do {

        float z_at_pt[13] = { 0.0 };

        test_precision = zero_std_dev_old != 999.0 ? (zero_std_dev + zero_std_dev_old) / 2 : zero_std_dev;

        iterations++;

        // Probe the points

        if (!_7p_half_circle && !_7p_triple_circle) { // probe the center
          #if ENABLED(PROBE_MANUALLY)
            z_at_pt[0] += lcd_probe_pt(0, 0);
          #else
            z_at_pt[0] += probe_pt(dx, dy, stow_after_each, 1, false);
          #endif
        }
        if (_7p_calibration) { // probe extra center points
          for (int8_t axis = _7p_multi_circle ? 11 : 9; axis > 0; axis -= _7p_multi_circle ? 2 : 4) {
            const float a = RADIANS(180 + 30 * axis), r = delta_calibration_radius * 0.1;
            #if ENABLED(PROBE_MANUALLY)
              z_at_pt[0] += lcd_probe_pt(cos(a) * r, sin(a) * r);
            #else
              z_at_pt[0] += probe_pt(cos(a) * r + dx, sin(a) * r + dy, stow_after_each, 1, false);
            #endif
          }
          z_at_pt[0] /= float(_7p_double_circle ? 7 : probe_points);
        }
        if (!_1p_calibration) {  // probe the radius
          bool zig_zag = true;
          const uint8_t start = _4p_opposite_points ? 3 : 1,
                         step = _4p_calibration ? 4 : _7p_half_circle ? 2 : 1;
          for (uint8_t axis = start; axis < 13; axis += step) {
            const float zigadd = (zig_zag ? 0.5 : 0.0),
                        offset_circles = _7p_quadruple_circle ? zigadd + 1.0 :
                                         _7p_triple_circle    ? zigadd + 0.5 :
                                         _7p_double_circle    ? zigadd : 0;
            for (float circles = -offset_circles ; circles <= offset_circles; circles++) {
              const float a = RADIANS(180 + 30 * axis),
                          r = delta_calibration_radius * (1 + circles * (zig_zag ? 0.1 : -0.1));
              #if ENABLED(PROBE_MANUALLY)
                z_at_pt[axis] += lcd_probe_pt(cos(a) * r, sin(a) * r);
              #else
                z_at_pt[axis] += probe_pt(cos(a) * r + dx, sin(a) * r + dy, stow_after_each, 1, false);
              #endif
            }
            zig_zag = !zig_zag;
            z_at_pt[axis] /= (2 * offset_circles + 1);
          }
        }
        if (_7p_intermed_points) // average intermediates to tower and opposites
          for (uint8_t axis = 1; axis < 13; axis += 2)
            z_at_pt[axis] = (z_at_pt[axis] + (z_at_pt[axis + 1] + z_at_pt[(axis + 10) % 12 + 1]) / 2.0) / 2.0;

        float S1 = z_at_pt[0],
              S2 = sq(z_at_pt[0]);
        int16_t N = 1;
        if (!_1p_calibration) // std dev from zero plane
          for (uint8_t axis = (_4p_opposite_points ? 3 : 1); axis < 13; axis += (_4p_calibration ? 4 : 2)) {
            S1 += z_at_pt[axis];
            S2 += sq(z_at_pt[axis]);
            N++;
          }
        zero_std_dev_old = zero_std_dev;
        NOMORE(zero_std_dev_min, zero_std_dev);
        zero_std_dev = round(sqrt(S2 / N) * 1000.0) / 1000.0 + 0.00001;

        // Solve matrices

        if ((zero_std_dev < test_precision && zero_std_dev > calibration_precision) || iterations <= force_iterations) {
          if (zero_std_dev < zero_std_dev_min) {
            COPY(e_old, endstop_adj);
            dr_old = delta_radius;
            zh_old = home_offset[Z_AXIS];
            alpha_old = delta_tower_angle_trim[A_AXIS];
            beta_old = delta_tower_angle_trim[B_AXIS];
          }

          float e_delta[XYZ] = { 0.0 }, r_delta = 0.0, t_alpha = 0.0, t_beta = 0.0;
          const float r_diff = delta_radius - delta_calibration_radius,
                      h_factor = 1.00 + r_diff * 0.001,                          //1.02 for r_diff = 20mm
                      r_factor = -(1.75 + 0.005 * r_diff + 0.001 * sq(r_diff)),  //2.25 for r_diff = 20mm
                      a_factor = 100.0 / delta_calibration_radius;               //1.25 for cal_rd = 80mm

          #define ZP(N,I) ((N) * z_at_pt[I])
          #define Z1000(I) ZP(1.00, I)
          #define Z1050(I) ZP(h_factor, I)
          #define Z0700(I) ZP(h_factor * 2.0 / 3.00, I)
          #define Z0350(I) ZP(h_factor / 3.00, I)
          #define Z0175(I) ZP(h_factor / 6.00, I)
          #define Z2250(I) ZP(r_factor, I)
          #define Z0750(I) ZP(r_factor / 3.00, I)
          #define Z0375(I) ZP(r_factor / 6.00, I)
          #define Z0444(I) ZP(a_factor * 4.0 / 9.0, I)
          #define Z0888(I) ZP(a_factor * 8.0 / 9.0, I)

          #if ENABLED(PROBE_MANUALLY)
            test_precision = 0.00; // forced end
          #endif
          
          switch (probe_points) {
            case 1:
              test_precision = 0.00; // forced end
              LOOP_XYZ(i) e_delta[i] = Z1000(0);
              break;

            case 2:
              if (towers_set) {
                e_delta[X_AXIS] = Z1050(0) + Z0700(1) - Z0350(5) - Z0350(9);
                e_delta[Y_AXIS] = Z1050(0) - Z0350(1) + Z0700(5) - Z0350(9);
                e_delta[Z_AXIS] = Z1050(0) - Z0350(1) - Z0350(5) + Z0700(9);
                r_delta         = Z2250(0) - Z0750(1) - Z0750(5) - Z0750(9);
              }
              else {
                e_delta[X_AXIS] = Z1050(0) - Z0700(7) + Z0350(11) + Z0350(3);
                e_delta[Y_AXIS] = Z1050(0) + Z0350(7) - Z0700(11) + Z0350(3);
                e_delta[Z_AXIS] = Z1050(0) + Z0350(7) + Z0350(11) - Z0700(3);
                r_delta         = Z2250(0) - Z0750(7) - Z0750(11) - Z0750(3);
              }
              break;

            default:
              e_delta[X_AXIS] = Z1050(0) + Z0350(1) - Z0175(5) - Z0175(9) - Z0350(7) + Z0175(11) + Z0175(3);
              e_delta[Y_AXIS] = Z1050(0) - Z0175(1) + Z0350(5) - Z0175(9) + Z0175(7) - Z0350(11) + Z0175(3);
              e_delta[Z_AXIS] = Z1050(0) - Z0175(1) - Z0175(5) + Z0350(9) + Z0175(7) + Z0175(11) - Z0350(3);
              r_delta         = Z2250(0) - Z0375(1) - Z0375(5) - Z0375(9) - Z0375(7) - Z0375(11) - Z0375(3);

              if (towers_set) {
                t_alpha = Z0444(1) - Z0888(5) + Z0444(9) + Z0444(7) - Z0888(11) + Z0444(3);
                t_beta  = Z0888(1) - Z0444(5) - Z0444(9) + Z0888(7) - Z0444(11) - Z0444(3);
              }
              break;
          }

          LOOP_XYZ(axis) endstop_adj[axis] += e_delta[axis];
          delta_radius += r_delta;
          delta_tower_angle_trim[A_AXIS] += t_alpha;
          delta_tower_angle_trim[B_AXIS] += t_beta;

          // adjust delta_height and endstops by the max amount
          const float z_temp = MAX3(endstop_adj[A_AXIS], endstop_adj[B_AXIS], endstop_adj[C_AXIS]);
          home_offset[Z_AXIS] -= z_temp;
          LOOP_XYZ(i) endstop_adj[i] -= z_temp;

          recalc_delta_settings(delta_radius, delta_diagonal_rod);
        }
        else if (zero_std_dev >= test_precision) {   // step one back
          COPY(endstop_adj, e_old);
          delta_radius = dr_old;
          home_offset[Z_AXIS] = zh_old;
          delta_tower_angle_trim[A_AXIS] = alpha_old;
          delta_tower_angle_trim[B_AXIS] = beta_old;

          recalc_delta_settings(delta_radius, delta_diagonal_rod);
        }

         // print report

        if (verbose_level != 1) {
          SERIAL_PROTOCOLPGM(".    ");
          print_signed_float(PSTR("c"), z_at_pt[0]);
          if (_4p_towers_points || _7p_calibration) {
            print_signed_float(PSTR("   x"), z_at_pt[1]);
            print_signed_float(PSTR(" y"), z_at_pt[5]);
            print_signed_float(PSTR(" z"), z_at_pt[9]);
          }
          if (!_4p_opposite_points) SERIAL_EOL();
          if ((_4p_opposite_points) || _7p_calibration) {
            if (_7p_calibration) {
              SERIAL_CHAR('.');
              SERIAL_PROTOCOL_SP(13);
            }
            print_signed_float(PSTR("  yz"), z_at_pt[7]);
            print_signed_float(PSTR("zx"), z_at_pt[11]);
            print_signed_float(PSTR("xy"), z_at_pt[3]);
            SERIAL_EOL();
          }
        }
        if (verbose_level != 0) {                                    // !dry run
          if ((zero_std_dev >= test_precision || zero_std_dev <= calibration_precision) && iterations > force_iterations) {  // end iterations
            SERIAL_PROTOCOLPGM("Calibration OK");
            SERIAL_PROTOCOL_SP(36);
            #if DISABLED(PROBE_MANUALLY)
              if (zero_std_dev >= test_precision && !_1p_calibration)
                SERIAL_PROTOCOLPGM("rolling back.");
              else
            #endif
              {
                SERIAL_PROTOCOLPGM("std dev:");
                SERIAL_PROTOCOL_F(zero_std_dev, 3);
              }
            SERIAL_EOL();
            LCD_MESSAGEPGM("Calibration OK"); // TODO: Make translatable string
          }
          else {                                                     // !end iterations
            char mess[15] = "No convergence";
            if (iterations < 31)
              sprintf_P(mess, PSTR("Iteration : %02i"), (int)iterations);
            SERIAL_PROTOCOL(mess);
            SERIAL_PROTOCOL_SP(36);
            SERIAL_PROTOCOLPGM("std dev:");
            SERIAL_PROTOCOL_F(zero_std_dev, 3);
            SERIAL_EOL();
            lcd_setstatus(mess);
          }
          SERIAL_PROTOCOLPAIR(".Height:", DELTA_HEIGHT + home_offset[Z_AXIS]);
          if (!_1p_calibration) {
            print_signed_float(PSTR("  Ex"), endstop_adj[A_AXIS]);
            print_signed_float(PSTR("Ey"), endstop_adj[B_AXIS]);
            print_signed_float(PSTR("Ez"), endstop_adj[C_AXIS]);
            SERIAL_PROTOCOLPAIR("    Radius:", delta_radius);
          }
          SERIAL_EOL();
          if (_7p_calibration && towers_set) {
            SERIAL_PROTOCOLPGM(".Tower angle :  ");
            print_signed_float(PSTR("Tx"), delta_tower_angle_trim[A_AXIS]);
            print_signed_float(PSTR("Ty"), delta_tower_angle_trim[B_AXIS]);
            SERIAL_PROTOCOLPGM("  Tz:+0.00");
            SERIAL_EOL();
          }
          if ((zero_std_dev >= test_precision || zero_std_dev <= calibration_precision) && iterations > force_iterations)
            serialprintPGM(save_message);
            SERIAL_EOL();
        }
        else {                                                       // dry run
          SERIAL_PROTOCOLPGM("End DRY-RUN");
          SERIAL_PROTOCOL_SP(39);
          SERIAL_PROTOCOLPGM("std dev:");
          SERIAL_PROTOCOL_F(zero_std_dev, 3);
          SERIAL_EOL();
        }

        endstops.enable(true);
        home_delta();
        endstops.not_homing();

      }
      while ((zero_std_dev < test_precision && zero_std_dev > calibration_precision && iterations < 31) || iterations <= force_iterations);

      #if ENABLED(DELTA_HOME_TO_SAFE_ZONE)
        do_blocking_move_to_z(delta_clip_start_height);
      #endif
      STOW_PROBE();
      clean_up_after_endstop_or_probe_move();
      #if HOTENDS > 1
        tool_change(old_tool_index, 0, true);
      #endif
    }

  #endif // DELTA_AUTO_CALIBRATION

#endif // PROBE_SELECTED

#if ENABLED(G38_PROBE_TARGET)

  static bool G38_run_probe() {

    bool G38_pass_fail = false;

    // Get direction of move and retract
    float retract_mm[XYZ];
    LOOP_XYZ(i) {
      float dist = destination[i] - current_position[i];
      retract_mm[i] = FABS(dist) < G38_MINIMUM_MOVE ? 0 : home_bump_mm((AxisEnum)i) * (dist > 0 ? -1 : 1);
    }

    stepper.synchronize();  // wait until the machine is idle

    // Move until destination reached or target hit
    endstops.enable(true);
    G38_move = true;
    G38_endstop_hit = false;
    prepare_move_to_destination();
    stepper.synchronize();
    G38_move = false;

    endstops.hit_on_purpose();
    set_current_from_steppers_for_axis(ALL_AXES);
    SYNC_PLAN_POSITION_KINEMATIC();

    if (G38_endstop_hit) {

      G38_pass_fail = true;

      #if ENABLED(PROBE_DOUBLE_TOUCH)
        // Move away by the retract distance
        set_destination_to_current();
        LOOP_XYZ(i) destination[i] += retract_mm[i];
        endstops.enable(false);
        prepare_move_to_destination();
        stepper.synchronize();

        feedrate_mm_s /= 4;

        // Bump the target more slowly
        LOOP_XYZ(i) destination[i] -= retract_mm[i] * 2;

        endstops.enable(true);
        G38_move = true;
        prepare_move_to_destination();
        stepper.synchronize();
        G38_move = false;

        set_current_from_steppers_for_axis(ALL_AXES);
        SYNC_PLAN_POSITION_KINEMATIC();
      #endif
    }

    endstops.hit_on_purpose();
    endstops.not_homing();
    return G38_pass_fail;
  }

  /**
   * G38.2 - probe toward workpiece, stop on contact, signal error if failure
   * G38.3 - probe toward workpiece, stop on contact
   *
   * Like G28 except uses Z min probe for all axes
   */
  inline void gcode_G38(bool is_38_2) {
    // Get X Y Z E F
    gcode_get_destination();

    setup_for_endstop_or_probe_move();

    // If any axis has enough movement, do the move
    LOOP_XYZ(i)
      if (FABS(destination[i] - current_position[i]) >= G38_MINIMUM_MOVE) {
        if (!parser.seenval('F')) feedrate_mm_s = homing_feedrate(i);
        // If G38.2 fails throw an error
        if (!G38_run_probe() && is_38_2) {
          SERIAL_ERROR_START();
          SERIAL_ERRORLNPGM("Failed to reach target");
        }
        break;
      }

    clean_up_after_endstop_or_probe_move();
  }

#endif // G38_PROBE_TARGET

#if ENABLED(AUTO_BED_LEVELING_BILINEAR) || ENABLED(AUTO_BED_LEVELING_UBL) || ENABLED(MESH_BED_LEVELING)

  /**
   * G42: Move X & Y axes to mesh coordinates (I & J)
   */
  inline void gcode_G42() {
    if (IsRunning()) {
      const bool hasI = parser.seenval('I');
      const int8_t ix = hasI ? parser.value_int() : 0;
      const bool hasJ = parser.seenval('J');
      const int8_t iy = hasJ ? parser.value_int() : 0;

      if ((hasI && !WITHIN(ix, 0, GRID_MAX_POINTS_X - 1)) || (hasJ && !WITHIN(iy, 0, GRID_MAX_POINTS_Y - 1))) {
        SERIAL_ECHOLNPGM(MSG_ERR_MESH_XY);
        return;
      }

      #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
        #define _GET_MESH_X(I) bilinear_start[X_AXIS] + I * bilinear_grid_spacing[X_AXIS]
        #define _GET_MESH_Y(J) bilinear_start[Y_AXIS] + J * bilinear_grid_spacing[Y_AXIS]
      #elif ENABLED(AUTO_BED_LEVELING_UBL)
        #define _GET_MESH_X(I) ubl.mesh_index_to_xpos(I)
        #define _GET_MESH_Y(J) ubl.mesh_index_to_ypos(J)
      #elif ENABLED(MESH_BED_LEVELING)
        #define _GET_MESH_X(I) mbl.index_to_xpos[I]
        #define _GET_MESH_Y(J) mbl.index_to_ypos[J]
      #endif

      set_destination_to_current();
      if (hasI) destination[X_AXIS] = LOGICAL_X_POSITION(_GET_MESH_X(ix));
      if (hasJ) destination[Y_AXIS] = LOGICAL_Y_POSITION(_GET_MESH_Y(iy));
      if (parser.boolval('P')) {
        if (hasI) destination[X_AXIS] -= X_PROBE_OFFSET_FROM_EXTRUDER;
        if (hasJ) destination[Y_AXIS] -= Y_PROBE_OFFSET_FROM_EXTRUDER;
      }

      const float fval = parser.linearval('F');
      if (fval > 0.0) feedrate_mm_s = MMM_TO_MMS(fval);

      // SCARA kinematic has "safe" XY raw moves
      #if IS_SCARA
        prepare_uninterpolated_move_to_destination();
      #else
        prepare_move_to_destination();
      #endif
    }
  }

#endif // AUTO_BED_LEVELING_UBL

/**
 * G92: Set current position to given X Y Z E
 */
inline void gcode_G92() {
  bool didXYZ = false,
       didE = parser.seenval('E');

  if (!didE) stepper.synchronize();

  LOOP_XYZE(i) {
    if (parser.seenval(axis_codes[i])) {
      #if IS_SCARA
        current_position[i] = parser.value_axis_units((AxisEnum)i);
        if (i != E_AXIS) didXYZ = true;
      #else
        #if HAS_POSITION_SHIFT
          const float p = current_position[i];
        #endif
        const float v = parser.value_axis_units((AxisEnum)i);

        current_position[i] = v;

        if (i != E_AXIS) {
          didXYZ = true;
          #if HAS_POSITION_SHIFT
            position_shift[i] += v - p; // Offset the coordinate space
            update_software_endstops((AxisEnum)i);

            #if ENABLED(I2C_POSITION_ENCODERS)
              I2CPEM.encoders[I2CPEM.idx_from_axis((AxisEnum)i)].set_axis_offset(position_shift[i]);
            #endif

          #endif
        }
      #endif
    }
  }
  if (didXYZ)
    SYNC_PLAN_POSITION_KINEMATIC();
  else if (didE)
    sync_plan_position_e();

  report_current_position();
}

#if HAS_RESUME_CONTINUE

  /**
   * M0: Unconditional stop - Wait for user button press on LCD
   * M1: Conditional stop   - Wait for user button press on LCD
   */
  inline void gcode_M0_M1() {
    const char * const args = parser.string_arg;

    millis_t ms = 0;
    bool hasP = false, hasS = false;
    if (parser.seenval('P')) {
      ms = parser.value_millis(); // milliseconds to wait
      hasP = ms > 0;
    }
    if (parser.seenval('S')) {
      ms = parser.value_millis_from_seconds(); // seconds to wait
      hasS = ms > 0;
    }

    #if ENABLED(ULTIPANEL)

      if (!hasP && !hasS && args && *args)
        lcd_setstatus(args, true);
      else {
        LCD_MESSAGEPGM(MSG_USERWAIT);
        #if ENABLED(LCD_PROGRESS_BAR) && PROGRESS_MSG_EXPIRE > 0
          dontExpireStatus();
        #endif
      }

    #else

      if (!hasP && !hasS && args && *args) {
        SERIAL_ECHO_START();
        SERIAL_ECHOLN(args);
      }

    #endif

    KEEPALIVE_STATE(PAUSED_FOR_USER);
    wait_for_user = true;

    stepper.synchronize();
    refresh_cmd_timeout();

    if (ms > 0) {
      ms += previous_cmd_ms;  // wait until this time for a click
      while (PENDING(millis(), ms) && wait_for_user) idle();
    }
    else {
      #if ENABLED(ULTIPANEL)
        if (lcd_detected()) {
          while (wait_for_user) idle();
          IS_SD_PRINTING ? LCD_MESSAGEPGM(MSG_RESUMING) : LCD_MESSAGEPGM(WELCOME_MSG);
        }
      #else
        while (wait_for_user) idle();
      #endif
    }

    wait_for_user = false;
    KEEPALIVE_STATE(IN_HANDLER);
  }

#endif // HAS_RESUME_CONTINUE

#if ENABLED(SPINDLE_LASER_ENABLE)
  /**
   * M3: Spindle Clockwise
   * M4: Spindle Counter-clockwise
   *
   *  S0 turns off spindle.
   *
   *  If no speed PWM output is defined then M3/M4 just turns it on.
   *
   *  At least 12.8KHz (50Hz * 256) is needed for spindle PWM.
   *  Hardware PWM is required. ISRs are too slow.
   *
   * NOTE: WGM for timers 3, 4, and 5 must be either Mode 1 or Mode 5.
   *       No other settings give a PWM signal that goes from 0 to 5 volts.
   *
   *       The system automatically sets WGM to Mode 1, so no special
   *       initialization is needed.
   *
   *       WGM bits for timer 2 are automatically set by the system to
   *       Mode 1. This produces an acceptable 0 to 5 volt signal.
   *       No special initialization is needed.
   *
   * NOTE: A minimum PWM frequency of 50 Hz is needed. All prescaler
   *       factors for timers 2, 3, 4, and 5 are acceptable.
   *
   *  SPINDLE_LASER_ENABLE_PIN needs an external pullup or it may power on
   *  the spindle/laser during power-up or when connecting to the host
   *  (usually goes through a reset which sets all I/O pins to tri-state)
   *
   *  PWM duty cycle goes from 0 (off) to 255 (always on).
   */

  // Wait for spindle to come up to speed
  inline void delay_for_power_up() {
    refresh_cmd_timeout();
    while (PENDING(millis(), SPINDLE_LASER_POWERUP_DELAY + previous_cmd_ms)) idle();
  }

  // Wait for spindle to stop turning
  inline void delay_for_power_down() {
    refresh_cmd_timeout();
    while (PENDING(millis(), SPINDLE_LASER_POWERDOWN_DELAY + previous_cmd_ms + 1)) idle();
  }

  /**
   * ocr_val_mode() is used for debugging and to get the points needed to compute the RPM vs ocr_val line
   *
   * it accepts inputs of 0-255
   */

  inline void ocr_val_mode() {
    uint8_t spindle_laser_power = parser.value_byte();
    WRITE(SPINDLE_LASER_ENABLE_PIN, SPINDLE_LASER_ENABLE_INVERT); // turn spindle on (active low)
    if (SPINDLE_LASER_PWM_INVERT) spindle_laser_power = 255 - spindle_laser_power;
    analogWrite(SPINDLE_LASER_PWM_PIN, spindle_laser_power);
  }

  inline void gcode_M3_M4(bool is_M3) {

    stepper.synchronize();   // wait until previous movement commands (G0/G0/G2/G3) have completed before playing with the spindle
    #if SPINDLE_DIR_CHANGE
      const bool rotation_dir = (is_M3 && !SPINDLE_INVERT_DIR || !is_M3 && SPINDLE_INVERT_DIR) ? HIGH : LOW;
      if (SPINDLE_STOP_ON_DIR_CHANGE \
         && READ(SPINDLE_LASER_ENABLE_PIN) == SPINDLE_LASER_ENABLE_INVERT \
         && READ(SPINDLE_DIR_PIN) != rotation_dir
      ) {
        WRITE(SPINDLE_LASER_ENABLE_PIN, !SPINDLE_LASER_ENABLE_INVERT);  // turn spindle off
        delay_for_power_down();
      }
      digitalWrite(SPINDLE_DIR_PIN, rotation_dir);
    #endif

    /**
     * Our final value for ocr_val is an unsigned 8 bit value between 0 and 255 which usually means uint8_t.
     * Went to uint16_t because some of the uint8_t calculations would sometimes give 1000 0000 rather than 1111 1111.
     * Then needed to AND the uint16_t result with 0x00FF to make sure we only wrote the byte of interest.
     */
    #if ENABLED(SPINDLE_LASER_PWM)
      if (parser.seen('O')) ocr_val_mode();
      else {
        const float spindle_laser_power = parser.floatval('S');
        //fanSpeeds[1]= spindle_laser_power;
        if (spindle_laser_power == 0) {
          WRITE(SPINDLE_LASER_ENABLE_PIN, !SPINDLE_LASER_ENABLE_INVERT);                                    // turn spindle off (active low)
          delay_for_power_down();
        }
        else {
          int16_t ocr_val = (spindle_laser_power - (SPEED_POWER_INTERCEPT)) * (1.0 / (SPEED_POWER_SLOPE));  // convert RPM to PWM duty cycle
          NOMORE(ocr_val, 255);                                                                             // limit to max the Atmel PWM will support
          if (spindle_laser_power <= SPEED_POWER_MIN)
            ocr_val = (SPEED_POWER_MIN - (SPEED_POWER_INTERCEPT)) * (1.0 / (SPEED_POWER_SLOPE));            // minimum setting
          if (spindle_laser_power >= SPEED_POWER_MAX)
            ocr_val = (SPEED_POWER_MAX - (SPEED_POWER_INTERCEPT)) * (1.0 / (SPEED_POWER_SLOPE));            // limit to max RPM
          if (SPINDLE_LASER_PWM_INVERT) ocr_val = 255 - ocr_val;
          WRITE(SPINDLE_LASER_ENABLE_PIN, SPINDLE_LASER_ENABLE_INVERT);                                     // turn spindle on (active low)
         
          analogWrite(SPINDLE_LASER_PWM_PIN, ocr_val & 0xFF);                                               // only write low byte
          fanSpeeds[1]= ocr_val & 0xFF;
          delay_for_power_up();
        }
      }
    #else
      WRITE(SPINDLE_LASER_ENABLE_PIN, SPINDLE_LASER_ENABLE_INVERT); // turn spindle on (active low) if spindle speed option not enabled
      delay_for_power_up();
    #endif
  }

 /**
  * M5 turn off spindle
  */
  inline void gcode_M5() {
    stepper.synchronize();
    WRITE(SPINDLE_LASER_ENABLE_PIN, !SPINDLE_LASER_ENABLE_INVERT);
    fanSpeeds[1]=0;
    delay_for_power_down();
  }

#endif // SPINDLE_LASER_ENABLE

/**
 * M17: Enable power on all stepper motors
 */
inline void gcode_M17() {
  LCD_MESSAGEPGM(MSG_NO_MOVE);
  enable_all_steppers();
}

#if IS_KINEMATIC
  #define RUNPLAN(RATE_MM_S) planner.buffer_line_kinematic(destination, RATE_MM_S, active_extruder)
#else
  #define RUNPLAN(RATE_MM_S) line_to_destination(RATE_MM_S)
#endif

#if ENABLED(ADVANCED_PAUSE_FEATURE)

  static float resume_position[XYZE];
  static bool move_away_flag = false;
  #if ENABLED(SDSUPPORT)
    static bool sd_print_paused = false;
  #endif

  static void filament_change_beep(const int8_t max_beep_count, const bool init=false) {
    static millis_t next_buzz = 0;
    static int8_t runout_beep = 0;

    if (init) next_buzz = runout_beep = 0;

    const millis_t ms = millis();
    if (ELAPSED(ms, next_buzz)) {
      if (max_beep_count < 0 || runout_beep < max_beep_count + 5) { // Only beep as long as we're supposed to
        next_buzz = ms + ((max_beep_count < 0 || runout_beep < max_beep_count) ? 2500 : 400);
        BUZZ(300, 2000);
        runout_beep++;
      }
    }
  }

  static void ensure_safe_temperature() {
    bool heaters_heating = true;

    wait_for_heatup = true;    // M108 will clear this
    while (wait_for_heatup && heaters_heating) {
      idle();
      heaters_heating = false;
      HOTEND_LOOP() {
        if (thermalManager.degTargetHotend(e) && abs(thermalManager.degHotend(e) - thermalManager.degTargetHotend(e)) > TEMP_HYSTERESIS) {
          heaters_heating = true;
          #if ENABLED(ULTIPANEL)
            lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_WAIT_FOR_NOZZLES_TO_HEAT);
          #endif
          break;
        }
      }
    }
  }

  static bool pause_print(const float &retract, const float &z_lift, const float &x_pos, const float &y_pos,
                          const float &unload_length = 0 , const int8_t max_beep_count = 0, const bool show_lcd = false
  ) {
    if (move_away_flag) return false; // already paused

    if (!DEBUGGING(DRYRUN) && (unload_length != 0 || retract != 0)) {
      #if ENABLED(PREVENT_COLD_EXTRUSION)
        if (!thermalManager.allow_cold_extrude &&
            thermalManager.degTargetHotend(active_extruder) < thermalManager.extrude_min_temp) {
          SERIAL_ERROR_START();
          SERIAL_ERRORLNPGM(MSG_TOO_COLD_FOR_M600);
          return false;
        }
      #endif

      ensure_safe_temperature(); // wait for extruder to heat up before unloading
    }

    // Indicate that the printer is paused
    move_away_flag = true;

    // Pause the print job and timer
    #if ENABLED(SDSUPPORT)
      if (card.sdprinting) {
        card.pauseSDPrint();
        sd_print_paused = true;
      }
    #endif
    print_job_timer.pause();

    // Show initial message and wait for synchronize steppers
    if (show_lcd) {
      #if ENABLED(ULTIPANEL)
        lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_INIT);
      #endif
    }
    stepper.synchronize();

    // Save current position
    COPY(resume_position, current_position);
    set_destination_to_current();

    if (retract) {
      // Initial retract before move to filament change position
      destination[E_AXIS] += retract;
      RUNPLAN(PAUSE_PARK_RETRACT_FEEDRATE);
    }

    // Lift Z axis
    if (z_lift > 0) {
      destination[Z_AXIS] += z_lift;
      NOMORE(destination[Z_AXIS], Z_MAX_POS);
      RUNPLAN(PAUSE_PARK_Z_FEEDRATE);
    }

    // Move XY axes to filament exchange position
    destination[X_AXIS] = x_pos;
    destination[Y_AXIS] = y_pos;

    clamp_to_software_endstops(destination);
    RUNPLAN(PAUSE_PARK_XY_FEEDRATE);
    stepper.synchronize();

    if (unload_length != 0) {
      if (show_lcd) {
        #if ENABLED(ULTIPANEL)
          lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_UNLOAD);
          idle();
        #endif
      }

      // Unload filament
      destination[E_AXIS] += unload_length;
      RUNPLAN(FILAMENT_CHANGE_UNLOAD_FEEDRATE);
      stepper.synchronize();
    }

    if (show_lcd) {
      #if ENABLED(ULTIPANEL)
        lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_INSERT);
      #endif
    }

    #if HAS_BUZZER
      filament_change_beep(max_beep_count, true);
    #endif

    idle();

    // Disable extruders steppers for manual filament changing (only on boards that have separate ENABLE_PINS)
    #if E0_ENABLE_PIN != X_ENABLE_PIN && E1_ENABLE_PIN != Y_ENABLE_PIN
      disable_e_steppers();
      safe_delay(100);
    #endif

    // Start the heater idle timers
    const millis_t nozzle_timeout = (millis_t)(PAUSE_PARK_NOZZLE_TIMEOUT) * 1000UL;

    HOTEND_LOOP()
      thermalManager.start_heater_idle_timer(e, nozzle_timeout);

    return true;
  }

  static void wait_for_filament_reload(const int8_t max_beep_count = 0) {
    bool nozzle_timed_out = false;

    // Wait for filament insert by user and press button
    KEEPALIVE_STATE(PAUSED_FOR_USER);
    wait_for_user = true;    // LCD click or M108 will clear this
    while (wait_for_user) {
      #if HAS_BUZZER
        filament_change_beep(max_beep_count);
      #endif

      // If the nozzle has timed out, wait for the user to press the button to re-heat the nozzle, then
      // re-heat the nozzle, re-show the insert screen, restart the idle timers, and start over
      if (!nozzle_timed_out)
        HOTEND_LOOP()
          nozzle_timed_out |= thermalManager.is_heater_idle(e);

      if (nozzle_timed_out) {
        #if ENABLED(ULTIPANEL)
          lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_CLICK_TO_HEAT_NOZZLE);
        #endif

        // Wait for LCD click or M108
        while (wait_for_user) idle(true);

        // Re-enable the heaters if they timed out
        HOTEND_LOOP() thermalManager.reset_heater_idle_timer(e);

        // Wait for the heaters to reach the target temperatures
        ensure_safe_temperature();

        #if ENABLED(ULTIPANEL)
          lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_INSERT);
        #endif

        // Start the heater idle timers
        const millis_t nozzle_timeout = (millis_t)(PAUSE_PARK_NOZZLE_TIMEOUT) * 1000UL;

        HOTEND_LOOP()
          thermalManager.start_heater_idle_timer(e, nozzle_timeout);

        wait_for_user = true; /* Wait for user to load filament */
        nozzle_timed_out = false;

        #if HAS_BUZZER
          filament_change_beep(max_beep_count, true);
        #endif
      }

      idle(true);
    }
    KEEPALIVE_STATE(IN_HANDLER);
  }

  static void resume_print(const float &load_length = 0, const float &initial_extrude_length = 0, const int8_t max_beep_count = 0) {
    bool nozzle_timed_out = false;

    if (!move_away_flag) return;

    // Re-enable the heaters if they timed out
    HOTEND_LOOP() {
      nozzle_timed_out |= thermalManager.is_heater_idle(e);
      thermalManager.reset_heater_idle_timer(e);
    }

    if (nozzle_timed_out) ensure_safe_temperature();

    #if HAS_BUZZER
      filament_change_beep(max_beep_count, true);
    #endif

    if (load_length != 0) {
      #if ENABLED(ULTIPANEL)
        // Show "insert filament"
        if (nozzle_timed_out)
          lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_INSERT);
      #endif

      KEEPALIVE_STATE(PAUSED_FOR_USER);
      wait_for_user = true;    // LCD click or M108 will clear this
      while (wait_for_user && nozzle_timed_out) {
        #if HAS_BUZZER
          filament_change_beep(max_beep_count);
        #endif
        idle(true);
      }
      KEEPALIVE_STATE(IN_HANDLER);

      #if ENABLED(ULTIPANEL)
        // Show "load" message
        lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_LOAD);
      #endif

      // Load filament
      destination[E_AXIS] += load_length;

      RUNPLAN(FILAMENT_CHANGE_LOAD_FEEDRATE);
      stepper.synchronize();
    }

    #if ENABLED(ULTIPANEL) && ADVANCED_PAUSE_EXTRUDE_LENGTH > 0

      float extrude_length = initial_extrude_length;

      do {
        if (extrude_length > 0) {
          // "Wait for filament extrude"
          lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_EXTRUDE);

          // Extrude filament to get into hotend
          destination[E_AXIS] += extrude_length;
          RUNPLAN(ADVANCED_PAUSE_EXTRUDE_FEEDRATE);
          stepper.synchronize();
        }

        // Show "Extrude More" / "Resume" menu and wait for reply
        KEEPALIVE_STATE(PAUSED_FOR_USER);
        wait_for_user = false;
        lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_OPTION);
        while (advanced_pause_menu_response == ADVANCED_PAUSE_RESPONSE_WAIT_FOR) idle(true);
        KEEPALIVE_STATE(IN_HANDLER);

        extrude_length = ADVANCED_PAUSE_EXTRUDE_LENGTH;

        // Keep looping if "Extrude More" was selected
      } while (advanced_pause_menu_response == ADVANCED_PAUSE_RESPONSE_EXTRUDE_MORE);

    #endif

    #if ENABLED(ULTIPANEL)
      // "Wait for print to resume"
      lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_RESUME);
    #endif

    // Set extruder to saved position
    destination[E_AXIS] = current_position[E_AXIS] = resume_position[E_AXIS];
    planner.set_e_position_mm(current_position[E_AXIS]);

    #if IS_KINEMATIC
      // Move XYZ to starting position
      planner.buffer_line_kinematic(resume_position, PAUSE_PARK_XY_FEEDRATE, active_extruder);
    #else
      // Move XY to starting position, then Z
      destination[X_AXIS] = resume_position[X_AXIS];
      destination[Y_AXIS] = resume_position[Y_AXIS];
      RUNPLAN(PAUSE_PARK_XY_FEEDRATE);
      destination[Z_AXIS] = resume_position[Z_AXIS];
      RUNPLAN(PAUSE_PARK_Z_FEEDRATE);
    #endif
    stepper.synchronize();

    #if ENABLED(FILAMENT_RUNOUT_SENSOR)
      filament_ran_out = false;
    #endif

    #if ENABLED(ULTIPANEL)
      // Show status screen
      lcd_advanced_pause_show_message(ADVANCED_PAUSE_MESSAGE_STATUS);
    #endif

    #if ENABLED(SDSUPPORT)
      if (sd_print_paused) {
        card.startFileprint();
        sd_print_paused = false;
      }
    #endif

    move_away_flag = false;
  }
#endif // ADVANCED_PAUSE_FEATURE

#if ENABLED(SDSUPPORT)

  /**
   * M20: List SD card to serial output
   */
  inline void gcode_M20() {
    SERIAL_PROTOCOLLNPGM(MSG_BEGIN_FILE_LIST);
    card.ls();
    SERIAL_PROTOCOLLNPGM(MSG_END_FILE_LIST);
  }

  /**
   * M21: Init SD Card
   */
  inline void gcode_M21() { card.initsd(); }

  /**
   * M22: Release SD Card
   */
  inline void gcode_M22() { card.release(); }

  /**
   * M23: Open a file
   */
  inline void gcode_M23() { card.openFile(parser.string_arg, true); }

  /**
   * M24: Start or Resume SD Print
   */
  inline void gcode_M24() {
    #if ENABLED(PARK_HEAD_ON_PAUSE)
      resume_print();
    #endif

    card.startFileprint();
    print_job_timer.start();
  }

  /**
   * M25: Pause SD Print
   */
  inline void gcode_M25() {
    card.pauseSDPrint();
    print_job_timer.pause();

    #if ENABLED(PARK_HEAD_ON_PAUSE)
      enqueue_and_echo_commands_P(PSTR("M125")); // Must be enqueued with pauseSDPrint set to be last in the buffer
    #endif
  }

  /**
   * M26: Set SD Card file index
   */
  inline void gcode_M26() {
    if (card.cardOK && parser.seenval('S'))
      card.setIndex(parser.value_long());
  }

  /**
   * M27: Get SD Card status
   */
  inline void gcode_M27() { card.getStatus(); }

  /**
   * M28: Start SD Write
   */
  inline void gcode_M28() { card.openFile(parser.string_arg, false); }

  /**
   * M29: Stop SD Write
   * Processed in write to file routine above
   */
  inline void gcode_M29() {
    // card.saving = false;
  }

  /**
   * M30 <filename>: Delete SD Card file
   */
  inline void gcode_M30() {
    if (card.cardOK) {
      card.closefile();
      card.removeFile(parser.string_arg);
    }
  }

#endif // SDSUPPORT

/**
 * M31: Get the time since the start of SD Print (or last M109)
 */
inline void gcode_M31() {
  char buffer[21];
  duration_t elapsed = print_job_timer.duration();
  elapsed.toString(buffer);
  lcd_setstatus(buffer);

  SERIAL_ECHO_START();
  SERIAL_ECHOLNPAIR("Print time: ", buffer);
}

#if ENABLED(SDSUPPORT)

  /**
   * M32: Select file and start SD Print
   */
  inline void gcode_M32() {
    if (card.sdprinting)
      stepper.synchronize();

    char* namestartpos = parser.string_arg;
    const bool call_procedure = parser.boolval('P');

    if (card.cardOK) {
      card.openFile(namestartpos, true, call_procedure);

      if (parser.seenval('S'))
        card.setIndex(parser.value_long());

      card.startFileprint();

      // Procedure calls count as normal print time.
      if (!call_procedure) print_job_timer.start();
    }
  }

  #if ENABLED(LONG_FILENAME_HOST_SUPPORT)

    /**
     * M33: Get the long full path of a file or folder
     *
     * Parameters:
     *   <dospath> Case-insensitive DOS-style path to a file or folder
     *
     * Example:
     *   M33 miscel~1/armchair/armcha~1.gco
     *
     * Output:
     *   /Miscellaneous/Armchair/Armchair.gcode
     */
    inline void gcode_M33() {
      card.printLongPath(parser.string_arg);
    }

  #endif

  #if ENABLED(SDCARD_SORT_ALPHA) && ENABLED(SDSORT_GCODE)
    /**
     * M34: Set SD Card Sorting Options
     */
    inline void gcode_M34() {
      if (parser.seen('S')) card.setSortOn(parser.value_bool());
      if (parser.seenval('F')) {
        const int v = parser.value_long();
        card.setSortFolders(v < 0 ? -1 : v > 0 ? 1 : 0);
      }
      //if (parser.seen('R')) card.setSortReverse(parser.value_bool());
    }
  #endif // SDCARD_SORT_ALPHA && SDSORT_GCODE

  /**
   * M928: Start SD Write
   */
  inline void gcode_M928() {
    card.openLogFile(parser.string_arg);
  }

#endif // SDSUPPORT

/**
 * Sensitive pin test for M42, M226
 */
static bool pin_is_protected(const int8_t pin) {
  static const int8_t sensitive_pins[] PROGMEM = SENSITIVE_PINS;
  for (uint8_t i = 0; i < COUNT(sensitive_pins); i++)
    if (pin == (int8_t)pgm_read_byte(&sensitive_pins[i])) return true;
  return false;
}

/**
 * M42: Change pin status via GCode
 *
 *  P<pin>  Pin number (LED if omitted)
 *  S<byte> Pin status from 0 - 255
 */
inline void gcode_M42() {
  if (!parser.seenval('S')) return;
  const byte pin_status = parser.value_byte();

  const int pin_number = parser.intval('P', LED_PIN);
  if (pin_number < 0) return;

  if (pin_is_protected(pin_number)) {
    SERIAL_ERROR_START();
    SERIAL_ERRORLNPGM(MSG_ERR_PROTECTED_PIN);
    return;
  }

  pinMode(pin_number, OUTPUT);
  digitalWrite(pin_number, pin_status);
  analogWrite(pin_number, pin_status);

  #if FAN_COUNT > 0
    switch (pin_number) {
      #if HAS_FAN0
        case FAN_PIN: fanSpeeds[0] = pin_status; break;
      #endif
      #if HAS_FAN1
        case FAN1_PIN: fanSpeeds[1] = pin_status; break;
      #endif
      #if HAS_FAN2
        case FAN2_PIN: fanSpeeds[2] = pin_status; break;
      #endif
    }
  #endif
}

#if ENABLED(PINS_DEBUGGING)

  #include "pinsDebug.h"

  inline void toggle_pins() {
    const bool I_flag = parser.boolval('I');
    const int repeat = parser.intval('R', 1),
              start = parser.intval('S'),
              end = parser.intval('E', NUM_DIGITAL_PINS - 1),
              wait = parser.intval('W', 500);

    for (uint8_t pin = start; pin <= end; pin++) {
      //report_pin_state_extended(pin, I_flag, false);

      if (!I_flag && pin_is_protected(pin)) {
        report_pin_state_extended(pin, I_flag, true, "Untouched ");
        SERIAL_EOL();
      }
      else {
        report_pin_state_extended(pin, I_flag, true, "Pulsing   ");
        #if AVR_AT90USB1286_FAMILY // Teensy IDEs don't know about these pins so must use FASTIO
          if (pin == 46) {
            SET_OUTPUT(46);
            for (int16_t j = 0; j < repeat; j++) {
              WRITE(46, 0); safe_delay(wait);
              WRITE(46, 1); safe_delay(wait);
              WRITE(46, 0); safe_delay(wait);
            }
          }
          else if (pin == 47) {
            SET_OUTPUT(47);
            for (int16_t j = 0; j < repeat; j++) {
              WRITE(47, 0); safe_delay(wait);
              WRITE(47, 1); safe_delay(wait);
              WRITE(47, 0); safe_delay(wait);
            }
          }
          else
        #endif
        {
          pinMode(pin, OUTPUT);
          for (int16_t j = 0; j < repeat; j++) {
            digitalWrite(pin, 0); safe_delay(wait);
            digitalWrite(pin, 1); safe_delay(wait);
            digitalWrite(pin, 0); safe_delay(wait);
          }
        }

      }
      SERIAL_EOL();
    }
    SERIAL_ECHOLNPGM("Done.");

  } // toggle_pins

  inline void servo_probe_test() {
    #if !(NUM_SERVOS > 0 && HAS_SERVO_0)

      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM("SERVO not setup");

    #elif !HAS_Z_SERVO_ENDSTOP

      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM("Z_ENDSTOP_SERVO_NR not setup");

    #else

      const uint8_t probe_index = parser.byteval('P', Z_ENDSTOP_SERVO_NR);

      SERIAL_PROTOCOLLNPGM("Servo probe test");
      SERIAL_PROTOCOLLNPAIR(".  using index:  ", probe_index);
      SERIAL_PROTOCOLLNPAIR(".  deploy angle: ", z_servo_angle[0]);
      SERIAL_PROTOCOLLNPAIR(".  stow angle:   ", z_servo_angle[1]);

      bool probe_inverting;

      #if ENABLED(Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN)

        #define PROBE_TEST_PIN Z_MIN_PIN

        SERIAL_PROTOCOLLNPAIR(". probe uses Z_MIN pin: ", PROBE_TEST_PIN);
        SERIAL_PROTOCOLLNPGM(". uses Z_MIN_ENDSTOP_INVERTING (ignores Z_MIN_PROBE_ENDSTOP_INVERTING)");
        SERIAL_PROTOCOLPGM(". Z_MIN_ENDSTOP_INVERTING: ");

        #if Z_MIN_ENDSTOP_INVERTING
          SERIAL_PROTOCOLLNPGM("true");
        #else
          SERIAL_PROTOCOLLNPGM("false");
        #endif

        probe_inverting = Z_MIN_ENDSTOP_INVERTING;

      #elif ENABLED(Z_MIN_PROBE_ENDSTOP)

        #define PROBE_TEST_PIN Z_MIN_PROBE_PIN
        SERIAL_PROTOCOLLNPAIR(". probe uses Z_MIN_PROBE_PIN: ", PROBE_TEST_PIN);
        SERIAL_PROTOCOLLNPGM(". uses Z_MIN_PROBE_ENDSTOP_INVERTING (ignores Z_MIN_ENDSTOP_INVERTING)");
        SERIAL_PROTOCOLPGM(". Z_MIN_PROBE_ENDSTOP_INVERTING: ");

        #if Z_MIN_PROBE_ENDSTOP_INVERTING
          SERIAL_PROTOCOLLNPGM("true");
        #else
          SERIAL_PROTOCOLLNPGM("false");
        #endif

        probe_inverting = Z_MIN_PROBE_ENDSTOP_INVERTING;

      #endif

      SERIAL_PROTOCOLLNPGM(". deploy & stow 4 times");
      SET_INPUT_PULLUP(PROBE_TEST_PIN);
      bool deploy_state, stow_state;
      for (uint8_t i = 0; i < 4; i++) {
        servo[probe_index].move(z_servo_angle[0]); //deploy
        safe_delay(500);
        deploy_state = digitalRead(PROBE_TEST_PIN);
        servo[probe_index].move(z_servo_angle[1]); //stow
        safe_delay(500);
        stow_state = digitalRead(PROBE_TEST_PIN);
      }
      if (probe_inverting != deploy_state) SERIAL_PROTOCOLLNPGM("WARNING - INVERTING setting probably backwards");

      refresh_cmd_timeout();

      if (deploy_state != stow_state) {
        SERIAL_PROTOCOLLNPGM("BLTouch clone detected");
        if (deploy_state) {
          SERIAL_PROTOCOLLNPGM(".  DEPLOYED state: HIGH (logic 1)");
          SERIAL_PROTOCOLLNPGM(".  STOWED (triggered) state: LOW (logic 0)");
        }
        else {
          SERIAL_PROTOCOLLNPGM(".  DEPLOYED state: LOW (logic 0)");
          SERIAL_PROTOCOLLNPGM(".  STOWED (triggered) state: HIGH (logic 1)");
        }
        #if ENABLED(BLTOUCH)
          SERIAL_PROTOCOLLNPGM("ERROR: BLTOUCH enabled - set this device up as a Z Servo Probe with inverting as true.");
        #endif

      }
      else {                                           // measure active signal length
        servo[probe_index].move(z_servo_angle[0]);     // deploy
        safe_delay(500);
        SERIAL_PROTOCOLLNPGM("please trigger probe");
        uint16_t probe_counter = 0;

        // Allow 30 seconds max for operator to trigger probe
        for (uint16_t j = 0; j < 500 * 30 && probe_counter == 0 ; j++) {

          safe_delay(2);

          if (0 == j % (500 * 1)) // keep cmd_timeout happy
            refresh_cmd_timeout();

          if (deploy_state != digitalRead(PROBE_TEST_PIN)) { // probe triggered

            for (probe_counter = 1; probe_counter < 50 && deploy_state != digitalRead(PROBE_TEST_PIN); ++probe_counter)
              safe_delay(2);

            if (probe_counter == 50)
              SERIAL_PROTOCOLLNPGM("Z Servo Probe detected"); // >= 100mS active time
            else if (probe_counter >= 2)
              SERIAL_PROTOCOLLNPAIR("BLTouch compatible probe detected - pulse width (+/- 4mS): ", probe_counter * 2); // allow 4 - 100mS pulse
            else
              SERIAL_PROTOCOLLNPGM("noise detected - please re-run test"); // less than 2mS pulse

            servo[probe_index].move(z_servo_angle[1]); //stow

          }  // pulse detected

        } // for loop waiting for trigger

        if (probe_counter == 0) SERIAL_PROTOCOLLNPGM("trigger not detected");

      } // measure active signal length

    #endif

  } // servo_probe_test

  /**
   * M43: Pin debug - report pin state, watch pins, toggle pins and servo probe test/report
   *
   *  M43         - report name and state of pin(s)
   *                  P<pin>  Pin to read or watch. If omitted, reads all pins.
   *                  I       Flag to ignore Marlin's pin protection.
   *
   *  M43 W       - Watch pins -reporting changes- until reset, click, or M108.
   *                  P<pin>  Pin to read or watch. If omitted, read/watch all pins.
   *                  I       Flag to ignore Marlin's pin protection.
   *
   *  M43 E<bool> - Enable / disable background endstop monitoring
   *                  - Machine continues to operate
   *                  - Reports changes to endstops
   *                  - Toggles LED_PIN when an endstop changes
   *                  - Can not reliably catch the 5mS pulse from BLTouch type probes
   *
   *  M43 T       - Toggle pin(s) and report which pin is being toggled
   *                  S<pin>  - Start Pin number.   If not given, will default to 0
   *                  L<pin>  - End Pin number.   If not given, will default to last pin defined for this board
   *                  I<bool> - Flag to ignore Marlin's pin protection.   Use with caution!!!!
   *                  R       - Repeat pulses on each pin this number of times before continueing to next pin
   *                  W       - Wait time (in miliseconds) between pulses.  If not given will default to 500
   *
   *  M43 S       - Servo probe test
   *                  P<index> - Probe index (optional - defaults to 0
   */
  inline void gcode_M43() {

    if (parser.seen('T')) {   // must be first or else its "S" and "E" parameters will execute endstop or servo test
      toggle_pins();
      return;
    }

    // Enable or disable endstop monitoring
    if (parser.seen('E')) {
      endstop_monitor_flag = parser.value_bool();
      SERIAL_PROTOCOLPGM("endstop monitor ");
      SERIAL_PROTOCOL(endstop_monitor_flag ? "en" : "dis");
      SERIAL_PROTOCOLLNPGM("abled");
      return;
    }

    if (parser.seen('S')) {
      servo_probe_test();
      return;
    }

    // Get the range of pins to test or watch
    const uint8_t first_pin = parser.byteval('P'),
                  last_pin = parser.seenval('P') ? first_pin : NUM_DIGITAL_PINS - 1;

    if (first_pin > last_pin) return;

    const bool ignore_protection = parser.boolval('I');

    // Watch until click, M108, or reset
    if (parser.boolval('W')) {
      SERIAL_PROTOCOLLNPGM("Watching pins");
      byte pin_state[last_pin - first_pin + 1];
      for (int8_t pin = first_pin; pin <= last_pin; pin++) {
        if (pin_is_protected(pin) && !ignore_protection) continue;
        pinMode(pin, INPUT_PULLUP);
        delay(1);
        /*
          if (IS_ANALOG(pin))
            pin_state[pin - first_pin] = analogRead(pin - analogInputToDigitalPin(0)); // int16_t pin_state[...]
          else
        //*/
            pin_state[pin - first_pin] = digitalRead(pin);
      }

      #if HAS_RESUME_CONTINUE
        wait_for_user = true;
        KEEPALIVE_STATE(PAUSED_FOR_USER);
      #endif

      for (;;) {
        for (int8_t pin = first_pin; pin <= last_pin; pin++) {
          if (pin_is_protected(pin) && !ignore_protection) continue;
          const byte val =
            /*
              IS_ANALOG(pin)
                ? analogRead(pin - analogInputToDigitalPin(0)) : // int16_t val
                :
            //*/
              digitalRead(pin);
          if (val != pin_state[pin - first_pin]) {
            report_pin_state_extended(pin, ignore_protection, false);
            pin_state[pin - first_pin] = val;
          }
        }

        #if HAS_RESUME_CONTINUE
          if (!wait_for_user) {
            KEEPALIVE_STATE(IN_HANDLER);
            break;
          }
        #endif

        safe_delay(200);
      }
      return;
    }

    // Report current state of selected pin(s)
    for (uint8_t pin = first_pin; pin <= last_pin; pin++)
      report_pin_state_extended(pin, ignore_protection, true);
  }

#endif // PINS_DEBUGGING

#if ENABLED(Z_MIN_PROBE_REPEATABILITY_TEST)

  /**
   * M48: Z probe repeatability measurement function.
   *
   * Usage:
   *   M48 <P#> <X#> <Y#> <V#> <E> <L#>
   *     P = Number of sampled points (4-50, default 10)
   *     X = Sample X position
   *     Y = Sample Y position
   *     V = Verbose level (0-4, default=1)
   *     E = Engage Z probe for each reading
   *     L = Number of legs of movement before probe
   *     S = Schizoid (Or Star if you prefer)
   *
   * This function assumes the bed has been homed.  Specifically, that a G28 command
   * as been issued prior to invoking the M48 Z probe repeatability measurement function.
   * Any information generated by a prior G29 Bed leveling command will be lost and need to be
   * regenerated.
   */
  inline void gcode_M48() {

    if (axis_unhomed_error()) return;

    const int8_t verbose_level = parser.byteval('V', 1);
    if (!WITHIN(verbose_level, 0, 4)) {
      SERIAL_PROTOCOLLNPGM("?(V)erbose level is implausible (0-4).");
      return;
    }

    if (verbose_level > 0)
      SERIAL_PROTOCOLLNPGM("M48 Z-Probe Repeatability Test");

    const int8_t n_samples = parser.byteval('P', 10);
    if (!WITHIN(n_samples, 4, 50)) {
      SERIAL_PROTOCOLLNPGM("?Sample size not plausible (4-50).");
      return;
    }

    const bool stow_probe_after_each = parser.boolval('E');

    float X_current = current_position[X_AXIS],
          Y_current = current_position[Y_AXIS];

    const float X_probe_location = parser.linearval('X', X_current + X_PROBE_OFFSET_FROM_EXTRUDER),
                Y_probe_location = parser.linearval('Y', Y_current + Y_PROBE_OFFSET_FROM_EXTRUDER);

    #if DISABLED(DELTA)
      if (!WITHIN(X_probe_location, LOGICAL_X_POSITION(MIN_PROBE_X), LOGICAL_X_POSITION(MAX_PROBE_X))) {
        out_of_range_error(PSTR("X"));
        return;
      }
      if (!WITHIN(Y_probe_location, LOGICAL_Y_POSITION(MIN_PROBE_Y), LOGICAL_Y_POSITION(MAX_PROBE_Y))) {
        out_of_range_error(PSTR("Y"));
        return;
      }
    #else
      if (!position_is_reachable_by_probe_xy(X_probe_location, Y_probe_location)) {
        SERIAL_PROTOCOLLNPGM("? (X,Y) location outside of probeable radius.");
        return;
      }
    #endif

    bool seen_L = parser.seen('L');
    uint8_t n_legs = seen_L ? parser.value_byte() : 0;
    if (n_legs > 15) {
      SERIAL_PROTOCOLLNPGM("?Number of legs in movement not plausible (0-15).");
      return;
    }
    if (n_legs == 1) n_legs = 2;

    const bool schizoid_flag = parser.boolval('S');
    if (schizoid_flag && !seen_L) n_legs = 7;

    /**
     * Now get everything to the specified probe point So we can safely do a
     * probe to get us close to the bed.  If the Z-Axis is far from the bed,
     * we don't want to use that as a starting point for each probe.
     */
    if (verbose_level > 2)
      SERIAL_PROTOCOLLNPGM("Positioning the probe...");

    // Disable bed level correction in M48 because we want the raw data when we probe

    #if HAS_LEVELING
      const bool was_enabled = leveling_is_active();
      set_bed_leveling_enabled(false);
    #endif

    setup_for_endstop_or_probe_move();

    // Move to the first point, deploy, and probe
    const float t = probe_pt(X_probe_location, Y_probe_location, stow_probe_after_each, verbose_level);
    if (isnan(t)) return;

    randomSeed(millis());

    double mean = 0.0, sigma = 0.0, min = 99999.9, max = -99999.9, sample_set[n_samples];

    for (uint8_t n = 0; n < n_samples; n++) {
      if (n_legs) {
        int dir = (random(0, 10) > 5.0) ? -1 : 1;  // clockwise or counter clockwise
        float angle = random(0.0, 360.0),
              radius = random(
                #if ENABLED(DELTA)
                  DELTA_PROBEABLE_RADIUS / 8, DELTA_PROBEABLE_RADIUS / 3
                #else
                  5, X_MAX_LENGTH / 8
                #endif
              );

        if (verbose_level > 3) {
          SERIAL_ECHOPAIR("Starting radius: ", radius);
          SERIAL_ECHOPAIR("   angle: ", angle);
          SERIAL_ECHOPGM(" Direction: ");
          if (dir > 0) SERIAL_ECHOPGM("Counter-");
          SERIAL_ECHOLNPGM("Clockwise");
        }

        for (uint8_t l = 0; l < n_legs - 1; l++) {
          double delta_angle;

          if (schizoid_flag)
            // The points of a 5 point star are 72 degrees apart.  We need to
            // skip a point and go to the next one on the star.
            delta_angle = dir * 2.0 * 72.0;

          else
            // If we do this line, we are just trying to move further
            // around the circle.
            delta_angle = dir * (float) random(25, 45);

          angle += delta_angle;

          while (angle > 360.0)   // We probably do not need to keep the angle between 0 and 2*PI, but the
            angle -= 360.0;       // Arduino documentation says the trig functions should not be given values
          while (angle < 0.0)     // outside of this range.   It looks like they behave correctly with
            angle += 360.0;       // numbers outside of the range, but just to be safe we clamp them.

          X_current = X_probe_location - (X_PROBE_OFFSET_FROM_EXTRUDER) + cos(RADIANS(angle)) * radius;
          Y_current = Y_probe_location - (Y_PROBE_OFFSET_FROM_EXTRUDER) + sin(RADIANS(angle)) * radius;

          #if DISABLED(DELTA)
            X_current = constrain(X_current, X_MIN_POS, X_MAX_POS);
            Y_current = constrain(Y_current, Y_MIN_POS, Y_MAX_POS);
          #else
            // If we have gone out too far, we can do a simple fix and scale the numbers
            // back in closer to the origin.
            while (!position_is_reachable_by_probe_xy(X_current, Y_current)) {
              X_current *= 0.8;
              Y_current *= 0.8;
              if (verbose_level > 3) {
                SERIAL_ECHOPAIR("Pulling point towards center:", X_current);
                SERIAL_ECHOLNPAIR(", ", Y_current);
              }
            }
          #endif
          if (verbose_level > 3) {
            SERIAL_PROTOCOLPGM("Going to:");
            SERIAL_ECHOPAIR(" X", X_current);
            SERIAL_ECHOPAIR(" Y", Y_current);
            SERIAL_ECHOLNPAIR(" Z", current_position[Z_AXIS]);
          }
          do_blocking_move_to_xy(X_current, Y_current);
        } // n_legs loop
      } // n_legs

      // Probe a single point
      sample_set[n] = probe_pt(X_probe_location, Y_probe_location, stow_probe_after_each, 0);

      /**
       * Get the current mean for the data points we have so far
       */
      double sum = 0.0;
      for (uint8_t j = 0; j <= n; j++) sum += sample_set[j];
      mean = sum / (n + 1);

      NOMORE(min, sample_set[n]);
      NOLESS(max, sample_set[n]);

      /**
       * Now, use that mean to calculate the standard deviation for the
       * data points we have so far
       */
      sum = 0.0;
      for (uint8_t j = 0; j <= n; j++)
        sum += sq(sample_set[j] - mean);

      sigma = SQRT(sum / (n + 1));
      if (verbose_level > 0) {
        if (verbose_level > 1) {
          SERIAL_PROTOCOL(n + 1);
          SERIAL_PROTOCOLPGM(" of ");
          SERIAL_PROTOCOL((int)n_samples);
          SERIAL_PROTOCOLPGM(": z: ");
          SERIAL_PROTOCOL_F(sample_set[n], 3);
          if (verbose_level > 2) {
            SERIAL_PROTOCOLPGM(" mean: ");
            SERIAL_PROTOCOL_F(mean, 4);
            SERIAL_PROTOCOLPGM(" sigma: ");
            SERIAL_PROTOCOL_F(sigma, 6);
            SERIAL_PROTOCOLPGM(" min: ");
            SERIAL_PROTOCOL_F(min, 3);
            SERIAL_PROTOCOLPGM(" max: ");
            SERIAL_PROTOCOL_F(max, 3);
            SERIAL_PROTOCOLPGM(" range: ");
            SERIAL_PROTOCOL_F(max-min, 3);
          }
          SERIAL_EOL();
        }
      }

    } // End of probe loop

    if (STOW_PROBE()) return;

    SERIAL_PROTOCOLPGM("Finished!");
    SERIAL_EOL();

    if (verbose_level > 0) {
      SERIAL_PROTOCOLPGM("Mean: ");
      SERIAL_PROTOCOL_F(mean, 6);
      SERIAL_PROTOCOLPGM(" Min: ");
      SERIAL_PROTOCOL_F(min, 3);
      SERIAL_PROTOCOLPGM(" Max: ");
      SERIAL_PROTOCOL_F(max, 3);
      SERIAL_PROTOCOLPGM(" Range: ");
      SERIAL_PROTOCOL_F(max-min, 3);
      SERIAL_EOL();
    }

    SERIAL_PROTOCOLPGM("Standard Deviation: ");
    SERIAL_PROTOCOL_F(sigma, 6);
    SERIAL_EOL();
    SERIAL_EOL();

    clean_up_after_endstop_or_probe_move();

    // Re-enable bed level correction if it had been on
    #if HAS_LEVELING
      set_bed_leveling_enabled(was_enabled);
    #endif

    report_current_position();
  }

#endif // Z_MIN_PROBE_REPEATABILITY_TEST

#if ENABLED(AUTO_BED_LEVELING_UBL) && ENABLED(UBL_G26_MESH_VALIDATION)

  inline void gcode_M49() {
    ubl.g26_debug_flag ^= true;
    SERIAL_PROTOCOLPGM("UBL Debug Flag turned ");
    serialprintPGM(ubl.g26_debug_flag ? PSTR("on.") : PSTR("off."));
  }

#endif // AUTO_BED_LEVELING_UBL && UBL_G26_MESH_VALIDATION

/**
 * M75: Start print timer
 */
inline void gcode_M75() { print_job_timer.start(); }

/**
 * M76: Pause print timer
 */
inline void gcode_M76() { print_job_timer.pause(); }

/**
 * M77: Stop print timer
 */
inline void gcode_M77() { print_job_timer.stop(); }

#if ENABLED(PRINTCOUNTER)
  /**
   * M78: Show print statistics
   */
  inline void gcode_M78() {
    // "M78 S78" will reset the statistics
    if (parser.intval('S') == 78)
      print_job_timer.initStats();
    else
      print_job_timer.showStats();
  }
#endif

/**
 * M104: Set hot end temperature
 */
inline void gcode_M104() {
  if (get_target_extruder_from_command(104)) return;
  if (DEBUGGING(DRYRUN)) return;

  #if ENABLED(SINGLENOZZLE)
    if (target_extruder != active_extruder) return;
  #endif

  if (parser.seenval('S')) {
    const int16_t temp = parser.value_celsius();
    thermalManager.setTargetHotend(temp, target_extruder);

    #if ENABLED(DUAL_X_CARRIAGE)
      if (dual_x_carriage_mode == DXC_DUPLICATION_MODE && target_extruder == 0)
        thermalManager.setTargetHotend(temp ? temp + duplicate_extruder_temp_offset : 0, 1);
    #endif

    #if ENABLED(PRINTJOB_TIMER_AUTOSTART)
      /**
       * Stop the timer at the end of print. Start is managed by 'heat and wait' M109.
       * We use half EXTRUDE_MINTEMP here to allow nozzles to be put into hot
       * standby mode, for instance in a dual extruder setup, without affecting
       * the running print timer.
       */
      if (parser.value_celsius() <= (EXTRUDE_MINTEMP) / 2) {
        print_job_timer.stop();
        LCD_MESSAGEPGM(WELCOME_MSG);
      }
    #endif

    if (parser.value_celsius() > thermalManager.degHotend(target_extruder))
      lcd_status_printf_P(0, PSTR("E%i %s"), target_extruder + 1, MSG_HEATING);
  }

  #if ENABLED(AUTOTEMP)
    planner.autotemp_M104_M109();
  #endif
}

#if HAS_TEMP_HOTEND || HAS_TEMP_BED

  void print_heater_state(const float &c, const float &t,
    #if ENABLED(SHOW_TEMP_ADC_VALUES)
      const float r,
    #endif
    const int8_t e=-2
  ) {
    SERIAL_PROTOCOLCHAR(' ');
    SERIAL_PROTOCOLCHAR(
      #if HAS_TEMP_BED && HAS_TEMP_HOTEND
        e == -1 ? 'B' : 'T'
      #elif HAS_TEMP_HOTEND
        'T'
      #else
        'B'
      #endif
    );
    #if HOTENDS > 1
      if (e >= 0) SERIAL_PROTOCOLCHAR('0' + e);
    #endif
    SERIAL_PROTOCOLCHAR(':');
    SERIAL_PROTOCOL(c);
    SERIAL_PROTOCOLPAIR(" /" , t);
    #if ENABLED(SHOW_TEMP_ADC_VALUES)
      SERIAL_PROTOCOLPAIR(" (", r / OVERSAMPLENR);
      SERIAL_PROTOCOLCHAR(')');
    #endif
  }

  void print_heaterstates() {
    #if HAS_TEMP_HOTEND
      print_heater_state(thermalManager.degHotend(target_extruder), thermalManager.degTargetHotend(target_extruder)
        #if ENABLED(SHOW_TEMP_ADC_VALUES)
          , thermalManager.rawHotendTemp(target_extruder)
        #endif
      );
    #endif
    #if HAS_TEMP_BED
      print_heater_state(thermalManager.degBed(), thermalManager.degTargetBed(),
        #if ENABLED(SHOW_TEMP_ADC_VALUES)
          thermalManager.rawBedTemp(),
        #endif
        -1 // BED
      );
    #endif
    #if HOTENDS > 1
      HOTEND_LOOP() print_heater_state(thermalManager.degHotend(e), thermalManager.degTargetHotend(e),
        #if ENABLED(SHOW_TEMP_ADC_VALUES)
          thermalManager.rawHotendTemp(e),
        #endif
        e
      );
    #endif
    SERIAL_PROTOCOLPGM(" @:");
    SERIAL_PROTOCOL(thermalManager.getHeaterPower(target_extruder));
    #if HAS_TEMP_BED
      SERIAL_PROTOCOLPGM(" B@:");
      SERIAL_PROTOCOL(thermalManager.getHeaterPower(-1));
    #endif
    #if HOTENDS > 1
      HOTEND_LOOP() {
        SERIAL_PROTOCOLPAIR(" @", e);
        SERIAL_PROTOCOLCHAR(':');
        SERIAL_PROTOCOL(thermalManager.getHeaterPower(e));
      }
    #endif
  }
#endif

/**
 * M105: Read hot end and bed temperature
 */
inline void gcode_M105() {
  if (get_target_extruder_from_command(105)) return;

  #if HAS_TEMP_HOTEND || HAS_TEMP_BED
    SERIAL_PROTOCOLPGM(MSG_OK);
    print_heaterstates();
  #else // !HAS_TEMP_HOTEND && !HAS_TEMP_BED
    SERIAL_ERROR_START();
    SERIAL_ERRORLNPGM(MSG_ERR_NO_THERMISTORS);
  #endif

  SERIAL_EOL();
}

#if ENABLED(AUTO_REPORT_TEMPERATURES) && (HAS_TEMP_HOTEND || HAS_TEMP_BED)

  static uint8_t auto_report_temp_interval;
  static millis_t next_temp_report_ms;

  /**
   * M155: Set temperature auto-report interval. M155 S<seconds>
   */
  inline void gcode_M155() {
    if (parser.seenval('S')) {
      auto_report_temp_interval = parser.value_byte();
      NOMORE(auto_report_temp_interval, 60);
      next_temp_report_ms = millis() + 1000UL * auto_report_temp_interval;
    }
  }

  inline void auto_report_temperatures() {
    if (auto_report_temp_interval && ELAPSED(millis(), next_temp_report_ms)) {
      next_temp_report_ms = millis() + 1000UL * auto_report_temp_interval;
      print_heaterstates();
      SERIAL_EOL();
    }
  }

#endif // AUTO_REPORT_TEMPERATURES

#if FAN_COUNT > 0

  /**
   * M106: Set Fan Speed
   *
   *  S<int>   Speed between 0-255
   *  P<index> Fan index, if more than one fan
   */
  inline void gcode_M106() {
    uint16_t s = parser.ushortval('S', 255);
    NOMORE(s, 255);
   // const uint8_t p = parser.byteval('P', 0);
 //  p=0;
   // if (p < FAN_COUNT) fanSpeeds[p] = s;
   fanSpeeds[0] = s;
  }

  /**
   * M107: Fan Off
   */
  inline void gcode_M107() {
   // const uint16_t p = parser.ushortval('P');
    //if (p < FAN_COUNT) fanSpeeds[p] = 0;
    fanSpeeds[0] = 0;
  }

#endif // FAN_COUNT > 0
 inline void gcode_M7() {
    uint16_t s = parser.ushortval('S', 255);
    NOMORE(s, 255);
   // const uint8_t p = parser.byteval('P', 0);
 //  p=0;
   // if (p < FAN_COUNT) fanSpeeds[p] = s;
   fanSpeeds[1] = 255;
  }
   inline void gcode_M8() {
   // const uint16_t p = parser.ushortval('P');
    //if (p < FAN_COUNT) fanSpeeds[p] = 0;
    fanSpeeds[1] = 0;
  } 
  
#if DISABLED(EMERGENCY_PARSER)

  /**
   * M108: Stop the waiting for heaters in M109, M190, M303. Does not affect the target temperature.
   */
  inline void gcode_M108() { wait_for_heatup = false; }


  /**
   * M112: Emergency Stop
   */
  inline void gcode_M112() { kill(PSTR(MSG_KILLED)); }


  /**
   * M410: Quickstop - Abort all planned moves
   *
   * This will stop the carriages mid-move, so most likely they
   * will be out of sync with the stepper position after this.
   */
  inline void gcode_M410() { quickstop_stepper(); }

#endif

/**
 * M109: Sxxx Wait for extruder(s) to reach temperature. Waits only when heating.
 *       Rxxx Wait for extruder(s) to reach temperature. Waits when heating and cooling.
 */

#ifndef MIN_COOLING_SLOPE_DEG
  #define MIN_COOLING_SLOPE_DEG 1.50
#endif
#ifndef MIN_COOLING_SLOPE_TIME
  #define MIN_COOLING_SLOPE_TIME 60
#endif

inline void gcode_M109() {

  if (get_target_extruder_from_command(109)) return;
  if (DEBUGGING(DRYRUN)) return;

  #if ENABLED(SINGLENOZZLE)
    if (target_extruder != active_extruder) return;
  #endif

  const bool no_wait_for_cooling = parser.seenval('S');
  if (no_wait_for_cooling || parser.seenval('R')) {
    const int16_t temp = parser.value_celsius();
    thermalManager.setTargetHotend(temp, target_extruder);

    #if ENABLED(DUAL_X_CARRIAGE)
      if (dual_x_carriage_mode == DXC_DUPLICATION_MODE && target_extruder == 0)
        thermalManager.setTargetHotend(temp ? temp + duplicate_extruder_temp_offset : 0, 1);
    #endif

    #if ENABLED(PRINTJOB_TIMER_AUTOSTART)
      /**
       * Use half EXTRUDE_MINTEMP to allow nozzles to be put into hot
       * standby mode, (e.g., in a dual extruder setup) without affecting
       * the running print timer.
       */
      if (parser.value_celsius() <= (EXTRUDE_MINTEMP) / 2) {
        print_job_timer.stop();
        LCD_MESSAGEPGM(WELCOME_MSG);
      }
      else
        print_job_timer.start();
    #endif

    if (thermalManager.isHeatingHotend(target_extruder)) lcd_status_printf_P(0, PSTR("E%i %s"), target_extruder + 1, MSG_HEATING);
  }
  else return;

  #if ENABLED(AUTOTEMP)
    planner.autotemp_M104_M109();
  #endif

  #if TEMP_RESIDENCY_TIME > 0
    millis_t residency_start_ms = 0;
    // Loop until the temperature has stabilized
    #define TEMP_CONDITIONS (!residency_start_ms || PENDING(now, residency_start_ms + (TEMP_RESIDENCY_TIME) * 1000UL))
  #else
    // Loop until the temperature is very close target
    #define TEMP_CONDITIONS (wants_to_cool ? thermalManager.isCoolingHotend(target_extruder) : thermalManager.isHeatingHotend(target_extruder))
  #endif

  float target_temp = -1.0, old_temp = 9999.0;
  bool wants_to_cool = false;
  wait_for_heatup = true;
  millis_t now, next_temp_ms = 0, next_cool_check_ms = 0;

  KEEPALIVE_STATE(NOT_BUSY);

  #if ENABLED(PRINTER_EVENT_LEDS)
    const float start_temp = thermalManager.degHotend(target_extruder);
    uint8_t old_blue = 0;
  #endif

  do {
    // Target temperature might be changed during the loop
    if (target_temp != thermalManager.degTargetHotend(target_extruder)) {
      wants_to_cool = thermalManager.isCoolingHotend(target_extruder);
      target_temp = thermalManager.degTargetHotend(target_extruder);

      // Exit if S<lower>, continue if S<higher>, R<lower>, or R<higher>
      if (no_wait_for_cooling && wants_to_cool) break;
    }

    now = millis();
    if (ELAPSED(now, next_temp_ms)) { //Print temp & remaining time every 1s while waiting
      next_temp_ms = now + 1000UL;
      print_heaterstates();
      #if TEMP_RESIDENCY_TIME > 0
        SERIAL_PROTOCOLPGM(" W:");
        if (residency_start_ms)
          SERIAL_PROTOCOL(long((((TEMP_RESIDENCY_TIME) * 1000UL) - (now - residency_start_ms)) / 1000UL));
        else
          SERIAL_PROTOCOLCHAR('?');
      #endif
      SERIAL_EOL();
    }

    idle();
    refresh_cmd_timeout(); // to prevent stepper_inactive_time from running out

    const float temp = thermalManager.degHotend(target_extruder);

    #if ENABLED(PRINTER_EVENT_LEDS)
      // Gradually change LED strip from violet to red as nozzle heats up
      if (!wants_to_cool) {
        const uint8_t blue = map(constrain(temp, start_temp, target_temp), start_temp, target_temp, 255, 0);
        if (blue != old_blue) set_led_color(255, 0, (old_blue = blue));
      }
    #endif

    #if TEMP_RESIDENCY_TIME > 0

      const float temp_diff = FABS(target_temp - temp);

      if (!residency_start_ms) {
        // Start the TEMP_RESIDENCY_TIME timer when we reach target temp for the first time.
        if (temp_diff < TEMP_WINDOW) residency_start_ms = now;
      }
      else if (temp_diff > TEMP_HYSTERESIS) {
        // Restart the timer whenever the temperature falls outside the hysteresis.
        residency_start_ms = now;
      }

    #endif

    // Prevent a wait-forever situation if R is misused i.e. M109 R0
    if (wants_to_cool) {
      // break after MIN_COOLING_SLOPE_TIME seconds
      // if the temperature did not drop at least MIN_COOLING_SLOPE_DEG
      if (!next_cool_check_ms || ELAPSED(now, next_cool_check_ms)) {
        if (old_temp - temp < MIN_COOLING_SLOPE_DEG) break;
        next_cool_check_ms = now + 1000UL * MIN_COOLING_SLOPE_TIME;
        old_temp = temp;
      }
    }

  } while (wait_for_heatup && TEMP_CONDITIONS);

  if (wait_for_heatup) {
    LCD_MESSAGEPGM(MSG_HEATING_COMPLETE);
    #if ENABLED(PRINTER_EVENT_LEDS)
      #if ENABLED(RGBW_LED)
        set_led_color(0, 0, 0, 255);  // Turn on the WHITE LED
      #else
        set_led_color(255, 255, 255); // Set LEDs All On
      #endif
    #endif
  }

  KEEPALIVE_STATE(IN_HANDLER);
}

#if HAS_TEMP_BED

  #ifndef MIN_COOLING_SLOPE_DEG_BED
    #define MIN_COOLING_SLOPE_DEG_BED 1.50
  #endif
  #ifndef MIN_COOLING_SLOPE_TIME_BED
    #define MIN_COOLING_SLOPE_TIME_BED 60
  #endif

  /**
   * M190: Sxxx Wait for bed current temp to reach target temp. Waits only when heating
   *       Rxxx Wait for bed current temp to reach target temp. Waits when heating and cooling
   */
  inline void gcode_M190() {
    if (DEBUGGING(DRYRUN)) return;

    LCD_MESSAGEPGM(MSG_BED_HEATING);
    const bool no_wait_for_cooling = parser.seenval('S');
    if (no_wait_for_cooling || parser.seenval('R')) {
      thermalManager.setTargetBed(parser.value_celsius());
      #if ENABLED(PRINTJOB_TIMER_AUTOSTART)
        if (parser.value_celsius() > BED_MINTEMP)
          print_job_timer.start();
      #endif
    }
    else return;

    #if TEMP_BED_RESIDENCY_TIME > 0
      millis_t residency_start_ms = 0;
      // Loop until the temperature has stabilized
      #define TEMP_BED_CONDITIONS (!residency_start_ms || PENDING(now, residency_start_ms + (TEMP_BED_RESIDENCY_TIME) * 1000UL))
    #else
      // Loop until the temperature is very close target
      #define TEMP_BED_CONDITIONS (wants_to_cool ? thermalManager.isCoolingBed() : thermalManager.isHeatingBed())
    #endif

    float target_temp = -1.0, old_temp = 9999.0;
    bool wants_to_cool = false;
    wait_for_heatup = true;
    millis_t now, next_temp_ms = 0, next_cool_check_ms = 0;

    KEEPALIVE_STATE(NOT_BUSY);

    target_extruder = active_extruder; // for print_heaterstates

    #if ENABLED(PRINTER_EVENT_LEDS)
      const float start_temp = thermalManager.degBed();
      uint8_t old_red = 255;
    #endif

    do {
      // Target temperature might be changed during the loop
      if (target_temp != thermalManager.degTargetBed()) {
        wants_to_cool = thermalManager.isCoolingBed();
        target_temp = thermalManager.degTargetBed();

        // Exit if S<lower>, continue if S<higher>, R<lower>, or R<higher>
        if (no_wait_for_cooling && wants_to_cool) break;
      }

      now = millis();
      if (ELAPSED(now, next_temp_ms)) { //Print Temp Reading every 1 second while heating up.
        next_temp_ms = now + 1000UL;
        print_heaterstates();
        #if TEMP_BED_RESIDENCY_TIME > 0
          SERIAL_PROTOCOLPGM(" W:");
          if (residency_start_ms)
            SERIAL_PROTOCOL(long((((TEMP_BED_RESIDENCY_TIME) * 1000UL) - (now - residency_start_ms)) / 1000UL));
          else
            SERIAL_PROTOCOLCHAR('?');
        #endif
        SERIAL_EOL();
      }

      idle();
      refresh_cmd_timeout(); // to prevent stepper_inactive_time from running out

      const float temp = thermalManager.degBed();

      #if ENABLED(PRINTER_EVENT_LEDS)
        // Gradually change LED strip from blue to violet as bed heats up
        if (!wants_to_cool) {
          const uint8_t red = map(constrain(temp, start_temp, target_temp), start_temp, target_temp, 0, 255);
          if (red != old_red) set_led_color((old_red = red), 0, 255);
        }
      #endif

      #if TEMP_BED_RESIDENCY_TIME > 0

        const float temp_diff = FABS(target_temp - temp);

        if (!residency_start_ms) {
          // Start the TEMP_BED_RESIDENCY_TIME timer when we reach target temp for the first time.
          if (temp_diff < TEMP_BED_WINDOW) residency_start_ms = now;
        }
        else if (temp_diff > TEMP_BED_HYSTERESIS) {
          // Restart the timer whenever the temperature falls outside the hysteresis.
          residency_start_ms = now;
        }

      #endif // TEMP_BED_RESIDENCY_TIME > 0

      // Prevent a wait-forever situation if R is misused i.e. M190 R0
      if (wants_to_cool) {
        // Break after MIN_COOLING_SLOPE_TIME_BED seconds
        // if the temperature did not drop at least MIN_COOLING_SLOPE_DEG_BED
        if (!next_cool_check_ms || ELAPSED(now, next_cool_check_ms)) {
          if (old_temp - temp < MIN_COOLING_SLOPE_DEG_BED) break;
          next_cool_check_ms = now + 1000UL * MIN_COOLING_SLOPE_TIME_BED;
          old_temp = temp;
        }
      }

    } while (wait_for_heatup && TEMP_BED_CONDITIONS);

    if (wait_for_heatup) LCD_MESSAGEPGM(MSG_BED_DONE);
    KEEPALIVE_STATE(IN_HANDLER);
  }

#endif // HAS_TEMP_BED

/**
 * M110: Set Current Line Number
 */
inline void gcode_M110() {
  if (parser.seenval('N')) gcode_LastN = parser.value_long();
}

/**
 * M111: Set the debug level
 */
inline void gcode_M111() {
  marlin_debug_flags = parser.byteval('S', (uint8_t)DEBUG_NONE);

  const static char str_debug_1[] PROGMEM = MSG_DEBUG_ECHO;
  const static char str_debug_2[] PROGMEM = MSG_DEBUG_INFO;
  const static char str_debug_4[] PROGMEM = MSG_DEBUG_ERRORS;
  const static char str_debug_8[] PROGMEM = MSG_DEBUG_DRYRUN;
  const static char str_debug_16[] PROGMEM = MSG_DEBUG_COMMUNICATION;
  #if ENABLED(DEBUG_LEVELING_FEATURE)
    const static char str_debug_32[] PROGMEM = MSG_DEBUG_LEVELING;
  #endif

  const static char* const debug_strings[] PROGMEM = {
    str_debug_1, str_debug_2, str_debug_4, str_debug_8, str_debug_16
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      , str_debug_32
    #endif
  };

  SERIAL_ECHO_START();
  SERIAL_ECHOPGM(MSG_DEBUG_PREFIX);
  if (marlin_debug_flags) {
    uint8_t comma = 0;
    for (uint8_t i = 0; i < COUNT(debug_strings); i++) {
      if (TEST(marlin_debug_flags, i)) {
        if (comma++) SERIAL_CHAR(',');
        serialprintPGM((char*)pgm_read_word(&debug_strings[i]));
      }
    }
  }
  else {
    SERIAL_ECHOPGM(MSG_DEBUG_OFF);
  }
  SERIAL_EOL();
}

#if ENABLED(HOST_KEEPALIVE_FEATURE)

  /**
   * M113: Get or set Host Keepalive interval (0 to disable)
   *
   *   S<seconds> Optional. Set the keepalive interval.
   */
  inline void gcode_M113() {
    if (parser.seenval('S')) {
      host_keepalive_interval = parser.value_byte();
      NOMORE(host_keepalive_interval, 60);
    }
    else {
      SERIAL_ECHO_START();
      SERIAL_ECHOLNPAIR("M113 S", (unsigned long)host_keepalive_interval);
    }
  }

#endif

#if ENABLED(BARICUDA)

  #if HAS_HEATER_1
    /**
     * M126: Heater 1 valve open
     */
    inline void gcode_M126() { baricuda_valve_pressure = parser.byteval('S', 255); }
    /**
     * M127: Heater 1 valve close
     */
    inline void gcode_M127() { baricuda_valve_pressure = 0; }
  #endif

  #if HAS_HEATER_2
    /**
     * M128: Heater 2 valve open
     */
    inline void gcode_M128() { baricuda_e_to_p_pressure = parser.byteval('S', 255); }
    /**
     * M129: Heater 2 valve close
     */
    inline void gcode_M129() { baricuda_e_to_p_pressure = 0; }
  #endif

#endif // BARICUDA

/**
 * M140: Set bed temperature
 */
inline void gcode_M140() {
  if (DEBUGGING(DRYRUN)) return;
  if (parser.seenval('S')) thermalManager.setTargetBed(parser.value_celsius());
}

#if ENABLED(ULTIPANEL)

  /**
   * M145: Set the heatup state for a material in the LCD menu
   *
   *   S<material> (0=PLA, 1=ABS)
   *   H<hotend temp>
   *   B<bed temp>
   *   F<fan speed>
   */
  inline void gcode_M145() {
    const uint8_t material = (uint8_t)parser.intval('S');
    if (material >= COUNT(lcd_preheat_hotend_temp)) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM(MSG_ERR_MATERIAL_INDEX);
    }
    else {
      int v;
      if (parser.seenval('H')) {
        v = parser.value_int();
        lcd_preheat_hotend_temp[material] = constrain(v, EXTRUDE_MINTEMP, HEATER_0_MAXTEMP - 15);
      }
      if (parser.seenval('F')) {
        v = parser.value_int();
        lcd_preheat_fan_speed[material] = constrain(v, 0, 255);
      }
      #if TEMP_SENSOR_BED != 0
        if (parser.seenval('B')) {
          v = parser.value_int();
          lcd_preheat_bed_temp[material] = constrain(v, BED_MINTEMP, BED_MAXTEMP - 15);
        }
      #endif
    }
  }

#endif // ULTIPANEL

#if ENABLED(TEMPERATURE_UNITS_SUPPORT)
  /**
   * M149: Set temperature units
   */
  inline void gcode_M149() {
         if (parser.seenval('C')) parser.set_input_temp_units(TEMPUNIT_C);
    else if (parser.seenval('K')) parser.set_input_temp_units(TEMPUNIT_K);
    else if (parser.seenval('F')) parser.set_input_temp_units(TEMPUNIT_F);
  }
#endif

#if HAS_POWER_SWITCH

  /**
   * M80   : Turn on the Power Supply
   * M80 S : Report the current state and exit
   */
  inline void gcode_M80() {

    // S: Report the current power supply state and exit
    if (parser.seen('S')) {
      serialprintPGM(powersupply_on ? PSTR("PS:1\n") : PSTR("PS:0\n"));
      return;
    }

    OUT_WRITE(PS_ON_PIN, PS_ON_AWAKE); // GND

    /**
     * If you have a switch on suicide pin, this is useful
     * if you want to start another print with suicide feature after
     * a print without suicide...
     */
    #if HAS_SUICIDE
      OUT_WRITE(SUICIDE_PIN, HIGH);
    #endif

    #if ENABLED(HAVE_TMC2130)
      delay(100);
      tmc2130_init(); // Settings only stick when the driver has power
    #endif

    powersupply_on = true;

    #if ENABLED(ULTIPANEL)
      LCD_MESSAGEPGM(WELCOME_MSG);
    #endif
  }

#endif // HAS_POWER_SWITCH

/**
 * M81: Turn off Power, including Power Supply, if there is one.
 *
 *      This code should ALWAYS be available for EMERGENCY SHUTDOWN!
 */
inline void gcode_M81() {
  thermalManager.disable_all_heaters();
  stepper.finish_and_disable();

  #if FAN_COUNT > 0
    for (uint8_t i = 0; i < FAN_COUNT; i++) fanSpeeds[i] = 0;
    #if ENABLED(PROBING_FANS_OFF)
      fans_paused = false;
      ZERO(paused_fanSpeeds);
    #endif
  #endif

  safe_delay(1000); // Wait 1 second before switching off

  #if HAS_SUICIDE
    stepper.synchronize();
    suicide();
  #elif HAS_POWER_SWITCH
    OUT_WRITE(PS_ON_PIN, PS_ON_ASLEEP);
    powersupply_on = false;
  #endif

  #if ENABLED(ULTIPANEL)
    LCD_MESSAGEPGM(MACHINE_NAME " " MSG_OFF ".");
  #endif
}

/**
 * M82: Set E codes absolute (default)
 */
inline void gcode_M82() { axis_relative_modes[E_AXIS] = false; }

/**
 * M83: Set E codes relative while in Absolute Coordinates (G90) mode
 */
inline void gcode_M83() { axis_relative_modes[E_AXIS] = true; }

/**
 * M18, M84: Disable stepper motors
 */
inline void gcode_M18_M84() {
  if (parser.seenval('S')) {
    stepper_inactive_time = parser.value_millis_from_seconds();
  }
  else {
    bool all_axis = !((parser.seen('X')) || (parser.seen('Y')) || (parser.seen('Z')) || (parser.seen('E')));
    if (all_axis) {
      stepper.finish_and_disable();
    }
    else {
      stepper.synchronize();
      if (parser.seen('X')) disable_X();
      if (parser.seen('Y')) disable_Y();
      if (parser.seen('Z')) disable_Z();
      #if E0_ENABLE_PIN != X_ENABLE_PIN && E1_ENABLE_PIN != Y_ENABLE_PIN // Only enable on boards that have separate ENABLE_PINS
        if (parser.seen('E')) disable_e_steppers();
      #endif
    }

    #if ENABLED(AUTO_BED_LEVELING_UBL) && ENABLED(ULTRA_LCD)  // Only needed with an LCD
      ubl_lcd_map_control = defer_return_to_status = false;
    #endif
  }
}

/**
 * M85: Set inactivity shutdown timer with parameter S<seconds>. To disable set zero (default)
 */
inline void gcode_M85() {
  if (parser.seen('S')) max_inactive_time = parser.value_millis_from_seconds();
}

/**
 * Multi-stepper support for M92, M201, M203
 */
#if ENABLED(DISTINCT_E_FACTORS)
  #define GET_TARGET_EXTRUDER(CMD) if (get_target_extruder_from_command(CMD)) return
  #define TARGET_EXTRUDER target_extruder
#else
  #define GET_TARGET_EXTRUDER(CMD) NOOP
  #define TARGET_EXTRUDER 0
#endif

/**
 * M92: Set axis steps-per-unit for one or more axes, X, Y, Z, and E.
 *      (Follows the same syntax as G92)
 *
 *      With multiple extruders use T to specify which one.
 */
inline void gcode_M92() {

  GET_TARGET_EXTRUDER(92);

  LOOP_XYZE(i) {
    if (parser.seen(axis_codes[i])) {
      if (i == E_AXIS) {
        const float value = parser.value_per_axis_unit((AxisEnum)(E_AXIS + TARGET_EXTRUDER));
        if (value < 20.0) {
          float factor = planner.axis_steps_per_mm[E_AXIS + TARGET_EXTRUDER] / value; // increase e constants if M92 E14 is given for netfab.
          planner.max_jerk[E_AXIS] *= factor;
          planner.max_feedrate_mm_s[E_AXIS + TARGET_EXTRUDER] *= factor;
          planner.max_acceleration_steps_per_s2[E_AXIS + TARGET_EXTRUDER] *= factor;
        }
        planner.axis_steps_per_mm[E_AXIS + TARGET_EXTRUDER] = value;
      }
      else {
        planner.axis_steps_per_mm[i] = parser.value_per_axis_unit((AxisEnum)i);
      }
    }
  }
  planner.refresh_positioning();
}

/**
 * Output the current position to serial
 */
void report_current_position() {
  SERIAL_PROTOCOLPGM("X:");
  SERIAL_PROTOCOL(current_position[X_AXIS]);
  SERIAL_PROTOCOLPGM(" Y:");
  SERIAL_PROTOCOL(current_position[Y_AXIS]);
  SERIAL_PROTOCOLPGM(" Z:");
  SERIAL_PROTOCOL(current_position[Z_AXIS]);
  SERIAL_PROTOCOLPGM(" E:");
  SERIAL_PROTOCOL(current_position[E_AXIS]);

  stepper.report_positions();

  #if IS_SCARA
    SERIAL_PROTOCOLPAIR("SCARA Theta:", stepper.get_axis_position_degrees(A_AXIS));
    SERIAL_PROTOCOLLNPAIR("   Psi+Theta:", stepper.get_axis_position_degrees(B_AXIS));
    SERIAL_EOL();
  #endif
}

#ifdef M114_DETAIL

  void report_xyze(const float pos[XYZE], const uint8_t n = 4, const uint8_t precision = 3) {
    char str[12];
    for (uint8_t i = 0; i < n; i++) {
      SERIAL_CHAR(' ');
      SERIAL_CHAR(axis_codes[i]);
      SERIAL_CHAR(':');
      SERIAL_PROTOCOL(dtostrf(pos[i], 8, precision, str));
    }
    SERIAL_EOL();
  }

  inline void report_xyz(const float pos[XYZ]) { report_xyze(pos, 3); }

  void report_current_position_detail() {

    stepper.synchronize();

    SERIAL_PROTOCOLPGM("\nLogical:");
    report_xyze(current_position);

    SERIAL_PROTOCOLPGM("Raw:    ");
    const float raw[XYZ] = { RAW_X_POSITION(current_position[X_AXIS]), RAW_Y_POSITION(current_position[Y_AXIS]), RAW_Z_POSITION(current_position[Z_AXIS]) };
    report_xyz(raw);

    SERIAL_PROTOCOLPGM("Leveled:");
    float leveled[XYZ] = { current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS] };
    planner.apply_leveling(leveled);
    report_xyz(leveled);

    SERIAL_PROTOCOLPGM("UnLevel:");
    float unleveled[XYZ] = { leveled[X_AXIS], leveled[Y_AXIS], leveled[Z_AXIS] };
    planner.unapply_leveling(unleveled);
    report_xyz(unleveled);

    #if IS_KINEMATIC
      #if IS_SCARA
        SERIAL_PROTOCOLPGM("ScaraK: ");
      #else
        SERIAL_PROTOCOLPGM("DeltaK: ");
      #endif
      inverse_kinematics(leveled);  // writes delta[]
      report_xyz(delta);
    #endif

    SERIAL_PROTOCOLPGM("Stepper:");
    const float step_count[XYZE] = { stepper.position(X_AXIS), stepper.position(Y_AXIS), stepper.position(Z_AXIS), stepper.position(E_AXIS) };
    report_xyze(step_count, 4, 0);

    #if IS_SCARA
      const float deg[XYZ] = {
        stepper.get_axis_position_degrees(A_AXIS),
        stepper.get_axis_position_degrees(B_AXIS)
      };
      SERIAL_PROTOCOLPGM("Degrees:");
      report_xyze(deg, 2);
    #endif

    SERIAL_PROTOCOLPGM("FromStp:");
    get_cartesian_from_steppers();  // writes cartes[XYZ] (with forward kinematics)
    const float from_steppers[XYZE] = { cartes[X_AXIS], cartes[Y_AXIS], cartes[Z_AXIS], stepper.get_axis_position_mm(E_AXIS) };
    report_xyze(from_steppers);

    const float diff[XYZE] = {
      from_steppers[X_AXIS] - leveled[X_AXIS],
      from_steppers[Y_AXIS] - leveled[Y_AXIS],
      from_steppers[Z_AXIS] - leveled[Z_AXIS],
      from_steppers[E_AXIS] - current_position[E_AXIS]
    };
    SERIAL_PROTOCOLPGM("Differ: ");
    report_xyze(diff);
  }
#endif // M114_DETAIL

/**
 * M114: Report current position to host
 */
inline void gcode_M114() {

  #ifdef M114_DETAIL
    if (parser.seen('D')) {
      report_current_position_detail();
      return;
    }
  #endif

  stepper.synchronize();
  report_current_position();
}

/**
 * M115: Capabilities string
 */
inline void gcode_M115() {
  SERIAL_PROTOCOLLNPGM(MSG_M115_REPORT);

  #if ENABLED(EXTENDED_CAPABILITIES_REPORT)

    // EEPROM (M500, M501)
    #if ENABLED(EEPROM_SETTINGS)
      SERIAL_PROTOCOLLNPGM("Cap:EEPROM:1");
    #else
      SERIAL_PROTOCOLLNPGM("Cap:EEPROM:0");
    #endif

    // AUTOREPORT_TEMP (M155)
    #if ENABLED(AUTO_REPORT_TEMPERATURES)
      SERIAL_PROTOCOLLNPGM("Cap:AUTOREPORT_TEMP:1");
    #else
      SERIAL_PROTOCOLLNPGM("Cap:AUTOREPORT_TEMP:0");
    #endif

    // PROGRESS (M530 S L, M531 <file>, M532 X L)
    SERIAL_PROTOCOLLNPGM("Cap:PROGRESS:0");

    // Print Job timer M75, M76, M77
    SERIAL_PROTOCOLLNPGM("Cap:PRINT_JOB:1");

    // AUTOLEVEL (G29)
    #if HAS_ABL
      SERIAL_PROTOCOLLNPGM("Cap:AUTOLEVEL:1");
    #else
      SERIAL_PROTOCOLLNPGM("Cap:AUTOLEVEL:0");
    #endif

    // Z_PROBE (G30)
    #if HAS_BED_PROBE
      SERIAL_PROTOCOLLNPGM("Cap:Z_PROBE:1");
    #else
      SERIAL_PROTOCOLLNPGM("Cap:Z_PROBE:0");
    #endif

    // MESH_REPORT (M420 V)
    #if HAS_LEVELING
      SERIAL_PROTOCOLLNPGM("Cap:LEVELING_DATA:1");
    #else
      SERIAL_PROTOCOLLNPGM("Cap:LEVELING_DATA:0");
    #endif

    // SOFTWARE_POWER (M80, M81)
    #if HAS_POWER_SWITCH
      SERIAL_PROTOCOLLNPGM("Cap:SOFTWARE_POWER:1");
    #else
      SERIAL_PROTOCOLLNPGM("Cap:SOFTWARE_POWER:0");
    #endif

    // CASE LIGHTS (M355)
    #if HAS_CASE_LIGHT
      SERIAL_PROTOCOLLNPGM("Cap:TOGGLE_LIGHTS:1");
      if (USEABLE_HARDWARE_PWM(CASE_LIGHT_PIN)) {
        SERIAL_PROTOCOLLNPGM("Cap:CASE_LIGHT_BRIGHTNESS:1");
      }
      else
        SERIAL_PROTOCOLLNPGM("Cap:CASE_LIGHT_BRIGHTNESS:0");
    #else
      SERIAL_PROTOCOLLNPGM("Cap:TOGGLE_LIGHTS:0");
      SERIAL_PROTOCOLLNPGM("Cap:CASE_LIGHT_BRIGHTNESS:0");
    #endif

    // EMERGENCY_PARSER (M108, M112, M410)
    #if ENABLED(EMERGENCY_PARSER)
      SERIAL_PROTOCOLLNPGM("Cap:EMERGENCY_PARSER:1");
    #else
      SERIAL_PROTOCOLLNPGM("Cap:EMERGENCY_PARSER:0");
    #endif

  #endif // EXTENDED_CAPABILITIES_REPORT
}

/**
 * M117: Set LCD Status Message
 */
inline void gcode_M117() { lcd_setstatus(parser.string_arg); }

/**
 * M118: Display a message in the host console.
 *
 *  A  Append '// ' for an action command, as in OctoPrint
 *  E  Have the host 'echo:' the text
 */
inline void gcode_M118() {
  if (parser.boolval('E')) SERIAL_ECHO_START();
  if (parser.boolval('A')) SERIAL_ECHOPGM("// ");
  SERIAL_ECHOLN(parser.string_arg);
}

/**
 * M119: Output endstop states to serial output
 */
inline void gcode_M119() { endstops.M119(); }

/**
 * M120: Enable endstops and set non-homing endstop state to "enabled"
 */
inline void gcode_M120() { endstops.enable_globally(true); }

/**
 * M121: Disable endstops and set non-homing endstop state to "disabled"
 */
inline void gcode_M121() { endstops.enable_globally(false); }

#if ENABLED(PARK_HEAD_ON_PAUSE)

  /**
   * M125: Store current position and move to filament change position.
   *       Called on pause (by M25) to prevent material leaking onto the
   *       object. On resume (M24) the head will be moved back and the
   *       print will resume.
   *
   *       If Marlin is compiled without SD Card support, M125 can be
   *       used directly to pause the print and move to park position,
   *       resuming with a button click or M108.
   *
   *    L = override retract length
   *    X = override X
   *    Y = override Y
   *    Z = override Z raise
   */
  inline void gcode_M125() {

    // Initial retract before move to filament change position
    const float retract = parser.seen('L') ? parser.value_axis_units(E_AXIS) : 0
      #if defined(PAUSE_PARK_RETRACT_LENGTH) && PAUSE_PARK_RETRACT_LENGTH > 0
        - (PAUSE_PARK_RETRACT_LENGTH)
      #endif
    ;

    // Lift Z axis
    const float z_lift = parser.linearval('Z')
      #if PAUSE_PARK_Z_ADD > 0
        + PAUSE_PARK_Z_ADD
      #endif
    ;

    // Move XY axes to filament change position or given position
    const float x_pos = parser.linearval('X')
      #ifdef PAUSE_PARK_X_POS
        + PAUSE_PARK_X_POS
      #endif
      #if HOTENDS > 1 && DISABLED(DUAL_X_CARRIAGE)
        + (active_extruder ? hotend_offset[X_AXIS][active_extruder] : 0)
      #endif
    ;
    const float y_pos = parser.linearval('Y')
      #ifdef PAUSE_PARK_Y_POS
        + PAUSE_PARK_Y_POS
      #endif
      #if HOTENDS > 1 && DISABLED(DUAL_X_CARRIAGE)
        + (active_extruder ? hotend_offset[Y_AXIS][active_extruder] : 0)
      #endif
    ;

    const bool job_running = print_job_timer.isRunning();

    if (pause_print(retract, z_lift, x_pos, y_pos)) {
      #if DISABLED(SDSUPPORT)
        // Wait for lcd click or M108
        wait_for_filament_reload();

        // Return to print position and continue
        resume_print();

        if (job_running) print_job_timer.start();
      #endif
    }
  }

#endif // PARK_HEAD_ON_PAUSE

#if HAS_COLOR_LEDS

  /**
   * M150: Set Status LED Color - Use R-U-B-W for R-G-B-W
   *
   * Always sets all 3 or 4 components. If a component is left out, set to 0.
   *
   * Examples:
   *
   *   M150 R255       ; Turn LED red
   *   M150 R255 U127  ; Turn LED orange (PWM only)
   *   M150            ; Turn LED off
   *   M150 R U B      ; Turn LED white
   *   M150 W          ; Turn LED white using a white LED
   *
   */
  inline void gcode_M150() {
    set_led_color(
      parser.seen('R') ? (parser.has_value() ? parser.value_byte() : 255) : 0,
      parser.seen('U') ? (parser.has_value() ? parser.value_byte() : 255) : 0,
      parser.seen('B') ? (parser.has_value() ? parser.value_byte() : 255) : 0
      #if ENABLED(RGBW_LED)
        , parser.seen('W') ? (parser.has_value() ? parser.value_byte() : 255) : 0
      #endif
    );
  }

#endif // HAS_COLOR_LEDS

/**
 * M200: Set filament diameter and set E axis units to cubic units
 *
 *    T<extruder> - Optional extruder number. Current extruder if omitted.
 *    D<linear> - Diameter of the filament. Use "D0" to switch back to linear units on the E axis.
 */
inline void gcode_M200() {

  if (get_target_extruder_from_command(200)) return;

  if (parser.seen('D')) {
    // setting any extruder filament size disables volumetric on the assumption that
    // slicers either generate in extruder values as cubic mm or as as filament feeds
    // for all extruders
    volumetric_enabled = (parser.value_linear_units() != 0.0);
    if (volumetric_enabled) {
      filament_size[target_extruder] = parser.value_linear_units();
      // make sure all extruders have some sane value for the filament size
      for (uint8_t i = 0; i < COUNT(filament_size); i++)
        if (! filament_size[i]) filament_size[i] = DEFAULT_NOMINAL_FILAMENT_DIA;
    }
  }
  calculate_volumetric_multipliers();
}

/**
 * M201: Set max acceleration in units/s^2 for print moves (M201 X1000 Y1000)
 *
 *       With multiple extruders use T to specify which one.
 */
inline void gcode_M201() {

  GET_TARGET_EXTRUDER(201);

  LOOP_XYZE(i) {
    if (parser.seen(axis_codes[i])) {
      const uint8_t a = i + (i == E_AXIS ? TARGET_EXTRUDER : 0);
      planner.max_acceleration_mm_per_s2[a] = parser.value_axis_units((AxisEnum)a);
    }
  }
  // steps per sq second need to be updated to agree with the units per sq second (as they are what is used in the planner)
  planner.reset_acceleration_rates();
}

#if 0 // Not used for Sprinter/grbl gen6
  inline void gcode_M202() {
    LOOP_XYZE(i) {
      if (parser.seen(axis_codes[i])) axis_travel_steps_per_sqr_second[i] = parser.value_axis_units((AxisEnum)i) * planner.axis_steps_per_mm[i];
    }
  }
#endif


/**
 * M203: Set maximum feedrate that your machine can sustain (M203 X200 Y200 Z300 E10000) in units/sec
 *
 *       With multiple extruders use T to specify which one.
 */
inline void gcode_M203() {

  GET_TARGET_EXTRUDER(203);

  LOOP_XYZE(i)
    if (parser.seen(axis_codes[i])) {
      const uint8_t a = i + (i == E_AXIS ? TARGET_EXTRUDER : 0);
      planner.max_feedrate_mm_s[a] = parser.value_axis_units((AxisEnum)a);
    }
}

/**
 * M204: Set Accelerations in units/sec^2 (M204 P1200 R3000 T3000)
 *
 *    P = Printing moves
 *    R = Retract only (no X, Y, Z) moves
 *    T = Travel (non printing) moves
 *
 *  Also sets minimum segment time in ms (B20000) to prevent buffer under-runs and M20 minimum feedrate
 */
inline void gcode_M204() {
  if (parser.seen('S')) {  // Kept for legacy compatibility. Should NOT BE USED for new developments.
    planner.travel_acceleration = planner.acceleration = parser.value_linear_units();
    SERIAL_ECHOLNPAIR("Setting Print and Travel Acceleration: ", planner.acceleration);
  }
  if (parser.seen('P')) {
    planner.acceleration = parser.value_linear_units();
    SERIAL_ECHOLNPAIR("Setting Print Acceleration: ", planner.acceleration);
  }
  if (parser.seen('R')) {
    planner.retract_acceleration = parser.value_linear_units();
    SERIAL_ECHOLNPAIR("Setting Retract Acceleration: ", planner.retract_acceleration);
  }
  if (parser.seen('T')) {
    planner.travel_acceleration = parser.value_linear_units();
    SERIAL_ECHOLNPAIR("Setting Travel Acceleration: ", planner.travel_acceleration);
  }
}

/**
 * M205: Set Advanced Settings
 *
 *    S = Min Feed Rate (units/s)
 *    T = Min Travel Feed Rate (units/s)
 *    B = Min Segment Time (µs)
 *    X = Max X Jerk (units/sec^2)
 *    Y = Max Y Jerk (units/sec^2)
 *    Z = Max Z Jerk (units/sec^2)
 *    E = Max E Jerk (units/sec^2)
 */
inline void gcode_M205() {
  if (parser.seen('S')) planner.min_feedrate_mm_s = parser.value_linear_units();
  if (parser.seen('T')) planner.min_travel_feedrate_mm_s = parser.value_linear_units();
  if (parser.seen('B')) planner.min_segment_time = parser.value_millis();
  if (parser.seen('X')) planner.max_jerk[X_AXIS] = parser.value_linear_units();
  if (parser.seen('Y')) planner.max_jerk[Y_AXIS] = parser.value_linear_units();
  if (parser.seen('Z')) planner.max_jerk[Z_AXIS] = parser.value_linear_units();
  if (parser.seen('E')) planner.max_jerk[E_AXIS] = parser.value_linear_units();
}

#if HAS_M206_COMMAND

  /**
   * M206: Set Additional Homing Offset (X Y Z). SCARA aliases T=X, P=Y
   *
   * *** @thinkyhead: I recommend deprecating M206 for SCARA in favor of M665.
   * ***              M206 for SCARA will remain enabled in 1.1.x for compatibility.
   * ***              In the next 1.2 release, it will simply be disabled by default.
   */
  inline void gcode_M206() {
    LOOP_XYZ(i)
      if (parser.seen(axis_codes[i]))
        set_home_offset((AxisEnum)i, parser.value_linear_units());

    #if ENABLED(MORGAN_SCARA)
      if (parser.seen('T')) set_home_offset(A_AXIS, parser.value_linear_units()); // Theta
      if (parser.seen('P')) set_home_offset(B_AXIS, parser.value_linear_units()); // Psi
    #endif

    SYNC_PLAN_POSITION_KINEMATIC();
    report_current_position();
  }

#endif // HAS_M206_COMMAND

#if ENABLED(DELTA)
  /**
   * M665: Set delta configurations
   *
   *    H = delta height
   *    L = diagonal rod
   *    R = delta radius
   *    S = segments per second
   *    B = delta calibration radius
   *    X = Alpha (Tower 1) angle trim
   *    Y = Beta (Tower 2) angle trim
   *    Z = Rotate A and B by this angle
   */
  inline void gcode_M665() {
    if (parser.seen('H')) {
      home_offset[Z_AXIS] = parser.value_linear_units() - DELTA_HEIGHT;
      update_software_endstops(Z_AXIS);
    }
    if (parser.seen('L')) delta_diagonal_rod             = parser.value_linear_units();
    if (parser.seen('R')) delta_radius                   = parser.value_linear_units();
    if (parser.seen('S')) delta_segments_per_second      = parser.value_float();
    if (parser.seen('B')) delta_calibration_radius       = parser.value_float();
    if (parser.seen('X')) delta_tower_angle_trim[A_AXIS] = parser.value_float();
    if (parser.seen('Y')) delta_tower_angle_trim[B_AXIS] = parser.value_float();
    if (parser.seen('Z')) { // rotate all 3 axis for Z = 0
      delta_tower_angle_trim[A_AXIS] -= parser.value_float();
      delta_tower_angle_trim[B_AXIS] -= parser.value_float();
    }
    recalc_delta_settings(delta_radius, delta_diagonal_rod);
  }
  /**
   * M666: Set delta endstop adjustment
   */
  inline void gcode_M666() {
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOLNPGM(">>> gcode_M666");
      }
    #endif
    LOOP_XYZ(i) {
      if (parser.seen(axis_codes[i])) {
        endstop_adj[i] = parser.value_linear_units();
        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) {
            SERIAL_ECHOPAIR("endstop_adj[", axis_codes[i]);
            SERIAL_ECHOLNPAIR("] = ", endstop_adj[i]);
          }
        #endif
      }
    }
    #if ENABLED(DEBUG_LEVELING_FEATURE)
      if (DEBUGGING(LEVELING)) {
        SERIAL_ECHOLNPGM("<<< gcode_M666");
      }
    #endif
    // normalize endstops so all are <=0; set the residue to delta height
    const float z_temp = MAX3(endstop_adj[A_AXIS], endstop_adj[B_AXIS], endstop_adj[C_AXIS]);
    home_offset[Z_AXIS] -= z_temp;
    LOOP_XYZ(i) endstop_adj[i] -= z_temp;
  }

#elif IS_SCARA

  /**
   * M665: Set SCARA settings
   *
   * Parameters:
   *
   *   S[segments-per-second] - Segments-per-second
   *   P[theta-psi-offset]    - Theta-Psi offset, added to the shoulder (A/X) angle
   *   T[theta-offset]        - Theta     offset, added to the elbow    (B/Y) angle
   *
   *   A, P, and X are all aliases for the shoulder angle
   *   B, T, and Y are all aliases for the elbow angle
   */
  inline void gcode_M665() {
    if (parser.seen('S')) delta_segments_per_second = parser.value_float();

    const bool hasA = parser.seen('A'), hasP = parser.seen('P'), hasX = parser.seen('X');
    const uint8_t sumAPX = hasA + hasP + hasX;
    if (sumAPX == 1)
      home_offset[A_AXIS] = parser.value_float();
    else if (sumAPX > 1) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM("Only one of A, P, or X is allowed.");
      return;
    }

    const bool hasB = parser.seen('B'), hasT = parser.seen('T'), hasY = parser.seen('Y');
    const uint8_t sumBTY = hasB + hasT + hasY;
    if (sumBTY == 1)
      home_offset[B_AXIS] = parser.value_float();
    else if (sumBTY > 1) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM("Only one of B, T, or Y is allowed.");
      return;
    }
  }

#elif ENABLED(Z_DUAL_ENDSTOPS) // !DELTA && ENABLED(Z_DUAL_ENDSTOPS)

  /**
   * M666: For Z Dual Endstop setup, set z axis offset to the z2 axis.
   */
  inline void gcode_M666() {
    if (parser.seen('Z')) z_endstop_adj = parser.value_linear_units();
    SERIAL_ECHOLNPAIR("Z Endstop Adjustment set to (mm):", z_endstop_adj);
  }

#endif // !DELTA && Z_DUAL_ENDSTOPS

#if ENABLED(FWRETRACT)

  /**
   * M207: Set firmware retraction values
   *
   *   S[+units]    retract_length
   *   W[+units]    retract_length_swap (multi-extruder)
   *   F[units/min] retract_feedrate_mm_s
   *   Z[units]     retract_zlift
   */
  inline void gcode_M207() {
    if (parser.seen('S')) retract_length = parser.value_axis_units(E_AXIS);
    if (parser.seen('F')) retract_feedrate_mm_s = MMM_TO_MMS(parser.value_axis_units(E_AXIS));
    if (parser.seen('Z')) retract_zlift = parser.value_linear_units();
    #if EXTRUDERS > 1
      if (parser.seen('W')) retract_length_swap = parser.value_axis_units(E_AXIS);
    #endif
  }

  /**
   * M208: Set firmware un-retraction values
   *
   *   S[+units]    retract_recover_length (in addition to M207 S*)
   *   W[+units]    retract_recover_length_swap (multi-extruder)
   *   F[units/min] retract_recover_feedrate_mm_s
   */
  inline void gcode_M208() {
    if (parser.seen('S')) retract_recover_length = parser.value_axis_units(E_AXIS);
    if (parser.seen('F')) retract_recover_feedrate_mm_s = MMM_TO_MMS(parser.value_axis_units(E_AXIS));
    #if EXTRUDERS > 1
      if (parser.seen('W')) retract_recover_length_swap = parser.value_axis_units(E_AXIS);
    #endif
  }

  /**
   * M209: Enable automatic retract (M209 S1)
   *   For slicers that don't support G10/11, reversed extrude-only
   *   moves will be classified as retraction.
   */
  inline void gcode_M209() {
    if (parser.seen('S')) {
      autoretract_enabled = parser.value_bool();
      for (int i = 0; i < EXTRUDERS; i++) retracted[i] = false;
    }
  }

#endif // FWRETRACT

/**
 * M211: Enable, Disable, and/or Report software endstops
 *
 * Usage: M211 S1 to enable, M211 S0 to disable, M211 alone for report
 */
inline void gcode_M211() {
  SERIAL_ECHO_START();
  #if HAS_SOFTWARE_ENDSTOPS
    if (parser.seen('S')) soft_endstops_enabled = parser.value_bool();
    SERIAL_ECHOPGM(MSG_SOFT_ENDSTOPS);
    serialprintPGM(soft_endstops_enabled ? PSTR(MSG_ON) : PSTR(MSG_OFF));
  #else
    SERIAL_ECHOPGM(MSG_SOFT_ENDSTOPS);
    SERIAL_ECHOPGM(MSG_OFF);
  #endif
  SERIAL_ECHOPGM(MSG_SOFT_MIN);
  SERIAL_ECHOPAIR(    MSG_X, soft_endstop_min[X_AXIS]);
  SERIAL_ECHOPAIR(" " MSG_Y, soft_endstop_min[Y_AXIS]);
  SERIAL_ECHOPAIR(" " MSG_Z, soft_endstop_min[Z_AXIS]);
  SERIAL_ECHOPGM(MSG_SOFT_MAX);
  SERIAL_ECHOPAIR(    MSG_X, soft_endstop_max[X_AXIS]);
  SERIAL_ECHOPAIR(" " MSG_Y, soft_endstop_max[Y_AXIS]);
  SERIAL_ECHOLNPAIR(" " MSG_Z, soft_endstop_max[Z_AXIS]);
}

#if HOTENDS > 1

  /**
   * M218 - set hotend offset (in linear units)
   *
   *   T<tool>
   *   X<xoffset>
   *   Y<yoffset>
   *   Z<zoffset> - Available with DUAL_X_CARRIAGE and SWITCHING_NOZZLE
   */
  inline void gcode_M218() {
    if (get_target_extruder_from_command(218) || target_extruder == 0) return;

    if (parser.seenval('X')) hotend_offset[X_AXIS][target_extruder] = parser.value_linear_units();
    if (parser.seenval('Y')) hotend_offset[Y_AXIS][target_extruder] = parser.value_linear_units();

    #if ENABLED(DUAL_X_CARRIAGE) || ENABLED(SWITCHING_NOZZLE)
      if (parser.seenval('Z')) hotend_offset[Z_AXIS][target_extruder] = parser.value_linear_units();
    #endif

    SERIAL_ECHO_START();
    SERIAL_ECHOPGM(MSG_HOTEND_OFFSET);
    HOTEND_LOOP() {
      SERIAL_CHAR(' ');
      SERIAL_ECHO(hotend_offset[X_AXIS][e]);
      SERIAL_CHAR(',');
      SERIAL_ECHO(hotend_offset[Y_AXIS][e]);
      #if ENABLED(DUAL_X_CARRIAGE) || ENABLED(SWITCHING_NOZZLE)
        SERIAL_CHAR(',');
        SERIAL_ECHO(hotend_offset[Z_AXIS][e]);
      #endif
    }
    SERIAL_EOL();
  }

#endif // HOTENDS > 1

/**
 * M220: Set speed percentage factor, aka "Feed Rate" (M220 S95)
 */
inline void gcode_M220() {
  if (parser.seenval('S')) feedrate_percentage = parser.value_int();
}

/**
 * M221: Set extrusion percentage (M221 T0 S95)
 */
inline void gcode_M221() {
  if (get_target_extruder_from_command(221)) return;
  if (parser.seenval('S'))
    flow_percentage[target_extruder] = parser.value_int();
}

/**
 * M226: Wait until the specified pin reaches the state required (M226 P<pin> S<state>)
 */
inline void gcode_M226() {
  if (parser.seen('P')) {
    const int pin_number = parser.value_int(),
              pin_state = parser.intval('S', -1); // required pin state - default is inverted

    if (WITHIN(pin_state, -1, 1) && pin_number > -1 && !pin_is_protected(pin_number)) {

      int target = LOW;

      stepper.synchronize();

      pinMode(pin_number, INPUT);
      switch (pin_state) {
        case 1:
          target = HIGH;
          break;
        case 0:
          target = LOW;
          break;
        case -1:
          target = !digitalRead(pin_number);
          break;
      }

      while (digitalRead(pin_number) != target) idle();

    } // pin_state -1 0 1 && pin_number > -1
  } // parser.seen('P')
}

#if ENABLED(EXPERIMENTAL_I2CBUS)

  /**
   * M260: Send data to a I2C slave device
   *
   * This is a PoC, the formating and arguments for the GCODE will
   * change to be more compatible, the current proposal is:
   *
   *  M260 A<slave device address base 10> ; Sets the I2C slave address the data will be sent to
   *
   *  M260 B<byte-1 value in base 10>
   *  M260 B<byte-2 value in base 10>
   *  M260 B<byte-3 value in base 10>
   *
   *  M260 S1 ; Send the buffered data and reset the buffer
   *  M260 R1 ; Reset the buffer without sending data
   *
   */
  inline void gcode_M260() {
    // Set the target address
    if (parser.seen('A')) i2c.address(parser.value_byte());

    // Add a new byte to the buffer
    if (parser.seen('B')) i2c.addbyte(parser.value_byte());

    // Flush the buffer to the bus
    if (parser.seen('S')) i2c.send();

    // Reset and rewind the buffer
    else if (parser.seen('R')) i2c.reset();
  }

  /**
   * M261: Request X bytes from I2C slave device
   *
   * Usage: M261 A<slave device address base 10> B<number of bytes>
   */
  inline void gcode_M261() {
    if (parser.seen('A')) i2c.address(parser.value_byte());

    uint8_t bytes = parser.byteval('B', 1);

    if (i2c.addr && bytes && bytes <= TWIBUS_BUFFER_SIZE) {
      i2c.relay(bytes);
    }
    else {
      SERIAL_ERROR_START();
      SERIAL_ERRORLN("Bad i2c request");
    }
  }

#endif // EXPERIMENTAL_I2CBUS

#if HAS_SERVOS

  /**
   * M280: Get or set servo position. P<index> [S<angle>]
   */
  inline void gcode_M280() {
    if (!parser.seen('P')) return;
    const int servo_index = parser.value_int();
    if (WITHIN(servo_index, 0, NUM_SERVOS - 1)) {
      if (parser.seen('S'))
        MOVE_SERVO(servo_index, parser.value_int());
      else {
        SERIAL_ECHO_START();
        SERIAL_ECHOPAIR(" Servo ", servo_index);
        SERIAL_ECHOLNPAIR(": ", servo[servo_index].read());
      }
    }
    else {
      SERIAL_ERROR_START();
      SERIAL_ECHOPAIR("Servo ", servo_index);
      SERIAL_ECHOLNPGM(" out of range");
    }
  }

#endif // HAS_SERVOS

#if HAS_BUZZER

  /**
   * M300: Play beep sound S<frequency Hz> P<duration ms>
   */
  inline void gcode_M300() {
    uint16_t const frequency = parser.ushortval('S', 260);
    uint16_t duration = parser.ushortval('P', 1000);

    // Limits the tone duration to 0-5 seconds.
    NOMORE(duration, 5000);

    BUZZ(duration, frequency);
  }

#endif // HAS_BUZZER

#if ENABLED(PIDTEMP)

  /**
   * M301: Set PID parameters P I D (and optionally C, L)
   *
   *   P[float] Kp term
   *   I[float] Ki term (unscaled)
   *   D[float] Kd term (unscaled)
   *
   * With PID_EXTRUSION_SCALING:
   *
   *   C[float] Kc term
   *   L[float] LPQ length
   */
  inline void gcode_M301() {

    // multi-extruder PID patch: M301 updates or prints a single extruder's PID values
    // default behaviour (omitting E parameter) is to update for extruder 0 only
    const uint8_t e = parser.byteval('E'); // extruder being updated

    if (e < HOTENDS) { // catch bad input value
      if (parser.seen('P')) PID_PARAM(Kp, e) = parser.value_float();
      if (parser.seen('I')) PID_PARAM(Ki, e) = scalePID_i(parser.value_float());
      if (parser.seen('D')) PID_PARAM(Kd, e) = scalePID_d(parser.value_float());
      #if ENABLED(PID_EXTRUSION_SCALING)
        if (parser.seen('C')) PID_PARAM(Kc, e) = parser.value_float();
        if (parser.seen('L')) lpq_len = parser.value_float();
        NOMORE(lpq_len, LPQ_MAX_LEN);
      #endif

      thermalManager.updatePID();
      SERIAL_ECHO_START();
      #if ENABLED(PID_PARAMS_PER_HOTEND)
        SERIAL_ECHOPAIR(" e:", e); // specify extruder in serial output
      #endif // PID_PARAMS_PER_HOTEND
      SERIAL_ECHOPAIR(" p:", PID_PARAM(Kp, e));
      SERIAL_ECHOPAIR(" i:", unscalePID_i(PID_PARAM(Ki, e)));
      SERIAL_ECHOPAIR(" d:", unscalePID_d(PID_PARAM(Kd, e)));
      #if ENABLED(PID_EXTRUSION_SCALING)
        //Kc does not have scaling applied above, or in resetting defaults
        SERIAL_ECHOPAIR(" c:", PID_PARAM(Kc, e));
      #endif
      SERIAL_EOL();
    }
    else {
      SERIAL_ERROR_START();
      SERIAL_ERRORLN(MSG_INVALID_EXTRUDER);
    }
  }

#endif // PIDTEMP

#if ENABLED(PIDTEMPBED)

  inline void gcode_M304() {
    if (parser.seen('P')) thermalManager.bedKp = parser.value_float();
    if (parser.seen('I')) thermalManager.bedKi = scalePID_i(parser.value_float());
    if (parser.seen('D')) thermalManager.bedKd = scalePID_d(parser.value_float());

    thermalManager.updatePID();

    SERIAL_ECHO_START();
    SERIAL_ECHOPAIR(" p:", thermalManager.bedKp);
    SERIAL_ECHOPAIR(" i:", unscalePID_i(thermalManager.bedKi));
    SERIAL_ECHOLNPAIR(" d:", unscalePID_d(thermalManager.bedKd));
  }

#endif // PIDTEMPBED

#if defined(CHDK) || HAS_PHOTOGRAPH

  /**
   * M240: Trigger a camera by emulating a Canon RC-1
   *       See http://www.doc-diy.net/photo/rc-1_hacked/
   */
  inline void gcode_M240() {
    #ifdef CHDK

      OUT_WRITE(CHDK, HIGH);
      chdkHigh = millis();
      chdkActive = true;

    #elif HAS_PHOTOGRAPH

      const uint8_t NUM_PULSES = 16;
      const float PULSE_LENGTH = 0.01524;
      for (int i = 0; i < NUM_PULSES; i++) {
        WRITE(PHOTOGRAPH_PIN, HIGH);
        _delay_ms(PULSE_LENGTH);
        WRITE(PHOTOGRAPH_PIN, LOW);
        _delay_ms(PULSE_LENGTH);
      }
      delay(7.33);
      for (int i = 0; i < NUM_PULSES; i++) {
        WRITE(PHOTOGRAPH_PIN, HIGH);
        _delay_ms(PULSE_LENGTH);
        WRITE(PHOTOGRAPH_PIN, LOW);
        _delay_ms(PULSE_LENGTH);
      }

    #endif // !CHDK && HAS_PHOTOGRAPH
  }

#endif // CHDK || PHOTOGRAPH_PIN

#if HAS_LCD_CONTRAST

  /**
   * M250: Read and optionally set the LCD contrast
   */
  inline void gcode_M250() {
    if (parser.seen('C')) set_lcd_contrast(parser.value_int());
    SERIAL_PROTOCOLPGM("lcd contrast value: ");
    SERIAL_PROTOCOL(lcd_contrast);
    SERIAL_EOL();
  }

#endif // HAS_LCD_CONTRAST

#if ENABLED(PREVENT_COLD_EXTRUSION)

  /**
   * M302: Allow cold extrudes, or set the minimum extrude temperature
   *
   *       S<temperature> sets the minimum extrude temperature
   *       P<bool> enables (1) or disables (0) cold extrusion
   *
   *  Examples:
   *
   *       M302         ; report current cold extrusion state
   *       M302 P0      ; enable cold extrusion checking
   *       M302 P1      ; disables cold extrusion checking
   *       M302 S0      ; always allow extrusion (disables checking)
   *       M302 S170    ; only allow extrusion above 170
   *       M302 S170 P1 ; set min extrude temp to 170 but leave disabled
   */
  inline void gcode_M302() {
    const bool seen_S = parser.seen('S');
    if (seen_S) {
      thermalManager.extrude_min_temp = parser.value_celsius();
      thermalManager.allow_cold_extrude = (thermalManager.extrude_min_temp == 0);
    }

    if (parser.seen('P'))
      thermalManager.allow_cold_extrude = (thermalManager.extrude_min_temp == 0) || parser.value_bool();
    else if (!seen_S) {
      // Report current state
      SERIAL_ECHO_START();
      SERIAL_ECHOPAIR("Cold extrudes are ", (thermalManager.allow_cold_extrude ? "en" : "dis"));
      SERIAL_ECHOPAIR("abled (min temp ", thermalManager.extrude_min_temp);
      SERIAL_ECHOLNPGM("C)");
    }
  }

#endif // PREVENT_COLD_EXTRUSION

/**
 * M303: PID relay autotune
 *
 *       S<temperature> sets the target temperature. (default 150C)
 *       E<extruder> (-1 for the bed) (default 0)
 *       C<cycles>
 *       U<bool> with a non-zero value will apply the result to current settings
 */
inline void gcode_M303() {
  #if HAS_PID_HEATING
    const int e = parser.intval('E'), c = parser.intval('C', 5);
    const bool u = parser.boolval('U');

    int16_t temp = parser.celsiusval('S', e < 0 ? 70 : 150);

    if (WITHIN(e, 0, HOTENDS - 1))
      target_extruder = e;

    KEEPALIVE_STATE(NOT_BUSY); // don't send "busy: processing" messages during autotune output

    thermalManager.PID_autotune(temp, e, c, u);

    KEEPALIVE_STATE(IN_HANDLER);
  #else
    SERIAL_ERROR_START();
    SERIAL_ERRORLNPGM(MSG_ERR_M303_DISABLED);
  #endif
}

#if ENABLED(MORGAN_SCARA)

  bool SCARA_move_to_cal(uint8_t delta_a, uint8_t delta_b) {
    if (IsRunning()) {
      forward_kinematics_SCARA(delta_a, delta_b);
      destination[X_AXIS] = LOGICAL_X_POSITION(cartes[X_AXIS]);
      destination[Y_AXIS] = LOGICAL_Y_POSITION(cartes[Y_AXIS]);
      destination[Z_AXIS] = current_position[Z_AXIS];
      prepare_move_to_destination();
      return true;
    }
    return false;
  }

  /**
   * M360: SCARA calibration: Move to cal-position ThetaA (0 deg calibration)
   */
  inline bool gcode_M360() {
    SERIAL_ECHOLNPGM(" Cal: Theta 0");
    return SCARA_move_to_cal(0, 120);
  }

  /**
   * M361: SCARA calibration: Move to cal-position ThetaB (90 deg calibration - steps per degree)
   */
  inline bool gcode_M361() {
    SERIAL_ECHOLNPGM(" Cal: Theta 90");
    return SCARA_move_to_cal(90, 130);
  }

  /**
   * M362: SCARA calibration: Move to cal-position PsiA (0 deg calibration)
   */
  inline bool gcode_M362() {
    SERIAL_ECHOLNPGM(" Cal: Psi 0");
    return SCARA_move_to_cal(60, 180);
  }

  /**
   * M363: SCARA calibration: Move to cal-position PsiB (90 deg calibration - steps per degree)
   */
  inline bool gcode_M363() {
    SERIAL_ECHOLNPGM(" Cal: Psi 90");
    return SCARA_move_to_cal(50, 90);
  }

  /**
   * M364: SCARA calibration: Move to cal-position PsiC (90 deg to Theta calibration position)
   */
  inline bool gcode_M364() {
    SERIAL_ECHOLNPGM(" Cal: Theta-Psi 90");
    return SCARA_move_to_cal(45, 135);
  }

#endif // SCARA

#if ENABLED(EXT_SOLENOID)

  void enable_solenoid(const uint8_t num) {
    switch (num) {
      case 0:
        OUT_WRITE(SOL0_PIN, HIGH);
        break;
        #if HAS_SOLENOID_1 && EXTRUDERS > 1
          case 1:
            OUT_WRITE(SOL1_PIN, HIGH);
            break;
        #endif
        #if HAS_SOLENOID_2 && EXTRUDERS > 2
          case 2:
            OUT_WRITE(SOL2_PIN, HIGH);
            break;
        #endif
        #if HAS_SOLENOID_3 && EXTRUDERS > 3
          case 3:
            OUT_WRITE(SOL3_PIN, HIGH);
            break;
        #endif
        #if HAS_SOLENOID_4 && EXTRUDERS > 4
          case 4:
            OUT_WRITE(SOL4_PIN, HIGH);
            break;
        #endif
      default:
        SERIAL_ECHO_START();
        SERIAL_ECHOLNPGM(MSG_INVALID_SOLENOID);
        break;
    }
  }

  void enable_solenoid_on_active_extruder() { enable_solenoid(active_extruder); }

  void disable_all_solenoids() {
    OUT_WRITE(SOL0_PIN, LOW);
    #if HAS_SOLENOID_1 && EXTRUDERS > 1
      OUT_WRITE(SOL1_PIN, LOW);
    #endif
    #if HAS_SOLENOID_2 && EXTRUDERS > 2
      OUT_WRITE(SOL2_PIN, LOW);
    #endif
    #if HAS_SOLENOID_3 && EXTRUDERS > 3
      OUT_WRITE(SOL3_PIN, LOW);
    #endif
    #if HAS_SOLENOID_4 && EXTRUDERS > 4
      OUT_WRITE(SOL4_PIN, LOW);
    #endif
  }

  /**
   * M380: Enable solenoid on the active extruder
   */
  inline void gcode_M380() { enable_solenoid_on_active_extruder(); }

  /**
   * M381: Disable all solenoids
   */
  inline void gcode_M381() { disable_all_solenoids(); }

#endif // EXT_SOLENOID

/**
 * M400: Finish all moves
 */
inline void gcode_M400() { stepper.synchronize(); }

#if HAS_BED_PROBE

  /**
   * M401: Engage Z Servo endstop if available
   */
  inline void gcode_M401() { DEPLOY_PROBE(); }

  /**
   * M402: Retract Z Servo endstop if enabled
   */
  inline void gcode_M402() { STOW_PROBE(); }

#endif // HAS_BED_PROBE

#if ENABLED(FILAMENT_WIDTH_SENSOR)

  /**
   * M404: Display or set (in current units) the nominal filament width (3mm, 1.75mm ) W<3.0>
   */
  inline void gcode_M404() {
    if (parser.seen('W')) {
      filament_width_nominal = parser.value_linear_units();
    }
    else {
      SERIAL_PROTOCOLPGM("Filament dia (nominal mm):");
      SERIAL_PROTOCOLLN(filament_width_nominal);
    }
  }

  /**
   * M405: Turn on filament sensor for control
   */
  inline void gcode_M405() {
    // This is technically a linear measurement, but since it's quantized to centimeters and is a different
    // unit than everything else, it uses parser.value_byte() instead of parser.value_linear_units().
    if (parser.seen('D')) {
      meas_delay_cm = parser.value_byte();
      NOMORE(meas_delay_cm, MAX_MEASUREMENT_DELAY);
    }

    if (filwidth_delay_index[1] == -1) { // Initialize the ring buffer if not done since startup
      const uint8_t temp_ratio = thermalManager.widthFil_to_size_ratio() - 100; // -100 to scale within a signed byte

      for (uint8_t i = 0; i < COUNT(measurement_delay); ++i)
        measurement_delay[i] = temp_ratio;

      filwidth_delay_index[0] = filwidth_delay_index[1] = 0;
    }

    filament_sensor = true;

    //SERIAL_PROTOCOLPGM("Filament dia (measured mm):");
    //SERIAL_PROTOCOL(filament_width_meas);
    //SERIAL_PROTOCOLPGM("Extrusion ratio(%):");
    //SERIAL_PROTOCOL(flow_percentage[active_extruder]);
  }

  /**
   * M406: Turn off filament sensor for control
   */
  inline void gcode_M406() { filament_sensor = false; }

  /**
   * M407: Get measured filament diameter on serial output
   */
  inline void gcode_M407() {
    SERIAL_PROTOCOLPGM("Filament dia (measured mm):");
    SERIAL_PROTOCOLLN(filament_width_meas);
  }

#endif // FILAMENT_WIDTH_SENSOR

void quickstop_stepper() {
  stepper.quick_stop();
  stepper.synchronize();
  set_current_from_steppers_for_axis(ALL_AXES);
  SYNC_PLAN_POSITION_KINEMATIC();
}

#if HAS_LEVELING
  /**
   * M420: Enable/Disable Bed Leveling and/or set the Z fade height.
   *
   *   S[bool]   Turns leveling on or off
   *   Z[height] Sets the Z fade height (0 or none to disable)
   *   V[bool]   Verbose - Print the leveling grid
   *
   * With AUTO_BED_LEVELING_UBL only:
   *
   *   L[index]  Load UBL mesh from index (0 is default)
   */
  inline void gcode_M420() {

    #if ENABLED(AUTO_BED_LEVELING_UBL)

      // L to load a mesh from the EEPROM
      if (parser.seen('L')) {

        #if ENABLED(EEPROM_SETTINGS)
          const int8_t storage_slot = parser.has_value() ? parser.value_int() : ubl.state.storage_slot;
          const int16_t a = settings.calc_num_meshes();

          if (!a) {
            SERIAL_PROTOCOLLNPGM("?EEPROM storage not available.");
            return;
          }

          if (!WITHIN(storage_slot, 0, a - 1)) {
            SERIAL_PROTOCOLLNPGM("?Invalid storage slot.");
            SERIAL_PROTOCOLLNPAIR("?Use 0 to ", a - 1);
            return;
          }

          settings.load_mesh(storage_slot);
          ubl.state.storage_slot = storage_slot;

        #else

          SERIAL_PROTOCOLLNPGM("?EEPROM storage not available.");
          return;

        #endif
      }

      // L to load a mesh from the EEPROM
      if (parser.seen('L') || parser.seen('V')) {
        ubl.display_map(0);  // Currently only supports one map type
        SERIAL_ECHOLNPAIR("UBL_MESH_VALID = ", UBL_MESH_VALID);
        SERIAL_ECHOLNPAIR("ubl.state.storage_slot = ", ubl.state.storage_slot);
      }

    #endif // AUTO_BED_LEVELING_UBL

    // V to print the matrix or mesh
    if (parser.seen('V')) {
      #if ABL_PLANAR
        planner.bed_level_matrix.debug(PSTR("Bed Level Correction Matrix:"));
      #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)
        if (leveling_is_valid()) {
          print_bilinear_leveling_grid();
          #if ENABLED(ABL_BILINEAR_SUBDIVISION)
            bed_level_virt_print();
          #endif
        }
      #elif ENABLED(MESH_BED_LEVELING)
        if (leveling_is_valid()) {
          SERIAL_ECHOLNPGM("Mesh Bed Level data:");
          mbl_mesh_report();
        }
      #endif
    }

    const bool to_enable = parser.boolval('S');
    if (parser.seen('S'))
      set_bed_leveling_enabled(to_enable);

    #if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
      if (parser.seen('Z')) set_z_fade_height(parser.value_linear_units());
    #endif

    const bool new_status = leveling_is_active();

    if (to_enable && !new_status) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM(MSG_ERR_M420_FAILED);
    }

    SERIAL_ECHO_START();
    SERIAL_ECHOLNPAIR("Bed Leveling ", new_status ? MSG_ON : MSG_OFF);

    #if ENABLED(ENABLE_LEVELING_FADE_HEIGHT)
      SERIAL_ECHO_START();
      SERIAL_ECHOPGM("Fade Height ");
      if (planner.z_fade_height > 0.0)
        SERIAL_ECHOLN(planner.z_fade_height);
      else
        SERIAL_ECHOLNPGM(MSG_OFF);
    #endif
  }
#endif

#if ENABLED(MESH_BED_LEVELING)

  /**
   * M421: Set a single Mesh Bed Leveling Z coordinate
   *
   * Usage:
   *   M421 X<linear> Y<linear> Z<linear>
   *   M421 X<linear> Y<linear> Q<offset>
   *   M421 I<xindex> J<yindex> Z<linear>
   *   M421 I<xindex> J<yindex> Q<offset>
   */
  inline void gcode_M421() {
    const bool hasX = parser.seen('X'), hasI = parser.seen('I');
    const int8_t ix = hasI ? parser.value_int() : hasX ? mbl.probe_index_x(RAW_X_POSITION(parser.value_linear_units())) : -1;
    const bool hasY = parser.seen('Y'), hasJ = parser.seen('J');
    const int8_t iy = hasJ ? parser.value_int() : hasY ? mbl.probe_index_y(RAW_Y_POSITION(parser.value_linear_units())) : -1;
    const bool hasZ = parser.seen('Z'), hasQ = !hasZ && parser.seen('Q');

    if (int(hasI && hasJ) + int(hasX && hasY) != 1 || !(hasZ || hasQ)) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM(MSG_ERR_M421_PARAMETERS);
    }
    else if (ix < 0 || iy < 0) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM(MSG_ERR_MESH_XY);
    }
    else
      mbl.set_z(ix, iy, parser.value_linear_units() + (hasQ ? mbl.z_values[ix][iy] : 0));
  }

#elif ENABLED(AUTO_BED_LEVELING_BILINEAR)

  /**
   * M421: Set a single Mesh Bed Leveling Z coordinate
   *
   * Usage:
   *   M421 I<xindex> J<yindex> Z<linear>
   *   M421 I<xindex> J<yindex> Q<offset>
   */
  inline void gcode_M421() {
    int8_t ix = parser.intval('I', -1), iy = parser.intval('J', -1);
    const bool hasI = ix >= 0,
               hasJ = iy >= 0,
               hasZ = parser.seen('Z'),
               hasQ = !hasZ && parser.seen('Q');

    if (!hasI || !hasJ || !(hasZ || hasQ)) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM(MSG_ERR_M421_PARAMETERS);
    }
    else if (!WITHIN(ix, 0, GRID_MAX_POINTS_X - 1) || !WITHIN(iy, 0, GRID_MAX_POINTS_Y - 1)) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM(MSG_ERR_MESH_XY);
    }
    else {
      z_values[ix][iy] = parser.value_linear_units() + (hasQ ? z_values[ix][iy] : 0);
      #if ENABLED(ABL_BILINEAR_SUBDIVISION)
        bed_level_virt_interpolate();
      #endif
    }
  }

#elif ENABLED(AUTO_BED_LEVELING_UBL)

  /**
   * M421: Set a single Mesh Bed Leveling Z coordinate
   *
   * Usage:
   *   M421 I<xindex> J<yindex> Z<linear>
   *   M421 I<xindex> J<yindex> Q<offset>
   *   M421 C Z<linear>
   *   M421 C Q<offset>
   */
  inline void gcode_M421() {
    int8_t ix = parser.intval('I', -1), iy = parser.intval('J', -1);
    const bool hasI = ix >= 0,
               hasJ = iy >= 0,
               hasC = parser.seen('C'),
               hasZ = parser.seen('Z'),
               hasQ = !hasZ && parser.seen('Q');

    if (hasC) {
      const mesh_index_pair location = ubl.find_closest_mesh_point_of_type(REAL, current_position[X_AXIS], current_position[Y_AXIS], USE_NOZZLE_AS_REFERENCE, NULL, false);
      ix = location.x_index;
      iy = location.y_index;
    }

    if (int(hasC) + int(hasI && hasJ) != 1 || !(hasZ || hasQ)) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM(MSG_ERR_M421_PARAMETERS);
    }
    else if (!WITHIN(ix, 0, GRID_MAX_POINTS_X - 1) || !WITHIN(iy, 0, GRID_MAX_POINTS_Y - 1)) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM(MSG_ERR_MESH_XY);
    }
    else
      ubl.z_values[ix][iy] = parser.value_linear_units() + (hasQ ? ubl.z_values[ix][iy] : 0);
  }

#endif // AUTO_BED_LEVELING_UBL

#if HAS_M206_COMMAND

  /**
   * M428: Set home_offset based on the distance between the
   *       current_position and the nearest "reference point."
   *       If an axis is past center its endstop position
   *       is the reference-point. Otherwise it uses 0. This allows
   *       the Z offset to be set near the bed when using a max endstop.
   *
   *       M428 can't be used more than 2cm away from 0 or an endstop.
   *
   *       Use M206 to set these values directly.
   */
  inline void gcode_M428() {
    bool err = false;
    LOOP_XYZ(i) {
      if (axis_homed[i]) {
        const float base = (current_position[i] > (soft_endstop_min[i] + soft_endstop_max[i]) * 0.5) ? base_home_pos((AxisEnum)i) : 0,
                    diff = base - RAW_POSITION(current_position[i], i);
        if (WITHIN(diff, -20, 20)) {
          set_home_offset((AxisEnum)i, diff);
        }
        else {
          SERIAL_ERROR_START();
          SERIAL_ERRORLNPGM(MSG_ERR_M428_TOO_FAR);
          LCD_ALERTMESSAGEPGM("Err: Too far!");
          BUZZ(200, 40);
          err = true;
          break;
        }
      }
    }

    if (!err) {
      SYNC_PLAN_POSITION_KINEMATIC();
      report_current_position();
      LCD_MESSAGEPGM(MSG_HOME_OFFSETS_APPLIED);
      BUZZ(100, 659);
      BUZZ(100, 698);
    }
  }

#endif // HAS_M206_COMMAND

/**
 * M500: Store settings in EEPROM
 */
inline void gcode_M500() {
  (void)settings.save();
}

/**
 * M501: Read settings from EEPROM
 */
inline void gcode_M501() {
  (void)settings.load();
}

/**
 * M502: Revert to default settings
 */
inline void gcode_M502() {
  (void)settings.reset();
}

#if DISABLED(DISABLE_M503)
  /**
   * M503: print settings currently in memory
   */
  inline void gcode_M503() {
    (void)settings.report(!parser.boolval('S', true));
  }
#endif

#if ENABLED(ABORT_ON_ENDSTOP_HIT_FEATURE_ENABLED)

  /**
   * M540: Set whether SD card print should abort on endstop hit (M540 S<0|1>)
   */
  inline void gcode_M540() {
    if (parser.seen('S')) stepper.abort_on_endstop_hit = parser.value_bool();
  }

#endif // ABORT_ON_ENDSTOP_HIT_FEATURE_ENABLED

#if HAS_BED_PROBE

  void refresh_zprobe_zoffset(const bool no_babystep/*=false*/) {
    static float last_zoffset = NAN;

    if (!isnan(last_zoffset)) {

      #if ENABLED(AUTO_BED_LEVELING_BILINEAR) || ENABLED(BABYSTEP_ZPROBE_OFFSET) || ENABLED(DELTA)
        const float diff = zprobe_zoffset - last_zoffset;
      #endif

      #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
        // Correct bilinear grid for new probe offset
        if (diff) {
          for (uint8_t x = 0; x < GRID_MAX_POINTS_X; x++)
            for (uint8_t y = 0; y < GRID_MAX_POINTS_Y; y++)
              z_values[x][y] -= diff;
        }
        #if ENABLED(ABL_BILINEAR_SUBDIVISION)
          bed_level_virt_interpolate();
        #endif
      #endif

      #if ENABLED(BABYSTEP_ZPROBE_OFFSET)
        if (!no_babystep && leveling_is_active())
          thermalManager.babystep_axis(Z_AXIS, -LROUND(diff * planner.axis_steps_per_mm[Z_AXIS]));
      #else
        UNUSED(no_babystep);
      #endif

      #if ENABLED(DELTA) // correct the delta_height
        home_offset[Z_AXIS] -= diff;
      #endif
    }

    last_zoffset = zprobe_zoffset;
  }

  inline void gcode_M851() {
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM(MSG_ZPROBE_ZOFFSET " ");
    if (parser.seen('Z')) {
      const float value = parser.value_linear_units();
      if (WITHIN(value, Z_PROBE_OFFSET_RANGE_MIN, Z_PROBE_OFFSET_RANGE_MAX)) {
        zprobe_zoffset = value;
        refresh_zprobe_zoffset();
        SERIAL_ECHO(zprobe_zoffset);
      }
      else
        SERIAL_ECHOPGM(MSG_Z_MIN " " STRINGIFY(Z_PROBE_OFFSET_RANGE_MIN) " " MSG_Z_MAX " " STRINGIFY(Z_PROBE_OFFSET_RANGE_MAX));
    }
    else
      SERIAL_ECHOPAIR(": ", zprobe_zoffset);

    SERIAL_EOL();
  }

#endif // HAS_BED_PROBE

#if ENABLED(ADVANCED_PAUSE_FEATURE)

  /**
   * M600: Pause for filament change
   *
   *  E[distance] - Retract the filament this far (negative value)
   *  Z[distance] - Move the Z axis by this distance
   *  X[position] - Move to this X position, with Y
   *  Y[position] - Move to this Y position, with X
   *  U[distance] - Retract distance for removal (negative value) (manual reload)
   *  L[distance] - Extrude distance for insertion (positive value) (manual reload)
   *  B[count]    - Number of times to beep, -1 for indefinite (if equipped with a buzzer)
   *
   *  Default values are used for omitted arguments.
   *
   */
  inline void gcode_M600() {

    #if ENABLED(HOME_BEFORE_FILAMENT_CHANGE)
      // Don't allow filament change without homing first
      if (axis_unhomed_error()) home_all_axes();
    #endif

    // Initial retract before move to filament change position
    const float retract = parser.seen('E') ? parser.value_axis_units(E_AXIS) : 0
      #if defined(PAUSE_PARK_RETRACT_LENGTH) && PAUSE_PARK_RETRACT_LENGTH > 0
        - (PAUSE_PARK_RETRACT_LENGTH)
      #endif
    ;

    // Lift Z axis
    const float z_lift = parser.linearval('Z', 0
      #if defined(PAUSE_PARK_Z_ADD) && PAUSE_PARK_Z_ADD > 0
        + PAUSE_PARK_Z_ADD
      #endif
    );

    // Move XY axes to filament exchange position
    const float x_pos = parser.linearval('X', 0
      #ifdef PAUSE_PARK_X_POS
        + PAUSE_PARK_X_POS
      #endif
    );
    const float y_pos = parser.linearval('Y', 0
      #ifdef PAUSE_PARK_Y_POS
        + PAUSE_PARK_Y_POS
      #endif
    );

    // Unload filament
    const float unload_length = parser.seen('U') ? parser.value_axis_units(E_AXIS) : 0
      #if defined(FILAMENT_CHANGE_UNLOAD_LENGTH) && FILAMENT_CHANGE_UNLOAD_LENGTH > 0
        - (FILAMENT_CHANGE_UNLOAD_LENGTH)
      #endif
    ;

    // Load filament
    const float load_length = parser.seen('L') ? parser.value_axis_units(E_AXIS) : 0
      #ifdef FILAMENT_CHANGE_LOAD_LENGTH
        + FILAMENT_CHANGE_LOAD_LENGTH
      #endif
    ;

    const int beep_count = parser.intval('B',
      #ifdef FILAMENT_CHANGE_NUMBER_OF_ALERT_BEEPS
        FILAMENT_CHANGE_NUMBER_OF_ALERT_BEEPS
      #else
        -1
      #endif
    );

    const bool job_running = print_job_timer.isRunning();

    if (pause_print(retract, z_lift, x_pos, y_pos, unload_length, beep_count, true)) {
      wait_for_filament_reload(beep_count);
      resume_print(load_length, ADVANCED_PAUSE_EXTRUDE_LENGTH, beep_count);
    }

    // Resume the print job timer if it was running
    if (job_running) print_job_timer.start();
  }

#endif // ADVANCED_PAUSE_FEATURE

#if ENABLED(MK2_MULTIPLEXER)

  inline void select_multiplexed_stepper(const uint8_t e) {
    stepper.synchronize();
    disable_e_steppers();
    WRITE(E_MUX0_PIN, TEST(e, 0) ? HIGH : LOW);
    WRITE(E_MUX1_PIN, TEST(e, 1) ? HIGH : LOW);
    WRITE(E_MUX2_PIN, TEST(e, 2) ? HIGH : LOW);
    safe_delay(100);
  }

  /**
   * M702: Unload all extruders
   */
  inline void gcode_M702() {
    for (uint8_t s = 0; s < E_STEPPERS; s++) {
      select_multiplexed_stepper(e);
      // TODO: standard unload filament function
      // MK2 firmware behavior:
      //  - Make sure temperature is high enough
      //  - Raise Z to at least 15 to make room
      //  - Extrude 1cm of filament in 1 second
      //  - Under 230C quickly purge ~12mm, over 230C purge ~10mm
      //  - Change E max feedrate to 80, eject the filament from the tube. Sync.
      //  - Restore E max feedrate to 50
    }
    // Go back to the last active extruder
    select_multiplexed_stepper(active_extruder);
    disable_e_steppers();
  }

#endif // MK2_MULTIPLEXER

#if ENABLED(DUAL_X_CARRIAGE)

  /**
   * M605: Set dual x-carriage movement mode
   *
   *    M605 S0: Full control mode. The slicer has full control over x-carriage movement
   *    M605 S1: Auto-park mode. The inactive head will auto park/unpark without slicer involvement
   *    M605 S2 [Xnnn] [Rmmm]: Duplication mode. The second extruder will duplicate the first with nnn
   *                         units x-offset and an optional differential hotend temperature of
   *                         mmm degrees. E.g., with "M605 S2 X100 R2" the second extruder will duplicate
   *                         the first with a spacing of 100mm in the x direction and 2 degrees hotter.
   *
   *    Note: the X axis should be homed after changing dual x-carriage mode.
   */
  inline void gcode_M605() {
    stepper.synchronize();
    if (parser.seen('S')) dual_x_carriage_mode = (DualXMode)parser.value_byte();
    switch (dual_x_carriage_mode) {
      case DXC_FULL_CONTROL_MODE:
      case DXC_AUTO_PARK_MODE:
        break;
      case DXC_DUPLICATION_MODE:
        if (parser.seen('X')) duplicate_extruder_x_offset = max(parser.value_linear_units(), X2_MIN_POS - x_home_pos(0));
        if (parser.seen('R')) duplicate_extruder_temp_offset = parser.value_celsius_diff();
        SERIAL_ECHO_START();
        SERIAL_ECHOPGM(MSG_HOTEND_OFFSET);
        SERIAL_CHAR(' ');
        SERIAL_ECHO(hotend_offset[X_AXIS][0]);
        SERIAL_CHAR(',');
        SERIAL_ECHO(hotend_offset[Y_AXIS][0]);
        SERIAL_CHAR(' ');
        SERIAL_ECHO(duplicate_extruder_x_offset);
        SERIAL_CHAR(',');
        SERIAL_ECHOLN(hotend_offset[Y_AXIS][1]);
        break;
      default:
        dual_x_carriage_mode = DEFAULT_DUAL_X_CARRIAGE_MODE;
        break;
    }
    active_extruder_parked = false;
    extruder_duplication_enabled = false;
    delayed_move_time = 0;
  }

#elif ENABLED(DUAL_NOZZLE_DUPLICATION_MODE)

  inline void gcode_M605() {
    stepper.synchronize();
    extruder_duplication_enabled = parser.intval('S') == (int)DXC_DUPLICATION_MODE;
    SERIAL_ECHO_START();
    SERIAL_ECHOLNPAIR(MSG_DUPLICATION_MODE, extruder_duplication_enabled ? MSG_ON : MSG_OFF);
  }

#endif // DUAL_NOZZLE_DUPLICATION_MODE

#if ENABLED(LIN_ADVANCE)
  /**
   * M900: Set and/or Get advance K factor and WH/D ratio
   *
   *  K<factor>                  Set advance K factor
   *  R<ratio>                   Set ratio directly (overrides WH/D)
   *  W<width> H<height> D<diam> Set ratio from WH/D
   */
  inline void gcode_M900() {
    stepper.synchronize();

    const float newK = parser.floatval('K', -1);
    if (newK >= 0) planner.extruder_advance_k = newK;

    float newR = parser.floatval('R', -1);
    if (newR < 0) {
      const float newD = parser.floatval('D', -1),
                  newW = parser.floatval('W', -1),
                  newH = parser.floatval('H', -1);
      if (newD >= 0 && newW >= 0 && newH >= 0)
        newR = newD ? (newW * newH) / (sq(newD * 0.5) * M_PI) : 0;
    }
    if (newR >= 0) planner.advance_ed_ratio = newR;

    SERIAL_ECHO_START();
    SERIAL_ECHOPAIR("Advance K=", planner.extruder_advance_k);
    SERIAL_ECHOPGM(" E/D=");
    const float ratio = planner.advance_ed_ratio;
    if (ratio) SERIAL_ECHO(ratio); else SERIAL_ECHOPGM("Auto");
    SERIAL_EOL();
  }
#endif // LIN_ADVANCE

#if ENABLED(HAVE_TMC2130)

  static void tmc2130_get_current(TMC2130Stepper &st, const char name) {
    SERIAL_CHAR(name);
    SERIAL_ECHOPGM(" axis driver current: ");
    SERIAL_ECHOLN(st.getCurrent());
  }
  static void tmc2130_set_current(TMC2130Stepper &st, const char name, const int mA) {
    st.setCurrent(mA, R_SENSE, HOLD_MULTIPLIER);
    tmc2130_get_current(st, name);
  }

  static void tmc2130_report_otpw(TMC2130Stepper &st, const char name) {
    SERIAL_CHAR(name);
    SERIAL_ECHOPGM(" axis temperature prewarn triggered: ");
    serialprintPGM(st.getOTPW() ? PSTR("true") : PSTR("false"));
    SERIAL_EOL();
  }
  static void tmc2130_clear_otpw(TMC2130Stepper &st, const char name) {
    st.clear_otpw();
    SERIAL_CHAR(name);
    SERIAL_ECHOLNPGM(" prewarn flag cleared");
  }

  static void tmc2130_get_pwmthrs(TMC2130Stepper &st, const char name, const uint16_t spmm) {
    SERIAL_CHAR(name);
    SERIAL_ECHOPGM(" stealthChop max speed set to ");
    SERIAL_ECHOLN(12650000UL * st.microsteps() / (256 * st.stealth_max_speed() * spmm));
  }
  static void tmc2130_set_pwmthrs(TMC2130Stepper &st, const char name, const int32_t thrs, const uint32_t spmm) {
    st.stealth_max_speed(12650000UL * st.microsteps() / (256 * thrs * spmm));
    tmc2130_get_pwmthrs(st, name, spmm);
  }

  static void tmc2130_get_sgt(TMC2130Stepper &st, const char name) {
    SERIAL_CHAR(name);
    SERIAL_ECHOPGM(" driver homing sensitivity set to ");
    SERIAL_ECHOLN(st.sgt());
  }
  static void tmc2130_set_sgt(TMC2130Stepper &st, const char name, const int8_t sgt_val) {
    st.sgt(sgt_val);
    tmc2130_get_sgt(st, name);
  }

  /**
   * M906: Set motor current in milliamps using axis codes X, Y, Z, E
   * Report driver currents when no axis specified
   *
   * S1: Enable automatic current control
   * S0: Disable
   */
  inline void gcode_M906() {
    uint16_t values[XYZE];
    LOOP_XYZE(i)
      values[i] = parser.intval(axis_codes[i]);

    #if ENABLED(X_IS_TMC2130)
      if (values[X_AXIS]) tmc2130_set_current(stepperX, 'X', values[X_AXIS]);
      else tmc2130_get_current(stepperX, 'X');
    #endif
    #if ENABLED(Y_IS_TMC2130)
      if (values[Y_AXIS]) tmc2130_set_current(stepperY, 'Y', values[Y_AXIS]);
      else tmc2130_get_current(stepperY, 'Y');
    #endif
    #if ENABLED(Z_IS_TMC2130)
      if (values[Z_AXIS]) tmc2130_set_current(stepperZ, 'Z', values[Z_AXIS]);
      else tmc2130_get_current(stepperZ, 'Z');
    #endif
    #if ENABLED(E0_IS_TMC2130)
      if (values[E_AXIS]) tmc2130_set_current(stepperE0, 'E', values[E_AXIS]);
      else tmc2130_get_current(stepperE0, 'E');
    #endif

    #if ENABLED(AUTOMATIC_CURRENT_CONTROL)
      if (parser.seen('S')) auto_current_control = parser.value_bool();
    #endif
  }

  /**
   * M911: Report TMC2130 stepper driver overtemperature pre-warn flag
   * The flag is held by the library and persist until manually cleared by M912
   */
  inline void gcode_M911() {
    const bool reportX = parser.seen('X'), reportY = parser.seen('Y'), reportZ = parser.seen('Z'), reportE = parser.seen('E'),
             reportAll = (!reportX && !reportY && !reportZ && !reportE) || (reportX && reportY && reportZ && reportE);
    #if ENABLED(X_IS_TMC2130)
      if (reportX || reportAll) tmc2130_report_otpw(stepperX, 'X');
    #endif
    #if ENABLED(Y_IS_TMC2130)
      if (reportY || reportAll) tmc2130_report_otpw(stepperY, 'Y');
    #endif
    #if ENABLED(Z_IS_TMC2130)
      if (reportZ || reportAll) tmc2130_report_otpw(stepperZ, 'Z');
    #endif
    #if ENABLED(E0_IS_TMC2130)
      if (reportE || reportAll) tmc2130_report_otpw(stepperE0, 'E');
    #endif
  }

  /**
   * M912: Clear TMC2130 stepper driver overtemperature pre-warn flag held by the library
   */
  inline void gcode_M912() {
    const bool clearX = parser.seen('X'), clearY = parser.seen('Y'), clearZ = parser.seen('Z'), clearE = parser.seen('E'),
             clearAll = (!clearX && !clearY && !clearZ && !clearE) || (clearX && clearY && clearZ && clearE);
    #if ENABLED(X_IS_TMC2130)
      if (clearX || clearAll) tmc2130_clear_otpw(stepperX, 'X');
    #endif
    #if ENABLED(Y_IS_TMC2130)
      if (clearY || clearAll) tmc2130_clear_otpw(stepperY, 'Y');
    #endif
    #if ENABLED(Z_IS_TMC2130)
      if (clearZ || clearAll) tmc2130_clear_otpw(stepperZ, 'Z');
    #endif
    #if ENABLED(E0_IS_TMC2130)
      if (clearE || clearAll) tmc2130_clear_otpw(stepperE0, 'E');
    #endif
  }

  /**
   * M913: Set HYBRID_THRESHOLD speed.
   */
  #if ENABLED(HYBRID_THRESHOLD)
    inline void gcode_M913() {
      uint16_t values[XYZE];
      LOOP_XYZE(i)
        values[i] = parser.intval(axis_codes[i]);

      #if ENABLED(X_IS_TMC2130)
        if (values[X_AXIS]) tmc2130_set_pwmthrs(stepperX, 'X', values[X_AXIS], planner.axis_steps_per_mm[X_AXIS]);
        else tmc2130_get_pwmthrs(stepperX, 'X', planner.axis_steps_per_mm[X_AXIS]);
      #endif
      #if ENABLED(Y_IS_TMC2130)
        if (values[Y_AXIS]) tmc2130_set_pwmthrs(stepperY, 'Y', values[Y_AXIS], planner.axis_steps_per_mm[Y_AXIS]);
        else tmc2130_get_pwmthrs(stepperY, 'Y', planner.axis_steps_per_mm[Y_AXIS]);
      #endif
      #if ENABLED(Z_IS_TMC2130)
        if (values[Z_AXIS]) tmc2130_set_pwmthrs(stepperZ, 'Z', values[Z_AXIS], planner.axis_steps_per_mm[Z_AXIS]);
        else tmc2130_get_pwmthrs(stepperZ, 'Z', planner.axis_steps_per_mm[Z_AXIS]);
      #endif
      #if ENABLED(E0_IS_TMC2130)
        if (values[E_AXIS]) tmc2130_set_pwmthrs(stepperE0, 'E', values[E_AXIS], planner.axis_steps_per_mm[E_AXIS]);
        else tmc2130_get_pwmthrs(stepperE0, 'E', planner.axis_steps_per_mm[E_AXIS]);
      #endif
    }
  #endif // HYBRID_THRESHOLD

  /**
   * M914: Set SENSORLESS_HOMING sensitivity.
   */
  #if ENABLED(SENSORLESS_HOMING)
    inline void gcode_M914() {
      #if ENABLED(X_IS_TMC2130)
        if (parser.seen(axis_codes[X_AXIS])) tmc2130_set_sgt(stepperX, 'X', parser.value_int());
        else tmc2130_get_sgt(stepperX, 'X');
      #endif
      #if ENABLED(Y_IS_TMC2130)
        if (parser.seen(axis_codes[Y_AXIS])) tmc2130_set_sgt(stepperY, 'Y', parser.value_int());
        else tmc2130_get_sgt(stepperY, 'Y');
      #endif
    }
  #endif // SENSORLESS_HOMING

#endif // HAVE_TMC2130

/**
 * M907: Set digital trimpot motor current using axis codes X, Y, Z, E, B, S
 */
inline void gcode_M907() {
  #if HAS_DIGIPOTSS

    LOOP_XYZE(i) if (parser.seen(axis_codes[i])) stepper.digipot_current(i, parser.value_int());
    if (parser.seen('B')) stepper.digipot_current(4, parser.value_int());
    if (parser.seen('S')) for (uint8_t i = 0; i <= 4; i++) stepper.digipot_current(i, parser.value_int());

  #elif HAS_MOTOR_CURRENT_PWM

    #if PIN_EXISTS(MOTOR_CURRENT_PWM_XY)
      if (parser.seen('X')) stepper.digipot_current(0, parser.value_int());
    #endif
    #if PIN_EXISTS(MOTOR_CURRENT_PWM_Z)
      if (parser.seen('Z')) stepper.digipot_current(1, parser.value_int());
    #endif
    #if PIN_EXISTS(MOTOR_CURRENT_PWM_E)
      if (parser.seen('E')) stepper.digipot_current(2, parser.value_int());
    #endif

  #endif

  #if ENABLED(DIGIPOT_I2C)
    // this one uses actual amps in floating point
    LOOP_XYZE(i) if (parser.seen(axis_codes[i])) digipot_i2c_set_current(i, parser.value_float());
    // for each additional extruder (named B,C,D,E..., channels 4,5,6,7...)
    for (uint8_t i = NUM_AXIS; i < DIGIPOT_I2C_NUM_CHANNELS; i++) if (parser.seen('B' + i - (NUM_AXIS))) digipot_i2c_set_current(i, parser.value_float());
  #endif

  #if ENABLED(DAC_STEPPER_CURRENT)
    if (parser.seen('S')) {
      const float dac_percent = parser.value_float();
      for (uint8_t i = 0; i <= 4; i++) dac_current_percent(i, dac_percent);
    }
    LOOP_XYZE(i) if (parser.seen(axis_codes[i])) dac_current_percent(i, parser.value_float());
  #endif
}

#if HAS_DIGIPOTSS || ENABLED(DAC_STEPPER_CURRENT)

  /**
   * M908: Control digital trimpot directly (M908 P<pin> S<current>)
   */
  inline void gcode_M908() {
    #if HAS_DIGIPOTSS
      stepper.digitalPotWrite(
        parser.intval('P'),
        parser.intval('S')
      );
    #endif
    #ifdef DAC_STEPPER_CURRENT
      dac_current_raw(
        parser.byteval('P', -1),
        parser.ushortval('S', 0)
      );
    #endif
  }

  #if ENABLED(DAC_STEPPER_CURRENT) // As with Printrbot RevF

    inline void gcode_M909() { dac_print_values(); }

    inline void gcode_M910() { dac_commit_eeprom(); }

  #endif

#endif // HAS_DIGIPOTSS || DAC_STEPPER_CURRENT

#if HAS_MICROSTEPS

  // M350 Set microstepping mode. Warning: Steps per unit remains unchanged. S code sets stepping mode for all drivers.
  inline void gcode_M350() {
    if (parser.seen('S')) for (int i = 0; i <= 4; i++) stepper.microstep_mode(i, parser.value_byte());
    LOOP_XYZE(i) if (parser.seen(axis_codes[i])) stepper.microstep_mode(i, parser.value_byte());
    if (parser.seen('B')) stepper.microstep_mode(4, parser.value_byte());
    stepper.microstep_readings();
  }

  /**
   * M351: Toggle MS1 MS2 pins directly with axis codes X Y Z E B
   *       S# determines MS1 or MS2, X# sets the pin high/low.
   */
  inline void gcode_M351() {
    if (parser.seenval('S')) switch (parser.value_byte()) {
      case 1:
        LOOP_XYZE(i) if (parser.seenval(axis_codes[i])) stepper.microstep_ms(i, parser.value_byte(), -1);
        if (parser.seenval('B')) stepper.microstep_ms(4, parser.value_byte(), -1);
        break;
      case 2:
        LOOP_XYZE(i) if (parser.seenval(axis_codes[i])) stepper.microstep_ms(i, -1, parser.value_byte());
        if (parser.seenval('B')) stepper.microstep_ms(4, -1, parser.value_byte());
        break;
    }
    stepper.microstep_readings();
  }

#endif // HAS_MICROSTEPS

#if HAS_CASE_LIGHT
  #ifndef INVERT_CASE_LIGHT
    #define INVERT_CASE_LIGHT false
  #endif
  int case_light_brightness;  // LCD routine wants INT
  bool case_light_on;

  void update_case_light() {
    pinMode(CASE_LIGHT_PIN, OUTPUT); // digitalWrite doesn't set the port mode
    uint8_t case_light_bright = (uint8_t)case_light_brightness;
    if (case_light_on) {
      if (USEABLE_HARDWARE_PWM(CASE_LIGHT_PIN)) {
        analogWrite(CASE_LIGHT_PIN, INVERT_CASE_LIGHT ? 255 - case_light_brightness : case_light_brightness );
      }
      else digitalWrite(CASE_LIGHT_PIN, INVERT_CASE_LIGHT ? LOW : HIGH );
    }
    else digitalWrite(CASE_LIGHT_PIN, INVERT_CASE_LIGHT ? HIGH : LOW);
  }
#endif // HAS_CASE_LIGHT

/**
 * M355: Turn case light on/off and set brightness
 *
 *   P<byte>  Set case light brightness (PWM pin required - ignored otherwise)
 *
 *   S<bool>  Set case light on/off
 *
 *   When S turns on the light on a PWM pin then the current brightness level is used/restored
 *
 *   M355 P200 S0 turns off the light & sets the brightness level
 *   M355 S1 turns on the light with a brightness of 200 (assuming a PWM pin)
 */
inline void gcode_M355() {
  #if HAS_CASE_LIGHT
    uint8_t args = 0;
    if (parser.seenval('P')) ++args, case_light_brightness = parser.value_byte();
    if (parser.seenval('S')) ++args, case_light_on = parser.value_bool();
    if (args) update_case_light();

    // always report case light status
    SERIAL_ECHO_START();
    if (!case_light_on) {
      SERIAL_ECHOLN("Case light: off");
    }
    else {
      if (!USEABLE_HARDWARE_PWM(CASE_LIGHT_PIN)) SERIAL_ECHOLN("Case light: on");
      else SERIAL_ECHOLNPAIR("Case light: ", case_light_brightness);
    }

  #else
    SERIAL_ERROR_START();
    SERIAL_ERRORLNPGM(MSG_ERR_M355_NONE);
  #endif // HAS_CASE_LIGHT
}

#if ENABLED(MIXING_EXTRUDER)

  /**
   * M163: Set a single mix factor for a mixing extruder
   *       This is called "weight" by some systems.
   *
   *   S[index]   The channel index to set
   *   P[float]   The mix value
   *
   */
  inline void gcode_M163() {
    const int mix_index = parser.intval('S');
    if (mix_index < MIXING_STEPPERS) {
      float mix_value = parser.floatval('P');
      NOLESS(mix_value, 0.0);
      mixing_factor[mix_index] = RECIPROCAL(mix_value);
    }
  }

  #if MIXING_VIRTUAL_TOOLS > 1

    /**
     * M164: Store the current mix factors as a virtual tool.
     *
     *   S[index]   The virtual tool to store
     *
     */
    inline void gcode_M164() {
      const int tool_index = parser.intval('S');
      if (tool_index < MIXING_VIRTUAL_TOOLS) {
        normalize_mix();
        for (uint8_t i = 0; i < MIXING_STEPPERS; i++)
          mixing_virtual_tool_mix[tool_index][i] = mixing_factor[i];
      }
    }

  #endif

  #if ENABLED(DIRECT_MIXING_IN_G1)
    /**
     * M165: Set multiple mix factors for a mixing extruder.
     *       Factors that are left out will be set to 0.
     *       All factors together must add up to 1.0.
     *
     *   A[factor] Mix factor for extruder stepper 1
     *   B[factor] Mix factor for extruder stepper 2
     *   C[factor] Mix factor for extruder stepper 3
     *   D[factor] Mix factor for extruder stepper 4
     *   H[factor] Mix factor for extruder stepper 5
     *   I[factor] Mix factor for extruder stepper 6
     *
     */
    inline void gcode_M165() { gcode_get_mix(); }
  #endif

#endif // MIXING_EXTRUDER

/**
 * M999: Restart after being stopped
 *
 * Default behaviour is to flush the serial buffer and request
 * a resend to the host starting on the last N line received.
 *
 * Sending "M999 S1" will resume printing without flushing the
 * existing command buffer.
 *
 */
inline void gcode_M999() {
  Running = true;
  lcd_reset_alert_level();

  if (parser.boolval('S')) return;

  // gcode_LastN = Stopped_gcode_LastN;
  FlushSerialRequestResend();
}

#if ENABLED(SWITCHING_EXTRUDER)
  #if EXTRUDERS > 3
    #define REQ_ANGLES 4
    #define _SERVO_NR (e < 2 ? SWITCHING_EXTRUDER_SERVO_NR : SWITCHING_EXTRUDER_E23_SERVO_NR)
  #else
    #define REQ_ANGLES 2
    #define _SERVO_NR SWITCHING_EXTRUDER_SERVO_NR
  #endif
  inline void move_extruder_servo(const uint8_t e) {
    constexpr int16_t angles[] = SWITCHING_EXTRUDER_SERVO_ANGLES;
    static_assert(COUNT(angles) == REQ_ANGLES, "SWITCHING_EXTRUDER_SERVO_ANGLES needs " STRINGIFY(REQ_ANGLES) " angles.");
    stepper.synchronize();
    #if EXTRUDERS & 1
      if (e < EXTRUDERS - 1)
    #endif
    {
      MOVE_SERVO(_SERVO_NR, angles[e]);
      safe_delay(500);
    }
  }
#endif // SWITCHING_EXTRUDER

#if ENABLED(SWITCHING_NOZZLE)
  inline void move_nozzle_servo(const uint8_t e) {
    const int16_t angles[2] = SWITCHING_NOZZLE_SERVO_ANGLES;
    stepper.synchronize();
    MOVE_SERVO(SWITCHING_NOZZLE_SERVO_NR, angles[e]);
    safe_delay(500);
  }
#endif

inline void invalid_extruder_error(const uint8_t e) {
  SERIAL_ECHO_START();
  SERIAL_CHAR('T');
  SERIAL_ECHO_F(e, DEC);
  SERIAL_CHAR(' ');
  SERIAL_ECHOLN(MSG_INVALID_EXTRUDER);
}

/**
 * Perform a tool-change, which may result in moving the
 * previous tool out of the way and the new tool into place.
 */
void tool_change(const uint8_t tmp_extruder, const float fr_mm_s/*=0.0*/, bool no_move/*=false*/) {
  #if ENABLED(MIXING_EXTRUDER) && MIXING_VIRTUAL_TOOLS > 1

    if (tmp_extruder >= MIXING_VIRTUAL_TOOLS)
      return invalid_extruder_error(tmp_extruder);

    // T0-Tnnn: Switch virtual tool by changing the mix
    for (uint8_t j = 0; j < MIXING_STEPPERS; j++)
      mixing_factor[j] = mixing_virtual_tool_mix[tmp_extruder][j];

  #else // !MIXING_EXTRUDER || MIXING_VIRTUAL_TOOLS <= 1

    if (tmp_extruder >= EXTRUDERS)
      return invalid_extruder_error(tmp_extruder);

    #if HOTENDS > 1

      const float old_feedrate_mm_s = fr_mm_s > 0.0 ? fr_mm_s : feedrate_mm_s;

      feedrate_mm_s = fr_mm_s > 0.0 ? fr_mm_s : XY_PROBE_FEEDRATE_MM_S;

      if (tmp_extruder != active_extruder) {
        if (!no_move && axis_unhomed_error()) {
          SERIAL_ECHOLNPGM("No move on toolchange");
          no_move = true;
        }

        // Save current position to destination, for use later
        set_destination_to_current();

        #if ENABLED(DUAL_X_CARRIAGE)

          #if ENABLED(DEBUG_LEVELING_FEATURE)
            if (DEBUGGING(LEVELING)) {
              SERIAL_ECHOPGM("Dual X Carriage Mode ");
              switch (dual_x_carriage_mode) {
                case DXC_FULL_CONTROL_MODE: SERIAL_ECHOLNPGM("DXC_FULL_CONTROL_MODE"); break;
                case DXC_AUTO_PARK_MODE: SERIAL_ECHOLNPGM("DXC_AUTO_PARK_MODE"); break;
                case DXC_DUPLICATION_MODE: SERIAL_ECHOLNPGM("DXC_DUPLICATION_MODE"); break;
              }
            }
          #endif

          const float xhome = x_home_pos(active_extruder);
          if (dual_x_carriage_mode == DXC_AUTO_PARK_MODE
              && IsRunning()
              && (delayed_move_time || current_position[X_AXIS] != xhome)
          ) {
            float raised_z = current_position[Z_AXIS] + TOOLCHANGE_PARK_ZLIFT;
            #if ENABLED(MAX_SOFTWARE_ENDSTOPS)
              NOMORE(raised_z, soft_endstop_max[Z_AXIS]);
            #endif
            #if ENABLED(DEBUG_LEVELING_FEATURE)
              if (DEBUGGING(LEVELING)) {
                SERIAL_ECHOLNPAIR("Raise to ", raised_z);
                SERIAL_ECHOLNPAIR("MoveX to ", xhome);
                SERIAL_ECHOLNPAIR("Lower to ", current_position[Z_AXIS]);
              }
            #endif
            // Park old head: 1) raise 2) move to park position 3) lower
            for (uint8_t i = 0; i < 3; i++)
              planner.buffer_line(
                i == 0 ? current_position[X_AXIS] : xhome,
                current_position[Y_AXIS],
                i == 2 ? current_position[Z_AXIS] : raised_z,
                current_position[E_AXIS],
                planner.max_feedrate_mm_s[i == 1 ? X_AXIS : Z_AXIS],
                active_extruder
              );
            stepper.synchronize();
          }

          // Apply Y & Z extruder offset (X offset is used as home pos with Dual X)
          current_position[Y_AXIS] -= hotend_offset[Y_AXIS][active_extruder] - hotend_offset[Y_AXIS][tmp_extruder];
          current_position[Z_AXIS] -= hotend_offset[Z_AXIS][active_extruder] - hotend_offset[Z_AXIS][tmp_extruder];

          // Activate the new extruder
          active_extruder = tmp_extruder;

          // This function resets the max/min values - the current position may be overwritten below.
          set_axis_is_at_home(X_AXIS);

          #if ENABLED(DEBUG_LEVELING_FEATURE)
            if (DEBUGGING(LEVELING)) DEBUG_POS("New Extruder", current_position);
          #endif

          // Only when auto-parking are carriages safe to move
          if (dual_x_carriage_mode != DXC_AUTO_PARK_MODE) no_move = true;

          switch (dual_x_carriage_mode) {
            case DXC_FULL_CONTROL_MODE:
              // New current position is the position of the activated extruder
              current_position[X_AXIS] = LOGICAL_X_POSITION(inactive_extruder_x_pos);
              // Save the inactive extruder's position (from the old current_position)
              inactive_extruder_x_pos = RAW_X_POSITION(destination[X_AXIS]);
              break;
            case DXC_AUTO_PARK_MODE:
              // record raised toolhead position for use by unpark
              COPY(raised_parked_position, current_position);
              raised_parked_position[Z_AXIS] += TOOLCHANGE_UNPARK_ZLIFT;
              #if ENABLED(MAX_SOFTWARE_ENDSTOPS)
                NOMORE(raised_parked_position[Z_AXIS], soft_endstop_max[Z_AXIS]);
              #endif
              active_extruder_parked = true;
              delayed_move_time = 0;
              break;
            case DXC_DUPLICATION_MODE:
              // If the new extruder is the left one, set it "parked"
              // This triggers the second extruder to move into the duplication position
              active_extruder_parked = (active_extruder == 0);

              if (active_extruder_parked)
                current_position[X_AXIS] = LOGICAL_X_POSITION(inactive_extruder_x_pos);
              else
                current_position[X_AXIS] = destination[X_AXIS] + duplicate_extruder_x_offset;
              inactive_extruder_x_pos = RAW_X_POSITION(destination[X_AXIS]);
              extruder_duplication_enabled = false;
              #if ENABLED(DEBUG_LEVELING_FEATURE)
                if (DEBUGGING(LEVELING)) {
                  SERIAL_ECHOLNPAIR("Set inactive_extruder_x_pos=", inactive_extruder_x_pos);
                  SERIAL_ECHOLNPGM("Clear extruder_duplication_enabled");
                }
              #endif
              break;
          }

          #if ENABLED(DEBUG_LEVELING_FEATURE)
            if (DEBUGGING(LEVELING)) {
              SERIAL_ECHOLNPAIR("Active extruder parked: ", active_extruder_parked ? "yes" : "no");
              DEBUG_POS("New extruder (parked)", current_position);
            }
          #endif

          // No extra case for HAS_ABL in DUAL_X_CARRIAGE. Does that mean they don't work together?
        #else // !DUAL_X_CARRIAGE

          #if ENABLED(SWITCHING_NOZZLE)
            #define DONT_SWITCH (SWITCHING_EXTRUDER_SERVO_NR == SWITCHING_NOZZLE_SERVO_NR)
            // <0 if the new nozzle is higher, >0 if lower. A bigger raise when lower.
            const float z_diff = hotend_offset[Z_AXIS][active_extruder] - hotend_offset[Z_AXIS][tmp_extruder],
                        z_raise = 0.3 + (z_diff > 0.0 ? z_diff : 0.0);

            // Always raise by some amount (destination copied from current_position earlier)
            current_position[Z_AXIS] += z_raise;
            planner.buffer_line_kinematic(current_position, planner.max_feedrate_mm_s[Z_AXIS], active_extruder);
            move_nozzle_servo(tmp_extruder);
          #endif

          /**
           * Set current_position to the position of the new nozzle.
           * Offsets are based on linear distance, so we need to get
           * the resulting position in coordinate space.
           *
           * - With grid or 3-point leveling, offset XYZ by a tilted vector
           * - With mesh leveling, update Z for the new position
           * - Otherwise, just use the raw linear distance
           *
           * Software endstops are altered here too. Consider a case where:
           *   E0 at X=0 ... E1 at X=10
           * When we switch to E1 now X=10, but E1 can't move left.
           * To express this we apply the change in XY to the software endstops.
           * E1 can move farther right than E0, so the right limit is extended.
           *
           * Note that we don't adjust the Z software endstops. Why not?
           * Consider a case where Z=0 (here) and switching to E1 makes Z=1
           * because the bed is 1mm lower at the new position. As long as
           * the first nozzle is out of the way, the carriage should be
           * allowed to move 1mm lower. This technically "breaks" the
           * Z software endstop. But this is technically correct (and
           * there is no viable alternative).
           */
          #if ABL_PLANAR
            // Offset extruder, make sure to apply the bed level rotation matrix
            vector_3 tmp_offset_vec = vector_3(hotend_offset[X_AXIS][tmp_extruder],
                                               hotend_offset[Y_AXIS][tmp_extruder],
                                               0),
                     act_offset_vec = vector_3(hotend_offset[X_AXIS][active_extruder],
                                               hotend_offset[Y_AXIS][active_extruder],
                                               0),
                     offset_vec = tmp_offset_vec - act_offset_vec;

            #if ENABLED(DEBUG_LEVELING_FEATURE)
              if (DEBUGGING(LEVELING)) {
                tmp_offset_vec.debug(PSTR("tmp_offset_vec"));
                act_offset_vec.debug(PSTR("act_offset_vec"));
                offset_vec.debug(PSTR("offset_vec (BEFORE)"));
              }
            #endif

            offset_vec.apply_rotation(planner.bed_level_matrix.transpose(planner.bed_level_matrix));

            #if ENABLED(DEBUG_LEVELING_FEATURE)
              if (DEBUGGING(LEVELING)) offset_vec.debug(PSTR("offset_vec (AFTER)"));
            #endif

            // Adjustments to the current position
            const float xydiff[2] = { offset_vec.x, offset_vec.y };
            current_position[Z_AXIS] += offset_vec.z;

          #else // !ABL_PLANAR

            const float xydiff[2] = {
              hotend_offset[X_AXIS][tmp_extruder] - hotend_offset[X_AXIS][active_extruder],
              hotend_offset[Y_AXIS][tmp_extruder] - hotend_offset[Y_AXIS][active_extruder]
            };

            #if ENABLED(MESH_BED_LEVELING)

              if (leveling_is_active()) {
                #if ENABLED(DEBUG_LEVELING_FEATURE)
                  if (DEBUGGING(LEVELING)) SERIAL_ECHOPAIR("Z before MBL: ", current_position[Z_AXIS]);
                #endif
                float x2 = current_position[X_AXIS] + xydiff[X_AXIS],
                      y2 = current_position[Y_AXIS] + xydiff[Y_AXIS],
                      z1 = current_position[Z_AXIS], z2 = z1;
                planner.apply_leveling(current_position[X_AXIS], current_position[Y_AXIS], z1);
                planner.apply_leveling(x2, y2, z2);
                current_position[Z_AXIS] += z2 - z1;
                #if ENABLED(DEBUG_LEVELING_FEATURE)
                  if (DEBUGGING(LEVELING))
                    SERIAL_ECHOLNPAIR(" after: ", current_position[Z_AXIS]);
                #endif
              }

            #endif // MESH_BED_LEVELING

          #endif // !HAS_ABL

          #if ENABLED(DEBUG_LEVELING_FEATURE)
            if (DEBUGGING(LEVELING)) {
              SERIAL_ECHOPAIR("Offset Tool XY by { ", xydiff[X_AXIS]);
              SERIAL_ECHOPAIR(", ", xydiff[Y_AXIS]);
              SERIAL_ECHOLNPGM(" }");
            }
          #endif

          // The newly-selected extruder XY is actually at...
          current_position[X_AXIS] += xydiff[X_AXIS];
          current_position[Y_AXIS] += xydiff[Y_AXIS];
          #if HAS_WORKSPACE_OFFSET || ENABLED(DUAL_X_CARRIAGE)
            for (uint8_t i = X_AXIS; i <= Y_AXIS; i++) {
              #if HAS_POSITION_SHIFT
                position_shift[i] += xydiff[i];
              #endif
              update_software_endstops((AxisEnum)i);
            }
          #endif

          // Set the new active extruder
          active_extruder = tmp_extruder;

        #endif // !DUAL_X_CARRIAGE

        #if ENABLED(DEBUG_LEVELING_FEATURE)
          if (DEBUGGING(LEVELING)) DEBUG_POS("Sync After Toolchange", current_position);
        #endif

        // Tell the planner the new "current position"
        SYNC_PLAN_POSITION_KINEMATIC();

        // Move to the "old position" (move the extruder into place)
        if (!no_move && IsRunning()) {
          #if ENABLED(DEBUG_LEVELING_FEATURE)
            if (DEBUGGING(LEVELING)) DEBUG_POS("Move back", destination);
          #endif
          prepare_move_to_destination();
        }

        #if ENABLED(SWITCHING_NOZZLE)
          // Move back down, if needed. (Including when the new tool is higher.)
          if (z_raise != z_diff) {
            destination[Z_AXIS] += z_diff;
            feedrate_mm_s = planner.max_feedrate_mm_s[Z_AXIS];
            prepare_move_to_destination();
          }
        #endif

      } // (tmp_extruder != active_extruder)

      stepper.synchronize();

      #if ENABLED(EXT_SOLENOID)
        disable_all_solenoids();
        enable_solenoid_on_active_extruder();
      #endif // EXT_SOLENOID

      feedrate_mm_s = old_feedrate_mm_s;

    #else // HOTENDS <= 1

      UNUSED(fr_mm_s);
      UNUSED(no_move);

      #if ENABLED(SWITCHING_EXTRUDER) && !DONT_SWITCH

        stepper.synchronize();
        move_extruder_servo(tmp_extruder);

      #elif ENABLED(MK2_MULTIPLEXER)

        if (tmp_extruder >= E_STEPPERS)
          return invalid_extruder_error(tmp_extruder);

        select_multiplexed_stepper(tmp_extruder);

      #endif

    #endif // HOTENDS <= 1

    active_extruder = tmp_extruder;

    SERIAL_ECHO_START();
    SERIAL_ECHOLNPAIR(MSG_ACTIVE_EXTRUDER, (int)active_extruder);

  #endif // !MIXING_EXTRUDER || MIXING_VIRTUAL_TOOLS <= 1
}

/**
 * T0-T3: Switch tool, usually switching extruders
 *
 *   F[units/min] Set the movement feedrate
 *   S1           Don't move the tool in XY after change
 */
inline void gcode_T(uint8_t tmp_extruder) {

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      SERIAL_ECHOPAIR(">>> gcode_T(", tmp_extruder);
      SERIAL_CHAR(')');
      SERIAL_EOL();
      DEBUG_POS("BEFORE", current_position);
    }
  #endif

  #if HOTENDS == 1 || (ENABLED(MIXING_EXTRUDER) && MIXING_VIRTUAL_TOOLS > 1)

    tool_change(tmp_extruder);

  #elif HOTENDS > 1

    tool_change(
      tmp_extruder,
      MMM_TO_MMS(parser.linearval('F')),
      (tmp_extruder == active_extruder) || parser.boolval('S')
    );

  #endif

  #if ENABLED(DEBUG_LEVELING_FEATURE)
    if (DEBUGGING(LEVELING)) {
      DEBUG_POS("AFTER", current_position);
      SERIAL_ECHOLNPGM("<<< gcode_T");
    }
  #endif
}

/**
 * Process a single command and dispatch it to its handler
 * This is called from the main loop()
 */
void process_next_command() {
  char * const current_command = command_queue[cmd_queue_index_r];

  if (DEBUGGING(ECHO)) {
    SERIAL_ECHO_START();
    SERIAL_ECHOLN(current_command);
    #if ENABLED(M100_FREE_MEMORY_WATCHER)
      SERIAL_ECHOPAIR("slot:", cmd_queue_index_r);
      M100_dump_routine("   Command Queue:", (const char*)command_queue, (const char*)(command_queue + sizeof(command_queue)));
    #endif
  }

  KEEPALIVE_STATE(IN_HANDLER);

  // Parse the next command in the queue
  parser.parse(current_command);

  // Handle a known G, M, or T
  switch (parser.command_letter) {
    case 'G': switch (parser.codenum) {

      // G0, G1
      case 0:
      case 1:
        #if IS_SCARA
          gcode_G0_G1(parser.codenum == 0);
        #else
          gcode_G0_G1();
        #endif
        break;

      // G2, G3
      #if ENABLED(ARC_SUPPORT) && DISABLED(SCARA)
        case 2: // G2  - CW ARC
        case 3: // G3  - CCW ARC
          gcode_G2_G3(parser.codenum == 2);
          break;
      #endif

      // G4 Dwell
      case 4:
        gcode_G4();
        break;

      #if ENABLED(BEZIER_CURVE_SUPPORT)
        // G5
        case 5: // G5  - Cubic B_spline
          gcode_G5();
          break;
      #endif // BEZIER_CURVE_SUPPORT

      #if ENABLED(FWRETRACT)
        case 10: // G10: retract
        case 11: // G11: retract_recover
          gcode_G10_G11(parser.codenum == 10);
          break;
      #endif // FWRETRACT

      #if ENABLED(NOZZLE_CLEAN_FEATURE)
        case 12:
          gcode_G12(); // G12: Nozzle Clean
          break;
      #endif // NOZZLE_CLEAN_FEATURE

      #if ENABLED(CNC_WORKSPACE_PLANES)
        case 17: // G17: Select Plane XY
          gcode_G17();
          break;
        case 18: // G18: Select Plane ZX
          gcode_G18();
          break;
        case 19: // G19: Select Plane YZ
          gcode_G19();
          break;
      #endif // CNC_WORKSPACE_PLANES

      #if ENABLED(INCH_MODE_SUPPORT)
        case 20: //G20: Inch Mode
          gcode_G20();
          break;

        case 21: //G21: MM Mode
          gcode_G21();
          break;
      #endif // INCH_MODE_SUPPORT

      #if ENABLED(AUTO_BED_LEVELING_UBL) && ENABLED(UBL_G26_MESH_VALIDATION)
        case 26: // G26: Mesh Validation Pattern generation
          gcode_G26();
          break;
      #endif // AUTO_BED_LEVELING_UBL

      #if ENABLED(NOZZLE_PARK_FEATURE)
        case 27: // G27: Nozzle Park
          gcode_G27();
          break;
      #endif // NOZZLE_PARK_FEATURE

      case 28: // G28: Home all axes, one at a time
        gcode_G28(false);
        break;

      #if HAS_LEVELING
        case 29: // G29 Detailed Z probe, probes the bed at 3 or more points,
                 // or provides access to the UBL System if enabled.
          gcode_G29();
          break;
      #endif // HAS_LEVELING

      #if HAS_BED_PROBE

        case 30: // G30 Single Z probe
          gcode_G30();
          break;

        #if ENABLED(Z_PROBE_SLED)

            case 31: // G31: dock the sled
              gcode_G31();
              break;

            case 32: // G32: undock the sled
              gcode_G32();
              break;

        #endif // Z_PROBE_SLED

      #endif // HAS_BED_PROBE

      #if PROBE_SELECTED

        #if ENABLED(DELTA_AUTO_CALIBRATION)

          case 33: // G33: Delta Auto-Calibration
            gcode_G33();
            break;

        #endif // DELTA_AUTO_CALIBRATION

      #endif // PROBE_SELECTED

      #if ENABLED(G38_PROBE_TARGET)
        case 38: // G38.2 & G38.3
          if (subcode == 2 || subcode == 3)
            gcode_G38(subcode == 2);
          break;
      #endif

      case 90: // G90
        relative_mode = false;
        break;
      case 91: // G91
        relative_mode = true;
        break;

      case 92: // G92
        gcode_G92();
        break;

      #if ENABLED(AUTO_BED_LEVELING_BILINEAR) || ENABLED(AUTO_BED_LEVELING_UBL) || ENABLED(MESH_BED_LEVELING)
        case 42:
          gcode_G42();
          break;
      #endif

      #if ENABLED(DEBUG_GCODE_PARSER)
        case 800:
          parser.debug(); // GCode Parser Test for G
          break;
      #endif
    }
    break;

    case 'M': switch (parser.codenum) {
      #if HAS_RESUME_CONTINUE
        case 0: // M0: Unconditional stop - Wait for user button press on LCD
        case 1: // M1: Conditional stop - Wait for user button press on LCD
          gcode_M0_M1();
          break;
      #endif // ULTIPANEL

//      #if ENABLED(SPINDLE_LASER_ENABLE)
//        case 3:
//          gcode_M3_M4(true);   // M3: turn spindle/laser on, set laser/spindle power/speed, set rotation direction CW
//          break;               // synchronizes with movement commands
//        case 4:
//          gcode_M3_M4(false);  // M4: turn spindle/laser on, set laser/spindle power/speed, set rotation direction CCW
//          break;               // synchronizes with movement commands
//        case 5:
//          gcode_M5();     // M5 - turn spindle/laser off
//          break;          // synchronizes with movement commands
//      #endif


      case 17: // M17: Enable all stepper motors
        gcode_M17();
        break;

      #if ENABLED(SDSUPPORT)
        case 20: // M20: list SD card
          gcode_M20(); break;
        case 21: // M21: init SD card
          gcode_M21(); break;
        case 22: // M22: release SD card
          gcode_M22(); break;
        case 23: // M23: Select file
          gcode_M23(); break;
        case 24: // M24: Start SD print
          gcode_M24(); break;
        case 25: // M25: Pause SD print
          gcode_M25(); break;
        case 26: // M26: Set SD index
          gcode_M26(); break;
        case 27: // M27: Get SD status
          gcode_M27(); break;
        case 28: // M28: Start SD write
          gcode_M28(); break;
        case 29: // M29: Stop SD write
          gcode_M29(); break;
        case 30: // M30 <filename> Delete File
          gcode_M30(); break;
        case 32: // M32: Select file and start SD print
          gcode_M32(); break;

        #if ENABLED(LONG_FILENAME_HOST_SUPPORT)
          case 33: // M33: Get the long full path to a file or folder
            gcode_M33(); break;
        #endif

        #if ENABLED(SDCARD_SORT_ALPHA) && ENABLED(SDSORT_GCODE)
          case 34: //M34 - Set SD card sorting options
            gcode_M34(); break;
        #endif // SDCARD_SORT_ALPHA && SDSORT_GCODE

        case 928: // M928: Start SD write
          gcode_M928(); break;
      #endif // SDSUPPORT

      case 31: // M31: Report time since the start of SD print or last M109
        gcode_M31(); break;

      case 42: // M42: Change pin state
        gcode_M42(); break;

      #if ENABLED(PINS_DEBUGGING)
        case 43: // M43: Read pin state
          gcode_M43(); break;
      #endif


      #if ENABLED(Z_MIN_PROBE_REPEATABILITY_TEST)
        case 48: // M48: Z probe repeatability test
          gcode_M48();
          break;
      #endif // Z_MIN_PROBE_REPEATABILITY_TEST

      #if ENABLED(AUTO_BED_LEVELING_UBL) && ENABLED(UBL_G26_MESH_VALIDATION)
        case 49: // M49: Turn on or off G26 debug flag for verbose output
          gcode_M49();
          break;
      #endif // AUTO_BED_LEVELING_UBL && UBL_G26_MESH_VALIDATION

      case 75: // M75: Start print timer
        gcode_M75(); break;
      case 76: // M76: Pause print timer
        gcode_M76(); break;
      case 77: // M77: Stop print timer
        gcode_M77(); break;

      #if ENABLED(PRINTCOUNTER)
        case 78: // M78: Show print statistics
          gcode_M78(); break;
      #endif

      #if ENABLED(M100_FREE_MEMORY_WATCHER)
        case 100: // M100: Free Memory Report
          gcode_M100();
          break;
      #endif

      case 104: // M104: Set hot end temperature
        gcode_M104();
        break;

      case 110: // M110: Set Current Line Number
        gcode_M110();
        break;

      case 111: // M111: Set debug level
        gcode_M111();
        break;

      #if DISABLED(EMERGENCY_PARSER)

        case 108: // M108: Cancel Waiting
          gcode_M108();
          break;

        case 112: // M112: Emergency Stop
          gcode_M112();
          break;

        case 410: // M410 quickstop - Abort all the planned moves.
          gcode_M410();
          break;

      #endif

      #if ENABLED(HOST_KEEPALIVE_FEATURE)
        case 113: // M113: Set Host Keepalive interval
          gcode_M113();
          break;
      #endif

      case 140: // M140: Set bed temperature
        gcode_M140();
        break;

      case 105: // M105: Report current temperature
        gcode_M105();
        KEEPALIVE_STATE(NOT_BUSY);
        return; // "ok" already printed

      #if ENABLED(AUTO_REPORT_TEMPERATURES) && (HAS_TEMP_HOTEND || HAS_TEMP_BED)
        case 155: // M155: Set temperature auto-report interval
          gcode_M155();
          break;
      #endif

      case 109: // M109: Wait for hotend temperature to reach target
        gcode_M109();
        break;

      #if HAS_TEMP_BED
        case 190: // M190: Wait for bed temperature to reach target
          gcode_M190();
          break;
      #endif // HAS_TEMP_BED

      #if FAN_COUNT > 0
        case 3: // M106: Fan On
          gcode_M106();
          break;
        case 5: // M107: Fan Off
          gcode_M107();
          break;
      #endif // FAN_COUNT > 0
      
          case 8: // Cool ON
          gcode_M7();
          break;
          case 9: //Cool OFF
          gcode_M8();
          break;

      #if ENABLED(PARK_HEAD_ON_PAUSE)
        case 125: // M125: Store current position and move to filament change position
          gcode_M125(); break;
      #endif

      #if ENABLED(BARICUDA)
        // PWM for HEATER_1_PIN
        #if HAS_HEATER_1
          case 126: // M126: valve open
            gcode_M126();
            break;
          case 127: // M127: valve closed
            gcode_M127();
            break;
        #endif // HAS_HEATER_1

        // PWM for HEATER_2_PIN
        #if HAS_HEATER_2
          case 128: // M128: valve open
            gcode_M128();
            break;
          case 129: // M129: valve closed
            gcode_M129();
            break;
        #endif // HAS_HEATER_2
      #endif // BARICUDA

      #if HAS_POWER_SWITCH

        case 80: // M80: Turn on Power Supply
          gcode_M80();
          break;

      #endif // HAS_POWER_SWITCH

      case 81: // M81: Turn off Power, including Power Supply, if possible
        gcode_M81();
        break;

      case 82: // M82: Set E axis normal mode (same as other axes)
        gcode_M82();
        break;
      case 83: // M83: Set E axis relative mode
        gcode_M83();
        break;
      case 18: // M18 => M84
      case 84: // M84: Disable all steppers or set timeout
        gcode_M18_M84();
        break;
      case 85: // M85: Set inactivity stepper shutdown timeout
        gcode_M85();
        break;
      case 92: // M92: Set the steps-per-unit for one or more axes
        gcode_M92();
        break;
      case 114: // M114: Report current position
        gcode_M114();
        break;
      case 115: // M115: Report capabilities
        gcode_M115();
        break;
      case 117: // M117: Set LCD message text, if possible
        gcode_M117();
        break;
      case 118: // M118: Display a message in the host console
        gcode_M118();
        break;
      case 119: // M119: Report endstop states
        gcode_M119();
        break;
      case 120: // M120: Enable endstops
        gcode_M120();
        break;
      case 121: // M121: Disable endstops
        gcode_M121();
        break;

      #if ENABLED(ULTIPANEL)

        case 145: // M145: Set material heatup parameters
          gcode_M145();
          break;

      #endif

      #if ENABLED(TEMPERATURE_UNITS_SUPPORT)
        case 149: // M149: Set temperature units
          gcode_M149();
          break;
      #endif

      #if HAS_COLOR_LEDS

        case 150: // M150: Set Status LED Color
          gcode_M150();
          break;

      #endif // HAS_COLOR_LEDS

      #if ENABLED(MIXING_EXTRUDER)
        case 163: // M163: Set a component weight for mixing extruder
          gcode_M163();
          break;
        #if MIXING_VIRTUAL_TOOLS > 1
          case 164: // M164: Save current mix as a virtual extruder
            gcode_M164();
            break;
        #endif
        #if ENABLED(DIRECT_MIXING_IN_G1)
          case 165: // M165: Set multiple mix weights
            gcode_M165();
            break;
        #endif
      #endif

      case 200: // M200: Set filament diameter, E to cubic units
        gcode_M200();
        break;
      case 201: // M201: Set max acceleration for print moves (units/s^2)
        gcode_M201();
        break;
      #if 0 // Not used for Sprinter/grbl gen6
        case 202: // M202
          gcode_M202();
          break;
      #endif
      case 203: // M203: Set max feedrate (units/sec)
        gcode_M203();
        break;
      case 204: // M204: Set acceleration
        gcode_M204();
        break;
      case 205: //M205: Set advanced settings
        gcode_M205();
        break;

      #if HAS_M206_COMMAND
        case 206: // M206: Set home offsets
          gcode_M206();
          break;
      #endif

      #if ENABLED(DELTA)
        case 665: // M665: Set delta configurations
          gcode_M665();
          break;
      #endif

      #if ENABLED(DELTA) || ENABLED(Z_DUAL_ENDSTOPS)
        case 666: // M666: Set delta or dual endstop adjustment
          gcode_M666();
          break;
      #endif

      #if ENABLED(FWRETRACT)
        case 207: // M207: Set Retract Length, Feedrate, and Z lift
          gcode_M207();
          break;
        case 208: // M208: Set Recover (unretract) Additional Length and Feedrate
          gcode_M208();
          break;
        case 209: // M209: Turn Automatic Retract Detection on/off
          gcode_M209();
          break;
      #endif // FWRETRACT

      case 211: // M211: Enable, Disable, and/or Report software endstops
        gcode_M211();
        break;

      #if HOTENDS > 1
        case 218: // M218: Set a tool offset
          gcode_M218();
          break;
      #endif

      case 220: // M220: Set Feedrate Percentage: S<percent> ("FR" on your LCD)
        gcode_M220();
        break;

      case 221: // M221: Set Flow Percentage
        gcode_M221();
        break;

      case 226: // M226: Wait until a pin reaches a state
        gcode_M226();
        break;

      #if HAS_SERVOS
        case 280: // M280: Set servo position absolute
          gcode_M280();
          break;
      #endif // HAS_SERVOS

      #if HAS_BUZZER
        case 300: // M300: Play beep tone
          gcode_M300();
          break;
      #endif // HAS_BUZZER

      #if ENABLED(PIDTEMP)
        case 301: // M301: Set hotend PID parameters
          gcode_M301();
          break;
      #endif // PIDTEMP

      #if ENABLED(PIDTEMPBED)
        case 304: // M304: Set bed PID parameters
          gcode_M304();
          break;
      #endif // PIDTEMPBED

      #if defined(CHDK) || HAS_PHOTOGRAPH
        case 240: // M240: Trigger a camera by emulating a Canon RC-1 : http://www.doc-diy.net/photo/rc-1_hacked/
          gcode_M240();
          break;
      #endif // CHDK || PHOTOGRAPH_PIN

      #if HAS_LCD_CONTRAST
        case 250: // M250: Set LCD contrast
          gcode_M250();
          break;
      #endif // HAS_LCD_CONTRAST

      #if ENABLED(EXPERIMENTAL_I2CBUS)

        case 260: // M260: Send data to an i2c slave
          gcode_M260();
          break;

        case 261: // M261: Request data from an i2c slave
          gcode_M261();
          break;

      #endif // EXPERIMENTAL_I2CBUS

      #if ENABLED(PREVENT_COLD_EXTRUSION)
        case 302: // M302: Allow cold extrudes (set the minimum extrude temperature)
          gcode_M302();
          break;
      #endif // PREVENT_COLD_EXTRUSION

      case 303: // M303: PID autotune
        gcode_M303();
        break;

      #if ENABLED(MORGAN_SCARA)
        case 360:  // M360: SCARA Theta pos1
          if (gcode_M360()) return;
          break;
        case 361:  // M361: SCARA Theta pos2
          if (gcode_M361()) return;
          break;
        case 362:  // M362: SCARA Psi pos1
          if (gcode_M362()) return;
          break;
        case 363:  // M363: SCARA Psi pos2
          if (gcode_M363()) return;
          break;
        case 364:  // M364: SCARA Psi pos3 (90 deg to Theta)
          if (gcode_M364()) return;
          break;
      #endif // SCARA

      case 400: // M400: Finish all moves
        gcode_M400();
        break;

      #if HAS_BED_PROBE
        case 401: // M401: Deploy probe
          gcode_M401();
          break;
        case 402: // M402: Stow probe
          gcode_M402();
          break;
      #endif // HAS_BED_PROBE

      #if ENABLED(FILAMENT_WIDTH_SENSOR)
        case 404:  // M404: Enter the nominal filament width (3mm, 1.75mm ) N<3.0> or display nominal filament width
          gcode_M404();
          break;
        case 405:  // M405: Turn on filament sensor for control
          gcode_M405();
          break;
        case 406:  // M406: Turn off filament sensor for control
          gcode_M406();
          break;
        case 407:   // M407: Display measured filament diameter
          gcode_M407();
          break;
      #endif // FILAMENT_WIDTH_SENSOR

      #if HAS_LEVELING
        case 420: // M420: Enable/Disable Bed Leveling
          gcode_M420();
          break;
      #endif

      #if ENABLED(MESH_BED_LEVELING) || ENABLED(AUTO_BED_LEVELING_UBL) || ENABLED(AUTO_BED_LEVELING_BILINEAR)
        case 421: // M421: Set a Mesh Bed Leveling Z coordinate
          gcode_M421();
          break;
      #endif

      #if HAS_M206_COMMAND
        case 428: // M428: Apply current_position to home_offset
          gcode_M428();
          break;
      #endif

      case 500: // M500: Store settings in EEPROM
        gcode_M500();
        break;
      case 501: // M501: Read settings from EEPROM
        gcode_M501();
        break;
      case 502: // M502: Revert to default settings
        gcode_M502();
        break;

      #if DISABLED(DISABLE_M503)
        case 503: // M503: print settings currently in memory
          gcode_M503();
          break;
      #endif

      #if ENABLED(ABORT_ON_ENDSTOP_HIT_FEATURE_ENABLED)
        case 540: // M540: Set abort on endstop hit for SD printing
          gcode_M540();
          break;
      #endif

      #if HAS_BED_PROBE
        case 851: // M851: Set Z Probe Z Offset
          gcode_M851();
          break;
      #endif // HAS_BED_PROBE

      #if ENABLED(ADVANCED_PAUSE_FEATURE)
        case 600: // M600: Pause for filament change
          gcode_M600();
          break;
      #endif // ADVANCED_PAUSE_FEATURE

      #if ENABLED(DUAL_X_CARRIAGE) || ENABLED(DUAL_NOZZLE_DUPLICATION_MODE)
        case 605: // M605: Set Dual X Carriage movement mode
          gcode_M605();
          break;
      #endif // DUAL_X_CARRIAGE

      #if ENABLED(MK2_MULTIPLEXER)
        case 702: // M702: Unload all extruders
          gcode_M702();
          break;
      #endif

      #if ENABLED(LIN_ADVANCE)
        case 900: // M900: Set advance K factor.
          gcode_M900();
          break;
      #endif

      #if ENABLED(HAVE_TMC2130)
        case 906: // M906: Set motor current in milliamps using axis codes X, Y, Z, E
          gcode_M906();
          break;
      #endif

      case 907: // M907: Set digital trimpot motor current using axis codes.
        gcode_M907();
        break;

      #if HAS_DIGIPOTSS || ENABLED(DAC_STEPPER_CURRENT)

        case 908: // M908: Control digital trimpot directly.
          gcode_M908();
          break;

        #if ENABLED(DAC_STEPPER_CURRENT) // As with Printrbot RevF

          case 909: // M909: Print digipot/DAC current value
            gcode_M909();
            break;

          case 910: // M910: Commit digipot/DAC value to external EEPROM
            gcode_M910();
            break;

        #endif

      #endif // HAS_DIGIPOTSS || DAC_STEPPER_CURRENT

      #if ENABLED(HAVE_TMC2130)
        case 911: // M911: Report TMC2130 prewarn triggered flags
          gcode_M911();
          break;

        case 912: // M911: Clear TMC2130 prewarn triggered flags
          gcode_M912();
          break;

        #if ENABLED(HYBRID_THRESHOLD)
          case 913: // M913: Set HYBRID_THRESHOLD speed.
            gcode_M913();
            break;
        #endif

        #if ENABLED(SENSORLESS_HOMING)
          case 914: // M914: Set SENSORLESS_HOMING sensitivity.
            gcode_M914();
            break;
        #endif
      #endif

      #if HAS_MICROSTEPS

        case 350: // M350: Set microstepping mode. Warning: Steps per unit remains unchanged. S code sets stepping mode for all drivers.
          gcode_M350();
          break;

        case 351: // M351: Toggle MS1 MS2 pins directly, S# determines MS1 or MS2, X# sets the pin high/low.
          gcode_M351();
          break;

      #endif // HAS_MICROSTEPS

      case 355: // M355 set case light brightness
        gcode_M355();
        break;

      #if ENABLED(DEBUG_GCODE_PARSER)
        case 800:
          parser.debug(); // GCode Parser Test for M
          break;
      #endif

      #if ENABLED(I2C_POSITION_ENCODERS)

        case 860: // M860 Report encoder module position
          gcode_M860();
          break;

        case 861: // M861 Report encoder module status
          gcode_M861();
          break;

        case 862: // M862 Perform axis test
          gcode_M862();
          break;

        case 863: // M863 Calibrate steps/mm
          gcode_M863();
          break;

        case 864: // M864 Change module address
          gcode_M864();
          break;

        case 865: // M865 Check module firmware version
          gcode_M865();
          break;

        case 866: // M866 Report axis error count
          gcode_M866();
          break;

        case 867: // M867 Toggle error correction
          gcode_M867();
          break;

        case 868: // M868 Set error correction threshold
          gcode_M868();
          break;

        case 869: // M869 Report axis error
          gcode_M869();
          break;

      #endif // I2C_POSITION_ENCODERS

      case 999: // M999: Restart after being Stopped
        gcode_M999();
        break;
    }
    break;

    case 'T':
      gcode_T(parser.codenum);
      break;

    default: parser.unknown_command_error();
  }

  KEEPALIVE_STATE(NOT_BUSY);

  ok_to_send();
}

/**
 * Send a "Resend: nnn" message to the host to
 * indicate that a command needs to be re-sent.
 */
void FlushSerialRequestResend() {
  //char command_queue[cmd_queue_index_r][100]="Resend:";
  MYSERIAL.flush();
  SERIAL_PROTOCOLPGM(MSG_RESEND);
  SERIAL_PROTOCOLLN(gcode_LastN + 1);
  ok_to_send();
}

/**
 * Send an "ok" message to the host, indicating
 * that a command was successfully processed.
 *
 * If ADVANCED_OK is enabled also include:
 *   N<int>  Line number of the command, if any
 *   P<int>  Planner space remaining
 *   B<int>  Block queue space remaining
 */
void ok_to_send() {
  refresh_cmd_timeout();
  if (!send_ok[cmd_queue_index_r]) return;
  SERIAL_PROTOCOLPGM(MSG_OK);
  #if ENABLED(ADVANCED_OK)
    char* p = command_queue[cmd_queue_index_r];
    if (*p == 'N') {
      SERIAL_PROTOCOL(' ');
      SERIAL_ECHO(*p++);
      while (NUMERIC_SIGNED(*p))
        SERIAL_ECHO(*p++);
    }
    SERIAL_PROTOCOLPGM(" P"); SERIAL_PROTOCOL(int(BLOCK_BUFFER_SIZE - planner.movesplanned() - 1));
    SERIAL_PROTOCOLPGM(" B"); SERIAL_PROTOCOL(BUFSIZE - commands_in_queue);
  #endif
  SERIAL_EOL();
}

#if HAS_SOFTWARE_ENDSTOPS

  /**
   * Constrain the given coordinates to the software endstops.
   */

  // NOTE: This makes no sense for delta beds other than Z-axis.
  //       For delta the X/Y would need to be clamped at
  //       DELTA_PRINTABLE_RADIUS from center of bed, but delta
  //       now enforces is_position_reachable for X/Y regardless
  //       of HAS_SOFTWARE_ENDSTOPS, so that enforcement would be
  //       redundant here.  Probably should #ifdef out the X/Y
  //       axis clamps here for delta and just leave the Z clamp.

  void clamp_to_software_endstops(float target[XYZ]) {
    if (!soft_endstops_enabled) return;
    #if ENABLED(MIN_SOFTWARE_ENDSTOPS)
      NOLESS(target[X_AXIS], soft_endstop_min[X_AXIS]);
      NOLESS(target[Y_AXIS], soft_endstop_min[Y_AXIS]);
      NOLESS(target[Z_AXIS], soft_endstop_min[Z_AXIS]);
    #endif
    #if ENABLED(MAX_SOFTWARE_ENDSTOPS)
      NOMORE(target[X_AXIS], soft_endstop_max[X_AXIS]);
      NOMORE(target[Y_AXIS], soft_endstop_max[Y_AXIS]);
      NOMORE(target[Z_AXIS], soft_endstop_max[Z_AXIS]);
    #endif
  }

#endif

#if ENABLED(AUTO_BED_LEVELING_BILINEAR)

  #if ENABLED(ABL_BILINEAR_SUBDIVISION)
    #define ABL_BG_SPACING(A) bilinear_grid_spacing_virt[A]
    #define ABL_BG_FACTOR(A)  bilinear_grid_factor_virt[A]
    #define ABL_BG_POINTS_X   ABL_GRID_POINTS_VIRT_X
    #define ABL_BG_POINTS_Y   ABL_GRID_POINTS_VIRT_Y
    #define ABL_BG_GRID(X,Y)  z_values_virt[X][Y]
  #else
    #define ABL_BG_SPACING(A) bilinear_grid_spacing[A]
    #define ABL_BG_FACTOR(A)  bilinear_grid_factor[A]
    #define ABL_BG_POINTS_X   GRID_MAX_POINTS_X
    #define ABL_BG_POINTS_Y   GRID_MAX_POINTS_Y
    #define ABL_BG_GRID(X,Y)  z_values[X][Y]
  #endif

  // Get the Z adjustment for non-linear bed leveling
  float bilinear_z_offset(const float logical[XYZ]) {

    static float z1, d2, z3, d4, L, D, ratio_x, ratio_y,
                 last_x = -999.999, last_y = -999.999;

    // Whole units for the grid line indices. Constrained within bounds.
    static int8_t gridx, gridy, nextx, nexty,
                  last_gridx = -99, last_gridy = -99;

    // XY relative to the probed area
    const float x = RAW_X_POSITION(logical[X_AXIS]) - bilinear_start[X_AXIS],
                y = RAW_Y_POSITION(logical[Y_AXIS]) - bilinear_start[Y_AXIS];

    #if ENABLED(EXTRAPOLATE_BEYOND_GRID)
      // Keep using the last grid box
      #define FAR_EDGE_OR_BOX 2
    #else
      // Just use the grid far edge
      #define FAR_EDGE_OR_BOX 1
    #endif

    if (last_x != x) {
      last_x = x;
      ratio_x = x * ABL_BG_FACTOR(X_AXIS);
      const float gx = constrain(FLOOR(ratio_x), 0, ABL_BG_POINTS_X - FAR_EDGE_OR_BOX);
      ratio_x -= gx;      // Subtract whole to get the ratio within the grid box

      #if DISABLED(EXTRAPOLATE_BEYOND_GRID)
        // Beyond the grid maintain height at grid edges
        NOLESS(ratio_x, 0); // Never < 0.0. (> 1.0 is ok when nextx==gridx.)
      #endif

      gridx = gx;
      nextx = min(gridx + 1, ABL_BG_POINTS_X - 1);
    }

    if (last_y != y || last_gridx != gridx) {

      if (last_y != y) {
        last_y = y;
        ratio_y = y * ABL_BG_FACTOR(Y_AXIS);
        const float gy = constrain(FLOOR(ratio_y), 0, ABL_BG_POINTS_Y - FAR_EDGE_OR_BOX);
        ratio_y -= gy;

        #if DISABLED(EXTRAPOLATE_BEYOND_GRID)
          // Beyond the grid maintain height at grid edges
          NOLESS(ratio_y, 0); // Never < 0.0. (> 1.0 is ok when nexty==gridy.)
        #endif

        gridy = gy;
        nexty = min(gridy + 1, ABL_BG_POINTS_Y - 1);
      }

      if (last_gridx != gridx || last_gridy != gridy) {
        last_gridx = gridx;
        last_gridy = gridy;
        // Z at the box corners
        z1 = ABL_BG_GRID(gridx, gridy);       // left-front
        d2 = ABL_BG_GRID(gridx, nexty) - z1;  // left-back (delta)
        z3 = ABL_BG_GRID(nextx, gridy);       // right-front
        d4 = ABL_BG_GRID(nextx, nexty) - z3;  // right-back (delta)
      }

      // Bilinear interpolate. Needed since y or gridx has changed.
                  L = z1 + d2 * ratio_y;   // Linear interp. LF -> LB
      const float R = z3 + d4 * ratio_y;   // Linear interp. RF -> RB

      D = R - L;
    }

    const float offset = L + ratio_x * D;   // the offset almost always changes

    /*
    static float last_offset = 0;
    if (FABS(last_offset - offset) > 0.2) {
      SERIAL_ECHOPGM("Sudden Shift at ");
      SERIAL_ECHOPAIR("x=", x);
      SERIAL_ECHOPAIR(" / ", bilinear_grid_spacing[X_AXIS]);
      SERIAL_ECHOLNPAIR(" -> gridx=", gridx);
      SERIAL_ECHOPAIR(" y=", y);
      SERIAL_ECHOPAIR(" / ", bilinear_grid_spacing[Y_AXIS]);
      SERIAL_ECHOLNPAIR(" -> gridy=", gridy);
      SERIAL_ECHOPAIR(" ratio_x=", ratio_x);
      SERIAL_ECHOLNPAIR(" ratio_y=", ratio_y);
      SERIAL_ECHOPAIR(" z1=", z1);
      SERIAL_ECHOPAIR(" z2=", z2);
      SERIAL_ECHOPAIR(" z3=", z3);
      SERIAL_ECHOLNPAIR(" z4=", z4);
      SERIAL_ECHOPAIR(" L=", L);
      SERIAL_ECHOPAIR(" R=", R);
      SERIAL_ECHOLNPAIR(" offset=", offset);
    }
    last_offset = offset;
    //*/

    return offset;
  }

#endif // AUTO_BED_LEVELING_BILINEAR

#if ENABLED(DELTA)

  /**
   * Recalculate factors used for delta kinematics whenever
   * settings have been changed (e.g., by M665).
   */
  void recalc_delta_settings(float radius, float diagonal_rod) {
    const float trt[ABC] = DELTA_RADIUS_TRIM_TOWER,
                drt[ABC] = DELTA_DIAGONAL_ROD_TRIM_TOWER;
    delta_tower[A_AXIS][X_AXIS] = cos(RADIANS(210 + delta_tower_angle_trim[A_AXIS])) * (radius + trt[A_AXIS]); // front left tower
    delta_tower[A_AXIS][Y_AXIS] = sin(RADIANS(210 + delta_tower_angle_trim[A_AXIS])) * (radius + trt[A_AXIS]);
    delta_tower[B_AXIS][X_AXIS] = cos(RADIANS(330 + delta_tower_angle_trim[B_AXIS])) * (radius + trt[B_AXIS]); // front right tower
    delta_tower[B_AXIS][Y_AXIS] = sin(RADIANS(330 + delta_tower_angle_trim[B_AXIS])) * (radius + trt[B_AXIS]);
    delta_tower[C_AXIS][X_AXIS] = 0.0; // back middle tower
    delta_tower[C_AXIS][Y_AXIS] = (radius + trt[C_AXIS]);
    delta_diagonal_rod_2_tower[A_AXIS] = sq(diagonal_rod + drt[A_AXIS]);
    delta_diagonal_rod_2_tower[B_AXIS] = sq(diagonal_rod + drt[B_AXIS]);
    delta_diagonal_rod_2_tower[C_AXIS] = sq(diagonal_rod + drt[C_AXIS]);
  }

  #if ENABLED(DELTA_FAST_SQRT)
    /**
     * Fast inverse sqrt from Quake III Arena
     * See: https://en.wikipedia.org/wiki/Fast_inverse_square_root
     */
    float Q_rsqrt(float number) {
      long i;
      float x2, y;
      const float threehalfs = 1.5f;
      x2 = number * 0.5f;
      y  = number;
      i  = * ( long * ) &y;                       // evil floating point bit level hacking
      i  = 0x5F3759DF - ( i >> 1 );               // what the f***?
      y  = * ( float * ) &i;
      y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
      // y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
      return y;
    }

    #define _SQRT(n) (1.0f / Q_rsqrt(n))

  #else

    #define _SQRT(n) SQRT(n)

  #endif

  /**
   * Delta Inverse Kinematics
   *
   * Calculate the tower positions for a given logical
   * position, storing the result in the delta[] array.
   *
   * This is an expensive calculation, requiring 3 square
   * roots per segmented linear move, and strains the limits
   * of a Mega2560 with a Graphical Display.
   *
   * Suggested optimizations include:
   *
   * - Disable the home_offset (M206) and/or position_shift (G92)
   *   features to remove up to 12 float additions.
   *
   * - Use a fast-inverse-sqrt function and add the reciprocal.
   *   (see above)
   */

  // Macro to obtain the Z position of an individual tower
  #define DELTA_Z(T) raw[Z_AXIS] + _SQRT(     \
    delta_diagonal_rod_2_tower[T] - HYPOT2(   \
        delta_tower[T][X_AXIS] - raw[X_AXIS], \
        delta_tower[T][Y_AXIS] - raw[Y_AXIS]  \
      )                                       \
    )

  #define DELTA_RAW_IK() do {        \
    delta[A_AXIS] = DELTA_Z(A_AXIS); \
    delta[B_AXIS] = DELTA_Z(B_AXIS); \
    delta[C_AXIS] = DELTA_Z(C_AXIS); \
  }while(0)

  #define DELTA_LOGICAL_IK() do {      \
    const float raw[XYZ] = {           \
      RAW_X_POSITION(logical[X_AXIS]), \
      RAW_Y_POSITION(logical[Y_AXIS]), \
      RAW_Z_POSITION(logical[Z_AXIS])  \
    };                                 \
    DELTA_RAW_IK();                    \
  }while(0)

  #define DELTA_DEBUG() do { \
      SERIAL_ECHOPAIR("cartesian X:", raw[X_AXIS]); \
      SERIAL_ECHOPAIR(" Y:", raw[Y_AXIS]);          \
      SERIAL_ECHOLNPAIR(" Z:", raw[Z_AXIS]);        \
      SERIAL_ECHOPAIR("delta A:", delta[A_AXIS]);   \
      SERIAL_ECHOPAIR(" B:", delta[B_AXIS]);        \
      SERIAL_ECHOLNPAIR(" C:", delta[C_AXIS]);      \
    }while(0)

  void inverse_kinematics(const float logical[XYZ]) {
    DELTA_LOGICAL_IK();
    // DELTA_DEBUG();
  }

  /**
   * Calculate the highest Z position where the
   * effector has the full range of XY motion.
   */
  float delta_safe_distance_from_top() {
    float cartesian[XYZ] = {
      LOGICAL_X_POSITION(0),
      LOGICAL_Y_POSITION(0),
      LOGICAL_Z_POSITION(0)
    };
    inverse_kinematics(cartesian);
    float distance = delta[A_AXIS];
    cartesian[Y_AXIS] = LOGICAL_Y_POSITION(DELTA_PRINTABLE_RADIUS);
    inverse_kinematics(cartesian);
    return FABS(distance - delta[A_AXIS]);
  }

  /**
   * Delta Forward Kinematics
   *
   * See the Wikipedia article "Trilateration"
   * https://en.wikipedia.org/wiki/Trilateration
   *
   * Establish a new coordinate system in the plane of the
   * three carriage points. This system has its origin at
   * tower1, with tower2 on the X axis. Tower3 is in the X-Y
   * plane with a Z component of zero.
   * We will define unit vectors in this coordinate system
   * in our original coordinate system. Then when we calculate
   * the Xnew, Ynew and Znew values, we can translate back into
   * the original system by moving along those unit vectors
   * by the corresponding values.
   *
   * Variable names matched to Marlin, c-version, and avoid the
   * use of any vector library.
   *
   * by Andreas Hardtung 2016-06-07
   * based on a Java function from "Delta Robot Kinematics V3"
   * by Steve Graves
   *
   * The result is stored in the cartes[] array.
   */
  void forward_kinematics_DELTA(float z1, float z2, float z3) {
    // Create a vector in old coordinates along x axis of new coordinate
    float p12[3] = { delta_tower[B_AXIS][X_AXIS] - delta_tower[A_AXIS][X_AXIS], delta_tower[B_AXIS][Y_AXIS] - delta_tower[A_AXIS][Y_AXIS], z2 - z1 };

    // Get the Magnitude of vector.
    float d = SQRT( sq(p12[0]) + sq(p12[1]) + sq(p12[2]) );

    // Create unit vector by dividing by magnitude.
    float ex[3] = { p12[0] / d, p12[1] / d, p12[2] / d };

    // Get the vector from the origin of the new system to the third point.
    float p13[3] = { delta_tower[C_AXIS][X_AXIS] - delta_tower[A_AXIS][X_AXIS], delta_tower[C_AXIS][Y_AXIS] - delta_tower[A_AXIS][Y_AXIS], z3 - z1 };

    // Use the dot product to find the component of this vector on the X axis.
    float i = ex[0] * p13[0] + ex[1] * p13[1] + ex[2] * p13[2];

    // Create a vector along the x axis that represents the x component of p13.
    float iex[3] = { ex[0] * i, ex[1] * i, ex[2] * i };

    // Subtract the X component from the original vector leaving only Y. We use the
    // variable that will be the unit vector after we scale it.
    float ey[3] = { p13[0] - iex[0], p13[1] - iex[1], p13[2] - iex[2] };

    // The magnitude of Y component
    float j = SQRT( sq(ey[0]) + sq(ey[1]) + sq(ey[2]) );

    // Convert to a unit vector
    ey[0] /= j; ey[1] /= j;  ey[2] /= j;

    // The cross product of the unit x and y is the unit z
    // float[] ez = vectorCrossProd(ex, ey);
    float ez[3] = {
      ex[1] * ey[2] - ex[2] * ey[1],
      ex[2] * ey[0] - ex[0] * ey[2],
      ex[0] * ey[1] - ex[1] * ey[0]
    };

    // We now have the d, i and j values defined in Wikipedia.
    // Plug them into the equations defined in Wikipedia for Xnew, Ynew and Znew
    float Xnew = (delta_diagonal_rod_2_tower[A_AXIS] - delta_diagonal_rod_2_tower[B_AXIS] + sq(d)) / (d * 2),
          Ynew = ((delta_diagonal_rod_2_tower[A_AXIS] - delta_diagonal_rod_2_tower[C_AXIS] + HYPOT2(i, j)) / 2 - i * Xnew) / j,
          Znew = SQRT(delta_diagonal_rod_2_tower[A_AXIS] - HYPOT2(Xnew, Ynew));

    // Start from the origin of the old coordinates and add vectors in the
    // old coords that represent the Xnew, Ynew and Znew to find the point
    // in the old system.
    cartes[X_AXIS] = delta_tower[A_AXIS][X_AXIS] + ex[0] * Xnew + ey[0] * Ynew - ez[0] * Znew;
    cartes[Y_AXIS] = delta_tower[A_AXIS][Y_AXIS] + ex[1] * Xnew + ey[1] * Ynew - ez[1] * Znew;
    cartes[Z_AXIS] =             z1 + ex[2] * Xnew + ey[2] * Ynew - ez[2] * Znew;
  }

  void forward_kinematics_DELTA(float point[ABC]) {
    forward_kinematics_DELTA(point[A_AXIS], point[B_AXIS], point[C_AXIS]);
  }

#endif // DELTA

/**
 * Get the stepper positions in the cartes[] array.
 * Forward kinematics are applied for DELTA and SCARA.
 *
 * The result is in the current coordinate space with
 * leveling applied. The coordinates need to be run through
 * unapply_leveling to obtain the "ideal" coordinates
 * suitable for current_position, etc.
 */
void get_cartesian_from_steppers() {
  #if ENABLED(DELTA)
    forward_kinematics_DELTA(
      stepper.get_axis_position_mm(A_AXIS),
      stepper.get_axis_position_mm(B_AXIS),
      stepper.get_axis_position_mm(C_AXIS)
    );
    cartes[X_AXIS] += LOGICAL_X_POSITION(0);
    cartes[Y_AXIS] += LOGICAL_Y_POSITION(0);
    cartes[Z_AXIS] += LOGICAL_Z_POSITION(0);
  #elif IS_SCARA
    forward_kinematics_SCARA(
      stepper.get_axis_position_degrees(A_AXIS),
      stepper.get_axis_position_degrees(B_AXIS)
    );
    cartes[X_AXIS] += LOGICAL_X_POSITION(0);
    cartes[Y_AXIS] += LOGICAL_Y_POSITION(0);
    cartes[Z_AXIS] = stepper.get_axis_position_mm(Z_AXIS);
  #else
    cartes[X_AXIS] = stepper.get_axis_position_mm(X_AXIS);
    cartes[Y_AXIS] = stepper.get_axis_position_mm(Y_AXIS);
    cartes[Z_AXIS] = stepper.get_axis_position_mm(Z_AXIS);
  #endif
}

/**
 * Set the current_position for an axis based on
 * the stepper positions, removing any leveling that
 * may have been applied.
 */
void set_current_from_steppers_for_axis(const AxisEnum axis) {
  get_cartesian_from_steppers();
  #if PLANNER_LEVELING
    planner.unapply_leveling(cartes);
  #endif
  if (axis == ALL_AXES)
    COPY(current_position, cartes);
  else
    current_position[axis] = cartes[axis];
}

#if ENABLED(MESH_BED_LEVELING)

  /**
   * Prepare a mesh-leveled linear move in a Cartesian setup,
   * splitting the move where it crosses mesh borders.
   */
  void mesh_line_to_destination(float fr_mm_s, uint8_t x_splits = 0xFF, uint8_t y_splits = 0xFF) {
    int cx1 = mbl.cell_index_x(RAW_CURRENT_POSITION(X)),
        cy1 = mbl.cell_index_y(RAW_CURRENT_POSITION(Y)),
        cx2 = mbl.cell_index_x(RAW_X_POSITION(destination[X_AXIS])),
        cy2 = mbl.cell_index_y(RAW_Y_POSITION(destination[Y_AXIS]));
    NOMORE(cx1, GRID_MAX_POINTS_X - 2);
    NOMORE(cy1, GRID_MAX_POINTS_Y - 2);
    NOMORE(cx2, GRID_MAX_POINTS_X - 2);
    NOMORE(cy2, GRID_MAX_POINTS_Y - 2);

    if (cx1 == cx2 && cy1 == cy2) {
      // Start and end on same mesh square
      line_to_destination(fr_mm_s);
      set_current_to_destination();
      return;
    }

    #define MBL_SEGMENT_END(A) (current_position[A ##_AXIS] + (destination[A ##_AXIS] - current_position[A ##_AXIS]) * normalized_dist)

    float normalized_dist, end[XYZE];

    // Split at the left/front border of the right/top square
    const int8_t gcx = max(cx1, cx2), gcy = max(cy1, cy2);
    if (cx2 != cx1 && TEST(x_splits, gcx)) {
      COPY(end, destination);
      destination[X_AXIS] = LOGICAL_X_POSITION(mbl.index_to_xpos[gcx]);
      normalized_dist = (destination[X_AXIS] - current_position[X_AXIS]) / (end[X_AXIS] - current_position[X_AXIS]);
      destination[Y_AXIS] = MBL_SEGMENT_END(Y);
      CBI(x_splits, gcx);
    }
    else if (cy2 != cy1 && TEST(y_splits, gcy)) {
      COPY(end, destination);
      destination[Y_AXIS] = LOGICAL_Y_POSITION(mbl.index_to_ypos[gcy]);
      normalized_dist = (destination[Y_AXIS] - current_position[Y_AXIS]) / (end[Y_AXIS] - current_position[Y_AXIS]);
      destination[X_AXIS] = MBL_SEGMENT_END(X);
      CBI(y_splits, gcy);
    }
    else {
      // Already split on a border
      line_to_destination(fr_mm_s);
      set_current_to_destination();
      return;
    }

    destination[Z_AXIS] = MBL_SEGMENT_END(Z);
    destination[E_AXIS] = MBL_SEGMENT_END(E);

    // Do the split and look for more borders
    mesh_line_to_destination(fr_mm_s, x_splits, y_splits);

    // Restore destination from stack
    COPY(destination, end);
    mesh_line_to_destination(fr_mm_s, x_splits, y_splits);
  }

#elif ENABLED(AUTO_BED_LEVELING_BILINEAR) && !IS_KINEMATIC

  #define CELL_INDEX(A,V) ((RAW_##A##_POSITION(V) - bilinear_start[A##_AXIS]) * ABL_BG_FACTOR(A##_AXIS))

  /**
   * Prepare a bilinear-leveled linear move on Cartesian,
   * splitting the move where it crosses grid borders.
   */
  void bilinear_line_to_destination(float fr_mm_s, uint16_t x_splits = 0xFFFF, uint16_t y_splits = 0xFFFF) {
    int cx1 = CELL_INDEX(X, current_position[X_AXIS]),
        cy1 = CELL_INDEX(Y, current_position[Y_AXIS]),
        cx2 = CELL_INDEX(X, destination[X_AXIS]),
        cy2 = CELL_INDEX(Y, destination[Y_AXIS]);
    cx1 = constrain(cx1, 0, ABL_BG_POINTS_X - 2);
    cy1 = constrain(cy1, 0, ABL_BG_POINTS_Y - 2);
    cx2 = constrain(cx2, 0, ABL_BG_POINTS_X - 2);
    cy2 = constrain(cy2, 0, ABL_BG_POINTS_Y - 2);

    if (cx1 == cx2 && cy1 == cy2) {
      // Start and end on same mesh square
      line_to_destination(fr_mm_s);
      set_current_to_destination();
      return;
    }

    #define LINE_SEGMENT_END(A) (current_position[A ##_AXIS] + (destination[A ##_AXIS] - current_position[A ##_AXIS]) * normalized_dist)

    float normalized_dist, end[XYZE];

    // Split at the left/front border of the right/top square
    const int8_t gcx = max(cx1, cx2), gcy = max(cy1, cy2);
    if (cx2 != cx1 && TEST(x_splits, gcx)) {
      COPY(end, destination);
      destination[X_AXIS] = LOGICAL_X_POSITION(bilinear_start[X_AXIS] + ABL_BG_SPACING(X_AXIS) * gcx);
      normalized_dist = (destination[X_AXIS] - current_position[X_AXIS]) / (end[X_AXIS] - current_position[X_AXIS]);
      destination[Y_AXIS] = LINE_SEGMENT_END(Y);
      CBI(x_splits, gcx);
    }
    else if (cy2 != cy1 && TEST(y_splits, gcy)) {
      COPY(end, destination);
      destination[Y_AXIS] = LOGICAL_Y_POSITION(bilinear_start[Y_AXIS] + ABL_BG_SPACING(Y_AXIS) * gcy);
      normalized_dist = (destination[Y_AXIS] - current_position[Y_AXIS]) / (end[Y_AXIS] - current_position[Y_AXIS]);
      destination[X_AXIS] = LINE_SEGMENT_END(X);
      CBI(y_splits, gcy);
    }
    else {
      // Already split on a border
      line_to_destination(fr_mm_s);
      set_current_to_destination();
      return;
    }

    destination[Z_AXIS] = LINE_SEGMENT_END(Z);
    destination[E_AXIS] = LINE_SEGMENT_END(E);

    // Do the split and look for more borders
    bilinear_line_to_destination(fr_mm_s, x_splits, y_splits);

    // Restore destination from stack
    COPY(destination, end);
    bilinear_line_to_destination(fr_mm_s, x_splits, y_splits);
  }

#endif // AUTO_BED_LEVELING_BILINEAR

#if IS_KINEMATIC && !UBL_DELTA

  /**
   * Prepare a linear move in a DELTA or SCARA setup.
   *
   * This calls planner.buffer_line several times, adding
   * small incremental moves for DELTA or SCARA.
   */
  inline bool prepare_kinematic_move_to(float ltarget[XYZE]) {

    // Get the top feedrate of the move in the XY plane
    const float _feedrate_mm_s = MMS_SCALED(feedrate_mm_s);

    // If the move is only in Z/E don't split up the move
    if (ltarget[X_AXIS] == current_position[X_AXIS] && ltarget[Y_AXIS] == current_position[Y_AXIS]) {
      planner.buffer_line_kinematic(ltarget, _feedrate_mm_s, active_extruder);
      return false;
    }

    // Fail if attempting move outside printable radius
    if (!position_is_reachable_xy(ltarget[X_AXIS], ltarget[Y_AXIS])) return true;

    // Get the cartesian distances moved in XYZE
    const float difference[XYZE] = {
      ltarget[X_AXIS] - current_position[X_AXIS],
      ltarget[Y_AXIS] - current_position[Y_AXIS],
      ltarget[Z_AXIS] - current_position[Z_AXIS],
      ltarget[E_AXIS] - current_position[E_AXIS]
    };

    // Get the linear distance in XYZ
    float cartesian_mm = SQRT(sq(difference[X_AXIS]) + sq(difference[Y_AXIS]) + sq(difference[Z_AXIS]));

    // If the move is very short, check the E move distance
    if (UNEAR_ZERO(cartesian_mm)) cartesian_mm = FABS(difference[E_AXIS]);

    // No E move either? Game over.
    if (UNEAR_ZERO(cartesian_mm)) return true;

    // Minimum number of seconds to move the given distance
    const float seconds = cartesian_mm / _feedrate_mm_s;

    // The number of segments-per-second times the duration
    // gives the number of segments
    uint16_t segments = delta_segments_per_second * seconds;

    // For SCARA minimum segment size is 0.25mm
    #if IS_SCARA
      NOMORE(segments, cartesian_mm * 4);
    #endif

    // At least one segment is required
    NOLESS(segments, 1);

    // The approximate length of each segment
    const float inv_segments = 1.0 / float(segments),
                segment_distance[XYZE] = {
                  difference[X_AXIS] * inv_segments,
                  difference[Y_AXIS] * inv_segments,
                  difference[Z_AXIS] * inv_segments,
                  difference[E_AXIS] * inv_segments
                };

    // SERIAL_ECHOPAIR("mm=", cartesian_mm);
    // SERIAL_ECHOPAIR(" seconds=", seconds);
    // SERIAL_ECHOLNPAIR(" segments=", segments);

    #if IS_SCARA && ENABLED(SCARA_FEEDRATE_SCALING)
      // SCARA needs to scale the feed rate from mm/s to degrees/s
      const float inv_segment_length = min(10.0, float(segments) / cartesian_mm), // 1/mm/segs
                  feed_factor = inv_segment_length * _feedrate_mm_s;
      float oldA = stepper.get_axis_position_degrees(A_AXIS),
            oldB = stepper.get_axis_position_degrees(B_AXIS);
    #endif

    // Get the logical current position as starting point
    float logical[XYZE];
    COPY(logical, current_position);

    // Drop one segment so the last move is to the exact target.
    // If there's only 1 segment, loops will be skipped entirely.
    --segments;

    // Calculate and execute the segments
    for (uint16_t s = segments + 1; --s;) {
      LOOP_XYZE(i) logical[i] += segment_distance[i];
      #if ENABLED(DELTA)
        DELTA_LOGICAL_IK(); // Delta can inline its kinematics
      #else
        inverse_kinematics(logical);
      #endif

      ADJUST_DELTA(logical); // Adjust Z if bed leveling is enabled

      #if IS_SCARA && ENABLED(SCARA_FEEDRATE_SCALING)
        // For SCARA scale the feed rate from mm/s to degrees/s
        // Use ratio between the length of the move and the larger angle change
        const float adiff = abs(delta[A_AXIS] - oldA),
                    bdiff = abs(delta[B_AXIS] - oldB);
        planner.buffer_line(delta[A_AXIS], delta[B_AXIS], delta[C_AXIS], logical[E_AXIS], max(adiff, bdiff) * feed_factor, active_extruder);
        oldA = delta[A_AXIS];
        oldB = delta[B_AXIS];
      #else
        planner.buffer_line(delta[A_AXIS], delta[B_AXIS], delta[C_AXIS], logical[E_AXIS], _feedrate_mm_s, active_extruder);
      #endif
    }

    // Since segment_distance is only approximate,
    // the final move must be to the exact destination.

    #if IS_SCARA && ENABLED(SCARA_FEEDRATE_SCALING)
      // For SCARA scale the feed rate from mm/s to degrees/s
      // With segments > 1 length is 1 segment, otherwise total length
      inverse_kinematics(ltarget);
      ADJUST_DELTA(ltarget);
      const float adiff = abs(delta[A_AXIS] - oldA),
                  bdiff = abs(delta[B_AXIS] - oldB);
      planner.buffer_line(delta[A_AXIS], delta[B_AXIS], delta[C_AXIS], logical[E_AXIS], max(adiff, bdiff) * feed_factor, active_extruder);
    #else
      planner.buffer_line_kinematic(ltarget, _feedrate_mm_s, active_extruder);
    #endif

    return false;
  }

#else // !IS_KINEMATIC || UBL_DELTA

  /**
   * Prepare a linear move in a Cartesian setup.
   * If Mesh Bed Leveling is enabled, perform a mesh move.
   *
   * Returns true if the caller didn't update current_position.
   */
  inline bool prepare_move_to_destination_cartesian() {
    #if ENABLED(AUTO_BED_LEVELING_UBL)
      const float fr_scaled = MMS_SCALED(feedrate_mm_s);
      if (ubl.state.active) { // direct use of ubl.state.active for speed
        ubl.line_to_destination_cartesian(fr_scaled, active_extruder);
        return true;
      }
      else
        line_to_destination(fr_scaled);
    #else
      // Do not use feedrate_percentage for E or Z only moves
      if (current_position[X_AXIS] == destination[X_AXIS] && current_position[Y_AXIS] == destination[Y_AXIS])
        line_to_destination();
      else {
        const float fr_scaled = MMS_SCALED(feedrate_mm_s);
        #if ENABLED(MESH_BED_LEVELING)
          if (mbl.active()) { // direct used of mbl.active() for speed
            mesh_line_to_destination(fr_scaled);
            return true;
          }
          else
        #elif ENABLED(AUTO_BED_LEVELING_BILINEAR)
          if (planner.abl_enabled) { // direct use of abl_enabled for speed
            bilinear_line_to_destination(fr_scaled);
            return true;
          }
          else
        #endif
            line_to_destination(fr_scaled);
      }
    #endif
    return false;
  }

#endif // !IS_KINEMATIC || UBL_DELTA

#if ENABLED(DUAL_X_CARRIAGE)

  /**
   * Prepare a linear move in a dual X axis setup
   */
  inline bool prepare_move_to_destination_dualx() {
    if (active_extruder_parked) {
      switch (dual_x_carriage_mode) {
        case DXC_FULL_CONTROL_MODE:
          break;
        case DXC_AUTO_PARK_MODE:
          if (current_position[E_AXIS] == destination[E_AXIS]) {
            // This is a travel move (with no extrusion)
            // Skip it, but keep track of the current position
            // (so it can be used as the start of the next non-travel move)
            if (delayed_move_time != 0xFFFFFFFFUL) {
              set_current_to_destination();
              NOLESS(raised_parked_position[Z_AXIS], destination[Z_AXIS]);
              delayed_move_time = millis();
              return true;
            }
          }
          // unpark extruder: 1) raise, 2) move into starting XY position, 3) lower
          for (uint8_t i = 0; i < 3; i++)
            planner.buffer_line(
              i == 0 ? raised_parked_position[X_AXIS] : current_position[X_AXIS],
              i == 0 ? raised_parked_position[Y_AXIS] : current_position[Y_AXIS],
              i == 2 ? current_position[Z_AXIS] : raised_parked_position[Z_AXIS],
              current_position[E_AXIS],
              i == 1 ? PLANNER_XY_FEEDRATE() : planner.max_feedrate_mm_s[Z_AXIS],
              active_extruder
            );
          delayed_move_time = 0;
          active_extruder_parked = false;
          #if ENABLED(DEBUG_LEVELING_FEATURE)
            if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("Clear active_extruder_parked");
          #endif
          break;
        case DXC_DUPLICATION_MODE:
          if (active_extruder == 0) {
            #if ENABLED(DEBUG_LEVELING_FEATURE)
              if (DEBUGGING(LEVELING)) {
                SERIAL_ECHOPAIR("Set planner X", LOGICAL_X_POSITION(inactive_extruder_x_pos));
                SERIAL_ECHOLNPAIR(" ... Line to X", current_position[X_AXIS] + duplicate_extruder_x_offset);
              }
            #endif
            // move duplicate extruder into correct duplication position.
            planner.set_position_mm(
              LOGICAL_X_POSITION(inactive_extruder_x_pos),
              current_position[Y_AXIS],
              current_position[Z_AXIS],
              current_position[E_AXIS]
            );
            planner.buffer_line(
              current_position[X_AXIS] + duplicate_extruder_x_offset,
              current_position[Y_AXIS], current_position[Z_AXIS], current_position[E_AXIS],
              planner.max_feedrate_mm_s[X_AXIS], 1
            );
            SYNC_PLAN_POSITION_KINEMATIC();
            stepper.synchronize();
            extruder_duplication_enabled = true;
            active_extruder_parked = false;
            #if ENABLED(DEBUG_LEVELING_FEATURE)
              if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("Set extruder_duplication_enabled\nClear active_extruder_parked");
            #endif
          }
          else {
            #if ENABLED(DEBUG_LEVELING_FEATURE)
              if (DEBUGGING(LEVELING)) SERIAL_ECHOLNPGM("Active extruder not 0");
            #endif
          }
          break;
      }
    }
    return false;
  }

#endif // DUAL_X_CARRIAGE

/**
 * Prepare a single move and get ready for the next one
 *
 * This may result in several calls to planner.buffer_line to
 * do smaller moves for DELTA, SCARA, mesh moves, etc.
 */
void prepare_move_to_destination() {
  clamp_to_software_endstops(destination);
  refresh_cmd_timeout();

  #if ENABLED(PREVENT_COLD_EXTRUSION)

    if (!DEBUGGING(DRYRUN)) {
      if (destination[E_AXIS] != current_position[E_AXIS]) {
        if (thermalManager.tooColdToExtrude(active_extruder)) {
          current_position[E_AXIS] = destination[E_AXIS]; // Behave as if the move really took place, but ignore E part
          SERIAL_ECHO_START();
          SERIAL_ECHOLNPGM(MSG_ERR_COLD_EXTRUDE_STOP);
        }
        #if ENABLED(PREVENT_LENGTHY_EXTRUDE)
          if (destination[E_AXIS] - current_position[E_AXIS] > EXTRUDE_MAXLENGTH) {
            current_position[E_AXIS] = destination[E_AXIS]; // Behave as if the move really took place, but ignore E part
            SERIAL_ECHO_START();
            SERIAL_ECHOLNPGM(MSG_ERR_LONG_EXTRUDE_STOP);
          }
        #endif
      }
    }

  #endif

  if (
    #if UBL_DELTA // Also works for CARTESIAN (smaller segments follow mesh more closely)
      ubl.prepare_segmented_line_to(destination, feedrate_mm_s)
    #elif IS_KINEMATIC
      prepare_kinematic_move_to(destination)
    #elif ENABLED(DUAL_X_CARRIAGE)
      prepare_move_to_destination_dualx()
    #else
      prepare_move_to_destination_cartesian()
    #endif
  ) return;

  set_current_to_destination();
}

#if ENABLED(ARC_SUPPORT)

  #if N_ARC_CORRECTION < 1
    #undef N_ARC_CORRECTION
    #define N_ARC_CORRECTION 1
  #endif

  /**
   * Plan an arc in 2 dimensions
   *
   * The arc is approximated by generating many small linear segments.
   * The length of each segment is configured in MM_PER_ARC_SEGMENT (Default 1mm)
   * Arcs should only be made relatively large (over 5mm), as larger arcs with
   * larger segments will tend to be more efficient. Your slicer should have
   * options for G2/G3 arc generation. In future these options may be GCode tunable.
   */
  void plan_arc(
    float logical[XYZE], // Destination position
    float *offset,       // Center of rotation relative to current_position
    uint8_t clockwise    // Clockwise?
  ) {
    #if ENABLED(CNC_WORKSPACE_PLANES)
      AxisEnum p_axis, q_axis, l_axis;
      switch (workspace_plane) {
        case PLANE_XY: p_axis = X_AXIS; q_axis = Y_AXIS; l_axis = Z_AXIS; break;
        case PLANE_ZX: p_axis = Z_AXIS; q_axis = X_AXIS; l_axis = Y_AXIS; break;
        case PLANE_YZ: p_axis = Y_AXIS; q_axis = Z_AXIS; l_axis = X_AXIS; break;
      }
    #else
      constexpr AxisEnum p_axis = X_AXIS, q_axis = Y_AXIS, l_axis = Z_AXIS;
    #endif

    // Radius vector from center to current location
    float r_P = -offset[0], r_Q = -offset[1];

    const float radius = HYPOT(r_P, r_Q),
                center_P = current_position[p_axis] - r_P,
                center_Q = current_position[q_axis] - r_Q,
                rt_X = logical[p_axis] - center_P,
                rt_Y = logical[q_axis] - center_Q,
                linear_travel = logical[l_axis] - current_position[l_axis],
                extruder_travel = logical[E_AXIS] - current_position[E_AXIS];

    // CCW angle of rotation between position and target from the circle center. Only one atan2() trig computation required.
    float angular_travel = ATAN2(r_P * rt_Y - r_Q * rt_X, r_P * rt_X + r_Q * rt_Y);
    if (angular_travel < 0) angular_travel += RADIANS(360);
    if (clockwise) angular_travel -= RADIANS(360);

    // Make a circle if the angular rotation is 0 and the target is current position
    if (angular_travel == 0 && current_position[p_axis] == logical[p_axis] && current_position[q_axis] == logical[q_axis])
      angular_travel = RADIANS(360);

    const float mm_of_travel = HYPOT(angular_travel * radius, FABS(linear_travel));
    if (mm_of_travel < 0.001) return;

    uint16_t segments = FLOOR(mm_of_travel / (MM_PER_ARC_SEGMENT));
    if (segments == 0) segments = 1;

    /**
     * Vector rotation by transformation matrix: r is the original vector, r_T is the rotated vector,
     * and phi is the angle of rotation. Based on the solution approach by Jens Geisler.
     *     r_T = [cos(phi) -sin(phi);
     *            sin(phi)  cos(phi)] * r ;
     *
     * For arc generation, the center of the circle is the axis of rotation and the radius vector is
     * defined from the circle center to the initial position. Each line segment is formed by successive
     * vector rotations. This requires only two cos() and sin() computations to form the rotation
     * matrix for the duration of the entire arc. Error may accumulate from numerical round-off, since
     * all double numbers are single precision on the Arduino. (True double precision will not have
     * round off issues for CNC applications.) Single precision error can accumulate to be greater than
     * tool precision in some cases. Therefore, arc path correction is implemented.
     *
     * Small angle approximation may be used to reduce computation overhead further. This approximation
     * holds for everything, but very small circles and large MM_PER_ARC_SEGMENT values. In other words,
     * theta_per_segment would need to be greater than 0.1 rad and N_ARC_CORRECTION would need to be large
     * to cause an appreciable drift error. N_ARC_CORRECTION~=25 is more than small enough to correct for
     * numerical drift error. N_ARC_CORRECTION may be on the order a hundred(s) before error becomes an
     * issue for CNC machines with the single precision Arduino calculations.
     *
     * This approximation also allows plan_arc to immediately insert a line segment into the planner
     * without the initial overhead of computing cos() or sin(). By the time the arc needs to be applied
     * a correction, the planner should have caught up to the lag caused by the initial plan_arc overhead.
     * This is important when there are successive arc motions.
     */
    // Vector rotation matrix values
    float arc_target[XYZE];
    const float theta_per_segment = angular_travel / segments,
                linear_per_segment = linear_travel / segments,
                extruder_per_segment = extruder_travel / segments,
                sin_T = theta_per_segment,
                cos_T = 1 - 0.5 * sq(theta_per_segment); // Small angle approximation

    // Initialize the linear axis
    arc_target[l_axis] = current_position[l_axis];

    // Initialize the extruder axis
    arc_target[E_AXIS] = current_position[E_AXIS];

    const float fr_mm_s = MMS_SCALED(feedrate_mm_s);

    millis_t next_idle_ms = millis() + 200UL;

    #if N_ARC_CORRECTION > 1
      int8_t count = N_ARC_CORRECTION;
    #endif

    for (uint16_t i = 1; i < segments; i++) { // Iterate (segments-1) times

      thermalManager.manage_heater();
      if (ELAPSED(millis(), next_idle_ms)) {
        next_idle_ms = millis() + 200UL;
        idle();
      }

      #if N_ARC_CORRECTION > 1
        if (--count) {
          // Apply vector rotation matrix to previous r_P / 1
          const float r_new_Y = r_P * sin_T + r_Q * cos_T;
          r_P = r_P * cos_T - r_Q * sin_T;
          r_Q = r_new_Y;
        }
        else
      #endif
      {
        #if N_ARC_CORRECTION > 1
          count = N_ARC_CORRECTION;
        #endif

        // Arc correction to radius vector. Computed only every N_ARC_CORRECTION increments.
        // Compute exact location by applying transformation matrix from initial radius vector(=-offset).
        // To reduce stuttering, the sin and cos could be computed at different times.
        // For now, compute both at the same time.
        const float cos_Ti = cos(i * theta_per_segment), sin_Ti = sin(i * theta_per_segment);
        r_P = -offset[0] * cos_Ti + offset[1] * sin_Ti;
        r_Q = -offset[0] * sin_Ti - offset[1] * cos_Ti;
      }

      // Update arc_target location
      arc_target[p_axis] = center_P + r_P;
      arc_target[q_axis] = center_Q + r_Q;
      arc_target[l_axis] += linear_per_segment;
      arc_target[E_AXIS] += extruder_per_segment;

      clamp_to_software_endstops(arc_target);

      planner.buffer_line_kinematic(arc_target, fr_mm_s, active_extruder);
    }

    // Ensure last segment arrives at target location.
    planner.buffer_line_kinematic(logical, fr_mm_s, active_extruder);

    // As far as the parser is concerned, the position is now == target. In reality the
    // motion control system might still be processing the action and the real tool position
    // in any intermediate location.
    set_current_to_destination();
  }
#endif

#if ENABLED(BEZIER_CURVE_SUPPORT)

  void plan_cubic_move(const float offset[4]) {
    cubic_b_spline(current_position, destination, offset, MMS_SCALED(feedrate_mm_s), active_extruder);

    // As far as the parser is concerned, the position is now == destination. In reality the
    // motion control system might still be processing the action and the real tool position
    // in any intermediate location.
    set_current_to_destination();
  }

#endif // BEZIER_CURVE_SUPPORT

#if ENABLED(USE_CONTROLLER_FAN)

  void controllerFan() {
    static millis_t lastMotorOn = 0, // Last time a motor was turned on
                    nextMotorCheck = 0; // Last time the state was checked
    const millis_t ms = millis();
    if (ELAPSED(ms, nextMotorCheck)) {
      nextMotorCheck = ms + 2500UL; // Not a time critical function, so only check every 2.5s
      if (X_ENABLE_READ == X_ENABLE_ON || Y_ENABLE_READ == Y_ENABLE_ON || Z_ENABLE_READ == Z_ENABLE_ON || thermalManager.soft_pwm_amount_bed > 0
          || E0_ENABLE_READ == E_ENABLE_ON // If any of the drivers are enabled...
          #if E_STEPPERS > 1
            || E1_ENABLE_READ == E_ENABLE_ON
            #if HAS_X2_ENABLE
              || X2_ENABLE_READ == X_ENABLE_ON
            #endif
            #if E_STEPPERS > 2
              || E2_ENABLE_READ == E_ENABLE_ON
              #if E_STEPPERS > 3
                || E3_ENABLE_READ == E_ENABLE_ON
                #if E_STEPPERS > 4
                  || E4_ENABLE_READ == E_ENABLE_ON
                #endif // E_STEPPERS > 4
              #endif // E_STEPPERS > 3
            #endif // E_STEPPERS > 2
          #endif // E_STEPPERS > 1
      ) {
        lastMotorOn = ms; //... set time to NOW so the fan will turn on
      }

      // Fan off if no steppers have been enabled for CONTROLLERFAN_SECS seconds
      uint8_t speed = (!lastMotorOn || ELAPSED(ms, lastMotorOn + (CONTROLLERFAN_SECS) * 1000UL)) ? 0 : CONTROLLERFAN_SPEED;

      // allows digital or PWM fan output to be used (see M42 handling)
      WRITE(CONTROLLER_FAN_PIN, speed);
      analogWrite(CONTROLLER_FAN_PIN, speed);
    }
  }

#endif // USE_CONTROLLER_FAN

#if ENABLED(MORGAN_SCARA)

  /**
   * Morgan SCARA Forward Kinematics. Results in cartes[].
   * Maths and first version by QHARLEY.
   * Integrated into Marlin and slightly restructured by Joachim Cerny.
   */
  void forward_kinematics_SCARA(const float &a, const float &b) {

    float a_sin = sin(RADIANS(a)) * L1,
          a_cos = cos(RADIANS(a)) * L1,
          b_sin = sin(RADIANS(b)) * L2,
          b_cos = cos(RADIANS(b)) * L2;

    cartes[X_AXIS] = a_cos + b_cos + SCARA_OFFSET_X;  //theta
    cartes[Y_AXIS] = a_sin + b_sin + SCARA_OFFSET_Y;  //theta+phi

    /*
      SERIAL_ECHOPAIR("SCARA FK Angle a=", a);
      SERIAL_ECHOPAIR(" b=", b);
      SERIAL_ECHOPAIR(" a_sin=", a_sin);
      SERIAL_ECHOPAIR(" a_cos=", a_cos);
      SERIAL_ECHOPAIR(" b_sin=", b_sin);
      SERIAL_ECHOLNPAIR(" b_cos=", b_cos);
      SERIAL_ECHOPAIR(" cartes[X_AXIS]=", cartes[X_AXIS]);
      SERIAL_ECHOLNPAIR(" cartes[Y_AXIS]=", cartes[Y_AXIS]);
    //*/
  }

  /**
   * Morgan SCARA Inverse Kinematics. Results in delta[].
   *
   * See http://forums.reprap.org/read.php?185,283327
   *
   * Maths and first version by QHARLEY.
   * Integrated into Marlin and slightly restructured by Joachim Cerny.
   */
  void inverse_kinematics(const float logical[XYZ]) {

    static float C2, S2, SK1, SK2, THETA, PSI;

    float sx = RAW_X_POSITION(logical[X_AXIS]) - SCARA_OFFSET_X,  // Translate SCARA to standard X Y
          sy = RAW_Y_POSITION(logical[Y_AXIS]) - SCARA_OFFSET_Y;  // With scaling factor.

    if (L1 == L2)
      C2 = HYPOT2(sx, sy) / L1_2_2 - 1;
    else
      C2 = (HYPOT2(sx, sy) - (L1_2 + L2_2)) / (2.0 * L1 * L2);

    S2 = SQRT(1 - sq(C2));

    // Unrotated Arm1 plus rotated Arm2 gives the distance from Center to End
    SK1 = L1 + L2 * C2;

    // Rotated Arm2 gives the distance from Arm1 to Arm2
    SK2 = L2 * S2;

    // Angle of Arm1 is the difference between Center-to-End angle and the Center-to-Elbow
    THETA = ATAN2(SK1, SK2) - ATAN2(sx, sy);

    // Angle of Arm2
    PSI = ATAN2(S2, C2);

    delta[A_AXIS] = DEGREES(THETA);        // theta is support arm angle
    delta[B_AXIS] = DEGREES(THETA + PSI);  // equal to sub arm angle (inverted motor)
    delta[C_AXIS] = logical[Z_AXIS];

    /*
      DEBUG_POS("SCARA IK", logical);
      DEBUG_POS("SCARA IK", delta);
      SERIAL_ECHOPAIR("  SCARA (x,y) ", sx);
      SERIAL_ECHOPAIR(",", sy);
      SERIAL_ECHOPAIR(" C2=", C2);
      SERIAL_ECHOPAIR(" S2=", S2);
      SERIAL_ECHOPAIR(" Theta=", THETA);
      SERIAL_ECHOLNPAIR(" Phi=", PHI);
    //*/
  }

#endif // MORGAN_SCARA

#if ENABLED(TEMP_STAT_LEDS)

  static bool red_led = false;
  static millis_t next_status_led_update_ms = 0;

  void handle_status_leds(void) {
    if (ELAPSED(millis(), next_status_led_update_ms)) {
      next_status_led_update_ms += 500; // Update every 0.5s
      float max_temp = 0.0;
      #if HAS_TEMP_BED
        max_temp = MAX3(max_temp, thermalManager.degTargetBed(), thermalManager.degBed());
      #endif
      HOTEND_LOOP()
        max_temp = MAX3(max_temp, thermalManager.degHotend(e), thermalManager.degTargetHotend(e));
      const bool new_led = (max_temp > 55.0) ? true : (max_temp < 54.0) ? false : red_led;
      if (new_led != red_led) {
        red_led = new_led;
        #if PIN_EXISTS(STAT_LED_RED)
          WRITE(STAT_LED_RED_PIN, new_led ? HIGH : LOW);
          #if PIN_EXISTS(STAT_LED_BLUE)
            WRITE(STAT_LED_BLUE_PIN, new_led ? LOW : HIGH);
          #endif
        #else
          WRITE(STAT_LED_BLUE_PIN, new_led ? HIGH : LOW);
        #endif
      }
    }
  }

#endif

#if ENABLED(FILAMENT_RUNOUT_SENSOR)

  void handle_filament_runout() {
    if (!filament_ran_out) {
      filament_ran_out = true;
      enqueue_and_echo_commands_P(PSTR(FILAMENT_RUNOUT_SCRIPT));
      stepper.synchronize();
    }
  }

#endif // FILAMENT_RUNOUT_SENSOR

#if ENABLED(FAST_PWM_FAN)

  void setPwmFrequency(uint8_t pin, int val) {
    val &= 0x07;
    switch (digitalPinToTimer(pin)) {
      #ifdef TCCR0A
        #if !AVR_AT90USB1286_FAMILY
          case TIMER0A:
        #endif
        case TIMER0B:
          //_SET_CS(0, val);
          break;
      #endif
      #ifdef TCCR1A
        case TIMER1A:
        case TIMER1B:
          //_SET_CS(1, val);
          break;
      #endif
      #ifdef TCCR2
        case TIMER2:
        case TIMER2:
          _SET_CS(2, val);
          break;
      #endif
      #ifdef TCCR2A
        case TIMER2A:
        case TIMER2B:
          _SET_CS(2, val);
          break;
      #endif
      #ifdef TCCR3A
        case TIMER3A:
        case TIMER3B:
        case TIMER3C:
          _SET_CS(3, val);
          break;
      #endif
      #ifdef TCCR4A
        case TIMER4A:
        case TIMER4B:
        case TIMER4C:
          _SET_CS(4, val);
          break;
      #endif
      #ifdef TCCR5A
        case TIMER5A:
        case TIMER5B:
        case TIMER5C:
          _SET_CS(5, val);
          break;
      #endif
    }
  }

#endif // FAST_PWM_FAN

float calculate_volumetric_multiplier(float diameter) {
  if (!volumetric_enabled || diameter == 0) return 1.0;
  return 1.0 / (M_PI * sq(diameter * 0.5));
}

void calculate_volumetric_multipliers() {
  for (uint8_t i = 0; i < COUNT(filament_size); i++)
    volumetric_multiplier[i] = calculate_volumetric_multiplier(filament_size[i]);
}

void enable_all_steppers() {
  enable_X();
  enable_Y();
  enable_Z();
  enable_E0();
  enable_E1();
  enable_E2();
  enable_E3();
  enable_E4();
}

void disable_e_steppers() {
  disable_E0();
  disable_E1();
  disable_E2();
  disable_E3();
  disable_E4();
}

void disable_all_steppers() {
  disable_X();
  disable_Y();
  disable_Z();
  disable_e_steppers();
}

#if ENABLED(HAVE_TMC2130)

  void automatic_current_control(TMC2130Stepper &st, String axisID) {
    // Check otpw even if we don't use automatic control. Allows for flag inspection.
    const bool is_otpw = st.checkOT();

    // Report if a warning was triggered
    static bool previous_otpw = false;
    if (is_otpw && !previous_otpw) {
      char timestamp[10];
      duration_t elapsed = print_job_timer.duration();
      const bool has_days = (elapsed.value > 60*60*24L);
      (void)elapsed.toDigital(timestamp, has_days);
      SERIAL_ECHO(timestamp);
      SERIAL_ECHOPGM(": ");
      SERIAL_ECHO(axisID);
      SERIAL_ECHOLNPGM(" driver overtemperature warning!");
    }
    previous_otpw = is_otpw;

    #if CURRENT_STEP > 0 && ENABLED(AUTOMATIC_CURRENT_CONTROL)
      // Return if user has not enabled current control start with M906 S1.
      if (!auto_current_control) return;

      /**
       * Decrease current if is_otpw is true.
       * Bail out if driver is disabled.
       * Increase current if OTPW has not been triggered yet.
       */
      uint16_t current = st.getCurrent();
      if (is_otpw) {
        st.setCurrent(current - CURRENT_STEP, R_SENSE, HOLD_MULTIPLIER);
        #if ENABLED(REPORT_CURRENT_CHANGE)
          SERIAL_ECHO(axisID);
          SERIAL_ECHOPAIR(" current decreased to ", st.getCurrent());
        #endif
      }

      else if (!st.isEnabled())
        return;

      else if (!is_otpw && !st.getOTPW()) {
        current += CURRENT_STEP;
        if (current <= AUTO_ADJUST_MAX) {
          st.setCurrent(current, R_SENSE, HOLD_MULTIPLIER);
          #if ENABLED(REPORT_CURRENT_CHANGE)
            SERIAL_ECHO(axisID);
            SERIAL_ECHOPAIR(" current increased to ", st.getCurrent());
          #endif
        }
      }
      SERIAL_EOL();
    #endif
  }

  void checkOverTemp() {
    static millis_t next_cOT = 0;
    if (ELAPSED(millis(), next_cOT)) {
      next_cOT = millis() + 5000;
      #if ENABLED(X_IS_TMC2130)
        automatic_current_control(stepperX, "X");
      #endif
      #if ENABLED(Y_IS_TMC2130)
        automatic_current_control(stepperY, "Y");
      #endif
      #if ENABLED(Z_IS_TMC2130)
        automatic_current_control(stepperZ, "Z");
      #endif
      #if ENABLED(X2_IS_TMC2130)
        automatic_current_control(stepperX2, "X2");
      #endif
      #if ENABLED(Y2_IS_TMC2130)
        automatic_current_control(stepperY2, "Y2");
      #endif
      #if ENABLED(Z2_IS_TMC2130)
        automatic_current_control(stepperZ2, "Z2");
      #endif
      #if ENABLED(E0_IS_TMC2130)
        automatic_current_control(stepperE0, "E0");
      #endif
      #if ENABLED(E1_IS_TMC2130)
        automatic_current_control(stepperE1, "E1");
      #endif
      #if ENABLED(E2_IS_TMC2130)
        automatic_current_control(stepperE2, "E2");
      #endif
      #if ENABLED(E3_IS_TMC2130)
        automatic_current_control(stepperE3, "E3");
      #endif
      #if ENABLED(E4_IS_TMC2130)
        automatic_current_control(stepperE4, "E4");
      #endif
      #if ENABLED(E4_IS_TMC2130)
        automatic_current_control(stepperE4);
      #endif
    }
  }

#endif // HAVE_TMC2130

/**
 * Manage several activities:
 *  - Check for Filament Runout
 *  - Keep the command buffer full
 *  - Check for maximum inactive time between commands
 *  - Check for maximum inactive time between stepper commands
 *  - Check if pin CHDK needs to go LOW
 *  - Check for KILL button held down
 *  - Check for HOME button held down
 *  - Check if cooling fan needs to be switched on
 *  - Check if an idle but hot extruder needs filament extruded (EXTRUDER_RUNOUT_PREVENT)
 */
void manage_inactivity(bool ignore_stepper_queue/*=false*/) {

  #if ENABLED(FILAMENT_RUNOUT_SENSOR)
    if ((IS_SD_PRINTING || print_job_timer.isRunning()) && (READ(FIL_RUNOUT_PIN) == FIL_RUNOUT_INVERTING))
      handle_filament_runout();
  #endif

  if (commands_in_queue < BUFSIZE) get_available_commands();

  const millis_t ms = millis();

  if (max_inactive_time && ELAPSED(ms, previous_cmd_ms + max_inactive_time)) {
    SERIAL_ERROR_START();
    SERIAL_ECHOLNPAIR(MSG_KILL_INACTIVE_TIME, parser.command_ptr);
    kill(PSTR(MSG_KILLED));
  }

  // Prevent steppers timing-out in the middle of M600
  #if ENABLED(ADVANCED_PAUSE_FEATURE) && ENABLED(PAUSE_PARK_NO_STEPPER_TIMEOUT)
    #define MOVE_AWAY_TEST !move_away_flag
  #else
    #define MOVE_AWAY_TEST true
  #endif

  if (MOVE_AWAY_TEST && stepper_inactive_time && ELAPSED(ms, previous_cmd_ms + stepper_inactive_time)
      && !ignore_stepper_queue && !planner.blocks_queued()) {
    #if ENABLED(DISABLE_INACTIVE_X)
      disable_X();
    #endif
    #if ENABLED(DISABLE_INACTIVE_Y)
      disable_Y();
    #endif
    #if ENABLED(DISABLE_INACTIVE_Z)
      disable_Z();
    #endif
    #if ENABLED(DISABLE_INACTIVE_E)
      disable_e_steppers();
    #endif
    #if ENABLED(AUTO_BED_LEVELING_UBL) && ENABLED(ULTRA_LCD)  // Only needed with an LCD
      ubl_lcd_map_control = defer_return_to_status = false;
    #endif
  }

  #ifdef CHDK // Check if pin should be set to LOW after M240 set it to HIGH
    if (chdkActive && ELAPSED(ms, chdkHigh + CHDK_DELAY)) {
      chdkActive = false;
      WRITE(CHDK, LOW);
    }
  #endif

  #if HAS_KILL

    // Check if the kill button was pressed and wait just in case it was an accidental
    // key kill key press
    // -------------------------------------------------------------------------------
    static int killCount = 0;   // make the inactivity button a bit less responsive
    const int KILL_DELAY = 750;
    if (!READ(KILL_PIN))
      killCount++;
    else if (killCount > 0)
      killCount--;

    // Exceeded threshold and we can confirm that it was not accidental
    // KILL the machine
    // ----------------------------------------------------------------
    if (killCount >= KILL_DELAY) {
      SERIAL_ERROR_START();
      SERIAL_ERRORLNPGM(MSG_KILL_BUTTON);
      kill(PSTR(MSG_KILLED));
    }
  #endif

  #if HAS_HOME
    // Check to see if we have to home, use poor man's debouncer
    // ---------------------------------------------------------
    static int homeDebounceCount = 0;   // poor man's debouncing count
    const int HOME_DEBOUNCE_DELAY = 2500;
    if (!IS_SD_PRINTING && !READ(HOME_PIN)) {
      if (!homeDebounceCount) {
        enqueue_and_echo_commands_P(PSTR("G28"));
        LCD_MESSAGEPGM(MSG_AUTO_HOME);
      }
      if (homeDebounceCount < HOME_DEBOUNCE_DELAY)
        homeDebounceCount++;
      else
        homeDebounceCount = 0;
    }
  #endif

  #if ENABLED(USE_CONTROLLER_FAN)
    controllerFan(); // Check if fan should be turned on to cool stepper drivers down
  #endif

  #if ENABLED(EXTRUDER_RUNOUT_PREVENT)
    if (ELAPSED(ms, previous_cmd_ms + (EXTRUDER_RUNOUT_SECONDS) * 1000UL)
      && thermalManager.degHotend(active_extruder) > EXTRUDER_RUNOUT_MINTEMP) {
      bool oldstatus;
      #if ENABLED(SWITCHING_EXTRUDER)
        oldstatus = E0_ENABLE_READ;
        enable_E0();
      #else // !SWITCHING_EXTRUDER
        switch (active_extruder) {
          case 0: oldstatus = E0_ENABLE_READ; enable_E0(); break;
          #if E_STEPPERS > 1
            case 1: oldstatus = E1_ENABLE_READ; enable_E1(); break;
            #if E_STEPPERS > 2
              case 2: oldstatus = E2_ENABLE_READ; enable_E2(); break;
              #if E_STEPPERS > 3
                case 3: oldstatus = E3_ENABLE_READ; enable_E3(); break;
                #if E_STEPPERS > 4
                  case 4: oldstatus = E4_ENABLE_READ; enable_E4(); break;
                #endif // E_STEPPERS > 4
              #endif // E_STEPPERS > 3
            #endif // E_STEPPERS > 2
          #endif // E_STEPPERS > 1
        }
      #endif // !SWITCHING_EXTRUDER

      previous_cmd_ms = ms; // refresh_cmd_timeout()

      const float olde = current_position[E_AXIS];
      current_position[E_AXIS] += EXTRUDER_RUNOUT_EXTRUDE;
      planner.buffer_line_kinematic(current_position, MMM_TO_MMS(EXTRUDER_RUNOUT_SPEED), active_extruder);
      current_position[E_AXIS] = olde;
      planner.set_e_position_mm(olde);
      stepper.synchronize();
      #if ENABLED(SWITCHING_EXTRUDER)
        E0_ENABLE_WRITE(oldstatus);
      #else
        switch (active_extruder) {
          case 0: E0_ENABLE_WRITE(oldstatus); break;
          #if E_STEPPERS > 1
            case 1: E1_ENABLE_WRITE(oldstatus); break;
            #if E_STEPPERS > 2
              case 2: E2_ENABLE_WRITE(oldstatus); break;
              #if E_STEPPERS > 3
                case 3: E3_ENABLE_WRITE(oldstatus); break;
                #if E_STEPPERS > 4
                  case 4: E4_ENABLE_WRITE(oldstatus); break;
                #endif // E_STEPPERS > 4
              #endif // E_STEPPERS > 3
            #endif // E_STEPPERS > 2
          #endif // E_STEPPERS > 1
        }
      #endif // !SWITCHING_EXTRUDER
    }
  #endif // EXTRUDER_RUNOUT_PREVENT

  #if ENABLED(DUAL_X_CARRIAGE)
    // handle delayed move timeout
    if (delayed_move_time && ELAPSED(ms, delayed_move_time + 1000UL) && IsRunning()) {
      // travel moves have been received so enact them
      delayed_move_time = 0xFFFFFFFFUL; // force moves to be done
      set_destination_to_current();
      prepare_move_to_destination();
    }
  #endif

  #if ENABLED(TEMP_STAT_LEDS)
    handle_status_leds();
  #endif

  #if ENABLED(HAVE_TMC2130)
    checkOverTemp();
  #endif

  planner.check_axes_activity();
}

/**
 * Standard idle routine keeps the machine alive
 */
void idle(
  #if ENABLED(ADVANCED_PAUSE_FEATURE)
    bool no_stepper_sleep/*=false*/
  #endif
) {
  lcd_update();

  host_keepalive();

  #if ENABLED(AUTO_REPORT_TEMPERATURES) && (HAS_TEMP_HOTEND || HAS_TEMP_BED)
    auto_report_temperatures();
  #endif

  manage_inactivity(
    #if ENABLED(ADVANCED_PAUSE_FEATURE)
      no_stepper_sleep
    #endif
  );

  thermalManager.manage_heater();

  #if ENABLED(PRINTCOUNTER)
    print_job_timer.tick();
  #endif

  #if HAS_BUZZER && DISABLED(LCD_USE_I2C_BUZZER)
    buzzer.tick();
  #endif

  #if ENABLED(I2C_POSITION_ENCODERS)
    if (planner.blocks_queued() &&
        ( (blockBufferIndexRef != planner.block_buffer_head) ||
          ((lastUpdateMillis + I2CPE_MIN_UPD_TIME_MS) < millis())) ) {
      blockBufferIndexRef = planner.block_buffer_head;
      I2CPEM.update();
      lastUpdateMillis = millis();
    }
  #endif
}

/**
 * Kill all activity and lock the machine.
 * After this the machine will need to be reset.
 */
void kill(const char* lcd_msg) {
  SERIAL_ERROR_START();
  SERIAL_ERRORLNPGM(MSG_ERR_KILLED);

  thermalManager.disable_all_heaters();
  disable_all_steppers();

  #if ENABLED(ULTRA_LCD)
    kill_screen(lcd_msg);
  #else
    UNUSED(lcd_msg);
  #endif

  _delay_ms(600); // Wait a short time (allows messages to get out before shutting down.
  cli(); // Stop interrupts

  _delay_ms(250); //Wait to ensure all interrupts routines stopped
  thermalManager.disable_all_heaters(); //turn off heaters again

  #if defined(ACTION_ON_KILL)
    SERIAL_ECHOLNPGM("//action:" ACTION_ON_KILL);
  #endif
  
  #if HAS_POWER_SWITCH
    SET_INPUT(PS_ON_PIN);
  #endif

  suicide();
  while (1) {
    #if ENABLED(USE_WATCHDOG)
      watchdog_reset();
    #endif
  } // Wait for reset
}

/**
 * Turn off heaters and stop the print in progress
 * After a stop the machine may be resumed with M999
 */
void stop() {
  thermalManager.disable_all_heaters(); // 'unpause' taken care of in here

  #if ENABLED(PROBING_FANS_OFF)
    if (fans_paused) fans_pause(false); // put things back the way they were
  #endif

  if (IsRunning()) {
    Stopped_gcode_LastN = gcode_LastN; // Save last g_code for restart
    SERIAL_ERROR_START();
    SERIAL_ERRORLNPGM(MSG_ERR_STOPPED);
    LCD_MESSAGEPGM(MSG_STOPPED);
    safe_delay(350);       // allow enough time for messages to get out before stopping
    Running = false;
  }
}

/**
 * Marlin entry-point: Set up before the program loop
 *  - Set up the kill pin, filament runout, power hold
 *  - Start the serial port
 *  - Print startup messages and diagnostics
 *  - Get EEPROM or default settings
 *  - Initialize managers for:
 *    • temperature
 *    • planner
 *    • watchdog
 *    • stepper
 *    • photo pin
 *    • servos
 *    • LCD controller
 *    • Digipot I2C
 *    • Z probe sled
 *    • status LEDs
 */
void setup() {

  #ifdef DISABLE_JTAG
    // Disable JTAG on AT90USB chips to free up pins for IO
    MCUCR = 0x80;
    MCUCR = 0x80;
  #endif

  #if ENABLED(FILAMENT_RUNOUT_SENSOR)
    setup_filrunoutpin();
  #endif

  setup_killpin();

  setup_powerhold();

  #if HAS_STEPPER_RESET
    disableStepperDrivers();
  #endif

  MYSERIAL.begin(BAUDRATE);
  SERIAL_PROTOCOLLNPGM("start");
  SERIAL_ECHO_START();

  // Check startup - does nothing if bootloader sets MCUSR to 0
  byte mcu = MCUSR;
  if (mcu &  1) SERIAL_ECHOLNPGM(MSG_POWERUP);
  if (mcu &  2) SERIAL_ECHOLNPGM(MSG_EXTERNAL_RESET);
  if (mcu &  4) SERIAL_ECHOLNPGM(MSG_BROWNOUT_RESET);
  if (mcu &  8) SERIAL_ECHOLNPGM(MSG_WATCHDOG_RESET);
  if (mcu & 32) SERIAL_ECHOLNPGM(MSG_SOFTWARE_RESET);
  MCUSR = 0;

  SERIAL_ECHOPGM(MSG_MARLIN);
  SERIAL_CHAR(' ');
  SERIAL_ECHOLNPGM(SHORT_BUILD_VERSION);
  SERIAL_EOL();

  #if defined(STRING_DISTRIBUTION_DATE) && defined(STRING_CONFIG_H_AUTHOR)
    SERIAL_ECHO_START();
    SERIAL_ECHOPGM(MSG_CONFIGURATION_VER);
    SERIAL_ECHOPGM(STRING_DISTRIBUTION_DATE);
    SERIAL_ECHOLNPGM(MSG_AUTHOR STRING_CONFIG_H_AUTHOR);
    SERIAL_ECHOLNPGM("Compiled: " __DATE__);
  #endif

  SERIAL_ECHO_START();
  SERIAL_ECHOPAIR(MSG_FREE_MEMORY, freeMemory());
  SERIAL_ECHOLNPAIR(MSG_PLANNER_BUFFER_BYTES, (int)sizeof(block_t)*BLOCK_BUFFER_SIZE);

  // Send "ok" after commands by default
  for (int8_t i = 0; i < BUFSIZE; i++) send_ok[i] = true;

  // Load data from EEPROM if available (or use defaults)
  // This also updates variables in the planner, elsewhere
  (void)settings.load();

  #if HAS_M206_COMMAND
    // Initialize current position based on home_offset
    COPY(current_position, home_offset);
  #else
    ZERO(current_position);
  #endif

  // Vital to init stepper/planner equivalent for current_position
  SYNC_PLAN_POSITION_KINEMATIC();

  thermalManager.init();    // Initialize temperature loop

  #if ENABLED(USE_WATCHDOG)
    watchdog_init();
  #endif

  stepper.init();    // Initialize stepper, this enables interrupts!
  servo_init();

  #if HAS_PHOTOGRAPH
    OUT_WRITE(PHOTOGRAPH_PIN, LOW);
  #endif

  #if HAS_CASE_LIGHT
    case_light_on = CASE_LIGHT_DEFAULT_ON;
    case_light_brightness = CASE_LIGHT_DEFAULT_BRIGHTNESS;
    update_case_light();
  #endif

  #if ENABLED(SPINDLE_LASER_ENABLE)
    OUT_WRITE(SPINDLE_LASER_ENABLE_PIN, !SPINDLE_LASER_ENABLE_INVERT);  // init spindle to off
    #if SPINDLE_DIR_CHANGE
      OUT_WRITE(SPINDLE_DIR_PIN, SPINDLE_INVERT_DIR ? 255 : 0);  // init rotation to clockwise (M3)
    #endif
    #if ENABLED(SPINDLE_LASER_PWM)
      SET_OUTPUT(SPINDLE_LASER_PWM_PIN);
      analogWrite(SPINDLE_LASER_PWM_PIN, SPINDLE_LASER_PWM_INVERT ? 255 : 0);  // set to lowest speed
    #endif
  #endif

  #if HAS_BED_PROBE
    endstops.enable_z_probe(false);
  #endif

  #if ENABLED(USE_CONTROLLER_FAN)
    SET_OUTPUT(CONTROLLER_FAN_PIN); //Set pin used for driver cooling fan
  #endif

  #if HAS_STEPPER_RESET
    enableStepperDrivers();
  #endif

  #if ENABLED(DIGIPOT_I2C)
    digipot_i2c_init();
  #endif

  #if ENABLED(DAC_STEPPER_CURRENT)
    dac_init();
  #endif

  #if (ENABLED(Z_PROBE_SLED) || ENABLED(SOLENOID_PROBE)) && HAS_SOLENOID_1
    OUT_WRITE(SOL1_PIN, LOW); // turn it off
  #endif

  #if HAS_HOME
    SET_INPUT_PULLUP(HOME_PIN);
  #endif

  #if PIN_EXISTS(STAT_LED_RED)
    OUT_WRITE(STAT_LED_RED_PIN, LOW); // turn it off
  #endif

  #if PIN_EXISTS(STAT_LED_BLUE)
    OUT_WRITE(STAT_LED_BLUE_PIN, LOW); // turn it off
  #endif

  #if ENABLED(RGB_LED) || ENABLED(RGBW_LED)
    SET_OUTPUT(RGB_LED_R_PIN);
    SET_OUTPUT(RGB_LED_G_PIN);
    SET_OUTPUT(RGB_LED_B_PIN);
    #if ENABLED(RGBW_LED)
      SET_OUTPUT(RGB_LED_W_PIN);
    #endif
  #endif

  #if ENABLED(MK2_MULTIPLEXER)
    SET_OUTPUT(E_MUX0_PIN);
    SET_OUTPUT(E_MUX1_PIN);
    SET_OUTPUT(E_MUX2_PIN);
  #endif

  lcd_init();

  #ifndef CUSTOM_BOOTSCREEN_TIMEOUT
    #define CUSTOM_BOOTSCREEN_TIMEOUT 2500
  #endif

  #if ENABLED(SHOW_BOOTSCREEN)
    #if ENABLED(DOGLCD)                           // On DOGM the first bootscreen is already drawn
      #if ENABLED(SHOW_CUSTOM_BOOTSCREEN)
        safe_delay(CUSTOM_BOOTSCREEN_TIMEOUT);    // Custom boot screen pause
        lcd_bootscreen();                         // Show Marlin boot screen
      #endif
      safe_delay(BOOTSCREEN_TIMEOUT);             // Pause
    #elif ENABLED(ULTRA_LCD)
      lcd_bootscreen();
      #if DISABLED(SDSUPPORT)
        lcd_init();
      #endif
    #endif
  #endif

  #if ENABLED(MIXING_EXTRUDER) && MIXING_VIRTUAL_TOOLS > 1
    // Initialize mixing to 100% color 1
    for (uint8_t i = 0; i < MIXING_STEPPERS; i++)
      mixing_factor[i] = (i == 0) ? 1.0 : 0.0;
    for (uint8_t t = 0; t < MIXING_VIRTUAL_TOOLS; t++)
      for (uint8_t i = 0; i < MIXING_STEPPERS; i++)
        mixing_virtual_tool_mix[t][i] = mixing_factor[i];
  #endif

  #if ENABLED(BLTOUCH)
    // Make sure any BLTouch error condition is cleared
    bltouch_command(BLTOUCH_RESET);
    set_bltouch_deployed(true);
    set_bltouch_deployed(false);
  #endif

  #if ENABLED(I2C_POSITION_ENCODERS)
    I2CPEM.init();
  #endif

  #if ENABLED(EXPERIMENTAL_I2CBUS) && I2C_SLAVE_ADDRESS > 0
    i2c.onReceive(i2c_on_receive);
    i2c.onRequest(i2c_on_request);
  #endif

  #if ENABLED(ENDSTOP_INTERRUPTS_FEATURE)
    setup_endstop_interrupts();
  #endif

  #if ENABLED(SWITCHING_EXTRUDER)
    move_extruder_servo(0);  // Initialize extruder servo
  #endif

  #if ENABLED(SWITCHING_NOZZLE)
    move_nozzle_servo(0);  // Initialize nozzle servo
  #endif
}

/**
 * The main Marlin program loop
 *
 *  - Save or log commands to SD
 *  - Process available commands (if not saving)
 *  - Call heater manager
 *  - Call inactivity manager
 *  - Call endstop manager
 *  - Call LCD update
 */
void loop() {
  if (commands_in_queue < BUFSIZE) get_available_commands();

  #if ENABLED(SDSUPPORT)
    card.checkautostart(false);
  #endif

  if (commands_in_queue) {

    #if ENABLED(SDSUPPORT)

      if (card.saving) {
        char* command = command_queue[cmd_queue_index_r];
        if (strstr_P(command, PSTR("M29"))) {
          // M29 closes the file
          card.closefile();
          SERIAL_PROTOCOLLNPGM(MSG_FILE_SAVED);
          ok_to_send();
        }
        else {
          // Write the string from the read buffer to SD
          card.write_command(command);
          if (card.logging)
            process_next_command(); // The card is saving because it's logging
          else
            ok_to_send();
        }
      }
      else
        process_next_command();

    #else

      process_next_command();

    #endif // SDSUPPORT

    // The queue may be reset by a command handler or by code invoked by idle() within a handler
    if (commands_in_queue) {
      --commands_in_queue;
      if (++cmd_queue_index_r >= BUFSIZE) cmd_queue_index_r = 0;
    }
  }
  endstops.report_state();
  idle();
}

