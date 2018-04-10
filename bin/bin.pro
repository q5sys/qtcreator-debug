TEMPLATE = app
TARGET = qtcreator-debug.sh

include(../qtcreator.pri)

OBJECTS_DIR =

PRE_TARGETDEPS = $$PWD/qtcreator-debug.sh

QMAKE_LINK = cp $$PWD/qtcreator-debug.sh $@ && : IGNORE REST OF LINE:
QMAKE_STRIP =
CONFIG -= qt debug separate_debug_info gdb_dwarf_index

QMAKE_CLEAN = qtcreator-debug.sh

target.path  = $$INSTALL_BIN_PATH
INSTALLS    += target

DISTFILES = $$PWD/qtcreator-debug.sh
