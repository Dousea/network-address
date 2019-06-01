## User-specific settings
CC       := gcc
STD      := c99

## Makefile
NAME   := netaddr
CONFIG ?= debug

OBJDIR = obj
OUTDIR = out

CFLAGS  := -std=$(STD) -Wall -Wextra

ifeq ($(CONFIG),debug)
	CFLAGS += -O0 -g
else ifeq ($(CONFIG),release)
	CFLAGS += -O3
endif

LDLIBS  :=
LDFLAGS :=

SRCH := $(wildcard src/*.h)
SRCC := $(wildcard src/*.c)
SRCO := $(addprefix $(OBJDIR)/$(CONFIG)/, $(notdir $(SRCC:.c=.o)))
SRCT := $(OUTDIR)/$(NAME)

ALLO := $(SRCO)
ALLT := $(SRCT)

default: $(ALLT)

echo:
	@echo "CC=$(CC)"
	@echo "STD=$(STD)"
	@echo "CFLAGS=$(CFLAGS)"
	@echo "LDLIBS=$(LDLIBS)"
	@echo "LDFLAGS=$(LDFLAGS)"
	@echo "NAME=$(NAME)"
	@echo "CONFIG=$(CONFIG)"

clean:
	$(RM) $(ALLO) $(ALLT)
	$(RM) -r $(OBJDIR) $(OUTDIR)

# Create an executable
$(SRCT): $(SRCO) | $(OUTDIR)/
	$(CC) -o $@ $^ $(LDFLAGS) -lm $(LDLIBS)

# Create objects for the executable
$(OBJDIR)/$(CONFIG)/%.o: src/%.c $(SRCH) | $(OBJDIR)/$(CONFIG)/
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTDIR)/:
	mkdir -p $@

$(OBJDIR)/$(CONFIG)/:
	mkdir -p $@

.PHONY: clean