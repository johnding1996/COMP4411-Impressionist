//
// RightMouseBrush.cpp
//
// The implementation of Right Mouse Brush. It is a kind of ImpBrush.
// The right mouse brush is an implementation of the red direction line when we drag the right mouse key

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "RightMouseBrush.h"

RightMouseBrush::RightMouseBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void RightMouseBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// set line width to minimum
	glLineWidth(1.0f);
	// record the origion
	rightMouseOrigion = target;
	BrushMove(source, target);
}

void RightMouseBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove document is NULL\n");
		return;
	}
	// color red
	GLubyte red[3] = { 255, 0, 0 };

	glBegin(GL_LINES);
		glColor3ubv(red);
		//draw line connecting origion and present position
		glVertex2d(rightMouseOrigion.x, rightMouseOrigion.y);
		glVertex2d(target.x, target.y);
	glEnd();
}

void RightMouseBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

