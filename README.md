# AXI4-Stream FIFO Loopback Validation on ZCU104

## 🧠 Overview
This project validates an AXI4-Stream-based FIFO communication pipeline using the ARM Cortex-A53 on the Zynq UltraScale+ ZCU104 platform. It showcases end-to-end packet transfer between the Processing System (PS) and Programmable Logic (PL) through an AXI FIFO MM IP core, with optional buffering via a FIFO Generator IP. Data is transmitted from the PS, looped through the PL streaming path, and received back on the PS — enabling thorough verification of AXI stream handshakes and data integrity.

## ⚙️ Block Design Highlights

- **PS ↔ AXI FIFO MM ↔ FIFO Generator ↔ AXI FIFO MM ↔ PS**
- Common `pl_clk0` and `resetn` domain for unified timing
- Round-trip stream loop established using:
  - `M_AXIS_TX → FIFO Generator → M_AXIS → S_AXIS_RX`

## 🧪 Testing Workflow

1. **Vivado Block Design**
   - Export hardware with bitstream (`.xsa`) after synthesis + implementation
2. **Vitis Application**
   - Standalone C application using `XLlFifo` driver
   - Performs:
     - Incremental pattern generation
     - MMIO-based FIFO TX
     - FIFO RX polling
     - Data comparison to verify stream integrity

3. **UART Console Output**
   ```text
   --- Entering main() ---
   Transmitting Data ...
   Receiving data ....
   Comparing data ...
   Successfully ran Axi Streaming FIFO Polling Example
   --- Exiting main() ---

## 📄 Key Files
| File/Folder                     | Type            | Description                                                                 |
|----------------------------------|------------------|-----------------------------------------------------------------------------|
| `_ide/`                         | IDE Config       | Auto-generated files for Vitis Unified IDE workspace                        |
| `platform/`                     | BSP & Platform   | Exported Board Support Package, includes PS configuration and drivers       |
| `xllfifo_polling_example/`     | Application Code | Standalone C app for AXI FIFO MM round-trip test                           |
| `2107-bitstream.bit`           | Bitstream        | Synthesized FPGA bitstream from Vivado for ZCU104                          |
| `fifo_test_wrapper.xsa`        | Hardware Export  | Hardware handoff including bitstream and hardware spec for Vitis integration |
| `.gitignore`                   | Metadata         | Git rules to exclude build artifacts and temporary files                    |

## 🛠️ Customization
- Modify SourceBuffer in TxSend() to change the test pattern:
*(SourceAddr + i) = 0x10000000 | (i & 0xFF);
- Add optional ILA trigger conditions (e.g., tvalid == 1) for visual debugging
- Expand stream packet structure with headers, flags, or timestamps

## 🧾 Dependencies
- Vivado 2025.1
- Vitis 2025.1
- ZCU104 board with JTAG & UART interface
- Drivers: xil, xiltimer, xilstandalone, xllfifo

## ✨ Credits
Developed by Roshan Yadav, PRA at IIT Bombay’s aiCAS Lab.

## 🧩 License
MIT License — feel free to adapt, extend, and fork this for your own embedded projects.
