/*
   Copyright (C) 2000 Nate Miller nkmiller@calpoly.edu

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

   See gpl.txt for more information regarding the GNU General Public License.
*/
/*
   Need to format this to fit on 80 cols, but its a pain
*/
#ifndef VEC3_T_H
#define VEC3_T_H

#include <math.h>

class vec3_t
{
 public:
  vec3_t() {v[0] = v[1] = v[2] = 0;}
  vec3_t(float px, float py, float pz) {v[0] = px; v[1] = py; v[2] = pz;}
  vec3_t(const vec3_t &pVec) 
    {v[0] = pVec.v[0]; v[1] = pVec.v[1]; v[2] = pVec.v[2];}
  vec3_t(float *pVec) {v[0] = pVec[0]; v[1] = pVec[1]; v[2] = pVec[2];}
  
  vec3_t operator=(const vec3_t &pVec)
    {return vec3_t(v[0] = pVec.v[0], v[1] = pVec.v[1], v[2] = pVec.v[2]);}
  vec3_t operator=(float *ptr)
    {return vec3_t(v[0] = ptr[0], v[1] = ptr[1], v[2] = ptr[2]);}
  int operator==(vec3_t &pVec)
    {return (v[0] == pVec.v[0] && v[1] == pVec.v[1] && v[2] == pVec.v[2]);}
  int operator==(float *pVec)
    {return (v[0] == pVec[0] && v[1] == pVec[1] && v[2] == pVec[2]);}
  inline int operator!=(vec3_t &pVec)
    {return !(pVec == (*this));}
  inline int operator!=(float *pVec)
    {return !(pVec == (*this));}
  
  vec3_t operator+=(vec3_t &pVec);  
  vec3_t operator-=(vec3_t &pVec);
  vec3_t operator*=(vec3_t &pVec);
  vec3_t operator*=(float val);  
  vec3_t operator/=(vec3_t &pVec);
  vec3_t operator/=(float val);
  
  vec3_t operator+(vec3_t &pVec)
    {return vec3_t(v[0] + pVec.v[0], v[1] + pVec.v[1], v[2] + pVec.v[2]);}
  vec3_t operator-(vec3_t &pVec)
    {return vec3_t(v[0] - pVec.v[0], v[1] - pVec.v[1], v[2] - pVec.v[2]);}
  vec3_t operator*(vec3_t &pVec)
    {return vec3_t(v[0] * pVec.v[0], v[1] * pVec.v[1], v[2] * pVec.v[2]);}
  vec3_t operator*(float val)
    {return vec3_t(v[0] * val, v[1] * val, v[2] * val);}
  friend vec3_t operator*(float val, vec3_t v)
    {return vec3_t(v[0] * val, v[1] * val, v[2] * val);}
  vec3_t operator/(vec3_t &pVec)  
    {return vec3_t(v[0] / pVec.v[0], v[1] / pVec.v[1], v[2] / pVec.v[2]);}
  vec3_t operator/(float val)
    {return vec3_t(v[0] / val, v[1] / val, v[2] / val);}
  
  void Clear(void) {v[0] = v[1] = v[2] = 0;}
  void Normalize(void);
  float Length(void);
  float Dot(vec3_t &pVec)
    {return v[0] * pVec.v[0] + v[1] * pVec.v[1] + v[2] * pVec.v[2];}
  void Cross(vec3_t &p, vec3_t &q);
  
  void Set(float x, float y, float z) {v[0] = x; v[1] = y; v[2] = z;}
  
  float X(void) {return v[0];}
  float Y(void) {return v[1];}
  float Z(void) {return v[2];}
  void X(float nx) {v[0] = nx;}
  void Y(float ny) {v[1] = ny;}
  void Z(float nz) {v[2] = nz;}
  
  const float &operator[](int ndx) const {return v[ndx];}
  float &operator[](int ndx) {return v[ndx];}
  operator float*(void) {return v;}
  
  void Clamp(float min, float max);
  
  void RotateX(float amnt);
  void RotateY(float amnt);
  void RotateZ(float amnt);
  
  // temp
  float GetDistance(vec3_t &dest);
  
 protected:
  float v[3];
};

#endif
