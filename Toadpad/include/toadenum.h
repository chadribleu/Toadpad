#pragma once

#include <Windows.h>

namespace toadenum
{
	namespace style
	{
		enum Window : unsigned long
		{
			USEDEFAULT = 0UL,
			OVERLAPPED = WS_OVERLAPPED,
			OVERLAPPEDWINDOW = WS_OVERLAPPEDWINDOW,
			CHILD = WS_CHILD,
			DISABLED = WS_DISABLED,
			HSCROLL = WS_HSCROLL,
			VSCROLL = WS_VSCROLL,
			VISIBLE = WS_VISIBLE,
			BORDER = WS_BORDER,
			CAPTION = WS_CAPTION,
			CLIPCHILDREN = WS_CLIPCHILDREN,
			CLIPSIBLINGS = WS_CLIPSIBLINGS,
			DLGFRAME = WS_DLGFRAME,
			GROUP = WS_GROUP,
			MINIMIZE = WS_ICONIC,
			MINIMIZEBUTTON = WS_MINIMIZEBOX,
			POPUP = WS_POPUP,
			POPUPMENU = WS_POPUPWINDOW,
			RESIZEABLE = WS_THICKFRAME,
			SYSMENU = WS_SYSMENU,
			TABFOCUS = WS_TABSTOP
		};

		enum WindowExStyle : unsigned long
		{
			DEFAULT = 0UL,
			DGFILES = WS_EX_ACCEPTFILES,
			CONTEXTHELP = WS_EX_CONTEXTHELP
		};
	}
	namespace KeyboardKeys
	{
		enum Modifiers : unsigned long
		{
			ALT = FALT,
			CTRL = FCONTROL,
			SHIFT = FSHIFT,
		};

		enum VirtualKey : unsigned long
		{
			LMOUSEBUTTON,
			RMOUSEBUTTON,
			MMOUSEBUTTON,
		};
	}
}
