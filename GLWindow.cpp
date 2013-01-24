#include "GLStdafx.h"
#include "GLWindow.h"
#include "GLDrawingArea.h"

namespace Gtk
{
namespace GL
{

/*******************************************/
CGLWindow::CGLWindow(CGLDrawingArea& drawArea) :
_drawArea(drawArea),
_isDoubleBuffered(false)
/*******************************************/
{
    CreateOpenGLCapability();
    InitializeDrawingArea();
    AttachDrawingAreaToWindow();
}

/*******************************************/
CGLWindow::~CGLWindow()
/*******************************************/
{
}

/*******************************************/
void CGLWindow::AttachDrawingAreaToWindow()
/*******************************************/
{  
    set_reallocate_redraws(true); // Get automatically redrawn if any of their children changed allocation.  
    set_border_width(0/*10*/); // Set border width.
    add(DrawArea());
    show_all();
}

/***************************************/
GdkGLConfig* CGLWindow::CreateGDKGLConfig()
/***************************************/
{
	/* Try double-buffered visual */
    GdkGLConfig* glconfig = gdk_gl_config_new_by_mode (static_cast<GdkGLConfigMode>(GDK_GL_MODE_RGB    |
										GDK_GL_MODE_DEPTH  |
										GDK_GL_MODE_DOUBLE));
    if (glconfig == NULL)
    {
        IsDoubleBuffered(false);
        g_print ("*** Cannot find the double-buffered visual.\n");
        g_print ("*** Trying single-buffered visual.\n");

        /* Try single-buffered visual */
        glconfig = gdk_gl_config_new_by_mode (static_cast<GdkGLConfigMode>(GDK_GL_MODE_RGB   |
								            GDK_GL_MODE_DEPTH));
        if (glconfig == NULL)
        {
          g_print ("*** No appropriate OpenGL-capable visual found.\n");
          exit (1);
        }
    }
    else
    {
        IsDoubleBuffered(true);
    }

    return(glconfig);
}

/***************************************/
void CGLWindow::CreateOpenGLCapability()
/***************************************/
{

    // Configure OpenGL-capable visual.
    GLConfig(CreateGDKGLConfig());

    // Set OpenGL-capability to the widget.
    gtk_widget_set_gl_capability (reinterpret_cast<GtkWidget*>(gobj()),
                                GLConfig(),
                                NULL,
                                TRUE,
                                GDK_GL_RGBA_TYPE);

}

/***************************************/
void CGLWindow::InitializeDrawingArea()
/***************************************/
{
    DrawArea().Holder(this);
    DrawArea().MakeDrawingAreaAnOpenGLContext();
    DrawArea().RegisterSignalHandlers();
}
};
};
