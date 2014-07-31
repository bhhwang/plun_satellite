################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
include/base.obj: ../include/base.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -Ooff --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/drivers/ek-tm4c123gxl" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/host_driver/core_driver" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/host_driver/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/spi" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/uart" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src" -g --define=_POSIX_SOURCE --define=UART_BUFFERED --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --define=CC3000_TM4C123_SPI --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="include/base.pp" --obj_directory="include" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/inth.obj: ../include/inth.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -Ooff --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/drivers/ek-tm4c123gxl" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/host_driver/core_driver" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/host_driver/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/spi" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/uart" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src" -g --define=_POSIX_SOURCE --define=UART_BUFFERED --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --define=CC3000_TM4C123_SPI --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="include/inth.pp" --obj_directory="include" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/matt_pub.obj: ../include/matt_pub.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -Ooff --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/drivers/ek-tm4c123gxl" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/host_driver/core_driver" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/host_driver/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/spi" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/uart" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src" -g --define=_POSIX_SOURCE --define=UART_BUFFERED --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --define=CC3000_TM4C123_SPI --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="include/matt_pub.pp" --obj_directory="include" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/plun.obj: ../include/plun.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -Ooff --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/drivers/ek-tm4c123gxl" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/host_driver/core_driver" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/host_driver/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/spi" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/uart" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src" -g --define=_POSIX_SOURCE --define=UART_BUFFERED --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --define=CC3000_TM4C123_SPI --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="include/plun.pp" --obj_directory="include" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

include/wifi.obj: ../include/wifi.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -Ooff --include_path="c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/drivers/ek-tm4c123gxl" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/host_driver/core_driver" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/host_driver/include" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/spi" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src/uart" --include_path="C:/ti/TivaWare_C_Series-2.1.0.12573/cc3000/src" -g --define=_POSIX_SOURCE --define=UART_BUFFERED --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --define=CC3000_TM4C123_SPI --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off --preproc_with_compile --preproc_dependency="include/wifi.pp" --obj_directory="include" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


