//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source, double alphaValue)
{
	ImpressionistDoc* pDoc = GetDocument();

	GLubyte color[4];
	bool isInputColor = pDoc->getIsInputColor();
	// copy the color
	if (isInputColor) memcpy(color, pDoc->getColor(), 3);
	else memcpy(color, pDoc->GetOriginalPixel(source), 3);
	// set the alpha value
	color[3] = (GLubyte)(alphaValue * 255.0f);
	// use glColor4
	glColor4ubv(color);
}