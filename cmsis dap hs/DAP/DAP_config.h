#ifndef __DAP_CONFIG_H__
#define __DAP_CONFIG_H__


#define DEBUG(...)


#define CPU_CLOCK               192000000       ///< Specifies the CPU Clock in Hz


#define IO_PORT_WRITE_CYCLES    2               ///< I/O Cycles: 2=default, 1=Cortex-M0+ fast I/0


#define DAP_SWD                 1               ///< SWD Mode:  1 = available, 0 = not available

#define DAP_JTAG                0               ///< JTAG Mode: 0 = not available

#define DAP_JTAG_DEV_CNT        8               ///< Maximum number of JTAG devices on scan chain

#define DAP_DEFAULT_PORT        1               ///< Default JTAG/SWJ Port Mode: 1 = SWD, 2 = JTAG.

#define DAP_DEFAULT_SWJ_CLOCK   400000         ///< Default SWD/JTAG clock frequency in Hz.


/// Maximum Package Size for Command and Response data.
#define DAP_PACKET_SIZE         1024              ///< USB: 64 = Full-Speed, 1024 = High-Speed.

/// Maximum Package Buffers for Command and Response data.
#define DAP_PACKET_COUNT        1              ///< Buffers: 64 = Full-Speed, 4 = High-Speed
//															4��Cannot Load Flash Programming Algorithm

/// Indicate that UART Serial Wire Output (SWO) trace is available.
#define SWO_UART                0               ///< SWO UART:  1 = available, 0 = not available

#define SWO_UART_MAX_BAUDRATE   0          ///< SWO UART Maximum Baudrate in Hz

/// Indicate that Manchester Serial Wire Output (SWO) trace is available.
#define SWO_MANCHESTER          0               ///< SWO Manchester:  1 = available, 0 = not available

#define SWO_BUFFER_SIZE         0            ///< SWO Trace Buffer Size in bytes (must be 2^n)


/// Debug Unit is connected to fixed Target Device.
#define TARGET_DEVICE_FIXED     0               ///< Target Device: 1 = known, 0 = unknown;



//**************************************************************************************************
/**
JTAG I/O Pin                 | SWD I/O Pin          | CMSIS-DAP Hardware pin mode
---------------------------- | -------------------- | ---------------------------------------------
TCK: Test Clock              | SWCLK: Clock         | Output Push/Pull
TMS: Test Mode Select        | SWDIO: Data I/O      | Output Push/Pull; Input (for receiving data)
TDI: Test Data Input         |                      | Output Push/Pull
TDO: Test Data Output        |                      | Input
nTRST: Test Reset (optional) |                      | Output Open Drain with pull-up resistor
nRESET: Device Reset         | nRESET: Device Reset | Output Open Drain with pull-up resistor

DAP Hardware I/O Pin Access Functions
*/
#include "NuMicro.h"


// Configure DAP I/O pins ------------------------------

#define SWD_GPIO   	PA
#define RST_GPIO   	PF
#define SWD_SWCLK   PA10
#define SWD_SWDIO   PA9
#define SWD_RST   	PF5
#define PIN_SWCLK  	10
#define PIN_SWDIO  	9
#define PIN_RST		 	5
#define MSK_SWCLK   (1 << PIN_SWCLK)
#define MSK_SWDIO   (1 << PIN_SWDIO)
#define MSK_RST     (1 << PIN_RST)

/** Setup JTAG I/O pins: TCK, TMS, TDI, TDO, nTRST, and nRESET.
 - TCK, TMS, TDI, nTRST, nRESET to output mode and set to high level.
 - TDO to input mode.
*/
static void PORT_JTAG_SETUP(void)
{
#if (DAP_JTAG != 0)
#endif
}

/** Setup SWD I/O pins: SWCLK, SWDIO, and nRESET.
 - SWCLK, SWDIO, nRESET to output mode and set to default high level.
*/
static void PORT_SWD_SETUP(void)
{
  GPIO_SetMode(SWD_GPIO, MSK_SWCLK, GPIO_MODE_OUTPUT);
	GPIO_SetMode(SWD_GPIO, MSK_SWDIO, GPIO_MODE_OUTPUT);
	GPIO_SetMode(RST_GPIO, MSK_RST, GPIO_MODE_OUTPUT);
	GPIO_SetSlewCtl(SWD_GPIO, MSK_SWCLK, GPIO_SLEWCTL_FAST);
	GPIO_SetSlewCtl(SWD_GPIO, MSK_SWDIO, GPIO_SLEWCTL_FAST);
}

