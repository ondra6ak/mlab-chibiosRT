#define MAX_SPD 1280
#define MOTOR_R_FWD 1
#define MOTOR_R_REV 0
#define MOTOR_L_FWD 3
#define MOTOR_L_REV 2
#define FWD 0
#define REV 1
#define LEFT 2
#define RIGHT 3

static PWMConfig pwmCfg = 
{
  20000,/*timer na pwm 20kHz*/
  10,/*perioda 2 tiky*/
  NULL,
  /*4 kanaly*/
  {
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
  },
  0
};


#define dip1 palReadPad(GPIOC, 13)
#define dip2 palReadPad(GPIOC, 14)


#define ADC_NUM_CHANNELS   2
#define ADC_BUF_DEPTH      4

static adcsample_t irSamples [ADC_NUM_CHANNELS * ADC_BUF_DEPTH];

static const ADCConversionGroup adcGrpCfg =
{
   TRUE,
   ADC_NUM_CHANNELS,
   NULL,
   NULL,
   ADC_CR2_TSVREFE,
   ADC_SMPR1_SMP_AN12(ADC_SAMPLE_41P5) | ADC_SMPR1_SMP_SENSOR(ADC_SAMPLE_239P5),
   0,
   ADC_SQR1_NUM_CH(ADC_NUM_CHANNELS),
   0,
   ADC_SQR3_SQ2_N(ADC_CHANNEL_IN2) | ADC_SQR3_SQ1_N(ADC_CHANNEL_SENSOR)
};
