BASE=..
include Makefile.sources
SRCPP = $(UTILS_SRC)
SUBDIRS = $(UTILS_SUBDIRS)

include $(BASE)/Makefile.param
include $(BASE)/Makefile.generic

