/*
*		This Code Was Created By Jeff Molofee 2000
*		A HUGE Thanks To Fredric Echols For Cleaning Up
*		And Optimizing This Code, Making It More Flexible!
*		If You've Found This Code Useful, Please Let Me Know.
*		Visit My Site At nehe.gamedev.net
*/

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
//#include <gl\glaux.h>		// Header File For The Glaux Library
#include <cmath>
HDC hDC = NULL; // Private GDI Device Context
HGLRC hRC = NULL; // Permanent Rendering Context
HWND hWnd = NULL; // Holds Our Window Handle
HINSTANCE hInstance; // Holds The Instance Of The Application

bool keys[256]; // Array Used For The Keyboard Routine
bool active = TRUE; // Window Active Flag Set To TRUE By Default
bool fullscreen = TRUE; // Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); // Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height) // Resize And Initialize The GL Window
{
	if (height == 0) // Prevent A Divide By Zero By
	{
		height = 1; // Making Height Equal One
	}

	glViewport(0, 0, width, height); // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION); // Select The Projection Matrix
	glLoadIdentity(); // Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glFrustum(1.0, 1.0, 1.0, 1.0, 1., 100.0);
	glOrtho(1.0, 1.0, 1.0, 1.0, 1., 100.0);
	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity(); // Reset The Modelview Matrix
}

int InitGL(GLvoid) // All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH); // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f); // Black Background
	glClearDepth(1.0f); // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST); // Enables Depth Testing
	glDepthFunc(GL_LEQUAL); // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Really Nice Perspective Calculations
	return TRUE; // Initialization Went OK
}

//float angle = 0;
// GLfloat xRotated = 0, yRotated = 0, zRotated = 0;
GLfloat delta = 0;


void drawSquare(bool isRed = true, float z = 0)
{
	glBegin(GL_QUADS);

	if (isRed)
		glColor3f(1.0f, 0.0f, 0.0f);
	else
		glColor3f(0.0f, 0.0f, 1.0f);

	glVertex3i(1, 1, z);
	glVertex3i(-1, 1, z);
	glVertex3i(-1, -1, z);
	glVertex3i(1, -1, z);

	glEnd();
}

void DrawCircle(GLfloat cX = 0, GLfloat cY = 0, double radius = 2,
                bool isRed = true, int step = 100)
{
	if (isRed)
		glColor3f(1, 0, 0);
	else
		glColor3f(0, 0, 1);

	GLfloat x, y, temp, xPrev, yPrev;
	glBegin(GL_TRIANGLES);
	temp = 360.0 / (float)step;
	long double PI = 3.14;
	xPrev = cX + radius * cos(0);
	yPrev = cY + radius * sin(0);
	for (float i = 0; i <= 361; i += temp)
	{
		x = cX + radius * cos(i * PI / 180.0f);
		y = cY + radius * sin(i * PI / 180.0f);
		glVertex2f(cX, cY);
		glVertex2f(xPrev, yPrev);
		glVertex2f(x, y);
		xPrev = x;
		yPrev = y;
	}
	glEnd();
}

void moonAndEarth()
{
	glTranslated(0, 0, -35);

	glColor3f(0.0f, 0.0f, 1.0f);
	DrawCircle(0, 0, 4);

	// change the order (shift rotation up) => camera (eye) direction won't change when coords changes
	glRotatef(delta++, 0, 1, 0);

	glColor3f(1.0f, 0.0f, 0.0f);
	DrawCircle(10, 0, 2);
}

void cubeViaSquads()
{
	glShadeModel(GL_FLAT);

	// DO NOT put transformation between glBegin and glEnd
	delta -= 2;

	// glTranslatef(0, 0, delta * .1);
	// glRotatef(delta * .5, 1, 1, 0);

	// glScalef(1, 2, 3);
	glColor3f(1.0f, 1.0f, 0.0f);

	glBegin(GL_QUADS); // Draw The Cube Using quads

	glVertex3f(1.0f, 1.0f, -1.0f); //   (Top)
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	glVertex3f(1.0f, -1.0f, 1.0f); // (Bottom)
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f); // (front)
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glVertex3f(1.0f, -1.0f, -1.0f); // (Back)
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	glVertex3f(-1.0f, 1.0f, 1.0f); //  (Left)
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);

	glVertex3f(1.0f, 1.0f, -1.0f); // (Right)
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);

	glEnd();
}

