/* CS580 Homework 3 */

#include	"stdafx.h"
#include	"stdio.h"
#include	"math.h"
#include	"Gz.h"
#include	"rend.h"

#define PI (3.1415926535f)

int GzRotXMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value
	if (mat == NULL)
	{
		return GZ_FAILURE;
	}
	float rDegree = degree * (PI / 180);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat[i][j] = 0;
		}
	}
	mat[0][0] = 1;
	mat[1][1] = cos(rDegree);
	mat[1][2] = -sin(rDegree);
	mat[2][1] = sin(rDegree);
	mat[2][2] = cos(rDegree);
	mat[3][3] = 1;
	return GZ_SUCCESS;
}


int GzRotYMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value
	if (mat == NULL)
	{
		return GZ_FAILURE;
	}
	float rDegree = degree * (PI / 180);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat[i][j] = 0;
		}
	}
	mat[0][0] = cos(rDegree);
	mat[0][2] = sin(rDegree);
	mat[1][1] = 1;
	mat[2][0] = -sin(rDegree);
	mat[2][2] = cos(rDegree);
	mat[3][3] = 1;
	return GZ_SUCCESS;
}


int GzRotZMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
	if (mat == NULL)
	{
		return GZ_FAILURE;
	}
	float rDegree = degree * (PI / 180);
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat[i][j] = 0;
		}
	}
	mat[0][0] = cos(rDegree);
	mat[0][1] = -sin(rDegree);
	mat[1][0] = sin(rDegree);
	mat[1][1] = cos(rDegree);
	mat[2][2] = 1;
	mat[3][3] = 1;
	return GZ_SUCCESS;
}


int GzTrxMat(GzCoord translate, GzMatrix mat)
{
// Create translation matrix
// Pass back the matrix using mat value
	if (translate == NULL || mat == NULL)
	{
		return GZ_FAILURE;
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat[i][j] = i == j ? 1 : 0;
		}
	}
	mat[0][3] = translate[X];
	mat[1][3] = translate[Y];
	mat[2][3] = translate[Z];
	return GZ_SUCCESS;
}


int GzScaleMat(GzCoord scale, GzMatrix mat)
{
// Create scaling matrix
// Pass back the matrix using mat value
	if (scale == NULL || mat == NULL)
	{
		return GZ_FAILURE;
	}
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			mat[i][j] = 0;
		}
	}
	mat[0][0] = scale[X];
	mat[1][1] = scale[Y];
	mat[2][2] = scale[Z];
	mat[3][3] = 1;
	return GZ_SUCCESS;
}


//----------------------------------------------------------
// Begin main functions

int GzNewRender(GzRender **render, GzDisplay	*display)
{
/*  
- malloc a renderer struct 
- setup Xsp and anything only done once 
- save the pointer to display 
- init default camera 
*/ 
	if (render != NULL && display != NULL)
	{
		// malloc a renderer struct
		*render = (GzRender *)malloc(sizeof(GzRender));

		// setup Xsp and anything only done once
		int xs = display->xres;
		int ys = display->yres;
		(*render)->Xsp[0][0] = xs / 2.0f;
		(*render)->Xsp[0][1] = 0;
		(*render)->Xsp[0][2] = 0;
		(*render)->Xsp[0][3] = xs / 2.0f;
		(*render)->Xsp[1][0] = 0;
		(*render)->Xsp[1][1] = -ys / 2.0f;
		(*render)->Xsp[1][2] = 0;
		(*render)->Xsp[1][3] = ys / 2.0f;
		(*render)->Xsp[2][0] = 0;
		(*render)->Xsp[2][1] = 0;
		(*render)->Xsp[2][2] = MAXINT;
		(*render)->Xsp[2][3] = 0;
		(*render)->Xsp[3][0] = 0;
		(*render)->Xsp[3][1] = 0;
		(*render)->Xsp[3][2] = 0;
		(*render)->Xsp[3][3] = 1;
		(*render)->matlevel = -1;

		// save the pointer to display
		(*render)->display = display;

		// init default camera
		(*render)->camera.FOV = DEFAULT_FOV;
		(*render)->camera.lookat[X] = 0;
		(*render)->camera.lookat[Y] = 0;
		(*render)->camera.lookat[Z] = 0;
		(*render)->camera.position[X] = DEFAULT_IM_X;
		(*render)->camera.position[Y] = DEFAULT_IM_Y;
		(*render)->camera.position[Z] = DEFAULT_IM_Z;
		(*render)->camera.worldup[X] = 0;
		(*render)->camera.worldup[Y] = 1;
		(*render)->camera.worldup[Z] = 0;

		// set default shading values
		(*render)->interp_mode = GZ_RGB_COLOR;
		(*render)->numlights = 0;
		GzColor ka = DEFAULT_AMBIENT;
		GzColor kd = DEFAULT_DIFFUSE;
		GzColor ks = DEFAULT_SPECULAR;
		(*render)->Ka[RED] = ka[RED];
		(*render)->Ka[GREEN] = ka[GREEN];
		(*render)->Ka[BLUE] = ka[BLUE];
		(*render)->Kd[RED] = kd[RED];
		(*render)->Kd[GREEN] = kd[GREEN];
		(*render)->Kd[BLUE] = kd[BLUE];
		(*render)->Ks[RED] = ks[RED];
		(*render)->Ks[GREEN] = ks[GREEN];
		(*render)->Ks[BLUE] = ks[BLUE];
		(*render)->spec = DEFAULT_SPEC;

		return GZ_SUCCESS;
	}
	return GZ_FAILURE;
}


int GzFreeRender(GzRender *render)
{
/* 
-free all renderer resources
*/
	if (render != NULL)
	{
		free(render);
	}
	return GZ_SUCCESS;
}


