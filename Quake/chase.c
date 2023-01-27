/*
Copyright (C) 1996-2001 Id Software, Inc.
Copyright (C) 2002-2009 John Fitzgibbons and others
Copyright (C) 2010-2014 QuakeSpasm developers

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/
// chase.c -- chase camera code

#include "quakedef.h"

cvar_t	chase_back = {"chase_back", "100", CVAR_NONE};
cvar_t	chase_up = {"chase_up", "16", CVAR_NONE};
cvar_t	chase_right = {"chase_right", "0", CVAR_NONE};
cvar_t	chase_active = {"chase_active", "0", CVAR_NONE};
cvar_t	chase_smoothing = { "chase_smoothing", "2", CVAR_NONE };

/*
==============
Chase_Init
==============
*/
void Chase_Init (void)
{
	Cvar_RegisterVariable (&chase_back);
	Cvar_RegisterVariable (&chase_up);
	Cvar_RegisterVariable (&chase_right);
	Cvar_RegisterVariable (&chase_active);
	Cvar_RegisterVariable(&chase_smoothing);
}

/*
==============
TraceLine

TODO: impact on bmodels, monsters
==============
*/
void TraceLine (vec3_t start, vec3_t end, vec3_t impact)
{
	trace_t	trace;

	memset (&trace, 0, sizeof(trace));
	SV_RecursiveHullCheck (cl.worldmodel->hulls, start, end, &trace, CONTENTMASK_ANYSOLID);

	VectorCopy (trace.endpos, impact);
}

/*
==============
TraceLine

TODO: impact on bmodels, monsters
==============
*/
void TraceData(vec3_t start, vec3_t end, vec3_t impact)
{
	trace_t	trace;

	memset(&trace, 0, sizeof(trace));
	SV_RecursiveHullCheck(cl.worldmodel->hulls, start, end, &trace, CONTENTMASK_ANYSOLID);

	VectorCopy(trace.endpos, impact);
}

/*
==============
Chase_UpdateForClient -- johnfitz -- orient client based on camera. called after input
==============
*/
void Chase_UpdateForClient (void)
{
	//place camera

	//assign client angles to camera

	//see where camera points

	//adjust client angles to point at the same place
}

/*
==============
Chase_UpdateForDrawing -- johnfitz -- orient camera based on client. called before drawing

TODO: stay at least 8 units away from all walls in this leaf
==============
*/
void Chase_UpdateForDrawing(void)
{
	int		i;
	vec3_t	forward, up, right;
	vec3_t	ideal, crosshair, temp;
	vec3_t	offset;

	AngleVectors(r_refdef.viewangles, forward, right, up);

	// calc ideal camera location before checking for walls
	for (i = 0; i < 3; i++)
		ideal[i] = cl.viewent.origin[i]
		- forward[i] * (chase_back.value)
		+ right[i] * chase_right.value;
	//+ up[i]*chase_up.value;
	ideal[2] = cl.viewent.origin[2] + chase_up.value;

	// make sure camera is not in or behind a wall
	//TraceLine(r_refdef.vieworg, ideal, temp);
	TraceLine(cl.viewent.origin, ideal, temp);

	if (VectorLength(temp) != 0)
		VectorCopy(temp, ideal);

	for (i = 0; i < 2; i++)
	{
		ideal[i] += forward[i] * 32;
		//ideal[1] += forward[1] * 32;
	}
	ideal[2] -= up[2] * 16;

	// place camera
	VectorCopy(ideal, r_refdef.vieworg);

	offset[0] = -forward[0] * 32;
	offset[1] = -forward[1] * 32;
	offset[2] = -up[2] * 0;

	temp[0] -= forward[0] * 32;
	temp[1] -= forward[1] * 32;
	temp[2] += forward[2] * 32;

	// find the spot the player is looking at
	VectorMA(cl.viewent.origin, 4096, forward, temp);
	TraceLine(cl.viewent.origin, temp, crosshair);

	//r_refdef.viewangles[YAW] = 0;

	// calculate camera angles to look at the same spot
	//VectorSubtract (crosshair, r_refdef.vieworg, temp);
//	VectorAngles (temp, NULL, r_refdef.viewangles);
	if (r_refdef.viewangles[PITCH] == 90 || r_refdef.viewangles[PITCH] == -90)
	{
		r_refdef.viewangles[YAW] = cl.viewangles[YAW];
	}
}

/*
==============
Chase_UpdateForDrawing -- johnfitz -- orient camera based on client. called before drawing

TODO: stay at least 8 units away from all walls in this leaf
==============
*/
void Chase_UpdateForDrawing2(void)
{
	int		i;
	vec3_t	forward, up, right;
	vec3_t	ideal, crosshair, temp;


	AngleVectors(r_refdef.viewangles, forward, right, up);

	// calc ideal camera location before checking for walls
	for (i = 0; i < 3; i++)
		ideal[i] = cl.viewent.origin[i]
		- forward[i] * (chase_back.value)
		+ right[i] * chase_right.value;
	//+ up[i]*chase_up.value;
	ideal[2] = cl.viewent.origin[2] + chase_up.value;

	// make sure camera is not in or behind a wall
	TraceLine(r_refdef.vieworg, ideal, temp);
	if (VectorLength(temp) != 0)
		VectorCopy(temp, ideal);

	// place camera
	VectorCopy(ideal, r_refdef.vieworg);

	// find the spot the player is looking at
	VectorMA(cl.viewent.origin, 4096, forward, temp);
	TraceLine(cl.viewent.origin, temp, crosshair);

	// calculate camera angles to look at the same spot
	VectorSubtract(crosshair, r_refdef.vieworg, temp);
	VectorAngles(temp, NULL, r_refdef.viewangles);
	if (r_refdef.viewangles[PITCH] == 90 || r_refdef.viewangles[PITCH] == -90)
	{
		r_refdef.viewangles[YAW] = cl.viewangles[YAW];
	}
}