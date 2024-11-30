#include "functions.h"
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "esp_sntp.h"  // Biblioteca para sincronização NTP

#define BUTTON_PIN GPIO_NUM_2     // Pino GPIO do ESP32 conectado ao botão
#define GREEN_LED GPIO_NUM_17     // GPIO17 (LED verde)
#define YELLOW_LED GPIO_NUM_5     // GPIO5 (LED amarelo)
#define RED_LED GPIO_NUM_18       // GPIO18 (LED vermelho)

static const char *TAG = "FIRE_SENSOR";

char name[10] = "Sensor2";
bool fire = false;
bool print_alert = true;
bool print_alarm = true;


// Função para inicializar o NTP e sincronizar o horário
void initialize_sntp()
{
    printf("Inicializando sincronização NTP...\n");

    // Configurar o fuso horário do Brasil (UTC-3)
    setenv("TZ", "UTC+3", 1);
    tzset();

    // Configurar o servidor NTP
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org"); // Servidor NTP padrão
    sntp_init();

    // Esperar até que o tempo esteja sincronizado
    time_t now = 0;
    struct tm timeinfo = {0};
    while (timeinfo.tm_year < (2016 - 1900)) {
        printf("Aguardando sincronização NTP...\n");
        time(&now);
        localtime_r(&now, &timeinfo);
        vTaskDelay(2000 / portTICK_PERIOD_MS); // Aguarda 2 segundos
    }
    printf("Sincronização NTP concluída!\n");
}

// Função para exibir o horário atual no Brasil
void print_current_time()
{
    time_t now;
    struct tm timeinfo;
    time(&now);
    localtime_r(&now, &timeinfo);
    printf(" - %02d:%02d:%02d\n",
           timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
}

void setup()
{
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON_PIN);
    gpio_set_direction(GREEN_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(YELLOW_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(RED_LED, GPIO_MODE_OUTPUT);
}

bool action_print_init()
{
    printf("%s iniciado",name);
    print_current_time();
    gpio_set_level(GREEN_LED, 1);
    gpio_set_level(YELLOW_LED, 0);
    gpio_set_level(RED_LED, 0);
    initialize_sntp();
    return true;
}

bool action_trigger_alarm()
{   
    if(print_alarm){
      printf("\n# ALERT! DANGEROUS CONDITION!!");
      print_current_time();
      print_alarm = false;
    }
    gpio_set_level(GREEN_LED, 0);
    gpio_set_level(YELLOW_LED, 0);
    gpio_set_level(RED_LED, 1);
    return true;
}

bool action_print_alert()
{
    if(print_alert){
      printf("%s operando em modo alerta",name);
      print_current_time();
      print_alert = false;
      print_alarm = true;
    }
    gpio_set_level(GREEN_LED, 0);
    gpio_set_level(YELLOW_LED, 1);
    gpio_set_level(RED_LED, 0);
    return true;
}

bool action_print_default()
{
    if(!print_alert){
      printf("%s operando em modo normal",name);
      print_current_time();
      print_alert = true;
      print_alarm = true;
    }
    gpio_set_level(GREEN_LED, 1);
    gpio_set_level(YELLOW_LED, 0);
    gpio_set_level(RED_LED, 0);
    return true;
}

bool action_print_fire()
{
    printf("# Fogo detectado!");
    print_current_time(); 
    return true;
}

bool action_print_not_fire()
{
    printf("# Sem Fogo!");
    print_current_time(); 
    return true;
}

bool update_fire(bool var)
{
    fire = gpio_get_level(BUTTON_PIN);
    if(fire == var)
    	return var;
    else
    	return !var;
}

