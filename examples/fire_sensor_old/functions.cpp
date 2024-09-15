#include "functions.h"

#define DHTPIN GPIO_NUM_4     // Pino GPIO do ESP32 conectado ao pino de dados do DHT11

// Definir os pinos dos LEDs
#define GREEN_LED GPIO_NUM_17    // GPIO17 (LED verde)
#define YELLOW_LED GPIO_NUM_5    // GPIO5 (LED amarelo)
#define RED_LED GPIO_NUM_18      // GPIO18 (LED vermelho)

static const char *TAG = "DHT11";
bool fire = false;
int temp = 0;

float temperature = 0;
float humidity = 0;

// ################################### Fuções DHT11 ########################################
void DHT11_start_signal() {
    // Configurar o pino como saída
    gpio_set_direction(DHTPIN, GPIO_MODE_OUTPUT);
    gpio_set_level(DHTPIN, 0);  // Pino baixo por 20ms
    vTaskDelay(20 / portTICK_PERIOD_MS);  // Manter baixo por 20ms
    gpio_set_level(DHTPIN, 1);  // Pino alto por 40µs
    esp_rom_delay_us(40);
    gpio_set_direction(DHTPIN, GPIO_MODE_INPUT);  // Mudar para entrada para receber a resposta
}

// Função para verificar a resposta do sensor
bool DHT11_check_response() {
    int response = 0;
    
    // O sensor deve enviar um pulso de 80us baixo e depois 80us alto
    esp_rom_delay_us(40);
    if (gpio_get_level(DHTPIN) == 0) {
        esp_rom_delay_us(80);
        if (gpio_get_level(DHTPIN) == 1) {
            esp_rom_delay_us(80);
            response = 1;
        }
    }

    // Retornar 1 se o sensor respondeu corretamente
    return response;
}

// Função para ler os dados de 40 bits do DHT11
uint8_t DHT11_read_byte() {
    uint8_t result = 0;

    // Ler 8 bits do sensor
    for (int i = 0; i < 8; i++) {
     printf("lendo bit %d",i);
        while (gpio_get_level(DHTPIN) == 0);  // Aguarda o início do bit
        esp_rom_delay_us(40);  // Espera 40µs
        
        // Se o pino ainda estiver alto após 40µs, é um bit 1
        if (gpio_get_level(DHTPIN) == 1) {
            result |= (1 << (7 - i));
        }
        
        while (gpio_get_level(DHTPIN) == 1);  // Aguarda o fim do bit
    }

    return result;
}

// Função para processar os dados do DHT11
void read_DHT11(int *temperature, int *humidity) {
    uint8_t hum_int, hum_dec, temp_int, temp_dec, checksum;

    DHT11_start_signal();  // Inicia a comunicação com o sensor

    // Verifica a resposta do sensor
    if (DHT11_check_response()) {
        // Lê os 5 bytes (umidade inteira, umidade decimal, temperatura inteira, temperatura decimal, checksum)
        hum_int = DHT11_read_byte();
        hum_dec = DHT11_read_byte();
        temp_int = DHT11_read_byte();
        temp_dec = DHT11_read_byte();
        checksum = DHT11_read_byte();

        // Verifica se os dados são válidos usando o checksum
        if (checksum == (hum_int + hum_dec + temp_int + temp_dec)) {
            *humidity = hum_int;
            *temperature = temp_int;
        } else {
            printf("Erro no checksum!\n");
        }
    } else {
        printf("Nenhuma resposta do sensor DHT11!\n");
    }
}

void DHT11_task(void *pvParameters) {
    int temp = 0, hum = 0;

    while (1) {
        read_DHT11(&temp, &hum);

        if (temp != 0 && hum != 0) {
            printf("Temperatura: %d°C, Umidade: %d%%\n", temp, hum);
        } else {
            printf("Falha ao ler do sensor DHT11!\n");
        }

        vTaskDelay(2000 / portTICK_PERIOD_MS);  // Espera de 2 segundos entre as leituras
    }
}

// ################################### Fuções DHT11 ########################################

bool action_trigger_alarm()
{
  printf("# ALERT! DANGEROUS CONDITION!! \n\n");
  return true;
}

bool action_print_init()
{
  printf("Sensor1 iniciado.\n\n");
  xTaskCreate(&DHT11_task, "DHT11_task", 2048, NULL, 5, NULL);
  return true;
}

bool action_print_alert()
{
  //printf("Sensor1 operando em modo alerta.\n\n");
  ESP_LOGI(TAG, "Sensor1 operando em modo alerta.\n\n");
  return true;
}

bool action_print_default()
{
  printf("Sensor1 operando em modo normal.\n\n");
  return true;
}

bool action_print_fire()
{
  printf("# Fogo detectado!.\n\n");
  return true;
}

bool action_print_not_fire()
{
  printf("# Sem Fogo!.\n\n");
  return true;
}

bool update_fire(bool var)
{
  //temp = read_DHT11();
     

  //printf("Temp: %d°C\n", temp);
  return true;
}
