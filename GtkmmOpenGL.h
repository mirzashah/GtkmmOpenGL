/*****************************************************************************/
// Filename: GtkmmOpenGL.h
/*****************************************************************************/

#ifndef GTKMM_OPEN_GL_H_DEFINED
#define GTKMM_OPEN_GL_H_DEFINED

#include "GLWindow.h"
#include "GLDrawingArea.h"

namespace Gtk
{

namespace GL
{
void InitializeOpenGLSupportForGTK(int argc, char* argv[]);
};

};


#endif
