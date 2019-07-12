#include "NuMicro.h"

#include "hid_transfer.h"
#include "DAP.h"

int main()
{
	delay_init();
	DAP_Setup();
  delay_ms(100);
	HID_Init();
	while(1)
	{	
		usbd_hid_process();
	}
}






