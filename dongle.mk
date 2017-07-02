##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=dongle
ConfigurationName      :=Debug
WorkspacePath          :=/Users/sergey/projects/teletram/dongle_fw
ProjectPath            :=/Users/sergey/projects/teletram/dongle_fw
IntermediateDirectory  :=./debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Sergey Sanders
Date                   :=02/07/2017
CodeLitePath           :="/Users/sergey/Library/Application Support/codelite"
LinkerName             :=/opt/arm-none-eabi/bin/arm-none-eabi-gcc
SharedObjectLinkerName :=/opt/arm-none-eabi/bin/arm-none-eabi-g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)DEBUG_EFM=1 $(PreprocessorSwitch)EFM32HG308F32=1 $(PreprocessorSwitch)DEBUG=1 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="dongle.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -T "m0.ld" -Xlinker --gc-sections --specs=nano.specs -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)device $(IncludeSwitch)cmsis $(IncludeSwitch)usb $(IncludeSwitch)emlib $(IncludeSwitch)kernel 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /opt/arm-none-eabi/bin/arm-none-eabi-ar rcu
CXX      := /opt/arm-none-eabi/bin/arm-none-eabi-g++
CC       := /opt/arm-none-eabi/bin/arm-none-eabi-gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -gdwarf-2 -mcpu=cortex-m0plus -mthumb -std=c99 -c -fmessage-length=0 -mno-sched-prolog -fno-builtin -ffunction-sections -fdata-sections -MMD -MP $(Preprocessors)
ASFLAGS  := -g -gdwarf-2 -mcpu=cortex-m0plus -mthumb -c -x assembler-with-cpp
AS       := /opt/arm-none-eabi/bin/arm-none-eabi-gcc


##
## User defined environment variables
##
CodeLiteDir:=/Applications/codelite.app/Contents/SharedSupport/
PATH:=/usr/local/bin/:$PATH
Objects0=$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IntermediateDirectory)/startup_efm32hg.c$(ObjectSuffix) $(IntermediateDirectory)/system_efm32hg.c$(ObjectSuffix) $(IntermediateDirectory)/parser.c$(ObjectSuffix) $(IntermediateDirectory)/dcc_drv.c$(ObjectSuffix) $(IntermediateDirectory)/dcc.c$(ObjectSuffix) $(IntermediateDirectory)/rx_drv.c$(ObjectSuffix) $(IntermediateDirectory)/usb_descriptors.c$(ObjectSuffix) $(IntermediateDirectory)/usb_em_usbd.c$(ObjectSuffix) $(IntermediateDirectory)/usb_em_usbdch9.c$(ObjectSuffix) \
	$(IntermediateDirectory)/usb_em_usbdep.c$(ObjectSuffix) $(IntermediateDirectory)/usb_em_usbdint.c$(ObjectSuffix) $(IntermediateDirectory)/usb_em_usbhal.c$(ObjectSuffix) $(IntermediateDirectory)/usb_cdc.c$(ObjectSuffix) $(IntermediateDirectory)/emlib_em_assert.c$(ObjectSuffix) $(IntermediateDirectory)/emlib_em_cmu.c$(ObjectSuffix) $(IntermediateDirectory)/emlib_em_core.c$(ObjectSuffix) $(IntermediateDirectory)/emlib_em_emu.c$(ObjectSuffix) $(IntermediateDirectory)/emlib_em_system.c$(ObjectSuffix) $(IntermediateDirectory)/kernel_heap_2.c$(ObjectSuffix) \
	$(IntermediateDirectory)/kernel_list.c$(ObjectSuffix) $(IntermediateDirectory)/kernel_port.c$(ObjectSuffix) $(IntermediateDirectory)/kernel_queue.c$(ObjectSuffix) $(IntermediateDirectory)/kernel_tasks.c$(ObjectSuffix) $(IntermediateDirectory)/kernel_timers.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

PostBuild:
	@echo Executing Post Build commands ...
	/opt/arm-none-eabi/bin/arm-none-eabi-size ./debug/dongle
	/opt/arm-none-eabi/bin/arm-none-eabi-objcopy -O binary ./debug/dongle ./debug/dongle.bin
	@echo Done

