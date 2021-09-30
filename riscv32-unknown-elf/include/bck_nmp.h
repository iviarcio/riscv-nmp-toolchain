#ifndef __NMP_H__
#define __NMP_H__

/*
 * Copyright (c) 2017-2019, LG Electronics Inc.
 *
 * This program or software including the accompanying associated documentation
 * ("Software") is the proprietary software of LG Electronics Inc. and or its
 * licensors, and may only be used, duplicated, modified or distributed pursuant
 * to the terms and conditions of a separate written license agreement between
 * you and LG Electronics Inc. ("Authorized License"). Except as set forth in an
 * Authorized License, LG Electronics Inc. grants no license (express or implied),
 * rights to use, or waiver of any kind with respect to the Software, and LG
 * Electronics Inc. expressly reserves all rights in and to the Software and all
 * intellectual property therein. If you have no Authorized License, then you
 * have no rights to use the Software in any ways, and should immediately notify
 * LG Electronics Inc. and discontinue all use of the Software.
 *
 * Author:
 *  Tariq Afzal <tariq.afzal@lge.com>
 *  Bharath <bharath.malalurrao@lgepartner.com>
 *  SeungRyeol Lee <zizztux.lee@lge.com>
 */

/* vi: set ts=4 sw=2 sts=2 expandtab: */

#include <stdint.h>


#define NMP_REG_STATUS            0x80
#define NMP_REG_CONFIG0           0x81
#define NMP_REG_CONFIG1           0x82
#define NMP_REG_MADDR             0x83
#define NMP_REG_MDATA             0x84
#define NMP_REG_ERROR             0x85
#define NMP_REG_SEMAPHORE         0x86
#define NMP_REG_ID                0x87
#define NMP_REG_PARAM0            0x88
#define NMP_REG_PARAM1            0x89
#define NMP_REG_PARAM2            0x8a
#define NMP_REG_PARAM3            0x8b
#define NMP_REG_PARAM4            0x8c
#define NMP_REG_STP_CONFIG0       0x8d
#define NMP_REG_STP_CONFIG1       0x8e
#define NMP_REG_RCORE_PC          0x8f
#define NMP_REG_CACHE_BASE        0x90
#define NMP_REG_GPR0              0x91
#define NMP_REG_GPR1              0x92
#define NMP_REG_GPR2              0x93
#define NMP_REG_GPR3              0x94

#define NMP_ELMSIZE_SAME          0x0
#define NMP_ELMSIZE_TRUNCATE_LSB  0x1
#define NMP_ELMSIZE_SIGNEXT_MSB   0x2
#define NMP_ELMSIZE_ZEROPAD_LSB   0x3

#define NMP_CONV_PADD_SAME        0
#define NMP_CONV_PADD_VALID       1

#define NMP_CONV_NORM             0x0
#define NMP_CONV_STACKED          0x8
#define NMP_CONV_DILATED          0x1
#define NMP_CONV_DILATED_STACKED  0x9

#define NMP_PERCEPT_NORM          0x0
#define NMP_PERCEPT_STACKED       0x1

#define NMP_LDST_MBLOB0           0x1
#define NMP_LDST_MBLOB1           0x2
#define NMP_LDST_MBLOB2           0x4
#define NMP_LDST_DMEM             0x20

#define NMP_ACT_NONE              0
#define NMP_ACT_RELU              1
#define NMP_ACT_RELU6             2
#define NMP_ACT_PRELU             3
#define NMP_ACT_SIGM              4
#define NMP_ACT_TANH              5

#define NMP_POOL_AVG              0
#define NMP_POOL_MAX              1
#define NMP_POOL_XXX              2
#define NMP_POOL_IDX              3

#define NMP_VEOP_VMIN             0x0
#define NMP_VEOP_VSYN             0x1

#define NMP_VEOP_OFFS             0x0
#define NMP_VEOP_NORM             0x1
#define NMP_VEOP_VADD             0x2
#define NMP_VEOP_VMUL             0x3

#define NMP_SATURATE_ON           0x1
#define NMP_SATURATE_OFF          0x0

#define NMP_BIT_EXT_ON            0x1
#define NMP_BIT_EXT_OFF           0x0

#define NMP_SEMA_TLT              0
#define NMP_SEMA_TLE              1
#define NMP_SEMA_GLB              2
#define NMP_SEMA_PRD              3

