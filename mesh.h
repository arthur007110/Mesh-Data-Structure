#ifndef MESH
#define MESH

#include <stdio.h>

typedef struct vertex
{
  float x;
  float y;
  float z;
} vertex;

typedef struct face
{
  int vertices_indexes[4];
} face;

typedef struct mesh
{
  int num_vertices;
  int num_faces;
  vertex *vertices;
  face *faces;
} mesh;

mesh *from_file(char *filename);
mesh *init_mesh();
char *read_line(FILE *arq, int attribute);
void read_vertices(FILE *arq, mesh *m);
void read_faces(FILE *arq, mesh *m);
void print_vertices(mesh *m);
void print_faces(mesh *m);
void print_mesh(mesh *m);

#endif