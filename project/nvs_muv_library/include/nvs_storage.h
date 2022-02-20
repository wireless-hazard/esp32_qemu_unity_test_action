#include "nvs.h"

#ifdef __cplusplus
extern "C" {
#endif

nvs_handle_t nvs_open_partition(const char *partition);
esp_err_t nvs_read_int8(nvs_handle_t nvs_handle, const char *key, int8_t *value);
esp_err_t nvs_read_int16(nvs_handle_t nvs_handle, const char *key, int16_t *value);
esp_err_t nvs_read_int32(nvs_handle_t nvs_handle, const char *key, int32_t *value);
esp_err_t nvs_read_int64(nvs_handle_t nvs_handle, const char *key, int64_t *value);
esp_err_t nvs_read_string(nvs_handle_t nvs_handle, const char *key, char *value, size_t max_length);
esp_err_t nvs_write_int8(nvs_handle_t nvs_handle, const char *key, int8_t value);
esp_err_t nvs_write_int16(nvs_handle_t nvs_handle, const char *key, int16_t value);
esp_err_t nvs_write_int32(nvs_handle_t nvs_handle, const char *key, int32_t value);
esp_err_t nvs_write_int64(nvs_handle_t nvs_handle, const char *key, int64_t value);
esp_err_t nvs_write_string(nvs_handle_t nvs_handle, const char *key, const char *value);
esp_err_t nvs_close_partition(nvs_handle_t nvs_handle);

#ifdef __cplusplus
}
#endif