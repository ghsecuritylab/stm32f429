/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2014-04-27     Bernard      make code cleanup. 
 */

#include <board.h>
#include <rtthread.h>

#ifdef RT_USING_LWIP
#include <lwip/sys.h>
#include <lwip/api.h>
#include <netif/ethernetif.h>
#include "stm32_eth.h"
#endif

#ifdef RT_USING_GDB
#include <gdb_stub.h>
#endif


extern    void audio_init(void);

extern void video_io_init(void);

extern 	void SDRAM_Init(void);
extern void gps_init(void);

extern  void LCD_Config(void);

extern void LCD_Init(void);

extern void LCD_LayerInit(void);

extern void lcd_open(void);


/**
  * @}
  */ 

/**
  * @brief  Initialize DMA2D module in MCU for lcd control.
  * @param  None
  * @retval None
  */
static void LCD_dma2d_init(void)
{
    /* Enable the DMA2D Clock. */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, ENABLE); 
}

void Back_light(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI,ENABLE);

    //GPIO_PinAFConfig(GPIOI, GPIO_PinSource5, GPIO_AF_LTDC);
    GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
                                   
    GPIO_Init(GPIOI, &GPIO_InitStructure);


    GPIO_SetBits(GPIOI,GPIO_Pin_5);

}

void rt_init_thread_entry(void* parameter)
{
    /* GDB STUB */
#ifdef RT_USING_GDB
    gdb_set_device("uart6");
    gdb_start();
#endif

    /* LwIP Initialization */
#ifdef RT_USING_LWIP
    {
        extern void lwip_sys_init(void);

        /* register ethernetif device */
        eth_system_device_init();

        rt_hw_stm32_eth_init();

        /* init lwip system */
        lwip_sys_init();
        rt_kprintf("TCP/IP initialized!\n");
    }
#endif
rt_kprintf("\n\n");
rt_kprintf("CLK : %dMHz\n", SystemCoreClock/1000000);	
#if 0		
rt_kprintf(".....8888888888888888888888888o.\n");
rt_kprintf("...............888::::888888888888888888888888o.\n");
rt_kprintf(".............88::::::::88888888888888888888888888o.\n");
rt_kprintf("...........o8:::::::::888::��88888888888888888888888.\n");
rt_kprintf("..........8888:8::::::8:::::::::��88888888888888888888.\n");
rt_kprintf(".........8888::::8888::::::::::::::::��88888888888?? '88\n");
rt_kprintf("........8888:::888888888::::::::::::::::��888888888????8\n");
rt_kprintf(".......88.88888888888888888:::::::::::::��88888888888\n");
rt_kprintf("......88..888888888888888888:::::::::::��88888888888888\n");
rt_kprintf("......88.888888888888888888888::::::::��88888888888888888\n");
rt_kprintf("......8..8888888888888888888888::::::��88888888888888888888\n");
rt_kprintf("........8888888888888888::88888:::::��8888888888888888888888\n");
rt_kprintf("......88888888888888888::::8888::::��8888888888888888?? '8888\n");
rt_kprintf(".....88888888888888888::::8888::::��:8::***::888888888????888\n");
rt_kprintf("....88888888888888888::::888:::::��::::*EYE*::888888888????88\n");
rt_kprintf("..888888888888888888::::88::::::��:::::::::::::888888888 88\n");
rt_kprintf(".8888888888888888888::::8::::::��:::::::::::::��888888888 88\n");
rt_kprintf("888...8888888888::88::::8:::::��:::8oo8::::::88888888888888 8\n");
rt_kprintf("88...88888888888:::8:::::::::��:::::::::::::88888888888888888\n");
rt_kprintf(".8..8888888888888:::::::::::��::\"8888888\":::��88888888888888888\n");
rt_kprintf("..8888888888::888::::::::::��:::::\"8a8\"::::��88888888888888888888\n");
rt_kprintf(".888888888:::::88:::::::::��88::::::::::::��88888888888888888888888\n");
rt_kprintf("8888888888:::::8:::::::::��88888::::::::��888888888888888888888888888\n");
rt_kprintf("888888888:::::8:::::::::��8888888ooooo��8888888888888888888888888888888\n");
rt_kprintf("888888.��::::::::::::::��8888888888::::::��8888888888888888?? '888888888\n");
rt_kprintf("8888..��:::::::::::::::��88888888888::::::��8888888888888888???? 88888888\n");
rt_kprintf(".888..��::::::::::::::��8888888888888:::::::��888888888888888??????888888\n");
rt_kprintf("..888.��:::::::::::::��88888888888888888::::::��8888888888888??????88888\n");
rt_kprintf("...88.��:::::::::::::8888:88888888888888888:::::����888888888???? 8888\n");
rt_kprintf("...88.��:::::::::::8888��::88888::888888888888:::::����88888???? 888\n");
rt_kprintf("...8...��::::::::::8888��:::8888:::::88888888888::::::����88???? 888\n");
rt_kprintf(".......8��:::::::8888��:::::888:::::::88:::8888888:::::::����?? 88 \n");
rt_kprintf("......88��:::::::8888��::::::88:::::::::8:::::888888::::::::���� 88\n");
rt_kprintf(".....8888��:::::888��:::::::::88::::::::::��::::8888::::::::::::�� 8\n");
rt_kprintf("....88888:��::::888��::::::::::8:::::::::::��::::888::::::::::::::��\n");
rt_kprintf("...88.888:��:::888:��::::::::::8::::::::::::��::888::::::::::::::::��\n");
rt_kprintf("...8.88888��:::88::��::::::::::::::::::::::::��:88::::::::::::::::::��\n");
rt_kprintf(".....88888��:::88::��:::::::::::::::::::::::::��88:::::::::::::::::::��\n");
rt_kprintf(".....88888��:::88::��:::::::::::::::::::::::::��:8::::::::::::::::::::��\n");
rt_kprintf("....888888��::::8::��::::::::::::::8888::::::::��8::::::::::::8888:::::��\n");
rt_kprintf("....88888..��:::8::����:::::::::::88@@88:::::::��::::::::::::88@@88::::��\n");
rt_kprintf("....8888...����:::::����::::::::::888888:::::::����::::::::::888888::::��\n");
rt_kprintf("....8888....��:::::::����::::::::::8888:::::::������::::::::::8888::::��'\n");
rt_kprintf(".....888....����::::::������:::::::::::::::::����::��::::::::::::::::��'\n");
rt_kprintf("......88.....��::::::::��������:::::::::::������:::����:::::::::::::��'\n");
rt_kprintf(".......88....����:::::::::��������������������:::::::����������������'\n");
rt_kprintf("........88....����::::::::::::��������������::::::::::::����������o'\n");
rt_kprintf(".........88...8����::::::::::::::::::::::::::::::::::::::::��\n");
rt_kprintf("..........8...88����::::::::::::::::::::::��:::��::::::::::��\n");
rt_kprintf("..............888����::::::::::::::::::����::::::����::::::��\n");
rt_kprintf(".............88888����:::::::::::::::������:::::::����:::::��\n");
rt_kprintf(".............888888����:::::::::::::������:::::::::����:::��\n");
rt_kprintf("............88888888����:::::::::::������:::::::::::��:::��\n");
rt_kprintf("...........88.8888888.��::::::::������::::::::::::::��::��\n");
rt_kprintf("...........8..888888..��::::::����:::::::::::::::::��::��\n");
rt_kprintf("..............888888..��:::::��:::::::::::::::::::��::����\n");
rt_kprintf(".............888888...��::::��::::::::::::::::::::::::����\n");
rt_kprintf(".............888888...��::::��::::::::::::::::::::::::��:��\n");
rt_kprintf(".............88888...��::::::::::::::8::::::::::::::::��::��\n");
rt_kprintf("............88888...��:::::::::::::::88::::::::::::::::��::��\n");
rt_kprintf("...........88888...��::::::::::::::::8::::::::::::::::::��::��\n");
rt_kprintf("..........88888...��:::::��:::::::::::::::::::::��::::::::��::��\n");
rt_kprintf("..........8888...��:::::��:::::::::::::::::::::::����::::::��::��\n");
rt_kprintf(".........8888...��:::::��:::::::::::::::::::::::������:::::::��:��\n");
rt_kprintf("........888....��:::::����::::::::::::::::::::::������::::::::��:��\n");
rt_kprintf("......8888....��::::::����:::::::::::::::::::::������::::::::: ��:��\n");
rt_kprintf(".....888......��:::::��:::::::::::::::::::::::����::::::::::::::��:��\n");
rt_kprintf("..8888.......��::::::::::::::::::::::::::::::��::::::::::::::::::��:��\n");
rt_kprintf(".............��::::::::::::::::::::::::::::::::::::::::::::::::::��:��\n");
rt_kprintf("............��::::::::��:::::::::::::::::::::::::::::::::::::::::��:��\n");
rt_kprintf("............��::::::::��:::::::::::::::::��::::::::::::::::::::::��:��\n");
rt_kprintf("...........��::::::::::��::::::::::::::��::::::::::::::::::::::::��:��\n");
rt_kprintf("...........��:::::::::::��8::::::::8:��:::::::::::::::::::::::::��:��p\n");
rt_kprintf("...........��::::::::::::8ole888888��:::::::::::::::::::::::::::��:��o\n");
rt_kprintf("...........��:::::::::::::88888888��:::::::::::::::::::::::::::��:��p\n");
rt_kprintf("...........��::::::::::::::888888��::::::::::::::::::::::::::::��:��\n");
rt_kprintf("...........��:::::::::::::::88**8��:::::::::::::::::::::::::::��:��\n");
rt_kprintf("...........��:::::::::::::::::88��::::::::::::::::::::::::::::����\n");
rt_kprintf("...........��:::::::::::::::::::��:::::::::::::::::::::::::::����\n");
rt_kprintf("...........��:::::::::::::::::::��::::::::::::::::::::::::::����\n");
rt_kprintf("............��:::::::::::::::::��::::::::::::::::::::::::::����\n");
rt_kprintf("............��:::::::::::::::::��::::::::::::::::::::::::::��\n");
rt_kprintf(".............��:::::::::::::::��::::::::::::::::::::::::::��\n");
rt_kprintf(".............��:::::::::::::::��:::::::::::::::::::::::::��\n");
rt_kprintf("..............��:::::::::::::��:::::::::::::::::::::::::��\n");
rt_kprintf("..............��:::::::::::::��:::::::::::::::::::::::��\n");
rt_kprintf("...............��:::::::::::��:::::::::::::::::::::::��\n");
rt_kprintf("...............��:::::::::::��::::::::::::::::::::::��\n");
rt_kprintf("................��:::::::::��::::::::::::::::::::::��\n");
rt_kprintf("................��:::::::::��:::::::::::::::::::::��\n");
rt_kprintf(".................��:::::::��:::::::::::::::::::::��\n");
rt_kprintf("..................��::::::��::::::::::::::::::::��\n");
rt_kprintf("..................��:::::��::::::::::::::::::::��\n");
rt_kprintf("...................��:::��::::::::::::::::::::��\n");
rt_kprintf("...................��::��::::::::::::::::::::��\n");
rt_kprintf("....................��:��:::::::::::::::::::��\n");
rt_kprintf("....................����:::::::::::::::::::��\n");
rt_kprintf("....................����::::::::::::::::::��\n");
rt_kprintf("....................����:::::::::::::::::��\n");
rt_kprintf("....................����:::::��::::::::����\n");
rt_kprintf("....................����::::����:::::::����\n");
rt_kprintf("....................����::::::����:::::����\n");
rt_kprintf(".....................����::::::::::::::����\n");
rt_kprintf(".....................����::::��:::::::::����\n");
rt_kprintf("......................����::������:::::::����\n");
rt_kprintf("......................����::������:::::::����\n");
rt_kprintf("......................����:::����::::::::::��\n");
rt_kprintf(".......................����::����::::::::::��\n");
rt_kprintf(".......................����::����:::::::::::��\n");
rt_kprintf(".......................����:::��::::::::::::��\n");
rt_kprintf(".......................����:::::::::::::::::��\n");
rt_kprintf(".......................����:::::::::::::::::��\n");
rt_kprintf(".......................����::::::::::::::::::��\n");
rt_kprintf(".......................����::::::::::::::::::��\n");
rt_kprintf(".......................����::::::::::::::::::��\n");
rt_kprintf("........................����:::::::::::::::::��\n");
rt_kprintf("........................����:::::::::::::::::��\n");
rt_kprintf("........................����:::::::::::::::::��\n");
rt_kprintf("........................����:::::::::::::::::��\n");
rt_kprintf("........................����:::::::::::::::::��\n");
rt_kprintf(".........................����:::::::::::::::��\n");
rt_kprintf(".........................����:::::::::::::::��\n");
rt_kprintf(".........................����:::::::::::::::��\n");
rt_kprintf(".........................����::::::::::::::��\n");
rt_kprintf("..........................����:::::::::::::��\n");
rt_kprintf("..........................����:::::::::::::��\n");
rt_kprintf("..........................����:::::::::::::��\n");
rt_kprintf("..........................����::::::::::::��\n");
rt_kprintf("..........................����::::::::::::��\n");
rt_kprintf("...........................����:::::::::::��\n");
rt_kprintf("...........................����::::::::::��\n");
rt_kprintf("...........................����::::::::::��\n");
rt_kprintf("............................����::::::::��\n");
rt_kprintf("............................����::::::::�� \n");
rt_kprintf("............................����:::::::��\n");
rt_kprintf("...............................��:::::��\n");
rt_kprintf("................................��::::��\n");
rt_kprintf(".................................��::::��\n");
rt_kprintf(".................................��:::::��\n");
rt_kprintf(".................................��::::::��\n");
rt_kprintf(".................................��::::::��\n");
rt_kprintf("...............................��:��,:::::��\n");
rt_kprintf("..............................��::��::::::��\n");
rt_kprintf(".............................��'::��:::::::��\n");
rt_kprintf(".............................��::::��:::::::��\n");
rt_kprintf(".............................��:::::��::::::��\n");
rt_kprintf(".............................��:::::��:::::::��\n");
rt_kprintf("..............................��::::��::::::::��\n");
rt_kprintf("..............................��::::��:::::::::��\n");
rt_kprintf("..............................��::::��::::::::::��\n");
rt_kprintf("...............................��::::��:::::::��\n");
rt_kprintf("................................��:::��:::::��\n");
rt_kprintf("..................................��.��,:::��\n");
rt_kprintf("...................................����,::��\n");
rt_kprintf(".....................................��::��\n");
rt_kprintf(".....................................��::��\n");
rt_kprintf("......................................����\n");
rt_kprintf(".......................................��\n");
#endif
//audio_init();
//gps_init();
video_io_init();
SDRAM_Init();
//LCD_Init();
/* Initialize the DMA2D Module. */
//LCD_dma2d_init();

//LCD_LayerInit();
Back_light();

//LCD_Config();

    lcd_open();
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
        rt_init_thread_entry, RT_NULL,
        2048, RT_THREAD_PRIORITY_MAX/3, 20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

/*@}*/
