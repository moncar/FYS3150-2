CXX = g++
RM = rm -r
CPPFLAGS = -O3 -std=c++11 -pedantic -Wall -lm
DEPS = src/vec3.h src/CelestialBody.h src/CBList.h

run:
	mkdir -p run/TEST

run/CelestialBody: src/CelestialBody.cpp $(DEPS) | run
	 $(CXX) $(CPPFLAGS) $< -o $@

#run/SolarSystem: src/SolarSystem.cpp src/PlanetList.h $(DEPS) | run
#	 $(CXX) $(CPPFLAGS) $< -o $@

run/vec3: src/vec3.cpp $(DEPS) | run
	$(CXX) $(CPPFLAGS) $< -o $@

run/CBList: src/CBList.cpp $(DEPS) | run
	$(CXX) $(CPPFLAGS) $< -o $@

run/TEST/testCelestialBody: test/testCelestialBody.cpp $(DEPS) | run/TEST
	$(CXX) $(CPPFLAGS) $< -o $@

clean:
	$(RM) run
