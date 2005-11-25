AUTOMAKE_OPTIONS=nostdinc subdir-objects
CPPFLAGS=-DDATADIR="\"$(pkgdatadir)\"" -DSYSCONFDIR="\"$(sysconfdir)\""
INCLUDES=-I.
CFLAGS=-Wall -Werror @CFLAGS@
CXXFLAGS=-Wall -Werror @CXXFLAGS@

noinst_LIBRARIES=libcommon.a
bin_PROGRAMS=odyssey

libcommon_a_SOURCES=ConfigFile.cxx ConfigFile.h \
	Util.cxx Util.h DataBuffer.cxx DataBuffer.h \
	HexFile.cxx HexFile.h HexFile_ihx16.cxx HexFile_ihx8.cxx \
	ParallelPort.cxx ParallelPort.h IO.cxx IO.h \
	Device.cxx Device.h device/PicDevice.h device/PicDevice.cxx \
	device/Pic16Device.cxx device/Pic16f8xxDevice.cxx \
	device/Pic16f7xDevice.cxx device/Pic18Device.cxx \
	device/Pic12f6xxDevice.cxx device/Pic16f6xx.cxx \
	device/Pic16f87xADevice.cxx \
	DirectPPIO.cxx DirectPPIO.h
EXTRA_libcommon_a_SOURCES=LinuxPPDevIO.cxx LinuxPPDevIO.h

if ENABLE_LINUX_PPDEV
libcommon_a_LIBADD=LinuxPPDevIO.o
endif


odyssey_SOURCES=main.cxx
odyssey_LDADD=libcommon.a
