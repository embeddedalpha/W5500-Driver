/*
 * W5500_LL_Regs.h
 *
 *  Created on: Oct 18, 2024
 *      Author: ksalvi
 */

#ifndef W5500_LOW_LEVEL_W5500_LL_REGS_H_
#define W5500_LOW_LEVEL_W5500_LL_REGS_H_

#include "main.h"

static const struct W5500_Control_Register
{
	struct Common_Register{
		uint16_t Mode;
		uint16_t GAR0;
		uint16_t GAR1;
		uint16_t GAR2;
		uint16_t GAR3;
		uint16_t SUBR0;
		uint16_t SUBR1;
		uint16_t SUBR2;
		uint16_t SUBR3;
		uint16_t SHAR0;
		uint16_t SHAR1;
		uint16_t SHAR2;
		uint16_t SHAR3;
		uint16_t SHAR4;
		uint16_t SHAR5;
		uint16_t SIPR0;
		uint16_t SIPR1;
		uint16_t SIPR2;
		uint16_t SIPR3;
		uint16_t INTLEVEL0;
		uint16_t INTLEVEL1;
		uint16_t IR;
		uint16_t IMR;
		uint16_t SIR;
		uint16_t SIMR;
		uint16_t RTR0;
		uint16_t RTR1;
		uint16_t RCR;
		uint16_t PTIMER;
		uint16_t PMAGIC;
		uint16_t PHAR0;
		uint16_t PHAR1;
		uint16_t PHAR2;
		uint16_t PHAR3;
		uint16_t PHAR4;
		uint16_t PHAR5;
		uint16_t PHAR6;
		uint16_t PSID0;
		uint16_t PSID1;
		uint16_t PMRU0;
		uint16_t PMRU1;
		uint16_t UIPR0;
		uint16_t UIPR1;
		uint16_t UIPR2;
		uint16_t UIPR3;
		uint16_t UPORTR0;
		uint16_t UPORTR1;
		uint16_t PHYCFGR;
		uint16_t VERSIONR;
	}Common_Register;

	struct Socket_Register{

		uint16_t	Sn_MR	;
		uint16_t	Sn_CR	;
		uint16_t	Sn_IR	;
		uint16_t	Sn_SR	;
		uint16_t	Sn_PORT0	;
		uint16_t	Sn_PORT1	;
		uint16_t	Sn_DHAR0	;
		uint16_t	Sn_DHAR1	;
		uint16_t	Sn_DHAR2	;
		uint16_t	Sn_DHAR3	;
		uint16_t	Sn_DHAR4	;
		uint16_t	Sn_DHAR5	;
		uint16_t	Sn_DIPR0	;
		uint16_t	Sn_DIPR1	;
		uint16_t	Sn_DIPR2	;
		uint16_t	Sn_DIPR3	;
		uint16_t	Sn_DPORT0	;
		uint16_t	Sn_DPORT1	;
		uint16_t	Sn_MSSR0	;
		uint16_t	Sn_MSSR1	;
		uint16_t	Sn_TOS	;
		uint16_t	Sn_TTL	;
		uint16_t	Sn_RXBUF_SIZE	;
		uint16_t	Sn_TXBUF_SIZE	;
		uint16_t	Sn_TX_FSR0	;
		uint16_t	Sn_TX_FSR1	;
		uint16_t	Sn_TX_RD0	;
		uint16_t	Sn_TX_RD1	;
		uint16_t	Sn_TX_WR0	;
		uint16_t	Sn_TX_WR1	;
		uint16_t	Sn_RX_RSR0	;
		uint16_t	Sn_RX_RSR1	;
		uint16_t	Sn_RX_RD0	;
		uint16_t	Sn_RX_RD1	;
		uint16_t	Sn_RX_WR0	;
		uint16_t	Sn_RX_WR1	;
		uint16_t	Sn_IMR	;
		uint16_t	Sn_FRAG0	;
		uint16_t	Sn_FRAG1	;
		uint16_t	Sn_KPALVTR	;

	}Socket_Register;

	uint16_t Common_Register_Base;

}W5500_Control_Register = {

		.Common_Register = {
				.Mode	 = 	0	,
				.GAR0	 = 	1	,
				.GAR1	 = 	2	,
				.GAR2	 = 	3	,
				.GAR3	 = 	4	,
				.SUBR0	 = 	5	,
				.SUBR1	 = 	6	,
				.SUBR2	 = 	7	,
				.SUBR3	 = 	8	,
				.SHAR0	 = 	9	,
				.SHAR1	 = 	10	,
				.SHAR2	 = 	11	,
				.SHAR3	 = 	12	,
				.SHAR4	 = 	13	,
				.SHAR5	 = 	14	,
				.SIPR0	 = 	15	,
				.SIPR1	 = 	16	,
				.SIPR2	 = 	17	,
				.SIPR3	 = 	18	,
				.INTLEVEL0	 = 	19	,
				.INTLEVEL1	 = 	20	,
				.IR	 = 	21	,
				.IMR	 = 	22	,
				.SIR	 = 	23	,
				.SIMR	 = 	24	,
				.RTR0	 = 	25	,
				.RTR1	 = 	26	,
				.RCR	 = 	27	,
				.PTIMER	 = 	28	,
				.PMAGIC	 = 	29	,
				.PHAR0	 = 	30	,
				.PHAR1	 = 	31	,
				.PHAR2	 = 	32	,
				.PHAR3	 = 	33	,
				.PHAR4	 = 	34	,
				.PHAR5	 = 	35	,
				.PSID0	 = 	36	,
				.PSID1	 = 	37	,
				.PMRU0	 = 	38	,
				.PMRU1	 = 	39	,
				.UIPR0	 = 	40	,
				.UIPR1	 = 	41	,
				.UIPR2	 = 	42	,
				.UIPR3	 = 	43	,
				.UPORTR0	 = 	44	,
				.UPORTR1	 = 	45	,
				.PHYCFGR	 = 	46	,
				.VERSIONR	 = 	57	,
		},

		.Socket_Register = {
				.Sn_MR	 = 	0	,
				.Sn_CR	 = 	1	,
				.Sn_IR	 = 	2	,
				.Sn_SR	 = 	3	,
				.Sn_PORT0	 = 	4	,
				.Sn_PORT1	 = 	5	,
				.Sn_DHAR0	 = 	6	,
				.Sn_DHAR1	 = 	7	,
				.Sn_DHAR2	 = 	8	,
				.Sn_DHAR3	 = 	9	,
				.Sn_DHAR4	 = 	10	,
				.Sn_DHAR5	 = 	11	,
				.Sn_DIPR0	 = 	12	,
				.Sn_DIPR1	 = 	13	,
				.Sn_DIPR2	 = 	14	,
				.Sn_DIPR3	 = 	15	,
				.Sn_DPORT0	 = 	16	,
				.Sn_DPORT1	 = 	17	,
				.Sn_MSSR0	 = 	18	,
				.Sn_MSSR1	 = 	19	,
				.Sn_TOS	 = 	21	,
				.Sn_TTL	 = 	22	,
				.Sn_RXBUF_SIZE	 = 	30	,
				.Sn_TXBUF_SIZE	 = 	31	,
				.Sn_TX_FSR0	 = 	32	,
				.Sn_TX_FSR1	 = 	33	,
				.Sn_TX_RD0	 = 	34	,
				.Sn_TX_RD1	 = 	35	,
				.Sn_TX_WR0	 = 	36	,
				.Sn_TX_WR1	 = 	37	,
				.Sn_RX_RSR0	 = 	38	,
				.Sn_RX_RSR1	 = 	39	,
				.Sn_RX_RD0	 = 	40	,
				.Sn_RX_RD1	 = 	41	,
				.Sn_RX_WR0	 = 	42	,
				.Sn_RX_WR1	 = 	43	,
				.Sn_IMR	 = 	44	,
				.Sn_FRAG0	 = 	45	,
				.Sn_FRAG1	 = 	46	,
				.Sn_KPALVTR	 = 	47	,
		},

		.Common_Register_Base	 = 	0	,

};

#endif /* W5500_LOW_LEVEL_W5500_LL_REGS_H_ */
