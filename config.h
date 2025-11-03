/* See LICENSE file for copyright and license details. */

/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"
#define BROWSER "zen-browser"
#define DISCORD "vesktop"
#define THUNAR "thunar"

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 10;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 10;       /* vert inner gap between windows */
static const unsigned int gappoh    = 10;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 10;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int swterminheritfs    = 1;        /* 1 terminal inherits fullscreen on unswallow, 0 otherwise */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
/* static const char *fonts[]          = { "monospace:size=10" }; */
/* static const char dmenufont[]       = "monospace:size=10"; */
static const char *fonts[]          = { "CaskaydiaMonoNerdFont-Bold:size=10.6:antialias=true:autohint=true" };
static const char dmenufont[]       = "CaskaydiaMonoNerdFont-Bold:size=10.6:antialias=true:autohint=true";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title            tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",     NULL,       NULL,            0,         1,          0,           0,        -1 },
	{ "Firefox",  NULL,       NULL,            1 << 8,    0,          0,          -1,        -1 },
	{ "St",       NULL,       NULL,            0,         0,          1,           0,        -1 },
	{ NULL,       NULL,       "Event Tester",  0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "vanitygaps.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[@]",      spiral },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define STATUSBAR "dwmblocks"

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { TERMINAL, NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,			XK_Return,     spawn,      {.v = termcmd } },
	{ MODKEY,			XK_b,          togglebar,              {0} },
	{ MODKEY,			XK_Left,       focusmon,               {.i = -1 } },
	{ MODKEY|ShiftMask,		XK_Left,       tagmon,                 {.i = -1 } },
	{ MODKEY,			XK_Right,      focusmon,               {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_Right,      tagmon,                 {.i = +1 } },
	{ MODKEY,			XK_h,          setmfact,               {.f = -0.05} },
	{ MODKEY,			XK_l,          setmfact,               {.f = +0.05} },
	{ MODKEY,			XK_q,          killclient,             {0} },
	{ MODKEY|ShiftMask,		XK_q,          killclient,             {0} },
	{ MODKEY,			XK_o,          incnmaster,             {.i = +1 } },
	{ MODKEY|ShiftMask,		XK_o,          incnmaster,             {.i = -1 } },
	{ MODKEY,			XK_space,      zoom,                   {0} },
	{ MODKEY|ShiftMask,		XK_space,      togglefloating,         {0} },
	{ MODKEY,             		XK_f,	       togglefullscr,	       {0} },
	{ MODKEY|ShiftMask,             XK_f,	       togglefullscr,	       {0} },
	{ MODKEY, 			XK_j, 	       focusstack, 	       {.i = +1 } },
	{ MODKEY, 			XK_k, 	       focusstack, 	       {.i = -1 } },

	{ MODKEY|ShiftMask,		XK_b,          spawn,                  {.v = (const char*[]){ BROWSER, NULL } } },
	{ MODKEY|ShiftMask,		XK_v,          spawn,                  {.v = (const char*[]){ DISCORD, NULL } } },
	{ MODKEY,			XK_t,          spawn,                  {.v = (const char*[]){ THUNAR, NULL } } },
	{ MODKEY|ShiftMask,		XK_w,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "sudo", "nmtui", NULL } } },
	{ MODKEY,			XK_r,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "lfub", NULL } } },
	{ MODKEY,			XK_d,          spawn,                  {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY|ShiftMask,		XK_d,          spawn,                  {.v = (const char*[]){ "dmenu_run", NULL } } },
	{ MODKEY|ShiftMask,		XK_l,          spawn,                  SHCMD("slock & xset dpms force off; pauseallmpv") },
	{ MODKEY,			XK_m,          spawn,                  {.v = (const char*[]){ TERMINAL, "-e", "ncspot", NULL } } },
	{ MODKEY|ShiftMask,		XK_m,          spawn,                  SHCMD("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle; kill -44 $(pidof dwmblocks)") },
	{ MODKEY,			XK_F3,         spawn,                  {.v = (const char*[]){ "displayselect", NULL } } },
	{ MODKEY,			XK_F4,         spawn,                  SHCMD(TERMINAL " -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	/* { MODKEY,			XK_F5,         xrdb,                   {.v = NULL } },	 */
	{ MODKEY,			XK_F11,        spawn,                  SHCMD("mpv --untimed --no-cache --no-osc --no-input-default-bindings --profile=low-latency --input-conf=/dev/null --title=webcam $(ls /dev/video[0,2,4,6,8] | tail -n 1)") },
	{ MODKEY,			XK_Print,      spawn,                  SHCMD("maim -u ~/Pictures/$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY|ShiftMask,		XK_Print,      spawn,                  SHCMD("maim -s --noopengl -u ~/Pictures/$(date '+%y%m%d-%H%M-%S').png") },
	{ MODKEY,                       XK_BackSpace,  togglehalfscreen,       {0} },
	{ MODKEY|ShiftMask,             XK_BackSpace,  toggleside,	       {0} },
	{ MODKEY,			XK_z,          incrgaps,               {.i = +3 } },
	{ MODKEY,			XK_x,          incrgaps,               {.i = -3 } },
	{ MODKEY,			XK_a,          togglegaps,             {0} },
	{ MODKEY|ShiftMask,		XK_a,          defaultgaps,            {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY,			XK_0,	       view,                   {.ui = ~0 } },
	{ MODKEY|ShiftMask,		XK_0,	       tag,                    {.ui = ~0 } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },
	{ ClkWinTitle,          0,              Button2,        togglebar,      {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	/* placemouse options, choose which feels more natural:
	 *    0 - tiled position is relative to mouse cursor
	 *    1 - tiled postiion is relative to window center
	 *    2 - mouse pointer warps to window center
	 *
	 * The moveorplace uses movemouse or placemouse depending on the floating state
	 * of the selected client. Set up individual keybindings for the two if you want
	 * to control these separately (i.e. to retain the feature to move a tiled window
	 * into a floating position).
	 */
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

