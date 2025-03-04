#include "lowpass_filter.h"
uint16_t Find_Median(uint16_t arr[], int size)
{
	// 对数组进行排序
	int i, j, temp;
	for (i = 0; i < size - 1; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	int mid_index = size / 2;
	return arr[mid_index];
}
float lpf_calc(LowPassFilter_Obj *lpf, float x)
{
	float y = lpf->alpha * lpf->y_prev + (1.0f - lpf->alpha) * x;

	lpf->y_prev = y;
	return y;
}

void lpf_reset(LowPassFilter_Obj *lpf, float x)
{
	lpf->y_prev = x;
}
