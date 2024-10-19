# Example to run io_test using 1-ling sdmmc on esp32-s3 n16r8



1. Configure flash size and psram type (quad or oct) in menuconfig, as well as the pin definition.

Note: In this example, we use [```sdkconfig.defaults```](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/kconfig.html#using-sdkconfig-defaults) to quickly generate a menuconfig specfically for [Freenove_ESP32_S3_WROOM_Board](https://github.com/Freenove/Freenove_ESP32_S3_WROOM_Board). You can define your own sd card's CLK, CMD, D0, D1, D2, D3 pins through menuconfig (See ''SD/MMC'').

2. Add component "sdmmc_perf_test" to your project, run:
```
idf.py add-dependency "syxiao2002/sdmmc_perf_test^1.0.0"
```

3. Build and flash, you should see following output like:
```
I (857) sd_card_io_test: Opening file /sdcard/test.bin
I (859) sd_card_io_test: File opened for writing
I (873) sd_card_io_test: Packet 1 written in 8968 us
I (883) sd_card_io_test: Packet 2 written in 8222 us
I (895) sd_card_io_test: Packet 3 written in 8404 us
I (906) sd_card_io_test: Packet 4 written in 8408 us
I (918) sd_card_io_test: Packet 5 written in 8589 us
I (926) sd_card_io_test: Total time: 42591 us
I (927) sd_card_io_test: Average write speed: 469.58 KB/s
I (932) sd_card_io_test: Peak write speed: 486.50 KB/s
I (938) example: Card unmounted
I (941) main_task: Returned from app_main()
```
