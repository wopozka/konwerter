all:konwerter
CC=g++
INCLUDE=.
DESTDIR=/usr/local/bin
CFLAGS=-Wall -g
konwerter: konwerter.o operacje.o czyt_zapis.o num_na_etyk.o prz_string.o operacje_na_tex.o system_zapisu.o
	$(CC)  $(CFLAGS) -o konwerter konwerter.o operacje.o czyt_zapis.o num_na_etyk.o prz_string.o operacje_na_tex.o system_zapisu.o
operacje.o: operacje.cc operacje.h czyt_zapis.h dl_wiersza.h system_zapisu.h
	$(CC) -c -I$(INCLUDE) $(CFLAGS) operacje.cc
konwerter.o: konwerter.cc operacje.h dl_wiersza.h system_zapisu.h
	$(CC) -c -I$(INCLUDE) $(CFLAGS) konwerter.cc
czyt_zapis.o: czyt_zapis.cc czyt_zapis.h
	$(CC) -c -I$(INCLUDE) $(CFLAGS) czyt_zapis.cc
num_na_etyk.o: num_na_etyk.cc num_na_etyk.h
	$(CC) -c -I$(INCLUDE) $(CFLAGS) num_na_etyk.cc
prz_string.o: prz_string.cc prz_string.h
	$(CC) -c -I$(INCLUDE) $(CFLAGS) prz_string.cc
operacje_na_tex.o: operacje_na_tex.cc operacje_na_tex.h
	$(CC) -c -I$(INCLUDE) $(CFLAGS) operacje_na_tex.cc
system_zapisu.o: system_zapisu.cc system_zapisu.h
	$(CC) -c -I$(INCLUDE) $(CFLAGS) system_zapisu.cc
clean:
	-rm *.o konwerter
install: konwerter
	cp konwerter $(DESTDIR)
	ln -s $(DESTDIR)/konwerter $(DESTDIR)/etykietuj
