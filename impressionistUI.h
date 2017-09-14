//
// impressionistUI.h
//
// The header file for the UI part
//

#ifndef ImpressionistUI_h
#define ImpressionistUI_h

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/fl_file_chooser.H>		// FLTK file chooser
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Value_Slider.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Light_Button.H>

#include "Impressionist.h"
#include "OriginalView.h"
#include "PaintView.h"

#include "ImpBrush.h"

class ImpressionistUI {
public:
	ImpressionistUI();

	// The FLTK widgets
	Fl_Window*			m_mainWindow;
	Fl_Menu_Bar*		m_menubar;
								
	PaintView*			m_paintView;
	OriginalView*		m_origView;

	// for brush dialog
	Fl_Window*			m_brushDialog;
	Fl_Choice*			m_BrushTypeChoice;
	Fl_Choice*			m_StrokeDirectionTypeChoice;

	Fl_Slider*			m_BrushSizeSlider;
	Fl_Slider*			m_LineWidthSlider;
	Fl_Slider*			m_LineAngleSlider;
	Fl_Slider*			m_AlphaValueSlider;
	Fl_Slider*			m_colorRed;
	Fl_Slider*			m_colorGreen;
	Fl_Slider*			m_colorBlue;
	Fl_Button*          m_ClearCanvasButton;
	Fl_Button*			m_undoButton;
	Fl_Light_Button*	m_imputColorButton;

	Fl_Value_Slider*	m_SpacingSlider;
	Fl_Light_Button*	m_sizeRandomButtion;
	Fl_Button*			m_autoPaintButtion;

	// Member functions
	void				setDocument(ImpressionistDoc* doc);
	ImpressionistDoc*	getDocument();

	void				show();
	void				resize_windows(int w, int h);

	// Interface to get attribute

	int					getSize();
	int					getLineWidth();
	int					getLineAngle();
	double				getAlphaValue();
	bool				getIsInputColor();
	bool				getCanUndo();
	GLubyte*			getColor();
	int					getSpacing();
	bool				getIsSizeRandom();
	void				setSize(int size);
	void				setLineWidth(int lineWidth);
	void				setLineAngle(int lineAngle);
	void				setAlphaValue(double alphaValue);
	void				setIsInputColor(bool isInputColor);
	void				setCanUndo(bool canUndo);
	void				setSpacing(int spacing);
	void				setIsSizeRandom(bool isSizeRandom);

private:
	ImpressionistDoc*	m_pDoc;		// pointer to document to communicate with the document

	// All attributes here
	int		m_nSize;
	int		m_nLineWidth;
	int		m_nLineAngle;
	double	m_nAlphaValue;
	bool	m_nIsInputColor;
	GLubyte	m_nColor[3];
	bool	m_nCanUndo;
	int		m_nSpacing;
	bool	m_nIsSizeRandom;

	// Static class members
	static Fl_Menu_Item		menuitems[];
	static Fl_Menu_Item		brushTypeMenu[NUM_BRUSH_TYPE + 1];
	static Fl_Menu_Item		strokeDirectionTypeMenu[NUM_STROKEDIRECTION_TYPE + 1];

	static ImpressionistUI*	whoami(Fl_Menu_* o);

	// All callbacks here.  Callbacks are declared 
	// static
	static void	cb_load_image(Fl_Menu_* o, void* v);
	static void	cb_save_image(Fl_Menu_* o, void* v);
	static void	cb_brushes(Fl_Menu_* o, void* v);
	static void	cb_clear_canvas(Fl_Menu_* o, void* v);
	static void	cb_exit(Fl_Menu_* o, void* v);
	static void	cb_swap_canvas(Fl_Menu_* o, void* v);
	static void	cb_about(Fl_Menu_* o, void* v);
	static void	cb_brushChoice(Fl_Widget* o, void* v);
	static void	cb_strokeDirectionChoice(Fl_Widget* o, void* v);
	static void	cb_clear_canvas_button(Fl_Widget* o, void* v);
	static void	cb_sizeSlides(Fl_Widget* o, void* v);
	static void	cb_lineWidthSlides(Fl_Widget* o, void* v);
	static void	cb_lineAngleSlides(Fl_Widget* o, void* v);
	static void	cb_alphaValueSlides(Fl_Widget* o, void* v);
	static void	cb_imputColorButton(Fl_Widget* o, void* v);
	static void	cb_colorRed(Fl_Widget* o, void* v);
	static void	cb_colorGreen(Fl_Widget* o, void* v);
	static void	cb_colorBlue(Fl_Widget* o, void* v);
	static void	cb_undoButton(Fl_Widget* o, void* v);
	static void	cb_spacingSlides(Fl_Widget* o, void* v);
	static void	cb_sizeRandomButton(Fl_Widget* o, void* v);
	static void	cb_autoPaintButton(Fl_Widget* o, void* v);
};

#endif
