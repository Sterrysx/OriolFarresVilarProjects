OPCIONS = -D_JUDGE_ -D_GLIBCXX_DEBUG -O2 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11
#
G++ = g++  #esto solo es necesario en la FIB, ya que su g++ es muy antiguo
#
program.exe: Process_Area.o Cluster.o Proceso.o Procesador.o program.o
	$(G++) -o program.exe Process_Area.o Cluster.o Proceso.o Procesador.o program.o
#
Process_Area.o: Process_Area.cc Process_Area.hh
	$(G++) -c Process_Area.cc $(OPCIONS) 
#
Cluster.o: Cluster.cc Cluster.hh
	$(G++) -c Cluster.cc $(OPCIONS) 
#
Procesador.o: Procesador.cc Procesador.hh
	$(G++) -c Procesador.cc $(OPCIONS) 
#
Proceso.o: Proceso.cc Proceso.hh
	$(G++) -c Proceso.cc $(OPCIONS) 
#
program.o: program.cc Proceso.hh Procesador.hh Process_Area.hh Cluster.hh
	$(G++) -c program.cc $(OPCIONS) 
#
practica.tar:  	program.exe
	tar cvf practica.tar program.cc Process_Area.cc Cluster.cc Procesador.cc Proceso.cc BinTree.hh Process_Area.hh Cluster.hh Procesador.hh Proceso.hh Makefile html.zip
#
clean:
	rm -f *.o
	rm -f *.exe
