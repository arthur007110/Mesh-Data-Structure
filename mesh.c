#include <stdio.h>
#include <stdlib.h>
#include "mesh.h"

mesh *init_mesh()
{
    mesh *m = malloc(sizeof(mesh));
    m->num_vertices = 0;
    m->num_faces = 0;
    m->vertices = NULL;
    m->faces = NULL;
    return m;
}

mesh *from_file(char *filename)
{
    mesh *m = init_mesh();
    printf("Reading file: %d\n", m->num_faces);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return NULL;
    }

    char *extension = read_line(file, 0);
    if (extension[0] != 'O' || extension[1] != 'F' || extension[2] != 'F' || extension[3] != '\0')
    {
        printf("Error: File is not an OFF file.\n");
        return NULL;
    }

    int vertex_amount = atoi(read_line(file, 1));
    int faces_amount = atoi(read_line(file, 1));
    int edges_amount = atoi(read_line(file, 1));

    if (edges_amount != 0)
    {
        printf("Error: File with edges are not supported yet.\n");
        return NULL;
    }

    m->num_vertices = vertex_amount;
    m->num_faces = faces_amount;

    read_vertices(file, m);
    read_faces(file, m);

    return m;
}

void read_vertices(FILE *arq, mesh *m)
{
    m->vertices = malloc(sizeof(vertex) * m->num_vertices);
    int i;
    for (i = 0; i < m->num_vertices; i++)
    {
        m->vertices[i].x = atof(read_line(arq, 1));
        m->vertices[i].y = atof(read_line(arq, 1));
        m->vertices[i].z = atof(read_line(arq, 1));
    }
}

void read_faces(FILE *arq, mesh *m)
{
    m->faces = malloc(sizeof(face) * m->num_faces);
    int i;
    for (i = 0; i < m->num_faces; i++)
    {
        int vertex_in_face = atoi(read_line(arq, 1));
        for (int j = 0; j < vertex_in_face; j++)
        {
            m->faces[i].vertices_indexes[j] = atoi(read_line(arq, 1));
        }
        if (vertex_in_face == 3)
        {
            m->faces[i].vertices_indexes[3] = -1;
        }
    }
}

char *read_line(FILE *arq, int is_attribute)
{
    char *buffer = malloc(sizeof(char) * 256);
    int i;
    for (i = 0; i < 256; i++)
    {
        buffer[i] = fgetc(arq);
        if (buffer[i] == ' ' && is_attribute == 1)
        {
            buffer[i] = '\0';
            break;
        }
        else if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            break;
        }
    }
    return buffer;
}

void print_vertices(mesh *m)
{
    printf("Vertices: %d\n", m->num_vertices);
    for (int i = 0; i < m->num_vertices; i++)
    {
        printf("Vertex %d: %f %f %f\n", i, m->vertices[i].x, m->vertices[i].y, m->vertices[i].z);
    }
}

void print_faces(mesh *m)
{
    printf("Faces: %d\n", m->num_faces);
    for (int i = 0; i < m->num_faces; i++)
    {
        printf("Face %d: ", i);
        for (int j = 0; j < 4; j++)
        {
            if (m->faces[i].vertices_indexes[j] != -1)
            {
                printf("%d ", m->faces[i].vertices_indexes[j]);
            }
        }
        printf("\n");
    }
}

void print_mesh(mesh *m)
{
    print_vertices(m);
    print_faces(m);
}