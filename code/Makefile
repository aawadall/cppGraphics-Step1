FLAGS = -I. -I /opt/local/include/eigen3 -I/usr/include -L/usr/lib -lglut -lGLEW -lGL -lGLU -lX11 -Wno-write-strings 
#-L /usr/lib/nvidia-304-updates
SOURCES = mv.cpp
EXECUTABLE = modelviewer
all: 
	g++ $(SOURCES) -o $(EXECUTABLE) $(FLAGS) 
#%: %.cpp
	#g++ $*.cpp -o $* $(FLAGS)
