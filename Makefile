##
## Makefile for show_text_input in /data/Documents/3ds
## 
## Made by Loïc Pirez
## Login   <loic.pirez@epitech.eu>
## 
## Started on  Wed Apr 22 22:24:25 2015 Loïc Pirez
## Last update Sat Apr 25 15:47:35 2015 Loïc Pirez
##

# /!\ Warning /!\
# I'm not responsable in any damage of your device!
# You should not change much things in this Makefile except basic things (title, description, etc.)
# This Makefile is quite unreadeable and complex. You've be warned.

#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

MYDIR 		:=	$(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
OUT_DIR		=	$(MYDIR)/out/
PRJ_NAME	=	$(shell basename $(MYDIR))
TOOL_DIR	=	$(MYDIR)tool
TOPDIR		=	$(CURDIR)

include $(DEVKITARM)/3ds_rules

TARGET		:=	$(notdir $(CURDIR))
BUILD		:=	build
SOURCES		:=	src
DATA		:=	data
INCLUDES	:=	include
APP_TITLE       :=	image
APP_DESCRIPTION :=	Simple app which react to key press.
APP_AUTHOR      :=	pirez_l
ICON            :=	logo.png

ARCH		:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard
CFLAGS		:=	-g -Wall -O3 -mword-relocations -fomit-frame-pointer -ffast-math $(ARCH)
CFLAGS		+=	$(INCLUDE) -DARM11 -D_3DS
#If you're crazy, uncomment below.
#CFLAGS		+=	-funroll-loops -fomg-optimize
CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11
ASFLAGS		:=	-g $(ARCH)
LDFLAGS		=	-specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)
LIBS		:= 	-lctru -lm

LIBDIRS	:= $(CTRULIB)

ifneq ($(BUILD),$(notdir $(CURDIR)))

export OUTPUT	:=	$(CURDIR)/$(TARGET)
export TOPDIR	:=	$(CURDIR)
export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))
export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

ifeq ($(strip $(CPPFILES)),)
	export LD	:=	$(CC)
else
	export LD	:=	$(CXX)
endif

export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
			$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)
export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)
export LIBPATHS	:=	$(foreach dir,$(LIBDIRS),-L$(dir)/lib)

ifeq ($(strip $(ICON)),)
	icons := $(wildcard *.png)
	ifneq (,$(findstring $(TARGET).png,$(icons)))
		export APP_ICON := $(TOPDIR)/$(TARGET).png
	else
		ifneq (,$(findstring icon.png,$(icons)))
			export APP_ICON := $(TOPDIR)/icon.png
		endif
	endif
else
	export APP_ICON := $(TOPDIR)/$(ICON)
endif

.PHONY: $(BUILD) clean fclean re all

all: $(BUILD)
$(BUILD):
	@[ -d $@ ] || mkdir -p $@
	@make --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile
clean:
	@rm -rf $(BUILD) $(TARGET).3dsx $(OUTPUT).smdh $(OUTPUT).3ds $(TARGET).elf
fclean: clean
	@rm -rf out/*
re:	fclean all

else
DEPENDS	:=	$(OFILES:.o=.d)

ifeq ($(strip $(NO_SMDH)),) #Work here
.PHONY: all
all	:	$(OUTPUT).3dsx $(OUTPUT).smdh
		mv $(MYDIR)/$(PRJ_NAME).3dsx $(MYDIR)/$(PRJ_NAME).smdh $(MYDIR)/$(PRJ_NAME).elf $(OUT_DIR)
		3dbuild $(OUT_DIR)$(PRJ_NAME).elf $(OUT_DIR)$(PRJ_NAME)
endif

$(OUTPUT).3dsx	:	$(OUTPUT).elf
$(OUTPUT).elf	:	$(OFILES)

%.bin.o		:	%.bin
		@echo $(notdir $<)
		@$(bin2o)

# It's ugly, but not my fault
%.vsh.o	:	%.vsh
	@echo $(notdir $<)
	@python $(AEMSTRO)/aemstro_as.py $< ../$(notdir $<).shbin
	@bin2s ../$(notdir $<).shbin | $(PREFIX)as -o $@
	@echo "extern const u8" `(echo $(notdir $<).shbin | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"_end[];" > `(echo $(notdir $<).shbin | tr . _)`.h
	@echo "extern const u8" `(echo $(notdir $<).shbin | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" >> `(echo $(notdir $<).shbin | tr . _)`.h
	@echo "extern const u32" `(echo $(notdir $<).shbin | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(notdir $<).shbin | tr . _)`.h
	@rm ../$(notdir $<).shbin

-include $(DEPENDS)
endif
