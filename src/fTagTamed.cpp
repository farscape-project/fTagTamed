// Based on CGAL's examples/Surface_mesh_segmentation/segmentation_via_sdf_values_example.cpp

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/Polyhedron_items_with_id_3.h>
#include <CGAL/boost/graph/IO/STL.h>
#include <CGAL/mesh_segmentation.h>
#include <CGAL/property_map.h>
#include <iostream>
#include <fstream>
#include <string>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_items_with_id_3 Items;
typedef CGAL::Polyhedron_3<Kernel, Items> Polyhedron;
typedef boost::graph_traits<Polyhedron>::vertex_descriptor vertex;
typedef boost::graph_traits<Polyhedron>::halfedge_descriptor halfedge;
typedef boost::graph_traits<Polyhedron>::face_descriptor facet;

int main(int argc, char **argv)
{
  // check for the correct number of command line arguments
  if( !(argc == 5 || argc == 6) ) {
    std::cerr << "usage: fTagTamed smoothing_lambda tag_offset input_stl_file output_tag_file [output_msh_file]" << std::endl;
    std::cerr << ""                                                                                              << std::endl;
    std::cerr << "  smoothing_lambda: the higher the fewer the number of segments (floating-point in [0, 1])"    << std::endl;
    std::cerr << "  tag_offset:       the initial tag from which to count from (strictly positive integer)"      << std::endl;
    std::cerr << "  input_stl_file:   the file describing the surface mesh to be tagged (STL)"                   << std::endl;
    std::cerr << "  output_tag_file:  the file to which the list of tags will be written to (Plain Text)"        << std::endl;
    std::cerr << "  output_msh_file:  the file to which the tagged surface mesh will be written to (MSH 2.2)"    << std::endl;
    return EXIT_FAILURE;
  }

  // create and read Polyhedron
  Polyhedron mesh;
  if( !CGAL::IO::read_STL(argv[3], mesh) || !CGAL::is_triangle_mesh(mesh) ) {
    std::cerr << "Input is not an STL triangle mesh." << std::endl;
    return EXIT_FAILURE;
  }

  // create a property-map for segment ids
  typedef std::map<facet, std::size_t> Facet_int_map;
  Facet_int_map internal_segment_map;
  boost::associative_property_map<Facet_int_map> facet_segment_map(internal_segment_map);

  // calculate SDF values and segment the mesh
  const double cone_angle = 2.0 / 3.0 * CGAL_PI;
  const std::size_t n_rays = 25;
  const std::size_t n_clusters = 5;
  double smoothing_lambda = std::stod(argv[1]);
  std::size_t n_segments = CGAL::segmentation_via_sdf_values(mesh, facet_segment_map, cone_angle, n_rays, n_clusters, smoothing_lambda);
  std::cerr << "Number of segments: " << n_segments << std::endl;

  // write offset segment ids in { offset, ..., offset + n_segments - 1 } to (possibly existing) tag file
  std::ofstream tag_file;
  tag_file.open(argv[4], std::ios_base::out | std::ios_base::app);
  for( facet f : mesh.facet_handles() )
    tag_file << std::stoi(argv[2]) + facet_segment_map[f] << std::endl;

  // early exit if no MSH filename provided
  if( argc < 6 )
    return EXIT_SUCCESS;

  // enumerate vertices and facets
  std::size_t vv = 0, ff = 0;
  for( vertex v : mesh.vertex_handles() )
    v->id() = ++vv;
  for( facet f : mesh.facet_handles() )
    f->id() = ++ff;

  // write tagged surface mesh to a MSH 2.2 file
  std::ofstream msh_file;
  msh_file.open(argv[5], std::ios_base::out | std::ios_base::trunc);
  msh_file << "$MeshFormat"                  << std::endl;
  msh_file << "2.2 0 " << sizeof(double)     << std::endl;
  msh_file << "$EndMeshFormat"               << std::endl;
  msh_file << "$Nodes"                       << std::endl;
  msh_file << mesh.size_of_vertices()        << std::endl;
  for( vertex v : mesh.vertex_handles() )
    msh_file << v->id() << " " << v->point() << std::endl;
  msh_file << "$EndNodes"                    << std::endl;
  msh_file << "$Elements"                    << std::endl;
  msh_file << mesh.size_of_facets()          << std::endl;
  for( facet f : mesh.facet_handles() ) {
    msh_file << f->id() << " 2 2"
              << " " << std::stoi(argv[2]) + facet_segment_map[f]
              << " " << std::stoi(argv[2]) + facet_segment_map[f];
    halfedge h = f->halfedge();
    do
      msh_file << " " << h->vertex()->id();
    while( (h = h->next()) != f->halfedge() );
    msh_file                                 << std::endl;
  }
  msh_file << "$EndElements"                 << std::endl;

  return EXIT_SUCCESS;
}
