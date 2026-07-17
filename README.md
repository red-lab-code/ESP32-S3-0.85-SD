# ESP32-S3-0.85-SD 

基于 ESP32-S3 + 0.85寸 LCD demo。

## 目录结构

```
ESP32-S3-0.85-demo/
├── Arduino/
│   ├── demo/
│   │   ├── LVGL_WeatherClock/   # 天气时钟主程序
│   │   ├── RGB_LCD/            # RGB LCD 测试
│   │   └── Video_demo/          # 视频播放测试
│   ├── libraries/              # Arduino 依赖库
│   └── SD/                     # SD 卡资源文件（视频等）
├── firmware/
│   └── ESP32-S3-0.85WeatherClock.bin   # 预编译固件
└── README.md
```

## 编译说明

1. 安装 Arduino IDE 或 PlatformIO
2. 将 `Arduino/libraries/` 下的库复制到 Arduino 库目录
3. 打开 `Arduino/demo/LVGL_WeatherClock/LVGL_WeatherClock.ino`
4. 选择 ESP32-S3 开发板，编译并烧录
