/***************************************************************
 * Name:      FourInLineMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2013-03-25
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef FOURINLINEMAIN_H
#define FOURINLINEMAIN_H

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "FourInLineApp.h"
#include "header/Canvas.h"

class FourInLineFrame: public wxFrame
{
    public:
        FourInLineFrame(wxFrame *frame, const wxString& title);
        ~FourInLineFrame();
    private:
        Canvas *canvas;
        GraphicManager * manager;

        void OnClose(wxCloseEvent& event);
        void OnQuit(wxCommandEvent& event);
        void onSize(wxSizeEvent &e);
        DECLARE_EVENT_TABLE()
};


#endif // FOURINLINEMAIN_H
