#include "freertos/FreeRTOS.h"
#include "freertos/portmacro.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "esp_sleep.h"

#include "nvs_storage.h"

extern "C" void app_main(){
  nvs_handle_t handler = nvs_open_partition("partition");

}