#define NMP_SEMA_SET              1
#define NMP_SEMA_CLEAR            0

#define NMP_NPU_IDLE              1

#define NMP_HALT_NOP              0
#define NMP_HALT_INT              1

#define NMP_CFG_REG_MBLOB0        0x0
#define NMP_CFG_REG_MBLOB1        0x1
#define NMP_CFG_REG_MBLOB2        0x2
#define NMP_CFG_REG_MBLOB3        0x3
#define NMP_CFG_REG_DATFMT        0x4
#define NMP_CFG_REG_WGTFMT        0x5
#define NMP_CFG_REG_SCLFAC        0x6
#define NMP_CFG_REG_RUNCTL        0x7
#define NMP_CFG_REG_OSE           0x8
#define NMP_CFG_REG_BIASQ         0x9

#define NMP_CFG_RD_MBLOB_VSC      0x0
#define NMP_CFG_RD_MBLOB_DEF      0x0
#define NMP_CFG_RD_MBLOB_MIN      0x1
#define NMP_CFG_RD_MBLOB_SYN      0x2
#define NMP_CFG_RD_MBLOB_DME      0x3
#define NMP_CFG_WR_MBLOB_VSC      (0x0 << 2)
#define NMP_CFG_WR_MBLOB_DEF      (0x0 << 2)
#define NMP_CFG_WR_MBLOB_MOU      (0x1 << 2)
#define NMP_CFG_WR_MBLOB_STP      (0x2 << 2)
#define NMP_CFG_WR_MBLOB_DME      (0x3 << 2)

#define NMP_CFG_DFXP_SIZE_D08     (0x1 << 4)
#define NMP_CFG_DFXP_SIZE_D16     (0x0 << 4)

#define NMP_CFG_DFXP_Q0           0x0
#define NMP_CFG_DFXP_Q1           0x1
#define NMP_CFG_DFXP_Q2           0x2
#define NMP_CFG_DFXP_Q3           0x3
#define NMP_CFG_DFXP_Q4           0x4
#define NMP_CFG_DFXP_Q5           0x5
#define NMP_CFG_DFXP_Q6           0x6
#define NMP_CFG_DFXP_Q7           0x7
#define NMP_CFG_DFXP_Q8           0x8
#define NMP_CFG_DFXP_Q9           0x9
#define NMP_CFG_DFXP_Q10          0xa
#define NMP_CFG_DFXP_Q11          0xb
#define NMP_CFG_DFXP_Q12          0xc
#define NMP_CFG_DFXP_Q13          0xd
#define NMP_CFG_DFXP_Q14          0xe
#define NMP_CFG_DFXP_Q15          0xf

#define NMP_INP_SCALE             0x1
#define NMP_INP_MEAN_CH           (0x1 << 1)
#define NMP_INP_MEAN_PX           (0x1 << 2)

static inline uint32_t nmp_csr_read(uint32_t csr)
{
  uint32_t value;

  __asm__ __volatile__ (
      "csrr       %0, %1"
      : "=r"(value)
      : "i"(csr));

  return value;
}

static inline void nmp_csr_write(uint32_t csr, uint32_t value)
{
  __asm__ __volatile__ (
      "csrw       %0, %1"
      :: "i"(csr), "r"(value));
}

static inline void nmp_csr_set(uint32_t csr, uint32_t value)
{
  __asm__ __volatile__ (
      "csrs       %0, %1"
      :: "i"(csr), "r"(value));
}

static inline void nmp_csr_clear(uint32_t csr, uint32_t value)
{
  __asm__ __volatile__ (
      "csrc       %0, %1"
      :: "i"(csr), "r"(value));
}

static inline uint32_t nmp_cfg_mblob(uint32_t mb0_cfg, uint32_t mb1_cfg, uint32_t mb2_cfg)
{
  uint32_t mb3_cfg = 0x0;
  uint32_t val = (mb3_cfg << 12) | (mb2_cfg << 8) | (mb1_cfg << 4) | mb0_cfg;

  nmp_csr_write(NMP_REG_CONFIG1, val);

  return val;
}

