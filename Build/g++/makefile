CC = g++
CFLAGS = -c -I -l
STD = -std=c++11
BFLAGS = -o
HEADER_DIR = -I ../../Headers
SCR_DIR = ../../Implementations
OBJ_DIR = ./
LIB_DIR = ../../Lib
WIN_DEP = -I /mnt/c/Program\ Files\ \(x86\)/Windows\ Kits/10/Include/10.0.14393.0/shared -I /mnt/c/Program\ Files\ \(x86\)/Windows\ Kits/10/Include/10.0.14393.0/ucrt -I /mnt/c/Program\ Files\ \(x86\)/Windows\ Kits/10/Include/10.0.14393.0/um -I /mnt/c/Program\ Files\ \(x86\)/Windows\ Kits/10/Include/10.0.14393.0/winrt -I /mnt/c/Program\ Files\ \(x86\)/Microsoft\ Visual\ Studio\ 14.0/VC/include -I /mnt/c/Program\ Files\ \(x86\)/Microsoft\ SDKs/Windows/v7.1A/Include
SRC_FILES = $(wildcard $(SCR_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SCR_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
EXTERN_LIB = GL3W.lib SOIL.lib tinyxml2.lib
ENDFILE = Killer_Engine_Win32_Debug.lib
BIN_DIR = ../../Bin/G++Win32_Debug

$(ENDFILE):$(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(BFLAGS) $(ENDFILE)
	chmod 744 $(ENDFILE)
	mkdir -p $(BIN_DIR)
	mv ./$(ENDFILE) $(BIN_DIR)/$(ENDFILE)

$(OBJ_FILES):
	$(CC) $(STD) -c $(HEADER_DIR) $(WIN_DEP) -l $(LIB_DIR) $(SRC_FILES)

clean:
	rm -rf *.o $(BIN_DIR)/$(ENDFILE)
	$(MAKE) $(ENDFILE)