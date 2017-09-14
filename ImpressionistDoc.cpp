// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "CircleBrush.h"
#include "LineBrush.h"
#include "ScatteredPointBrush.h"
#include "ScatteredCircleBrush.h"
#include "ScatteredLineBrush.h"
#include "RightMouseBrush.h"
#include "HeartBrush.h"
#include "ScatteredHeartBrush.h"
#include "SharpenBrush.h"

#include <cmath>
#include <algorithm>


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

extern int irand(int);
//---------------------------------------------------------
// Sobel masks to calculate the gradients
//---------------------------------------------------------
const int ImpressionistDoc::sobelMaskX[3][3] = 
{
	{ -1, 0, 1 },
	{ -2, 0, 2 },
	{ -1, 0, 1 }

};
const int ImpressionistDoc::sobelMaskY[3][3] =
{
	{ 1, 2, 1 },
	{ 0, 0, 0 },
	{ -1, -2, -1 }

};

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;
	m_ucLastPainting = NULL;

	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS] = new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES] = new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]	= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS] = new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]	= new ScatteredLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES] = new ScatteredCircleBrush( this, "Scattered Circles" );
	ImpBrush::c_pBrushes[BRUSH_HEARTS] = new HeartBrush(this, "Hearts");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_HEARTS] = new HeartBrush(this, "Scattered Hearts");
	ImpBrush::c_pBrushes[BRUSH_SHARPEN] = new SharpenBrush(this, "Sharpen");
	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];
	m_pRightMouseBrush = new RightMouseBrush(this, "Right Mouse");

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	// activate the sliders when using line or heart brushes
	if (type == BRUSH_LINES || type == BRUSH_SCATTERED_LINES || type == BRUSH_HEARTS || type == BRUSH_SCATTERED_HEARTS) {
		m_pUI->m_LineWidthSlider->activate();
		m_pUI->m_LineAngleSlider->activate();
		m_pUI->m_StrokeDirectionTypeChoice->activate();
	}
	else {
		m_pUI->m_LineWidthSlider->deactivate();
		m_pUI->m_LineAngleSlider->deactivate();
		m_pUI->m_StrokeDirectionTypeChoice->deactivate();
	}
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}

//---------------------------------------------------------
// Get the parameters of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

int ImpressionistDoc::getLineWidth()
{
	return m_pUI->getLineWidth();
}

int ImpressionistDoc::getLineAngle()
{
	return m_pUI->getLineAngle();
}

double ImpressionistDoc::getAlphaValue()
{
	return m_pUI->getAlphaValue();
}

bool ImpressionistDoc::getIsInputColor()
{
	return m_pUI->getIsInputColor();
}

GLubyte* ImpressionistDoc::getColor()
{
	return m_pUI->getColor();
}
bool ImpressionistDoc::getCanUndo()
{
	return m_pUI->getCanUndo();
}
int ImpressionistDoc::getSpacing()
{
	return m_pUI->getSpacing();
}
bool ImpressionistDoc::getIsSizeRandom()
{
	return m_pUI->getIsSizeRandom();
}
//---------------------------------------------------------
// Set the parameters of the brush.
//---------------------------------------------------------
void ImpressionistDoc::setSize(int size)
{
	return m_pUI->setSize(size);
}

void ImpressionistDoc::setLineWidth(int lineWidth)
{
	return m_pUI->setLineWidth(lineWidth);
}

void ImpressionistDoc::setLineAngle(int lineAngle)
{
	return m_pUI->setLineAngle(lineAngle);
}

void ImpressionistDoc::setAlphaValue(double alphaValue)
{
	return m_pUI->setAlphaValue(alphaValue);
}

void ImpressionistDoc::setIsInputColor(bool isInputColor)
{
	if (isInputColor) {
		m_pUI->m_colorRed->activate();
		m_pUI->m_colorGreen->activate();
		m_pUI->m_colorBlue->activate();
	}
	else {
		m_pUI->m_colorRed->deactivate();
		m_pUI->m_colorGreen->deactivate();
		m_pUI->m_colorBlue->deactivate();
	}
	return m_pUI->setIsInputColor(isInputColor);
}