/** Disable JTAG/SWD I/O Pins.
 - TCK/SWCLK, TMS/SWDIO, TDI, TDO, nTRST, nRESET to High-Z mode.
*/
static void PORT_OFF(void)
{
	GPIO_SetMode(SWD_GPIO, MSK_SWCLK, GPIO_MODE_INPUT);
	GPIO_SetMode(SWD_GPIO, MSK_SWDIO, GPIO_MODE_INPUT);
	GPIO_SetMode(RST_GPIO, MSK_RST, GPIO_MODE_INPUT);
}


// SWCLK/TCK I/O pin -------------------------------------

// Current status of the SWCLK/TCK DAP hardware I/O pin
static __inline uint32_t PIN_SWCLK_TCK_IN(void)
{
    return (SWD_GPIO->MODE & (3 << (PIN_SWCLK << 1))) ? 1 : 0;
}

static __inline void PIN_SWCLK_TCK_SET(void)
{
	SWD_SWCLK = 1;
}

static __inline void PIN_SWCLK_TCK_CLR(void)
{
    SWD_SWCLK = 0;
}


// SWDIO/TMS Pin I/O --------------------------------------

// Current status of the SWDIO/TMS DAP hardware I/O pin
static __inline uint32_t PIN_SWDIO_TMS_IN(void)
{
    return (SWD_GPIO->MODE & (3 << (PIN_SWDIO << 1))) ? 1 : 0;
}

static __inline void PIN_SWDIO_TMS_SET(void)
{
    SWD_SWDIO = 1;
}

static __inline void PIN_SWDIO_TMS_CLR(void)
{
    SWD_SWDIO = 0;
}


static __inline uint32_t PIN_SWDIO_IN(void)
{
    return SWD_SWDIO;
}

static __inline void PIN_SWDIO_OUT(uint32_t bit)
{
    SWD_SWDIO = bit;
}

static __inline void PIN_SWDIO_OUT_ENABLE(void)
{
	GPIO_SetMode(SWD_GPIO, MSK_SWDIO, GPIO_MODE_OUTPUT);
	SWD_SWDIO = 0;
}

static __inline void PIN_SWDIO_OUT_DISABLE(void)
{
    GPIO_SetMode(SWD_GPIO, MSK_SWDIO, GPIO_MODE_INPUT);
}


// TDI Pin I/O ---------------------------------------------

static __inline uint32_t PIN_TDI_IN(void)
{
#if (DAP_JTAG != 0)
#endif
	return 0;
}

static __inline void PIN_TDI_OUT(uint32_t bit)
{
#if (DAP_JTAG != 0)
#endif
}


// TDO Pin I/O ---------------------------------------------

static __inline uint32_t PIN_TDO_IN(void)
{
#if (DAP_JTAG != 0)
#endif
	return 0;
}


// nTRST Pin I/O -------------------------------------------

static __inline uint32_t PIN_nTRST_IN(void)
{
    return 0;
}

static __inline void PIN_nTRST_OUT(uint32_t bit)
{
}

// nRESET Pin I/O------------------------------------------
static __inline uint32_t PIN_nRESET_IN(void)
{
    return 0;
}

static __inline void PIN_nRESET_OUT(uint32_t bit)
{
	SWD_RST=bit;
}


//**************************************************************************************************
/** Connect LED: is active when the DAP hardware is connected to a debugger
    Running LED: is active when program execution in target started
*/

static __inline void LED_CONNECTED_OUT(uint32_t bit)
{
}

static __inline void LED_RUNNING_OUT(uint32_t bit)
{
	PF4=!bit;
}



static void DAP_SETUP(void)
{	
	PORT_OFF();
}


static uint32_t RESET_TARGET(void)
{
    return (0);              // change to '1' when a device reset sequence is implemented
}


#endif // __DAP_CONFIG_H__
