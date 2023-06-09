# -----------------------------------------------------------------------------
#
#                              M A K E F I L E
#
# zum Uebungsbetriebssystem Co-Stubs der Lehrveranstaltung
# 'Betriebssysteme 1' an der BTU-Cottbus im SS11
# -----------------------------------------------------------------------------
#
# Folgende Make-Targets sind m�glich
#
# depend 	: �berpr�ft alle Abh�ngigkeiten und schreibt diese in eine Datei
# system.img 	: erstellt das Speicherabbild des Betriebssystems
# bootdisk.img	: erstellt das Speicherabbild des Betriebssystem + Bootcode
# bootdisk	: kopiert das bootf�hig Speicherabbild auf Diskette
# clean		: l�scht alle generierten Dateien
#
# -----------------------------------------------------------------------------
#LINUX and CYGWIN so far
GENSYS = $(shell uname)

INITFINI = lib/finit.cc

# Liste der Quelltexte:
# (Beim Hinzufuegen neuer Module erweitern!)
# Achtung!!!! Hinter dem backslash am Zeilenende darf *kein* Zeichen stehen!!
# Die letzte Zeile bekommt kein backslash!!!


STARTUP_S = \
	boot/startup.asm

MACHINE_S = \
	io/ports.asm \
	cpu/cpu.asm\
	thread/switchContext.asm

SYSTEM_C = \
	lib/tools.c


SYSTEM_CC = \
	$(INITFINI) \
	device/CgaChannel.cc \
	device/CgaScreen.cc \
	device/Clock.cc\
	device/PIC.cc\
	device/PIT.cc\
	interrupts/Gate.cc\
	interrupts/InterruptGuardian.cc\
	interrupts/PageFaultGate.cc\
	interrupts/PanicGate.cc\
	interrupts/SpuriousGate.cc\
	io/PrintStream.cc \
	lib/Queue.cc\
	thread/Activity.cc\
	thread/Coroutine.cc\
	thread/Scheduler.cc\
	thread/ActivityScheduler.cc\
	device/Keyboard.cc \
	device/CodeTable.cc \
	tools/Interp.cc \
	tools/Scanner.cc \
	sync/KernelSemaphore.cc \
	sync/Monitor.cc \
	system/Console.cc \
	user/Hello.cc \
	user/Init.cc \
	mainMonitor.cc 
	#mainCo.cc


##############################################################################

STARTUP_SOURCE = $(addprefix ../machine/,$(STARTUP_S))
MACHINE_SOURCES = $(addprefix ../machine/,$(MACHINE_S))
SYSTEM_SOURCES = $(addprefix ../src/,$(SYSTEM_CC))
SYSTEM_C_SOURCES = $(addprefix ../src/,$(SYSTEM_C))

SOURCES = $(MACHINE_SOURCES) $(SYSTEM_SOURCES) $(SYSTEM_C_SOURCES)

FIRST_OBJECT = $(notdir $(STARTUP_SOURCE:.asm=.o))

OBJECTS = $(patsubst %.asm,%.o,$(patsubst %.c,%.o,$(patsubst %.cc,%.o,$(notdir $(SOURCES))) ))

VPATH = $(dir $(SOURCES) $(STARTUP_SOURCE) )

INCLUDES = -I../include \
	-I../machine

DEPENDENCIES_FILE = Dependencies.mk

##############################################################################

# Einstellungen in Abhaengigkeit vom Generierungssystem:
#
#    AS:          Zu benutzender Assembler
#    CC/CXX:       Zu benutzender C/C++-Compiler.
#    LD:           Zu benutzender Linker.
#    LDLIBS:       Dazuzulinkende Bibliotheken
#    LDHEAD:       Am Anfang zu linkende Dateien
#    LDTAIL:       Am Ende zu linkende Dateien
ifeq ($(GENSYS), Linux)

AS = nasm
CC = gcc
CXX = g++
# CC = clang
# CXX = clang++
LD = ld				# Default Linker gnu ld
OBJCOPY = objcopy