void ImpressionistDoc::setCanUndo(bool canUndo)
{
	if (canUndo) {
		m_pUI->m_undoButton->activate();
	}
	else {
		m_pUI->m_undoButton->deactivate();
	}
	return m_pUI->setCanUndo(canUndo);
}

void ImpressionistDoc::setSpacing(int spacing)
{
	return m_pUI->setSpacing(spacing);
}

void ImpressionistDoc::setIsSizeRandom(bool isSizeRandom)
{
	return m_pUI->setIsSizeRandom(isSizeRandom);
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;
	if ( m_ucLastPainting ) delete[] m_ucLastPainting;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);
	m_ucLastPainting = new unsigned char[width*height * 3];
	memset(m_ucLastPainting, 0, width*height * 3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//----------------------------------------------------------------
// Swap the content of original view to the painting view.
//----------------------------------------------------------------
void ImpressionistDoc::swapCanvas()
{
	std::swap(m_ucBitmap, m_ucPainting);
	m_pUI->m_origView->refresh();
	m_pUI->m_paintView->refresh();
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//------------------------------------------------------------------
// Get the color of the pixel in the painting image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetPaintingPixel(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_nWidth)
		x = m_nWidth - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_nHeight)
		y = m_nHeight - 1;

	return (GLubyte*)(m_ucPainting + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetPaintingPixel(const Point p)
{
	return GetPaintingPixel(p.x, p.y);
}

//----------------------------------------------------------------
// Calculate the gradient in X and Y by Sobel Mask
//----------------------------------------------------------------
double ImpressionistDoc::GetGradientX(const Point source)
{
	double Gx = 0.0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Gx += sobelMaskX[i][j] * GetPixelIntensity(source.x + j - 1,
				source.y - i + 1);
		}
	}
	return Gx;
}

double ImpressionistDoc::GetGradientY(const Point source)
{
	double Gy = 0.0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Gy += sobelMaskY[i][j] * GetPixelIntensity(source.x + j - 1,
				source.y - i + 1);
		}
	}
	return Gy;
}
//----------------------------------------------------------------
// Get the intensity of the pixel in the original image at point p
//----------------------------------------------------------------
int ImpressionistDoc::GetPixelIntensity(int x, int y)
{
	unsigned char color[3];
	memcpy(color, GetOriginalPixel(x,y), 3);
	return (0.299*color[0] + 0.587*color[1] + 0.144*color[2]);
}

//----------------------------------------------------------------
// Helper functions to calculate the distance and angle of two points
//----------------------------------------------------------------

int ImpressionistDoc::calcDistance(const Point a, const Point b)
{
	return (int)sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

int ImpressionistDoc::calcAngle(const Point a, const Point b)
{
	double degInRad = atan2((b.y - a.y), (b.x - a.x));
	int deg = (int)(degInRad * 180 / M_PI);
	if (deg < 0) deg = deg + 360;
	return deg;
}

//----------------------------------------------------------------
// Update the last painting bitmap so that enable undo function
//----------------------------------------------------------------
void ImpressionistDoc::updateLastPainting()
{
	setCanUndo(TRUE);
	memcpy(m_ucLastPainting, m_ucPainting, m_nPaintWidth*m_nPaintHeight * 3);
}

void ImpressionistDoc::undoPainting()
{
	setCanUndo(FALSE);
	memcpy(m_ucPainting, m_ucLastPainting, m_nPaintWidth*m_nPaintHeight * 3);
	m_pUI->m_paintView->refresh();
}

void ImpressionistDoc::clearLastPainting()
{
	setCanUndo(FALSE);
	memset(m_ucLastPainting, 0, m_nPaintWidth*m_nPaintHeight * 3);
}

void ImpressionistDoc::autoPaint() {
	return m_pUI->m_paintView->autoPaint();
}