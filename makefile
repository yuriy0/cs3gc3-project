CC=g++ 
CFLAGS= -pedantic -Wall -std=c++11 -Wno-vla -Wno-sign-compare
LDFLAGS= -lGL -lGLU -lglut1
SRCDIR=src
EXE = cs3gc3-final
FILES = vec2 wall utils drawing main circle state 
PWDCMD = pwd 

ifeq "$(OS)" "Windows_NT"
    EXE =  cs3gc3-final.exe
    LDFLAGS = -lglut32 -lglu32 -lopengl32
    PWDCMD = cmd /c cd
endif


README = -D 'README=R"($(shell $(PWDCMD))/readme)"'

all: $(EXE)

$(EXE): $(patsubst %,$(SRCDIR)/%.o, $(FILES)) 
	$(CC) $(addsuffix .o, $(addprefix $(SRCDIR)/, $(FILES))) -o $@ $(CFLAGS) $(LDFLAGS) $(README)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)  $(README)

clean: 
	rm src/*.o
	rm ./$(EXE)

zip: 
	zip -r cs3gc3_final_project_y.toporovskyy_m.mohammed.zip makefile readme src/*.h src/*.cpp images/* $(EXE)
