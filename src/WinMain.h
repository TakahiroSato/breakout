#ifndef		__WINMAIN_H__
#define		__WINMAIN_H__

#define NULL    0

#define		_USE_MATH_DEFINES
#define		W_WIDTH  800
#define		W_HEIGHT  600

#define		SAFE_DELETE(p)	if((p) != NULL) delete (p);\
							(p) = NULL

#define		SAFE_ARRAY_DELETE(p) if((p) != NULL) delete [] (p); \
								 (p) = NULL

#endif		__WINMAIN_H__