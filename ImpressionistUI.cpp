//
// impressionistUI.h
//
// The user interface part for the program.
//


#include <FL/fl_ask.h>

#include <math.h>

#include "impressionistUI.h"
#include "impressionistDoc.h"

/*
//------------------------------ Widget Examples -------------------------------------------------
Here is some example code for all of the widgets that you may need to add to the 
project.  You can copy and paste these into your code and then change them to 
make them look how you want.  Descriptions for all of the widgets here can be found 
in links on the fltk help session page.

//---------Window/Dialog and Menubar-----------------------------------
	
	//----To install a window--------------------------
	Fl_Window* myWindow = new Fl_Window(600, 300, "MyWindow");
		myWindow->user_data((void*)(this));	// record self to be used by static callback functions
		
		// install menu bar
		myMenubar = new Fl_Menu_Bar(0, 0, 600, 25);
		Fl_Menu_Item ImpressionistUI::myMenuItems[] = {
			{ "&File",		0, 0, 0, FL_SUBMENU },
				{ "&Load...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load },
				{ "&Save...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save },
				{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
				{ 0 },
			{ "&Edit",		0, 0, 0, FL_SUBMENU },
				{ "&Copy",FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_copy, (void *)COPY },
				{ "&Cut",	FL_ALT + 'x', (Fl_Callback *)ImpressionistUI::cb_cut, (void *)CUT },
				{ "&Paste",	FL_ALT + 'v', (Fl_Callback *)ImpressionistUI::cb_paste, (void *)PASTE },
				{ 0 },
			{ "&Help",		0, 0, 0, FL_SUBMENU },
				{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
				{ 0 },
			{ 0 }
		};
		myMenubar->menu(myMenuItems);
    m_mainWindow->end();

	//----The window callback--------------------------
	// One of the callbacks
	void ImpressionistUI::cb_load(Fl_Menu_* o, void* v) 
	{	
		ImpressionistDoc *pDoc=whoami(o)->getDocument();

		char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
		if (newfile != NULL) {
			pDoc->loadImage(newfile);
		}
	}


//------------Slider---------------------------------------

	//----To install a slider--------------------------
	Fl_Value_Slider * mySlider = new Fl_Value_Slider(10, 80, 300, 20, "My Value");
	mySlider->user_data((void*)(this));	// record self to be used by static callback functions
	mySlider->type(FL_HOR_NICE_SLIDER);
    mySlider->labelfont(FL_COURIER);
    mySlider->labelsize(12);
	mySlider->minimum(1);
	mySlider->maximum(40);
	mySlider->step(1);
	mySlider->value(m_nMyValue);
	mySlider->align(FL_ALIGN_RIGHT);
	mySlider->callback(cb_MyValueSlides);

	//----The slider callback--------------------------
	void ImpressionistUI::cb_MyValueSlides(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyValue=int( ((Fl_Slider *)o)->value() ) ;
	}
	

//------------Choice---------------------------------------
	
	//----To install a choice--------------------------
	Fl_Choice * myChoice = new Fl_Choice(50,10,150,25,"&myChoiceLabel");
	myChoice->user_data((void*)(this));	 // record self to be used by static callback functions
	Fl_Menu_Item ImpressionistUI::myChoiceMenu[3+1] = {
	  {"one",FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)ONE},
	  {"two",FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)TWO},
	  {"three",FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_myChoice, (void *)THREE},
	  {0}
	};
	myChoice->menu(myChoiceMenu);
	myChoice->callback(cb_myChoice);
	
	//-----The choice callback-------------------------
	void ImpressionistUI::cb_myChoice(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
		ImpressionistDoc* pDoc=pUI->getDocument();

		int type=(int)v;

		pDoc->setMyType(type);
	}


//------------Button---------------------------------------

	//---To install a button---------------------------
	Fl_Button* myButton = new Fl_Button(330,220,50,20,"&myButtonLabel");
	myButton->user_data((void*)(this));   // record self to be used by static callback functions
	myButton->callback(cb_myButton);

	//---The button callback---------------------------
	void ImpressionistUI::cb_myButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI* pUI=((ImpressionistUI*)(o->user_data()));
		ImpressionistDoc* pDoc = pUI->getDocument();
		pDoc->startPainting();
	}


//---------Light Button------------------------------------
	
	//---To install a light button---------------------
	Fl_Light_Button* myLightButton = new Fl_Light_Button(240,10,150,25,"&myLightButtonLabel");
	myLightButton->user_data((void*)(this));   // record self to be used by static callback functions
	myLightButton->callback(cb_myLightButton);

	//---The light button callback---------------------
	void ImpressionistUI::cb_myLightButton(Fl_Widget* o, void* v)
	{
		ImpressionistUI *pUI=((ImpressionistUI*)(o->user_data()));

		if (pUI->myBool==TRUE) pUI->myBool=FALSE;
		else pUI->myBool=TRUE;
	}

//----------Int Input--------------------------------------

    //---To install an int input-----------------------
	Fl_Int_Input* myInput = new Fl_Int_Input(200, 50, 5, 5, "&My Input");
	myInput->user_data((void*)(this));   // record self to be used by static callback functions
	myInput->callback(cb_myInput);

	//---The int input callback------------------------
	void ImpressionistUI::cb_myInput(Fl_Widget* o, void* v)
	{
		((ImpressionistUI*)(o->user_data()))->m_nMyInputValue=int( ((Fl_Int_Input *)o)->value() );
	}

//------------------------------------------------------------------------------------------------
*/

