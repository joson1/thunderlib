/*
 * @Author: your name
 * @Date: 2020-10-09 18:39:07
 * @LastEditTime: 2020-10-09 21:32:55
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \ThunderLib\include\sensors\mlx90614.h
 */
#include <stdint.h>



#define MLX90614_I2CADDR 0x00

// RAM
#define MLX90614_RAWIR1 0x04
#define MLX90614_RAWIR2 0x05
#define MLX90614_TA 0x06
#define MLX90614_TOBJ1 0x07
#define MLX90614_TOBJ2 0x08
// EEPROM
#define MLX90614_TOMAX 0x20
#define MLX90614_TOMIN 0x21
#define MLX90614_PWMCTRL 0x22
#define MLX90614_TARANGE 0x23
#define MLX90614_EMISS 0x24
#define MLX90614_CONFIG 0x25
#define MLX90614_ADDR 0x0E
#define MLX90614_ID1 0x3C
#define MLX90614_ID2 0x3D
#define MLX90614_ID3 0x3E
#define MLX90614_ID4 0x3F




uint32_t mlx90614_init(void);
uint32_t mlx90614_readID(void);

double mlx90614_readObjectTempC(void);
double mlx90614_readAmbientTempC(void);
double mlx90614_readObjectTempF(void);
double mlx90614_readAmbientTempF(void);

double mlx90614_readTemp(uint8_t reg);
