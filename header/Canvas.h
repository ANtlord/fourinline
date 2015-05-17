#ifndef CANVAS_H
#define CANVAS_H

//#include "GameBoard.h"
#include "GraphicManager.h"
#include "Referee.h"
#include "PBgsound.h"
#include "PEvsound.h"
#include <wx/glcanvas.h>
#include <wx/dcclient.h>
#include <wx/timer.h>


class Canvas : public wxGLCanvas {
    public:
        Canvas(wxWindow *parent, wxWindowID id = wxID_ANY, int * attributes = 0,
               const wxPoint& pos = wxPoint(0,0),
               const wxSize& size = wxSize(200,200));
        ~Canvas();
        void initGL();

    protected:
        void onMouseLeftDown(wxMouseEvent &e);
        void onMouseMove(wxMouseEvent &e);
        void onSize(wxSizeEvent &e);
        void onPaint(wxPaintEvent &e);
        void onKeyDown(wxKeyEvent &e);
        void onTimer(wxTimerEvent& event);
        wxGLContext *context;

    private:
        void syncView();
        GameBoard * gameBoard;
        Chip * gameChip;
        wxTimer timer;
        Referee * referee;
        PEvsound * bumSound;
        bool p;


};

#endif // CANVAS_H
