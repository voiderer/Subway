#include "Structure.h"
#include "stdafx.h"
COLORREF ConvertToColor(long num)
{
	int r = 0xFF & num;
	int g = 0xFF00 & num;
	g >>= 8;
	int b = 0xFF0000 & num;
	b >>= 16;
	return RGB(r, g, b);
}