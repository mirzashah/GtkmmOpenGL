/*****************************************************************************/
// Filename: GLDrawingArea.h
/*****************************************************************************/
/*****************************************************************************/

#ifndef OPENGL_DRAWING_AREA_H_DEFINED
#define OPENGL_DRAWING_AREA_H_DEFINED

namespace Gtk
{
namespace GL
{

class CGLWindow;
class CGLDrawingArea : public Gtk::DrawingArea
{
    friend class CGLWindow;

	public:
		CGLDrawingArea();
		virtual ~CGLDrawingArea();
        CGLWindow&         Holder(){return(*_holder);}

    protected:

        virtual bool       OnKeyDown(char c){return(true);}
        virtual bool       OnKeyUp(char c){return(true);}
        virtual bool       OnLeftMouseDoubleClick(int x, int y){return(true);}
        virtual bool       OnLeftMouseDown(int x, int y){return(true);}
        virtual bool       OnLeftMouseUp(int x, int y){return(true);}
        virtual bool       OnMiddleMouseDoubleClick(int x, int y){return(true);}
        virtual bool       OnMiddleMouseDown(int x, int y){return(true);}
        virtual bool       OnMiddleMouseUp(int x, int y){return(true);}
        virtual bool       OnMouseMove(int x, int y){return(true);}
        virtual bool       OnRightMouseDoubleClick(int x, int y){return(true);}
        virtual bool       OnRightMouseDown(int x, int y){return(true);}
        virtual bool       OnRightMouseUp(int x, int y){return(true);}

        virtual void       OnRealize(){}
        virtual void       OnConfigureEvent(){}
        virtual void       OnExposeEvent(){}
        virtual void       OnUnrealize(){}
        virtual void       OnMapEvent(){}
        virtual void       OnUnmapEvent(){}
        virtual void       OnVisibilityNotifyEvent(){}

    protected:
        void               GTK_BeginGL();
        void               GTK_EndGL();
        void               GTK_FlushBufferGL();
        void               Invalidate();
        void               Invalidate(Gtk::Allocation allocation);
        void               Update();

	private:
        GdkGLConfig*       GLConfig();
        void               Holder(CGLWindow* holder){_holder = holder;}
        void               MakeDrawingAreaAnOpenGLContext();
        void               RegisterSignalHandlers();

    private: //Low-Level C Signal Handlers
        static void        realize (GtkWidget *widget, gpointer data);
        static gboolean    configure_event (GtkWidget* widget, GdkEventConfigure* eventInfo, gpointer data);
        static gboolean    expose_event (GtkWidget* widget, GdkEventExpose* eventInfo, gpointer data);
        static gboolean    timeout (GtkWidget* widget);
        static void        unrealize (GtkWidget* widget, gpointer data);
        static gboolean    map_event (GtkWidget* widget, GdkEvent* eventInfo, gpointer data);
        static gboolean    unmap_event (GtkWidget* widget, GdkEvent* eventInfo, gpointer data);
        static gboolean    visibility_notify_event (GtkWidget* widget,	GdkEventVisibility* eventInfo, gpointer data);

    private: //Low-Level C++ Signal Handlers
        virtual bool      on_key_press_event (GdkEventKey* eventInfo);
        virtual bool      on_key_release_event (GdkEventKey* eventInfo);
        virtual bool 	  on_motion_notify_event (GdkEventMotion* eventInfo);
        virtual bool   	  on_button_press_event (GdkEventButton* eventInfo);
        virtual bool 	  on_button_release_event (GdkEventButton* eventInfo);

    private:
        CGLWindow*        _holder;

};
};
};

#endif