//------------------------------------- Help Functions --------------------------------------------

//------------------------------------------------------------
// This returns the UI, given the menu item.  It provides a
// link from the menu items to the UI
//------------------------------------------------------------
ImpressionistUI* ImpressionistUI::whoami(Fl_Menu_* o)	
{
	return ( (ImpressionistUI*)(o->parent()->user_data()) );
}


//--------------------------------- Callback Functions --------------------------------------------

//------------------------------------------------------------------
// Brings up a file chooser and then loads the chosen image
// This is called by the UI when the load image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_load_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Open File?", "*.bmp", pDoc->getImageName() );
	if (newfile != NULL) {
		pDoc->loadImage(newfile);
	}
}


//------------------------------------------------------------------
// Brings up a file chooser and then saves the painted image
// This is called by the UI when the save image menu item is chosen
//------------------------------------------------------------------
void ImpressionistUI::cb_save_image(Fl_Menu_* o, void* v) 
{
	ImpressionistDoc *pDoc=whoami(o)->getDocument();

	char* newfile = fl_file_chooser("Save File?", "*.bmp", "save.bmp" );
	if (newfile != NULL) {
		pDoc->saveImage(newfile);
	}
}

//-------------------------------------------------------------
// Brings up the paint dialog
// This is called by the UI when the brushes menu item
// is chosen
//-------------------------------------------------------------
void ImpressionistUI::cb_brushes(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_brushDialog->show();
}

//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc* pDoc=whoami(o)->getDocument();

	pDoc->clearCanvas();
}

//------------------------------------------------------------
// Causes the Impressionist program to exit
// Called by the UI when the quit menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_exit(Fl_Menu_* o, void* v) 
{
	whoami(o)->m_mainWindow->hide();
	whoami(o)->m_brushDialog->hide();

}
//------------------------------------------------------------
// Swap the canvas of original view and painting view
// Called by the UI when the swap canvas menu item is chosen
//------------------------------------------------------------
void ImpressionistUI::cb_swap_canvas(Fl_Menu_* o, void* v)
{
	ImpressionistDoc *pDoc = whoami(o)->getDocument();
	if (pDoc->m_ucBitmap == NULL) {
		fl_alert("Please load an image before swapping canvas.");
		return;
	}
	pDoc->swapCanvas();

}

//-----------------------------------------------------------
// Brings up an about dialog box
// Called by the UI when the about menu item is chosen
//-----------------------------------------------------------
void ImpressionistUI::cb_about(Fl_Menu_* o, void* v) 
{
	fl_message("Impressionist FLTK version for COMP 4411, spring 2017, Mu Cong Ding.");
}

//------- UI should keep track of the current for all the controls for answering the query from Doc ---------
//-------------------------------------------------------------
// Sets the type of brush to use to the one chosen in the brush 
// choice.  
// Called by the UI when a brush is chosen in the brush choice
//-------------------------------------------------------------
void ImpressionistUI::cb_brushChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI=((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc=pUI->getDocument();

	int type=(int)v;

	pDoc->setBrushType(type);
}

void ImpressionistUI::cb_strokeDirectionChoice(Fl_Widget* o, void* v)
{
	ImpressionistUI* pUI = ((ImpressionistUI *)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

}


//------------------------------------------------------------
// Clears the paintview canvas.
// Called by the UI when the clear canvas button is pushed
//------------------------------------------------------------
void ImpressionistUI::cb_clear_canvas_button(Fl_Widget* o, void* v)
{
	ImpressionistDoc * pDoc = ((ImpressionistUI*)(o->user_data()))->getDocument();
	pDoc->clearCanvas();
	pDoc->clearLastPainting();
}


//-----------------------------------------------------------
// Updates the brush parameters to use from the value of the
// sliders
// Called by the UI when the sliders is moved
//-----------------------------------------------------------
void ImpressionistUI::cb_sizeSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSize=int( ((Fl_Slider *)o)->value() ) ;
}


void ImpressionistUI::cb_lineWidthSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineWidth = int(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_lineAngleSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nLineAngle = int(((Fl_Slider *)o)->value());
}


void ImpressionistUI::cb_alphaValueSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nAlphaValue = double(((Fl_Slider *)o)->value());
}

