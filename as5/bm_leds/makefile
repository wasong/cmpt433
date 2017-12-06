#
# Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
#
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#    Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the
#    distribution.
#
#    Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#
#******************************************************************************

#
# Locating the root directory
#
# (Unable to use ~; spell out full path or use HOME)
ROOT=${HOME}/cmpt433/AM335X_StarterWare/

# Path to compiler
LIB_PATH=${HOME}/cmpt433/linaro-gcc/gcc-arm-none-eabi-4_7-2012q4
export LIB_PATH

#
# Device and EVM definitions
#
DEVICE=am335x
EVM=beaglebone

#
# Include the makefile definitions. This contains compiler, linker and
# archiver definitions and options
#
include ${ROOT}/build/armv7a/gcc/makedefs

#
# Target Directories that need to be built
#
DIRS=${DRIVERS_BLD} ${PLATFORM_BLD} ${SYSCONFIG_BLD} ${UTILITY_BLD}

#
# The application name
#
APPNAME=bm_leds

#
# Where the application will be loaded to. This is required to generate
# image with Header (Load Address and Size)
#
IMG_LOAD_ADDR = 0x80000000

#
# Application Location
#
APP=./
DEPLOY=~/cmpt433/public/baremetal/

#
# Application source files
#
APP_SRC=$(APP)/*.c

#
# Required library files
#
APP_LIB=-ldrivers  \
	-lutils    \
	-lplatform \
	-lsystem_config

CFLAGS+=-std=c99 -Wall -Werror
#
# Rules for building the application and library
#
# Clean first because otherwise every other build fails.
# (some problem with files in the build directory).
#all: debug release
all: clean debug
#all: release

debug:
	make TARGET_MODE=debug lib
	make TARGET_MODE=Debug bin

release:
	make TARGET_MODE=release lib
	make TARGET_MODE=Release bin

lib:
	@for i in ${DIRS};				\
	do						\
		if [ -f $${i}/makefile ] ;		    \
		then					  \
			make $(TARGET_MODE) -C $${i} || exit $$?; \
		fi;					   \
	done;


bin:
	$(CC)  $(CFLAGS) $(APP_SRC)
	@mkdir -p $(TARGET_MODE)/
	@mv *.o* $(TARGET_MODE)/
	$(LD) ${LDFLAGS} ${LPATH} -o $(TARGET_MODE)/$(APPNAME).out \
          -Map $(TARGET_MODE)/$(APPNAME).map $(TARGET_MODE)/*.o* \
          $(APP_LIB) -lc -lgcc $(APP_LIB) $(RUNTIMELIB) -T load_script.lds
	$(BIN) $(BINFLAGS) $(TARGET_MODE)/$(APPNAME).out \
               $(TARGET_MODE)/$(APPNAME).bin
	cd $(ROOT)/tools/ti_image/; gcc tiimage.c -o a.out; cd -
	       $(ROOT)/tools/ti_image/a.out $(IMG_LOAD_ADDR) NONE \
               $(TARGET_MODE)/$(APPNAME).bin \
               $(TARGET_MODE)/$(APPNAME)_ti.bin; rm -rf $(ROOT)/tools/ti_image/a.out;
	cp $(TARGET_MODE)/$(APPNAME).bin $(DEPLOY)/$(APPNAME).bin

#
# Rules for cleaning
#
clean:
	@rm -rf Debug Release $(DEPLOY)/$(APPNAME).bin

clean+: clean
	@make TARGET_MODE=clean lib