static inline void nmp_cfg_update(uint32_t cfg_field, uint32_t value)
{
  uint32_t val = value;
  uint32_t clr_msk = 0;

  switch (cfg_field) {
  case NMP_CFG_REG_MBLOB0: // 4 bits, start 0
    val = val << 0;
    clr_msk = 0xf << 0;
    nmp_csr_clear(NMP_REG_CONFIG1, clr_msk);
    nmp_csr_set(NMP_REG_CONFIG1, val);
    break;
  case NMP_CFG_REG_MBLOB1: // 4 bits, start 4
    val = val << 4;
    clr_msk = 0xf << 4;
    nmp_csr_clear(NMP_REG_CONFIG1, clr_msk);
    nmp_csr_set(NMP_REG_CONFIG1, val);
    break;
  case NMP_CFG_REG_MBLOB2: // 4 bits, start 8
    val = val << 8;
    clr_msk = 0xf << 8;
    nmp_csr_clear(NMP_REG_CONFIG1, clr_msk);
    nmp_csr_set(NMP_REG_CONFIG1, val);
    break;
  case NMP_CFG_REG_MBLOB3: // 4 bits, start 12
    val = val << 12;
    clr_msk = 0xf << 12;
    nmp_csr_clear(NMP_REG_CONFIG1, clr_msk);
    nmp_csr_set(NMP_REG_CONFIG1, val);
    break;

  case NMP_CFG_REG_DATFMT: // 6 bits, start 4
    val = val << 4;
    clr_msk = 0x3f << 4;
    nmp_csr_clear(NMP_REG_CONFIG0, clr_msk);
    nmp_csr_set(NMP_REG_CONFIG0, val);
    break;
  case NMP_CFG_REG_WGTFMT: // 8 bits, start 12
    val = val << 12;
    clr_msk = 0xff << 12;
    nmp_csr_clear(NMP_REG_CONFIG0, clr_msk);
    nmp_csr_set(NMP_REG_CONFIG0, val);
    break;
  case NMP_CFG_REG_SCLFAC: // 4 bits, start 20
    val = (val & 0xf) << 20;
    clr_msk = 0xf << 20;
    nmp_csr_clear(NMP_REG_CONFIG0, clr_msk);
    nmp_csr_set(NMP_REG_CONFIG0, val);
    break;
  case NMP_CFG_REG_BIASQ: // 5 bits, start 24
    val = (val & 0x1f) << 24;
    clr_msk = 0x1f << 24;
    nmp_csr_clear(NMP_REG_CONFIG0, clr_msk);
    nmp_csr_set(NMP_REG_CONFIG0, val);
    break;
  case NMP_CFG_REG_RUNCTL: // 4 bits, start 0
    val = val << 0;
    clr_msk = 0xf;
    nmp_csr_clear(NMP_REG_CONFIG0, clr_msk);
    nmp_csr_set(NMP_REG_CONFIG0, val);
    break;
  case NMP_CFG_REG_OSE: // 1 bit, start 31
    val = val << 31;
    clr_msk = 0x1 << 31;
    nmp_csr_clear(NMP_REG_CONFIG0, clr_msk);
    nmp_csr_set(NMP_REG_CONFIG0, val);
    break;
  default:
    break;
  }
}

static inline uint32_t nmp_cfg_dfxp(uint32_t datfmt_cfg, uint32_t wgtfmt_cfg, int32_t ilsfmt_cfg, uint32_t sat_cfg/*, uint32_t biasq_cfg*/)
{
  uint32_t biasq_cfg = 0x0;
  uint32_t val = (sat_cfg << 31) | (biasq_cfg << 24) | ((ilsfmt_cfg & 0xf) << 20) | (wgtfmt_cfg << 12) | (datfmt_cfg << 4);

  nmp_csr_write(NMP_REG_CONFIG0, val);

  return val;
}

static inline void nmp_load(uint32_t sys_addr, uint32_t tlt_addr, uint32_t signal_done, uint32_t num_bytes, uint32_t target_mem, uint32_t elm_size)
{
  uint32_t p0 = (signal_done << 16) | (num_bytes - 1);
  uint32_t p4 = (elm_size << 28) | (target_mem << 17);

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "csrw       nparam4, %1\n\t"
      "n.load     %2, %3"
      :: "r"(p0), "r"(p4), "r"(sys_addr), "r"(tlt_addr));
}

static inline void nmp_store(uint32_t tlt_addr, uint32_t sys_addr, uint32_t signal_done, uint32_t num_bytes, uint32_t source_mem)
{
  uint32_t p0 = (signal_done << 16) | (num_bytes - 1);
  uint32_t p4 = source_mem << 17;

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "csrw       nparam4, %1\n\t"
      "n.store    %2, %3"
      :: "r"(p0), "r"(p4), "r"(sys_addr), "r"(tlt_addr));
}

