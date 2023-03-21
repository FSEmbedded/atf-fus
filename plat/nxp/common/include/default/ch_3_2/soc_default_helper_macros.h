/*
 * Copyright 2018-2021 NXP
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef SOC_DEFAULT_HELPER_MACROS_H
#define SOC_DEFAULT_HELPER_MACROS_H

#ifdef NXP_OCRAM_TZPC_ADDR

/* 0x1: means 4 KB
 * 0x2: means 8 KB
 */
#define TZPC_BLOCK_SIZE		0x1000
#endif

/* DDR controller offsets and defines */
#ifdef NXP_DDR_ADDR

#define DDR_CFG_2_OFFSET                0x114
#define CFG_2_FORCE_REFRESH             0x80000000

#endif /* NXP_DDR_ADDR */

 /* Reset block register offsets */
#ifdef NXP_RESET_ADDR

/* Register Offset */
#define RST_RSTCR_OFFSET		0x0
#define RST_RSTRQMR1_OFFSET		0x10
#define RST_RSTRQSR1_OFFSET		0x18
#define BRR_OFFSET			0x60

/* helper macros */
#define RSTRQSR1_SWRR			0x800
#define RSTRQMR_RPTOE_MASK		(1 << 19)

#endif /* NXP_RESET_ADDR */

/* secmon register offsets and bitfields */
#define SECMON_HPCOMR_OFFSET	0x4
#define SECMON_HPCOMR_NPSWAEN	0x80000000

/* Secure-Register-File register offsets and bit masks */
#ifdef NXP_RST_ADDR
/* Register Offset */
#define CORE_HOLD_OFFSET		0x140
#define RSTCNTL_OFFSET			0x180

/* Helper macros */
#define SW_RST_REQ_INIT			0x1
#endif

#ifdef NXP_CCN_ADDR
#define NXP_CCN_HN_F_1_ADDR		0x04210000

#define CCN_HN_F_SAM_NODEID_MASK	0x7f
#define CCN_HN_F_SNP_DMN_CTL_OFFSET	0x200
#define CCN_HN_F_SNP_DMN_CTL_SET_OFFSET	0x210
#define CCN_HN_F_SNP_DMN_CTL_CLR_OFFSET	0x220
#define CCN_HN_F_SNP_DMN_CTL_MASK	0x80a00
#define CCN_HNF_NODE_COUNT              8
#define CCN_HNF_OFFSET                  0x10000

#define SA_AUX_CTRL_REG_OFFSET		0x500
#define NUM_HNI_NODE			2
#define CCN_HNI_MEMORY_MAP_SIZE		0x10000

#define PCIeRC_RN_I_NODE_ID_OFFSET	0x8
#define PoS_CONTROL_REG_OFFSET		0x0
#define POS_EARLY_WR_COMP_EN		0x20
#define HNI_POS_EN			0x01
#define POS_TERMINATE_BARRIERS		0x10
#define SERIALIZE_DEV_nGnRnE_WRITES	0x200
#define ENABLE_ERR_SIGNAL_TO_MN		0x4
#define ENABLE_RESERVE_BIT53		0x400
#define ENABLE_WUO			0x10
#endif

#define DCFG_SBEESR2_ADDR		0x00100534
#define DCFG_MBEESR2_ADDR		0x00100544
/* SBEESR and MBEESR bit mask */
#define OCRAM_EESR_MASK			0x00000008

#endif	/*	SOC_DEFAULT_HELPER_MACROS_H	*/
