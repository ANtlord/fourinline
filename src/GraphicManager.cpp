#include "../header/GraphicManager.h"
#include <wx/msgdlg.h>
#include <fstream>
#define GL_CLAMP_TO_EDGE 0x812F
#include <cmath>

GLuint* GraphicManager::texture = NULL;
GraphicManager::GraphicManager(){ }

GLuint* loadImage(wxString path, int* imageWidth, int* imageHeight, int* textureWidth, int* textureHeight)
{

	GLuint* ID=new GLuint[1];
	glGenTextures( 1, &ID[0] );

	glBindTexture( GL_TEXTURE_2D, *ID );

	// the first time, init image handlers (remove this part if you do it somewhere else in your app)
	static bool is_first_time = true;
	if(is_first_time)
	{
		wxInitAllImageHandlers();

		is_first_time = false;
	}

	// check the file exists
	if(!wxFileExists(path))
	{
		wxMessageBox( _("Failed to load resource image") );
		exit(1);
	}

	wxImage* img=new wxImage(path);

	(*imageWidth)=img->GetWidth();
	(*imageHeight)=img->GetHeight();
	int w = img->GetWidth();
	int h = img->GetHeight();

	glPixelStorei(GL_UNPACK_ALIGNMENT,   1  );
glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    /*
     * Many graphics card require that textures be power of two.
     * Below is a simple implementation, probably not optimal but working.
     * If your texture sizes are not restricted to power of 2s, you can
     * of course adapt the bit below as needed.
     */

	float power_of_two_that_gives_correct_width=std::log((float)(*imageWidth))/std::log(2.0);
	float power_of_two_that_gives_correct_height=std::log((float)(*imageHeight))/std::log(2.0);

        // check if image dimensions are a power of two
        if( (int)power_of_two_that_gives_correct_width == power_of_two_that_gives_correct_width &&
            (int)power_of_two_that_gives_correct_height == power_of_two_that_gives_correct_height)
        {
            std::ofstream log("image.txt", std::ofstream::app);
	    log<<"321\n";
	    log.close();
                // note: must make a local copy before passing the data to OpenGL, as GetData() returns RGB
                // and we want the Alpha channel if it's present. Additionally OpenGL seems to interpret the
                // data upside-down so we need to compensate for that.
                GLubyte *bitmapData=img->GetData();
                GLubyte *alphaData=img->GetAlpha();

                int bytesPerPixel = img->HasAlpha() ?  4 : 3;

                int imageSize = (*imageWidth) * (*imageHeight) * bytesPerPixel;
                GLubyte *imageData=new GLubyte[imageSize];

                int rev_val=(*imageHeight)-1;

                for(int y=0; y<(*imageHeight); y++)
                {
                        for(int x=0; x<(*imageWidth); x++)
                        {
                                imageData[(x+y*(*imageWidth))*bytesPerPixel+0]=
                                        bitmapData[( x+(rev_val-y)*(*imageWidth))*3];

                                imageData[(x+y*(*imageWidth))*bytesPerPixel+1]=
                                        bitmapData[( x+(rev_val-y)*(*imageWidth))*3 + 1];

                                imageData[(x+y*(*imageWidth))*bytesPerPixel+2]=
                                        bitmapData[( x+(rev_val-y)*(*imageWidth))*3 + 2];

                                if(bytesPerPixel==4) imageData[(x+y*(*imageWidth))*bytesPerPixel+3]=
                                        alphaData[ x+(rev_val-y)*(*imageWidth) ];
                        }//next
                }//next

                // if yes, everything is fine
                glTexImage2D(GL_TEXTURE_2D,
                             0,
                             bytesPerPixel,
                             *imageWidth,
                             *imageHeight,
                             0,
                             img->HasAlpha() ?  GL_RGBA : GL_RGB,
                             GL_UNSIGNED_BYTE,
                             imageData);

                (*textureWidth)  = (*imageWidth);
                (*textureHeight) = (*imageHeight);

                delete [] imageData;
        }
	else // texture is not a power of two. We need to resize it
	{
	    std::ofstream log("image.txt", std::ofstream::app);
	    log<<"123\n";
	    log.close();
		int newWidth=(int)std::pow( 2.0, (int)(std::ceil(power_of_two_that_gives_correct_width)) );
		int newHeight=(int)std::pow( 2.0, (int)(std::ceil(power_of_two_that_gives_correct_height)) );

		//printf("Unsupported image size. Recommand values: %i %i\n",newWidth,newHeight);

		GLubyte	*bitmapData=img->GetData();
		GLubyte        *alphaData=img->GetAlpha();

		int old_bytesPerPixel = 3;
		int bytesPerPixel = img->HasAlpha() ?  4 : 3;

        newWidth = 256;
        newHeight = 256;
		int imageSize = newWidth * newHeight * bytesPerPixel;
		GLubyte	*imageData=new GLubyte[imageSize];

		int rev_val=h-1;

		for(int y=0; y<h; y++)		{
			for(int x=0; x<w; x++)			{
//				if( x<(*imageWidth) && y<(*imageHeight) ){
					imageData[(x+y*newWidth)*bytesPerPixel+0]=
					bitmapData[( x+(rev_val-y)*(w))*old_bytesPerPixel + 0];

					imageData[(x+y*newWidth)*bytesPerPixel+1]=
						bitmapData[( x+(rev_val-y)*(w))*old_bytesPerPixel + 1];

					imageData[(x+y*newWidth)*bytesPerPixel+2]=
						bitmapData[( x+(rev_val-y)*(w))*old_bytesPerPixel + 2];

					if(bytesPerPixel==4) imageData[(x+y*newWidth)*bytesPerPixel+3]=
						alphaData[ x+(rev_val-y)*(w) ];

//				}
//				else
//				{
//
//					imageData[(x+y*newWidth)*bytesPerPixel+0] = 0;
//					imageData[(x+y*newWidth)*bytesPerPixel+1] = 0;
//					imageData[(x+y*newWidth)*bytesPerPixel+2] = 0;
//					if(bytesPerPixel==4) imageData[(x+y*newWidth)*bytesPerPixel+3] = 0;
//				}

			}//next
		}//next


		glTexImage2D(GL_TEXTURE_2D,
					 0,
					 img->HasAlpha() ?  4 : 3,
					 newWidth,
					 newHeight,
					 0,
					 img->HasAlpha() ?  GL_RGBA : GL_RGB,
					 GL_UNSIGNED_BYTE,
					 imageData);

		delete [] imageData;
	}

	// set texture parameters as you wish
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	return ID;
}

