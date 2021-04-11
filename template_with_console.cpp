
//includes areas for keyboard control, mouse control, resizing the window
//and draws a spinning rectangle

#include <iostream>
#include "Image_Loading/nvImage.h"
#include "FreeType.h"
#include "Engine.h"

using namespace freetype;

int	mouse_x=0, mouse_y=0;
bool LeftPressed = false;
int screenWidth=480, screenHeight=480;
bool keys[256];
float spin=0;
float speed=1;
float acc = 0;
float cameraMoveX = 0;
float cameraMoveY = 0;
float cameraOrigin;
float score = 0;
float collected = 0;
float needed = 0;
float detalTime;

GLuint soilTexture = 0;
GLuint woodTexture = 0;
GLuint playerTexture = 0;
GLuint playerTexture2 = 0;
GLuint playerTexture3 = 0;
GLuint playerTexture4 = 0;
GLuint playerAttackTexture = 0;
GLuint enemyTexture = 0;
GLuint enemyTexture2 = 0;
GLuint interceptTexture = 0;
GLuint goalTexture = 0;
GLuint goalTexture2 = 0;
GLuint screenTexture = 0;
GLuint skyLineTexture = 0;

Charater* player;
screen* scr;
Background* background;
bool screenOn;
int level = 1;

std::vector<Actor*> colList;
std::vector<Enemy*> killList;
std::vector<MovingPlatform*> moveList;
std::vector<EnemyIntercept*> interceptList;
std::vector<Goal*> goalList;

std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();

font_data scoreFont;

//OPENGL FUNCTION PROTOTYPES
void display();				//called in winmain to draw everything to the screen
void reshape(int width, int height); //called when the window is resized
GLuint loadPNG(char* name, GLint param);
void loadLevelOne();
void reset(bool kill);
void init();				//called in winmain when the program starts.
void processKeys();         //called in winmain to process keyboard input
void update();				//called in winmain to update variables

/*************    START OF OPENGL FUNCTIONS   ****************/
// display object on screen an give then there texture
void display()									
{
	float hold = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	
	if (screenOn == true)
	{
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, screenTexture);
		scr->colour(1, 1, 1);
		scr->display();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		if (keys[VK_RETURN])
		{
			scr->~screen();
			screenOn = false;
		}
	}
	else
	{
		glPushMatrix();
		glTranslatef(-cameraMoveX + 250, -cameraMoveY + 300, 0.0f);

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBindTexture(GL_TEXTURE_2D, skyLineTexture);
		background->colour(1, 1, 1);
		background->display();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		if (!player->getAttacking())
		{
			if (player->moving())
			{
				if (player->getXVel() >= 0)
				{
					if (!player->animation())
					{
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						glBindTexture(GL_TEXTURE_2D, playerTexture2);
						player->colour(1, 1, 1);
						player->display();
						glDisable(GL_BLEND);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						glBindTexture(GL_TEXTURE_2D, playerTexture);
						player->colour(1, 1, 1);
						player->display();
						glDisable(GL_BLEND);
						glDisable(GL_TEXTURE_2D);
					}
				}
				else if (player->getXVel() < 0)
				{
					if (!player->animation())
					{
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						glBindTexture(GL_TEXTURE_2D, playerTexture3);
						player->colour(1, 1, 1);
						player->display();
						glDisable(GL_BLEND);
						glDisable(GL_TEXTURE_2D);
					}
					else {
						glEnable(GL_TEXTURE_2D);
						glEnable(GL_BLEND);
						glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
						glBindTexture(GL_TEXTURE_2D, playerTexture4);
						player->colour(1, 1, 1);
						player->display();
						glDisable(GL_BLEND);
						glDisable(GL_TEXTURE_2D);
					}
				}
			}
			else {
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, playerTexture);
				player->colour(1, 1, 1);
				player->display();
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
			}
		}
		else
		{
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, playerAttackTexture);
			player->colour(1, 1, 1);
			player->display();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}
		for (Goal* goal : goalList)
		{
			if (goal->getReach())
			{
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, goalTexture2);
				goal->colour(1, 1, 1);
				goal->display();
				glDisable(GL_BLEND);
			}
			else
			{
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, goalTexture);
				goal->colour(1, 1, 1);
				goal->display();
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
			}
		}

		for (Enemy* enemy : killList)
		{
			if (enemy->getSpeed() >= 0)
			{
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, enemyTexture2);
				enemy->colour(1, 1, 1);
				enemy->display();
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
			}
			else if (enemy->getSpeed() < 0)
			{
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				glBindTexture(GL_TEXTURE_2D, enemyTexture);
				enemy->colour(1, 1, 1);
				enemy->display();
				glDisable(GL_BLEND);
				glDisable(GL_TEXTURE_2D);
			}
		}

		for (EnemyIntercept* intercept : interceptList)
		{
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, interceptTexture);
			intercept->colour(1, 1, 1);
			intercept->display();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}

		for (Actor* a : colList)
		{
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, soilTexture);
			a->colour(1, 1, 1);
			a->display();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}

		for (MovingPlatform* m : moveList) {
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBindTexture(GL_TEXTURE_2D, woodTexture);
			m->colour(1, 1, 1);
			m->display();
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);
		}

		

		glPopMatrix();

		glColor3f(0.6, 0.6, 0.6);
		print(scoreFont, 50, 50, "%7.1f", score);

	}
	glFlush();
}

