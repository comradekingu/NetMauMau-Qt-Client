QT += svg

CONFIG += debug_and_release
CONFIG += rtti exceptions

VERSION = 0.7

DEFINES += "PACKAGE_NAME=\"\\\"NetMauMau Qt Client\\\"\"" "PACKAGE_VERSION=\"\\\"$$VERSION\\\"\""

QMAKE_RESOURCE_FLAGS += -compress 9

CONFIG(debug, debug|release) {
	 TARGET = nmm-qt-client-debug
	 DEFINES += _GLIBCXX_VISIBILITY=0 _GLIBCXX_CONCEPT_CHECKS QT_NO_CAST_FROM_BYTEARRAY \
		QT_NO_CAST_TO_ASCII
	 INCLUDEPATH += "../../netmaumau/src/include"
	 QMAKE_CXXFLAGS += -g3 -O0 -fstrict-aliasing -ftrapv -fno-inline -W -Wextra -Wall -Wnoexcept \
	-Woverloaded-virtual -Wno-packed-bitfield-compat -Wmissing-noreturn -Wunused -Wtrampolines \
	-Wdouble-promotion -Wnon-virtual-dtor -Wold-style-cast -Winit-self -Wctor-dtor-privacy \
	-Wunreachable-code -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 \
	-Wimport -Wmissing-format-attribute -Wmissing-include-dirs -Wredundant-decls -Winline \
	-Wuninitialized -Wvariadic-macros -Wlogical-op -Wnoexcept -Wmissing-noreturn -Wpointer-arith \
	-Wstrict-null-sentinel -Wstrict-overflow -Wshadow -Werror=strict-aliasing
	 LIBS    += ../../netmaumau/debug/src/client/.libs/libnetmaumauclient.a \
		 ../../netmaumau/debug/src/common/.libs/libnetmaumaucommon.a -lmagic
} else {
	 TARGET = nmm-qt-client
	 win32:CONFIG += static
	 DEFINES += NDEBUG _GLIBCXX_VISIBILITY=0 QT_NO_DEBUG_OUTPUT QT_NO_CAST_FROM_BYTEARRAY \
		QT_NO_CAST_TO_ASCII
	 unix:INCLUDEPATH += "/usr/include/netmaumau"
	 win32:INCLUDEPATH += "/usr/i686-pc-mingw32/usr/include/netmaumau"
	 unix:QMAKE_CXXFLAGS += -O3 -g -fno-omit-frame-pointer -march=native -fstrict-aliasing -Wformat \
	 -Wformat-security -Wno-packed-bitfield-compat -Wsuggest-attribute=pure \
	 -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wdisabled-optimization
	 win32:QMAKE_CXXFLAGS += -O2 -fomit-frame-pointer -fstrict-aliasing
	 win32:LIBS    += /usr/i686-pc-mingw32/usr/lib/libnetmaumauclient.a \
				/usr/i686-pc-mingw32/usr/lib/libnetmaumaucommon.a
	 unix:LIBS += -lnetmaumaucommon -lnetmaumauclient
}

SOURCES += cardpixmap.cpp \
	cardwidget.cpp \
	client.cpp \
	connectionlogdialog.cpp \
	deleteserversdialog.cpp \
	jackchoosedialog.cpp \
	launchdialogbase.cpp \
	launchserverdialog.cpp \
	licensedialog.cpp \
	localserveroutputview.cpp \
	main.cpp \
	mainwindow.cpp \
	messageitemdelegate.cpp \
	netmaumauapplication.cpp \
	netmaumaumessagebox.cpp \
	playerimagedelegate.cpp \
	playerimageprogressdialog.cpp \
	portspin.cpp \
	serverdialog.cpp \
	serverinfo.cpp \
	suitlabel.cpp \
	suitradiobutton.cpp \
	util.cpp

HEADERS  += cardpixmap.h \
	cardwidget.h \
	client.h \
	connectionlogdialog.h \
	deleteserversdialog.h \
	jackchoosedialog.h \
	launchdialogbase.h \
	launchserverdialog.h \
	licensedialog.h \
	localserveroutputview.h \
	mainwindow.h \
	messageitemdelegate.h \
	netmaumauapplication.h \
	netmaumaumessagebox.h \
	playerimagedelegate.h \
	playerimageprogressdialog.h \
	portspin.h \
	serverdialog.h \
	serverinfo.h \
	suitlabel.h \
	suitradiobutton.h \
	util.h

FORMS    += cardwidget.ui \
	connectionlogdialog.ui \
	deleteserversdialog.ui \
	jackchoosedialog.ui \
	launchserverdialog.ui \
	licensedialog.ui \
	localserveroutputview.ui \
	mainwindow.ui \
	serverdialog.ui \
	suitlabel.ui \
	suitradiobutton.ui

RESOURCES += cards.qrc \
	icons.qrc \
	license.qrc \
	nuoveXT2.qrc

RC_FILE += appicon.rc

DISTFILES += COPYING cards/* *.png *.ico nmm_qt_client.desktop

TRANSLATIONS += nmm_qt_client_de_DE.ts
