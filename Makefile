CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -O2
CPPFLAGS := -Isrc

DEMO_EXE := demo.exe
DEMO_SRC := demo/main.cpp

HEADERS  := src/HashMap.hpp src/Dictionary.hpp

.PHONY: all run clean

all: $(DEMO_EXE)

$(DEMO_EXE): $(DEMO_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(DEMO_SRC) -o $@

run: $(DEMO_EXE)
	./$(DEMO_EXE)

clean:
	rm -f $(DEMO_EXE)