int GzBeginRender(GzRender *render)
{
/*  
- setup for start of each frame - init frame buffer color,alpha,z
- compute Xiw and projection xform Xpi from camera definition 
- init Ximage - put Xsp at base of stack, push on Xpi and Xiw 
- now stack contains Xsw and app can push model Xforms when needed 
*/ 
	int status = GZ_SUCCESS;
	if (render != NULL && render->display != NULL)
	{
		// init frame buffer, color, alpha, z
		if (render->display->fbuf == NULL)
		{
			render->display->fbuf = (GzPixel *)malloc(sizeof(GzPixel) * render->display->xres * render->display->yres);
		}
		status |= GzInitDisplay(render->display);
		render->flatcolor[RED] = 0;
		render->flatcolor[GREEN] = 0;
		render->flatcolor[BLUE] = 0;

		// compute Xiw and projection xform Xpi from camera definition
		
		// Xpi
		float dInv = tan(((render)->camera.FOV / 2) * (PI / 180));
		(render)->camera.Xpi[0][0] = 1;
		(render)->camera.Xpi[0][1] = 0;
		(render)->camera.Xpi[0][2] = 0;
		(render)->camera.Xpi[0][3] = 0;
		(render)->camera.Xpi[1][0] = 0;
		(render)->camera.Xpi[1][1] = 1;
		(render)->camera.Xpi[1][2] = 0;
		(render)->camera.Xpi[1][3] = 0;
		(render)->camera.Xpi[2][0] = 0;
		(render)->camera.Xpi[2][1] = 0;
		(render)->camera.Xpi[2][2] = dInv;
		(render)->camera.Xpi[2][3] = 0;
		(render)->camera.Xpi[3][0] = 0;
		(render)->camera.Xpi[3][1] = 0;
		(render)->camera.Xpi[3][2] = dInv;
		(render)->camera.Xpi[3][3] = 1;

		// Xiw
		GzCoord cl, upPrime, cameraZaxis, cameraYaxis, cameraXaxis;
		
		// Z = cl / ||cl||
		cl[X] = render->camera.lookat[X] - render->camera.position[X];
		cl[Y] = render->camera.lookat[Y] - render->camera.position[Y];
		cl[Z] = render->camera.lookat[Z] - render->camera.position[Z];
		float mag_cl = sqrt(pow(cl[X],2) + pow(cl[Y],2) + pow(cl[Z],2));
		cameraZaxis[X] = cl[X] / mag_cl;
		cameraZaxis[Y] = cl[Y] / mag_cl;
		cameraZaxis[Z] = cl[Z] / mag_cl;
		
		// up' = up - (up . Z)Z
		// Y = up' / ||up'||
		float upDotZ =
			render->camera.worldup[X] * cameraZaxis[X] +
			render->camera.worldup[Y] * cameraZaxis[Y] +
			render->camera.worldup[Z] * cameraZaxis[Z];
		upPrime[X] = render->camera.worldup[X] - (upDotZ * cameraZaxis[X]);
		upPrime[Y] = render->camera.worldup[Y] - (upDotZ * cameraZaxis[Y]);
		upPrime[Z] = render->camera.worldup[Z] - (upDotZ * cameraZaxis[Z]);
		float mag_upPrime = sqrt(pow(upPrime[X], 2) + pow(upPrime[Y], 2) + pow(upPrime[Z], 2));
		cameraYaxis[X] = upPrime[X] / mag_upPrime;
		cameraYaxis[Y] = upPrime[Y] / mag_upPrime;
		cameraYaxis[Z] = upPrime[Z] / mag_upPrime;

		// X = (Y x X)
		cameraXaxis[X] = cameraYaxis[Y] * cameraZaxis[Z] - cameraYaxis[Z] * cameraZaxis[Y];
		cameraXaxis[Y] = cameraYaxis[Z] * cameraZaxis[X] - cameraYaxis[X] * cameraZaxis[Z];
		cameraXaxis[Z] = cameraYaxis[X] * cameraZaxis[Y] - cameraYaxis[Y] * cameraZaxis[X];

		// Xiw
		float xDotC =
			cameraXaxis[X] * render->camera.position[X] +
			cameraXaxis[Y] * render->camera.position[Y] +
			cameraXaxis[Z] * render->camera.position[Z];
		float yDotC =
			cameraYaxis[X] * render->camera.position[X] +
			cameraYaxis[Y] * render->camera.position[Y] +
			cameraYaxis[Z] * render->camera.position[Z];
		float zDotC =
			cameraZaxis[X] * render->camera.position[X] +
			cameraZaxis[Y] * render->camera.position[Y] +
			cameraZaxis[Z] * render->camera.position[Z];
		render->camera.Xiw[0][0] = cameraXaxis[X];
		render->camera.Xiw[0][1] = cameraXaxis[Y];
		render->camera.Xiw[0][2] = cameraXaxis[Z];
		render->camera.Xiw[0][3] = -xDotC;
		render->camera.Xiw[1][0] = cameraYaxis[X];
		render->camera.Xiw[1][1] = cameraYaxis[Y];
		render->camera.Xiw[1][2] = cameraYaxis[Z];
		render->camera.Xiw[1][3] = -yDotC;
		render->camera.Xiw[2][0] = cameraZaxis[X];
		render->camera.Xiw[2][1] = cameraZaxis[Y];
		render->camera.Xiw[2][2] = cameraZaxis[Z];
		render->camera.Xiw[2][3] = -zDotC;
		render->camera.Xiw[3][0] = 0;
		render->camera.Xiw[3][1] = 0;
		render->camera.Xiw[3][2] = 0;
		render->camera.Xiw[3][3] = 1;

		// init Ximage - put Xsp at base of stack, push on Xpi and Xiw
		// now stack contains Xsw and app can push model Xforms when needed 
		GzPushMatrix(render, render->Xsp);
		GzPushMatrix(render, render->camera.Xpi);
		GzPushMatrix(render, render->camera.Xiw);
	}
	return status;
}

int GzPutCamera(GzRender *render, GzCamera *camera)
{
/*
- overwrite renderer camera structure with new camera definition
*/
	if (render == NULL)
	{
		return GZ_FAILURE;
	}
	render->camera.position[X] = camera->position[X];
	render->camera.position[Y] = camera->position[Y];
	render->camera.position[Z] = camera->position[Z];
	render->camera.lookat[X] = camera->lookat[X];
	render->camera.lookat[Y] = camera->lookat[Y];
	render->camera.lookat[Z] = camera->lookat[Z];
	render->camera.worldup[X] = camera->worldup[X];
	render->camera.worldup[Y] = camera->worldup[Y];
	render->camera.worldup[Z] = camera->worldup[Z];
	render->camera.FOV = camera->FOV;
	float dInv = tan((camera->FOV / 2) * (PI / 180));
	render->camera.Xpi[2][2] = dInv;
	render->camera.Xpi[3][2] = dInv;
	return GZ_SUCCESS;
}

