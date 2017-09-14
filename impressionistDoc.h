// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	swapCanvas();
	void	setBrushType(int type);			// called by the UI to set the brushType
	int		getSize();						// get the UI size
	int		getLineWidth();
	int		getLineAngle();
	double	getAlphaValue();
	bool	getIsInputColor();
	GLubyte*getColor();
	bool	getCanUndo();
	int		getSpacing();
	bool	getIsSizeRandom();
	void	setSize(int size);				// set the UI size
	void	setLineWidth(int lineWidth);
	void	setLineAngle(int lineAngle);
	void	setAlphaValue(double alphaValue);
	void	setIsInputColor(bool isInputColor);
	void	setCanUndo(bool canUndo);
	void	setSpacing(int spacing);
	void	setIsSizeRandom(bool isSizeRandom);
	char*	getImageName();					// get the current image name

	int		calcDistance(const Point a, const Point b);
	int		calcAngle(const Point a, const Point b);

	void	updateLastPainting();
	void	undoPainting();
	void	clearLastPainting();

	void	autoPaint();
// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;
	unsigned char*	m_ucLastPainting;

	// The current active brush.
	ImpBrush*			m_pCurrentBrush;

	// The right mouse brush
	ImpBrush*			m_pRightMouseBrush;

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );
	GLubyte* GetPaintingPixel(int x, int y);
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );
	GLubyte* GetPaintingPixel(const Point p);

	double GetGradientX(const Point sourse);
	double GetGradientY(const Point sourse);

	int GetPixelIntensity(int x, int y);


private:
	char			m_imageName[256];
	static const int sobelMaskX[3][3];
	static const int sobelMaskY[3][3];

};

extern void MessageBox(char *message);

#endif
