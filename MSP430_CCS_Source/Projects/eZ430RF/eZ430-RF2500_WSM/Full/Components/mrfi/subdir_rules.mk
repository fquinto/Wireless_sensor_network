################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Components/mrfi/mrfi.obj: C:/Datos/Proyecto/workspace/CCS_Source/Components/mrfi/mrfi.c $(GEN_OPTS) $(GEN_SRCS) $(CFG_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Archivos de programa/Texas Instruments/ccsv4/tools/compiler/msp430/bin/cl430" --cmd_file="C:/Datos/Proyecto/workspace/CCS_Source/Projects/eZ430RF/eZ430-RF2500_WSM/../../Applications/Configuration/smpl_nwk_config.dat" --cmd_file="C:/Datos/Proyecto/workspace/CCS_Source/Projects/eZ430RF/eZ430-RF2500_WSM/../../Applications/Configuration/smpl_config.dat"  --silicon_version=msp -g --define=__MSP430F2274__ --define=MRFI_CC2500 --include_path="C:/Archivos de programa/Texas Instruments/ccsv4/msp430/include" --include_path="C:/Archivos de programa/Texas Instruments/ccsv4/tools/compiler/msp430/include" --include_path="C:/Archivos de programa/Texas Instruments/ccsv4/msp430/include" --include_path="C:/Datos/Proyecto/workspace/CCS_Source/Projects/eZ430RF/eZ430-RF2500_WSM/../../../Components/bsp" --include_path="C:/Datos/Proyecto/workspace/CCS_Source/Projects/eZ430RF/eZ430-RF2500_WSM/../../../Components/bsp/boards/EZ430RF" --include_path="C:/Datos/Proyecto/workspace/CCS_Source/Projects/eZ430RF/eZ430-RF2500_WSM/../../../Components/bsp/drivers" --include_path="C:/Datos/Proyecto/workspace/CCS_Source/Projects/eZ430RF/eZ430-RF2500_WSM/../../../Components/mrfi" --include_path="C:/Datos/Proyecto/workspace/CCS_Source/Projects/eZ430RF/eZ430-RF2500_WSM/../../../Components/simpliciti/nwk" --include_path="C:/Datos/Proyecto/workspace/CCS_Source/Projects/eZ430RF/eZ430-RF2500_WSM/../../../Components/simpliciti/nwk_applications" --diag_warning=225 --printf_support=minimal --preproc_with_compile --preproc_dependency="Components/mrfi/mrfi.pp" --obj_directory="Components/mrfi" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