void reshape(int width, int height)		// Resize the OpenGL window
{
	screenWidth=width; screenHeight = height;           // to ensure the mouse coordinates match 
														// we will use these values to set the coordinate system

	glViewport(0,0,width,height);						// Reset the current viewport

	glMatrixMode(GL_PROJECTION);						// select the projection matrix stack
	glLoadIdentity();									// reset the top of the projection matrix to an identity matrix

	gluOrtho2D(0,screenWidth,0,screenHeight);           // set the coordinate system for the window

	glMatrixMode(GL_MODELVIEW);							// Select the modelview matrix stack
	glLoadIdentity();									// Reset the top of the modelview matrix to an identity matrix
}


// load in PNG for use as textures
GLuint loadPNG(char* name, GLint param)
{
	// Texture loading object
	nv::Image img;
	GLuint myTextureID;

	// Return true on success
	if (img.loadImageFromFile(name))
	{

		glGenTextures(1, &myTextureID);
		glBindTexture(GL_TEXTURE_2D, myTextureID);
		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
		glTexImage2D(GL_TEXTURE_2D, 0, img.getInternalFormat(), img.getWidth(), img.getHeight(), 0, img.getFormat(), img.getType(), img.getLevel(0));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 16.0f);
	}
	else
	{
		MessageBox(NULL, "Failed to load texture", "End of the world", MB_OK | MB_ICONINFORMATION);
	}

	return myTextureID;
}

// load in actors for level 1
void loadLevelOne()
{
	colList.push_back(new Actor(500, -100, 400, 2000));
	colList.push_back(new Actor(1000, -100, 500, 1000));
	colList.push_back(new Actor(3000, 0, 400, 1000));
	colList.push_back(new Actor(4000, 0, 550, 500));
	colList.push_back(new Actor(5500, 0, 600, 500));
	
	moveList.push_back(new MovingPlatform(2000, 200, 50, 300, 30000));
	moveList.push_back(new MovingPlatform(4500, 250, 50, 147, 30000));
	moveList.push_back(new MovingPlatform(5000, 300, 50, 147, 30000));
	
	interceptList.push_back(new EnemyIntercept(550, 75, 100, 100));
	interceptList.push_back(new EnemyIntercept(5300, 250, 100, 100));

	killList.push_back(new Enemy(1250, 200, 100, 100, 50000));
	killList.push_back(new Enemy(4000, 350, 100, 100, 50000));
	player = new Charater(100, 200, 100, 100);
	
	goalList.push_back(new Goal(3050, 250, 100, 69));
	goalList.push_back(new Goal(5500, 350, 100, 69));
}

