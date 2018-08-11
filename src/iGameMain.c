/*
  iGameMain.c
  Main c  for iGame
  
  Copyright (c) 2016, Emmanuel Vasilakis
  
  This file is part of iGame.

  iGame is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  iGame is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with iGame. If not, see <http://www.gnu.org/licenses/>.
*/

/* Main-Header File inserted by GenCodeC */
/* Libraries */
#include <libraries/mui.h>
#include <libraries/gadtools.h> /* for BARLABEL in MenuItem */

/* Prototypes */
#ifdef __GNUC__
#include <proto/exec.h>
#include <proto/dos.h>
#else
#include <clib/muimaster_protos.h>
#include <clib/exec_protos.h>
#include <clib/alib_protos.h>
#include <clib/dos_protos.h>
#include <pragmas/muimaster_pragmas.h>
#endif /* __GNUC__ */

/*  Ansi  */
#include <stdlib.h>
#include <stdio.h>

/* Increase stack size */
LONG __stack = 32000;
/* GenCodeC header end */

/* Include generated by GenCodeC */
#include "iGameGUI.h"

/* Declarations for libraries (inserted by GenCodeC) */
struct Library* IntuitionBase;
struct Library* MUIMasterBase;

struct ObjApp* App = NULL; /* Object */

extern void AppStart();
extern void AppStop();
extern void ReadToolTypes();
extern struct ObjApp* CreateApp(void);
extern void DisposeApp(struct ObjApp*);

/* Init() function */
void init(void)
{
	if (!(IntuitionBase = OpenLibrary("intuition.library", 37)))
	{
		printf("Can't Open Intuition Library\n");
		exit(20);
	}
	if (!(MUIMasterBase = OpenLibrary(MUIMASTER_NAME, MUIMASTER_VMIN)))
	{
		printf("Can't Open MUIMaster Library\n");
		CloseLibrary(IntuitionBase);
		exit(20);
	}
}

/* GenCodeC init() end */

/* End() function */
void end(void)
{
	CloseLibrary(MUIMasterBase);
	CloseLibrary(IntuitionBase);
	exit(20);
}

/* GenCodeC end() end */

/* Main Function inserted by GenCodeC */
int main(int argc, char** argv)
{
	BOOL running = TRUE;
	ULONG signal;

	/* Program initialisation : generated by GenCodeC */
	init();

	//read tooltypes here?
	ReadToolTypes();

	/* Create Object : generated by GenCodeC */
	if (!(App = CreateApp()))
	{
		printf(
			"Can't Create App. Make sure all the required MUI mcc's are present, please check the included guide.\n");
		end();
	}

	AppStart();

	while (running)
	{
		switch (DoMethod(App->App, MUIM_Application_Input, &signal))
		{
		case MUIV_Application_ReturnID_Quit:
			running = FALSE;
			break;
		default:
			break;
		}
		if (running && signal) Wait(signal);
	}

	AppStop();
	DisposeApp(App);
	//end();    
	exit(EXIT_SUCCESS);
}
