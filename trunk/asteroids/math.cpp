// 3D mesh code from Figs. 6.13, 6.15, 6.78 on pp.296, 298, 348
// of Hill, F.S. "Computer Graphics Using
// OpenGL", 2nd edition, Prentice Hall, NJ, 2001.
// Modified Sept. 2002 by B.G. Nickerson.

#include "math.h"

Mesh::Mesh(){
  numVerts = numFaces = numNormals = 0; 
  pt = NULL; norm = NULL; face = NULL;
}

/** uses OpenGL to draw this mesh */
void Mesh:: draw(){ 
  for(int f = 0; f < numFaces; f++) // draw each face
  {
    glBegin(GL_POLYGON);
    for(int v = 0; v < face[f].nVerts; v++) // for each one..
    {
      int in = face[f].vert[v].normIndex ; // index of this normal
      int iv =  face[f].vert[v].vertIndex ; // index of this vertex
      glNormal3f(norm[in].x, norm[in].y, norm[in].z);
      glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
    }
    glEnd();
  }
}

int Mesh:: readFile(char * fileName){
  fstream infile;
  infile.open(fileName, ios::in);
  if(infile.fail()) return -1; // error - can't open file
  if(infile.eof())  return -1; // error - empty file
  infile >> numVerts >> numNormals >> numFaces;
  pt = new Point3[numVerts];
  norm = new Vector3[numNormals];
  face = new Face[numFaces];
  //check that enough memory was found:
  if( !pt || !norm || !face)return -1; // out of memory
  for(int p = 0; p < numVerts; p++) // read the vertices
	infile >> pt[p].x >> pt[p].y >> pt[p].z;
  for(int n = 0; n < numNormals; n++) // read the normals
	infile >> norm[n].x >> norm[n].y >> norm[n].z;
  for(int f = 0; f < numFaces; f++)// read the faces
  {
    infile >> face[f].nVerts;
    int nv = face[f].nVerts;  // no. of vertices in this face
    face[f].vert = new VertexID[nv];
    for(int i = 0; i < nv; i++)  // read vertex indices for this face
      infile >> face[f].vert[i].vertIndex;
    for(int i = 0; i < nv; i++)  // read normal indices for this face
      infile >> face[f].vert[i].normIndex;
  } 
  return 0; // success
} 

/** prints mesh to stdout */
void Mesh:: printMesh(void) { 
  if(numVerts == 0 || numNormals   == 0 || numFaces == 0) return; //empty
  cout << numVerts << " " << numNormals << " " << numFaces << "\n";
  // write the vertex and vertex normal list
  for(int i = 0; i < numVerts; i++)
    cout << pt[i].x   << " " << pt[i].y   << " " << pt[i].z << "\n";
  for(int ii = 0; ii < numNormals; ii++)
    cout  << norm[ii].x << " " << norm[ii].y << " " << norm[ii].z << "\n";
  // write the face data
  for(int f = 0; f < numFaces; f++)
  {
    int n = face[f].nVerts;
    cout << n << "\n";
    for(int v = 0; v < n; v++)// write vertex indices for this face
      cout << face[f].vert[v].vertIndex << " ";	
    cout << "\n";
    for(int k = 0; k < n; k++)	// write normal indices for this face 
      cout << face[f].vert[k].normIndex << " "; 
    cout << "\n";
  }
}

/** writes mesh */
void Mesh:: writeMesh(char * fname)
{ // write this mesh object into a new Chapter 6 format file.
  if(numVerts == 0 || numNormals   == 0 || numFaces == 0) return; //empty
  fstream outStream(fname, ios ::out); // open the output stream
  if(outStream.fail()) {cout << "can't make new file: " << fname << endl; return;}
  outStream << numVerts << " " << numNormals << " " << numFaces << "\n";
  // write the vertex and vertex normal list
  for(int i = 0; i < numVerts; i++)
    outStream << pt[i].x   << " " << pt[i].y   << " " << pt[i].z << "\n";
  for(int ii = 0; ii < numNormals; ii++)
    outStream  << norm[ii].x << " " << norm[ii].y << " " << norm[ii].z << "\n";
  // write the face data
  for(int f = 0; f < numFaces; f++)
  {
    int n = face[f].nVerts;
    outStream << n << "\n";
    for(int v = 0; v < n; v++)// write vertex indices for this face
      outStream << face[f].vert[v].vertIndex << " ";	
    outStream << "\n";
    for(int k = 0; k < n; k++)	// write normal indices for this face 
      outStream << face[f].vert[k].normIndex << " "; 
    outStream << "\n";
  }
  outStream.close();
}

