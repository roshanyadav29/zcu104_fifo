/***************************** Include Files *********************************/
#include "xparameters.h"
#include "xil_exception.h"
#include "xstreamer.h"
#include "xil_cache.h"
#include "xllfifo.h"
#include "xstatus.h"

/**************************** Type Definitions *******************************/

/***************** Macros (Inline Functions) Definitions *********************/

#define WORD_SIZE 4			/* Size of words in bytes */
#define MAX_PACKET_LEN 4
#define NO_OF_PACKETS 64
#define MAX_DATA_BUFFER_SIZE NO_OF_PACKETS*MAX_PACKET_LEN
#undef DEBUG

/************************** Function Prototypes ******************************/

int XLlFifoPollingExample(XLlFifo *InstancePtr, UINTPTR BaseAddress);

int TxSend(XLlFifo *InstancePtr, u32 *SourceAddr);
int RxReceive(XLlFifo *InstancePtr, u32 *DestinationAddr);

/************************** Variable Definitions *****************************/
/*
 * Device instance definitions
 */
XLlFifo FifoInstance;

u32 SourceBuffer[MAX_DATA_BUFFER_SIZE * WORD_SIZE];
u32 DestinationBuffer[MAX_DATA_BUFFER_SIZE * WORD_SIZE];

int main()
{
	int Status;

	xil_printf("--- Entering main() ---\n\r");

	Status = XLlFifoPollingExample(&FifoInstance, XPAR_XLLFIFO_0_BASEADDR);

	if (Status != XST_SUCCESS) {
		xil_printf("Axi Streaming FIFO Polling Example Test Failed\n\r");
		xil_printf("--- Exiting main() ---\n\r");
		return XST_FAILURE;
	}

	xil_printf("Successfully ran Axi Streaming FIFO Polling Example\n\r");
	xil_printf("--- Exiting main() ---\n\r");

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
*
* This function demonstrates the usage AXI FIFO
* It does the following:
*       - Set up the output terminal if UART16550 is in the hardware build
*       - Initialize the Axi FIFO Device.
*	- Transmit the data
*	- Receive the data from fifo
*	- Compare the data
*	- Return the result
* @param	InstancePtr is a pointer to the instance of the
*		XLlFifo component.
* @param	DeviceId is Device ID of the Axi Fifo Device instance,
*		typically XPAR_<AXI_FIFO_instance>_DEVICE_ID value from
*		xparameters.h.
* @return
*		-XST_SUCCESS to indicate success
*		-XST_FAILURE to indicate failure
*
******************************************************************************/

int XLlFifoPollingExample(XLlFifo *InstancePtr, UINTPTR BaseAddress)
{
	XLlFifo_Config *Config;
	int Status;
	int i;
	int Error;
	Status = XST_SUCCESS;

	/* Initialize the Device Configuration Interface driver */
	Config = XLlFfio_LookupConfig(BaseAddress);
	if (!Config) {
#ifndef SDT
		xil_printf("No config found for %d\r\n", DeviceId);
#endif
		return XST_FAILURE;
	}

	/*
	 * This is where the virtual address would be used, this example
	 * uses physical address.
	 */
	Status = XLlFifo_CfgInitialize(InstancePtr, Config, Config->BaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("Initialization failed\n\r");
		return Status;
	}

	/* Check for the Reset value */
	Status = XLlFifo_Status(InstancePtr);
	XLlFifo_IntClear(InstancePtr,0xffffffff);
	Status = XLlFifo_Status(InstancePtr);
	if(Status != 0x0) {
		xil_printf("\n ERROR : Reset value of ISR0 : 0x%x\t"
			    "Expected : 0x0\n\r",
			    XLlFifo_Status(InstancePtr));
		return XST_FAILURE;
	}

	/* Transmit the Data Stream */
	Status = TxSend(InstancePtr, SourceBuffer);
	if (Status != XST_SUCCESS){
		xil_printf("Transmission of Data failed\n\r");
		return XST_FAILURE;
	}

	/* Receive the Data Stream */
	Status = RxReceive(InstancePtr, DestinationBuffer);
	if (Status != XST_SUCCESS){
		xil_printf("Receiving data failed");
		return XST_FAILURE;
	}

    /* Print the transmitted buffer */
    xil_printf("\n\r--- Transmitted Data ---\n\r");
    for(i = 0; i < MAX_DATA_BUFFER_SIZE; i++) {
        if(i % 8 == 0) {
            xil_printf("\n\r[%3d]: ", i);
        }
        xil_printf("0x%08x ", *(SourceBuffer + i));
    }
    xil_printf("\n\r");

    /* Print the received buffer */
    xil_printf("\n\r--- Received Data ---\n\r");
    for(i = 0; i < MAX_DATA_BUFFER_SIZE; i++) {
        if(i % 8 == 0) {
            xil_printf("\n\r[%3d]: ", i);
        }
        xil_printf("0x%08x ", *(DestinationBuffer + i));
    }
    xil_printf("\n\r");

	Error = 0;

    /* Compare the data send with the data received */
    xil_printf(" Comparing data ...\n\r");
    for( i=0 ; i<MAX_DATA_BUFFER_SIZE ; i++ ){
        if ( *(SourceBuffer + i) != *(DestinationBuffer + i) ){
            xil_printf("Data mismatch at index %d: Sent=0x%08x, Received=0x%08x\n\r", 
                   i, *(SourceBuffer + i), *(DestinationBuffer + i));
            Error = 1;
            break;
        }

    }

    if (Error != 0){
        xil_printf("Data comparison FAILED\n\r");
        return XST_FAILURE;
    } else {
        xil_printf("Data comparison PASSED - All %d words match!\n\r", MAX_DATA_BUFFER_SIZE);
    }

	return Status;
}

/*****************************************************************************/
/**
*
* TxSend routine, It will send the requested amount of data at the
* specified addr.
* @param	InstancePtr is a pointer to the instance of the
*		XLlFifo component.
* @param	SourceAddr is the address where the FIFO stars writing
* @return
*		-XST_SUCCESS to indicate success
*		-XST_FAILURE to indicate failure
* @note		None
*
******************************************************************************/
int TxSend(XLlFifo *InstancePtr, u32  *SourceAddr)
{

	int i;
	int j;
	xil_printf(" Transmitting Data ... \r\n");

	/* Fill the transmit buffer with incremental pattern */
	for (i=0;i<MAX_DATA_BUFFER_SIZE;i++)
		*(SourceAddr + i) = i;

	for(i=0 ; i < NO_OF_PACKETS ; i++){

		/* Writing into the FIFO Transmit Port Buffer */
		for (j=0 ; j < MAX_PACKET_LEN ; j++){
			if( XLlFifo_iTxVacancy(InstancePtr) ){
				XLlFifo_TxPutWord(InstancePtr,
					*(SourceAddr+(i*MAX_PACKET_LEN)+j));
			}
		}

	}

	/* Start Transmission by writing transmission length into the TLR */
	XLlFifo_iTxSetLen(InstancePtr, (MAX_DATA_BUFFER_SIZE * WORD_SIZE));

	/* Check for Transmission completion */
	while( !(XLlFifo_IsTxDone(InstancePtr)) ){

	}

	/* Transmission Complete */
	return XST_SUCCESS;
}

/*****************************************************************************/
/**
* RxReceive routine.It will receive the data from the FIFO.
* @param	InstancePtr is a pointer to the instance of the
*		XLlFifo instance.
* @param	DestinationAddr is the address where to copy the received data.
* @return
*		-XST_SUCCESS to indicate success
*		-XST_FAILURE to indicate failure
* @note		None
*
******************************************************************************/
int RxReceive (XLlFifo *InstancePtr, u32* DestinationAddr)
{

	int i;
	int Status;
	u32 RxWord;
	static u32 ReceiveLength;

	xil_printf(" Receiving data ....\n\r");

	while(XLlFifo_iRxOccupancy(InstancePtr)) {
		/* Read Receive Length */
		ReceiveLength = (XLlFifo_iRxGetLen(InstancePtr))/WORD_SIZE;
		for (i=0; i < ReceiveLength; i++) {
			RxWord = XLlFifo_RxGetWord(InstancePtr);
			*(DestinationBuffer+i) = RxWord;
		}
	}

	Status = XLlFifo_IsRxDone(InstancePtr);
	if(Status != TRUE){
		xil_printf("Failing in receive complete ... \r\n");
		return XST_FAILURE;
	}

	return XST_SUCCESS;
}