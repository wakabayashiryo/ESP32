#include "freertos/task.h"

typedef enum
{
	NONE = 0,//bypass
	LPF1 = 1,//DifferenceMethod_LPF 
	LPF2 = 2,//BilinerTransform_LPF
}FILTER_e;

typedef struct
{
    uint16_t rawData;
    float    voltage;
    float    Temperature;
    struct
    {
        FILTER_e switch_filter;
        float    fc;
        float    Ts;
    }Filter;
}SensorData;

#define TaskDelay(x)	vTaskDelay(x/portTICK_PERIOD_MS)

void setup(void)
{
    static SensorData sData;

    sData.Filter.switch_filter = NONE;
    sData.Filter.fc = 50;
    sData.Filter.Ts = 0.001;

    Serial.begin(115200);
    // Serial.println("start program!");
    // Serial.printf("setup() runs on core %d\n", xPortGetCoreID());
 
    xTaskCreate(LM35DZ_Read,"read",4096,&sData,1,NULL);
    
    xTaskCreate(Filter_SensorData,"LPF",4096,&sData,2,NULL);

    // xTaskCreate(Display_monitor,"monitor",4096,&sData,2,NULL);
    // xTaskCreate(Display_plotter,"plotter",4096,&sData,2,NULL);
    xTaskCreate(Send_processing,"processing",4096,&sData,2,NULL);

    // xTaskCreate(DAC_SetParameter,"DAC",4096,NULL,2,NULL);
    // xTaskCreate(ADC2DAC,"ADC2DAC",4096,NULL,2,NULL);
}

void loop(void)
{
    while(1)
    {
        TaskDelay(1);
    }
}

void Display_monitor(void *pvParameters)
{
    while(1)
    {
        Serial.println("Temperature is " + String(((SensorData*)pvParameters)->Temperature) + "Degree C");
        TaskDelay(100);
    }
}

void Display_plotter(void *pvParameters)
{
    while(1)
    {
        Serial.println(((SensorData*)pvParameters)->Temperature);
		TaskDelay(1);
	}   
}

void Send_processing(void *pvParameters)
{
    while(1)
    {
        Serial.print(((SensorData*)pvParameters)->rawData);
        TaskDelay(100);
    }
}

void DAC_SetParameter(void *pvParameters)
{
    //pin:      IO25  
    //parameter:127
    while(1)
    {    
        dacWrite(25,127); //8Bits DAC(MAX parameter 255)
		TaskDelay(1);
    }
}

void ADC2DAC(void *pvParameters)
{   
    while(1)
    {
        uint8_t volume = (uint8_t)(analogRead(A5)>>4);    //IO33 ADC1_CH5
        dacWrite(26,volume); //8Bits DAC(MAX parameter 255)

        Serial.println(analogRead(A6));//IO34 ADC1_CH6
        
		TaskDelay(1); 
    }
}