static inline void nmp_load3d(uint32_t sys_addr, uint32_t tlt_addr, uint32_t signal_done, uint32_t num_bytes, uint32_t target_mem, uint32_t num_rows, uint32_t num_chans, uint32_t bytes_row_skip, uint32_t bytes_chan_skip, uint32_t multicast, uint32_t tlt_bytes_row_skip, uint32_t tlt_bytes_chan_skip, uint32_t zero_fill, uint32_t elm_size)
{
  uint32_t p0 = (signal_done << 16) | (num_bytes - 1);
  //uint32_t p0 = ((num_bytes - 1) << 16) | signal_done;
  uint32_t p1 = ((num_rows - 1) << 16) | (num_chans - 1);
  uint32_t p2 = (bytes_chan_skip << 12) | bytes_row_skip;
  uint32_t p3 = (tlt_bytes_chan_skip << 16) | tlt_bytes_row_skip;
  uint32_t p4 = (elm_size << 28) | (target_mem << 17) | (zero_fill << 16) | multicast;

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "csrw       nparam1, %1\n\t"
      "csrw       nparam2, %2\n\t"
      "csrw       nparam3, %3\n\t"
      "csrw       nparam4, %4\n\t"
      "n.load3d   %5, %6"
      :: "r"(p0), "r"(p1), "r"(p2), "r"(p3), "r"(p4), "r"(sys_addr), "r"(tlt_addr));
}

static inline void nmp_zrfill(uint32_t tlt_addr, uint32_t signal_done, uint32_t num_bytes, uint32_t target_mem, uint32_t num_rows, uint32_t num_chans, uint32_t multicast, uint32_t tlt_bytes_row_skip, uint32_t tlt_bytes_chan_skip)
{
  uint32_t p0 = (signal_done << 16) | (num_bytes - 1);
  uint32_t p1 = ((num_rows - 1) << 16) | (num_chans - 1);
  uint32_t p3 = (tlt_bytes_chan_skip << 16) | tlt_bytes_row_skip;
  uint32_t p4 = (target_mem << 17) | (0x1 << 16) | multicast;

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "csrw       nparam1, %1\n\t"
      "csrw       nparam2, zero\n\t"
      "csrw       nparam3, %2\n\t"
      "csrw       nparam4, %3\n\t"
      "n.load3d   zero, %4"
      :: "r"(p0), "r"(p1), "r"(p3), "r"(p4), "r"(tlt_addr));
}

static inline void nmp_store3d(uint32_t tlt_addr, uint32_t sys_addr, uint32_t signal_done, uint32_t num_bytes, uint32_t source_mem, uint32_t num_rows, uint32_t num_chans, uint32_t bytes_row_skip, uint32_t bytes_chan_skip, uint32_t multicast, uint32_t tlt_bytes_row_skip, uint32_t tlt_bytes_chan_skip, uint32_t zero_fill)
{
  uint32_t p0 = (signal_done << 16) | (num_bytes - 1);
  uint32_t p1 = ((num_rows - 1) << 16) | (num_chans - 1);
  uint32_t p2 = (bytes_chan_skip << 12) | bytes_row_skip;
  uint32_t p3 = (tlt_bytes_chan_skip << 16) | tlt_bytes_row_skip;
  uint32_t p4 = (source_mem << 17) | (zero_fill << 16) | multicast;

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "csrw       nparam1, %1\n\t"
      "csrw       nparam2, %2\n\t"
      "csrw       nparam3, %3\n\t"
      "csrw       nparam4, %4\n\t"
      "n.store3d  %5, %6"
      :: "r"(p0), "r"(p1), "r"(p2), "r"(p3), "r"(p4), "r"(sys_addr), "r"(tlt_addr));
}

static inline void nmp_activate(uint32_t src_addr, uint32_t dst_addr, uint32_t in_size, uint32_t act_type/*, uint32_t alpha*/)
{
  uint32_t alpha = 0x0;
  uint32_t rs1 = (dst_addr << 16) | src_addr;
  uint32_t rs2 = in_size - 1;
  uint32_t p2 = (alpha << 20) | (act_type << 13);
  uint32_t p1 = act_type;

  __asm__ __volatile__ (
      "csrw       nparam1, %0\n\t"
      "n.activate %1, %2"
      :: "r"(p1), "r"(rs1), "r"(rs2));
}

