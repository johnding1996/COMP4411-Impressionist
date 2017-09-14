//
// SharpenBrush.cpp
//
// The implementation of Sharpen Brush. It is a kind of ImpBrush. 
// It will sharpen the image in the brush region.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "SharpenBrush.h"

const int SharpenBrush::SharpenMask[5][5] =
{
	{-1, -1, -1, -1, -1},
	{-1, 2, 2, 2, -1},
	{-1, 2, 8, 2, -1},
	{-1, 2, 2, 2, -1},
	{-1, -1, -1, -1, -1}
};

SharpenBrush::SharpenBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void SharpenBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	// Set to one, we want to get color per pixel
	glPointSize(1.0f);

	BrushMove(source, target);
}

void SharpenBrush::SetColor(const Point source, double alphaValue)
{
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte	 sourceColor[3];
	GLubyte	 color[4];
	double tempColor[3] = {0.0,0.0,0.0};

	for (int i = -2; i <= 2; i++) {
		for (int j = -2; j <= 2; j++) {
			memcpy(sourceColor, pDoc->GetOriginalPixel(source.x + i, source.y + j), 3);
			for (int n = 0; n < 3; n++) tempColor[n] += (double)(SharpenMask[i+2][j+2]) * (double)(sourceColor[n]);
		}
	}
	for (int n = 0; n < 3; n++) color[n] = (GLubyte)(min(max((int)(tempColor[n]/8.0),0),255));
	color[3] = (GLubyte)(alphaValue * 255.0f);
	glColor4ubv(color);
}

void SharpenBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("PointBrush::BrushMove document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	double alphaValue = pDoc->getAlphaValue();

	glBegin(GL_POINTS);

	for (int i = -size / 2; i <= size / 2; i++) {
		for (int j = -size / 2; j <= size / 2; j++) {
			SetColor(Point(source.x + i, source.y + j),alphaValue);
			glVertex2d(target.x + i, target.y + j);
		}
	}

	glEnd();
}

void SharpenBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