GLuint* GraphicManager::loadTexture(char * path)
{
//    int q,w,e,a;
//    return loadImage(wxString()<<path, &q,&w,&e,&a);

    std::ofstream log("image.txt", std::ofstream::out);
    GLuint* ID = new GLuint[1];
    wxImage * TexFile = new wxImage(wxString()<<path, wxBITMAP_TYPE_ANY, 100);

    if (TexFile->IsOk() == false){
        std::cout<<"File doesn't exists\n";
        wxMessageBox("File doesn't exists");
    }
    else {
        log<<"texture before generating: "<<(int)ID[0]<<"\n";
        glGenTextures(1, &ID[0]);
        glBindTexture(GL_TEXTURE_2D, *ID);

        int width=TexFile->GetWidth();
        int height=TexFile->GetHeight();
//        width=height=256;
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        GLubyte *bitmapData=TexFile->GetData();
        GLubyte *alphaData=TexFile->GetAlpha();

        const char RGB_CHANNELS = 3;
        const char RGBA_CHANNELS = 4;

        unsigned char bytesPerPixel = (alphaData != NULL) ?  RGBA_CHANNELS : RGB_CHANNELS;
//        wxMessageBox(wxString()<<(int)bytesPerPixel);
        GLubyte *imageData=new GLubyte[width * height * bytesPerPixel];
//
        for(unsigned int y=0; y<height; y++) {        // To get every channel
            for(unsigned int x=0; x<width; x++) {     // by full width
                for (char i=0; i<bytesPerPixel; ++i){    // in every pixel column.
                    imageData[(x + y * width) * bytesPerPixel + i]=   // Set bitmap
                            bitmapData[( x + y * width) * 3 + i];   // to image.
                }
                if (alphaData != NULL)
                    imageData[(x + y * width) * bytesPerPixel + 3] = alphaData[x + y * width];
            }

        }




        glTexImage2D(GL_TEXTURE_2D, 0, bytesPerPixel, width, height, 0,
                     (alphaData != NULL ?  GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE ,
                     imageData);

        delete [ ] imageData;

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_LINEAR
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    log<<"texture after generating: "<<(int)ID[0]<<"\n";
    log.close();
    return ID;
}



void GraphicManager::drawRectangle(GLfloat x1,GLfloat x2,
                                   GLfloat y1,GLfloat y2,GLfloat z)
{
    glBegin(GL_POLYGON);
        glVertex3f(x1,y1,z);
        glVertex3f(x1,y2,z);
        glVertex3f(x2,y2,z);
        glVertex3f(x2,y1,z);
    glEnd();
}



void GraphicManager::drawTexturedQuad(GLfloat quadCoords[5], GLfloat texCoords[4])
{
    std::ofstream log("image.txt", std::ofstream::app);
    log<<"FUCK\n";

    if (GraphicManager::texture != NULL) {
        log<<"texture before binding"<<(int)GraphicManager::texture[0]<<"\n";
        glBindTexture(GL_TEXTURE_2D, GraphicManager::texture[0]);
    }
    log.close();
    glBegin(GL_QUADS);  //  Draws slot and sets texture on it.
        glTexCoord2f(texCoords[0], texCoords[2]);
        glVertex2f(quadCoords[0], quadCoords[2]);

        glTexCoord2f(texCoords[0], texCoords[3]);
        glVertex2f(quadCoords[0], quadCoords[3]);

        glTexCoord2f(texCoords[1], texCoords[3]);
        glVertex2f(quadCoords[1], quadCoords[3]);

        glTexCoord2f(texCoords[1], texCoords[2]);
        glVertex2f(quadCoords[1], quadCoords[2]);
    glEnd();
}