int GzPushMatrix(GzRender *render, GzMatrix	matrix)
{
/*
- push a matrix onto the Ximage stack
- check for stack overflow
*/
	// check arguments
	if (render == NULL || matrix == NULL)
	{
		return GZ_FAILURE;
	}
	// check for stack overflow
	if (render->matlevel == MATLEVELS)
	{
		return GZ_FAILURE;
	}
	// If the stack is empty, push matrix
	if (render->matlevel == -1)
	{
		render->matlevel++;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				render->Ximage[render->matlevel][i][j] = matrix[i][j];
			}
		}
	}
	// otherwise push top matrix * matrix
	else
	{
		// calculate matrix multiplication
		GzMatrix newMatrix;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				newMatrix[i][j] = 0;
				for (int k = 0; k < 4; ++k)
				{
					newMatrix[i][j] += render->Ximage[render->matlevel][i][k] * matrix[k][j];
				}
			}
		}
		// push new matrix
		render->matlevel++;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				render->Ximage[render->matlevel][i][j] = newMatrix[i][j];
			}
		}
	}

	// push new matrix for Xnorm
	if (render->matlevel == 0 || render->matlevel == 1)
	{
		// Push Identity
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				render->Xnorm[render->matlevel][i][j] = i == j ? 1 : 0;
			}
		}
	}
	else
	{
		// Push Xnorm
		GzMatrix normalMatrix;
		calculateNormalMatrix(matrix, &normalMatrix);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				render->Xnorm[render->matlevel][i][j] = 0;
				for (int k = 0; k < 4; ++k)
				{
					render->Xnorm[render->matlevel][i][j] += render->Xnorm[render->matlevel - 1][i][k] * normalMatrix[k][j];
				}
			}
		}
	}

	return GZ_SUCCESS;
}

int GzPopMatrix(GzRender *render)
{
/*
- pop a matrix off the Ximage stack
- check for stack underflow
*/
	// check arguments
	if (render == NULL)
	{
		return GZ_FAILURE;
	}
	// check for stack underflow
	if (render->matlevel < 0)
	{
		return GZ_FAILURE;
	}
	// pop a matrix off the Ximage stack (just decrease top pointer)
	render->matlevel--;
	return GZ_SUCCESS;
}


int GzPutAttribute(GzRender	*render, int numAttributes, GzToken	*nameList, 
	GzPointer	*valueList) /* void** valuelist */
{
/*
- set renderer attribute states (e.g.: GZ_RGB_COLOR default color)
- later set shaders, interpolaters, texture maps, and lights
*/
	if (render != NULL)
	{
		for (int i = 0; i < numAttributes; ++i)
		{
			GzColor *color, *acolor, *dcolor, *scolor;
			GzLight *alight, *dlight;
			switch (nameList[i])
			{
				case GZ_RGB_COLOR:
					// LATER: Do I have to increment through tokens (ints) and use (sizeof) token type
					// to increment the ponter through the value list
					color = (GzColor *)valueList[i];
					// clamp color values
					(*color)[RED] = fmaxf(0, fminf(4095, (*color)[RED]));
					(*color)[GREEN] = fmaxf(0, fminf(4095, (*color)[GREEN]));
					(*color)[BLUE] = fmaxf(0, fminf(4095, (*color)[BLUE]));
					render->flatcolor[RED] = (*color)[RED];
					render->flatcolor[GREEN] = (*color)[GREEN];
					render->flatcolor[BLUE] = (*color)[BLUE];
					break;
				case GZ_AMBIENT_COEFFICIENT:
					acolor = (GzColor *)valueList[i];
					// clamp color values
					(*acolor)[RED] = fmaxf(0, fminf(4095, (*acolor)[RED]));
					(*acolor)[GREEN] = fmaxf(0, fminf(4095, (*acolor)[GREEN]));
					(*acolor)[BLUE] = fmaxf(0, fminf(4095, (*acolor)[BLUE]));
					render->Ka[RED] = (*acolor)[RED];
					render->Ka[GREEN] = (*acolor)[GREEN];
					render->Ka[BLUE] = (*acolor)[BLUE];
					break;
				case GZ_DIFFUSE_COEFFICIENT:
					dcolor = (GzColor *)valueList[i];
					// clamp color values
					(*dcolor)[RED] = fmaxf(0, fminf(4095, (*dcolor)[RED]));
					(*dcolor)[GREEN] = fmaxf(0, fminf(4095, (*dcolor)[GREEN]));
					(*dcolor)[BLUE] = fmaxf(0, fminf(4095, (*dcolor)[BLUE]));
					render->Kd[RED] = (*dcolor)[RED];
					render->Kd[GREEN] = (*dcolor)[GREEN];
					render->Kd[BLUE] = (*dcolor)[BLUE];
					break;
				case GZ_SPECULAR_COEFFICIENT:
					scolor = (GzColor *)valueList[i];
					// clamp color values
					(*scolor)[RED] = fmaxf(0, fminf(4095, (*scolor)[RED]));
					(*scolor)[GREEN] = fmaxf(0, fminf(4095, (*scolor)[GREEN]));
					(*scolor)[BLUE] = fmaxf(0, fminf(4095, (*scolor)[BLUE]));
					render->Ks[RED] = (*scolor)[RED];
					render->Ks[GREEN] = (*scolor)[GREEN];
					render->Ks[BLUE] = (*scolor)[BLUE];
					break;
				case GZ_AMBIENT_LIGHT:
					alight = (GzLight *)valueList[i];
					// clamp color values
					render->ambientlight.color[RED] = fmaxf(0, fminf(4095, alight->color[RED]));
					render->ambientlight.color[GREEN] = fmaxf(0, fminf(4095, alight->color[GREEN]));;
					render->ambientlight.color[BLUE] = fmaxf(0, fminf(4095, alight->color[BLUE]));
					break;
				case GZ_DIRECTIONAL_LIGHT:
					if (render->numlights >= MAX_LIGHTS)
					{
						return GZ_FAILURE;
					}
					dlight = (GzLight *)valueList[i];
					// clamp color values
					render->lights[render->numlights].color[RED] = fmaxf(0, fminf(4095, dlight->color[RED]));
					render->lights[render->numlights].color[GREEN] = fmaxf(0, fminf(4095, dlight->color[GREEN]));
					render->lights[render->numlights].color[BLUE] = fmaxf(0, fminf(4095, dlight->color[BLUE]));

					render->lights[render->numlights].direction[X] = dlight->direction[X];
					render->lights[render->numlights].direction[Y] = dlight->direction[Y];
					render->lights[render->numlights].direction[Z] = dlight->direction[Z];
					render->numlights++;
					break;
				case GZ_DISTRIBUTION_COEFFICIENT:
					render->spec = *((float *)valueList[i]);
					break;
				case GZ_INTERPOLATE:
					render->interp_mode = *((int *)valueList[i]);
					break;
				case GZ_TEXTURE_MAP:
					render->tex_fun = (GzTexture)valueList[i];
				// later set texture maps
			}
		}
		return GZ_SUCCESS;
	}
	return GZ_FAILURE;
}

