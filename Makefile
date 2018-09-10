# checkfs - Checks the filesystem of an image
# Copyright (C) 2018  Bruno Mondelo

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

.PHONY: all clean dist testdrivers

AUXFILES := Makefile README.md LICENSE
PROJDIRS := src include

SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.c")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.h")
BINFILES := checkfs

OBJFILES := $(patsubst %.c,%.o,$(SRCFILES))
TSTFILES := $(patsubst %.c,%_t,$(SRCFILES))

DEPFILES := $(patsubst %.c,%.d,$(SRCFILES))
TSTDEPFILES := $(patsubst %,%.d,$(TSTFILES))

ALLFILES := $(AUXFILES) $(SRCFILES) $(HDRFILES)

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wconversion -Wstrict-prototypes -Werror
CFLAGS := -std=c99 $(WARNINGS)

all: $(BINFILES)

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(TSTFILES) $(BINFILES) checkfs.tar.gz)

dist:
	@tar czf checkfs.tar.gz $(ALLFILES)

testdrivers: $(TSTFILES)

-include $(DEPFILES) $(TSTDEPFILES)

%.o: %.c Makefile
	@$(CC) $(CFLAGS) -Iinclude -MMD -MP -c $< -o $@

%_t: %.c
	@$(CC) $(CFLAGS) -Iinclude -DTEST $< -o $@

checkfs: $(OBJFILES)
	@$(CC) $(CFLAGS) -Iinclude $^ -o $@
