# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "")
  file(REMOVE_RECURSE
  "C:\\Users\\yrosh\\Documents\\real-fifo\\xsa-2107\\platform\\psu_cortexa53_0\\standalone_psu_cortexa53_0\\bsp\\include\\sleep.h"
  "C:\\Users\\yrosh\\Documents\\real-fifo\\xsa-2107\\platform\\psu_cortexa53_0\\standalone_psu_cortexa53_0\\bsp\\include\\xiltimer.h"
  "C:\\Users\\yrosh\\Documents\\real-fifo\\xsa-2107\\platform\\psu_cortexa53_0\\standalone_psu_cortexa53_0\\bsp\\include\\xtimer_config.h"
  "C:\\Users\\yrosh\\Documents\\real-fifo\\xsa-2107\\platform\\psu_cortexa53_0\\standalone_psu_cortexa53_0\\bsp\\lib\\libxiltimer.a"
  )
endif()
