// SPM.cpp: implementation of the SPM class.
//
//////////////////////////////////////////////////////////////////////
#include "SPM.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SPM::SPM()
{
	height = 0;
	width = 0;
    codesize = 200;//????
    level = 3;//
	spmData = 0;
}

SPM::~SPM()
{

}

void SPM::getSPM(int h, int w, int Tcodesize, int Tlevel, int *pyramid, int **tData)
{
	height = h;
	width = w;
	codesize = Tcodesize;
	level = Tlevel;
	
	int dim, len;
	int i, j, k, m, n, p, q;
	int blocks = 0;
	double wUnit, hUnit;
	int wb, we, hb, he;
	
    for (i = 0; i<level; i++)
	{
		blocks = blocks + pyramid[i] * pyramid[i];
	}
	dim = blocks * codesize;
	
	spmData = new double [dim];
	int *hist = new int [codesize];
	
	len = 0;
	for ( i = 0; i<level; i++)
	{
		hUnit = height / (1.0 * pyramid[i]);
		wUnit = width / (1.0 * pyramid[i]);
		
		for (j = 0; j<pyramid[i]; j++)
		{
			hb = int( j * hUnit );
			he = int( (j+1) * hUnit );
			for (k = 0; k<pyramid[i]; k++)
			{
				wb = int( k * wUnit );
				we = int( (k+1) * wUnit );
				p = 0;
                int *data = new int [(he-hb)*(we-wb)];
				for (m = hb; m<he; m++)
				{
					for (n = wb; n<we; n++)
					{
						data[p] = tData[m][n];
						p = p + 1;
					}
				}
				
				histogram(data, p, hist);
				
				for (q = 0; q<codesize; q++)
				{
					spmData[len] = hist[q];
					len = len + 1;
				}
				
				delete []data;
			}
		}
	}
	
	int pixels = (height*width);
	for ( i = 0; i<dim; i++)
	{
		spmData[i] = spmData[i] / pixels;		
	}
	
}

void SPM::histogram(int *data, int len, int *&hist)
{
	int i;
	for (i = 0;i <codesize; i++)
	{
		hist[i] = 0;
	}
	
	for (i = 0; i<len; i++)
	{
		hist[data[i]] = hist[data[i]] + 1 ;
	}
}