int GzPutTriangle(GzRender	*render, int numParts, GzToken *nameList, GzPointer	*valueList)
/* numParts : how many names and values */
{
/*  
- pass in a triangle description with tokens and values corresponding to 
      GZ_POSITION:3 vert positions in model space 
- Xform positions of verts using matrix on top of stack 
- Clip - just discard any triangle with any vert(s) behind view plane 
       - optional: test for triangles with all three verts off-screen (trivial frustum cull)
- invoke triangle rasterizer  
*/ 
	// Edge Classifiers
	const int UNDEFINED_EDGE = -1;
	const int TOP_EDGE = 0;
	const int BOTTOM_EDGE = 1;
	const int LEFT_EDGE = 2;
	const int RIGHT_EDGE = 3;

	if (render != NULL)
	{
		const int VERTICES_PER_TRIANGLE = 3;
		GzCoord triangleVertices[VERTICES_PER_TRIANGLE];
		GzCoord triangleNormals[VERTICES_PER_TRIANGLE];
		GzTextureIndex triangleTextureIndices[VERTICES_PER_TRIANGLE];
		int * indices;
		GzCoord Vertices[VERTICES_PER_TRIANGLE], Normals[VERTICES_PER_TRIANGLE];
		GzTextureIndex TextureIndices[VERTICES_PER_TRIANGLE];
		for (int i = 0; i < numParts; ++i)
		{
			if (nameList[i] == GZ_POSITION)
			{
				// Load all coordinates from provided input
				float yValues[VERTICES_PER_TRIANGLE];
				float points[VERTICES_PER_TRIANGLE][4];
				for (int t = 0; t < VERTICES_PER_TRIANGLE; ++t)
				{
					points[t][X] = ((GzCoord *)(valueList[i]))[t][X];
					points[t][Y] = ((GzCoord *)(valueList[i]))[t][Y];
					points[t][Z] = ((GzCoord *)(valueList[i]))[t][Z];
					points[t][3] = 1;
				}

				// Xform positions of verts using matrix on top of stack
				for (int t = 0; t < VERTICES_PER_TRIANGLE; ++t)
				{
					float xResult =
						render->Ximage[render->matlevel][0][0] * points[t][X] +
						render->Ximage[render->matlevel][0][1] * points[t][Y] +
						render->Ximage[render->matlevel][0][2] * points[t][Z] +
						render->Ximage[render->matlevel][0][3] * points[t][3];
					float yResult =
						render->Ximage[render->matlevel][1][0] * points[t][X] +
						render->Ximage[render->matlevel][1][1] * points[t][Y] +
						render->Ximage[render->matlevel][1][2] * points[t][Z] +
						render->Ximage[render->matlevel][1][3] * points[t][3];
					float zResult =
						render->Ximage[render->matlevel][2][0] * points[t][X] +
						render->Ximage[render->matlevel][2][1] * points[t][Y] +
						render->Ximage[render->matlevel][2][2] * points[t][Z] +
						render->Ximage[render->matlevel][2][3] * points[t][3];
					float wResult =
						render->Ximage[render->matlevel][3][0] * points[t][X] +
						render->Ximage[render->matlevel][3][1] * points[t][Y] +
						render->Ximage[render->matlevel][3][2] * points[t][Z] +
						render->Ximage[render->matlevel][3][3] * points[t][3];
					triangleVertices[t][X] = xResult / wResult;
					triangleVertices[t][Y] = yResult / wResult;
					triangleVertices[t][Z] = zResult / wResult;
					yValues[t] = triangleVertices[t][Y];

				}


				// Clip - just discard any triangle with any vert(s) behind view plane
				// TODO: optional test for triangles with all three verts off-screen (trivial frustum cull)
				for (int t = 0; t < VERTICES_PER_TRIANGLE; ++t)
				{
					if (triangleVertices[t][Z] < 0)
					{
						return GZ_FAILURE;
					}
				}

				// invoke triangle rasterizer (HW2)

				// Get indices of vertices corresponding to increasing Y
				sortTriangleVertices(yValues, &indices);
				int i0 = indices[0];
				int i1 = indices[1];
				int i2 = indices[2];

				// Get vertices in increasing Y
				memcpy(Vertices[0], triangleVertices[i0], sizeof(float) * 3);
				memcpy(Vertices[1], triangleVertices[i1], sizeof(float) * 3);
				memcpy(Vertices[2], triangleVertices[i2], sizeof(float) * 3);

			}
			else if (nameList[i] == GZ_NORMAL)
			{
				// Load all vectors from provided input
				float vectors[VERTICES_PER_TRIANGLE][4];
				for (int t = 0; t < VERTICES_PER_TRIANGLE; ++t)
				{
					vectors[t][X] = ((GzCoord *)(valueList[i]))[t][X];
					vectors[t][Y] = ((GzCoord *)(valueList[i]))[t][Y];
					vectors[t][Z] = ((GzCoord *)(valueList[i]))[t][Z];
					vectors[t][3] = 0;
				}

				for (int t = 0; t < VERTICES_PER_TRIANGLE; ++t)
				{
					float xResult =
						render->Xnorm[render->matlevel][0][0] * vectors[t][X] +
						render->Xnorm[render->matlevel][0][1] * vectors[t][Y] +
						render->Xnorm[render->matlevel][0][2] * vectors[t][Z];
					float yResult =
						render->Xnorm[render->matlevel][1][0] * vectors[t][X] +
						render->Xnorm[render->matlevel][1][1] * vectors[t][Y] +
						render->Xnorm[render->matlevel][1][2] * vectors[t][Z];
					float zResult =
						render->Xnorm[render->matlevel][2][0] * vectors[t][X] +
						render->Xnorm[render->matlevel][2][1] * vectors[t][Y] +
						render->Xnorm[render->matlevel][2][2] * vectors[t][Z];
					
					float length = sqrt(xResult*xResult + yResult*yResult + zResult*zResult);

					triangleNormals[t][X] = xResult / length;
					triangleNormals[t][Y] = yResult / length;
					triangleNormals[t][Z] = zResult / length;
				}

				// Get indices of vertices corresponding to increasing Y
				int i0 = indices[0];
				int i1 = indices[1];
				int i2 = indices[2];

				// Get normals in increasing vertex-Y
				memcpy(Normals[0], triangleNormals[i0], sizeof(GzCoord));
				memcpy(Normals[1], triangleNormals[i1], sizeof(GzCoord));
				memcpy(Normals[2], triangleNormals[i2], sizeof(GzCoord));
			}
			else if (nameList[i] == GZ_TEXTURE_INDEX)
			{
				// Load all texture indices from provided input
				for (int t = 0; t < VERTICES_PER_TRIANGLE; ++t)
				{
					triangleTextureIndices[t][U] = ((GzTextureIndex *)(valueList[i]))[t][X];
					triangleTextureIndices[t][V] = ((GzTextureIndex *)(valueList[i]))[t][Y];

					// Warping
					triangleTextureIndices[t][U] /= ((triangleVertices[t][Z] / (MAXINT - triangleVertices[t][Z])) + 1);
					triangleTextureIndices[t][V] /= ((triangleVertices[t][Z] / (MAXINT - triangleVertices[t][Z])) + 1);
				}

				// Get indices of texture indices corresponding to increasing Y
				int i0 = indices[0];
				int i1 = indices[1];
				int i2 = indices[2];

				// Get texture indices in increasing vertex-Y
				memcpy(TextureIndices[0], triangleTextureIndices[i0], sizeof(GzTextureIndex));
				memcpy(TextureIndices[1], triangleTextureIndices[i1], sizeof(GzTextureIndex));
				memcpy(TextureIndices[2], triangleTextureIndices[i2], sizeof(GzTextureIndex));
			}
		}

		// Do actual rendering of triangle //

		// Consistently arrange vertices and generate edges
		// also making sure to note what type of edge it is
		// note: E_i starts with V_i at its tail
		int edgeTypes[] = { UNDEFINED_EDGE, UNDEFINED_EDGE, UNDEFINED_EDGE };

		// Check for Horizontal edges first
		if (Vertices[0][Y] == Vertices[1][Y] && Vertices[1][Y] == Vertices[2][Y])
		{
			// All points have same Y value (horizontal lines)
			// TODO: what???
			// Assuming we won't have to deal with this for now?
			return GZ_SUCCESS;
		}
		else if (Vertices[0][Y] == Vertices[1][Y])
		{
			// Top Edge
			if (Vertices[0][X] < Vertices[1][X])
			{
				// Leave alone
			}
			else if (Vertices[0][X] > Vertices[1][X])
			{
				// Swap V0 and V1
				GzCoord temp;
				memcpy(temp, Vertices[0], sizeof(GzCoord));
				memcpy(Vertices[0], Vertices[1], sizeof(GzCoord));
				memcpy(Vertices[1], temp, sizeof(GzCoord));

				// Swap N0 and N1
				memcpy(temp, Normals[0], sizeof(GzCoord));
				memcpy(Normals[0], Normals[1], sizeof(GzCoord));
				memcpy(Normals[1], temp, sizeof(GzCoord));

				// Swap T0 and T1
				memcpy(temp, TextureIndices[0], sizeof(GzTextureIndex));
				memcpy(TextureIndices[0], TextureIndices[1], sizeof(GzTextureIndex));
				memcpy(TextureIndices[1], temp, sizeof(GzTextureIndex));
			}
			else
			{
				// Top edge is a line in the z-axis (triangle appears as vertical line)
				// TODO: what???
				// Assuming we won't have to deal with this for now?
				return GZ_SUCCESS;
			}
			// E0 is a top edge
			// E1 is a right edge
			// E2 is a left edge
			edgeTypes[0] = TOP_EDGE;
			edgeTypes[1] = RIGHT_EDGE;
			edgeTypes[2] = LEFT_EDGE;
		}
		else if (Vertices[1][Y] == Vertices[2][Y])
		{
			// Bottom Edge
			if (Vertices[1][X] < Vertices[2][X])
			{
				// Swap V1 and V2
				GzCoord temp;
				memcpy(temp, Vertices[1], sizeof(GzCoord));
				memcpy(Vertices[1], Vertices[2], sizeof(GzCoord));
				memcpy(Vertices[2], temp, sizeof(GzCoord));

				// Swap N1 and N2
				memcpy(temp, Normals[1], sizeof(GzCoord));
				memcpy(Normals[1], Normals[2], sizeof(GzCoord));
				memcpy(Normals[2], temp, sizeof(GzCoord));

				// Swap T1 and T2
				memcpy(temp, TextureIndices[1], sizeof(GzTextureIndex));
				memcpy(TextureIndices[1], TextureIndices[2], sizeof(GzTextureIndex));
				memcpy(TextureIndices[2], temp, sizeof(GzTextureIndex));
			}
			else if (Vertices[1][X] > Vertices[2][X])
			{
				// Leave alone
			}
			else
			{
				// Bottom edge is a line in the z-axis (triangle appears as vertical line)
				// TODO: what???
				// Assuming we won't have to deal with this for now?
				return GZ_SUCCESS;
			}
			// E0 is a right edge
			// E1 is a bottom edge
			// E2 is a left edge
			edgeTypes[0] = RIGHT_EDGE;
			edgeTypes[1] = BOTTOM_EDGE;
			edgeTypes[2] = LEFT_EDGE;
		}
		else
		{
			// Non-Horizontal Edges
			float dY = Vertices[2][Y] - Vertices[0][Y];
			float dX = Vertices[2][X] - Vertices[0][X];
			float oppositeEdgeX = Vertices[0][X] + (dX / dY) * (Vertices[1][Y] - Vertices[0][Y]);
			if (oppositeEdgeX < Vertices[1][X])
			{
				// V1 is R-edge
				// Don't need to do anything (leave order of vertices)
				// E1 is a right edge
				edgeTypes[1] = RIGHT_EDGE;
			}
			else if (oppositeEdgeX > Vertices[1][X])
			{
				// V1 is L-edge
				// Want to switch V1 and V2
				GzCoord temp;
				memcpy(temp, Vertices[1], sizeof(GzCoord));
				memcpy(Vertices[1], Vertices[2], sizeof(GzCoord));
				memcpy(Vertices[2], temp, sizeof(GzCoord));

				// Want to switch N1 and N2
				memcpy(temp, Normals[1], sizeof(GzCoord));
				memcpy(Normals[1], Normals[2], sizeof(GzCoord));
				memcpy(Normals[2], temp, sizeof(GzCoord));

				// Want to switch T1 and T2
				memcpy(temp, TextureIndices[1], sizeof(GzTextureIndex));
				memcpy(TextureIndices[1], TextureIndices[2], sizeof(GzTextureIndex));
				memcpy(TextureIndices[2], temp, sizeof(GzTextureIndex));

				// E1 is a left edge
				edgeTypes[1] = LEFT_EDGE;
			}
			else
			{
				// Weird case where all edges have same slope (triangle appears as line)
				// TODO: what???
				// Assuming we won't have to deal with this for now?
				return GZ_SUCCESS;
			}
			// E0 is a right edge
			// E1 is either a L/R edge (see above)
			// E2 is a left edge
			edgeTypes[0] = RIGHT_EDGE;
			edgeTypes[2] = LEFT_EDGE;
		}

		// Compute projection for vertices, compute the E_i
		float A[3], B[3], C[3];
		for (int j = 0; j < 3; ++j)
		{
			float dX = Vertices[(j + 1) % 3][X] - Vertices[j][X];
			float dY = Vertices[(j + 1) % 3][Y] - Vertices[j][Y];
			A[j] = dY;
			B[j] = -dX;
			C[j] = dX * Vertices[j][Y] - dY * Vertices[j][X];
		}

		// Compute bbox
		int xmin, xmax, ymin, ymax;
		xmin = floor(fminf(fminf(triangleVertices[0][X], triangleVertices[1][X]), triangleVertices[2][X]));
		xmax = ceil(fmaxf(fmaxf(triangleVertices[0][X], triangleVertices[1][X]), triangleVertices[2][X]));
		ymin = floor(fminf(fminf(triangleVertices[0][Y], triangleVertices[1][Y]), triangleVertices[2][Y]));
		ymax = ceil(fmaxf(fmaxf(triangleVertices[0][Y], triangleVertices[1][Y]), triangleVertices[2][Y]));

		// Clip bbox to screen limits
		int xres, yres;
		xres = render->display->xres;
		yres = render->display->yres;
		xmin = max(0, min(xres - 1, xmin));
		xmax = max(0, min(xres - 1, xmax));
		ymin = max(0, min(yres - 1, ymin));
		ymax = max(0, min(yres - 1, ymax));

		// Find plane equation for triangle
		float NA, NB, NC, ND;
		float zValues[3] = { Vertices[0][Z], Vertices[1][Z], Vertices[2][Z] };
		getTriangleInterpolator(Vertices, zValues, &NA, &NB, &NC, &ND);

		// Get linear interpolation for texture coordinates (indices)
		float uValues[3] = { TextureIndices[0][U], TextureIndices[1][U], TextureIndices[2][U] };
		float vValues[3] = { TextureIndices[0][V], TextureIndices[1][V], TextureIndices[2][V] };
		float uA, uB, uC, uD;
		float vA, vB, vC, vD;
		getTriangleInterpolator(Vertices, uValues, &uA, &uB, &uC, &uD);
		getTriangleInterpolator(Vertices, vValues, &vA, &vB, &vC, &vD);

		// Calculate Flat Surface color
		GzColor flatColor;
		if (render->interp_mode == GZ_FLAT)
		{
			GzCoord faceNormal = { NA, NB, NC };
			normalize(&faceNormal);
			getColor(render, &faceNormal, &flatColor);
		}

		// Find color for each vertex
		float redA, redB, redC, redD;
		float greenA, greenB, greenC, greenD;
		float blueA, blueB, blueC, blueD;
		if (render->interp_mode == GZ_COLOR && render->tex_fun == (GzPointer)0)
		{
			// Make sure we aren't trying to do texture

			// Get color at each vertex
			GzColor triangleVertexColors[VERTICES_PER_TRIANGLE];
			for (int i = 0; i < VERTICES_PER_TRIANGLE; ++i)
			{
				getColor(render, &(Normals[i]), &triangleVertexColors[i]);
			}
			float redValues[3] = { triangleVertexColors[0][RED], triangleVertexColors[1][RED], triangleVertexColors[2][RED] };
			float greenValues[3] = { triangleVertexColors[0][GREEN], triangleVertexColors[1][GREEN], triangleVertexColors[2][GREEN] };
			float blueValues[3] = { triangleVertexColors[0][BLUE], triangleVertexColors[1][BLUE], triangleVertexColors[2][BLUE] };

			// Get linear interpolator for vertex colors
			getTriangleInterpolator(Vertices, redValues, &redA, &redB, &redC, &redD);
			getTriangleInterpolator(Vertices, greenValues, &greenA, &greenB, &greenC, &greenD);
			getTriangleInterpolator(Vertices, blueValues, &blueA, &blueB, &blueC, &blueD);
		}

		// For all pixels in bbox
		for (int i = xmin; i < xmax; ++i)
		{
			for (int j = ymin; j < ymax; ++j)
			{
				// Evaluate edge functions a_i * x + b_i * y + c_i
				float E0 = A[0] * i + B[0] * j + C[0];
				float E1 = A[1] * i + B[1] * j + C[1];
				float E2 = A[2] * i + B[2] * j + C[2];
				int s0 = sign(E0);
				int s1 = sign(E1);
				int s2 = sign(E2);

				if (s0 == 0)
				{
					if (!(edgeTypes[0] == LEFT_EDGE || edgeTypes[0] == TOP_EDGE))
					{
						// On edge 0 but edge 0 is neither a left or top edge
						continue;
					}
				}
				if (s1 == 0)
				{
					if (!(edgeTypes[1] == LEFT_EDGE || edgeTypes[1] == TOP_EDGE))
					{
						// On edge 1 but edge 1 is neither a left or top edge
						continue;
					}
				}
				if (s2 == 0)
				{
					if (!(edgeTypes[2] == LEFT_EDGE || edgeTypes[2] == TOP_EDGE))
					{
						// On edge 2 but edge 2 is neither a left or top edge
						continue;
					}
				}

				if (!((s0 == s1) && (s1 == s2) && (s0 == s2)))
				{
					// Outside the triangle
					continue;
				}

				// Fill in pixel
				GzColor pixelColor;
				GzIntensity r, g, b, a;
				GzDepth z;
				GzGetDisplay(render->display, i, j, &r, &g, &b, &a, &z);
				
				// Interpolate z-depth
				float interpZ = interpolate(NA, NB, NC, ND, i, j);
				if (interpZ < z || z == 0)
				{
					// closer - update pixel
					if (render->interp_mode == GZ_FLAT)
					{
						// just use surface flat color
						pixelColor[RED] = flatColor[RED];
						pixelColor[GREEN] = flatColor[GREEN];
						pixelColor[BLUE] = flatColor[BLUE];
					}
					else if (render->interp_mode == GZ_COLOR)
					{
						// If texture enabled
						if (render->tex_fun != (GzPointer)0)
						{
							// Get TextureColor from interpolated U,V
							float interpU = interpolate(uA, uB, uC, uD, i, j);
							float interpV = interpolate(vA, vB, vC, vD, i, j);
							
							// Unwarping
							interpU *= ((interpZ / (MAXINT - interpZ)) + 1);
							interpV *= ((interpZ / (MAXINT - interpZ)) + 1);
							
							// Get Texture Color
							GzColor textureColor;
							render->tex_fun(interpU, interpV, textureColor);
							
							// Apply texture color to Ka, Kd, and Ks
							render->Ka[RED] = textureColor[RED];
							render->Ka[GREEN] = textureColor[GREEN];
							render->Ka[BLUE] = textureColor[BLUE];
							render->Kd[RED] = textureColor[RED];
							render->Kd[GREEN] = textureColor[GREEN];
							render->Kd[BLUE] = textureColor[BLUE];
							render->Ks[RED] = textureColor[RED];
							render->Ks[GREEN] = textureColor[GREEN];
							render->Ks[BLUE] = textureColor[BLUE];

							// Get color at each vertex
							GzColor triangleVertexColors[VERTICES_PER_TRIANGLE];
							for (int i = 0; i < VERTICES_PER_TRIANGLE; ++i)
							{
								getColor(render, &(Normals[i]), &triangleVertexColors[i]);
							}
							float redValues[3] = { triangleVertexColors[0][RED], triangleVertexColors[1][RED], triangleVertexColors[2][RED] };
							float greenValues[3] = { triangleVertexColors[0][GREEN], triangleVertexColors[1][GREEN], triangleVertexColors[2][GREEN] };
							float blueValues[3] = { triangleVertexColors[0][BLUE], triangleVertexColors[1][BLUE], triangleVertexColors[2][BLUE] };

							// Get linear interpolator for vertex colors
							getTriangleInterpolator(Vertices, redValues, &redA, &redB, &redC, &redD);
							getTriangleInterpolator(Vertices, greenValues, &greenA, &greenB, &greenC, &greenD);
							getTriangleInterpolator(Vertices, blueValues, &blueA, &blueB, &blueC, &blueD);
						}

						// interpolate color based on vertex colors
						pixelColor[RED] = interpolate(redA, redB, redC, redD, i, j);
						pixelColor[GREEN] = interpolate(greenA, greenB, greenC, greenD, i, j);
						pixelColor[BLUE] = interpolate(blueA, blueB, blueC, blueD, i, j);
					}

					else if (render->interp_mode == GZ_NORMALS)
					{
						// interpolate normal and calculate color
						float xA, xB, xC, xD;
						float yA, yB, yC, yD;
						float zA, zB, zC, zD;
						
						// vertex normals to use for interpolator
						float xNormals[3] = { Normals[0][X], Normals[1][X], Normals[2][X] };
						float yNormals[3] = { Normals[0][Y], Normals[1][Y], Normals[2][Y] };
						float zNormals[3] = { Normals[0][Z], Normals[1][Z], Normals[2][Z] };
						
						// get linear interpolator for normals
						getTriangleInterpolator(Vertices, xNormals, &xA, &xB, &xC, &xD);
						getTriangleInterpolator(Vertices, yNormals, &yA, &yB, &yC, &yD);
						getTriangleInterpolator(Vertices, zNormals, &zA, &zB, &zC, &zD);
						
						// get interpolated normal
						GzCoord pixelNormal;
						pixelNormal[X] = interpolate(xA, xB, xC, xD, i, j);
						pixelNormal[Y] = interpolate(yA, yB, yC, yD, i, j);
						pixelNormal[Z] = interpolate(zA, zB, zC, zD, i, j);
						normalize(&pixelNormal);

						// If texture enabled
						if (render->tex_fun != (GzPointer)0)
						{
							// Get TextureColor from interpolated U,V
							float interpU = interpolate(uA, uB, uC, uD, i, j);
							float interpV = interpolate(vA, vB, vC, vD, i, j);
							
							// Unwarping
							interpU *= ((interpZ / (MAXINT - interpZ)) + 1);
							interpV *= ((interpZ / (MAXINT - interpZ)) + 1);

							// Get Texture Color
							GzColor textureColor;
							render->tex_fun(interpU, interpV, textureColor);
							
							// Apply texture color to Ka and Kd
							render->Ka[RED] = textureColor[RED];
							render->Ka[GREEN] = textureColor[GREEN];
							render->Ka[BLUE] = textureColor[BLUE];
							render->Kd[RED] = textureColor[RED];
							render->Kd[GREEN] = textureColor[GREEN];
							render->Kd[BLUE] = textureColor[BLUE];
						}

						// get pixel color
						getColor(render, &pixelNormal, &pixelColor);
					}

					// Clamp pixel color [0, 1]
					pixelColor[RED] = fmaxf(0, fminf(1, pixelColor[RED]));
					pixelColor[GREEN] = fmaxf(0, fminf(1, pixelColor[GREEN]));
					pixelColor[BLUE] = fmaxf(0, fminf(1, pixelColor[BLUE]));

					GzPutDisplay(render->display, i, j, ctoi(pixelColor[RED]), ctoi(pixelColor[GREEN]), ctoi(pixelColor[BLUE]), a, interpZ);
				}
			}
		}

		return GZ_SUCCESS;
	}
	return GZ_FAILURE;
}

