/**
 **************************************************************************************************
 * @file        app_net.c
 * @author
 * @version   v0.1.0
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *
 **************************************************************************************************
 */
#include "app_net.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "string.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "system_param.h"
#include "net_task.h"
#include "clog.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include <lwip/netdb.h>

/**
 * @addtogroup    app_net_Modules 
 * @{  
 */

/**
 * @defgroup      app_net_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_net_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_net_Constants_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_net_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */
 
/**
 * @defgroup      app_net_Private_Variables 
 * @brief         
 * @{  
 */
static const char *TAG = "wifi station";
/**
 * @}
 */
 
/**
 * @defgroup      app_net_Public_Variables 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      app_net_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */
static esp_err_t event_handler(void *ctx, system_event_t *event);
/**
 * @}
 */

/**
 * @defgroup      app_net_Functions 
 * @brief         
 * @{  
 */

typedef struct 
{
    uint8_t Cur_Mode;

}APP_Net_Param_t;

typedef enum
{
    Net_Mode_UDP,
}APP_Net_Mode_e;

APP_Net_Param_t APP_Net_Param = 
{
    .Cur_Mode = Net_Mode_UDP,
};

void APP_Net_Init(void)
{
    APP_Net_Param.Cur_Mode = g_SystemParam_Config.Net_Mode;
    Net_Task_Event_Start(NET_TASK_STA_EVENT,EVENT_FROM_TASK);
}

void APP_NET_STA(void)
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


static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    DEBUG("event->event_id:%d\n" , event->event_id);
    
    switch (event->event_id) {
        case SYSTEM_EVENT_STA_START:
            ESP_LOGE(TAG, "SYSTEM_EVENT_STA_START");

            break;
        case SYSTEM_EVENT_STA_GOT_IP:

            Net_Task_Event_Start(NET_TASK_UDP_EVENT,EVENT_FROM_TASK);
            ESP_LOGE(TAG, "SYSTEM_EVENT_STA_GOT_IP");
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            ESP_LOGE(TAG, "SYSTEM_EVENT_STA_DISCONNECTED");
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            ESP_LOGE(TAG, "SYSTEM_EVENT_STA_CONNECTED");
            break;    
        default:
            ESP_LOGE(TAG, "SYSTEM_EVENT_STA_Default");
            break;
    }
    return ESP_OK;
}

void APP_Net_UDPProcess(void)
{
    /*
    SOCK_DGRAM - > UDP
    SOCK_STREAM - > TCP
    */
    char rx_buffer[128];
    char addr_str[128];
    int addr_family;
    int ip_protocol;
    struct sockaddr_in dest_addr;
    dest_addr.sin_addr.s_addr = inet_addr("192.168.2.100");
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(20000);
    addr_family = AF_INET;
    ip_protocol = IPPROTO_IP;
    inet_ntoa_r(dest_addr.sin_addr, addr_str, sizeof(addr_str) - 1);

    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);

    uint8_t payload[1024] = {0x12,0x45,0xff,0xac,0xbb,0xdc,0x10,0x00,0x88};
    int err = sendto(sock, payload, 1024, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));

/*
    int len = recvfrom(sock, rx_buffer, sizeof(rx_buffer) - 1, 0, (struct sockaddr *)&source_addr, &socklen);

    if (sock != -1) 
    {
        ESP_LOGE(TAG, "Shutting down socket and restarting...");
        shutdown(sock, 0);
        close(sock);
    }
*/
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

