/**************************************************************************//**
 * @file     descriptors.c
 * @version  V1.00
 * @brief    M480 HSUSBD driver source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __DESCRIPTORS_C__
#define __DESCRIPTORS_C__

/*!<Includes */
#include "NuMicro.h"
#include "hid_transfer.h"






/*!<USB HID Report Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t HID_DeviceReportDescriptor[] =
{
#else
uint8_t HID_DeviceReportDescriptor[] __attribute__((aligned(4))) =
{
#endif
   0x06, 0x00, 0xFF,   // Usage Page = 0xFF00 (Vendor Defined Page 1)
    0x09, 0x01,         // Usage (Vendor Usage 1)
    0xA1, 0x01,         // Collection (Application)
    0x19, 0x01,         // Usage Minimum
    0x29, 0x40,         // Usage Maximum //64 input usages total (0x01 to 0x40)
    0x15, 0x00,         // Logical Minimum (data bytes in the report may have minimum value = 0x00)
    0x26, 0xFF, 0x00,   // Logical Maximum (data bytes in the report may have maximum value = 0x00FF = unsigned 255)
    0x75, 0x08,         // Report Size: 8-bit field size
    0x96, 0x00, 0x04,        // Report Count: Make sixty-four 8-bit fields (the next time the parser hits an "Input", "Output", or "Feature" item)
    0x81, 0x00,         // Input (Data, Array, Abs): Instantiates input packet fields based on the above report size, count, logical min/max, and usage.
    0x19, 0x01,         // Usage Minimum
    0x29,	0x00,	0x04,         // Usage Maximum //64 output usages total (0x01 to 0x40)
    0x91, 0x00,         // Output (Data, Array, Abs): Instantiates output packet fields. Uses same report size and count as "Input" fields, since nothing new/different was specified to the parser since the "Input" item.
    0xC0                // End Collection
	
	
};


/*----------------------------------------------------------------------------*/
/*!<USB Device Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8DeviceDescriptor[] =
{
#else
uint8_t gu8DeviceDescriptor[] __attribute__((aligned(4))) =
{
#endif
    LEN_DEVICE,     /* bLength */
    DESC_DEVICE,    /* bDescriptorType */
    0x00, 0x02,     /* bcdUSB */
    0x00,           /* bDeviceClass */
    0x00,           /* bDeviceSubClass */
    0x00,           /* bDeviceProtocol */
    CEP_MAX_PKT_SIZE,   /* bMaxPacketSize0 */
    /* idVendor */
    USBD_VID & 0x00FF,
    ((USBD_VID & 0xFF00) >> 8),
    /* idProduct */
    USBD_PID & 0x00FF,
    ((USBD_PID & 0xFF00) >> 8),
    0x00, 0x00,     /* bcdDevice */
    0x01,           /* iManufacture */
    0x02,           /* iProduct */
    0x00,           /* iSerialNumber - no serial */
    0x01            /* bNumConfigurations */
};

/*!<USB Qualifier Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8QualifierDescriptor[] =
{
#else
uint8_t gu8QualifierDescriptor[] __attribute__((aligned(4))) =
{
#endif
    LEN_QUALIFIER,  /* bLength */
    DESC_QUALIFIER, /* bDescriptorType */
    0x10, 0x01,     /* bcdUSB */
    0x00,           /* bDeviceClass */
    0x00,           /* bDeviceSubClass */
    0x00,           /* bDeviceProtocol */
    CEP_OTHER_MAX_PKT_SIZE, /* bMaxPacketSize0 */
    0x01,           /* bNumConfigurations */
    0x00
};

/*!<USB Configure Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ConfigDescriptor[] =
{
#else
uint8_t gu8ConfigDescriptor[] __attribute__((aligned(4))) =
{
#endif
    LEN_CONFIG,     /* bLength */
    DESC_CONFIG,    /* bDescriptorType */
    /* wTotalLength */
    (LEN_CONFIG+LEN_INTERFACE+LEN_HID+LEN_ENDPOINT*2) & 0x00FF,
    (((LEN_CONFIG+LEN_INTERFACE+LEN_HID+LEN_ENDPOINT*2) & 0xFF00) >> 8),
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    0x80 | (USBD_SELF_POWERED << 6) | (USBD_REMOTE_WAKEUP << 5),/* bmAttributes */
    USBD_MAX_POWER,         /* MaxPower */

    /* I/F descr: HID */
    LEN_INTERFACE,  /* bLength */
    DESC_INTERFACE, /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x02,           /* bNumEndpoints */
    0x03,           /* bInterfaceClass */
    0x00,           /* bInterfaceSubClass */
    0x00,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* HID Descriptor */
    LEN_HID,        /* Size of this descriptor in UINT8s. */
    DESC_HID,       /* HID descriptor type. */
    0x10, 0x01,     /* HID Class Spec. release number. */
    0x00,           /* H/W target country. */
    0x01,           /* Number of HID class descriptors to follow. */
    DESC_HID_RPT,   /* Descriptor type. */
    /* Total length of report descriptor. */
    sizeof(HID_DeviceReportDescriptor) & 0x00FF,
    ((sizeof(HID_DeviceReportDescriptor) & 0xFF00) >> 8),

    /* EP Descriptor: interrupt in. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (INT_IN_EP_NUM | EP_INPUT), /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    EPA_MAX_PKT_SIZE & 0x00FF,
    ((EPA_MAX_PKT_SIZE & 0xFF00) >> 8),
    HID_DEFAULT_INT_IN_INTERVAL,        /* bInterval */

    /* EP Descriptor: interrupt out. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (INT_OUT_EP_NUM | EP_OUTPUT),   /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    EPB_MAX_PKT_SIZE & 0x00FF,
    ((EPB_MAX_PKT_SIZE & 0xFF00) >> 8),
    HID_DEFAULT_INT_IN_INTERVAL     /* bInterval */
};

