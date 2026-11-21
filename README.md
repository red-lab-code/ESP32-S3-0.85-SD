# ESP32-S3-0.85-SD

Demo projects for the ESP32-S3 with a 0.85-inch LCD.  
Project revised for use with Platformio/PioArduino IDE in VS code

## Folder structure

```
ESP32-S3-0.85-SD/
├── Shipped firmware/
│   └── ESP32-S3-0.85WeatherClock.bin # Precompiled firmware
├── lib/                              # Arduino libraries and dependencies
├── src/
│   ├── LVGL_WeatherClock/            # Main weather clock demo
│   ├── RGB_LCD/                      # RGB LCD demo
│   └── Video_demo/                   # Video playback demo
│       └── SD/
│           └── video/                # Videos. Copy to a FAT32 SD card
└── README.md
```

## Building

1. Install VS Code and PlatformIo or Pioarduino extension.
2. Open this folder and check that .ini file is detected.
3. Compile default environment to compile all the 3 demo projects.
4. Select a project and upload it to device.
