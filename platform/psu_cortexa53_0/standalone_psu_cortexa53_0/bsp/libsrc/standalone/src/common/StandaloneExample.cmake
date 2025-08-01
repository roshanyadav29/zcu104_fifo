set(CORESIGHTPS_DCC_NUM_DRIVER_INSTANCES "psu_coresight_0")
set(CORESIGHTPS_DCC0_PROP_LIST "0xfe800000")
list(APPEND TOTAL_CORESIGHTPS_DCC_PROP_LIST CORESIGHTPS_DCC0_PROP_LIST)
set(IOMODULE_NUM_DRIVER_INSTANCES "")
set(UARTLITE_NUM_DRIVER_INSTANCES "")
set(UARTNS550_NUM_DRIVER_INSTANCES "")
set(UARTPS_NUM_DRIVER_INSTANCES "psu_uart_0;psu_uart_1")
set(UARTPS0_PROP_LIST "0xff000000")
list(APPEND TOTAL_UARTPS_PROP_LIST UARTPS0_PROP_LIST)
set(UARTPS1_PROP_LIST "0xff010000")
list(APPEND TOTAL_UARTPS_PROP_LIST UARTPS1_PROP_LIST)
set(UARTPSV_NUM_DRIVER_INSTANCES "")
set(STDIN_INSTANCE "psu_uart_0")
set(NUMBER_OF_SLRS 0x1 CACHE STRING "Number of slrs")
set(DEVICE_ID "xczu7ev" CACHE STRING "Device Id")
set(SPEED_GRADE "2" CACHE STRING "Speed Grade")
set(BOARD "zcu104" CACHE STRING "BOARD")
set(XPAR_CPU_ID "0")