void ImpressionistUI::cb_imputColorButton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();

	if (pUI->getIsInputColor() == TRUE) {
		pDoc->setIsInputColor(FALSE);
	}
	else {
		pDoc->setIsInputColor(TRUE);
	}
}
void ImpressionistUI::cb_colorRed(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nColor[0] = (GLubyte)(((Fl_Slider *)o)->value());
}
void ImpressionistUI::cb_colorGreen(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nColor[1] = (GLubyte)(((Fl_Slider *)o)->value());
}
void ImpressionistUI::cb_colorBlue(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nColor[2] = (GLubyte)(((Fl_Slider *)o)->value());
}
void ImpressionistUI::cb_undoButton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	pDoc->undoPainting();
}
void ImpressionistUI::cb_spacingSlides(Fl_Widget* o, void* v)
{
	((ImpressionistUI*)(o->user_data()))->m_nSpacing = (GLubyte)(((Fl_Slider *)o)->value());
}
void ImpressionistUI::cb_sizeRandomButton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	if (pUI->getIsSizeRandom() == TRUE) {
		pDoc->setIsSizeRandom(FALSE);
	}
	else {
		pDoc->setIsSizeRandom(TRUE);
	}
}
void ImpressionistUI::cb_autoPaintButton(Fl_Widget* o, void* v)
{
	ImpressionistUI *pUI = ((ImpressionistUI*)(o->user_data()));
	ImpressionistDoc* pDoc = pUI->getDocument();
	pDoc->autoPaint();
}



//---------------------------------- per instance functions --------------------------------------

//------------------------------------------------
// Return the ImpressionistDoc used
//------------------------------------------------
ImpressionistDoc* ImpressionistUI::getDocument()
{
	return m_pDoc;
}

//------------------------------------------------
// Draw the main window
//------------------------------------------------
void ImpressionistUI::show() {
	m_mainWindow->show();
	m_paintView->show();
	m_origView->show();
}

//------------------------------------------------
// Change the paint and original window sizes to 
// w by h
//------------------------------------------------
void ImpressionistUI::resize_windows(int w, int h) {
	m_paintView->size(w,h);
	m_origView->size(w,h);
}

//------------------------------------------------ 
// Set the ImpressionistDoc used by the UI to 
// communicate with the brushes 
//------------------------------------------------
void ImpressionistUI::setDocument(ImpressionistDoc* doc)
{
	m_pDoc = doc;

	m_origView->m_pDoc = doc;
	m_paintView->m_pDoc = doc;
}

//------------------------------------------------
// Return the brush parameters
//------------------------------------------------
int ImpressionistUI::getSize()
{
	return m_nSize;
}

int ImpressionistUI::getLineWidth()
{
	return m_nLineWidth;
}

int ImpressionistUI::getLineAngle()
{
	return m_nLineAngle;
}

double ImpressionistUI::getAlphaValue()
{
	return m_nAlphaValue;
}

bool ImpressionistUI::getIsInputColor()
{
	return m_nIsInputColor;
}

GLubyte* ImpressionistUI::getColor()
{
	return m_nColor;
}

bool ImpressionistUI::getCanUndo()
{
	return m_nCanUndo;
}

int ImpressionistUI::getSpacing()
{
	return m_nSpacing;
}

bool ImpressionistUI::getIsSizeRandom()
{
	return m_nIsSizeRandom;
}

//-------------------------------------------------
// Set the brush parameters
//-------------------------------------------------
void ImpressionistUI::setSize(int size)
{
	m_nSize = size;

	if (1 <= size&&size <= 40) 
		m_BrushSizeSlider->value(m_nSize);
}

