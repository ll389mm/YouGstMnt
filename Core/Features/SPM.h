// SPM.h: interface for the SPM class.
//
//////////////////////////////////////////////////////////////////////


class SPM  
{
public:
	int height;
	int width;
	int codesize;
	int level;
	double *spmData;
	
public:
	SPM( );
	virtual ~SPM( );
	
	void getSPM(int h, int w, int Tcodesize, int Tlevel, int *pyramid, int **tData);
	void histogram(int *data, int len, int *&hist);

};


