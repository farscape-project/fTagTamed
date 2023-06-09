// Based on CGAL's examples/Surface_mesh_segmentation/segmentation_from_sdf_values_example.cpp

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
#include <CGAL/boost/graph/IO/STL.h>
#include <iostream>
#include <string>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;
typedef boost::graph_traits<Polyhedron>::face_descriptor face_descriptor;

int main(int argc, char **argv)
{
    // create and read Polyhedron
    Polyhedron mesh;
    CGAL::IO::read_STL(argv[1], mesh);
    if ( mesh.empty() || !CGAL::is_triangle_mesh(mesh) )
    {
      std::cerr << "Input is not a triangle mesh." << std::endl;
      return EXIT_FAILURE;
    }

    // create a property-map for SDF values
    typedef std::map<face_descriptor, double> Facet_double_map;
    Facet_double_map internal_sdf_map;
    boost::associative_property_map<Facet_double_map> sdf_property_map(internal_sdf_map);

    // compute SDF values using default parameters for number of rays, and cone angle
    CGAL::sdf_values(mesh, sdf_property_map);

    // create a property-map for segment-ids
    typedef std::map<face_descriptor, std::size_t> Facet_int_map;
    Facet_int_map internal_segment_map;
    boost::associative_property_map<Facet_int_map> segment_property_map(internal_segment_map);

    // segment the mesh using custom parameters for number of clusters and smoothing lambda
    const std::size_t n_clusters = 5;              // no. of clusters in soft clustering
    double smoothing_lambda = std::stod(argv[2]);  // importance of surface features, suggested to be in [0,1]
    std::size_t n_segments = CGAL::segmentation_from_sdf_values(mesh, sdf_property_map, segment_property_map,
                                                                n_clusters, smoothing_lambda);
    std::cout << "Number of segments: " << n_segments << std::endl;

    // print segment-ids
    for(face_descriptor f : faces(mesh)) {
        // ids are between [0, n_segments -1]
        std::cout << segment_property_map[f] << std::endl;
    }

    return EXIT_SUCCESS;
}
