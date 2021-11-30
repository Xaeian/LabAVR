#ifndef ADC_H_
#define ADC_H_

//---------------------------------------------------------------------------------------------------------------------

typedef enum {
  ADC_VReference_External = 0,
  ADC_VReference_Internal = 1,
  ADC_VReference_Integrated = 3
} ADC_VReference_e;

#define ADC_VREF ADC_VReference_Internal
#define ADC_FREERUN 0

//---------------------------------------------------------------------------------------------------------------------

void ADC_Init();
void ADC_Mux(char channel);
uint16_t ADC_Run(char channel);
float ADC_RunFilter(char channel, char filter);

//---------------------------------------------------------------------------------------------------------------------
#endif

// ISR ( ADC_vect )