/*!<USB Other Speed Configure Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8OtherConfigDescriptorHS[] =
{
#else
uint8_t gu8OtherConfigDescriptorHS[] __attribute__((aligned(4))) =
{
#endif
    LEN_CONFIG,     /* bLength */
    DESC_OTHERSPEED,    /* bDescriptorType */
    /* wTotalLength */
    (LEN_CONFIG+LEN_INTERFACE+LEN_HID+LEN_ENDPOINT*2) & 0x00FF,
    (((LEN_CONFIG+LEN_INTERFACE+LEN_HID+LEN_ENDPOINT*2) & 0xFF00) >> 8),
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    0x80 | (USBD_SELF_POWERED << 6) | (USBD_REMOTE_WAKEUP << 5),/* bmAttributes */
    USBD_MAX_POWER,         /* MaxPower */

    /* I/F descr: HID */
    LEN_INTERFACE,  /* bLength */
    DESC_INTERFACE, /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x02,           /* bNumEndpoints */
    0x03,           /* bInterfaceClass */
    0x00,           /* bInterfaceSubClass */
    0x00,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* HID Descriptor */
    LEN_HID,        /* Size of this descriptor in UINT8s. */
    DESC_HID,       /* HID descriptor type. */
    0x10, 0x01,     /* HID Class Spec. release number. */
    0x00,           /* H/W target country. */
    0x01,           /* Number of HID class descriptors to follow. */
    DESC_HID_RPT,   /* Descriptor type. */
    /* Total length of report descriptor. */
    sizeof(HID_DeviceReportDescriptor) & 0x00FF,
    ((sizeof(HID_DeviceReportDescriptor) & 0xFF00) >> 8),

    /* EP Descriptor: interrupt in. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (INT_IN_EP_NUM | EP_INPUT), /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    EPA_OTHER_MAX_PKT_SIZE & 0x00FF,
    ((EPA_OTHER_MAX_PKT_SIZE & 0xFF00) >> 8),
    HID_DEFAULT_INT_IN_INTERVAL,        /* bInterval */

    /* EP Descriptor: interrupt out. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (INT_OUT_EP_NUM | EP_OUTPUT),   /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    EPB_OTHER_MAX_PKT_SIZE & 0x00FF,
    ((EPB_OTHER_MAX_PKT_SIZE & 0xFF00) >> 8),
    HID_DEFAULT_INT_IN_INTERVAL     /* bInterval */
};


