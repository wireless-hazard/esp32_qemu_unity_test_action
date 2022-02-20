#include "unity.h"
#include "nvs_flash.h"
#include "nvs_storage.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <string.h>

void setUp(void) {

}

void tearDown(void) {
}

TEST_CASE("open/close partition", "[open close]")
{
	nvs_handle_t handler = nvs_open_partition("partition");
	TEST_ASSERT_NOT_NULL(handler);
	esp_err_t err = nvs_close_partition(handler);
	TEST_ASSERT_EQUAL_INT(ESP_OK, err);
}

TEST_CASE("null_handler writing", "[null tests]")
{
	nvs_handle_t handler = NULL;
	esp_err_t err = nvs_write_int8(handler, "teste", 5);
	TEST_ASSERT_EQUAL_INT(ESP_ERR_INVALID_ARG, err);
	err = nvs_write_string(handler, "teste", "const char *value");
	TEST_ASSERT_EQUAL_INT(ESP_ERR_INVALID_ARG, err);
}

TEST_CASE("close without opening the partition", "[]"){
	nvs_handle_t handler = NULL;
	esp_err_t err = nvs_close_partition(handler);
	TEST_ASSERT_EQUAL_INT(ESP_ERR_INVALID_ARG, err);
}

TEST_CASE("wrong random handler", "[]"){
	nvs_handle_t handler = 25;
	esp_err_t err = nvs_write_int8(handler, "teste", 5);
	TEST_ASSERT_NOT_EQUAL(ESP_OK, err);
	err = nvs_write_string(handler, "teste", "const char *value");
	TEST_ASSERT_NOT_EQUAL(ESP_OK, err);
}

TEST_CASE("write/read value", "[]")
{
	nvs_handle_t handler = nvs_open_partition("partition");
	
	esp_err_t err = nvs_write_int32(handler, "key", 589);
	TEST_ASSERT_EQUAL_INT(ESP_OK, err);
	int32_t value = 0;

	err =  nvs_read_int32(handler, "key", &value);
	TEST_ASSERT_EQUAL_INT(ESP_OK, err);

	TEST_ASSERT_EQUAL_INT(589, value);

	err = nvs_close_partition(handler);
	TEST_ASSERT_EQUAL_INT(ESP_OK, err);	
}

TEST_CASE("write/read string", "[]")
{
	nvs_handle_t handler = nvs_open_partition("part");

	esp_err_t err = nvs_write_string(handler, "string", "const char *value");
	TEST_ASSERT_EQUAL_INT(ESP_OK, err);	

	char value[30];
	err = nvs_read_string(handler, "string", value, sizeof(value)/sizeof(char));
	TEST_ASSERT_EQUAL_INT(ESP_OK, err);	

	TEST_ASSERT_EQUAL_STRING("const char *value",value);

	err = nvs_close_partition(handler);
	TEST_ASSERT_EQUAL_INT(ESP_OK, err);		
}

TEST_CASE("out of bounds string", "[]")
{
	nvs_handle_t handler = nvs_open_partition("partasd");
	esp_err_t err = nvs_write_string(handler, "string", "So this is a story how about I moved from 7 different states");
	TEST_ASSERT_EQUAL_INT(ESP_OK, err);

	char tiny_array[15];
	err = nvs_read_string(handler, "string", tiny_array, sizeof(tiny_array)/sizeof(char));
	TEST_ASSERT_NOT_EQUAL(ESP_OK, err);

}