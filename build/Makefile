INCLUDES=-I../include
LINKLIBS=-L../libs/SDL2 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
CPPFLAGS=$(INCLUDES)

SRC_DIR := ../src
SRC_DIR_LIBS := ../libs
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
SRC_FILES_LIBS := $(wildcard $(SRC_DIR_LIBS)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES)) $(patsubst $(SRC_DIR_LIBS)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES_LIBS))

all: a.exe

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(OBJ_DIR)
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR_LIBS)/%.cpp $(OBJ_DIR)
	g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

a.exe: $(SRC_FILES) $(SRC_FILES_LIBS) $(OBJ_FILES)
	g++ $(INCLUDES) $(OBJ_FILES) -o main.exe $(LINKLIBS)
