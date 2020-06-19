/**
 **************************************************************************************************
 * @file        system_param.c
 * @author
 * @version
 * @date        
 * @brief
 **************************************************************************************************
 * @attention
 *              
 **************************************************************************************************
 */
#include "self_def.h"
#include "system_param.h"

/**
 * @addtogroup    XXX 
 * @{  
 */
#include "clog.h"

#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"


/**
 * @addtogroup    system_param_Modules 
 * @{  
 */

/**
 * @defgroup      system_param_IO_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Macros_Defines 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Constants_Defines 
 * @brief         
 * @{  
 */

const char storage_name_NetMode[] = "Net_Mode";
const char storage_name_Local_IP[] = "Local_IP";
const char storage_name_Local_port[] = "Local_port";
const char storage_name_Target_IP[] = "Target_IP";
const char storage_name_Target_port[] = "Target_port";
const char storage_name_DHCP_Flag[] = "DHCP_Flag";

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Types
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Private_Variables 
 * @brief         
 * @{  
 */
const SystemParam_Config_t SystemParam_Config_Default = 
{

};
/**
 * @}
 */

/**
 * @defgroup      system_param_Public_Variables 
 * @brief         
 * @{  
 */
SystemParam_Config_t g_SystemParam_Config;
/**
 * @}
 */

/**
 * @defgroup      system_param_Private_FunctionPrototypes 
 * @brief         
 * @{  
 */

/**
 * @}
 */

/**
 * @defgroup      system_param_Functions 
 * @brief         
 * @{  
 */
 
 
 
void SystemParam_Init(void)
{		
    // Initialize NVS
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        // NVS partition was truncated and needs to be erased
        // Retry nvs_flash_init
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK( err );


}

nvs_handle_t my_handle;
int16_t SystemParam_Read(void)
{

const char storage_name_NetMode[] = "Net_Mode";
const char storage_name_Local_IP[] = "Local_IP";
const char storage_name_Local_port[] = "Local_port";
const char storage_name_Target_IP[] = "Target_IP";
const char storage_name_Target_port[] = "Target_port";
const char storage_name_DHCP_Flag[] = "DHCP_Flag";


    esp_err_t err ; 
    // Open
    printf("\n");
    printf("Opening Non-Volatile Storage (NVS) handle... ");
    err = nvs_open("storage", NVS_READONLY, &my_handle);
    if (err != ESP_OK) 
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } 
    else 
    {
        // Read
        printf("Reading System from NVS ... ");
        err = nvs_get_u8(my_handle, storage_name_NetMode, &g_SystemParam_Config.Net_Mode);
        err = nvs_get_u32(my_handle, storage_name_Local_IP, &g_SystemParam_Config.Local_IP);
        err = nvs_get_u16(my_handle, storage_name_Local_port, &g_SystemParam_Config.Local_port);
        err = nvs_get_u32(my_handle, storage_name_Target_IP, &g_SystemParam_Config.Target_IP);        
        err = nvs_get_u16(my_handle, storage_name_Target_port, &g_SystemParam_Config.Target_port);
        err = nvs_get_u8(my_handle, storage_name_DHCP_Flag, &g_SystemParam_Config.DHCP_Flag);
         
        switch (err) {
            case ESP_OK:
                printf("Read System OK\n");
                break;
            case ESP_ERR_NVS_NOT_FOUND:
                printf("Read System Err!NOT_FOUND\n");
                break;
            default :
                printf("Read System Err!!\n");
        }
        // Close
        nvs_close(my_handle);
    }
    return 0;
}

void SystemParam_Save(void)
{
    esp_err_t err ; 
    err = nvs_open("storage", NVS_READWRITE, &my_handle);
    if (err != ESP_OK) 
    {
        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
    } 
    else 
    {
        // Write
        printf("Updating restart counter in NVS ... ");

        err = nvs_set_u8(my_handle, storage_name_NetMode, g_SystemParam_Config.Net_Mode);
        err = nvs_set_u32(my_handle, storage_name_Local_IP, g_SystemParam_Config.Local_IP);
        err = nvs_set_u16(my_handle, storage_name_Local_port, g_SystemParam_Config.Local_port);
        err = nvs_set_u32(my_handle, storage_name_Target_IP, g_SystemParam_Config.Target_IP);        
        err = nvs_set_u16(my_handle, storage_name_Target_port, g_SystemParam_Config.Target_port);
        err = nvs_set_u8(my_handle, storage_name_DHCP_Flag, g_SystemParam_Config.DHCP_Flag);
         




        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

        // Commit written value.
        // After setting any values, nvs_commit() must be called to ensure changes are written
        // to flash storage. Implementations may write to storage at other times,
        // but this is not guaranteed.
        printf("Committing updates in NVS ... ");
        err = nvs_commit(my_handle);
        printf((err != ESP_OK) ? "Failed!\n" : "Done\n");

        // Close
        nvs_close(my_handle);
    }
}

void SystemParam_Reset(void)
{

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

