# Makefile

# Ustawienia kompilatora
CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lcomdlg32 -lgdi32  # Biblioteki linkuj¹ce dla GUI w Windows

# Katalogi
GUI_DIR = GUI
VERIFY_KEY_DIR = VerifyKey
CRACK_DIR = Crack

# Pliki wyjœciowe
EXE_FILE = app.exe
DLL_FILE = verify_key.dll
PATCHER_FILE = patcher.exe

# Cel g³ówny
all: $(EXE_FILE) $(DLL_FILE)

# Kompilacja aplikacji GUI
$(EXE_FILE): $(GUI_DIR)/graphical_user_interface.cpp $(DLL_FILE)
	$(CXX) $(CXXFLAGS) $(GUI_DIR)/graphical_user_interface.cpp -o $(EXE_FILE) $(LDFLAGS)

# Kompilacja DLL
$(DLL_FILE): $(VERIFY_KEY_DIR)/verify_key.cpp
	$(CXX) -shared $(CXXFLAGS) -o $(DLL_FILE) $(VERIFY_KEY_DIR)/verify_key.cpp

# Kompilacja programu do patchowania DLL
$(PATCHER_FILE): $(CRACK_DIR)/crack.cpp
	$(CXX) $(CXXFLAGS) $(CRACK_DIR)/crack.cpp -o $(PATCHER_FILE)

# Usuwanie plików wyjœciowych
clean:
	rm -f $(EXE_FILE) $(DLL_FILE) $(PATCHER_FILE)
