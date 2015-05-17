/***************************************************************
 * Name:      FourInLineApp.cpp
 * Purpose:   Code for Application Class
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

#include "FourInLineApp.h"
#include "FourInLineMain.h"

IMPLEMENT_APP(FourInLineApp);

bool FourInLineApp::OnInit()
{
    wxInitAllImageHandlers();
    FourInLineFrame* frame = new FourInLineFrame(0L, _("wxWidgets Application Template"));

    frame->Show();

    return true;
}
