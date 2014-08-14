#include "Quad.h"

float Quad::easeIn (float t,float b , float c, float d) {
  t /= d;
	return c*t*t + b;
}
float Quad::easeOut(float t,float b , float c, float d) {
  t /= d;
	return -c *t*(t-2) + b;
}

float Quad::easeInOut(float t,float b , float c, float d) {
	if ((t/=d/2) < 1) return ((c/2)*(t*t)) + b;
  // TODO I changed this... not sure if it's correct. It used to be t-- instead of t-1.
	return -c/2 * (((t-2)*(t-1)) - 1) + b;
	/*
	originally return -c/2 * (((t-2)*(--t)) - 1) + b;
	
	I've had to swap (--t)*(t-2) due to diffence in behaviour in 
	pre-increment operators between java and c++, after hours
	of joy
	*/
	
}