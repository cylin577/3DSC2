# Simple Makefile for 3DS Homebrew

TARGET		:=	3dsc2_calib
BUILD		:=	build
SOURCES		:=	source

#---------------------------------------------------------------------------------
# Options for code generation
#---------------------------------------------------------------------------------
ARCH		:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

CFLAGS	:=	-g -Wall -O2 -mword-relocations \
			-ffunction-sections \
			$(ARCH)

CFLAGS	+=	$(INCLUDE) -D__3DS__

CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11

ASFLAGS		:= 	-g $(ARCH)
LDFLAGS	= 	-specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map) 

LIBS		:= -lctru -lm

#---------------------------------------------------------------------------------
# path to tools - assuming /opt/devkitpro if not set
#---------------------------------------------------------------------------------
export DEVKITPRO ?= /opt/devkitpro
export DEVKITARM ?= $(DEVKITPRO)/devkitARM

include $(DEVKITARM)/3ds_rules

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS		:= $(CTRULIB)

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT		:= 	$(CURDIR)/$(TARGET)
export TOPDIR		:= 	$(CURDIR)

export VPATH		:= 	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir))
export DEPSDIR	:= 	$(CURDIR)/$(BUILD)

CFILES		:= 	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:= 	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:= 	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:= 	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.bin)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for pure C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
	export LD		:= 	$(CC)
else
	export LD		:= 	$(CXX)
endif

export OFILES	:= 	$(addsuffix .o,$(BINFILES)) \
				$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE	:= 	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
				$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
				-I$(CURDIR)/$(BUILD)

export LIBPATHS	:= 	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------
all: $(BUILD)

$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -fr $(BUILD) $(TARGET).3dsx $(TARGET).elf

else

$(OUTPUT).3dsx		: 	$(OUTPUT).elf

$(OUTPUT).elf		: 	$(OFILES)

%.bin.o		: 	%.bin
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
# rules for assembling GPU shaders
#---------------------------------------------------------------------------------
define shader-as
	$(eval CURBIN := $(patsubst %.shbin.o,%.shbin,$(notdir $@)))
	picasso -o $(CURBIN) $1
	bin2s $(CURBIN) | $(AS) -o $@
	echo "extern const u8" `(echo $(CURBIN) | sed -e 's/^\]([0-9])/_\]1/' | tr . _)`"_end[];" > `(echo $(CURBIN) | tr . _)`".h"
	echo "extern const u8" `(echo $(CURBIN) | sed -e 's/^\]([0-9])/_\]1/' | tr . _)`"[];" >> `(echo $(CURBIN) | tr . _)`".h"
	echo "extern const u32" `(echo $(CURBIN) | sed -e 's/^\]([0-9])/_\]1/' | tr . _)`"_size";" >> `(echo $(CURBIN) | tr . _)`".h"
endef

%.shbin.o : %.v.pica
	@echo $(notdir $<)
	@$(call shader-as,$<)

%.shbin.o : %.g.pica
	@echo $(notdir $<)
	@$(call shader-as,$<)

#---------------------------------------------------------------------------------

-include $(DEPSDIR)/*.d

endif
