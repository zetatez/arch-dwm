/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */  // dwm-swallow
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

typedef struct {                                                                        // dwm-scratchpads
	const char *name;                                                                   // dwm-scratchpads
	const void *cmd;                                                                    // dwm-scratchpads
} Sp;                                                                                   // dwm-scratchpads
const char *spcmd1[] = {"st", "-n", "spst", "-g", "120x20", NULL };                     // dwm-scratchpads
const char *spcmd2[] = {"st", "-n", "spfzfvim", "-g", "120x30", "-e", "fzfvim", NULL }; // dwm-scratchpads
const char *spcmd3[] = {"obsidian", NULL };                                             // dwm-scratchpads
const char *spcmd4[] = {"kitty", NULL };                                                // dwm-scratchpads
const char *spcmd5[] = {"vivaldi-stable", NULL };                                       // dwm-scratchpads
static Sp scratchpads[] = {                                                             // dwm-scratchpads
	/* name          cmd  */                                                            // dwm-scratchpads
	{"spst",         spcmd1},                                                           // dwm-scratchpads
	{"spvimfzf",     spcmd2},                                                           // dwm-scratchpads
	{"obsidian",     spcmd3},                                                           // dwm-scratchpads
	{"kitty",        spcmd4},                                                           // dwm-scratchpads
    {"vivaldi",      spcmd5},                                                           // dwm-scratchpads
};                                                                                      // dwm-scratchpads

/* tagging */
static const char *tags[] = { "ζ(s)=∑1/n^s", "-e^iπ=1", "i", "o", "∞", "∫", "∇", "i", "0" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	         instance    title    tags mask     isfloating   CenterThisWindow?    isterminal    noswallow    monitor */
	{ "st",                  NULL,       NULL,    0,            0,     	     1,		              1,             1,          -1 }, // dwm-centerfirstwindow // dwm-scratchpads // dwm-swallow
	{ "kitty",               NULL,       NULL,    0,            0,     	     0,		              0,             0,          -1 }, // dwm-centerfirstwindow // dwm-scratchpads // dwm-swallow
	{ "netease-cloud-music", NULL,       NULL,    0,            0,     	     1,		              0,             0,          -1 }, // dwm-centerfirstwindow // dwm-scratchpads // dwm-swallow
	{ "Gimp",                NULL,       NULL,    0,            1,           1,                   0,             0,          -1 }, // dwm-centerfirstwindow // dwm-scratchpads // dwm-swallow
	{ "Firefox",             NULL,       NULL,    1 << 8,       0,           0,                   0,            -1,          -1 }, // dwm-centerfirstwindow // dwm-scratchpads // dwm-swallow
	{ NULL,		             "spst",     NULL,	  SPTAG(0),		1,			 1,                   0,             0,          -1 }, // dwm-centerfirstwindow // dwm-scratchpads // dwm-swallow
	{ NULL,		             "spvimfzf", NULL,	  SPTAG(1),		0,			 0,                   0,             0,          -1 }, // dwm-centerfirstwindow // dwm-scratchpads // dwm-swallow
    { NULL,		             "obsidian", NULL,	  SPTAG(2),		1,			 0,                   0,             0,          -1 }, // dwm-centerfirstwindow // dwm-scratchpads // dwm-swallow
    { NULL,		             "kitty",    NULL,	  SPTAG(3),		0,			 1,                   0,             0,          -1 }, // dwm-centerfirstwindow // dwm-scratchpads // dwm-swallow
	{ NULL,		             "vivaldi",  NULL,	  SPTAG(4), 	1,			 0,                   0,             0,          -1 }, // dwm-centerfirstwindow // dwm-scratchpads // dwm-swallow
};

/* layout(s) */
static const float mfact            = 0.90; /* factor of master area size [0.05..0.95] */
static const int nmaster            = 2;    /* number of clients in master area */
// static const int resizehints     = 1;    /* 1 means respect size hints in tiled resizals */    // dwm-tatami
static const int resizehints        = 0;    /* 1 means respect size hints in tiled resizals */    // dwm-tatami
static const int lockfullscreen     = 1;    /* 1 will force focus on the fullscreen window */
static const int mcenterfirstwindow = 1;    /* factor of center first window size [0.20, 0.80] */ // dwm-centerfistwindow
static const float firstwindowszw   = 0.64; /* factor of center first window size width  [0.20, 0.80] */ // dwm-centerfistwindow
static const float firstwindowszh   = 0.48; /* factor of center first window size height [0.20, 0.80] */ // dwm-centerfistwindow
static const float cakefact         = 0.70; /* factor of focus above area size [0.05..0.95] */
static const float cakewindowszw    = 0.64; /* factor of cake center window size width  [0.20, 0.80] */ // dwm-cake my layout
static const float cakewindowszh    = 0.48; /* factor of cake center window size height [0.20, 0.80] */ // dwm-cake my layout

