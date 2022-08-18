// app includes
#include "wifi_app.h"
#include "http_server.h"
#include "tasks_common.h"
// FreeRTOS includes
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "Lang_conect/lang_conect.h"

// IDF includes
#include "esp_err.h"
#include "esp_log.h"
#include "esp_wifi.h"
#include "lwip/netdb.h"

// Tag used for ESP serial console messages
static const char TAG[] = "wifi_app";

// Queue handle used to manipulate the main queue of events
static QueueSetHandle_t wifi_app_queue_handle;

// netif objects for the station and access point
esp_netif_t *esp_netif_sta = NULL;
esp_netif_t *esp_netif_ap = NULL;

/**
 * @brief Wifi application event handler
 *
 * @param arg aside from event data, that is passed to the handler when it is called
 * @param event_base the base id of the event to register the handler for
 * @param event_id the id to the event to register the handler for
 * @param event_data event data
 */
static void
wifi_app_event_handler(void *arg, esp_event_base_t event_base, int32_t event_id, void *event_data)
{
    if (event_base == WIFI_EVENT)
    {
        switch (event_id)
        {
        case WIFI_EVENT_AP_START:
            ESP_LOGI(TAG, "WIFI_EVENT_AP_START");
            break;
        case WIFI_EVENT_AP_STOP:
            ESP_LOGI(TAG, "WIFI_EVENT_AP_STOP");
            break;
        case WIFI_EVENT_AP_STACONNECTED:
            ESP_LOGI(TAG, "WIFI_EVENT_AP_STACONNECTED");
            break;
        case WIFI_EVENT_AP_STADISCONNECTED:
            ESP_LOGI(TAG, "WIFI_EVENT_AP_STADISCONNECTED");
            break;
        case WIFI_EVENT_STA_START:
            ESP_LOGI(TAG, "WIFI_EVENT_STA_START");
            break;
        case WIFI_EVENT_STA_CONNECTED:
            ESP_LOGI(TAG, "WIFI_EVENT_STA_CONNECTED");
            break;
        case WIFI_EVENT_STA_DISCONNECTED:
            ESP_LOGI(TAG, "WIFI_EVENT_STA_DISCONNECTED");
            break;
        }
    }
    else if (event_base == IP_EVENT)
    {
        switch (event_id)
        {
        case IP_EVENT_STA_GOT_IP:
            ESP_LOGI(TAG, "IP_EVENT_STA_GOT_IP");
            break;
        }
    }
}

/**
 * @brief Initializes the WIFI application event handler for wifi and ip events
 *
 */
static void
wifi_app_event_handler_init(void)
{
    // Event loop for the wifi driver
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    // Event handler for the connection
    esp_event_handler_instance_t instance_wifi_event;
    esp_event_handler_instance_t instance_ip_event;
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_app_event_handler, NULL, &instance_wifi_event));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, ESP_EVENT_ANY_ID, &wifi_app_event_handler, NULL, &instance_ip_event));
}

/**
 * @brief Initializes the TCP stack and default wifi configuration.
 */

static void wifi_app_default_wifi_init(void)
{
    // inicialize the TCP stack
    ESP_ERROR_CHECK(esp_netif_init());

    // default wifi config operations must be in this order
    wifi_init_config_t wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_init_config));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
    esp_netif_sta = esp_netif_create_default_wifi_sta();
    esp_netif_ap = esp_netif_create_default_wifi_ap();
}

/**
 * @brief configure the wifi access point settings and assigns the static IP to the SoftAP.
 */

