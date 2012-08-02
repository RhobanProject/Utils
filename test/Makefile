BASE=../..
SRC = 
SRCPP = 

EXE = test-state-machine test-timed-thread


LIBS += $(LIB_RHOBAN) $(LIB_RHOBAN_MATH)
LIBFILES += $(RHOBAN_LIB_FILE) $(RHOBAN_MATH_LIB_FILE) 


include $(BASE)/Makefile.param
include $(BASE)/Makefile.modules
include $(BASE)/Makefile.generic

#hugo: what for? because of this line target 'clean' is building dependency files -include $(DEPS)

$(BINDIR)/test-state-machine: $(UTILS_OBJ) $(BUILDDIR)/test-state-machine.o $(BUILDDIR) 
	$(CC) -o $(BINDIR)/test-state-machine -DMACHINE_THREAD $(LDFLAGS) $(BUILDDIR)/test-state-machine.o $(LIB_RHOBAN)
