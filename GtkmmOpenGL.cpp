#include "GLStdafx.h"
#include <GtkmmOpenGL.h>


/*****************************************************/
void Gtk::GL::InitializeOpenGLSupportForGTK(int argc, char* argv[])
/*****************************************************/
{
    gtk_gl_init(&argc, &argv);
}
