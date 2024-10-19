
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

#include <stdio.h>
#include <string.h>
#include "include/io_test.h"
#include "esp_timer.h"
#include "esp_heap_caps.h"
#include "include/io_test.h"
#include "esp_log.h"

static const char *TAG = "sd_card_io_test"; // Log tag for identifying log messages
char *buffer = NULL;

void clear_and_open_file()
{
	// Clear the file; if the file does not exist, no action is taken
	remove(FILE_NAME);

	// Open the file in binary write mode
	FILE *f = fopen(FILE_NAME, "wb");
	if (f == NULL)
	{
		perror("Error opening file"); // Print error if file cannot be opened
		return;
	}

	// Close the file
	fclose(f);
}

void sd_card_io_test()
{

#ifdef WRITE_TEST_USE_PSRAM
	// Allocate memory in PSRAM
	buffer = (char *)heap_caps_malloc(TEST_SIZE, MALLOC_CAP_SPIRAM);
#else
	// Allocate memory in DRAM
	buffer = (char *)malloc(TEST_SIZE);
#endif

	// Open the file for writing
	clear_and_open_file();
	ESP_LOGI(TAG, "Opening file %s", FILE_NAME);
	FILE *f = fopen(FILE_NAME, "ab"); // Open file in append binary mode
	if (!f)
	{
		ESP_LOGE(TAG, "Failed to open file for writing"); // Log error if opening fails
		return;
	}
	else
	{
		ESP_LOGI(TAG, "File opened for writing");
	}

	if (buffer == NULL)
	{
		printf("Failed to allocate memory in PSRAM\n"); // Print error if memory allocation fails
		return;
	}

	memset(buffer, 'A', TEST_SIZE); // Fill the buffer with the character 'A'

	uint64_t total_time = 0; // Variable to store total elapsed time
	uint64_t peak_time = 0;	 // Variable to store peak write time
	uint64_t write_size = 0; // Variable to store total written size

	for (int i = 0; i < NUM_PACKETS; i++)
	{
		uint64_t start_time = esp_timer_get_time(); // Start timing
		fwrite(buffer, 1, TEST_SIZE, f);			// Write data to file
		uint64_t end_time = esp_timer_get_time();	// End timing

		uint64_t elapsed_time = end_time - start_time; // Calculate elapsed time
		total_time += elapsed_time;					   // Accumulate total time
		write_size += TEST_SIZE;					   // Accumulate total written size

		// Record peak time
		if (peak_time == 0)
		{
			peak_time = elapsed_time;
		}
		if (elapsed_time < peak_time)
		{
			peak_time = elapsed_time; // Update peak time if current is less
		}

		ESP_LOGI(TAG, "Packet %d written in %lld us", i + 1, elapsed_time); // Log write time
	}

	fclose(f); // Close the file

#ifdef WRITE_TEST_USE_PSRAM
	// Free the allocated memory in PSRAM
	heap_caps_free(buffer);
#else 
	// Free the allocated memory in DRAM
	free(buffer);
#endif

	// Calculate average write speed in KB/s
	double average_speed = (double)write_size / (total_time / 1000000.0) / 1024;
	double peak_speed = (double)(TEST_SIZE) / (peak_time / 1000000.0) / 1024; // Calculate peak speed in KB/s

	ESP_LOGI(TAG, "Total time: %lld us", total_time);				// Log total time
	ESP_LOGI(TAG, "Average write speed: %.2f KB/s", average_speed); // Log average speed
	ESP_LOGI(TAG, "Peak write speed: %.2f KB/s", peak_speed);		// Log peak speed
}