// load in actors for level 2
void loadLevelTwo()
{
	colList.push_back(new Actor(500, 0, 250, 2000));
	colList.push_back(new Actor(2000, 0, 500, 500));
	colList.push_back(new Actor(5000, 0, 600, 4000));
	colList.push_back(new Actor(4400, 400, 50, 400));
	colList.push_back(new Actor(5000, 600, 50, 400));
	colList.push_back(new Actor(4600, 800, 50, 200));
	colList.push_back(new Actor(4000, 1000, 50, 600));
	colList.push_back(new Actor(6500, 0, 1200, 1000));
	colList.push_back(new Actor(2400, 1000, 50, 500));

	interceptList.push_back(new EnemyIntercept(550, 50, 100, 100));
	interceptList.push_back(new EnemyIntercept(3500, 250, 100, 100));

	moveList.push_back(new MovingPlatform(2600, 250,50,236,30000));
	moveList.push_back(new MovingPlatform(5500, 600, 50,236, 40000));
	moveList.push_back(new MovingPlatform(3400, 1000, 50, 236, 20000));
	moveList.push_back(new MovingPlatform(3000, 1000, 50, 236, 10000));

	killList.push_back(new Enemy(1950, 310, 100, 100, 50000));
	killList.push_back(new Enemy(5000, 700, 100, 100, 40000));

	player = new Charater(100, 250, 100, 100);
	
	goalList.push_back(new Goal(2150, 300, 100, 69));
	goalList.push_back(new Goal(700, 175, 100, 69));
	goalList.push_back(new Goal(4000, 1060, 100, 69));
	goalList.push_back(new Goal(6500, 650, 100, 69));
	goalList.push_back(new Goal(2400, 1060, 100, 69));
}

void reset(bool kill)
{
	colList.clear();
	moveList.clear();
	interceptList.clear(); 
	killList.clear();
	goalList.clear();
	if (kill)
	{
		score = 0;
	}
}

void init()
{
	glClearColor(1.0,1.0,1.0,0.0);						//sets the clear colour to yellow
				
	//glClear(GL_COLOR_BUFFER_BIT) in the display function	
	//will clear the buffer to this colour.

	soilTexture = loadPNG("soil.png", GL_REPEAT);
	woodTexture = loadPNG("wood.png", GL_REPEAT);

	playerTexture = loadPNG("character.png", GL_CLAMP_TO_EDGE);
	playerTexture2 = loadPNG("character2.png", GL_CLAMP_TO_EDGE);
	playerTexture3 = loadPNG("character3.png", GL_CLAMP_TO_EDGE);
	playerTexture4 = loadPNG("character4.png", GL_CLAMP_TO_EDGE);
	playerAttackTexture = loadPNG("attack.png",GL_CLAMP_TO_EDGE);

	interceptTexture = loadPNG("moleEnemy.png", GL_CLAMP_TO_EDGE);

	enemyTexture = loadPNG("enemy.png", GL_CLAMP_TO_EDGE);
	enemyTexture2 = loadPNG("enemy2.png", GL_CLAMP_TO_EDGE);

	goalTexture = loadPNG("goal.png", GL_CLAMP_TO_EDGE);
	goalTexture2 = loadPNG("goal2.png", GL_CLAMP_TO_EDGE);

	screenTexture = loadPNG("screen.png", GL_CLAMP_TO_BORDER);
	skyLineTexture = loadPNG("skyline.png", GL_CLAMP_TO_BORDER);

	scoreFont.init("LHANDW.TTF", 22);

	scr = new screen(((float)screenWidth/2),((float)screenHeight/2),screenHeight,screenWidth);
	screenOn = true;
	background = new Background(100, 500, 10000, 10000);
	loadLevelOne();
}
void processKeys()
{
	if(keys[VK_RIGHT])
	{
		player->moveRight();
		//cameraMove -= 1;
		//glViewport(cameraMove, 0, screenWidth, screenHeight);
	}
	else if (!keys[VK_LEFT]) 
	{ 
		player->stop(); 
	}
	if(keys[VK_LEFT])
	{
		player->moveLeft();
		//cameraMove += 1;
		//glViewport(cameraMove, 0, screenWidth, screenHeight);
	}
	else if(!keys[VK_RIGHT])
	{ 
		player->stop(); 
	}
	if (keys[VK_SPACE])
	{
		player->jump();
		
	}
	if (keys[VK_UP])
	{
		player->attack();
		//player->setYVel(100);
	}
	else {
		player->stopAttack();
	}
}
void update()
{
	needed = goalList.size();
	int numEnemy = 0;
	int numIntercept = 0;
	bool land = false;

	if (screenOn)
	{
		scr->screenHeight(screenHeight);
		scr->screenWidth(screenWidth);
	}
	else
	{

		if (collected == needed)
		{
			level++;
			needed = 0;
			collected = 0;
			scr->screenHeight(screenHeight);
			scr->screenWidth(screenWidth);
			screenOn = true;
			reset(false);
			if (level == 1)
			{
				loadLevelOne();
			}
			else if (level == 2)
			{
				loadLevelTwo();
			}
			else if (level == 3)
			{
				level = 0;
				score = 0;
			}
		}

		for (Goal* goal : goalList)
		{

			if (goal->isCol(player))
			{
				if (!goal->getReach()) {
					score = score + 200;
					collected++;
				}
				goal->reached();
				
			}
		}


		for (MovingPlatform* move : moveList) {
			move->update();
			if (move->isCol(player))
			{
				player->setYVel(-(move->getSpeed()));
				player->land();
			}
			else {
				player->fall();
			}
		}
		player->update();
		background->move(player->getXpos());

		if (player->getDead())
		{
			reset(true);
			collected = 0;
			if (level == 1)
			{
				loadLevelOne();
			}
			else if (level == 2)
			{
				loadLevelTwo();
			}
			player->setDead();
		}

		for (Enemy* enemy : killList) {
			enemy->update();
			if (enemy->isCol(player) && !player->getAttacking())
			{
				//player->reset();
				reset(true);
				collected = 0;
				if (level == 1)
				{
					loadLevelOne();
				}
				else if (level == 2)
				{
					loadLevelTwo();
				}
			}
			else if (enemy->isCol(player) && player->getAttacking())
			{
				killList.erase(killList.begin() + numEnemy);
				score = score + 100;
			}
			numEnemy++;
		}


		for (EnemyIntercept* i : interceptList) {
			i->update();
			if (i->isColIntercept(player))
			{
				i->collide();
			}
			else {
				i->returnDown();
			}
			if (i->isCol(player) && !player->getAttacking())
			{
				//player->reset();
				reset(true);
				collected = 0;
				if (level == 1)
				{
					loadLevelOne();
				}
				else if (level == 2)
				{
					loadLevelTwo();
				}
			}
			else if (i->isCol(player) && player->getAttacking())
			{
				interceptList.erase(interceptList.begin() + numIntercept);
				score = score + 100;
			}
			numIntercept++;
		}

		cameraMoveX = player->getXpos();

		int delta = (player->getYpos() - cameraMoveY);

		cameraMoveY = cameraMoveY + delta * detalTime;

		//cameraMoveY = player->getYpos();


		for (Goal* goal : goalList)
		{
			goal->update();
		}
	}
	///*spin += speed;
	//if(spin > 360)
	//	spin = 0;*/


}
/**************** END OPENGL FUNCTIONS *************************/