#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ConfigDescriptorFS[] =
{
#else
uint8_t gu8ConfigDescriptorFS[] __attribute__((aligned(4))) =
{
#endif
    LEN_CONFIG,     /* bLength */
    DESC_CONFIG,    /* bDescriptorType */
    /* wTotalLength */
    (LEN_CONFIG+LEN_INTERFACE+LEN_HID+LEN_ENDPOINT*2) & 0x00FF,
    (((LEN_CONFIG+LEN_INTERFACE+LEN_HID+LEN_ENDPOINT*2) & 0xFF00) >> 8),
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    0x80 | (USBD_SELF_POWERED << 6) | (USBD_REMOTE_WAKEUP << 5),/* bmAttributes */
    USBD_MAX_POWER,         /* MaxPower */

    /* I/F descr: HID */
    LEN_INTERFACE,  /* bLength */
    DESC_INTERFACE, /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x02,           /* bNumEndpoints */
    0x03,           /* bInterfaceClass */
    0x00,           /* bInterfaceSubClass */
    0x00,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* HID Descriptor */
    LEN_HID,        /* Size of this descriptor in UINT8s. */
    DESC_HID,       /* HID descriptor type. */
    0x10, 0x01,     /* HID Class Spec. release number. */
    0x00,           /* H/W target country. */
    0x01,           /* Number of HID class descriptors to follow. */
    DESC_HID_RPT,   /* Descriptor type. */
    /* Total length of report descriptor. */
    sizeof(HID_DeviceReportDescriptor) & 0x00FF,
    ((sizeof(HID_DeviceReportDescriptor) & 0xFF00) >> 8),

    /* EP Descriptor: interrupt in. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (INT_IN_EP_NUM | EP_INPUT), /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    EPA_OTHER_MAX_PKT_SIZE & 0x00FF,
    ((EPA_OTHER_MAX_PKT_SIZE & 0xFF00) >> 8),
    HID_DEFAULT_INT_IN_INTERVAL,        /* bInterval */

    /* EP Descriptor: interrupt out. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (INT_OUT_EP_NUM | EP_OUTPUT),   /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    EPB_OTHER_MAX_PKT_SIZE & 0x00FF,
    ((EPB_OTHER_MAX_PKT_SIZE & 0xFF00) >> 8),
    HID_DEFAULT_INT_IN_INTERVAL     /* bInterval */
};

/*!<USB Other Speed Configure Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8OtherConfigDescriptorFS[] =
{
#else
uint8_t gu8OtherConfigDescriptorFS[] __attribute__((aligned(4))) =
{
#endif
    LEN_CONFIG,     /* bLength */
    DESC_OTHERSPEED,    /* bDescriptorType */
    /* wTotalLength */
    (LEN_CONFIG+LEN_INTERFACE+LEN_HID+LEN_ENDPOINT*2) & 0x00FF,
    (((LEN_CONFIG+LEN_INTERFACE+LEN_HID+LEN_ENDPOINT*2) & 0xFF00) >> 8),
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    0x80 | (USBD_SELF_POWERED << 6) | (USBD_REMOTE_WAKEUP << 5),/* bmAttributes */
    USBD_MAX_POWER,         /* MaxPower */

    /* I/F descr: HID */
    LEN_INTERFACE,  /* bLength */
    DESC_INTERFACE, /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x02,           /* bNumEndpoints */
    0x03,           /* bInterfaceClass */
    0x00,           /* bInterfaceSubClass */
    0x00,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* HID Descriptor */
    LEN_HID,        /* Size of this descriptor in UINT8s. */
    DESC_HID,       /* HID descriptor type. */
    0x10, 0x01,     /* HID Class Spec. release number. */
    0x00,           /* H/W target country. */
    0x01,           /* Number of HID class descriptors to follow. */
    DESC_HID_RPT,   /* Descriptor type. */
    /* Total length of report descriptor. */
    sizeof(HID_DeviceReportDescriptor) & 0x00FF,
    ((sizeof(HID_DeviceReportDescriptor) & 0xFF00) >> 8),

    /* EP Descriptor: interrupt in. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (INT_IN_EP_NUM | EP_INPUT), /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    EPA_MAX_PKT_SIZE & 0x00FF,
    ((EPA_MAX_PKT_SIZE & 0xFF00) >> 8),
    HID_DEFAULT_INT_IN_INTERVAL,        /* bInterval */

    /* EP Descriptor: interrupt out. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (INT_OUT_EP_NUM | EP_OUTPUT),   /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    EPB_MAX_PKT_SIZE & 0x00FF,
    ((EPB_MAX_PKT_SIZE & 0xFF00) >> 8),
    HID_DEFAULT_INT_IN_INTERVAL     /* bInterval */
};


/*!<USB Language String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8StringLang[4] =
{
#else
uint8_t gu8StringLang[4] __attribute__((aligned(4))) =
{
#endif
    4,              /* bLength */
    DESC_STRING,    /* bDescriptorType */
    0x09, 0x04
};

/*!<USB Vendor String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8VendorStringDesc[] =
{
#else
uint8_t gu8VendorStringDesc[] __attribute__((aligned(4))) =
{
#endif
    16,
    DESC_STRING,
    'N', 0, 'u', 0, 'v', 0, 'o', 0, 't', 0, 'o', 0, 'n', 0
};

/*!<USB Product String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ProductStringDesc[] =
{
#else
uint8_t gu8ProductStringDesc[] __attribute__((aligned(4))) =
{
#endif
    30,             /* bLength          */
    DESC_STRING,    /* bDescriptorType  */
    'M', 0, '4', 0, '8', 0, '0', 0, ' ', 0, 'C', 0, 'M', 0, 'S', 0, 'I', 0, 'S', 0, '-', 0, 'D', 0, 'A', 0, 'P', 0};

uint8_t *gpu8UsbString[4] =
{
    gu8StringLang,
    gu8VendorStringDesc,
    gu8ProductStringDesc,
    NULL,
};

uint8_t *gu8UsbHidReport[3] =
{
    HID_DeviceReportDescriptor,
    NULL,
    NULL,
};

uint32_t gu32UsbHidReportLen[3] =
{
    sizeof(HID_DeviceReportDescriptor),
    0,
    0,
};

S_HSUSBD_INFO_T gsHSInfo =
{
    gu8DeviceDescriptor,
    gu8ConfigDescriptor,
    gpu8UsbString,
    gu8QualifierDescriptor,
    gu8ConfigDescriptorFS,
    gu8OtherConfigDescriptorHS,
    gu8OtherConfigDescriptorFS,
    gu8UsbHidReport,
    gu32UsbHidReportLen,
    gu8UsbHidReport,
    gu32UsbHidReportLen,
};


#endif  /* __DESCRIPTORS_C__ */
