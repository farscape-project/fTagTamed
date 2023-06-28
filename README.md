## fTagTamed: an app to tag surface meshes to be tetrahedralized by fTetWild

fTagTamed decomposes a triangulated surface mesh provided in an STL file into
smaller and meaningful sub-meshes, or segments, by assigning a tag, or segment
id, to each triangle. fTagTamed is essentially a wrapper around
[CGAL](https://www.cgal.org)'s
[Triangulated Surface Mesh Segmentation](https://doc.cgal.org/latest/Surface_mesh_segmentation/)
package. The output is a list with as many tags as triangles in the provided
surface mesh and, optionally, a tagged MSH file for visualization in Gmsh.

### Installation

To install fTagTamed on GNU/Linux or on macOS, simply clone this repo and build
the app's executable using the included makefile:

```
git clone https://github.com/farscape-project/fTagTamed.git
cd fTagTamed
make
```

Note that the first time you run `make`, a few dependencies, namely
[GMP](https://gmplib.org), [Boost](https://www.boost.org) and
[CGAL](https://www.cgal.org), will be automatically downloaded and installed
under `dep/`.

### Usage

fTagTamed provides some flexibility regarding the segmentation algorithm and
its input and outputs. Here is a description of the available parameters:

```
usage: fTagTamed aperture clusters smoothing offset input_stl output_tags [output_msh]

  aperture    floating-point in [0, 180[ aperture of the ray sampling cone on each facet
  clusters    strictly positive integer  number of segments without considering connectivity
  smoothing   floating-point in [0, 1]   the higher the fewer the number of segments
  offset      strictly positive integer  initial tag from which to count from
  input_stl   STL                        file describing the surface mesh to be tagged
  output_tags Plain Text                 file to which the list of tags will be appended to
  output_msh  MSH 2.2                    file to which the tagged surface mesh will be written to
```

If you wish to better understand the segmentation algorithm parameters, we
encourage you to read CGAL's documentation, and to inspect and maybe edit the
(very short) source code in `src/fTagTamed.cpp`. All contributions are welcome.
