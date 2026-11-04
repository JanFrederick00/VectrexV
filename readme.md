# Vectrex-V

This device can generate a vector signal that can be displayed as X/Y on an oscilloscope or vector monitor.

The DACs used are MCP4811-devices featuring a built-in voltage reference, giving a stable output with a 10-bit range.

The DACs are connected to a CH32V003 microcontroller running at 48MHz. In practice the maximum output frequency on the DACs is about 60KHz, minus the time needed for calculations.

A third output channel is provided (Z) to control the beam brightness (on/off), which eliminates faint line when "jumping" from one position to another.

A simple 2-channel pulse wave audio output is provided.

A controller header can be used to connect a SNES/NES controller or potentially other styles of controllers, provided they use no more than 3 I/O pins.

# Firmware

Firmware is written in c++ (Arduino / PlatformIO). 

## Asteroids

As a proof-of-concept I implemented my own version of the classic Atari game "Asteroids". It is not meant to be a faithful recreation of the original, even though it re-uses the graphics from the Atari version.
This program uses more than 98% of the CH32's flash memory (for game code and graphics data), and thus is probably a good representation of the capabilities of this device.