MakeIntermediateDirs:
	@test -d ./debug || $(MakeDirCommand) ./debug


$(IntermediateDirectory)/.d:
	@test -d ./debug || $(MakeDirCommand) ./debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.c$(ObjectSuffix): main.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/main.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.c$(PreprocessSuffix): main.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.c$(PreprocessSuffix) main.c

$(IntermediateDirectory)/startup_efm32hg.c$(ObjectSuffix): startup_efm32hg.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/startup_efm32hg.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/startup_efm32hg.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/startup_efm32hg.c$(PreprocessSuffix): startup_efm32hg.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/startup_efm32hg.c$(PreprocessSuffix) startup_efm32hg.c

$(IntermediateDirectory)/system_efm32hg.c$(ObjectSuffix): system_efm32hg.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/system_efm32hg.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/system_efm32hg.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/system_efm32hg.c$(PreprocessSuffix): system_efm32hg.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/system_efm32hg.c$(PreprocessSuffix) system_efm32hg.c

$(IntermediateDirectory)/parser.c$(ObjectSuffix): parser.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/parser.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/parser.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/parser.c$(PreprocessSuffix): parser.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/parser.c$(PreprocessSuffix) parser.c

$(IntermediateDirectory)/dcc_drv.c$(ObjectSuffix): dcc_drv.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/dcc_drv.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dcc_drv.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dcc_drv.c$(PreprocessSuffix): dcc_drv.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dcc_drv.c$(PreprocessSuffix) dcc_drv.c

$(IntermediateDirectory)/dcc.c$(ObjectSuffix): dcc.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/dcc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/dcc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/dcc.c$(PreprocessSuffix): dcc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/dcc.c$(PreprocessSuffix) dcc.c

$(IntermediateDirectory)/rx_drv.c$(ObjectSuffix): rx_drv.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/rx_drv.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/rx_drv.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/rx_drv.c$(PreprocessSuffix): rx_drv.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/rx_drv.c$(PreprocessSuffix) rx_drv.c

$(IntermediateDirectory)/usb_descriptors.c$(ObjectSuffix): usb/descriptors.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/usb/descriptors.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/usb_descriptors.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/usb_descriptors.c$(PreprocessSuffix): usb/descriptors.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/usb_descriptors.c$(PreprocessSuffix) usb/descriptors.c

$(IntermediateDirectory)/usb_em_usbd.c$(ObjectSuffix): usb/em_usbd.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/usb/em_usbd.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/usb_em_usbd.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/usb_em_usbd.c$(PreprocessSuffix): usb/em_usbd.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/usb_em_usbd.c$(PreprocessSuffix) usb/em_usbd.c

$(IntermediateDirectory)/usb_em_usbdch9.c$(ObjectSuffix): usb/em_usbdch9.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/usb/em_usbdch9.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/usb_em_usbdch9.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/usb_em_usbdch9.c$(PreprocessSuffix): usb/em_usbdch9.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/usb_em_usbdch9.c$(PreprocessSuffix) usb/em_usbdch9.c

$(IntermediateDirectory)/usb_em_usbdep.c$(ObjectSuffix): usb/em_usbdep.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/usb/em_usbdep.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/usb_em_usbdep.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/usb_em_usbdep.c$(PreprocessSuffix): usb/em_usbdep.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/usb_em_usbdep.c$(PreprocessSuffix) usb/em_usbdep.c

$(IntermediateDirectory)/usb_em_usbdint.c$(ObjectSuffix): usb/em_usbdint.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/usb/em_usbdint.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/usb_em_usbdint.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/usb_em_usbdint.c$(PreprocessSuffix): usb/em_usbdint.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/usb_em_usbdint.c$(PreprocessSuffix) usb/em_usbdint.c

$(IntermediateDirectory)/usb_em_usbhal.c$(ObjectSuffix): usb/em_usbhal.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/usb/em_usbhal.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/usb_em_usbhal.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/usb_em_usbhal.c$(PreprocessSuffix): usb/em_usbhal.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/usb_em_usbhal.c$(PreprocessSuffix) usb/em_usbhal.c

