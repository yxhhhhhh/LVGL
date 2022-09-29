CROSS_COMPILE ?= arm-linux-gnueabihf-
GCC   ?= $(CROSS_COMPILE)gcc
GXX   ?= $(CROSS_COMPILE)g++
STRIP ?= $(CROSS_COMPILE)strip

LVGL_DIR   = $(shell pwd)/../

C_INCLUDES := -I$(LVGL_DIR)

PROGS = liblinux.a

OMX_COMP_C_SRCS=$(wildcard ./*.c)
OMX_COMP_C_SRCS_NO_DIR=$(notdir $(OMX_COMP_C_SRCS))
OBJECTS=$(patsubst %.c, %.c.o, $(OMX_COMP_C_SRCS_NO_DIR))

OMX_COMP_CPP_SRCS=$(wildcard ./*.cpp)
OMX_COMP_CPP_SRCS_NO_DIR=$(notdir $(OMX_COMP_CPP_SRCS))
CXXOBJS=$(patsubst %.cpp, %.cpp.o, $(OMX_COMP_CPP_SRCS_NO_DIR))

OBJDIR ?= $(shell pwd)/obj
LIBDIR ?= $(shell pwd)/lib

OBJPROG = $(addprefix $(OBJDIR)/, $(PROGS))


.PHONY: clean prepare PROGS

all: prepare $(OBJPROG)

prepare:

clean:
	@rm -Rf $(OBJDIR)
	@rm -Rf $(LIBDIR)

$(OBJPROG): $(addprefix $(OBJDIR)/, $(OBJECTS)) $(addprefix $(OBJDIR)/, $(CXXOBJS))
	@mkdir -p $(LIBDIR)
	@echo "  LIBDIR $@"
	@$(AR) rcs $@ $(OBJDIR)/*.o
	@echo ""
	mv -f $(OBJDIR)/$(PROGS) $(LIBDIR)

$(OBJDIR)/%.c.o : %.c
	@mkdir -p obj
	@echo "  CC  $<"
	$(GCC) $(C_FLAGS) $(C_INCLUDES) -c $< -o $@

$(OBJDIR)/%.cpp.o : %.cpp
	@mkdir -p obj
	@echo "  CC  $<"
	@$(GXX) $(C_FLAGS) -std=c++11 $(C_INCLUDES) -c $< -o $@