static inline void nmp_pool(uint32_t src_addr, uint32_t dst_addr, uint32_t isize_x, uint32_t isize_y, uint32_t pool_type, uint32_t kx, uint32_t ky, uint32_t sx, uint32_t sy)
{
  uint32_t osize_x = (isize_x - kx) / sx;
  uint32_t osize_y = (isize_y - ky) / sy;
  uint32_t ix_sy = isize_x * sy;
  uint32_t rs1 = (dst_addr << 16) | src_addr;
  uint32_t rs2 = (pool_type << 28) | ((isize_y -1) << 14) | (isize_x - 1);  // isize_y used in spike

  /*
     * From spike -- it is different
      unsigned p2 = size_col*(sy - 1) + 1;
  */

  uint32_t p0 = ((ky - 1) << 16) | (kx - 1);
  uint32_t p1 = (sy << 16) | sx;
  //uint32_t p2 = (osize_y << 16) | osize_x;
  uint32_t p2 = isize_x * (sy - 1) + 1;

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "csrw       nparam1, %1\n\t"
      "csrw       nparam2, %2\n\t"
      "n.pool     %3, %4"
      :: "r"(p0), "r"(p1), "r"(p2), "r"(rs1), "r"(rs2));

//  __asm__ __volatile__ (
//      "csrw       nparam0, %0\n\t"
//      "csrw       nparam1, %1\n\t"
// //     "csrw       nparam2, %2\n\t"
//      "n.pool     %3, %4"
//      :: "r"(p0), "r"(p1), /*"r"(p2),*/ "r"(rs1), "r"(rs2));
}

static inline void nmp_percept(uint32_t src_addr, uint32_t dst_addr, uint32_t wgt_addr, uint32_t in_size, uint32_t out_size, uint32_t act_type, /*uint32_t alpha,*/ uint32_t percept_type, uint32_t be)
{
  uint32_t alpha = 0x0;
  uint32_t rs1 = (dst_addr << 16) | src_addr;
  uint32_t rs2 = wgt_addr;
  uint32_t p0 = ((out_size - 1) << 16) | (in_size - 1);
  uint32_t p2 = (percept_type << 27) | (alpha << 20) | (be << 18) | (act_type << 13);

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "csrw       nparam2, %1\n\t"
      "n.percept  %2, %3"
      :: "r"(p0), "r"(p2), "r"(rs1), "r"(rs2));
}

static inline void nmp_veop(uint32_t src1_addr, uint32_t src2_addr, uint32_t dst_addr, uint32_t size, uint32_t num_vector, uint32_t src2_mblob, uint32_t vop)
{
  uint32_t rs1 = (dst_addr << 16) | src1_addr;
  uint32_t rs2 = src2_addr;
  uint32_t p0 = (vop << 25) | (src2_mblob << 24) | ((num_vector - 1) << 16) | (size - 1);

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "n.veop     %1, %2"
      :: "r"(p0), "r"(rs1), "r"(rs2));
}

static inline void nmp_conv3d(uint32_t src_addr, uint32_t dst_addr, uint32_t wgt_addr,/* uint32_t ba_addr,*/ uint32_t conv_type, uint32_t ifm, uint32_t ofm, uint32_t in_row, uint32_t in_col, uint32_t kx, uint32_t ky, uint32_t stride, uint32_t dilation, /*uint32_t bias, uint32_t act, uint32_t alpha,*/ uint32_t be)
{
  uint32_t ba_addr = 0x0;
  uint32_t bias = 0x0;
  uint32_t act = 0x0;
  uint32_t alpha = 0x0;
  uint32_t p0, p1, p2, p3;
  uint32_t out_row, out_col;
  uint32_t str_dil;
  uint32_t rs1 = (dst_addr << 16) | src_addr;
  uint32_t rs2 = (ba_addr << 16) | wgt_addr;

  if ((conv_type & 0x7) == NMP_CONV_DILATED) {
    str_dil = dilation;
    stride = 1;
    out_row = in_row - (1 << dilation) * (ky - 1) - 1;
    out_col = in_col - (1 << dilation) * (kx - 1) - 1;
  }
  else {
    str_dil = stride;
    out_row = (in_row - ky) / stride;
    out_col = (in_col - kx) / stride;
  }

  if (stride == 0)
    stride = 1;

  p0 = ((ifm - 1) << 16) | (ofm - 1);
  p1 = (out_col << 16) | out_row;
  p2 = (conv_type << 24) | (alpha << 20) | (be << 18) | (bias << 17) | (act << 13) | (str_dil << 8) | ((ky - 1) << 4) | (kx - 1);
  p3 = (in_col << 16) | in_row;

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "csrw       nparam1, %1\n\t"
      "csrw       nparam2, %2\n\t"
      "csrw       nparam3, %3\n\t"
      "n.conv3d   %4, %5"
      :: "r"(p0), "r"(p1), "r"(p2), "r"(p3), "r"(rs1), "r"(rs2));
}