/* NOT part of API - just for general assistance */

void sortTriangleVertices(float * values, int ** sortedIndices)
{
	// Default order
	*sortedIndices = (int *)malloc(sizeof(int) * 3);
	(*sortedIndices)[0] = 0;
	(*sortedIndices)[1] = 1;
	(*sortedIndices)[2] = 2;

	float v0 = values[0];
	float v1 = values[1];
	float v2 = values[2];

	int tempIndex;
	float tempFloat;

	if (v0 > v1)
	{
		tempIndex = (*sortedIndices)[0];
		(*sortedIndices)[0] = (*sortedIndices)[1];
		(*sortedIndices)[1] = tempIndex;
		tempFloat = v0;
		v0 = v1;
		v1 = tempFloat;
	}
	if (v1 > v2)
	{
		tempIndex = (*sortedIndices)[1];
		(*sortedIndices)[1] = (*sortedIndices)[2];
		(*sortedIndices)[2] = tempIndex;
		tempFloat = v1;
		v1 = v2;
		v2 = tempFloat;
	}
	if (v0 > v1)
	{
		tempIndex = (*sortedIndices)[0];
		(*sortedIndices)[0] = (*sortedIndices)[1];
		(*sortedIndices)[1] = tempIndex;
		tempFloat = v0;
		v0 = v1;
		v1 = tempFloat;
	}
}

