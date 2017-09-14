//
// ScatteredHeartBrush.h
//
// The header file for Scattered Heart Brush.
//

#ifndef SCATTEREDHEARTBRUSH_H
#define SCATTEREDHEARTBRUSH_H
#include "HeartBrush.h"

class ScatteredHeartBrush : public HeartBrush
{
public:
	ScatteredHeartBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

	void BrushBegin(const Point source, const Point target);
	void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char* BrushName(void);
};

#endif