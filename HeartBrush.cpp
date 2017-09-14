#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "HeartBrush.h"

#include <cmath>
#include <iostream>

using namespace std;

extern double drand();

HeartBrush::HeartBrush(ImpressionistDoc* pDoc, char* name) : 
	ImpBrush(pDoc, name)
{

}


void HeartBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// record the last target position for drawing lines with direction parallel to the brush direction
	lastTarget = target;
	BrushMove(source, target);
}

void HeartBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	if (pDoc == NULL) {
		printf("HeartBrush::BrushMove  document is NULL\n");
		return;
	}

	// get size and alpha value
	int size = pDoc->getSize();
	double alphaValue = pDoc->getAlphaValue();
	int lineAngle;

	// switch the methods to decide line angle
	// the same as line brush
	int strokeDirectionChoice = dlg->m_StrokeDirectionTypeChoice->value();
	switch (strokeDirectionChoice)
	{
	case SLIDER_OR_RIGHTMOUSE:
		lineAngle = pDoc->getLineAngle();
		break;
	case BRUSH_DIRECTION:
		lineAngle = pDoc->calcAngle(lastTarget, target);
		lastTarget = target;
		break;
	case GRADIENT:
		lineAngle = 90 + (int)(atan2(pDoc->GetGradientY(source), pDoc->GetGradientX(source)) * 180 / M_PI);
		if (lineAngle < 0) lineAngle = lineAngle + 360;
		break;
	default:
		break;
	}

	double deg = (lineAngle * M_PI) / 180;

	glBegin(GL_TRIANGLE_FAN);

		SetColor(source, alphaValue);

		/*
		Graph function:
		(x^2 + y^2 - 1)^3 - x^2*y^3 = 0
		=> y^2 - y*cbrt(x^2) + x^2 - 1 = 0
		*/
		// learn from website :: https://www.snip2code.com/Snippet/159660/Draw-heart-shape-in-dumb-way-with-Opengl
		for (double x = -1.139; x <= 1.139; x += 0.001)
		{
			double delta = cbrt(x*x) * cbrt(x*x) - 4 * x*x + 4;
			double y1 = (cbrt(x*x) + sqrt(delta)) / 2;
			double y2 = (cbrt(x*x) - sqrt(delta)) / 2;
			double x1p = x*cos(deg) - y1*sin(deg);
			double y1p = x*sin(deg) + y1*cos(deg);
			double x2p = x*cos(deg) - y2*sin(deg);
			double y2p = x*sin(deg) + y2*cos(deg);
			// resize the heart
			glVertex2d(target.x + x1p/1.139*(size/2), target.y + y1p/1.139*(size/2));
			glVertex2d(target.x + x2p/1.139*(size/2), target.y + y2p/1.139*(size/2));
		}

	glEnd();
	glFlush();
}

void HeartBrush::BrushEnd(const Point source, const Point target) {}