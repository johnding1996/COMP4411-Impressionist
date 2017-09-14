//
// ScatteredHeartBrush.cpp
//
// The implementation of Scattered Heart Brush. It is a kind of HeartBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredHeartBrush.h"

extern int irand(int);

ScatteredHeartBrush::ScatteredHeartBrush(ImpressionistDoc* pDoc, char* name) :
	HeartBrush(pDoc, name)
{
}

void ScatteredHeartBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void ScatteredHeartBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}

	// set the size and alpha value
	int size = pDoc->getSize();
	double alphaValue = pDoc->getAlphaValue();

	// 3 scattered hearts
	for (int i = 0; i < 3; i++) {

		int randomX = irand(size) + (-size / 2);
		int randomY = irand(size) + (-size / 2);

		// generating new source and target
		Point newSource(source.x + randomX, source.y + randomY);
		Point newTarget(target.x + randomX, target.y + randomY);
		// call the heart brush funciton to draw
		HeartBrush::BrushMove(newSource, newTarget);
	}
}

void ScatteredHeartBrush::BrushEnd(const Point source, const Point target)
{
}