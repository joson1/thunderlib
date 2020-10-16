/*
 * @Author: your name
 * @Date: 2020-10-09 18:38:32
 * @LastEditTime: 2020-10-09 21:44:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit#
 * @FilePath: \ThunderLib\drivers\sensors\mlx90614\mlx90614.c
 */
#include <thunder/i2c.h>
#include "sensors/mlx90614.h"

struct i2c_dev* mlx;

static uint16_t read16(uint8_t addr)
{
    uint8_t buf[3];
    buf[0] = addr;
    mlx->i2c_wirte(MLX90614_I2CADDR,buf,1);
    mlx->i2c_read(MLX90614_I2CADDR,buf,3);
    return buf[0]|(buf[1]<<8);
}
static void write16(uint8_t addr, uint16_t data)
{
    return;
}



uint32_t mlx90614_init()
{
    mlx = i2c_open(0);
    
}
uint32_t mlx90614_readID(void)
{
    return 0;
}


double mlx90614_readTemp(uint8_t reg)
{
  double temp;
  
  temp = read16(reg);
  temp *= .02;
  temp  -= 273.15;
  return temp;
}

double mlx90614_readObjectTempC(void)
{
  return mlx90614_readTemp(MLX90614_TOBJ1);


}
double mlx90614_readAmbientTempC(void)
{
  return mlx90614_readTemp(MLX90614_TA);
    
}
double mlx90614_readObjectTempF(void)
{
  return (mlx90614_readTemp(MLX90614_TOBJ1) * 9 / 5) + 32;

}
double mlx90614_readAmbientTempF(void)
{
  return (mlx90614_readTemp(MLX90614_TA) * 9 / 5) + 32;

}



