//Program to calculate Area of a Polygon

/*
Given the coordinates of the vertices of a convex polygon, calculate its area and Perimeter.
Subdivide it into triangles and calculate the area of each Triangle with Heron's formula.
Requires data file pvert.txt containing coordinates of each vertex.
Example of data for a polygon with 5 vertices:

3 7 6 4 3 -2 -6 1 -6 7
*/

#include <STDIO.H>
#include <STDLIB.H>
#include <MATH.H>

#define MAX_VERT 50

enum Cordinate
{
    x = 0,
    y = 1,
    z = 2
};

struct Triangle
{
    double v1[2];
    double v2[2];
    double v3[2];
};

double HeronsArea(Triangle tri);
double Perimeter(double* vertices, int size);
double SideLength(double* p1, double* p2);


// calculate length of side
double SideLength(double* p1, double* p2)
{
    double dx = p1[x] - p2[x];
    double dy = p1[y] - p2[y];
    return sqrt(dx*dx + dy*dy);
}

// calculate Triangle area with Heron's formula
double HeronsArea(Triangle tri)
{
    double s1 = SideLength(tri.v1, tri.v2);
    double s2 = SideLength(tri.v2, tri.v3);
    double s3 = SideLength(tri.v3, tri.v1);

    double S = (s1 + s2 + s3) / 2;
    return sqrt(S*(S - s1)*(S - s2)*(S - s3));
}

// calculate polygon Perimeter
double Perimeter(double* vertices, int size)
{
    double perimeter = 0.0;
    // 1st vertex of the polygon
    pfirst[x] = vertices[0];
    pfirst[y] = vertices[1];
    // last vertex of polygon
    plast[x] = vertices[size-2];
    plast[y] = vertices[size-1];

    double p1[2], p2[2], pfirst[2], plast[2];
    // calculate Perimeter minus last side
    for (int idx = 0; idx <= size-3; idx += 2)
    {
        p1[x] = vertices[idx+0];
        p1[y] = vertices[idx+1];
        p2[x] = vertices[idx+2];
        p2[y] = vertices[idx+3];
        perimeter += SideLength(p1, p2);
    }
    // add last side
    perimeter += SideLength(plast, pfirst);

    return perimeter;
}

//  Public-domain function by Darel Rex Finley, 2006
double PolygonArea(double *X, double *Y, int points)
{
    double area = 0.0;
    for (int i=0, j=0; i < points; ++i)
    {
        if (++j == points)
        {
            j = 0;
        }
        area += (X[i] + X[j])*(Y[i] - Y[j]);
    }
    return area/2;
}

void main()
{
    double polygon_vertices[MAX_VERT] = { 0.0 };

    FILE *data;
    if ((data = fopen("pvert.txt", "r")) == NULL)
    {
        fprintf(stderr, "can't open data file");
        exit(EXIT_FAILURE);
    }

    // Read x-y coordinates of the vertices of the polygon from a file
    double xy;
    int xycount = 0;
    while (fscanf(data, "%lf", &xy) == 1)
    {
        polygon_vertices[xycount++] = xy;
    }
    fclose(data);

    // triangles in polygon = vertices - 2
    int triangles = (xycount / 2) - 2;
    putchar('        ');

    Triangle tri;
    double areaTriangle;
    double areaPolygon = 0;
    for (int index = 2, idx = 0; idx < triangles; index += 2, ++idx)
    {
        // Load vertices of a Triangle into struct.
        // 1st vertex of the polygon will be the 1st vertex of each Triangle.
        // index holds the starting index of each consecutive set of Triangle vertices after the 1st.
        tri.v1[x] = polygon_vertices[0];
        tri.v1[y] = polygon_vertices[1];
        tri.v2[x] = polygon_vertices[index+0];
        tri.v2[y] = polygon_vertices[index+1];
        tri.v3[x] = polygon_vertices[index+2];
        tri.v3[y] = polygon_vertices[index+3];

        // calculate the area of the Triangle
        areaTriangle = HeronsArea(tri);
        printf("Area of Triangle = %.2f            ", areaTriangle);

        // add Triangle area to polygon area
        areaPolygon += areaTriangle;
    }
    printf("   Area of polygon = %.2f            ", areaPolygon);

    // calculate the Perimeter of the polygon
    double perimeter = Perimeter(polygon_vertices, xycount);
    printf("Perimeter of polygon = %.2f  ", perimeter);
}