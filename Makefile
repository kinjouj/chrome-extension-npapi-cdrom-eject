CFLAGS = -g -Wall -I. -DXP_UNIX=1

all:
	g++ -I/opt/npapi/headers $(CFLAGS) -fPIC -c plugin.cc -o cdrom_eject_plugin.o
	g++ -shared cdrom_eject_plugin.o -o plugin/libcdrom_eject_plugin.so

clean:
	rm cdrom_eject_plugin.o plugin/libcdrom_eject_plugin.so