static inline uint32_t nmp_conv3d_v2_param(uint32_t conv_type, uint32_t kx, uint32_t ky, uint32_t stride, uint32_t dilation)
{
  uint32_t str_dil;
  uint32_t conv_param;

  if (conv_type == NMP_CONV_DILATED)
    str_dil = dilation;
  else
    str_dil = stride;

  conv_param = (str_dil << 8) | ((ky - 1) << 4) | (kx - 1);

  return conv_param;
}

static inline void nmp_conv3d_v2(uint32_t src_addr, uint32_t dst_addr, uint32_t wgt_addr, uint32_t ba_addr, uint32_t conv_type, uint32_t ifm, uint32_t ofm, uint32_t in_row, uint32_t in_col, int32_t out_row, uint32_t out_col, uint32_t conv_param, uint32_t bias, uint32_t act, uint32_t alpha, uint32_t be)
{
  uint32_t p0, p1, p2, p3;
  uint32_t rs1 = (dst_addr << 16) | src_addr;
  uint32_t rs2 = (ba_addr << 16) | wgt_addr;

  p0 = ((ifm - 1) << 16) | (ofm - 1);
  p1 = ((out_col - 1) << 16) | (out_row - 1);
  p2 = (conv_type << 24) | (alpha << 20) | (be << 18) | (bias << 17) | (act << 13) | conv_param;
  p3 = (in_col << 16) | in_row;

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "csrw       nparam1, %1\n\t"
      "csrw       nparam2, %2\n\t"
      "csrw       nparam3, %3\n\t"
      "n.conv3d   %4, %5"
      :: "r"(p0), "r"(p1), "r"(p2), "r"(p3), "r"(rs1), "r"(rs2));
}

static inline void nmp_wait(uint32_t domain, uint32_t mask)
{
  uint32_t rs2 = (domain == NMP_SEMA_PRD) ? ((mask << 2) | domain) : domain;

  __asm__ __volatile__ (
      "n.wait     %0, %1"
      :: "r"(mask), "r"(rs2));
}

static inline void nmp_signal(uint32_t domain, uint32_t sop, uint32_t mask)
{
  uint32_t rs2 = (sop << 2) | domain;

  __asm__ __volatile__ (
      "n.signal   %0, %1"
      :: "r"(mask), "r"(rs2));
}

static inline void nmp_signal_n_wait(uint32_t signal_domain, uint32_t wait_domain, uint32_t signal_op, uint32_t signal_mask, uint32_t wait_mask)
{
  uint32_t p0 = (wait_domain << 3) | (signal_op << 2) | signal_domain;

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "n.signwait %1, %2"
      :: "r"(p0), "r"(signal_mask), "r"(wait_mask));
}

static inline void nmp_halt(uint32_t hop, uint32_t mask)
{
  __asm__ __volatile__ (
      "n.halt     %0, %1"
      :: "r"(mask), "r"(hop));
}

static inline void nmp_cpy2stp(uint32_t src_addr, uint32_t num_bytes)
{
  __asm__ __volatile__ (
      "n.cpy2stp  %0, %1"
      :: "r"(src_addr), "r"(num_bytes - 1));
}

static inline void nmp_set_n_clr(uint32_t set_domain, uint32_t clr_domain, uint32_t set_mask, uint32_t clr_mask)
{
  uint32_t p0 = (clr_domain << 2) | set_domain;

  __asm__ __volatile__ (
      "csrw       nparam0, %0\n\t"
      "n.setnclr  %1, %2"
      :: "r"(p0), "r"(set_mask), "r"(clr_mask));
}

#endif