void lookAtExample2()
{
	// position the camera before drawing..
	if (keys[VK_SPACE])
		gluLookAt(0, 0, 0, 0, 0, -1, 0, 1, 0);
	else
		gluLookAt(0, 0, -20, 0, 0, 1, 0, 1, 0);

	glTranslated(0, 0, -10); // passing a vector, not a point
	drawSquare(); // red
	glTranslated(0, 0, -1); // change z
	drawSquare(false); // blue

	// play with up
}

/*
push-pop principles:
1- you are dealing with just one matrix, only one
2- any transformation you do is applied on the top matrix of the stack
3- pushing is copying the current matrix and pasting the new copy on top of the current matrix (i.e. you save the last state of the current matrix, and every change you do is applied on the new matrix only, so at any time you can return to the old matrix using pop).
4- number of pops must be equal to number of pushes
 */
void pushPopExample()
{
	glTranslated(2, 0, -10);
	glPushMatrix(); // current 2,0,-10

	glTranslated(-4, 0, 0); // current -2,0,-10
	glPushMatrix(); // stack: -2,0,-10 -> -2,0,-10

	glTranslated(0, -3, 0); // stack: -2, 0, -10 -> - 2, -3, -10
	glPushMatrix(); //  -2, 0, -10 -> - 2, -3, -10 -> - 2, -3, -10

	// drawings
	drawSquare(); // draw at -2,-3,-10

	glPopMatrix(); // back to -2,-3,-10 and draw
	drawSquare();

	glPopMatrix(); // back to -2,0,-10 and draw
	drawSquare(false);

	glPopMatrix();
	// if not exist -> there will be additional matrix at every DrawGlScene(), then a stackoverflow will happen
}


void lookAtExample() // lots of exercises on this next time: playing with all triplets
{
	glTranslated(0, 0, -10);

	// glMatrixMode(GL_MODELVIEW); // default, important but no need for it
	// look at (0,0,-10) does not affect the scene coordinates
	// but eye-point can be translated in all directions
	// Important: The UP vector must not be parallel to the line of sight from the eye point to the reference point.
	// up vector analogy = rotating the camera or rotating the scene
	gluLookAt(0, 0, 0,
	          0, 0, -1,
	          0, 1, 0);

	drawSquare(); // on z = 0,
}

GLfloat cx = -40;

GLdouble angle = 0;


GLfloat x = -15;

void homework()
{
	double radius = 1;

	glTranslated(0, 0, -15);
	DrawCircle(0, 0, radius);
	if (x < -2 * radius || angle >= 180)
	{
		// move case
		x += 1;
		DrawCircle(x, 0, radius, false);
	}
	else
	{
		// collision
		glRotated(angle, 0, 0, -1);
		angle += 2;
		x = 2 * radius;
		DrawCircle(-2 * radius, 0, radius, false);
	}
}

void DrawGLScene(GLvoid) // Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear Screen And Depth Buffer
	glLoadIdentity(); // Reset The Current Modelview Matrix

	// lookAtExample();
	// lookAtExample2();
	// pushPopExample();
	// pushPopExample2();

	// DrawCircle();
	homework();

	glFlush(); //DO NOT REMOVE THIS
	SwapBuffers(hDC);
}

