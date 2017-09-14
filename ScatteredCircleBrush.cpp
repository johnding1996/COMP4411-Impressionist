//
// ScatteredCircleBrush.cpp
//
// The implementation of Scattered Circle Brush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCircleBrush.h"

#include <math.h>

extern double drand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
	CircleBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove document is NULL\n");
		return;
	}

	// get the radius of circles
	int radius = pDoc->getSize() / 2;
	// 4 scattered circles
	for (int i = 0; i < 4; i++) {

		double distance = drand() * radius;
		double degInRad = 2 * drand() * M_PI;
		int randomX = cos(degInRad)*distance;
		int randomY = sin(degInRad)*distance;

		// generating new source and target
		Point newSource(source.x + randomX, source.y + randomY);
		Point newTarget(target.x + randomX, target.y + randomY);
		// call the circle brush funciton to draws
		CircleBrush::BrushMove(newSource, newTarget);
	}
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
}