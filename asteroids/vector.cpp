#include "vector.h"

vec3_t vec3_t::operator+=(vec3_t &pVec)
{
  vec3_t ret;

  ret = *this = *this + pVec;
  
  return ret;
}

vec3_t vec3_t::operator-=(vec3_t &pVec)
{
  vec3_t ret;
  
  ret = *this = *this - pVec;
  
  return ret;
}

vec3_t vec3_t::operator*=(vec3_t &pVec)
{
  vec3_t ret;
  
  ret = *this = *this * pVec;
  
  return ret;
}

vec3_t vec3_t::operator*=(float val)
{
  vec3_t ret;
  
  ret = *this = *this * val;
  
  return ret;
}

vec3_t vec3_t::operator/=(vec3_t &pVec)
{
  vec3_t ret;
  
  ret = *this = *this / pVec;
  
  return ret;
}

vec3_t vec3_t::operator/=(float val)
{
  vec3_t ret;
  
  ret = *this = *this / val;
  
  return ret;
}

void vec3_t::Normalize(void) 
{
  float length, len = 0;
  
  length = Length();
  
  if (length == 0)
    return;
  
  len = 1.0f / length;
  
  v[0] *= len;
  v[1] *= len;
  v[2] *= len;
}

float vec3_t::Length(void) 
{
  double length = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
  
  return (float) sqrt(length);
}

void vec3_t::Cross(vec3_t &p, vec3_t &q)
{
  v[0] = (p.v[1] * q.v[2]) - (p.v[2] * q.v[1]);
  v[1] = (p.v[2] * q.v[0]) - (p.v[0] * q.v[2]);
  v[2] = (p.v[0] * q.v[1]) - (p.v[1] * q.v[0]);
}

void vec3_t::Clamp(float min, float max)
{
  if (v[0] > max || v[0] < min)
    v[0] = 0;
  
  if (v[1] > max || v[1] < min)
    v[1] = 0;
  
  if (v[2] > max || v[2] < min)
    v[2] = 0;   
}

void vec3_t::RotateX(float amnt)
{
  float s = MySin(amnt);
  float c = MyCos(amnt);
  float y = v[1];
  float z = v[2];
  
  v[1] = (y * c) - (z * s);
  v[2] = (y * s) + (z * c);
}

void vec3_t::RotateY(float amnt)
{
  float s = MySin(amnt);
  float c = MyCos(amnt);
  float x = v[0];
  float z = v[2];
  
  v[0] = (x * c) + (z * s);
  v[2] = (z * c) - (x * s);
}

void vec3_t::RotateZ(float amnt)
{
  float s = MySin(amnt);
  float c = MyCos(amnt);
  float x = v[0];
  float y = v[1];
  
  v[0] = (x * c) - (y * s);
  v[1] = (y * c) + (x * s);
}

// test
float vec3_t::GetDistance(vec3_t &dest)
{
  float d1 = dest[0] - v[0];
  float d2 = dest[1] - v[1];
  float d3 = dest[2] - v[2];
  
  return (float) sqrt((d1 * d1) + (d2 * d2) + (d3 * d3));
}
