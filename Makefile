IFLAGS  = -I$$GMP_INC_DIR -I$$BOOST_INC_DIR -I$$CGAL_INC_DIR
OFLAGS  = -Ofast
LDFLAGS = -Wl,-rpath=$$GMP_LIB_DIR -L$$GMP_LIB_DIR -lgmp

fTagTamed: src/fTagTamed.cpp | dep/env_dep.sh
	. $| && $(CXX) $(IFLAGS) $(OFLAGS) -o $@ $^ $(LDFLAGS)

dep/env_dep.sh:
	cd $(@D) && ./get_dep.sh