$(IntermediateDirectory)/usb_cdc.c$(ObjectSuffix): usb/cdc.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/usb/cdc.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/usb_cdc.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/usb_cdc.c$(PreprocessSuffix): usb/cdc.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/usb_cdc.c$(PreprocessSuffix) usb/cdc.c

$(IntermediateDirectory)/emlib_em_assert.c$(ObjectSuffix): emlib/em_assert.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/emlib/em_assert.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/emlib_em_assert.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/emlib_em_assert.c$(PreprocessSuffix): emlib/em_assert.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/emlib_em_assert.c$(PreprocessSuffix) emlib/em_assert.c

$(IntermediateDirectory)/emlib_em_cmu.c$(ObjectSuffix): emlib/em_cmu.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/emlib/em_cmu.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/emlib_em_cmu.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/emlib_em_cmu.c$(PreprocessSuffix): emlib/em_cmu.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/emlib_em_cmu.c$(PreprocessSuffix) emlib/em_cmu.c

$(IntermediateDirectory)/emlib_em_core.c$(ObjectSuffix): emlib/em_core.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/emlib/em_core.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/emlib_em_core.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/emlib_em_core.c$(PreprocessSuffix): emlib/em_core.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/emlib_em_core.c$(PreprocessSuffix) emlib/em_core.c

$(IntermediateDirectory)/emlib_em_emu.c$(ObjectSuffix): emlib/em_emu.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/emlib/em_emu.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/emlib_em_emu.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/emlib_em_emu.c$(PreprocessSuffix): emlib/em_emu.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/emlib_em_emu.c$(PreprocessSuffix) emlib/em_emu.c

$(IntermediateDirectory)/emlib_em_system.c$(ObjectSuffix): emlib/em_system.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/emlib/em_system.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/emlib_em_system.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/emlib_em_system.c$(PreprocessSuffix): emlib/em_system.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/emlib_em_system.c$(PreprocessSuffix) emlib/em_system.c

$(IntermediateDirectory)/kernel_heap_2.c$(ObjectSuffix): kernel/heap_2.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/kernel/heap_2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/kernel_heap_2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/kernel_heap_2.c$(PreprocessSuffix): kernel/heap_2.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/kernel_heap_2.c$(PreprocessSuffix) kernel/heap_2.c

$(IntermediateDirectory)/kernel_list.c$(ObjectSuffix): kernel/list.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/kernel/list.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/kernel_list.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/kernel_list.c$(PreprocessSuffix): kernel/list.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/kernel_list.c$(PreprocessSuffix) kernel/list.c

$(IntermediateDirectory)/kernel_port.c$(ObjectSuffix): kernel/port.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/kernel/port.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/kernel_port.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/kernel_port.c$(PreprocessSuffix): kernel/port.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/kernel_port.c$(PreprocessSuffix) kernel/port.c

$(IntermediateDirectory)/kernel_queue.c$(ObjectSuffix): kernel/queue.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/kernel/queue.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/kernel_queue.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/kernel_queue.c$(PreprocessSuffix): kernel/queue.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/kernel_queue.c$(PreprocessSuffix) kernel/queue.c

$(IntermediateDirectory)/kernel_tasks.c$(ObjectSuffix): kernel/tasks.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/kernel/tasks.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/kernel_tasks.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/kernel_tasks.c$(PreprocessSuffix): kernel/tasks.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/kernel_tasks.c$(PreprocessSuffix) kernel/tasks.c

$(IntermediateDirectory)/kernel_timers.c$(ObjectSuffix): kernel/timers.c 
	$(CC) $(SourceSwitch) "/Users/sergey/projects/teletram/dongle_fw/kernel/timers.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/kernel_timers.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/kernel_timers.c$(PreprocessSuffix): kernel/timers.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/kernel_timers.c$(PreprocessSuffix) kernel/timers.c

##
## Clean
##
clean:
	$(RM) -r ./debug/


