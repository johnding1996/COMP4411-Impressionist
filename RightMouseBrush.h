//
// RightMouseBrush.h
//
// The header file for Right Mouse Brush. 
//

#ifndef RIGHTMOUSEBRUSH_H
#define RIGHTMOUSEBRUSH_H

#include "ImpBrush.h"

class RightMouseBrush : public ImpBrush
{
public:
	RightMouseBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);

private:
	Point rightMouseOrigion;
};

#endif