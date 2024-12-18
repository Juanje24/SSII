SOURCES_COMMON_CPP=main.cpp BaseHechos.cpp BaseConocimientos.cpp MotorInferencias.cpp Regla.cpp
SOURCES_COMMON_H=../include/BaseConocimientos.h ../include/BaseHechos.h ../include/MotorInferencias.h ../include/Regla.h
SOURCES_COMMON=$(SOURCES_COMMON_CPP) $(SOURCES_COMMON_H)


SBR-FC: $(SOURCES_COMMON)
	x86_64-w64-mingw32-g++ -static -o SBR-FC.exe main.cpp BaseHechos.cpp BaseConocimientos.cpp MotorInferencias.cpp Regla.cpp -I../include -L../lib 

clean:	
	rm -f SBR-FC
