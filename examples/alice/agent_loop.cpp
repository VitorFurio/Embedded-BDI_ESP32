/*
 * agent_loop.cpp
 *
 *  Created on: Jun 28, 2020
 *      Author: Matuzalem Muller
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_task_wdt.h"


#include "agent/agent_comm.h"
#include "config/configuration.h"

#include <unistd.h>
#include <stdio.h>
#include "../data/functions.h"

extern "C" {
 	#include "../wifi_functions/wifi_station.h"
	void app_main(void);
}

void app_main()
{
	// # Cinfigurações da esp32:
	// Desativa o Task Watchdog Timer
	esp_task_wdt_deinit();
    
	//Wi-fi - Initialize NVS 
	//esp_err_t ret = nvs_flash_init();
	//if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	//ESP_ERROR_CHECK(nvs_flash_erase());
	//ret = nvs_flash_init();
	//}
	//ESP_ERROR_CHECK(ret);

	//ESP_LOGI(TAG, "ESP_WIFI_MODE_STA");
	wifi_init_sta();

	
  AgentSettings agent_settings;

  BeliefBase * beliefs = agent_settings.get_belief_base();
  EventBase * events = agent_settings.get_event_base();
  PlanBase * plans = agent_settings.get_plan_base();
  IntentionBase * intentions = agent_settings.get_intention_base();
  Communicator * communicator = agent_settings.get_communicator();
  
  communicator->initialize();
  
  AgentComm agent(beliefs, events, plans, intentions, communicator);
  
  while(true)
  {
    agent.run();
  }

  return;
}