int sign(float value)
{
	if (value == 0)
	{
		return 0;
	}
	return fabsf(value) / value;
}

void getTriangleInterpolator(GzCoord * triangleVertices, float * values, float * A, float * B, float * C, float * D)
{
	float X1 = triangleVertices[1][X] - triangleVertices[0][X];
	float Y1 = triangleVertices[1][Y] - triangleVertices[0][Y];
	float V1 = values[1] - values[0];

	float X2 = triangleVertices[2][X] - triangleVertices[0][X];
	float Y2 = triangleVertices[2][Y] - triangleVertices[0][Y];
	float V2 = values[2] - values[0];

	*C = X1*Y2 - Y1*X2;

	*A = Y1*V2 - V1*Y2;
	*B = V1*X2 - X1*V2;

	float x = triangleVertices[0][X];
	float y = triangleVertices[0][Y];
	float v = values[0];
	*D = -1 * ((*A)*x + (*B)*y + (*C)*v);
}

float interpolate(float A, float B, float C, float D, float x, float y)
{
	return -1 * (A*x + B*y + D) / C;
}

void calculateNormalMatrix(GzMatrix matrix, GzMatrix * normalMatrix)
{
	float a = matrix[0][0];
	float b = matrix[0][1];
	float c = matrix[0][2];
	float d = matrix[1][0];
	float e = matrix[1][1];
	float f = matrix[1][2];
	float g = matrix[2][0];
	float h = matrix[2][1];
	float i = matrix[2][2];
	
	float determinant = a*e*i + b*f*g + c*d*h - c*e*g - b*d*i - a*f*h;
	float invDet = 1.0f / determinant;
	
	for (int row = 0; row < 4; ++row)
	{
		for (int col = 0; col < 4; ++col)
		{
			if (row == 3 && col == 3)
			{
				(*normalMatrix)[row][col] = 1;
			}
			else if (row == 3 || col == 3)
			{
				(*normalMatrix)[row][col] = 0;
			}
			else
			{
				(*normalMatrix)[row][col] = invDet * (
					matrix[(row + 1) % 3][(col + 1) % 3] * matrix[(row + 2) % 3][(col + 2) % 3] -
					matrix[(row + 2) % 3][(col + 1) % 3] * matrix[(row + 1) % 3][(col + 2) % 3]
				);
			}
		}
	}
	
}

