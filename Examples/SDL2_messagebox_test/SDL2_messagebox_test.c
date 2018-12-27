/*
  Copyright (C) 1997-2018 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/

/* Simple test of the SDL MessageBox API */

/* Compile:
 * $ gcc `sdl2-config --cflags --libs` SDL2_messagebox_test.c
 * $ ./a.out
 */

#include <stdio.h>
#include <stdlib.h>

#include "SDL.h"

/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
static void
quit(int rc)
{
	SDL_Quit();
	exit(rc);
}

static int SDLCALL
button_messagebox(void *eventNumber)
{
	const SDL_MessageBoxButtonData buttons[] = {
	    {
	        SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT,
	        0,
	        "OK"
	    },{
	        SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT,
	        1,
	        "Cancel"
	    },
	};

	SDL_MessageBoxData data = {
	    SDL_MESSAGEBOX_INFORMATION,
	    NULL, /* no parent window */
	    "Custom MessageBox",
	    "This is a custom messagebox",
	    2,
	    NULL,/* buttons */
	    NULL /* Default color scheme */
	};

	int button = -1;
	int success = 0;
	data.buttons = buttons;
	if (eventNumber) {
		data.message = "This is a custom messagebox from a background thread.";
	}

	success = SDL_ShowMessageBox(&data, &button);
	if (success == -1) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error Presenting MessageBox: %s\n", SDL_GetError());
		if (eventNumber) {
			SDL_UserEvent event;
			event.type = (intptr_t)eventNumber;
			SDL_PushEvent((SDL_Event*)&event);
			return 1;
		} else {
			quit(2);
		}
	}
	SDL_Log("Pressed button: %d, %s\n", button, button == -1 ? "[closed]" : button == 1 ? "Cancel" : "OK");

	if (eventNumber) {
		SDL_UserEvent event;
		event.type = (intptr_t)eventNumber;
		SDL_PushEvent((SDL_Event*)&event);
	}

	return 0;
}

int
main(int argc, char *argv[])
{
	int success;

	/* Enable standard application logging */
	SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

	success = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING,
	                                   "Simple MessageBox",
	                                   "12 символов.",
	                                   NULL);
	if (success == -1) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error Presenting MessageBox: %s\n", SDL_GetError());
		// fprintf(stderr, "%s\n", SDL_GetError());
		quit(1);
	}

	success = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
	                                   "Simple MessageBox",
	                                   "This is a simple MessageBox with a newline:\r\nHello world!\nFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFочень_длинная_строкаFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",
	                                   NULL);
	if (success == -1) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error Presenting MessageBox: %s\n", SDL_GetError());
		quit(1);
	}

	/* Google says this is Traditional Chinese for "beef with broccoli" */
	success = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
	                                   "UTF-8 Simple MessageBox",
	                                   "'牛肉西蘭花'\n'牛肉西蘭花'\n'牛肉西蘭花'\n'牛肉西蘭花'",
	                                   NULL);
	if (success == -1) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error Presenting MessageBox: %s\n", SDL_GetError());
		quit(1);
	}

	/* Google says this is Traditional Chinese for "beef with broccoli" */
	success = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
	                                   "UTF-8 Simple MessageBox",
	                                   "Unicode text and newline:\r\n'牛肉西蘭花'\n'牛肉西蘭花'",
	                                   NULL);
	if (success == -1) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error Presenting MessageBox: %s\n", SDL_GetError());
		quit(1);
	}

	/* Google says this is Traditional Chinese for "beef with broccoli" */
	success = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
	                                   "Проверочка :3",
	                                   "Unicode text in the title.",
	                                   NULL);
	if (success == -1) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error Presenting MessageBox: %s\n", SDL_GetError());
		quit(1);
	}

	button_messagebox(NULL);

	/* Test showing a message box from a background thread.

	   On Mac OS X, the video subsystem needs to be initialized for this
	   to work, since the message box events are dispatched by the Cocoa
	   subsystem on the main thread.
	 */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL video subsystem: %s\n", SDL_GetError());
		return (1);
	}
	{
		int status = 0;
		SDL_Event event;
		intptr_t eventNumber = SDL_RegisterEvents(1);
		SDL_Thread* thread = SDL_CreateThread(&button_messagebox, "MessageBox", (void*)eventNumber);

		while (SDL_WaitEvent(&event))
		{
			if (event.type == eventNumber) {
				break;
			}
		}

		SDL_WaitThread(thread, &status);

		SDL_Log("Message box thread return %i\n", status);
	}

	/* Test showing a message box with a parent window */
	{
		SDL_Event event;
		SDL_Window *window = SDL_CreateWindow("Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
		SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
		SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

		success = SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
		                                   "Simple MessageBox",
		                                   "This is a simple error MessageBox with a parent window",
		                                   window);
		if (success == -1) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Error Presenting MessageBox: %s\n", SDL_GetError());
			quit(1);
		}

		while (SDL_WaitEvent(&event))
		{
			if (event.type == SDL_QUIT || event.type == SDL_KEYUP) {
				break;
			}
			SDL_RenderClear(renderer);
			SDL_RenderPresent(renderer);
		}
		SDL_DestroyWindow(window);
	}


	const SDL_MessageBoxButtonData buttons[] = {
	    { /* .flags, .buttonid, .text */        0, 1, "no" },
	    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 2, "yes" },
	    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 0, "cancel" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
	    { /* .colors (.r, .g, .b) */
	      /* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
	      { 255,   255,   0 },
	      /* [SDL_MESSAGEBOX_COLOR_TEXT] */
	      {   255, 0,   0 },
	      /* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
	      { 0 , 255,   0 },
	      /* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
	      {   255,   0, 255 },
	      /* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
	      { 255,   0, 255 }
	    }
	};
	const SDL_MessageBoxData messageboxdata = {
	    SDL_MESSAGEBOX_INFORMATION, /* .flags */
	    NULL, /* .window */
	    "example message box", /* .title */
	    "select a button", /* .message */
	    SDL_arraysize(buttons), /* .numbuttons */
	    buttons, /* .buttons */
	    &colorScheme /* .colorScheme */
	};


	int buttonid;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
		return 1;
	}
	if (buttonid == -1) {
		SDL_Log("no selection");
	} else {
		for (int i = 0; i < 3; ++i) {
			if (buttons[i].buttonid == buttonid)
				SDL_Log("selection was %s", buttons[i].text);
		}
	}

	const SDL_MessageBoxButtonData buttons_many[] = {
	    { /* .flags, .buttonid, .text */        0, 0, "Button 0" },
	    { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "Defaul 1" },
	    { SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "Cancel 2" },
	    { 3, 2, "Button 3" },
	    { 4, 2, "Button 4" },
	    { 5, 2, "Button 5" },
	    { 6, 2, "Button 6" },
	    { 7, 2, "Button 7" },
	    { 8, 2, "Button 8" },
	    { 9, 2, "Button 9" },
	    { 10, 2, "Button 10" },
	};
	const SDL_MessageBoxData messageboxdata_many = {
	    SDL_MESSAGEBOX_INFORMATION, /* .flags */
	    NULL, /* .window */
	    "MessageBox with many Buttons", /* .title */
	    "Select a button :)", /* .message */
	    SDL_arraysize(buttons_many), /* .numbuttons */
	    buttons_many /* .buttons */
	};

	SDL_ShowMessageBox(&messageboxdata_many, &buttonid);
	fprintf(stderr, "Pushed ==> %d\n", buttonid);

	SDL_Quit();
	return (0);
}
