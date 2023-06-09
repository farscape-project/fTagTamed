tag_surface_mesh: src/tag_surface_mesh.cpp | dep
	. ./dep/env_cgal.sh && $(CXX) -I$$CGAL_DIR/include -I$$BOOST_DIR -Ofast -o $@ $< -lgmp

dep:
	./get_cgal.sh
