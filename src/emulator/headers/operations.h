//
// Created by crist on 5/28/2020.
//

#ifndef ARM11_10_OPERATIONS_H
#define ARM11_10_OPERATIONS_H

#include "../../structures.h"

Reg do_and(Reg rn, uint32_t operand2);

Reg do_eor(Reg rn, uint32_t operand2);

Reg do_sub(Reg rn, uint32_t operand2);

Reg do_rsb(Reg rn, uint32_t operand2);

Reg do_add(Reg rn, uint32_t operand2);

uint32_t do_tst(Reg rn, uint32_t operand2);

uint32_t do_teq(Reg rn, uint32_t operand2);

uint32_t do_cmp(Reg rn, uint32_t operand2);

Reg do_orr(Reg rn, uint32_t operand2);

#endif //ARM11_10_OPERATIONS_H
