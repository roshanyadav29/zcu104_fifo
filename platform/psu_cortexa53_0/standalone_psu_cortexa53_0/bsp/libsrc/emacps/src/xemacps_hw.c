/******************************************************************************
* Copyright (C) 2010 - 2022 Xilinx, Inc.  All rights reserved.
* Copyright (C) 2022 - 2024 Advanced Micro Devices, Inc. All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
*
* @file xemacps_hw.c
* @addtogroup emacps Overview
* @{
*
* This file contains the implementation of the ethernet interface reset sequence
*
* <pre>
* MODIFICATION HISTORY:
*
* Ver   Who  Date     Changes
* ----- ---- -------- -------------------------------------------------------
* 1.05a kpc  28/06/13 First release
* 3.00  kvn  02/13/15 Modified code for MISRA-C:2012 compliance.
* </pre>
*
******************************************************************************/

/***************************** Include Files *********************************/

#include <assert.h>
#include "xemacps_hw.h"
#include "xparameters.h"

/************************** Constant Definitions *****************************/


/**************************** Type Definitions *******************************/


/***************** Macros (Inline Functions) Definitions *********************/


/************************** Function Prototypes ******************************/

/*****************************************************************************/
/**
* This function perform the reset sequence to the given emacps interface by
* configuring the appropriate control bits in the emacps specific registers.
* the emacps reset sequence involves the following steps
*	Disable all the interuupts
*	Clear the status registers
*	Disable Rx and Tx engines
*	Update the Tx and Rx descriptor queue registers with reset values
*	Update the other relevant control registers with reset value
*
* @param   BaseAddr of the interface
*
* @return N/A
*
* @note
* This function will not modify the slcr registers that are relevant for
* emacps controller
******************************************************************************/
void XEmacPs_ResetHw(u32 BaseAddr)
{
	u32 RegVal;

	/* Disable the interrupts  */
	XEmacPs_WriteReg(BaseAddr,XEMACPS_IDR_OFFSET,0x0U);

	/* Stop transmission,disable loopback and Stop tx and Rx engines */
	RegVal = XEmacPs_ReadReg(BaseAddr,XEMACPS_NWCTRL_OFFSET);
	RegVal &= ~((u32)XEMACPS_NWCTRL_TXEN_MASK|
				(u32)XEMACPS_NWCTRL_RXEN_MASK|
				(u32)XEMACPS_NWCTRL_HALTTX_MASK|
				(u32)XEMACPS_NWCTRL_LOOPEN_MASK);
	/* Clear the statistic registers, flush the packets in DPRAM*/
	RegVal |= (XEMACPS_NWCTRL_STATCLR_MASK|
				XEMACPS_NWCTRL_FLUSH_DPRAM_MASK);
	XEmacPs_WriteReg(BaseAddr,XEMACPS_NWCTRL_OFFSET,RegVal);
	/* Clear the interrupt status */
	XEmacPs_WriteReg(BaseAddr,XEMACPS_ISR_OFFSET,XEMACPS_IXR_ALL_MASK);
	/* Clear the tx status */
	XEmacPs_WriteReg(BaseAddr,XEMACPS_TXSR_OFFSET,(XEMACPS_TXSR_ERROR_MASK|
									(u32)XEMACPS_TXSR_TXCOMPL_MASK|
									(u32)XEMACPS_TXSR_TXGO_MASK));
	/* Clear the rx status */
	XEmacPs_WriteReg(BaseAddr,XEMACPS_RXSR_OFFSET,
								XEMACPS_RXSR_FRAMERX_MASK);
	/* Clear the tx base address */
	XEmacPs_WriteReg(BaseAddr,XEMACPS_TXQBASE_OFFSET,0x0U);
	/* Clear the rx base address */
	XEmacPs_WriteReg(BaseAddr,XEMACPS_RXQBASE_OFFSET,0x0U);
	/* Update the network config register with reset value */
	XEmacPs_WriteReg(BaseAddr,XEMACPS_NWCFG_OFFSET,XEMACPS_NWCFG_RESET_MASK);
	/* Update the hash address registers with reset value */
	XEmacPs_WriteReg(BaseAddr,XEMACPS_HASHL_OFFSET,0x0U);
	XEmacPs_WriteReg(BaseAddr,XEMACPS_HASHH_OFFSET,0x0U);
}

/*****************************************************************************/
/**
* The register offset of a specific queue register is returned by this function.
*
* @param   RegName  Basename of the register
* @param   Queue    Corresponsing Queue
*
* @return  Register offset
******************************************************************************/
u32 XEmacPs_GetQxOffset(XEmacPs_QxRegOffset RegName, u8 Queue)
{
	u32 Map[REG_END][MAX_QUEUES_FEASIBLE] = {
		{XEMACPS_TXQBASE_OFFSET, XEMACPS_TXQ1BASE_OFFSET,
		XEMACPS_TXQ2BASE_OFFSET, XEMACPS_TXQ3BASE_OFFSET }, /* TXQIBASE */
		{XEMACPS_RXQBASE_OFFSET, XEMACPS_RXQ1BASE_OFFSET,
		XEMACPS_RXQ2BASE_OFFSET, XEMACPS_RXQ3BASE_OFFSET }, /* RXQIBASE */
		{0, XEMACPS_DMA_RXQ1_BUFSIZE_OFFSET,
		XEMACPS_DMA_RXQ2_BUFSIZE_OFFSET,
		XEMACPS_DMA_RXQ3_BUFSIZE_OFFSET }, /* DMA_RXQI_BUFSIZE */
		{XEMACPS_ISR_OFFSET, XEMACPS_INTQ1_STS_OFFSET,
		XEMACPS_INTQ2_STS_OFFSET, XEMACPS_INTQ3_STS_OFFSET }, /* INTQI_STS */
		{0, XEMACPS_INTQ1_IER_OFFSET, XEMACPS_INTQ2_IER_OFFSET,
		XEMACPS_INTQ3_IER_OFFSET },  /* INTQI_IER */
		{0, XEMACPS_INTQ1_IDR_OFFSET, XEMACPS_INTQ2_IDR_OFFSET,
		XEMACPS_INTQ3_IDR_OFFSET }}; /* INTQI_IDR */

	/* Assert when Queue passed is greater than Max Queues Possible */
	assert(Queue <= MAX_QUEUES_FEASIBLE && \
		"ERROR: Specified Queue exceeds the Max Queue!");

	return Map[RegName][Queue];
}
/** @} */
