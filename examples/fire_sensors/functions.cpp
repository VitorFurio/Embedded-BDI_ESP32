#include "functions.h"

#define BUTTON_PIN GPIO_NUM_2     // Pino GPIO do ESP32 conectado ao botão
#define GREEN_LED GPIO_NUM_17     // GPIO17 (LED verde)
#define YELLOW_LED GPIO_NUM_5     // GPIO5 (LED amarelo)
#define RED_LED GPIO_NUM_18       // GPIO18 (LED vermelho)

static const char *TAG = "FIRE_SENSOR";

bool fire = false;

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
    printf("Sensor1 iniciado.\n");
    gpio_set_level(GREEN_LED, 1);
    gpio_set_level(YELLOW_LED, 0);
    gpio_set_level(RED_LED, 0);
    return true;
}

bool action_trigger_alarm()
{
    printf("\n# ALERT! DANGEROUS CONDITION!! \n");
    gpio_set_level(GREEN_LED, 0);
    gpio_set_level(YELLOW_LED, 0);
    gpio_set_level(RED_LED, 1);
    return true;
}

bool action_print_alert()
{
    printf("Sensor1 operando em modo alerta.\n");
    gpio_set_level(GREEN_LED, 0);
    gpio_set_level(YELLOW_LED, 1);
    gpio_set_level(RED_LED, 0);
    return true;
}

bool action_print_default()
{
    printf("Sensor1 operando em modo normal.\n");
    gpio_set_level(GREEN_LED, 1);
    gpio_set_level(YELLOW_LED, 0);
    gpio_set_level(RED_LED, 0);
    return true;
}

bool action_print_fire()
{
    printf("# Fogo detectado!.\n");
    return true;
}

bool action_print_not_fire()
{
    printf("# Sem Fogo!.\n");
    return true;
}

bool update_fire(bool var)
{
    fire = gpio_get_level(BUTTON_PIN);
    return fire;
}

