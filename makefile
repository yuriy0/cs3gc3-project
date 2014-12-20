CC=g++ 
CFLAGS= -pedantic -Wall -std=c++11 -Wno-vla -Wno-sign-compare
LDFLAGS= -lGL -lGLU -lglut1
SRCDIR=src
EXE = cs3gc3-final
FILES = vec2 wall utils drawing main circle state 

ifeq "$(OS)" "Windows_NT"
    LDFLAGS = -lglut32 -lglu32 -lopengl32
endif

all: $(EXE)


$(EXE): $(patsubst %,$(SRCDIR)/%.o, $(FILES)) 
	$(CC) $(addsuffix .o, $(addprefix $(SRCDIR)/, $(FILES))) -o $@ $(CFLAGS) $(LDFLAGS)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS) 

clean: 
	rm src/*.o
	rm ./$(EXE)
