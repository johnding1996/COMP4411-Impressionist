//
// ScatteredPointBrush.cpp
//
// The implementation of Scattered Point Brush. It is a kind of PointBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"

extern int irand(int);

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
	PointBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glPointSize((float)1.0); // Set the point size to minimum

	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}

	// get the size and alpha value
	int size = pDoc->getSize();
	double alphaValue = pDoc->getAlphaValue();
	// the number of points should be propotional to the area
	for (int i = 0; i < 1 + size*size/6; i++) {

		int randomX = irand(size) + (-size / 2);
		int randomY = irand(size) + (-size / 2);

		// generating new source and target
		Point newSource(source.x + randomX, source.y + randomY);
		Point newTarget(target.x + randomX, target.y + randomY);

		//call the point brush funciton to draw
		PointBrush::BrushMove(newSource, newTarget);
	}
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
}