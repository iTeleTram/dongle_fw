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
#ifndef DCC_H_INCLUDED
#define DCC_H_INCLUDED

#include "dcc_drv.h"

#define DCC_MAX_SCHEDULED   16
#define DCC_PACKET_GAP      10 //mSec

void dcc_scheduler(void *param);
extern dcc_pkt_t *dccOnDemand;
bool dcc_add_pkt(dcc_pkt_t *pkt);
bool dcc_del_pkt(uint16_t addr);
void dcc_sch_list(void);

#endif // DCC_H_INCLUDED