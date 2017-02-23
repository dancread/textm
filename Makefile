CC=cl /nologo
LINK=link
SOURCES=textm.c utils.c tui.c
CFLAGS=
OBJECTS=$(SOURCES:.c=.obj)
LIBS=pdcurses.lib
TINY_LINK_FLAGS=/NODEFAULTLIB
TINY_INCLUDE_DIRS=/Iinclude
TINY_LIBS=pdcurses.lib wcrt.lib kernel32.lib user32.lib  legacy_stdio_definitions.lib
all:
	$(CC) $(CFLAGS) $(SOURCES) /link $(LINK_FLAGS) $(LIBS)
tiny:
#    $(CC) $(CFLAGS) $(TINY_INCLUDE_DIRS) $(SOURCES) /link $(TINY_LINK_FLAGS) $(TINY_LIBS)
	$(CC) $(CFLAGS) $(SOURCES) /link $(TINY_LINK_FLAGS) $(TINY_LIBS)
clean:
	del $(OBJECTS) textm.exe
