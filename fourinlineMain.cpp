/***************************************************************
 * Name:      FourInLineMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2013-03-25
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "FourInLineMain.h"

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__WXMAC__)
        wxbuild << _T("-Mac");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}
//
BEGIN_EVENT_TABLE(FourInLineFrame, wxFrame)
END_EVENT_TABLE()

FourInLineFrame::FourInLineFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
    Connect(wxEVT_SIZE, (wxObjectEventFunction)&FourInLineFrame::onSize,0,this);

    SetSize(700, 700);
    wxSize size = wxSize(GetSize().GetWidth(), GetSize().GetHeight());

    int attributes[5] = { WX_GL_RGBA, WX_GL_DEPTH_SIZE, 16, WX_GL_DOUBLEBUFFER};

    canvas = new Canvas(this, wxID_ANY, attributes, wxPoint(0,0), size);
    Show(true);
    Raise();

    canvas->initGL();
}


FourInLineFrame::~FourInLineFrame()
{
    delete canvas;
}

void FourInLineFrame::onSize(wxSizeEvent &e){
    //std::cout<<"canvas: "<<canvas<<"\n";
    if (this->canvas != NULL)
        this->canvas->SetSize(GetSize().GetWidth(), GetSize().GetHeight());
}
void FourInLineFrame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void FourInLineFrame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}
