// Based on CGAL's examples/Surface_mesh_segmentation/segmentation_via_sdf_values_example.cpp

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
#include <CGAL/boost/graph/IO/STL.h>

#include <iostream>
#include <fstream>
#include <string>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef boost::graph_traits<Polyhedron>::face_descriptor face_descriptor;

int main(int argc, char **argv)
{
    // create and read Polyhedron
    Polyhedron mesh;
    if ( !CGAL::IO::read_STL(argv[3], mesh) || !CGAL::is_triangle_mesh(mesh) )
    {
      std::cerr << "Input is not an STL triangle mesh." << std::endl;
      return EXIT_FAILURE;
    }

    // create a property-map for segment-ids
    typedef std::map<face_descriptor, std::size_t> Facet_int_map;
    Facet_int_map internal_segment_map;
    boost::associative_property_map<Facet_int_map> segment_property_map(internal_segment_map);

    // calculate SDF values and segment the mesh
    const double cone_angle = 2.0 / 3.0 * CGAL_PI;
    const std::size_t n_rays = 25;
    const std::size_t n_clusters = 5;
    double smoothing_lambda = std::stod(argv[1]);
    std::size_t n_segments = CGAL::segmentation_via_sdf_values(mesh, segment_property_map, cone_angle, n_rays, n_clusters, smoothing_lambda);
    std::cerr << "Number of segments: " << n_segments << std::endl;

    // print (offset) segment-ids to (existing) tag file
    std::ofstream tag_file;
    tag_file.open(argv[4], std::ios_base::out | std::ios_base::app);
    for(face_descriptor f : faces(mesh)) {
        // ids are between [1, n_segments]
        tag_file << std::stoi(argv[2]) + ++segment_property_map[f] << std::endl;
    }
    tag_file.close();

    return EXIT_SUCCESS;
}
