/*****************************************************************************/
// Filename: GLWindow.h
/*****************************************************************************/
/*****************************************************************************/

#ifndef GL_WINDOW_H_DEFINED
#define GL_WINDOW_H_DEFINED

#include "GLStdafx.h"

namespace Gtk
{

namespace GL
{

class CGLDrawingArea;
class CGLWindow : public Gtk::Window
{
    friend class CGLDrawingArea;

    public:
        CGLWindow(CGLDrawingArea& drawArea);
        virtual ~CGLWindow();

    private:
        void              AttachDrawingAreaToWindow();
		GdkGLConfig*      CreateGDKGLConfig();
		void              CreateOpenGLCapability();
        CGLDrawingArea&   DrawArea(){return(_drawArea);}
        GdkGLConfig*      GLConfig(){return(_glConfig);}
        void              GLConfig(GdkGLConfig* config){_glConfig = config;}
        void              InitializeDrawingArea();
        bool              IsDoubleBuffered(){return(_isDoubleBuffered);}
        void              IsDoubleBuffered(bool isIt){_isDoubleBuffered = isIt;}

    private:
        CGLDrawingArea&   _drawArea;
        bool              _isDoubleBuffered;
        GdkGLConfig*      _glConfig;

};

};
};
#endif
