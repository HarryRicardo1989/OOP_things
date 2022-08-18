#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

//#include "Lang_conect/lang_conect.h"
#include "esp_netif.h"

// Wifi application settings
#define WIFI_AP_SSID "ESP32_AP"          // AP name
#define WIFI_AP_PASSWORD "password"      // AP password
#define WIFI_AP_CHANNEL 1                // AP channel
#define WIFI_AP_SSID_HIDDEN 0            // AP visibility
#define WIFI_AP_MAX_CONNECTIONS 5        // AP max clients
#define WIFI_AP_BEACON_INTERVAL 100      // AP beacon: 100ms recommended
#define WIFI_AP_IP "192.168.0.1"         // AP Defautl IP
#define WIFI_AP_GATEWAY "192.168.0.1"    // AP Defautl Gateway
#define WIFI_AP_NETMASK "255.255.255.0"  // AP NetMask
#define WIFI_AP_BANDWIDTH WIFI_BW_HT20   // AP bandwidth 20MHz(40 MHz is the other option)
#define WIFI_STA_POWER_SAVE WIFI_PS_NONE // Power save not used
#define MAX_SSID_LENGTH 32               // IEEE standard maximum
#define MAX_PASSWORD_LENGTH 64           // IEEE standard maximum
#define MAX_CONNECTION_RETRIES 5         // Retry number on disconnect

    // netif object for the Station and Access Point

    extern esp_netif_t *esp_netif_sta;
    extern esp_netif_t *esp_netif_ap;
    typedef enum wifi_app_message
    {
        WIFI_APP_MSG_START_HTTP_SERVER = 0,
        WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER,
        WIFI_APP_MSG_STA_CONNECTED_GOT_IP,
    } wifi_app_message_e;
    /**
     * @brief structure for the message queue
     * @note Expand this based on application requirements e.g. add anothertype and parameter as required
     */
    typedef struct wifi_app_queue_message
    {
        wifi_app_message_e msgID;
    } wifi_app_queue_message_t;

    /**
     * @brief Sends a message to the queue
     *
     * @param msgID  message ID from the wifi_app_message_e enun
     * @return BaseType_t pdTRUE if an item was successfully sent to the queue, otherwise pdFALSE.
     * @note Expand the parameter list based on your requirements e.g. how you've expanded the wifi_app_queue_message_t.
     */
    BaseType_t wifi_app_send_message(wifi_app_message_e msgID);

    /**
     * @brief starts the wifi RTOS task
     */
    void wifi_app_start(void);

// fim do header
#ifdef __cplusplus
}
#endif
