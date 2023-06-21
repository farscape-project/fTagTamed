## fTagTamed: an app to tag surface meshes to be tetrahedralized by fTetWild

fTagTamed decomposes a triangulated surface mesh provided in an STL file into
smaller and meaningful sub-meshes, or segments, by assigning a tag, or segment
id, to each triangle. fTagTamed is essentially a wrapper around
[CGAL](https://www.cgal.org)'s
[Triangulated Surface Mesh Segmentation](https://doc.cgal.org/latest/Surface_mesh_segmentation/)
package with a reduced feature set for ease of use. The output is a list with
as many tags as triangles in the provided surface mesh.

### Installation

To install fTagTamed, simply clone this repo and build the app's executable
using the included makefile:

```
git clone https://github.com/farscape-project/fTagTamed.git
cd fTagTamed
make
```

Note that the first time you run `make`, a couple of dependencies,
[Boost](https://www.boost.org) and [CGAL](https://www.cgal.org), will be
automatically downloaded and installed under `dep/`.

### Usage

fTagTamed provides limited tuning for the segmentation algorithm and instead
focuses on an easy to use interface. The following is a list of the available
options:

```
usage: fTagTamed smoothing_lambda tag_offset input_stl_file output_tag_file [output_msh_file]

  smoothing_lambda: the higher the fewer the number of segments (floating-point in [0, 1])
  tag_offset:       the initial tag from which to count from (strictly positive integer)
  input_stl_file:   the file describing the surface mesh to be tagged (STL)
  output_tag_file:  the file to which the list of tags will be written to (Plain Text)
  output_msh_file:  the file to which the tagged surface mesh will be written to (MSH 2.2)
```

If you wish to fine-tune any of the segmentation algorithm parameters, we
encourage you to inspect and edit the (very short) source code in
`src/fTagTamed.cpp`. All contributions are welcome.
