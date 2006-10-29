// 3D mesh code from Figs. 6.13, 6.15, 6.78 on pp.296, 298, 348
// of Hill, F.S. "Computer Graphics Using
// OpenGL", 2nd edition, Prentice Hall, NJ, 2001.
// Modified Sept. 2002 by B.G. Nickerson.

#ifndef MATH_H
#define MATH_H

#include<GL/glut.h>
#include<math.h>
#include<iostream.h>
#include<fstream.h>


//<<Support Classes for Mesh>>>

/** Point2 class for 2D points with real coordinates */ 
class Point2{ 
public: 
	float x,y;
	void set(float dx, float dy){x = dx; y = dy;}
	void set(Point2& p){ x = p.x; y = p.y;} 
	Point2(float xx, float yy){x = xx; y = yy;}
	Point2(){x = y = 0;}
};

/** a polyline is a num plus an array of points */
class PolyLine{ 
public:
	int num;
	Point2 pt[80]; //may need larger arrays in some circumstances
	PolyLine(){num = 0;}
};

/** Point3 class */
class Point3{ 
public: 
	float x,y,z;
	void set(float dx, float dy, float dz){x = dx; y = dy; z = dz;}
	void set(Point3& p){x = p.x; y = p.y; z = p.z;} 	
 Point3(float xx,     float yy, float zz){x = xx; y = yy; z = zz;}
	Point3(){x = y = z = 0;}
	void build4tuple(float v[])
	{// load 4-tuple with this color: v[3] = 1 for homogeneous
		v[0] = x; v[1] = y; v[2] = z; v[3] = 1.0f;
	}	
};

/** Vector3 class */
class Vector3{ 
public: 
	float x,y,z;
	void set(float dx, float dy, float dz){ x = dx; y = dy; z = dz;} 
	void set(Vector3& v){ x = v.x; y = v.y; z = v.z;}
	void flip(){x = -x; y = -y; z = -z;} // reverse this vector
	void setDiff(Point3& a, Point3& b)//set to difference a - b
	{ x = a.x - b.x; y = a.y - b.y; z = a.z - b.z;}
	void normalize()//adjust this vector to unit length
	{		
		double sizeSq = x * x + y * y + z * z;
		if(sizeSq < 0.0000001)
		{
			cerr << "\nnormalize() sees vector (0,0,0)!";
			return; // does nothing to zero vectors;
		}
		float scaleFactor = 1.0/(float)sqrt(sizeSq);
		x *= scaleFactor; y *= scaleFactor; z *= scaleFactor;
	}
	Vector3(float xx, float yy, float zz){x = xx; y = yy; z = zz;}
	Vector3(const Vector3& v){x = v.x; y = v.y; z = v.z;}
	Vector3(){x = y = z = 0;} //default constructor
	Vector3 cross(Vector3 b) //return this cross b
	{
	   Vector3 c(y*b.z - z*b.y, z*b.x - x*b.z, x*b.y - y*b.x);
	   return c;
	}
	float dot(Vector3 b) // return this dotted with b
           {return x * b.x + y * b.y + z * b.z;}
};

/** VertexID class */
class VertexID {
public:
  int vertIndex;  // index of this vertex in the vertex list
  int normIndex;  // index of this vertex's normal
};

/** Face class */
class Face {
public:
  int nVerts; // number of vertices in this face
  VertexID * vert; // the list of vertex and normal indices
  Face(){nVerts = 0; vert = NULL;} // constructor
  ~Face(){delete[] vert; nVerts = 0;} // destructor
};

//###################### Mesh #######################
class Mesh{
   private:
	int numVerts;	// number of vertices in the mesh
	Point3* pt;	      // array of 3D vertices
	int numNormals;   // number of normal vectors for the mesh
	Vector3 *norm;    // array of normals 
	int numFaces; 	// number of faces in the mesh
	Face* face;	      // array of face data
	
   public:
	Mesh(); 		// constructor
	//        ~Mesh();                // destructor
	int readFile(char * fileName);  // to read in a filed mesh
	void draw();
	void freeMesh();
        void printMesh();
        void writeMesh(char * fname);
        int isEmpty(){ return (numVerts = 0) || (numFaces == 0) || (numNormals == 0);}
        void makeEmpty() { numVerts = numFaces = numNormals = 0;}
        Vector3 newell4(int indx[]);
};	

#endif