/** return the normalized normal to face with vertices */
/** pt[indx[0]],...,pt[indx[3]]. i.e. indx[] contains the four indices 
     into the vertex list to be used in the Newell calculation */
Vector3 Mesh :: newell4(int indx[]) { 
  Vector3 m;
  for(int i = 0; i < 4 ; i++)
  {
    int next = (i== 3) ? 0 : i + 1; // which index is next?
    int f = indx[i], n = indx[next]; // names for the indices in the pair
    m.x += (pt[f].y - pt[n].y) * (pt[f].z + pt[n].z);
    m.y += (pt[f].z - pt[n].z) * (pt[f].x + pt[n].x);
    m.z += (pt[f].x - pt[n].x) * (pt[f].y + pt[n].y);
  }
  m.normalize();
  return m;
}

int math::RGBpixmap::B(float x, float y, float z){
  return ((int)(5*x) + (int)(5*y) + (int) (5*z))%2;
}

void math::RGBpixmap::setTexture(GLuint textureName){
	glBindTexture(GL_TEXTURE_2D,textureName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,nCols,nRows,0, GL_RGB,
               GL_UNSIGNED_BYTE, pixel);
}

int math::RGBpixmap::readBMPFile(string fname) 
{  // Read into memory an mRGB image from an uncompressed BMP file.
	// return 0 on failure, 1 on success
	inf.open(fname.c_str(), ios::in|ios::binary); //read binary char's
	if(!inf){ cout << " can't open file: " << fname << endl; return 0;}
	int k, row, col, numPadBytes, nBytesInRow;
	// read the file header information
	char ch1, ch2;
	inf.get(ch1); inf.get(ch2); //type: always 'BM'
	ulong fileSize =      getLong();
	ushort reserved1 =    getShort();    // always 0
	ushort reserved2= 	getShort();     // always 0 
	ulong offBits =		getLong(); // offset to image - unreliable
	ulong headerSize =     getLong();     // always 40
	ulong numCols =		getLong(); // number of columns in image
	ulong numRows = 		getLong(); // number of rows in image
	ushort planes=    	getShort();      // always 1 
	ushort bitsPerPixel=   getShort();    //8 or 24; allow 24 here
	ulong compression =    getLong();      // must be 0 for uncompressed 
	ulong imageSize = 	getLong();       // total bytes in image 
	ulong xPels =    	getLong();    // always 0 
	ulong yPels =    	getLong();    // always 0 
	ulong numLUTentries = getLong();    // 256 for 8 bit, otherwise 0 
	ulong impColors = 	getLong();       // always 0 
	if(bitsPerPixel != 24) 
	{ // error - must be a 24 bit uncompressed image
		cout << "not a 24 bit/pixelimage, or is compressed!\n";
		inf.close(); return 0;
	} 
	//add bytes at end of each row so total # is a multiple of 4
	// round up 3*numCols to next mult. of 4
	nBytesInRow = ((3 * numCols + 3)/4) * 4;
	numPadBytes = nBytesInRow - 3 * numCols; // need this many
	nRows = numRows; // set class's data members
	nCols = numCols;
        pixel = new RGB[nRows * nCols]; //make space for array
	if(!pixel) return 0; // out of memory!
	long count = 0;
	char dum;
	for(row = 0; row < nRows; row++) // read pixel values
	{
		for(col = 0; col < nCols; col++)
		{
			char r,g,b;
			inf.get(b); inf.get(g); inf.get(r); //read bytes
			pixel[count].r = r; //place them in colors
			pixel[count].g = g;
			pixel[count++].b = b;
		}
   		for(k = 0; k < numPadBytes ; k++) //skip pad bytes at row's end
			inf >> dum;
	}
	inf.close(); return 1; // success
}


