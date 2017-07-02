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
     
****************************************************************************/
#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "bsp.h"

#define ECHO_ON 1 // echo status on start
#define CLI_PROMPT "->"
#define CMD_BUFF_LEN    32

typedef struct 
{
    const char *name;//[16];
    const char *help;//[32];
    void (*func)(char *param);
} cmd_t;

void parse(void *param);

#endif //PARSER_H_INCLUDED