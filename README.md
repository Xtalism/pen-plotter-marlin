# Marlin CNC Pen Plotter

A custom Marlin firmware configuration for a 2-axis CNC pen plotter build. This project adapts the popular Marlin 3D printer firmware to control a pen plotting machine capable of drawing vector graphics and designs.

## Demonstration

## Features

- **2-Axis Control**: Precise X/Y movement for drawing applications
- **Servo Pen Control**: Automated pen lift/lower mechanism using servo motor
- **G-code Compatible**: Standard G-code interpretation for drawing commands
- **RAMPS 1.6 Based**: Uses standard 3D printer electronics (RAMPS 1.4 EFF)
- **PlatformIO Support**: Easy compilation and uploading using PlatformIO

## Hardware Requirements

- **Controller**: Arduino Mega 2560 with RAMPS 1.4 shield
- **Stepper Motors**: 2x stepper motors for X and Y axes
- **Servo Motor**: 1x servo for pen lift mechanism (connected to pin P0)
- **Stepper Drivers**: Compatible stepper motor drivers (A4988, DRV8825, etc.)
- **Power Supply**: 12V power supply for motors
- **Mechanical Frame**: Custom pen plotter frame (see blueprints/)

## Project Structure

```text
├── Marlin/                 # Modified Marlin firmware source code
├── gcode/                  # Example G-code files for testing
├── documentation/          # Project documentation (PDF)
├── blueprints/            # Hardware blueprints and schematics (PDF)
├── buildroot/             # Build tools and dependencies
├── platformio.ini         # PlatformIO configuration file
└── README.md              # This file
```

## Setup and Installation

### Prerequisites

1. Install [PlatformIO](https://platformio.org/) or use VS Code with PlatformIO extension
2. Clone this repository to your local machine

### Building and Uploading

1. Open the project in PlatformIO
2. Connect your Arduino Mega 2560 via USB
3. Build and upload the firmware:

   ```bash
   pio run --target upload
   ```

### Configuration

The main configuration is already set up for the pen plotter, but you may need to adjust:

- **Steps per mm**: Calibrate for your specific mechanical setup
- **Travel speeds**: Adjust drawing and travel speeds in `Configuration.h`
- **Servo angles**: Fine-tune pen up/down positions (currently S20 for down, S120 for up)

## Usage

### G-code Commands

The plotter responds to standard G-code commands:

- `G1 X## Y##`: Linear move to coordinates
- `G2/G3`: Circular/arc movements
- `M280 P0 S##`: Servo control (pen up/down)
  - `M280 P0 S20`: Pen down (drawing)
  - `M280 P0 S120`: Pen up (travel)
- `G28`: Home axes
- `G90`: Absolute positioning
- `G91`: Relative positioning

### Example Drawing Sequence

```gcode
M280 P0 S20        ; Pen up
G28 X Y            ; Home X and Y axes
G90                ; Absolute positioning
G1 F6000           ; Set feed rate
G1 X10 Y10         ; Move to start position
M280 P0 S120       ; Pen down
G1 X50 Y10         ; Draw line
G1 X50 Y50         ; Draw line
G1 X10 Y50         ; Draw line
G1 X10 Y10         ; Draw line (complete square)
M280 P0 S20        ; Pen up
```

## Sample Files

Check the `gcode/` directory for example drawing files. The included `UACJ.g` file demonstrates complex curved drawing using G2 arc commands.

## Documentation

- **Hardware Plans**: See `blueprints/blueprints.pdf` for mechanical drawings
- **Technical Documentation**: See `documentation/documentation.pdf` for detailed setup instructions

## Troubleshooting

### Common Issues

1. **Pen not lifting/lowering properly**
   - Check servo connections (should be connected to pin P0)
   - Adjust servo angle values in G-code (S20 for down, S120 for up)
   - Verify servo power supply

2. **Incorrect movement scaling**
   - Calibrate steps per mm in `Configuration.h`
   - Check belt tension and mechanical backlash

3. **Communication issues**
   - Verify baud rate settings (typically 250000)
   - Check USB cable and connections

## Contributing

This is a specialized firmware configuration. When making changes:

1. Test thoroughly with sample G-code
2. Document any configuration changes
3. Update this README if adding new features

## License

This project is based on Marlin firmware and inherits its GPL v3.0 license. See `LICENSE` file for details.

## Acknowledgments

- Based on [Marlin Firmware](https://github.com/MarlinFirmware/Marlin)
- Adapted for CNC pen plotting applications
- Thanks to the RepRap and maker communities for hardware designs

