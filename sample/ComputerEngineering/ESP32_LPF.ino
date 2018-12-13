#include "math.h"

#define omegaTs (omega_c*sData->Filter.Ts)

void DifferenceMethod_LPF(SensorData* sData)
{
	static uint16_t yk_1 = 0;
	uint16_t uk = sData->rawData;
	
	float omega_c = 2 * 3.14159265359f * sData->Filter.fc;

	sData->rawData 		= (1/(1+omegaTs))*yk_1 + (omegaTs/(1+omegaTs))*uk;   
	sData->voltage 		= Data2Voltage( sData->rawData );
	sData->Temperature 	= Voltage2Temperature( sData->voltage );

	yk_1 = sData->rawData;
}

void BilinerTransform_LPF(SensorData *sData)
{
	static uint16_t xk_1 = 0;
	uint16_t xk = sData->rawData;
	static uint16_t yk_1 = 0;

	xk_1 = sData->rawData;

	float omega_c = 2 * 3.14159265359f * sData->Filter.fc;
	float omega_a = tan(omegaTs/2);
	
	sData->rawData 		= ((1-omega_a)/(1+omega_a))*yk_1 + (omega_a/(1+omega_a))*(xk+xk_1);
	sData->voltage 		= Data2Voltage( sData->rawData );
	sData->Temperature 	= Voltage2Temperature( sData->voltage );

	yk_1 = sData->rawData;
}

void Filter_SensorData(void *pvParameters)
{
    while(1)
    {
		switch(((SensorData*)pvParameters)->Filter.switch_filter)
		{
			case 1:
				DifferenceMethod_LPF((SensorData*)pvParameters);
			break;

			case 2:
				BilinerTransform_LPF((SensorData*)pvParameters);
			break;

			default:
			break;
		}
        TaskDelay(1);
    }
}