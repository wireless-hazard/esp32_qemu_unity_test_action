#include "unity.h"
#include "esp_system.h"
#include "sdkconfig.h"

#include "nvs_storage.h"

void app_main(void){

#ifndef CONFIG_RUN_UNITTESTS
	 printf("Hello world!\n");
#endif

	nvs_handle_t handler = nvs_open_partition("partition");
	
	UNITY_BEGIN();
	unity_run_all_tests();
	UNITY_END();
	// unity_run_menu();
	esp_restart();
}
