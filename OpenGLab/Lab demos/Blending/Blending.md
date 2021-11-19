- Blending is used to combine the color of a given pixel that is about to be drawn with the pixel that is already on the screen. 

- How the colors are combined is based on the alpha value of the colors, and/or the blending function that is being used. 

- Alpha is a 4th color component usually specified at the end.

- We use glColor4f() instead of glColor3f().

- An alpha value of 0.0 would mean that the material is completely transparent. 
	- A value of 1.0 would be totally opaque.

- Blending Equation
	- (Rs As + Rd (1 - As), Gs As + Gd (1 - As), Bs As + Bs (1 - As), As As + Ad (1 - As))
	- Where R = red, d = destination (already drawn), s = source (to be drawn).

- To set up blending we first need to enable its configuration (in InitGL()), . 
	- Then we set the equation up, 
	- Turn off depth-buffer writing when drawing transparent objects.

- Example
	```
	glColor4f(1.0f,1.0f,1.0f,0.5f);		// Full Brightness, 50% Alpha ( NEW )
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);	// Blending Function For Translucency Based On Source Alpha Value
	```
	- This sets the drawing brightness to full brightness with 50% alpha
	- See the examples in DrawGlScene().

