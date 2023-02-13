#include "mesh.h"

int main()
{
  mesh *m;
  m = from_file("examples/hand-hybrid.off");
  print_mesh(m);
}