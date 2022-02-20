/* Non-Volatile Storage (NVS) Read and Write a Value - Example
   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "nvs_flash.h"
#include "esp_log.h"
#include "nvs.h"
#include "nvs_storage.h"

nvs_handle_t nvs_open_partition(const char *partition){
    
    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_LOGE("NVS","WAS TRUNCATED!!!");
        ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK_WITHOUT_ABORT( err );

    // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle...\n");
    nvs_handle_t nvs_handle;
    
    err = nvs_open(partition, NVS_READWRITE, &nvs_handle);
    ESP_ERROR_CHECK_WITHOUT_ABORT(err);
    if (err != ESP_OK) {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
        return (nvs_handle_t)0;
    }
    ESP_LOGI("NVS"," PARTITION OPEN: %s",partition);
    return nvs_handle; 
}

// READ
esp_err_t nvs_read_int8(nvs_handle_t nvs_handle, const char *key, int8_t *value){
	
	if (nvs_handle){
	    esp_err_t err = nvs_get_i8(nvs_handle, key, value);
	
		if (err != ESP_OK) {
			*value = -1;
		}		
	
		return err;
	}
	
	return ESP_ERR_INVALID_ARG;
}

esp_err_t nvs_read_int16(nvs_handle_t nvs_handle, const char *key, int16_t *value){

	if (nvs_handle){

		esp_err_t err = nvs_get_i16(nvs_handle, key, value);
	
		if (err != ESP_OK) {
			*value = -1;
		}		
	
		return err;
	}
	
	return ESP_ERR_INVALID_ARG;
}

esp_err_t nvs_read_int32(nvs_handle_t nvs_handle, const char *key, int32_t *value){

	if (nvs_handle){

		esp_err_t err = nvs_get_i32(nvs_handle, key, value);
	
		if (err != ESP_OK) {
			*value = -1;
		}		
	
		return err;
	}
	
	return ESP_ERR_INVALID_ARG;
}
    
	
esp_err_t nvs_read_int64(nvs_handle_t nvs_handle, const char *key, int64_t *value){

	if (nvs_handle){

		esp_err_t err = nvs_get_i64(nvs_handle, key, value);
	
		if (err != ESP_OK) {
			*value = -1;
		}		
	
		return err;
	}
	
	return ESP_ERR_INVALID_ARG;
}

esp_err_t nvs_read_string(nvs_handle_t nvs_handle, const char *key, char *value, size_t max_length){

	if (nvs_handle){
		
		size_t length = 0;
	
		esp_err_t err = nvs_get_str(nvs_handle, key, NULL, &length);
	
		if (err != ESP_OK) {
			return err;
		}
	
		if (max_length < length){
			return ESP_ERR_INVALID_SIZE;
		}
	
		err = nvs_get_str(nvs_handle, key, value, &length);	
	
		if (err != ESP_OK) {
			*value = -1;
		}		
	
		return err;
	}
	
	return ESP_ERR_INVALID_ARG;
}
	
// WRITE
esp_err_t nvs_write_int8(nvs_handle_t nvs_handle, const char *key, int8_t value){

	if (nvs_handle){
		
	    esp_err_t err = nvs_set_i8(nvs_handle, key, value);
	
		if (err != ESP_OK) {
			return err;
		}		
	
		err = nvs_commit(nvs_handle);
	
		return err;
	}
	
	return ESP_ERR_INVALID_ARG;
}

esp_err_t nvs_write_int16(nvs_handle_t nvs_handle, const char *key, int16_t value){

	if (nvs_handle){
		
	    esp_err_t err = nvs_set_i16(nvs_handle, key, value);
	
		if (err != ESP_OK) {
			return err;
		}		
	
		err = nvs_commit(nvs_handle);
	
		return err;
	}
	
	return ESP_ERR_INVALID_ARG;
}

esp_err_t nvs_write_int32(nvs_handle_t nvs_handle, const char *key, int32_t value){

	if (nvs_handle){
		
	    esp_err_t err = nvs_set_i32(nvs_handle, key, value);
	
		if (err != ESP_OK) {
			return err;
		}		
	
		err = nvs_commit(nvs_handle);
	
		return err;
	}
	
	return ESP_ERR_INVALID_ARG;
}

esp_err_t nvs_write_int64(nvs_handle_t nvs_handle, const char *key, int64_t value){

	if (nvs_handle){
		
	    esp_err_t err = nvs_set_i64(nvs_handle, key, value);
	
		if (err != ESP_OK) {
			return err;
		}		
	
		err = nvs_commit(nvs_handle);
	
		return err;
	}
	
	return ESP_ERR_INVALID_ARG;
}

esp_err_t nvs_write_string(nvs_handle_t nvs_handle, const char *key, const char *value){
		
	if (nvs_handle){
		
		esp_err_t err = nvs_set_str(nvs_handle, key, value);
	
		if (err != ESP_OK) {
			return err;
		}		
	
		err = nvs_commit(nvs_handle);
	
		return err;
	}
	
	return ESP_ERR_INVALID_ARG;
}

esp_err_t nvs_close_partition(nvs_handle_t nvs_handle){
	
	if(nvs_handle){
	
		nvs_close(nvs_handle);
		return ESP_OK;
	}
	
	return ESP_ERR_INVALID_ARG;
}



