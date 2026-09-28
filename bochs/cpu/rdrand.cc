/////////////////////////////////////////////////////////////////////////
// $Id$
/////////////////////////////////////////////////////////////////////////
//
//  Copyright (C) 2012-2019  The Bochs Project
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA B 02110-1301 USA
//
/////////////////////////////////////////////////////////////////////////

#define NEED_CPU_REG_SHORTCUTS 1
#include "bochs.h"
#include "cpu.h"
#define LOG_THIS BX_CPU_THIS_PTR

#include <stdlib.h>
#ifdef WASI
#include <unistd.h>
#endif

#define HW_RANDOM_GENERATOR_READY (1)

static int random_byte(void)
{
#ifdef WASI
  // rand() state is captured in the Wizer snapshot, so every resume would replay it.
  unsigned char byte;
  if (getentropy(&byte, 1) == 0) return byte;
#endif
  return rand() & 0xff;
}

void BX_CPP_AttrRegparmN(1) BX_CPU_C::RDRAND_Ew(bxInstruction_c *i)
{
#if BX_SUPPORT_VMX
  if (BX_CPU_THIS_PTR in_vmx_guest) {
    if (SECONDARY_VMEXEC_CONTROL(VMX_VM_EXEC_CTRL3_RDRAND_VMEXIT)) {
      VMexit_Instruction(i, VMX_VMEXIT_RDRAND, BX_READ);
    }
  }
#endif

  Bit16u val_16 = 0;

  clearEFlagsOSZAPC();

  if (HW_RANDOM_GENERATOR_READY) {
    val_16 |= random_byte();
    val_16 <<= 8;
    val_16 |= random_byte();

    assert_CF();
  }

  BX_WRITE_16BIT_REG(i->dst(), val_16);

  BX_NEXT_INSTR(i);
}

void BX_CPP_AttrRegparmN(1) BX_CPU_C::RDRAND_Ed(bxInstruction_c *i)
{
#if BX_SUPPORT_VMX
  if (BX_CPU_THIS_PTR in_vmx_guest) {
    if (SECONDARY_VMEXEC_CONTROL(VMX_VM_EXEC_CTRL3_RDRAND_VMEXIT)) {
      VMexit_Instruction(i, VMX_VMEXIT_RDRAND, BX_READ);
    }
  }
#endif

  Bit32u val_32 = 0;

  clearEFlagsOSZAPC();

  if (HW_RANDOM_GENERATOR_READY) {
    val_32 |= random_byte();
    val_32 <<= 8;
    val_32 |= random_byte();
    val_32 <<= 8;
    val_32 |= random_byte();
    val_32 <<= 8;
    val_32 |= random_byte();

    assert_CF();
  }

  BX_WRITE_32BIT_REGZ(i->dst(), val_32);

  BX_NEXT_INSTR(i);
}

#if BX_SUPPORT_X86_64
void BX_CPP_AttrRegparmN(1) BX_CPU_C::RDRAND_Eq(bxInstruction_c *i)
{
#if BX_SUPPORT_VMX
  if (BX_CPU_THIS_PTR in_vmx_guest) {
    if (SECONDARY_VMEXEC_CONTROL(VMX_VM_EXEC_CTRL3_RDRAND_VMEXIT)) {
      VMexit_Instruction(i, VMX_VMEXIT_RDRAND, BX_READ);
    }
  }
#endif

  Bit64u val_64 = 0;

  clearEFlagsOSZAPC();

  if (HW_RANDOM_GENERATOR_READY) {
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();

    assert_CF();
  }

  BX_WRITE_64BIT_REG(i->dst(), val_64);

  BX_NEXT_INSTR(i);
}
#endif

void BX_CPP_AttrRegparmN(1) BX_CPU_C::RDSEED_Ew(bxInstruction_c *i)
{
#if BX_SUPPORT_VMX
  if (BX_CPU_THIS_PTR in_vmx_guest) {
    if (SECONDARY_VMEXEC_CONTROL(VMX_VM_EXEC_CTRL3_RDSEED_VMEXIT)) {
      VMexit_Instruction(i, VMX_VMEXIT_RDSEED, BX_READ);
    }
  }
#endif

  Bit16u val_16 = 0;

  clearEFlagsOSZAPC();

  if (HW_RANDOM_GENERATOR_READY) {
    val_16 |= random_byte();
    val_16 <<= 8;
    val_16 |= random_byte();

    assert_CF();
  }

  BX_WRITE_16BIT_REG(i->dst(), val_16);

  BX_NEXT_INSTR(i);
}

void BX_CPP_AttrRegparmN(1) BX_CPU_C::RDSEED_Ed(bxInstruction_c *i)
{
#if BX_SUPPORT_VMX
  if (BX_CPU_THIS_PTR in_vmx_guest) {
    if (SECONDARY_VMEXEC_CONTROL(VMX_VM_EXEC_CTRL3_RDSEED_VMEXIT)) {
      VMexit_Instruction(i, VMX_VMEXIT_RDSEED, BX_READ);
    }
  }
#endif

  Bit32u val_32 = 0;

  clearEFlagsOSZAPC();

  if (HW_RANDOM_GENERATOR_READY) {
    val_32 |= random_byte();
    val_32 <<= 8;
    val_32 |= random_byte();
    val_32 <<= 8;
    val_32 |= random_byte();
    val_32 <<= 8;
    val_32 |= random_byte();

    assert_CF();
  }

  BX_WRITE_32BIT_REGZ(i->dst(), val_32);

  BX_NEXT_INSTR(i);
}

#if BX_SUPPORT_X86_64
void BX_CPP_AttrRegparmN(1) BX_CPU_C::RDSEED_Eq(bxInstruction_c *i)
{
#if BX_SUPPORT_VMX
  if (BX_CPU_THIS_PTR in_vmx_guest) {
    if (SECONDARY_VMEXEC_CONTROL(VMX_VM_EXEC_CTRL3_RDSEED_VMEXIT)) {
      VMexit_Instruction(i, VMX_VMEXIT_RDSEED, BX_READ);
    }
  }
#endif

  Bit64u val_64 = 0;

  clearEFlagsOSZAPC();

  if (HW_RANDOM_GENERATOR_READY) {
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();
    val_64 <<= 8;
    val_64 |= random_byte();

    assert_CF();
  }

  BX_WRITE_64BIT_REG(i->dst(), val_64);

  BX_NEXT_INSTR(i);
}
#endif
