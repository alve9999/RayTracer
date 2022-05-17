INCLUDES=-I../include -I../include/imgui
LINKLIBS=-L../libs/glad -L../libs/glfw -lglfw3 -lopengl32 -lgdi32 #-luser32 -lkernel32
CPPFLAGS=$(INCLUDES)

SRC_DIR := ../src
SRC_DIR_LIBS := ../libs/imgui
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES_LIBS := $(wildcard $(SRC_DIR_LIBS)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES)) $(patsubst $(SRC_DIR_LIBS)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES_LIBS))

all: a.exe

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR_LIBS)/%.cpp
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/glad.o: ../libs/glad/glad.c
	gcc -c $(INCLUDES) ../libs/glad/glad.c -o $(OBJ_DIR)/glad.o

a.exe: $(SRC_FILES) $(SRC_FILES_LIBS) $(OBJ_FILES) $(OBJ_DIR)/glad.o
	g++ $(INCLUDES) $(OBJ_FILES) $(OBJ_DIR)/glad.o -o main.exe $(LINKLIBS)
