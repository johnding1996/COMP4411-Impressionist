//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include <cmath>


CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove document is NULL\n");
		return;
	}

	// set radius and alpha value
	int radius = pDoc->getSize() / 2;
	double alphaValue = pDoc->getAlphaValue();

	glBegin(GL_TRIANGLE_FAN);
		SetColor(source, alphaValue);

		// draw 360 trangular fans
		for (int i = 0; i < 360; i++)
		{
			double degInRad = i * M_PI / 180.0;
			glVertex2d(cos(degInRad)*radius + target.x, sin(degInRad)*radius + target.y);
		}
	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
}