TARGET = -target i386-unknown-none-elf

COMMON_FLAGS = -m32 -fno-stack-protector -DLINUX -Wall -fno-exceptions -mno-sse -mno-sse2 -ffreestanding -fno-builtin -nostdlib -nostdinc -mno-red-zone
ASFLAGS = -DLINUX -f elf32
CFLAGS = -c $(COMMON_FLAGS) $(INCLUDES)
CXXFLAGS = -c $(COMMON_FLAGS) -fno-rtti -nostdinc++ $(INCLUDES)
LDFLAGS = -melf_i386 -e get_protected -T ../machine/linux.ls -o system
LDHEAD = $(shell $(CXX) -m32 --print-file-name=crti.o && \
	   $(CXX) -m32 --print-file-name=crtbegin.o)
LDTAIL = $(shell $(CXX) -m32 --print-file-name=crtend.o && \
	   $(CXX) -m32 --print-file-name=crtn.o)

# Pr�fe ob LLVM-Cross Toolchein genutzt wird
# Wenn ja f�ge Cross Target i386 hinzu
# Verhindert Probleme welche auftreten wenn
# gcc annahmen aus der Host-Plotform in
# die Kompilierung einbezieht
ifeq ($(CC), clang)
ifeq ($(CXX), clang++)
COMMON_FLAGS += $(TARGET)
LD = ld.lld		# Wenn LLVM-Toolchain genutzt wird nutze LLVM-lld als Linker
endif
endif

endif

# -------------------------------------------------------------------------
# Die Targets f�r die Kompilierung

%.o : %.asm
	$(AS) $(ASFLAGS) -o $@ $<

%.bin : %.asm
	$(AS) -f bin -o $@ $<

%.o : %.cc
	$(CXX) $(CXXFLAGS) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) -o $@ $<

# Linken des Systems
system : $(FIRST_OBJECT) $(OBJECTS)
	$(LD)  $(LDFLAGS) $(FIRST_OBJECT) $(LDHEAD) $(OBJECTS) $(LDTAIL)

bootdisk: system
	cp system isodir/boot/costubs.elf
	grub-mkrescue -d /usr/lib/grub/i386-pc -o costubs.iso isodir

# Ease of life statt st�ndig bochs separat auszuf�hren
bochs-run: bootdisk
	bochs -q

bochs-debug: ASFLAGS += -g
bochs-debug: COMMON_FLAGS += -ggdb3
bochs-debug: bootdisk
	bochs -qf bochsrc_debug.txt & sleep 1 && gdb -x gdb.script system

# Wenn statt bochs qemu genutzt wird
# Wichtig:
# qemu hat bei Aufgabe 1 keine M�glichkeit zu blinken
# stattdessem stehen mehr Hintergrundfarben zur Verf�gung
qemu-run: system
	qemu-system-i386 -kernel system

# debug build und run wenn qemu vorhanden
qemu-debug: ASFLAGS += -g
qemu-debug: COMMON_FLAGS += -ggdb3
qemu-debug: system
	qemu-system-i386 -kernel system -s -S & sleep 1 && gdb -x gdb.script system

# Bekanntmachen von Targets die keine Abh�ngigkeiten haben
.PHONY: clean depend

depend:
	@echo "" > $(DEPENDENCIES_FILE)
ifneq ($(strip $(SYSTEM_SOURCES)),)
	$(CXX) -MM $(CXXFLAGS) $(SYSTEM_SOURCES) >> $(DEPENDENCIES_FILE)
endif

clean:
	@rm -f *.o
	@rm -f isodir/boot/costubs.elf
	@rm -f costubs.iso
	@rm -f bochsout.txt
	@rm -f system
	@rm -f $(DEPENDENCIES_FILE)

# erstellt die Datei mit den Abh�ngigkeiten
$(DEPENDENCIES_FILE):
	touch $(DEPENDENCIES_FILE)
	$(MAKE) depend

# einbinden der Datei mit den aktuellen Abh�ngigkeiten
sinclude $(DEPENDENCIES_FILE)

