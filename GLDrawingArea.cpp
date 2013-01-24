#include "GLStdafx.h"
#include "GLDrawingArea.h"
#include "GLWindow.h"
#include "GLException.h"

namespace Gtk
{
namespace GL
{

/***************************************/
CGLDrawingArea::CGLDrawingArea() :
_holder(NULL)
/***************************************/
{
}

/***************************************/
CGLDrawingArea::~CGLDrawingArea()
/***************************************/
{
}

/***************************************/
void CGLDrawingArea::GTK_BeginGL()
/***************************************/
{
    GtkWidget*     widget = reinterpret_cast<GtkWidget*>(gobj());
    GdkGLContext*  glcontext = gtk_widget_get_gl_context (widget);
    GdkGLDrawable* gldrawable = gtk_widget_get_gl_drawable (widget);

    /*** OpenGL BEGIN ***/
    if (!gdk_gl_drawable_gl_begin (gldrawable, glcontext))
        throw(CGLException());
}

/***************************************/
void CGLDrawingArea::GTK_EndGL()
/***************************************/
{
    GtkWidget*     widget     = reinterpret_cast<GtkWidget*>(gobj());
    GdkGLDrawable* gldrawable = gtk_widget_get_gl_drawable (widget);
    gdk_gl_drawable_gl_end (gldrawable);
}

/***************************************/
void CGLDrawingArea::GTK_FlushBufferGL()
/***************************************/
{
    GtkWidget*     widget     = reinterpret_cast<GtkWidget*>(gobj());
    GdkGLDrawable* gldrawable = gtk_widget_get_gl_drawable (widget);
    if (gdk_gl_drawable_is_double_buffered (gldrawable))
        gdk_gl_drawable_swap_buffers (gldrawable);
    else
        glFlush();
}

/***************************************/
GdkGLConfig* CGLDrawingArea::GLConfig()
/***************************************/
{
    return(Holder().GLConfig());
}

/***************************************/
void CGLDrawingArea::Invalidate()
/***************************************/
{
    /* Invalidate the whole window. */
    Invalidate(Holder().get_allocation());
}

/***************************************/
void CGLDrawingArea::Invalidate(Gtk::Allocation allocation)
/***************************************/
{
    GtkWidget* me = reinterpret_cast<GtkWidget*>(gobj());
    gdk_window_invalidate_rect (me->window, allocation.gobj(), FALSE);
}

/***************************************/
void CGLDrawingArea::Update()
/***************************************/
{
    GtkWidget* me = reinterpret_cast<GtkWidget*>(gobj());
    gdk_window_process_updates (me->window, FALSE);     /* Update synchronously (fast). */
}

/***************************************/
void CGLDrawingArea::MakeDrawingAreaAnOpenGLContext()
/***************************************/
{
    GtkWidget* widget = reinterpret_cast<GtkWidget*>(gobj());
    gtk_widget_set_gl_capability(widget,
                                GLConfig(),
                                NULL,
                                TRUE,
                                GDK_GL_RGBA_TYPE);
}
/***************************************/
void CGLDrawingArea::RegisterSignalHandlers()
/***************************************/
{
    //TODO: There's probably a better way to do this with gtkmm, but I don't really want to figure it out.
    //I have the C-style handler functions turn around and call the C++ virtual methods.

    GtkWidget* drawing_area = reinterpret_cast<GtkWidget*>(gobj());

    g_signal_connect_after (G_OBJECT (drawing_area), "realize",
                          G_CALLBACK (realize), this);
    g_signal_connect (G_OBJECT (drawing_area), "configure_event",
	        G_CALLBACK (configure_event), this);
    g_signal_connect (G_OBJECT (drawing_area), "expose_event",
	        G_CALLBACK (expose_event), this);
    g_signal_connect (G_OBJECT (drawing_area), "unrealize",
	        G_CALLBACK (unrealize), this);

    g_signal_connect (G_OBJECT (drawing_area), "map_event",
	        G_CALLBACK (map_event), this);
    g_signal_connect (G_OBJECT (drawing_area), "unmap_event",
	        G_CALLBACK (unmap_event), this);
    g_signal_connect (G_OBJECT (drawing_area), "visibility_notify_event",
	        G_CALLBACK (visibility_notify_event), this);

    //Here are the ones for mouse+keyboard
    add_events((Gdk::EventMask)(Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::KEY_PRESS_MASK | Gdk::KEY_RELEASE_MASK));

}

/******************************************************/
/******************************************************/
/******************************************************/
// C Signal Handlers
/******************************************************/
/******************************************************/

/***************************************/
void CGLDrawingArea::realize (GtkWidget *widget, gpointer data)
/***************************************/
{
    static_cast<CGLDrawingArea*>(data)->OnRealize();
}

/***************************************/
gboolean CGLDrawingArea::configure_event (GtkWidget* widget, GdkEventConfigure* eventInfo, gpointer data)
/***************************************/
{
    try
    {
        static_cast<CGLDrawingArea*>(data)->OnConfigureEvent();
        return(TRUE);
    }
    catch(CGLException e)
    {
        return(FALSE);
    }
}

/***************************************/
gboolean CGLDrawingArea::expose_event (GtkWidget* widget, GdkEventExpose* eventInfo, gpointer data)
/***************************************/
{
    try
    {
        static_cast<CGLDrawingArea*>(data)->OnExposeEvent();
        return(TRUE);
    }
    catch(CGLException e)
    {
        return(FALSE);
    }
}

/***************************************/
void CGLDrawingArea::unrealize (GtkWidget* widget, gpointer data)
/***************************************/
{
    static_cast<CGLDrawingArea*>(data)->OnUnrealize();
}

/***************************************/
gboolean CGLDrawingArea::map_event (GtkWidget* widget, GdkEvent* eventInfo, gpointer data)
/***************************************/
{
    try
    {
        static_cast<CGLDrawingArea*>(data)->OnMapEvent();
        return(TRUE);
    }
    catch(CGLException e)
    {
        return(FALSE);
    }
}

/***************************************/
gboolean CGLDrawingArea::unmap_event (GtkWidget* widget, GdkEvent* eventInfo, gpointer data)
/***************************************/
{
    try
    {
        static_cast<CGLDrawingArea*>(data)->OnUnmapEvent();
        return(TRUE);
    }
    catch(CGLException e)
    {
        return(FALSE);
    }
}

/***************************************/
gboolean CGLDrawingArea::visibility_notify_event (GtkWidget* widget, GdkEventVisibility* eventInfo, gpointer data)
/***************************************/
{
    try
    {
        static_cast<CGLDrawingArea*>(data)->OnVisibilityNotifyEvent();
        return(TRUE);
    }
    catch(CGLException e)
    {
        return(FALSE);
    }
}

/***************************************/
bool CGLDrawingArea::on_button_press_event(GdkEventButton* eventInfo)
/***************************************/
{
    int x = (int)(eventInfo->x);
    int y = (int)(eventInfo->y);

    bool isDoubleClick = (eventInfo->type == /*GdkEventType::*/GDK_2BUTTON_PRESS);

    switch(eventInfo->button)
    {
        case 1:
            if(isDoubleClick)
                return(OnLeftMouseDoubleClick(x,y));
            else
                return(OnLeftMouseDown(x, y));
        case 2:
            if(isDoubleClick)
                return(OnMiddleMouseDoubleClick(x,y));
            else
                return(OnMiddleMouseDown(x, y));
        case 3:
            if(isDoubleClick)
                return(OnRightMouseDoubleClick(x,y));
            else
                return(OnRightMouseDown(x, y));
        default:
            throw;
    };
}

/***************************************/
bool CGLDrawingArea::on_button_release_event(GdkEventButton* eventInfo)
/***************************************/
{
    int x = (int)(eventInfo->x);
    int y = (int)(eventInfo->y);
    switch(eventInfo->button)
    {
        case 1:
            return(OnLeftMouseUp(x, y));
        case 2:
            return(OnMiddleMouseUp(x, y));
        case 3:
            return(OnRightMouseUp(x, y));
        default:
            throw;
    };
}

/***************************************/
bool CGLDrawingArea::on_key_press_event (GdkEventKey* eventInfo)
/***************************************/
{
    return(OnKeyDown(eventInfo->keyval));
}

/***************************************/
bool CGLDrawingArea::on_key_release_event (GdkEventKey* eventInfo)
/***************************************/
{
    return(OnKeyUp(eventInfo->keyval));
}

/***************************************/
bool CGLDrawingArea::on_motion_notify_event(GdkEventMotion* eventInfo)
/***************************************/
{
    return(OnMouseMove((int)eventInfo->x, (int)eventInfo->y));
}



};
};
