################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := c:/ti/ccsv6/tools/compiler/arm_5.1.5

ORDERED_OBJS += \
$(GEN_CMDS__FLAG) \
"./include/wifi.obj" \
"./include/plun.obj" \
"./include/matt_pub.obj" \
"./include/inth.obj" \
"./include/base.obj" \
"./ustdlib.obj" \
"./uartstdio.obj" \
"./tm4c123gh6pm_startup_ccs.obj" \
"./main.obj" \
"./cc3000lib.obj" \
"../tm4c123gh6pm.cmd" \
-l"libc.a" \
-l"C:/ti/TivaWare_C_Series-2.1.0.12573/driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include include/subdir_vars.mk
-include subdir_rules.mk
-include include/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
plun_satellite_tm4c123.out \

EXE_OUTPUTS__QUOTED += \
"plun_satellite_tm4c123.out" \

BIN_OUTPUTS += \
plun_satellite_tm4c123.hex \

BIN_OUTPUTS__QUOTED += \
"plun_satellite_tm4c123.hex" \


# All Target
all: plun_satellite_tm4c123.out

# Tool invocations
plun_satellite_tm4c123.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Linker'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -Ooff -g --define=_POSIX_SOURCE --define=UART_BUFFERED --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --define=CC3000_TM4C123_SPI --define=ccs="ccs" --display_error_number --diag_warning=225 --diag_wrap=off -z -m"plun_satellite_tm4c123.map" --heap_size=0 --stack_size=512 -i"c:/ti/ccsv6/tools/compiler/arm_5.1.5/lib" -i"c:/ti/ccsv6/tools/compiler/arm_5.1.5/include" --reread_libs --warn_sections --display_error_number --diag_wrap=off --xml_link_info="plun_satellite_tm4c123_linkInfo.xml" --rom_model -o "plun_satellite_tm4c123.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

plun_satellite_tm4c123.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: ARM Hex Utility'
	"c:/ti/ccsv6/tools/compiler/arm_5.1.5/bin/armhex"  -o "plun_satellite_tm4c123.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "cc3000lib.pp" "main.pp" "tm4c123gh6pm_startup_ccs.pp" "uartstdio.pp" "ustdlib.pp" "include\base.pp" "include\inth.pp" "include\matt_pub.pp" "include\plun.pp" "include\wifi.pp" 
	-$(RM) "cc3000lib.obj" "main.obj" "tm4c123gh6pm_startup_ccs.obj" "uartstdio.obj" "ustdlib.obj" "include\base.obj" "include\inth.obj" "include\matt_pub.obj" "include\plun.obj" "include\wifi.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

