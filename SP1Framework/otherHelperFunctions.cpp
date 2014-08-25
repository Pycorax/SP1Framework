#include "otherHelperFunctions.h"
#include <sstream>

using std::ostringstream;

void newSetConsoleSize(COORD size)
{
	newSetConsoleSize(size.X, size.Y);
}

void newSetConsoleSize(int x, int y)
{
	ostringstream oss;
	oss << "mode " << x << "," << y;

	system(oss.str().c_str());
}