//
// ScatteredLineBrush.cpp
//
// The implementation of Scattered Line Brush. It is a kind of LineBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLineBrush.h"

extern int irand(int);

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
	LineBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// set the linewidth before brush move function
	int lineWidth = pDoc->getLineWidth();
	glLineWidth((float)lineWidth);

	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove document is NULL\n");
		return;
	}

	// get the size
	int size = pDoc->getSize();

	// 4 scattered lines
	for (int i = 0; i < 4; i++) {

		int randomX = irand(size) + (-size / 2);
		int randomY = irand(size) + (-size / 2);

		// generating new source and new target
		Point newSource(source.x + randomX, source.y + randomY);
		Point newTarget(target.x + randomX, target.y + randomY);

		// call the line brush move function to draw
		LineBrush::BrushMove(newSource, newTarget);
	}
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
}