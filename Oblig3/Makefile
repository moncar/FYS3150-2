CXX = g++
RM = rm -r
CPPFLAGS = -O3 -std=c++11
DEPS = src/vec3.h src/Planet.h

run:
	mkdir -p run

run/Planet: src/Planet.cpp $(DEPS) | run
	$(CXX) $(CPPFLAGS) $< -o $@

run/SolarSystem: src/SolarSystem.cpp $(DEPS) | run
	$(CXX) $(CPPFLAGS) $< -o $@

run/vec3: src/vec3.cpp $(DEPS) | run
	$(CXX) $(CPPFLAGS) $< -o $@

#run/PlanetList: src/PlanetList.cpp $(DEPS) | run
#	$(CXX) $(CPPFLAGS) $< -o $@

clean:
	$(RM) run
