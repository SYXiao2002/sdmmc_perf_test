/*MIT License

Copyright (c) [2024] [SYXiao2002]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef IO_TEST_H
#define IO_TEST_H

#define TEST_SIZE (1 * 1024 * 4)     // Size of each packet in bytes
#define NUM_PACKETS 5                // Total number of packets to be written
#define FILE_NAME "/sdcard/test.bin" // Name of the test file on the SD card
// #define WRITE_TEST_USE_PSRAM // Uncomment to use PSRAM for writing test

void sd_card_io_test(); // Function declaration for SD card I/O test

#endif // IO_TEST_H
