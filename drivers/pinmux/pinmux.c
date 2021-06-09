#include <thunder/pinmux.h>
#include <stdint.h>




int pinmux_table_set(uint32_t size,uint32_t* ptable)
{
    for (uint32_t i = 0; i < size/sizeof(uint32_t); i=i+nBrOfPar)
    {
        pin_mux_set( ptable[i],&ptable[i]);

    }
    return 0;
}