//WIN32 functions
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
void KillGLWindow();									// releases and destroys the window
bool CreateGLWindow(char* title, int width, int height); //creates the window
int WINAPI WinMain(	HINSTANCE, HINSTANCE, LPSTR, int);  // Win32 main function

//win32 global variabless
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application


/******************* WIN32 FUNCTIONS ***************************/
int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	bool	done=false;								// Bool Variable To Exit Loop


	AllocConsole();
	FILE *stream;
	freopen_s(&stream, "CONOUT$", "w", stdout);
	
	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL Win32 Example",screenWidth,screenHeight))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=true;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			if(keys[VK_ESCAPE])
				done = true;

			processKeys();			//process keyboard
			
			update();
			display();					// Draw The Scene
			//update();					// update variables
			SwapBuffers(hDC);			// Swap Buffers (Double Buffering)
			std::chrono::high_resolution_clock::time_point finalTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> timeElapsed = finalTime - beginTime;
			detalTime = timeElapsed.count() / 1000;
			beginTime = finalTime;
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (int)(msg.wParam);						// Exit The Program
}

//WIN32 Processes function - useful for responding to user inputs or other events.
LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		break;

		case WM_SIZE:								// Resize The OpenGL Window
		{
			reshape(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
		break;

		case WM_LBUTTONDOWN:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight - HIWORD(lParam);
				LeftPressed = true;
			}
		break;

		case WM_LBUTTONUP:
			{
	            LeftPressed = false;
			}
		break;

		case WM_MOUSEMOVE:
			{
	            mouse_x = LOWORD(lParam);          
				mouse_y = screenHeight  - HIWORD(lParam);
			}
		break;
		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = true;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}
		break;
		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = false;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}
		break;
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

void KillGLWindow()								// Properly Kill The Window
{
	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*/
 
bool CreateGLWindow(char* title, int width, int height)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;											// Return FALSE
	}
	
	dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
	dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		24,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		24,											// 24Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return false;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	reshape(width, height);					// Set Up Our Perspective GL Screen

	init();
	
	return true;									// Success
}