void getColor(GzRender * render, GzCoord * N, GzColor * color)
{
	// Color coefficients
	GzColor Ka, Kd, Ks;
	GzColor Is, Id, Ia;
	Ka[RED] = render->Ka[RED];
	Ka[GREEN] = render->Ka[GREEN];
	Ka[BLUE] = render->Ka[BLUE];
	Kd[RED] = render->Kd[RED];
	Kd[GREEN] = render->Kd[GREEN];
	Kd[BLUE] = render->Kd[BLUE];
	Ks[RED] = render->Ks[RED];
	Ks[GREEN] = render->Ks[GREEN];
	Ks[BLUE] = render->Ks[BLUE];
	float spec = render->spec;

	// Lights
	GzLight * directionalLights = render->lights;
	GzLight ambientLight = render->ambientlight;
	Ia[RED] = ambientLight.color[RED];
	Ia[GREEN] = ambientLight.color[GREEN];
	Ia[BLUE] = ambientLight.color[BLUE];
	Is[RED] = 0;
	Is[GREEN] = 0;
	Is[BLUE] = 0;
	Id[RED] = 0;
	Id[GREEN] = 0;
	Id[BLUE] = 0;

	// Eye vector (constant in camera space);
	GzCoord E = { 0, 0, -1 };

	// Iterate through all the lights
	for (int i = 0; i < render->numlights; ++i)
	{
		// Get L
		GzCoord L;
		for (int j = 0; j < 3; ++j)
		{
			L[j] = render->lights[i].direction[j];
		}
		normalize(&L);

		// test cases
		float NdotL = dotProduct(N, &L);
		float NdotE = dotProduct(N, &E);
		if (NdotE < 0 && NdotL < 0)
		{
			// Flip the normal
			scaleVector(N, -1);
			NdotL = dotProduct(N, &L);
		}
		else if (sign(NdotE) != sign(NdotL))
		{
			// Skip
			continue;
		}

		// Calculate R (in image space)
		// R = -L + 2 * ( N * (N . L)  )
		GzCoord R;
		scalarProduct(N, 2*NdotL, &R);
		vectorSubtract(&R, &L, &R);
		normalize(&R);
		
		// Clamp R.E in [0,1]
		float RdotE = fmaxf(0, fminf(1, dotProduct(&R, &E)));

		// Get Ie
		GzColor Ie;
		Ie[RED] = render->lights[i].color[RED];
		Ie[GREEN] = render->lights[i].color[GREEN];
		Ie[BLUE] = render->lights[i].color[BLUE];

		// Specular color
		GzColor specComponent;
		scalarProduct(&Ie, powf((RdotE), render->spec), &specComponent);
		vectorIncrease(&Is, &specComponent);
		
		// Diffuse color
		GzColor diffuseComponent;
		scalarProduct(&Ie, (dotProduct(N, &L)), &diffuseComponent);
		vectorIncrease(&Id, &diffuseComponent);
	}

	// C = (Ks * sum[over all lights] {Ie * (R . E)^spec} ) +(Kd sum[over all lights] {Ie (N . L)}) + (Ka * Ia)
	GzColor specularColor, diffuseColor, ambientColor;
	GzColor materialColor;
	colorMultiply(&Ks, &Is, &specularColor);
	colorMultiply(&Kd, &Id, &diffuseColor);
	colorMultiply(&Ka, &Ia, &ambientColor);
	vectorAdd(&specularColor, &diffuseColor, &materialColor);
	vectorAdd(&materialColor, &ambientColor, color);

	(*color)[RED] = fmaxf(0, fminf(1, (*color)[RED]));
	(*color)[GREEN] = fmaxf(0, fminf(1, (*color)[GREEN]));
	(*color)[BLUE] = fmaxf(0, fminf(1, (*color)[BLUE]));
}