static void wifi_app_soft_ap_config()
{
    // SoftAP -wifi access point configuration
    wifi_config_t ap_config = {
        .ap = {
            .ssid = WIFI_AP_SSID,
            .ssid_len = strlen(WIFI_AP_SSID),
            .password = WIFI_AP_PASSWORD,
            .channel = WIFI_AP_CHANNEL,
            .ssid_hidden = WIFI_AP_SSID_HIDDEN,
            .authmode = WIFI_AUTH_WPA2_PSK,
            .max_connection = WIFI_AP_MAX_CONNECTIONS,
            .beacon_interval = WIFI_AP_BEACON_INTERVAL,
        },
    };
    esp_netif_ip_info_t ap_ip_info;
    memset(&ap_ip_info, 0x00, sizeof(ap_ip_info));

    esp_netif_dhcps_stop(esp_netif_ap);                                     // must call this first
    inet_pton(AF_INET, WIFI_AP_IP, &ap_ip_info.ip);                         // Assign access point's STATIC IP, GW and netmask
    inet_pton(AF_INET, WIFI_AP_GATEWAY, &ap_ip_info.gw);                    //
    inet_pton(AF_INET, WIFI_AP_NETMASK, &ap_ip_info.netmask);               //
    ESP_ERROR_CHECK(esp_netif_set_ip_info(esp_netif_ap, &ap_ip_info));      // static configure the network interface
    ESP_ERROR_CHECK(esp_netif_dhcps_start(esp_netif_ap));                   // start the AP dhcp server (for connecting stations e.g. your mobile device)
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));                    // setting the mode as access point /station mode
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &ap_config));       // set our config
    ESP_ERROR_CHECK(esp_wifi_set_bandwidth(WIFI_IF_AP, WIFI_AP_BANDWIDTH)); // our default bandwidth 20MHz
    ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_STA_POWER_SAVE));                  // power save set to "NONE"
}

/**
 * @brief Main task for the wifi application
 *
 * @param pvParameters parameter which can be passed to the task
 */
static void
wifi_app_task(void *pvParameters)
{
    wifi_app_queue_message_t msg;

    // initialize the event handler
    wifi_app_event_handler_init();

    // initializer the TCP/IP stack and Wifi config

    wifi_app_default_wifi_init();

    // SoftAP config
    wifi_app_soft_ap_config();

    // start Wifi
    ESP_ERROR_CHECK(esp_wifi_start());

    // send first event message
    wifi_app_send_message(WIFI_APP_MSG_START_HTTP_SERVER);

    while (true)
    {
        if (xQueueReceive(wifi_app_queue_handle, &msg, portMAX_DELAY))
        {
            switch (msg.msgID)
            {
            case WIFI_APP_MSG_START_HTTP_SERVER:
                ESP_LOGI(TAG, "WIFI_APP_MSG_START_HTTP_SERVER");
                http_server_start();
                // rgb_led_http_server_started();
                set_rgb_led_interface(0, 10, 10);

                break;
            case WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER:
                ESP_LOGI(TAG, "WIFI_APP_MSG_CONNECTING_FROM_HTTP_SERVER");
                break;

            case WIFI_APP_MSG_STA_CONNECTED_GOT_IP:
                ESP_LOGI(TAG, "WIFI_APP_MSG_STA_CONNECTED_GOT_IP");
                // rgb_led_wifi_connected();
                set_rgb_led_interface(0, 0, 10);
                break;

            default:
                break;
            }
        }
    }
}

BaseType_t wifi_app_send_message(wifi_app_message_e msgID)
{
    wifi_app_queue_message_t msg;
    msg.msgID = msgID;
    return xQueueSend(wifi_app_queue_handle, &msg, portMAX_DELAY);
}
void wifi_app_start(void)
{
    ESP_LOGI(TAG, "STARTING WIFI APPLICATION");

    // Start wifi started LED
    // rgb_led_wifi_app_started();

    // Disable default WIFI logging messages
    esp_log_level_set("wifi", ESP_LOG_NONE);

    // Create message queue
    wifi_app_queue_handle = xQueueCreate(3, sizeof(wifi_app_queue_message_t));

    xTaskCreatePinnedToCore(&wifi_app_task, "wifi_app_task", WIFI_APP_TASK_STACK_SIZE, NULL, WIFI_APP_TASK_PRIORITY, NULL, WIFI_APP_TASK_CORE_ID);
}
void wifi_app_stop(void)
{
}
