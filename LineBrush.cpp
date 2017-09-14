//
// LineBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"
#include <cmath>

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// get line width
	int lineWidth = pDoc->getLineWidth();
	glLineWidth((float)lineWidth);

	// record the last target position for drawing lines with direction parallel to the brush direction
	lastTarget = target;

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove document is NULL\n");
		return;
	}

	// get size and alpha value
	int size = pDoc->getSize();
	int lineAngle;
	double alphaValue = pDoc->getAlphaValue();
	// switch the methods to decide line angle
	int strokeDirectionChoice = dlg->m_StrokeDirectionTypeChoice->value();
	switch (strokeDirectionChoice)
	{
	case SLIDER_OR_RIGHTMOUSE:
		// directly get
		lineAngle = pDoc->getLineAngle();
		break;
	case BRUSH_DIRECTION:
		// calculated from the trace
		lineAngle = pDoc->calcAngle(lastTarget, target);
		lastTarget = target;
		break;
	case GRADIENT:
		// calcualted form the gradient
		lineAngle = 90 + (int)(atan2(pDoc->GetGradientY(source), pDoc->GetGradientX(source)) * 180 / M_PI);
		if (lineAngle < 0) lineAngle = lineAngle + 360;
		break;
	default:
		break;
	}

	double degInRad = lineAngle * M_PI / 180.0;

	glBegin(GL_LINES);
		SetColor(source, alphaValue);
		// draw a line
		glVertex2d(-cos(degInRad)*size/2 + target.x, -sin(degInRad)*size / 2 + target.y);
		glVertex2d(cos(degInRad)*size / 2 + target.x, sin(degInRad)*size / 2 + target.y);

	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

