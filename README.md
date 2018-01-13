# Traffic-light-controller

___
## Introduction & Overview

Designing Traffic light controller using <b>TM4C123 Tiva C Series LAUNCHPAD</b> an<b> ARM Cortex M4 based MCU</b>
from Scratch in C using Industrial Tool <b> ARM Keil </b>. ARM Cortex M4 Processor is used in modern Embedded Devices like
fitness bands & other Automative applications. <b>ARM Cortex M series</b> processors are of great importance to modern day Embedded industry. 

___

## Hardware Components used

1. TM4C123 Tiva C Series Launchpad.
2. Resistors.
3. Red , Yellow , Green LEDs
4. Switches

___

## Software tool Used

I used ARM Keil IDE to write code , compile & Burn the code.
One may use other Embedded Designing Tools like <b>IAR Embedded Benchmark</b> or <b>TI Code Compose Studio</b>

### Links for downloading the Tools

1. [ARM Keil](http://www2.keil.com/mdk5/)
2. [IAR Embedded Benchmark](https://www.iar.com/iar-embedded-workbench/)
3. [TI Code Compose Studio](http://www.ti.com/tool/CCSTUDIO)

___

## Working   

Circuit consists of North Bridge & South Bridge , 3 Switches.
When Sw1 is pressed first of all yellow light switches on for 1 sec and then North Bridge goes green & West Bridge goes red.
When Sw2 is pressed first of all yellow light switches on for 1 sec & then West Bridge goes green & North Bridge goes red.
Sw3 Acts as Pedestrian Switch.

One must use <b>Finite State Machine (FSM)</b> which make your program less reduntant to exceptional cases and provides good insight of 
flow of control of the code.

___

## Deployment of Machine

First of all Make a new project and add <b>Startup.s </b>file to your project or the startupfile provided by your tool for yours praticular processor Model. Now add <b>main.c</b> file , main.c file consists of main C code of your Machine now <b>compile and debug</b> your
code using your Embedded Designing Tool. After Succesful Debugging Burn the code onto your Machine and your Prototype is ready to use

