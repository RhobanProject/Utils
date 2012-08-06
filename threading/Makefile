BASE=../..

include Makefile.sources
include $(BASE)/Makefile.param
include $(BASE)/Makefile.modules

SRCPP = $(UTILS_THREAD_EXE_SRC)

EXE = $(UTILS_THREAD_EXE)
LIBFILES += $(RHOBAN_LIB_FILE)
LIBS +=  $(LIB_RHOBAN)
ALL_OBJECTS_IN_LIBS = 1

ifeq ($(PLATFORM),win32)
LIBS +=	-lws2_32 -lpthread
endif

IS_TESTSDIR := 1

include $(BASE)/Makefile.generic