void ImpressionistUI::setLineWidth(int lineWidth)
{
	m_nLineWidth = lineWidth;

	if (1 <= lineWidth&&lineWidth <= 40)
		m_LineWidthSlider->value(m_nLineWidth);
}

void ImpressionistUI::setLineAngle(int lineAngle)
{
	m_nLineAngle = lineAngle;

	if (0 <= lineAngle&&lineAngle <= 359)
		m_LineAngleSlider->value(m_nLineAngle);
}

void ImpressionistUI::setAlphaValue(double alphaValue)
{
	m_nAlphaValue = alphaValue;

	if (0.00 <= alphaValue&&alphaValue <= 1.00)
		m_AlphaValueSlider->value(m_nAlphaValue);
}

void ImpressionistUI::setIsInputColor(bool isInputColor)
{
	m_nIsInputColor = isInputColor;
}

void ImpressionistUI::setCanUndo(bool canUndo)
{
	m_nCanUndo = canUndo;
}

void ImpressionistUI::setSpacing(int spacing)
{
	m_nSpacing = spacing;
}

void ImpressionistUI::setIsSizeRandom(bool isSizeRandom)
{
	m_nIsSizeRandom = isSizeRandom;
}


// Main menu definition
Fl_Menu_Item ImpressionistUI::menuitems[] = {
	{ "&File",		0, 0, 0, FL_SUBMENU },
		{ "&Load Image...",	FL_ALT + 'l', (Fl_Callback *)ImpressionistUI::cb_load_image },
		{ "&Save Image...",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_save_image },
		{ "&Brushes...",	FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_brushes }, 
		{ "&Clear Canvas", FL_ALT + 'c', (Fl_Callback *)ImpressionistUI::cb_clear_canvas, 0, FL_MENU_DIVIDER },
		
		{ "&Quit",			FL_ALT + 'q', (Fl_Callback *)ImpressionistUI::cb_exit },
		{ 0 },
	{ "&Display",   0, 0, 0, FL_SUBMENU },
		{ "&Swap Canvas", FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_swap_canvas },
		{ 0 },
	{ "&Help",		0, 0, 0, FL_SUBMENU },
		{ "&About",	FL_ALT + 'a', (Fl_Callback *)ImpressionistUI::cb_about },
		{ 0 },

	{ 0 }
};

// Brush choice menu definition
Fl_Menu_Item ImpressionistUI::brushTypeMenu[NUM_BRUSH_TYPE+1] = {
  {"Points",			FL_ALT+'p', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_POINTS},
  {"Lines",				FL_ALT+'l', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_LINES},
  {"Circles",			FL_ALT+'c', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_CIRCLES},
  {"Scattered Points",	FL_ALT+'q', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_POINTS},
  {"Scattered Lines",	FL_ALT+'m', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_LINES},
  {"Scattered Circles",	FL_ALT+'d', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_CIRCLES},
  {"Hearts",			FL_ALT+'f', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_HEARTS},
  {"Scattered Hearts",	FL_ALT+'g', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SCATTERED_HEARTS},
  {"Sharpen",			FL_ALT+'h', (Fl_Callback *)ImpressionistUI::cb_brushChoice, (void *)BRUSH_SHARPEN},
  {0}
};

Fl_Menu_Item ImpressionistUI::strokeDirectionTypeMenu[NUM_STROKEDIRECTION_TYPE + 1] = {
	{ "Slider/Right Mouse",	FL_ALT + 's', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)SLIDER_OR_RIGHTMOUSE },
	{ "Gradient",				FL_ALT + 'g', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)GRADIENT },
	{ "Brush Direction",		FL_ALT + 'b', (Fl_Callback *)ImpressionistUI::cb_strokeDirectionChoice, (void *)BRUSH_DIRECTION },
	{ 0 }
};