void vectorAdd(GzCoord * u, GzCoord * v, GzCoord * out)
{
	(*out)[X] = (*v)[X] + (*u)[X];
	(*out)[Y] = (*v)[Y] + (*u)[Y];
	(*out)[Z] = (*v)[Z] + (*u)[Z];
}

void vectorIncrease(GzCoord * u, GzCoord * v)
{
	(*u)[X] += (*v)[X];
	(*u)[Y] += (*v)[Y];
	(*u)[Z] += (*v)[Z];
}

void vectorSubtract(GzCoord * u, GzCoord * v, GzCoord * out)
{
	(*out)[X] = (*u)[X] - (*v)[X];
	(*out)[Y] = (*u)[Y] - (*v)[Y];
	(*out)[Z] = (*u)[Z] - (*v)[Z];
}

void scaleVector(GzCoord * v, float scalar)
{
	(*v)[X] *= scalar;
	(*v)[Y] *= scalar;
	(*v)[Z] *= scalar;
}

void scalarProduct(GzCoord * v, float scalar, GzCoord * out)
{
	(*out)[X] = (*v)[X] * scalar;
	(*out)[Y] = (*v)[Y] * scalar;
	(*out)[Z] = (*v)[Z] * scalar;
}

void normalize(GzCoord * v)
{
	float length = sqrt((*v)[X] * (*v)[X] + (*v)[Y] * (*v)[Y] + (*v)[Z] * (*v)[Z]);
	scaleVector(v, 1.0f / length);
}

float dotProduct(GzCoord * u, GzCoord * v)
{
	return (*u)[X] * (*v)[X] + (*u)[Y] * (*v)[Y] + (*u)[Z] * (*v)[Z];
}

void colorMultiply(GzColor * u, GzColor * v, GzColor * out)
{
	(*out)[RED] = (*u)[RED] * (*v)[RED];
	(*out)[GREEN] = (*u)[GREEN] * (*v)[GREEN];
	(*out)[BLUE] = (*u)[BLUE] * (*v)[BLUE];
}

short	ctoi(float color)		/* convert float color to GzIntensity short */
{
  return(short)((int)(color * ((1 << 12) - 1)));
}

