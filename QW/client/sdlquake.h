/*
Copyright (C) 1996-1997 Id Software, Inc.

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
// sdlquake.h: SDL3-specific Quake header file

#include <SDL3/SDL.h>

// Compatibility typedefs for Win32 types → SDL3 equivalents
// Note: on Win32 builds, HWND, HDC, HINSTANCE, HMODULE, HANDLE, BOOL, PROC,
// and DWORD are already defined by <windows.h>. We provide these only for
// non-Win32 platforms. SDL_Window* is used directly for SDL window handles.
#ifndef _WIN32
typedef int HINSTANCE;
typedef int HMODULE;
typedef void* HANDLE;
typedef int BOOL;
#define TRUE 1
#define FALSE 0
typedef SDL_FunctionPointer PROC;
typedef unsigned long DWORD;
typedef void* HDC;
#endif

// RECT compatibility structure (matches Win32 RECT layout)
#ifndef _WIN32
typedef struct RECT_tag {
	int left;
	int top;
	int right;
	int bottom;
} RECT;

// POINT compatibility structure (matches Win32 POINT layout)
typedef struct POINT_tag {
	int x;
	int y;
} POINT;
#endif

#ifndef SERVERONLY
#include <SDL3/SDL_video.h>
#endif

extern	HINSTANCE	global_hInstance;
extern	int			global_nCmdShow;

#ifndef SERVERONLY

// DirectDraw compatibility (stubs for non-GL builds)
typedef void* LPDIRECTDRAW;
typedef void* LPDIRECTDRAWSURFACE;
typedef void* LPDIRECTDRAWPALETTE;
typedef void* LPDIRECTSOUND;
typedef void* LPDIRECTSOUNDBUFFER;

extern LPDIRECTDRAW		lpDD;
extern qboolean			DDActive;
extern LPDIRECTDRAWSURFACE	lpPrimary;
extern LPDIRECTDRAWSURFACE	lpFrontBuffer;
extern LPDIRECTDRAWSURFACE	lpBackBuffer;
extern LPDIRECTDRAWPALETTE	lpDDPal;
extern LPDIRECTSOUND pDS;
extern LPDIRECTSOUNDBUFFER pDSBuf;

extern DWORD gSndBufSize;
//#define SNDBUFSIZE 65536

void	VID_LockBuffer (void);
void	VID_UnlockBuffer (void);

#endif

typedef enum {MS_WINDOWED, MS_FULLSCREEN, MS_FULLDIB, MS_UNINIT} modestate_t;

extern modestate_t	modestate;

extern SDL_Window		*mainwindow;
extern qboolean		ActiveApp, Minimized;

extern qboolean	WinNT;

int VID_ForceUnlockedAndReturnState (void);
void VID_ForceLockState (int lk);

void IN_ShowMouse (void);
void IN_DeactivateMouse (void);
void IN_HideMouse (void);
void IN_ActivateMouse (void);
void IN_RestoreOriginalMouseState (void);
void IN_SetQuakeMouseState (void);
void IN_MouseEvent (int mstate);

extern qboolean	winsock_lib_initialized;

extern int		window_center_x, window_center_y;
extern RECT		window_rect;

extern qboolean	mouseinitialized;
extern SDL_Window	*hwnd_dialog;

extern HANDLE	hinput, houtput;

void IN_UpdateClipCursor (void);
void CenterWindow(SDL_Window *hWndCenter, int width, int height, BOOL lefttopjustify);

void S_BlockSound (void);
void S_UnblockSound (void);

void VID_SetDefaultMode (void);

// Winsock function pointers (kept for compatibility; may be stubbed on non-Win32)
#ifdef _WIN32
int (PASCAL FAR *pWSAStartup)(WORD wVersionRequired, LPWSADATA lpWSAData);
int (PASCAL FAR *pWSACleanup)(void);
int (PASCAL FAR *pWSAGetLastError)(void);
SOCKET (PASCAL FAR *psocket)(int af, int type, int protocol);
int (PASCAL FAR *pioctlsocket)(SOCKET s, long cmd, u_long FAR *argp);
int (PASCAL FAR *psetsockopt)(SOCKET s, int level, int optname,
							  const char FAR * optval, int optlen);
int (PASCAL FAR *precvfrom)(SOCKET s, char FAR * buf, int len, int flags,
							struct sockaddr FAR *from, int FAR * fromlen);
int (PASCAL FAR *psendto)(SOCKET s, const char FAR * buf, int len, int flags,
						  const struct sockaddr FAR *to, int tolen);
int (PASCAL FAR *pclosesocket)(SOCKET s);
int (PASCAL FAR *pgethostname)(char FAR * name, int namelen);
struct hostent FAR * (PASCAL FAR *pgethostbyname)(const char FAR * name);
struct hostent FAR * (PASCAL FAR *pgethostbyaddr)(const char FAR * addr,
												  int len, int type);
int (PASCAL FAR *pgetsockname)(SOCKET s, struct sockaddr FAR *name,
							   int FAR * namelen);
#else
// Non-Win32: stub declarations for socket function pointers
extern int (*pWSAStartup)(void*, void*);
extern int (*pWSACleanup)(void);
extern int (*pWSAGetLastError)(void);
extern void* (*psocket)(int, int, int);
extern int (*pioctlsocket)(void*, long, void*);
extern int (*psetsockopt)(void*, int, int, const char*, int);
extern int (*precvfrom)(void*, char*, int, int, void*, int*);
extern int (*psendto)(void*, const char*, int, int, const void*, int);
extern int (*pclosesocket)(void*);
extern int (*pgethostname)(char*, int);
extern void* (*pgethostbyname)(const char*);
extern void* (*pgethostbyaddr)(const char*, int, int);
extern int (*pgetsockname)(void*, void*, int*);
#endif
