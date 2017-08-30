LIBDIR := lib
SRCDIR := src
TESTDIR := test

OBJDIR := obj
DEPDIR := dep
BINDIR := bin

SOBJDIR := obj/src
SDEPDIR := dep/src
TOBJDIR := obj/test
TDEPDIR := dep/test
LOBJDIR := obj/lib
LDEPDIR := dep/lib

TESTEXEC := test.out
MAINEXEC := main.out

SRCS := $(shell find $(SRCDIR) -name "*.cpp")
SOBJS := $(SRCS:$(SRCDIR)/%.cpp=$(SOBJDIR)/%.o)
SDEPS := $(SRCS:$(SRCDIR)/%.cpp=$(SDEPDIR)/%.d)
STREE := $(patsubst %/,%,$(dir $(SOBJS)))

TESTS := $(shell find $(TESTDIR) -name "*.cpp")
TOBJS := $(TESTS:$(TESTDIR)/%.cpp=$(TOBJDIR)/%.o)
TDEPS := $(TESTS:$(TESTDIR)/%.cpp=$(TDEPDIR)/%.d)
TTREE := $(patsubst %/,%,$(dir $(TOBJS)))

LIBS := $(shell find $(LIBDIR) -name "*.cpp")
LOBJS := $(LIBS:$(LIBDIR)/%.cpp=$(LOBJDIR)/%.o)
LDEPS := $(LIBS:$(LIBDIR)/%.cpp=$(LDEPDIR)/%.d)
LTREE := $(patsubst %/,%,$(dir $(LOBJS)))

SCPPFLAGS  = -MMD -MP -MF $(@:$(SOBJDIR)/%.o=$(SDEPDIR)/%.d)
TCPPFLAGS  = -MMD -MP -MF $(@:$(TOBJDIR)/%.o=$(TDEPDIR)/%.d)
LCPPFLAGS  = -MMD -MP -MF $(@:$(LOBJDIR)/%.o=$(LDEPDIR)/%.d)

BCXXFLAGS = -I$(SRCDIR) -I$(TESTDIR) -I$(LIBDIR) -O3 -std=c++1z -stdlib=libc++
LINKERFLAGS = -stdlib=libc++ -pthread

all: CXXFLAGS = $(BCXXFLAGS) -D __main__
test: CXXFLAGS = $(BCXXFLAGS) -D __test__

.PHONY: all test clean

all: $(BINDIR)/$(MAINEXEC)

run: all
	@printf " --------------------------\n\n"
	@$(BINDIR)/$(MAINEXEC)

test: $(BINDIR)/$(TESTEXEC)
	$(BINDIR)/$(TESTEXEC)

clean:
	@$(RM) -r $(OBJDIR) $(DEPDIR) $(BINDIR)

.SECONDEXPANSION:
$(SOBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)
	$(CXX) $(SCPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(TOBJDIR)/%.o: $(TESTDIR)/%.cpp | $$(@D)
	$(CXX) $(TCPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(LOBJDIR)/%.o: $(LIBDIR)/%.cpp | $$(@D)
	$(CXX) $(LCPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(BINDIR):
	mkdir -p $(BINDIR)

$(STREE): %:
	mkdir -p $@
	mkdir -p $(@:$(SOBJDIR)%=$(SDEPDIR)%)

$(TTREE): %:
	mkdir -p $@
	mkdir -p $(@:$(TOBJDIR)%=$(TDEPDIR)%)

$(LTREE): %:
	mkdir -p $@
	mkdir -p $(@:$(LOBJDIR)%=$(LDEPDIR)%)

$(BINDIR)/$(TESTEXEC): $(SOBJS) $(TOBJS) $(LOBJS) $(BINDIR)
	$(CXX) $(LINKERFLAGS) -o $(BINDIR)/$(TESTEXEC) $(SOBJS) $(TOBJS) $(LOBJS)

$(BINDIR)/$(MAINEXEC): $(SOBJS) $(LOBJS) $(BINDIR)
	$(CXX) $(LINKERFLAGS) -o $(BINDIR)/$(MAINEXEC) $(SOBJS) $(LOBJS)
ifeq "$(MAKECMDGOALS)" ""
-include $(SDEPS)
-include $(TDEPS)
-include $(LDEPS)
endif
