#include "SD_Card.h"

uint16_t SDCard_Size;
uint16_t Flash_Size;

bool SD_Init() {
  // MMC/SD卡初始化
  printf("Initializing MicroSD card with SD_MMC...\r\n");
  printf("Pin configuration: CS=%d, MOSI(CMD)=%d, CLK=%d, MISO(DAT0)=%d\r\n", 
         SD_CS, SD_MOSI, SD_SCK, SD_MISO);
  
  // 配置CS引脚为输出并拉高
  pinMode(SD_CS, OUTPUT);    
  digitalWrite(SD_CS, HIGH);
  
  // 短暂延时让SD卡稳定
  delay(100);
  
  // ESP32-S3的SD_MMC引脚配置
  printf("\r\nConfiguring SD_MMC pins...\r\n");
  bool pinResult = SD_MMC.setPins(SD_SCK, SD_MOSI, SD_MISO);
  printf("setPins result: %s\r\n", pinResult ? "OK" : "FAILED");
  
  if (!pinResult) {
    printf("Failed to configure SD_MMC pins!\r\n");
    return false;
  }
  
  // 尝试以1线模式初始化（最兼容的模式）
  printf("\r\nAttempting SD_MMC initialization in 1-line mode...\r\n");
  delay(50);
  
  // 使用自定义挂载点和1线模式
  if (!SD_MMC.begin("/sdcard", true)) {
    printf("\r\n========================================\r\n");
    printf("SD_MMC initialization FAILED!\r\n");
    printf("========================================\r\n");
    
    return false;
  }
  
  printf("\r\n✓ SD_MMC initialization successful!\r\n");
  
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
    printf("✗ No SD card detected!\r\n");
    return false;
  }
  
  printf("✓ Card detected successfully\r\n");
  printf("Card Type: ");
  if(cardType == CARD_MMC){
    printf("MMC\r\n");
  } else if(cardType == CARD_SD){
    printf("SDSC (Standard Capacity)\r\n");
  } else if(cardType == CARD_SDHC){
    printf("SDHC/SDXC (High/Extended Capacity)\r\n");
  } else {
    printf("UNKNOWN\r\n");
  }
  
  uint64_t totalBytes = SD_MMC.totalBytes();
  uint64_t usedBytes = SD_MMC.usedBytes();
  SDCard_Size = totalBytes/(1024*1024);
  
  printf("\r\nStorage Information:\r\n");
  printf("  Total: %llu MB (%.2f GB)\r\n", totalBytes/(1024*1024), totalBytes/(1024.0*1024*1024));
  printf("  Used:  %llu MB\r\n", usedBytes/(1024*1024));
  printf("  Free:  %llu MB\r\n", (totalBytes - usedBytes)/(1024*1024));
  printf("\r\nSD card ready to use!\r\n");
  
  return true;
}

bool File_Search(const char* directory, const char* fileName)    
{
  File Path = SD_MMC.open(directory);
  if (!Path) {
    printf("Path: <%s> does not exist\r\n",directory);
    return false;
  }
  File file = Path.openNextFile();
  while (file) {
    if (strcmp(file.name(), fileName) == 0) {                           
      if (strcmp(directory, "/") == 0)
        printf("File '%s%s' found in root directory.\r\n",directory,fileName);  
      else
        printf("File '%s/%s' found in root directory.\r\n",directory,fileName); 
      Path.close();                                                     
      return true;                                                     
    }
    file = Path.openNextFile();                                        
  }
  if (strcmp(directory, "/") == 0)
    printf("File '%s%s' not found in root directory.\r\n",directory,fileName);           
  else
    printf("File '%s/%s' not found in root directory.\r\n",directory,fileName);          
  Path.close();                                                         
  return false;                                                         
}

uint16_t Folder_retrieval(const char* directory, const char* fileExtension, char File_Name[][100],uint16_t maxFiles)    
{
  File Path = SD_MMC.open(directory);
  if (!Path) {
    printf("Path: <%s> does not exist\r\n",directory);
    return false;
  }
  
  uint16_t fileCount = 0;
  char filePath[100];
  File file = Path.openNextFile();
  while (file && fileCount < maxFiles) {
    if (!file.isDirectory() && strstr(file.name(), fileExtension)) {
      strncpy(File_Name[fileCount], file.name(), sizeof(File_Name[fileCount])); 
      if (strcmp(directory, "/") == 0) {                                      
        snprintf(filePath, 100, "%s%s", directory, file.name());   
      } else {                                                            
        snprintf(filePath, 100, "%s/%s", directory, file.name());
      }
      printf("File found: %s\r\n", filePath);
      fileCount++;
    }
    file = Path.openNextFile();                                       
  }
  Path.close();                                                         
  if (fileCount > 0) {
    printf(" %d <%s> files were retrieved\r\n",fileCount,fileExtension);
    return fileCount;                                                 
  } else {
    printf("No files with extension '%s' found in directory: %s\r\n", fileExtension, directory);
    return 0;                                                         
  }
}

void remove_file_extension(char *file_name) {
  char *last_dot = strrchr(file_name, '.');
  if (last_dot != NULL) {
    *last_dot = '\0'; 
  }
}

void Flash_test()
{
  printf("/********** RAM Test**********/\r\n");
  // Get Flash size
  uint32_t flashSize = ESP.getFlashChipSize();
  Flash_Size = flashSize/1024/1024;
  printf("Flash size: %d MB \r\n", flashSize/1024/1024);

  printf("/******* RAM Test Over********/\r\n\r\n");
}
