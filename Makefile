fTagTamed: src/fTagTamed.cpp | dep/env_dep.sh
	. $| && $(CXX) -I$$CGAL_DIR/include -I$$BOOST_DIR -Ofast -o $@ $^ -lgmp

dep/env_dep.sh:
	cd $(@D) && ./get_dep.sh
