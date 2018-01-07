// ***** 0. Documentation Section *****



// ***** 1. Pre-processor Directives Section *****



// ***** 2. Global Declarations Section *****
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))

#define GPIO_PORTB_DATA_R       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_R        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_R      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_PUR_R        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_DEN_R        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_AMSEL_R      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_R       (*((volatile unsigned long *)0x4000552C))

#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_PUR_R        (*((volatile unsigned long *)0x40024510))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_LOCK_R       (*((volatile unsigned long *)0x40024520))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))

#define NVIC_ST_CTRL_R      (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R    (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R   (*((volatile unsigned long *)0xE000E018))
	
#define SYSCTL_RCC2_R           (*((volatile unsigned long *)0x400FE070))
#define SYSCTL_RCC_R            (*((volatile unsigned long *)0x400FE060))
#define SYSCTL_RIS_R            (*((volatile unsigned long *)0x400FE050))	
	
unsigned int st = 0;	
	
// FUNCTION PROTOTYPES: Each subroutine defined

void Port_Init(void);// Initializes the port
void Delay1ms(unsigned long msec); // Delay function
void PLL_Init(void); // Initializes PLL to run clock Cycles at 80Mhz
void SysTick_Init(void); // Initializes SYS_TICK Counter
void SysTick_Wait(unsigned long delay); // SYS_tick Wait Function
void SysTick_Wait10ms(unsigned long delay); // Delay function

// ***** 3. Subroutines Section *****

// PE0, PB0, or PA2 connected to positive logic momentary switch using 10k ohm pull down resistor
// PE1, PB1, or PA3 connected to positive logic LED through 470 ohm current limiting resistor
// To avoid damaging your hardware, ensure that your circuits match the schematic

int main(void){ 
//**********************************************************************
// The following version tests input on PE0 and output on PE1
//**********************************************************************
  
  PLL_Init();// Initializes PLL to run Cycles at 80Mhz
	Port_Init();// Initializes Ports for Parellel communication 
  
	
  while(1){
			int Data1,Data2,Data3;
			Data1 = GPIO_PORTE_DATA_R&0x01 ; 
			Data2 = GPIO_PORTB_DATA_R&0x01 ;
			Data3 = GPIO_PORTB_DATA_R&0x10 ;
			
			if ( Data1 == 0x01 && st == 0 ) // Switch1 is Pressed
			{ // North bridge 
					GPIO_PORTE_DATA_R = 0x04;// switches on yellow light
					GPIO_PORTB_DATA_R = 0x04;// switches on yellow light
					SysTick_Wait10ms(100); // Waits for 1 sec
					GPIO_PORTE_DATA_R = 0x02;// Switch on the red LED
					GPIO_PORTB_DATA_R = 0x08;// Switch on the green LED
					st = 1;
			}
			
			
			else if ( Data2 == 0x01 && st == 1 ) // Switch2 is pressed
			{
					// West bridge
					GPIO_PORTE_DATA_R = 0x04;// switches on yellow light
					GPIO_PORTB_DATA_R = 0x04;// switches on yellow light
					SysTick_Wait10ms(100); // Waits for 1 sec
					GPIO_PORTE_DATA_R = 0x08;// Switch on the green LED
					GPIO_PORTB_DATA_R = 0x02;// Switch on the red LED
					st = 0;
					
			}
			
			else if ( Data3 == 0x10  )
			{
						// Pedestrian Switch 
						SysTick_Wait10ms(500); // Wait for 5 sec
						GPIO_PORTE_DATA_R = 0x04 ; // Switches to yellow
						GPIO_PORTB_DATA_R = 0x04 ; // Switches to yellow
						SysTick_Wait10ms(100) ; // Waits for 1 sec
						GPIO_PORTE_DATA_R = 0x02 ; // Switches to red
						GPIO_PORTB_DATA_R = 0x02 ; // Switches to red
						SysTick_Wait10ms(500) ; // Waits for 5 sec
				
			}
  }
  
}

void Port_Init(void)
{
	
		unsigned long int Delay;
		SYSCTL_RCGC2_R = SYSCTL_RCGC2_R | 0x12 ; // Enables Clock for PortE & PortB
		Delay = SYSCTL_RCGC2_R ; // Time for Clock to get stabilised
	
		
		GPIO_PORTE_AMSEL_R = 0x00; // Disables Analog Funtion
		GPIO_PORTE_AFSEL_R = 0x00; // No Alternate function selected
		GPIO_PORTE_PCTL_R  = 0x00000000; // Clears pin PCTL
		GPIO_PORTE_PUR_R   = 0x00 ; // No Pull up resistor to be activated
		GPIO_PORTE_DEN_R   = 0x0F; // Enables Digital Functionality  for PE0 ,PE1 ,PE2 ,PE3 
	  GPIO_PORTE_DIR_R   = 0x0E; // Enables PE1,PE2,PE3 as O/P & PE0 as I/P :- Sw1
	
		GPIO_PORTB_AMSEL_R = 0x00; // Disables Analog Funtion
		GPIO_PORTB_AFSEL_R = 0x00; // No Alternate function selected
		GPIO_PORTB_PCTL_R  = 0x00000000; // Clears pin PCTL
		GPIO_PORTB_PUR_R   = 0x00 ; // No Pull up resistor to be activated
		GPIO_PORTB_DEN_R   = 0x1F; // Enables Digital Functionality  for PE0 ,PE1 ,PE2 ,PE3 ,PE4 
	  GPIO_PORTB_DIR_R   = 0x0E; // Enables PE1,PE2,PE3 as O/P & PE0 ,PE4 as I/P :- Sw2
		
}

void PLL_Init(void){
  // 0) Use RCC2
  SYSCTL_RCC2_R |=  0x80000000;  // USERCC2
  // 1) bypass PLL while initializing
  SYSCTL_RCC2_R |=  0x00000800;  // BYPASS2, PLL bypass
  // 2) select the crystal value and oscillator source
  SYSCTL_RCC_R = (SYSCTL_RCC_R &~0x000007C0)   // clear XTAL field, bits 10-6
                 + 0x00000540;   // 10101, configure for 16 MHz crystal
  SYSCTL_RCC2_R &= ~0x00000070;  // configure for main oscillator source
  // 3) activate PLL by clearing PWRDN
  SYSCTL_RCC2_R &= ~0x00002000;
  // 4) set the desired system divider
  SYSCTL_RCC2_R |= 0x40000000;   // use 400 MHz PLL
  SYSCTL_RCC2_R = (SYSCTL_RCC2_R&~ 0x1FC00000)  // clear system clock divider
                  + (4<<22);      // configure for 80 MHz clock ( writes on SYSDIV2 feild )
  // 5) wait for the PLL to lock by polling PLLLRIS
  while((SYSCTL_RIS_R&0x00000040)==0){};  // wait for PLLRIS bit
  // 6) enable use of PLL by clearing BYPASS
  SYSCTL_RCC2_R &= ~0x00000800;
}

void SysTick_Init(void){
  NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
  NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock
}

// The delay parameter is in units of the 80 MHz c ore clock. (12.5 ns)

void SysTick_Wait(unsigned long delay){
  NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
  NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
  while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
  }
}

// 800000*12.5ns equals 10ms

void SysTick_Wait10ms(unsigned long delay){
  unsigned long i;
  for(i=0; i<delay; i++){
    SysTick_Wait(800000);  // wait 10ms
  }
}
