SOURCES_COMMON_CPP=main.cpp BaseHechos.cpp BaseConocimientos.cpp MotorInferencias.cpp Regla.cpp
SOURCES_COMMON_H=..\include\BaseConocimientos.h ..\include\BaseHechos.h ..\include\MotorInferencias.h ..\include\Regla.h
SOURCES_COMMON=$(SOURCES_COMMON_CPP) $(SOURCES_COMMON_H)


SBR-FC: $(SOURCES_COMMON)
	g++ -std=c++20 -Wall -O3 -I..\include $(SOURCES_COMMON_CPP) -o SBR-FC -static

clean:	
	rm -f SBR-FC
