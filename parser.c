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
 * @file parser.c
 * @author Sergey Sanders
 * @date 2 January 2017
 * @brief uart command parser
 *
 * Implementation of command line parser
 */

#include "FreeRTOS.h"
#include "task.h"
#include "parser.h"
#include "string.h"
#include "stdlib.h"
#include "cdc.h"
#include "em_cmu.h"
#include "dcc.h"

void led_ctrl(char *param);
void cmd_status(char *param);
void cmd_dcc_en(char *param);
void cmd_add(char *param);
void cmd_del(char *param);
void cmd_list(char *param);
void cmd_tx(char *param);
void cmd_rx(char *param);
void cmd_help(char *param);
void cmd_echo(char *param);

cmd_t commands[] =
{
    {.func=led_ctrl,.name="led",.help="0-turn led off,1-turn led on"},
    {.func=cmd_echo,.name="echo",.help="echo on(0)/off(1)"},
    {.func=cmd_status,.name="stat",.help="print system status"},
    {.func=cmd_dcc_en,.name="en",.help="DCC signal enable(1)/disable(0)"},
    {.func=cmd_add,.name="add",.help="add packet to scheduler"},
    {.func=cmd_list,.name="ls",.help="list scheduled packets"},
    {.func=cmd_del,.name="del",.help="delete packet from scheduler"},
    {.func=cmd_tx,.name="tx",.help="transmit packet"},
    {.func=cmd_rx,.name="rx",.help="receive packet from dcc"},
    {.func=cmd_help,.name="?",.help="print help"},
    {.func=NULL,.name="",.help="command list terminator"}
};

bool echo = ECHO_ON ? true:false;
char cLine[CMD_BUFF_LEN];

/**
 * @brief command line edit
 * @return edit done status.
 */
bool cl_edit(void)
{
    static uint8_t clPtr=0;
    char cc;
    if (cdc_getch(&cc))
    {
        switch (cc)
        {
        case '\r':  // return
            cLine[clPtr]='\0';
            clPtr = 0;
            if (echo) cdc_puts("\n\r");
            return true;
        case '\n': // skip new line
            return false;
        case '\b': // backspace
            if (clPtr)
            {
                clPtr--;
                if (echo) cdc_puts("\b \b");
            }
            break;
        default:
            cLine[clPtr]=cc;
            if (clPtr<(CMD_BUFF_LEN-1))
                clPtr++;
            else if (echo) cdc_putc('\b');
            if (echo) cdc_putc(cc);
        }
    }
    return false;
}

/**
 * @brief parsing command line.
 */
void parse(void *param)
{
    uint16_t cmdIndx;
    char *cmd,*clPtr;
    while(1)
        if (cl_edit())
        {
            clPtr = cLine;
            cmd = strtok(clPtr," \n\r");
            cmdIndx=0;
            if (cmd[0])
                while (commands[cmdIndx].func!=NULL)
                {
                    if (!strcmp(cmd,commands[cmdIndx].name))
                    {
                        clPtr = strtok(NULL,"\n\r");
                        commands[cmdIndx].func(clPtr?clPtr:"");
                        break;
                    }
                    else cmdIndx++;
                }
            if (echo) cdc_puts(CLI_PROMPT);
        }
}

void cmd_help(char *param)
{
    uint16_t cmdIndx=0;
    cdc_puts("\r\n -- Help\r\n");
    while (commands[cmdIndx].func!=NULL)
    {
        cdc_puts((char *)commands[cmdIndx].name);
        cdc_puts("\t- ");
        cdc_puts((char *)commands[cmdIndx++].help);
        cdc_puts("\r\n");
    }
}

void led_ctrl(char *param)
{
    if (param[0]!='0')
    {
        led(1);
    }
    else
    {
        led(0);
    }
}

void cmd_dcc_en(char *param)
{
    if (echo) cdc_puts("DCC power: \r\n");
    if (param[0])
        dcc_enable((param[0]=='0')?0:1);
    cdc_puts(dcc_stat() ? "1\r\n":"0\r\n");
}

void cmd_echo(char *param)
{
    if (param[0])
        echo = (param[0]=='0')?0:1;
    cdc_puts(echo ? "0\r\n":"1\r\n");
}

void cmd_status(char *param)
{
    if (!echo) return;
    cdc_puts("\r\ndcc v0.1\r\n");
    cdc_print_num(CMU_ClockFreqGet(cmuClock_TIMER0),10,0);
    cdc_puts("\r\n0x");
    cdc_print_num(TIMER0->STATUS,16,8);
    cdc_puts("\r\n");
}

void cmd_list(char *param)
{
    dcc_sch_list();
}

dcc_pkt_t *param2pkt(char *param)
{
    static dcc_pkt_t pkt;
    char *str = strtok(param," \r\n");
    if (!str) return NULL;
    memset(pkt.data,0x00,DCC_MAX_DATA_BYTES);
    for (pkt.size=0; pkt.size<DCC_MAX_DATA_BYTES; pkt.size++)
    {
        pkt.data[pkt.size] = strtol(str,NULL,16);
        if(!(str = strtok(NULL," \r\n")))
            break;
    }
    if (pkt.size==DCC_MAX_DATA_BYTES) pkt.size--;
    else
        pkt.size++;
    return &pkt;
}
void cmd_add(char *param)
{
    dcc_pkt_t *pkt = param2pkt(param);
    if (!pkt)
    {
        if (echo)
            cdc_puts ("Too few params");
        else
            cdc_puts ("E\r\n");
        return;
    }
    dcc_add_pkt(pkt);
    cdc_puts (dcc_add_pkt(pkt)?"1\r\n":"0\r\n");
}
void cmd_del(char *param)
{
    dcc_pkt_t *pkt = param2pkt(param);
    if (!pkt)
    {
        if (echo)
            cdc_puts ("Too few params");
        else
            cdc_puts ("E\r\n");
        return;
    }
    cdc_puts ((dcc_del_pkt(pkt->data[0]+(pkt->data[1]<<8)))?"1\r\n":"0\r\n");
}
void cmd_tx(char *param)
{
    dcc_pkt_t *pkt = param2pkt(param);
    if (!pkt)
    {
        if (echo)
            cdc_puts ("Too few params");
        else
            cdc_puts ("E\r\n");
        return;
    }
    dccOnDemand = pkt;
    while (dccOnDemand) taskYIELD();
    cdc_puts ("1\r\n");
}
void cmd_rx(char *param)
{

}
