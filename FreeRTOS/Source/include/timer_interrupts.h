__irq void Timer0IRQHandler();
__irq void Timer1IRQHandler();
void Timer0Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void));
void Timer1Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void));