# ✅ AXI4-Stream FIFO Validation on ZCU104

This project validates an AXI4-Stream-based FIFO communication pipeline using the ARM Cortex-A53 on the Zynq UltraScale+ ZCU104 platform.

---

## 📌 Overview

Using Xilinx’s `XLlFifo` driver, this standalone C application demonstrates:

- **Initialization** of the AXI4-Stream FIFO core
- **Transmission** of stream data using polling
- **Reception** and buffer handling of incoming data
- **Data integrity verification** through end-to-end comparison

The design targets the **Processing System (PS)** running on Cortex-A53, interfacing with FIFO IPs in the **Programmable Logic (PL)** region.

---

## 📁 File Summary

- `main()` – Entry point, runs the polling example
- `XLlFifoPollingExample()` – End-to-end test of the FIFO pipeline
- `TxSend()` – Fills source buffer and sends packets via FIFO
- `RxReceive()` – Receives and stores streamed data into a buffer

---

## ⚙️ Key Parameters

| Macro                   | Value   | Description                       |
|------------------------|---------|-----------------------------------|
| `WORD_SIZE`            | `4`     | Bytes per data word               |
| `MAX_PACKET_LEN`       | `4`     | Words per packet                  |
| `NO_OF_PACKETS`        | `64`    | Number of packets to send         |
| `MAX_DATA_BUFFER_SIZE` | `256`   | Total number of words             |

---

## 🔁 Data Flow

1. **Initialization**
   - Configures FIFO hardware via `XLlFifo_CfgInitialize`
   - Clears interrupts and checks reset status

2. **Transmission**
   - Source buffer filled with incrementing pattern
   - Data streamed using `XLlFifo_TxPutWord`
   - Transmission begins with `XLlFifo_iTxSetLen`

3. **Reception**
   - Data occupancy checked using `XLlFifo_iRxOccupancy`
   - FIFO read via `XLlFifo_RxGetWord`
   - Reception verified using `XLlFifo_IsRxDone`

4. **Verification**
   - Source and received buffers compared for mismatch
   - Returns `XST_SUCCESS` or `XST_FAILURE` accordingly

---

## 🧪 How to Run

1. Synthesize and implement your design with the AXI FIFO IP integrated.
2. Build the application in **Vitis** or using cross-compilation tools.
3. Load and run the ELF binary on ZCU104 via JTAG or SD boot.
4. Observe UART output for success/failure messages.

---

## 📚 Requirements

- Xilinx SDK or Vitis
- Vivado hardware project with AXI FIFO IP
- ZCU104 board (or compatible Zynq Ultrascale+ platform)
- UART terminal for output (e.g., PuTTY, Tera Term)

---