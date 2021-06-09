#ifndef INTERRUPT_NAMES_H
#define INTERRUPT_NAMES_H

#define INT0_vect _VECTOR(2)
#define INT1_vect _VECTOR(3)
#define INT2_vect _VECTOR(4)
#define TIMER2_COMP_vect _VECTOR(5)
#define TIMER2_OVF_vect _VECTOR(6)
#define TIMER1_CAPT_vect _VECTOR(7)
#define TIMER1_COMPA_vect _VECTOR(8)
#define TIMER1_COMPB_vect _VECTOR(9)
#define TIMER1_OVF_vect _VECTOR(10)
#define TIMER0_COMP_vect _VECTOR(11)
#define TIMER0_OVF_vect _VECTOR(12)
#define SPI_STC_vect _VECTOR(13)
#define USART_RXC_vect _VECTOR(14)
#define USART_UDRE_vect _VECTOR(15)
#define USART_TXC_vect _VECTOR(16)
#define ADC_vect _VECTOR(17)
#define EE_RDY_vect _VECTOR(18)
#define ANA_COMP_vect _VECTOR(19)
#define TWI_vect _VECTOR(20)
#define SPM_RDY_vect _VECTOR(21)

#endif /* INTERRUPT_NAMES_H */