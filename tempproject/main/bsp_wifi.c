/**
 **************************************************************************************************
 * @file        bsp_wifi.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "bsp_wifi.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "string.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
/**
 * @addtogroup    bsp_wifi_Modules 
 * @{  
 */

/**
 * @defgroup      bsp_wifi_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_wifi_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_wifi_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_wifi_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      bsp_wifi_Private_Variables 
 * @brief         
 * @{  
 */
static const char *TAG = "wifi station";
/**
 * @}
 */
 
/**
 * @defgroup      bsp_wifi_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_wifi_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      bsp_wifi_Functions 
 * @brief         
 * @{  
 */
void BSP_Wifi_Scan(void)
{

}


// ----------------Test Code ------------------


static esp_err_t event_handler(void *ctx, system_event_t *event)
{

    
    switch (event->event_id) {
        case SYSTEM_EVENT_STA_START:
            ESP_LOGE(TAG, "SYSTEM_EVENT_STA_START");

            break;
        case SYSTEM_EVENT_STA_GOT_IP:
            ESP_LOGE(TAG, "SYSTEM_EVENT_STA_GOT_IP");
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            ESP_LOGE(TAG, "SYSTEM_EVENT_STA_DISCONNECTED");
            break;
        default:
            ESP_LOGE(TAG, "SYSTEM_EVENT_STA_Default");
            break;
    }
    
    return ESP_OK;
}



void BSP_Wifi_TestCode(void)
{
    tcpip_adapter_init(); // TCP/IP Init
    //ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .sta= {
            .ssid = "Bigym",
            .password = "1234567890",
        },
    };  

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());  
    ESP_ERROR_CHECK( esp_wifi_connect() );

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:%s password:%s \n",\
             wifi_config.ap.ssid, wifi_config.ap.password);

}

// --------------------------------------------

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

