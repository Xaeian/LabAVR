#ifndef PWM_H_
#define PWM_H_

// This library used TIMER 1
//---------------------------------------------------------------------------------------------------------------------

#define PWM_PRESCALER 8 // { 1, 8, 64, 256, 1024 }

#define PWM_ENABLE_A 1
#define PWM_ENABLE_B 0
#define PWM_NEGATION_A 0
#define PWM_NEGATION_B 0

typedef enum {
  PWM_Mode_PhaseAndFrequencyCorrect = 0,
  PWM_Mode_PhaseCorrect = 1,
  PWM_Mode_Fast = 2
} PWM_Mode_e;

#define PWM_MODE PWM_Mode_Fast

//---------------------------------------------------------------------------------------------------------------------

void PWM_Init(uint32_t autoreload);
__inline void PWM_SetA(uint32_t value);
__inline void PWM_SetB(uint32_t value);

//-------------------------------------------------------------------------------------------------
#endif