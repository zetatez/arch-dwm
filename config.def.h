/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
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

static const char *const autostart[] = {                               // dwm-cool-autostart
	"dwmstatus", "2>&1 >>/dev/null &", NULL,                           // dwm-cool-autostart
// 	"picom", NULL,                                                     // dwm-cool-autostart
	"dunst", NULL,                                                     // dwm-cool-autostart
    "warpd", NULL,                                                     // dwm-cool-autostart
    "sh", "-c", "pkill -9 trojan; cd ~/.trojan; ./trojan &; cd", NULL, // dwm-cool-autostart
// 	"st", NULL,                                                        // dwm-cool-autostart
	NULL /* terminate */                                               // dwm-cool-autostart
};                                                                     // dwm-cool-autostart

typedef struct {                                                                    // dwm-scratchpads
	const char *name;                                                               // dwm-scratchpads
	const void *cmd;                                                                // dwm-scratchpads
} Sp;                                                                               // dwm-scratchpads
const char *spcmd1[] = {"st", "-n", "spst", "-g", "154x44", NULL };                 // dwm-scratchpads
const char *spcmd2[] = {"st", "-n", "spra", "-g", "154x44", "-e", "ranger", NULL }; // dwm-scratchpads
const char *spcmd3[] = {"vivaldi-stable", NULL };                                   // dwm-scratchpads
static Sp scratchpads[] = {                                                         // dwm-scratchpads
	/* name          cmd  */                                                        // dwm-scratchpads
	{"spst",         spcmd1},                                                       // dwm-scratchpads
	{"spra",         spcmd2},                                                       // dwm-scratchpads
    {"vivaldi",      spcmd3},                                                       // dwm-scratchpads
};                                                                                  // dwm-scratchpads

/* tagging */
static const char *tags[] = { "ζ(s)=∑1/n^s", "-e^iπ=1", "i", "o", "∞", "∫", "∇", "i", "0" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
	{ NULL,		  "spst",     NULL,	      SPTAG(0),		1,			 -1 },
	{ NULL,		  "spra",     NULL,		  SPTAG(1),		1,			 -1 },
	{ NULL,		  "vivaldi",  NULL,		  SPTAG(2), 	0,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "layouts.c"                                                                  // layouts: dwm-fibonacci
static const Layout layouts[] = {
	/* symbol     arrange function */
    { "|f:x->y",          tile },    /* first entry is default */
    { "|g:y->x",      lefttile },                                                     // dwm-leftstack
    { "|M/R",          monocle },
    { "|A=>B",          spiral },                                                     // dwm-fibonacci
    { "|A<=B",         dwindle },                                                     // dwm-fibonacci
    { "|π",        gaplessgrid },                                                     // dwm-gaplessgrid
	{ "|Ξ",             bstack },                                                     // dwm-bottomstack
	{ "|Τ",        bstackhoriz },                                                     // dwm-bottomstack
	{ "|∫",               deck },                                                     // dwm-deck-double
    { "|∅",               NULL },    /* no layout function means floating behavior */
	{ NULL,               NULL },                                                     // dwm-cyclelayouts
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/zsh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.025} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.025} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // tile
    { MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[1]} }, // lefttile    dwm-lefttile
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} }, // monocle
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[3]} }, // sprial      dwm-fibonacci
	{ MODKEY|ShiftMask,             XK_r,      setlayout,      {.v = &layouts[4]} }, // dwindle     dwm-fibonacci
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[5]} }, // gaplessgrid dwm-gaplessgrid
	{ MODKEY,                       XK_e,      setlayout,      {.v = &layouts[6]} }, // bstack      dwm-bottomstack
	{ MODKEY|ShiftMask,             XK_e,      setlayout,      {.v = &layouts[7]} }, // bstackhoriz dwm-bottomstack
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[8]} }, // deck        dwm-deck-double
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[9]} }, // no layout function means floating behavior
	{ MODKEY|ControlMask,		    XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,           			XK_apostrophe, togglescratch,  {.ui = 0 } }, // dwm-scratchpads
	{ MODKEY,            			XK_u,	       togglescratch,  {.ui = 1 } }, // dwm-scratchpads
	{ MODKEY,            			XK_v,	       togglescratch,  {.ui = 2 } }, // dwm-scratchpads
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
//  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },                    // dwm-scratchpads
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },                    // dwm-scratchpads
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

