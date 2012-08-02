BASE=../..
include Makefile.sources
include $(BASE)/Makefile.param
include $(BASE)/Makefile.modules

SRCPP = $(UTILS_TIMING_SRC)
EXE = $(UTILS_TIMING_EXE)

LIBFILES += $(RHOBAN_LIB_FILE)

ALL_OBJECTS_IN_LIBS = 1

ifeq ($(PLATFORM),win32)
LIBS +=	$(LIB_RHOBAN) -lrt -lpthread -lws2_32  
else
LIBS +=	$(LIB_RHOBAN) -lrt -pthread
endif

IS_TESTSDIR := 1

include $(BASE)/Makefile.generic

