#include "../header/Canvas.h"
#include <iostream>
#include <fstream>

Canvas::Canvas(wxWindow *parent, wxWindowID id, int * attributes,const wxPoint& pos,
               const wxSize& size) : wxGLCanvas(parent, id, attributes, pos, size)
{
    p=false;
    parent->Show();
    Connect(wxEVT_SIZE, (wxObjectEventFunction)&Canvas::onSize,0,this);
    Connect(wxEVT_PAINT, (wxObjectEventFunction)&Canvas::onPaint,0,this);
    Connect(wxEVT_MOTION, (wxObjectEventFunction)&Canvas::onMouseMove,0,this);
    Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&Canvas::onMouseLeftDown,0,this);
    Connect(wxEVT_KEY_DOWN, (wxObjectEventFunction)&Canvas::onKeyDown,0,this);
    Connect(wxEVT_TIMER, (wxObjectEventFunction)&Canvas::onTimer,0,this);

    context = new wxGLContext(this);
    SetCurrent(*context);

    GraphicManager::texture = GraphicManager::loadTexture((char*)"static\\GeneralTex.png");
//    glBindTexture(GL_TEXTURE_2D, GraphicManager::texture[0]);

    std::ofstream log("image.txt", std::ofstream::app);
    log<<"global texture: "<<(int)GraphicManager::texture[0]<<"\n";
    log.close();


    timer.SetOwner(this);

    ALfloat ResPos[3] = { 0.0, 0.0, 0.0 };
    ALfloat ResVel[3] = { 0.0, 0.0, 0.1 };

    ALfloat LisPos[] = { 0.0, 0.0, 0.0 };
    ALfloat LisVel[] = { 0.0, 0.0, 0.0 };
    ALfloat LisOri[] = { 0.0, -1.0, 0.0,  0.0, 1.0, 0.0 };

    bumSound = new PEvsound("static\\bum.ogg");
    bumSound->Custom(*ResPos, *ResVel, *LisPos, *LisVel, *LisOri);

}

void Canvas::initGL()
{
    std::ofstream log("gl.txt");
    log<<"initialization"<<"\n";
    log.close();
    SetCurrent(*context);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   // Black Background
    glEnable(GL_TEXTURE_2D);    // textures
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    short w = GetSize().GetWidth(); // Get size of canvas.
    short h = GetSize().GetHeight();
    glViewport(0, 0, (GLint)w, (GLint)h);
    glLoadIdentity();

    // Make matrix with 1 element per pixel.
    gluOrtho2D(0.0, (GLfloat)w, 0.0, (GLfloat)h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gameBoard = new GameBoard(wxPoint(0,0), wxSize(GetSize().GetWidth(),
                                    GetSize().GetHeight()-100));
    gameChip = new Chip(wxPoint(0, GetSize().GetHeight() - 100));
    referee = new Referee(*gameBoard);
    Refresh(false);
}

void Canvas::onMouseLeftDown(wxMouseEvent &e){
    if (timer.IsRunning() == true){
        return; // Protection against haters;
    }
    for (char i=0; i<gameBoard->NUM_COLUMNS; ++i){  // In this cycle, prorgamm
        Column &currentCol = *gameBoard->columns[i];
        short x=currentCol.position.x;  // finds column, which has
        bool cond1 = e.GetX() >= x;                 // placing over click.
        bool cond2 = e.GetX() < x + currentCol.size.GetWidth();

        if ( cond1 == cond2 == true ){   // Get column for drawing.
            if ( currentCol.isFull() != true) {
                gameChip->position.x = currentCol.position.x;
                gameChip->initTaking(currentCol);   // Animate starts since here.
                timer.Start(5);
                referee->checkGame(i);
            }
            i = gameBoard->NUM_COLUMNS; // Break cycle.
        }
    }
}


void Canvas::syncView()
{
    short w = GetSize().GetWidth(); // Get size of canvas.
    short h = GetSize().GetHeight();
    glViewport(0, 0, (GLint)w, (GLint)h);
}

void Canvas::onSize(wxSizeEvent &e){
    SetCurrent(*context);
    syncView();
}

void Canvas::onPaint(wxPaintEvent& e ){
    if (p==false) {
        std::ofstream log("gl.txt", std::ofstream::app);
        log<<"drawing"<<"\n";
        log.close();
        p=true;
    }
    wxPaintDC dc(this); // Without this doesn't work.
    SetCurrent(*context);
    if (timer.IsRunning() == false){
//        // Doesn't clear becouse, clearing was when gamechip had moving.
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    }
    gameBoard->draw();  // Draws game board.
    SwapBuffers();
}


void Canvas::onTimer(wxTimerEvent& e){
    if ( gameChip->animate() == true){
        Refresh();
    }
    else {
        timer.Stop();
        // Respawn gamechip.
        bumSound->Play();
        gameChip->position = wxPoint(0, GetSize().GetHeight() - 100);
        if (referee->winner != -1){
            std::cout<<"Winner: "<<referee->winner<<"\n";
            PBgsound * winMelody = new PBgsound("static\\Queen – We Are The Champions.ogg");
            winMelody->Custom();
            winMelody->Play();
        }
    }
}

// Unusable methods.
void Canvas::onMouseMove(wxMouseEvent &e){ }
void Canvas::onKeyDown(wxKeyEvent &e){ }

Canvas::~Canvas()
{
    delete bumSound;
    delete gameBoard;
    delete context;
    delete gameChip;
}