//----------------------------------------------------
// Constructor.  Creates all of the widgets.
// Add new widgets here
//----------------------------------------------------
ImpressionistUI::ImpressionistUI() {
	// Create the main window
	m_mainWindow = new Fl_Window(600, 300, "Impressionist");
		m_mainWindow->user_data((void*)(this));	// record self to be used by static callback functions
		// install menu bar
		m_menubar = new Fl_Menu_Bar(0, 0, 600, 25);
		m_menubar->menu(menuitems);

		// Create a group that will hold two sub windows inside the main
		// window
		Fl_Group* group = new Fl_Group(0, 25, 600, 275);

			// install paint view window
			m_paintView = new PaintView(300, 25, 300, 275, "This is the paint view");//0jon
			m_paintView->box(FL_DOWN_FRAME);

			// install original view window
			m_origView = new OriginalView(0, 25, 300, 275, "This is the orig view");//300jon
			m_origView->box(FL_DOWN_FRAME);
			m_origView->deactivate();

		group->end();
		Fl_Group::current()->resizable(group);
    m_mainWindow->end();

	// init values

	m_nSize = 10;
	m_nLineWidth = 1;
	m_nLineAngle = 0;
	m_nAlphaValue = 1.00;
	m_nIsInputColor = false;
	m_nColor[0] = 0;
	m_nColor[1] = 0;
	m_nColor[2] = 0;
	m_nCanUndo = false;
	m_nSpacing = 10;
	m_nIsSizeRandom = false;

	// brush dialog definition
	m_brushDialog = new Fl_Window(400, 350, "Brush Dialog");
		// Add a brush type choice to the dialog
		m_BrushTypeChoice = new Fl_Choice(51,10,150,25,"&Brush");
		m_BrushTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushTypeChoice->menu(brushTypeMenu);
		m_BrushTypeChoice->callback(cb_brushChoice);

		// Add a stroke direction type choice to the dialog
		m_StrokeDirectionTypeChoice = new Fl_Choice(115, 45, 150, 25, "&Stroke Direction");
		m_StrokeDirectionTypeChoice->user_data((void*)(this));	// record self to be used by static callback functions
		m_StrokeDirectionTypeChoice->menu(strokeDirectionTypeMenu);
		m_StrokeDirectionTypeChoice->callback(cb_strokeDirectionChoice);
		m_StrokeDirectionTypeChoice->deactivate(); // deactive when not using line or heart brush

		m_ClearCanvasButton = new Fl_Button(240,10,150,25,"&Clear Canvas");
		m_ClearCanvasButton->user_data((void*)(this));
		m_ClearCanvasButton->callback(cb_clear_canvas_button);

		// Add undo button to the dialog
		m_undoButton = new Fl_Button(290, 45, 100, 25, "&Undo");
		m_undoButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_undoButton->callback(cb_undoButton);
		m_undoButton->deactivate();

		// Add brush size slider to the dialog 
		m_BrushSizeSlider = new Fl_Value_Slider(10, 80, 300, 20, "Size");
		m_BrushSizeSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_BrushSizeSlider->type(FL_HOR_NICE_SLIDER);
        m_BrushSizeSlider->labelfont(FL_COURIER);
        m_BrushSizeSlider->labelsize(12);
		m_BrushSizeSlider->minimum(1);
		m_BrushSizeSlider->maximum(40);
		m_BrushSizeSlider->step(1);
		m_BrushSizeSlider->value(m_nSize);
		m_BrushSizeSlider->align(FL_ALIGN_RIGHT);
		m_BrushSizeSlider->callback(cb_sizeSlides);

		// Add brush line width slider to the dialog
		m_LineWidthSlider = new Fl_Value_Slider(10, 110, 300, 20, "Line Width");
		m_LineWidthSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineWidthSlider->type(FL_HOR_NICE_SLIDER);
		m_LineWidthSlider->labelfont(FL_COURIER);
		m_LineWidthSlider->labelsize(12);
		m_LineWidthSlider->minimum(1);
		m_LineWidthSlider->maximum(40);
		m_LineWidthSlider->step(1);
		m_LineWidthSlider->value(m_nLineWidth);
		m_LineWidthSlider->align(FL_ALIGN_RIGHT);
		m_LineWidthSlider->callback(cb_lineWidthSlides);
		m_LineWidthSlider->deactivate(); // deactive when not using line or heart brush

		// Add brush line angle slider to the dialog
		m_LineAngleSlider = new Fl_Value_Slider(10, 140, 300, 20, "Line Algle");
		m_LineAngleSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_LineAngleSlider->type(FL_HOR_NICE_SLIDER);
		m_LineAngleSlider->labelfont(FL_COURIER);
		m_LineAngleSlider->labelsize(12);
		m_LineAngleSlider->minimum(0);
		m_LineAngleSlider->maximum(359);
		m_LineAngleSlider->step(1);
		m_LineAngleSlider->value(m_nLineAngle);
		m_LineAngleSlider->align(FL_ALIGN_RIGHT);
		m_LineAngleSlider->callback(cb_lineAngleSlides);
		m_LineAngleSlider->deactivate(); // deactive when not using line or heart brush

		// Add brush alpha value slider to the dialog
		m_AlphaValueSlider = new Fl_Value_Slider(10, 170, 300, 20, "Alpha Value");
		m_AlphaValueSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_AlphaValueSlider->type(FL_HOR_NICE_SLIDER);
		m_AlphaValueSlider->labelfont(FL_COURIER);
		m_AlphaValueSlider->labelsize(12);
		m_AlphaValueSlider->minimum(0.00);
		m_AlphaValueSlider->maximum(1.00);
		m_AlphaValueSlider->step(0.01);
		m_AlphaValueSlider->value(m_nAlphaValue);
		m_AlphaValueSlider->align(FL_ALIGN_RIGHT);
		m_AlphaValueSlider->callback(cb_alphaValueSlides);

		// Add input color light button to the dialog
		m_imputColorButton = new Fl_Light_Button(10,197,150,25,"&Input Color");
		m_imputColorButton->user_data((void*)(this));   // record self to be used by static callback functions
		m_imputColorButton->callback(cb_imputColorButton);


		// Add color red slider to the dialog
		m_colorRed = new Fl_Value_Slider(10, 230, 300, 20, "Red");
		m_colorRed->user_data((void*)(this));	// record self to be used by static callback functions
		m_colorRed->type(FL_HOR_NICE_SLIDER);
		m_colorRed->labelfont(FL_COURIER);
		m_colorRed->labelsize(12);
		m_colorRed->minimum(0);
		m_colorRed->maximum(255);
		m_colorRed->step(1);
		m_colorRed->value(m_nColor[0]);
		m_colorRed->align(FL_ALIGN_RIGHT);
		m_colorRed->callback(cb_colorRed);
		m_colorRed->deactivate(); // deactive when not imputting color

		// Add color red slider to the dialog
		m_colorGreen = new Fl_Value_Slider(10, 260, 300, 20, "Green");
		m_colorGreen->user_data((void*)(this));	// record self to be used by static callback functions
		m_colorGreen->type(FL_HOR_NICE_SLIDER);
		m_colorGreen->labelfont(FL_COURIER);
		m_colorGreen->labelsize(12);
		m_colorGreen->minimum(0);
		m_colorGreen->maximum(255);
		m_colorGreen->step(1);
		m_colorGreen->value(m_nColor[0]);
		m_colorGreen->align(FL_ALIGN_RIGHT);
		m_colorGreen->callback(cb_colorGreen);
		m_colorGreen->deactivate(); // deactive when not imputting color

		// Add color red slider to the dialog
		m_colorBlue = new Fl_Value_Slider(10, 290, 300, 20, "Blue");
		m_colorBlue->user_data((void*)(this));	// record self to be used by static callback functions
		m_colorBlue->type(FL_HOR_NICE_SLIDER);
		m_colorBlue->labelfont(FL_COURIER);
		m_colorBlue->labelsize(12);
		m_colorBlue->minimum(0);
		m_colorBlue->maximum(255);
		m_colorBlue->step(1);
		m_colorBlue->value(m_nColor[0]);
		m_colorBlue->align(FL_ALIGN_RIGHT);
		m_colorBlue->callback(cb_colorBlue);
		m_colorBlue->deactivate(); // deactive when not imputting color

		// Add spacing slider to the dialog
		m_SpacingSlider = new Fl_Value_Slider(10, 320, 150, 20, "Spacing");
		m_SpacingSlider->user_data((void*)(this));	// record self to be used by static callback functions
		m_SpacingSlider->type(FL_HOR_NICE_SLIDER);
		m_SpacingSlider->labelfont(FL_COURIER);
		m_SpacingSlider->labelsize(12);
		m_SpacingSlider->minimum(1);
		m_SpacingSlider->maximum(50);
		m_SpacingSlider->step(1);
		m_SpacingSlider->value(m_nSpacing);
		m_SpacingSlider->align(FL_ALIGN_RIGHT);
		m_SpacingSlider->callback(cb_spacingSlides);

		// Add the size random light button to the dialog
		m_sizeRandomButtion = new Fl_Light_Button(220, 317, 90, 25, "&Size Rand.");
		m_sizeRandomButtion->user_data((void*)(this));   // record self to be used by static callback functions
		m_sizeRandomButtion->callback(cb_sizeRandomButton);

		m_autoPaintButtion = new Fl_Button(320, 317, 70, 25, "&Paint");
		m_autoPaintButtion->user_data((void*)(this));   // record self to be used by static callback functions
		m_autoPaintButtion->callback(cb_autoPaintButton);

    m_brushDialog->end();	

}
