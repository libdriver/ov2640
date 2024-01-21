/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "sdio.h"

/* Definitions of physical drive number for each drive */
#define DEV_TF		0	/* Example: Map Ramdisk to physical drive 0 */

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
    DSTATUS stat;

    switch (pdrv) 
   {
        case DEV_TF :
        {
            stat = 0;
            
            break;
        }
        
        default :
        {
            stat = STA_NODISK;
        }
   }
   
   return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
    DSTATUS stat;

    switch (pdrv) 
   {
        case DEV_TF :
        {
            stat = sdio_init();
            
            break;
        }
        
        default :
        {
            stat = STA_NODISK;
        }
   }
   
   return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
    DRESULT stat;
    uint8_t times = 2;
    
    switch (pdrv) 
   {
        case DEV_TF :
        {
            while (times)
            {
                stat = (DRESULT)sdio_read(sector, (uint8_t *)buff, count);
                if (stat)
                {
                   times--;
                }
                else
                {
                    break;
                }
            }
            
            break;
        }
        
        default :
        {
            stat = (DRESULT)STA_NODISK;
        }
   }
   
   return stat;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
    DRESULT stat;
    uint8_t times = 2;
    
    switch (pdrv) 
   {
        case DEV_TF :
        {
            while (times)
            {
                stat = (DRESULT)sdio_write(sector, (uint8_t *)buff, count);
                if (stat)
                {
                    times--;
                }
                else
                {
                    break;
                }
            }
            
            break;
        }
        
        default :
        {
            stat = (DRESULT)STA_NODISK;
        }
   }

   return stat;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
    DRESULT stat;

    switch (pdrv) 
   {
        case DEV_TF :
        {
            switch(cmd)
            {
                case CTRL_SYNC :
                {
                    stat = RES_OK; 
                    
                    break; 
                }
                case GET_SECTOR_SIZE :
                {
                    *(DWORD*)buff = 512; 
                    stat = RES_OK;
                    
                    break; 
                }
                case GET_BLOCK_SIZE :
                {
                    *(WORD*)buff = sdio_get_card_info()->LogBlockSize;
                    stat = RES_OK;
                    
                    break;
                }                    
                case GET_SECTOR_COUNT:
                {
                    *(DWORD*)buff = sdio_get_card_info()->LogBlockNbr;
                    stat = RES_OK;
                    
                    break;
                }
                default:
                {
                    stat = RES_PARERR;
                    
                    break;
                }
            }
            
            break;
        }
        
        default :
        {
            stat = (DRESULT)STA_NODISK;
        }
   }
   
   return stat;
}

//User defined function to give a current time to fatfs module      */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */
DWORD get_fattime (void)
{				 
	return 0;
}			 
