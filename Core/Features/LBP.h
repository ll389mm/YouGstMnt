// LBP.h: interface for the LBP class.
//
//////////////////////////////////////////////////////////////////////

#include <memory.h>
#include <stdio.h>
#include <math.h>

#define M_PI  3.14159265358979323846
#define bits  8       /* The number of bits */
#define predicate 1   /* Predicate 1 for the 3x3 neighborhood */

/* Compare a value pointed to by 'ptr' to the 'center' value and
* increment pointer. Comparison is made by masking the most
* significant bit of an integer (the sign) and shifting it to an
* appropriate position. */
#define compab_mask_inc(ptr,shift) {value |= ((unsigned int)(*center-*ptr-1) & 0x80000000)>>(31-shift); ptr++; }

/* Compare a value 'val' to the 'center' value. */
#define compab_mask(val,shift) {value |= ((unsigned int)(*center-(val)-1) & 0x80000000)>>(31-shift); }


typedef struct
{
	int x;
	int y;
} integerpoint;

typedef struct
{
	double x;
	double y;
} doublepoint;

class LBP  
{
public:
	integerpoint points[bits];  
	doublepoint offsets[bits];  

public:
	LBP();
	virtual ~LBP();

	void   calculate_points(void);
	double interpolate_at_ptr(char* upperLeft, int i, int columns);
    void   lbp_histogram(char* img, int rows, int columns, int* result, int interpolated);
	void   lbp_result(char* img, int rows, int columns, int**&result, int interpolated, int &height, int &width);

};



