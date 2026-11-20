#pragma once
#include "Arduino.h"
#include <cstring>
#include "Display_ST7789.h"
#include "SD_MMC.h"
#include "FS.h"

// Digital I/O used for MMC/SD
#define SD_CS     15        // SD_D3 / CMD
#define SD_MOSI   16        // SD_CMD / DAT0
#define SD_MISO   18        // SD_DAT0 / DAT1
#define SD_SCK    17        // SD_CLK

extern uint16_t SDCard_Size;
extern uint16_t Flash_Size;

bool SD_Init();
void Flash_test();

bool File_Search(const char* directory, const char* fileName);
uint16_t Folder_retrieval(const char* directory, const char* fileExtension, char File_Name[][100],uint16_t maxFiles);
void remove_file_extension(char *file_name);