GLvoid KillGLWindow(GLvoid) // Properly Kill The Window
{
	if (fullscreen) // Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0); // If So Switch Back To The Desktop
		ShowCursor(TRUE); // Show Mouse Pointer
	}

	if (hRC) // Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL)) // Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC)) // Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL; // Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC)) // Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL; // Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd)) // Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL; // Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance)) // Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL; // Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, byte bits, bool fullscreenflag)
{
	GLuint PixelFormat; // Holds The Results After Searching For A Match
	WNDCLASS wc; // Windows Class Structure
	DWORD dwExStyle; // Window Extended Style
	DWORD dwStyle; // Window Style
	RECT WindowRect; // Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0; // Set Left Value To 0
	WindowRect.right = (long)width; // Set Right Value To Requested Width
	WindowRect.top = (long)0; // Set Top Value To 0
	WindowRect.bottom = (long)height; // Set Bottom Value To Requested Height

	fullscreen = fullscreenflag; // Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL); // Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC; // Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc; // WndProc Handles Messages
	wc.cbClsExtra = 0; // No Extra Window Data
	wc.cbWndExtra = 0; // No Extra Window Data
	wc.hInstance = hInstance; // Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Load The Arrow Pointer
	wc.hbrBackground = NULL; // No Background Required For GL
	wc.lpszMenuName = NULL; // We Don't Want A Menu
	wc.lpszClassName = "OpenGL"; // Set The Class Name

	if (!RegisterClass(&wc)) // Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (fullscreen) // Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings; // Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings)); // Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings); // Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width; // Selected Screen Width
		dmScreenSettings.dmPelsHeight = height; // Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits; // Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(
				NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?",
				"NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE; // Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE; // Return FALSE
			}
		}
	}

	if (fullscreen) // Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW; // Window Extended Style
		dwStyle = WS_POPUP; // Windows Style
		ShowCursor(FALSE); // Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE; // Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW; // Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle); // Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle, // Extended Style For The Window
	                            "OpenGL", // Class Name
	                            title, // Window Title
	                            dwStyle | // Defined Window Style
	                            WS_CLIPSIBLINGS | // Required Window Style
	                            WS_CLIPCHILDREN, // Required Window Style
	                            0, 0, // Window Position
	                            WindowRect.right - WindowRect.left, // Calculate Window Width
	                            WindowRect.bottom - WindowRect.top, // Calculate Window Height
	                            NULL, // No Parent Window
	                            NULL, // No Menu
	                            hInstance, // Instance
	                            NULL))) // Dont Pass Anything To WM_CREATE
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	static PIXELFORMATDESCRIPTOR pfd = // pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
		1, // Version Number
		PFD_DRAW_TO_WINDOW | // Format Must Support Window
		PFD_SUPPORT_OPENGL | // Format Must Support OpenGL
		PFD_DOUBLEBUFFER, // Must Support Double Buffering
		PFD_TYPE_RGBA, // Request An RGBA Format
		bits, // Select Our Color Depth
		0, 0, 0, 0, 0, 0, // Color Bits Ignored
		0, // No Alpha Buffer
		0, // Shift Bit Ignored
		0, // No Accumulation Buffer
		0, 0, 0, 0, // Accumulation Bits Ignored
		16, // 16Bit Z-Buffer (Depth Buffer)  
		0, // No Stencil Buffer
		0, // No Auxiliary Buffer
		PFD_MAIN_PLANE, // Main Drawing Layer
		0, // Reserved
		0, 0, 0 // Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd))) // Did We Get A Device Context?
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd))) // Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd)) // Are We Able To Set The Pixel Format?
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC))) // Are We Able To Get A Rendering Context?
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC)) // Try To Activate The Rendering Context
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW); // Show The Window
	SetForegroundWindow(hWnd); // Slightly Higher Priority
	SetFocus(hWnd); // Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height); // Set Up Our Perspective GL Screen

	if (!InitGL()) // Initialize Our Newly Created GL Window
	{
		KillGLWindow(); // Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE; // Return FALSE
	}

	return TRUE; // Success
}

LRESULT CALLBACK WndProc(HWND hWnd, // Handle For This Window
                         UINT uMsg, // Message For This Window
                         WPARAM wParam, // Additional Message Information
                         LPARAM lParam) // Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg) // Check For Windows Messages
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE: // Watch For Window Activate Message
		{
			if (!HIWORD(wParam)) // Check Minimization State
			{
				active = TRUE; // Program Is Active
			}
			else
			{
				active = FALSE; // Program Is No Longer Active
			}

			return 0; // Return To The Message Loop
		}

	case WM_SYSCOMMAND: // Intercept System Commands
		{
			switch (wParam) // Check System Calls
			{
			case SC_SCREENSAVE: // Screensaver Trying To Start?
			case SC_MONITORPOWER: // Monitor Trying To Enter Powersave?
				return 0; // Prevent From Happening
			}
			break; // Exit
		}

	case WM_CLOSE: // Did We Receive A Close Message?
		{
			PostQuitMessage(0); // Send A Quit Message
			return 0; // Jump Back
		}

	case WM_KEYDOWN: // Is A Key Being Held Down?
		{
			keys[wParam] = TRUE; // If So, Mark It As TRUE
			return 0; // Jump Back
		}

	case WM_KEYUP: // Has A Key Been Released?
		{
			keys[wParam] = FALSE; // If So, Mark It As FALSE
			return 0; // Jump Back
		}

	case WM_SIZE: // Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam)); // LoWord=Width, HiWord=Height
			return 0; // Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, // Instance
                   HINSTANCE hPrevInstance, // Previous Instance
                   LPSTR lpCmdLine, // Command Line Parameters
                   int nCmdShow) // Window Show State
{
	MSG msg; // Windows Message Structure
	BOOL done = FALSE; // Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE; // Windowed Mode
	}

	// Create Our OpenGL Window
	char c[] = "test 2";
	if (!CreateGLWindow(c, 640, 480, 16, fullscreen))
	{
		return 0; // Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 50, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}