#include "layouts.c"                                                                    // layouts
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "cake",               cake }, // dwm-cake
	{ "f:x->y",           bstack }, // dwm-bottomstack
	{ "g:y->x",      bstackhoriz }, // dwm-bottomstack
    { "∫_E^r(t)du",     lefttile }, // dwm-leftstack
    { "∅",                  NULL }, /* no layout function means floating behavior */
    { "∫_E^r(t)du",      monocle },
    { "∫_E^r(t)du",         tile }, /* first entry is default */
	{ "∫_E^r(t)du",     tilewide }, // dwm-tilewide
    { "∫_E^r(t)du",       spiral }, // dwm-fibonacci
    { "∫_E^r(t)du",      dwindle }, // dwm-fibonacci
    { "∫_E^r(t)du",  gaplessgrid }, // dwm-gaplessgrid
	{ "∫_E^r(t)du",         deck }, // dwm-deck-double
	{ "∫_E^r(t)du",       tatami }, // dwm-tatami
	{ NULL,                NULL  }, // dwm-cyclelayouts
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
#include "shiftview.c"
static Key keys[] = {
	/* modifier                     key            function        argument */
	{ MODKEY,                       XK_p,          spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,     spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,          togglebar,      {0} },
	{ MODKEY,                       XK_j,          focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,          incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,          incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,          setmfact,       {.f = -0.025} },
	{ MODKEY|ShiftMask,             XK_l,          setmfact,       {.f = +0.025} },
	{ MODKEY|ShiftMask,             XK_j,          movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,          movestack,      {.i = -1 } },
	{ MODKEY,                       XK_Return,     zoom,           {0} },
	{ MODKEY,                       XK_Tab,        view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,     {0} },
	{ MODKEY,                       XK_n,          setlayout,      {.v = &layouts[0]} },  // cake
	{ MODKEY,                       XK_e,          setlayout,      {.v = &layouts[1]} },  // bstack      dwm-bottomstack
	{ MODKEY|ShiftMask,             XK_e,          setlayout,      {.v = &layouts[2]} },  // bstackhoriz dwm-bottomstack
    { MODKEY,                       XK_t,          setlayout,      {.v = &layouts[3]} },  // lefttile    dwm-lefttile
	{ MODKEY,                       XK_f,          setlayout,      {.v = &layouts[4]} },  // no layout function means floating behavior
	{ MODKEY,                       XK_m,          setlayout,      {.v = &layouts[5]} },  // monocle
	{ MODKEY|ShiftMask,             XK_t,          setlayout,      {.v = &layouts[6]} },  // tile
	{ MODKEY,                       XK_w,          setlayout,      {.v = &layouts[7]} },  // tilewide    dwm-tilewide
	{ MODKEY,                       XK_r,          setlayout,      {.v = &layouts[8]} },  // sprial      dwm-fibonacci
	{ MODKEY|ShiftMask,             XK_r,          setlayout,      {.v = &layouts[9]} },  // dwindle     dwm-fibonacci
    { MODKEY,                       XK_g,          setlayout,      {.v = &layouts[10]} }, // gaplessgrid dwm-gaplessgrid
	{ MODKEY,                       XK_y,          setlayout,      {.v = &layouts[11]} }, // deck        dwm-deck-double
	{ MODKEY,                       XK_o,          setlayout,      {.v = &layouts[12]} }, // tatami      dwm-tatami
	{ MODKEY|ControlMask,		    XK_comma,      cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,     cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,      setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_s,          togglesticky,   {0} },                // dwm-sticky
	{ MODKEY,                       XK_0,          view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,      focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,     focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,         {.i = +1 } },
    { MODKEY,                       XK_h,          shiftview,      {.i = -1 } }, // shiftview
    { MODKEY,                       XK_l,          shiftview,      {.i = +1 } }, // shiftview
	{ MODKEY,           			XK_apostrophe, togglescratch,  {.ui = 0 } }, // dwm-scratchpads
	{ MODKEY,            			XK_v,	       togglescratch,  {.ui = 1 } }, // dwm-scratchpads
	{ MODKEY,            			XK_q,	       togglescratch,  {.ui = 2 } }, // dwm-scratchpads
	{ MODKEY,            			XK_z,	       togglescratch,  {.ui = 3 } }, // dwm-scratchpads
	{ MODKEY,            			XK_u,	       togglescratch,  {.ui = 4 } }, // dwm-scratchpads
	TAGKEYS(                        XK_1,          0)
	TAGKEYS(                        XK_2,          1)
	TAGKEYS(                        XK_3,          2)
	TAGKEYS(                        XK_4,          3)
	TAGKEYS(                        XK_5,          4)
	TAGKEYS(                        XK_6,          5)
	TAGKEYS(                        XK_7,          6)
	TAGKEYS(                        XK_8,          7)
	TAGKEYS(                        XK_9,          8)
	{ MODKEY|ShiftMask,             XK_q,          quit,           {0} },
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
//  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} }, // dwm-scratchpads
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} }, // dwm-scratchpads
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTagBar,            0,              Button4,        shiftview,      { .i = -1 } }, // dwm-shiftview
    { ClkTagBar,            0,              Button5,        shiftview,      { .i = +1 } }, // dwm-shiftview
};

