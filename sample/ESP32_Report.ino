#include "freertos/task.h"
#include "driver/adc.h"

typedef struct
{
    uint16_t rawData;
    float    voltage;
    float    Temperature;
}SensorData;

static SensorData sData;
static uint8_t DAC_param; 

void setup(void)
{
    Serial.begin(115200);
    // Serial.println("start program!");
    // Serial.printf("setup() runs on core %d\n", xPortGetCoreID());
 
    xTaskCreate(LM35DZ_Read,"read",4096,&sData,1,NULL);
    // xTaskCreate(Display_temperature,"Report1_1",4096,&sData,2,NULL);
    // xTaskCreate(Plot_temperature,"Report1_2",4096,&sData,2,NULL);
    // xTaskCreate(DAC_SetParameter,"Report1_3",4096,NULL,2,NULL);
    // xTaskCreate(ADC2DAC,"Report1_4",4096,NULL,2,NULL);
    xTaskCreate(sendProcessing,"Report2",4096,&sData,2,NULL);
}

void loop(void)
{
    while(1);
    {
        delay(1);
    }
}

void Display_temperature(void *pvParameters)
{
    while(1)
    {
        Serial.println("Temperature is " + String(((SensorData*)pvParameters)->Temperature) + "Degree C");
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

void Plot_temperature(void *pvParameters)
{
    while(1)
    {
        Serial.println(((SensorData*)pvParameters)->Temperature);
        vTaskDelay(1/portTICK_PERIOD_MS);
    }   
}

void DAC_SetParameter(void *pvParameters)
{
    /*DAC pin : 25 or 26*/
    static uint8_t pinout = 25;
    
    DAC_param = 127;

    while(1)
    {    
        dacWrite(pinout,DAC_param); //8Bits DAC(MAX parameter 255)
        vTaskDelay(1/portTICK_PERIOD_MS);
    }
}

void ADC2DAC(void *pvParameters)
{   
    while(1)
    {
        uint8_t volume = (uint8_t)(analogRead(A5)>>4);    //IO33	ADC1_CH5
        dacWrite(26,volume); //8Bits DAC(MAX parameter 255)

        Serial.println(analogRead(A6));//IO34 	ADC1_CH6
        
        vTaskDelay(1/portTICK_PERIOD_MS);        
    }
}

void LM35DZ_Read(void *pvParameters)
{
    while(1)
    {
        /*ADC of ESP32 have 12bit resolutoons */   
        ((SensorData*)pvParameters)->rawData = analogRead(A16);   //IO14 ADC2_CH6
        ((SensorData*)pvParameters)->voltage = ((SensorData*)pvParameters)->rawData * (3600.f / 4096.f);
        ((SensorData*)pvParameters)->Temperature = (((SensorData*)pvParameters)->voltage - 400.f) / 19.5f;

        vTaskDelay(1/portTICK_PERIOD_MS);
    }   
}

void sendProcessing(void *pvParameters)
{
    while(1)
    {
        Serial.print(((SensorData*)pvParameters)->rawData);
        vTaskDelay(100/portTICK_PERIOD_MS);
    }
}