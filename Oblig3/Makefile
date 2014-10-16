CXX = g++
RM = rm -r
CPPFLAGS = -O3 -std=c++11
PLA = src/Planet.cpp
SOL = src/SolarSystem.cpp
VEC = src/vec3.cpp
HEAD = src/vec3.h

run:
	mkdir -p run

build/Planet: $(PLA) $(HEAD) | run
	$(CXX) $(CPPFLAGS) $< -o $@

build/SolarSystem: $(SOL) $(HEAD) | run
	$(CXX) $(CPPFLAGS) $< -o $@

build/vec3: $(VEC) $(HEAD) | run
	$(CXX) $(CPPFLAGS) $< -o $@

clean:
	$(RM) run
