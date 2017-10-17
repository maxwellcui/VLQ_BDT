#Compiling the program

BINS = prepTree

CXX = g++
CCFLAGS = -O0 -ggdb -std=c++11 


LD = g++
LDFLAGS = 

LIBS = $(shell root-config --libdir) 
INCS = $(shell root-config --incdir)  


default : $(BINS)

$(BINS): % : %.C 
	@echo -n "Building $@ ... "
	$(CXX) $(CCFLAGS) $<  $(addprefix -I, $(INCS))  $(shell root-config --libs) -lMLP -lMinuit -lTreePlayer -lTMVA -lTMVAGui -lXMLIO  -lMLP -lm  -g -o $@
	@echo "Done"


clean: 
	rm -f *.o	$(BINS)

