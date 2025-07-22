# 2025-07-21T13:33:11.392751400
import vitis

client = vitis.create_client()
client.set_workspace(path="xsa-2107")

advanced_options = client.create_advanced_options_dict(dt_overlay="0")

platform = client.create_platform_component(name = "platform",hw_design = "$COMPONENT_LOCATION/../fifo_test_wrapper.xsa",os = "standalone",cpu = "psu_cortexa53_0",domain_name = "standalone_psu_cortexa53_0",generate_dtb = False,advanced_options = advanced_options,architecture = "64-bit",compiler = "gcc")

platform = client.get_component(name="platform")
status = platform.build()

comp = client.create_app_component(name="fifo_app_component",platform = "$COMPONENT_LOCATION/../platform/export/platform/platform.xpfm",domain = "standalone_psu_cortexa53_0")

status = platform.build()

comp = client.get_component(name="fifo_app_component")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../fifo_test_wrapper.xsa")

status = platform.build()

comp.build()

status = platform.build()

comp = client.get_component(name="xllfifo_polling_example")
comp.build()

status = platform.build()

comp = client.get_component(name="fifo_app_component")
comp.build()

status = platform.build()

comp = client.get_component(name="xllfifo_polling_example")
comp.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

client.delete_component(name="fifo_app_component")

status = platform.update_hw(hw_design = "$COMPONENT_LOCATION/../fifo_test_wrapper.xsa")

status = platform.build()

status = platform.build()

comp.build()

status = platform.build()

comp.build()

