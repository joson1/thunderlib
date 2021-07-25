#ifndef __SSD1306_H_
#define __SSD1306_H_

// #include "iic.h"
#define u8 char
#define SSD1306_SLAVEADDRESS 0x78

#define SSD1306_DISPLAY_MODE_NORMAL 0xa6
#define SSD1306_DISPLAY_MODE_INVERSE 0xa7

#define SSD1306_MEMORYADDRESSINGMODE_HORIZONTIAL 0x00
#define SSD1306_MEMORYADDRESSINGMODE_VERTICAL    0x01
#define SSD1306_MEMORYADDRESSINGMODE_PAGE        0x02  //REST VALUE

#define SSD1306_setLowerColumnStartAddressForPageAddressingMode(startAddress)   SSD1306_writeConnand(startAddress)
#define SSD1306_setHigherColumnStartAddressForPageAddressingMode(startAddress)  SSD1306_writeConnand(0x10+startAddress)             
#define SSD1306_setMemoryAddressingMode(x)                              SSD1306_writeConnand(0x20+x)
#define SSD1306_setColumAddress(start,end)                              SSD1306_writeConnand(start);SSD1306_writeConnand(end)
                               //0-127d
#define SSD1306_setPgaeAddress(start,end);                              SSD1306_writeConnand(start);SSD1306_writeConnand(end)
                               //0=7d
#define SSD1306_setPgaeStartAddressForPageAddressingMode(x)             SSD1306_writeConnand(0xb0+x)
                                                        //0-7d
#define SSD1306_setDisplayStartLine();
#define SSD1306_setSegmentReMap();
#define SSD1306_setMultiplexRatio();
#define SSD1306_setCOMoutputScanDirection();
#define SSD1306_setDisplayOffset();
#define SSD1306_setCOMpinsHardwareConfiguration();

#define SSD1306_setDisplayON() SSD1306_writeConnand(0xaf)
#define SSD1306_setDisplayDFF() SSD1306_writeConnand(0xae)
#define SSD1306_setDisplay(displayMode) SSD1306_writeConnand(displayMode)
#define SSD1306_entireDisplayON() SSD1306_writeConnand(0xa5)

void SSD1306_writeData(unsigned char _data);
void SSD1306_writeConnand(unsigned char _cmd);
void SSD1306_init(void);
#endif
