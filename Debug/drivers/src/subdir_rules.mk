################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
drivers/src/%.obj: ../drivers/src/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.6.LTS/bin/cl430" -vmsp -O0 --opt_for_speed=0 --use_hw_mpy=none --include_path="C:/ti/ccsv8/ccs_base/msp430/include" --include_path="C:/Users/abema/Documents/workspace_ccs/afp" --include_path="C:/ti/ccsv8/tools/compiler/ti-cgt-msp430_18.1.6.LTS/include" --advice:power="all" --define=__MSP430G2433__ -g --c99 --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --preproc_with_compile --preproc_dependency="drivers/src/$(basename $(<F)).d_raw" --obj_directory="drivers/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


