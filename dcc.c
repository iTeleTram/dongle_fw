/****************************************************************************
    This file is part of TeleTram DCC project.

    TeleTram DCC is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TeleTram DCC is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TeleTram DCC.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @file dcc.c
 * @author Sergey Sanders
 * @date 22 January 2016
 * @brief DCC scheduler
 *
 * DCC Scheduler implementation using freeRTOS
 * @see http://www.nmra.org/sites/default/files/s-92-2004-07.pdf Datasheet
 * @see http://www.nmra.org/sites/default/files/s-9.2.1_2012_07.pdf
 */

#include "FreeRTOS.h"
#include "task.h"
#include "bsp.h"
#include "dcc_drv.h"
#include "rx_drv.h"
#include "cdc.h"
#include "dcc.h"



static dcc_pkt_t dccIdle= {.data={0xff,0x00},.size=2};
dcc_pkt_t dccScheduled[DCC_MAX_SCHEDULED];
dcc_pkt_t *dccOnDemand=NULL;

static dcc_pkt_t *dcc_next(void)
{
    static uint8_t ptr=0;
    for(uint8_t cnt=0; cnt<DCC_MAX_SCHEDULED; cnt++)
    {
        if (++ptr==DCC_MAX_SCHEDULED) ptr=0;
        if (dccScheduled[ptr].size) return &dccScheduled[ptr];
    }
    return &dccIdle; // no valid data found
}

bool dcc_add_pkt(dcc_pkt_t *pkt)
{
    if (!pkt->data[0]) return false; // can't add packet with address 0
    uint8_t i,addrSize = (pkt->data[0] > 0x40) ? 1:0;
    for (i=0; i<DCC_MAX_SCHEDULED; i++) // look for already scheduled packet with the same address
    {
        if (!dccScheduled[i].size) continue;
        if (pkt->data[0]==dccScheduled[i].data[0])
        {
            if(addrSize && (pkt->data[1]!=dccScheduled[i].data[1])) continue;// check for long address
            memcpy(&dccScheduled[i],pkt,sizeof(dcc_pkt_t));
            return true;
        }
    }
    // add new record
    for (i=0; i<DCC_MAX_SCHEDULED; i++)
    {
        if (!dccScheduled[i].size)
        {
            memcpy(&dccScheduled[i],pkt,sizeof(dcc_pkt_t));
            return true;
        }
    }
    // no room for new packet
    return false;
}

bool dcc_del_pkt(uint16_t addr)
{
    uint8_t addrSize = (addr > 0xff) ? 1:0;
    uint8_t i;
    if (!addr) // delete all scheduled packets
        for (i=0; i<DCC_MAX_SCHEDULED; i++)
        {
            dccScheduled[i].size = 0;
            return true;
        }
    for (i=0; i<DCC_MAX_SCHEDULED; i++) // look for already scheduled packet with the same address
    {
        if (!dccScheduled[i].size) continue;
        if ((uint8_t)addr==dccScheduled[i].data[0])
        {
            if(addrSize && ((addr>>8)!=dccScheduled[i].data[1])) continue;// check for long address
            dccScheduled[i].size = 0;
            return true;
        }
    }
    // no packet found with such address
    return false;
}

void dcc_sch_list(void)
{
    for (uint8_t i=0; i<DCC_MAX_SCHEDULED; i++)
    {
        if (!dccScheduled[i].size) continue;
        for (uint8_t j=0; (j<dccScheduled[i].size); j++)
        {
            cdc_print_num(dccScheduled[i].data[j],16,2);
            if(j<dccScheduled[i].size-1) cdc_putc(' ');
        }
        cdc_puts("\r\n");
    }
     cdc_puts("-\r\n");
    return;
}

void dcc_scheduler(void *param)
{
    uint8_t i;
    for (i=0; i<DCC_MAX_SCHEDULED; i++)
        dccScheduled[i].size = 0; // reset data
    dcc_init();
    rx_init();
    dcc_enable(1);
    while (1)
    {
        if (dccOnDemand)
        {
            dcc_send(dccOnDemand);
            dccOnDemand=NULL;
        }
        else
            dcc_send(dcc_next());
        while (!dcc_ready()) taskYIELD();
        // vTaskDelay(1);
        rx_enable(true);
        vTaskDelay(DCC_PACKET_GAP);
        rx_enable(false);
    }
}
