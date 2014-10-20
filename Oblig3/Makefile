CXX = g++
RM = rm -r
CPPFLAGS = -O3 -std=c++11 -pedantic -Wall
DEPS = src/vec3.h src/CelestialBody.h src/CBList.h
TESTFLAGS = -lgtest
COMP = run/vec3.o run/CelestialBody.o run/CBList.o run/SolarSystem.o

run:
	mkdir -p run/TEST

run/CelestialBody.o: src/CelestialBody.cpp $(DEPS) | run
	 $(CXX) $(CPPFLAGS) $< -c -o $@

run/SolarSystem.o: src/SolarSystem.cpp $(DEPS) | run
	 $(CXX) $(CPPFLAGS) $< -c -o $@

run/vec3.o: src/vec3.cpp $(DEPS) | run
	$(CXX) $(CPPFLAGS) $< -c -o $@

run/CBList.o: src/CBList.cpp $(DEPS) | run
	$(CXX) $(CPPFLAGS) $< -c -o $@

run/TEST/testCelestialBody: test/testCelestialBody.cpp $(DEPS) $(COMP) | run/TEST
	$(CXX) $(CPPFLAGS) $(TESTFLAGS) $(COMP) $< -o $@

run/TEST/testVec3: test/testVec3.cpp $(DEPS) $(COMP) | run/TEST
	$(CXX) $(CPPFLAGS) $(TESTFLAGS) $(COMP) $< -o $@

run/TEST/testCBList: test/testCBList.cpp $(DEPS) $(COMP) | run/TEST
	$(CXX) $(CPPFLAGS) $(TESTFLAGS) $(COMP) $< -o $@

clean:
	$(RM) run
