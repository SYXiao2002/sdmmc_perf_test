# ESP32: SD card I/O test using 1-line sdmmc

This repository does not initialize the SD card or the SDMMC peripheral. To use it, simply include the header file and call sd_card_io_test() after your own initialization.

# Example usage
```
#include "io_test.h"

void app_main(){
    // Your own code to initialize the SD card and the SDMMC peripheral, etc.
    // If you encounter issues using the SD card, refer to https://github.com/espressif/esp-idf/tree/master/examples/storage/sd_card/sdmmc
    ...
    ESP_LOGI(TAG, "Mounting filesystem");
    ret = esp_vfs_fat_sdmmc_mount(mount_point, &host, &slot_config, &mount_config, &card);
    ...

    // run io test
    sd_card_io_test();

    // Your own code to unmount partition and disable SDMMC peripheral
    esp_vfs_fat_sdcard_unmount(mount_point, card);
    ESP_LOGI(TAG, "Card unmounted");
}
```

## Setting in io_test.h
```
#define TEST_SIZE (1 * 1024 * 4)     // Size of each packet in bytes
#define NUM_PACKETS 5                // Total number of packets to be written
#define FILE_NAME "/sdcard/test.bin" // Name of the test file on the SD card
// #define WRITE_TEST_USE_PSRAM // Uncomment to use PSRAM for writing test
```