
float Data2Voltage(uint32_t Data)
{
	return Data * (3600.f / 4096.f);
}

float Voltage2Temperature( float voltage)
{
	return (voltage - 400.f) / 19.5f;
}

void LM35DZ_Read(void *pvParameters)
{
    while(1)
    {
        /*ADC of ESP32 have 12bit resolutoons */   
        ((SensorData*)pvParameters)->rawData 		= analogRead(A16);   //IO14 ADC2_CH6
        ((SensorData*)pvParameters)->voltage 		= Data2Voltage( ((SensorData*)pvParameters)->rawData );
        ((SensorData*)pvParameters)->Temperature 	= Voltage2Temperature( ((SensorData*)pvParameters)->voltage );
		
        TaskDelay(1);
    }   
}
