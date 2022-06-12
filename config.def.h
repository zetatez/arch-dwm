/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */  // dwm-swallow
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int barheight          = 24;       /* bh = (barheight > drw->fonts->h ) && (barheight < 3 * drw->fonts->h ) ? barheight : drw->fonts->h + 2 */ // dwm-bar-height
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
    "/home/lorenzo/.dwm/autostart.sh", NULL,                           // dwm-cool-autostart
	NULL /* terminate */                                               // dwm-cool-autostart
};                                                                     // dwm-cool-autostart

/* tagging */
static const char *tags[] = { "ζ(s)=∑1/n^s", "-e^iπ=1", "i", "o", "∞", "∫", "∇", "i", "0" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      	         instance    title    tags mask     isfloating   centerfirstwindow?   isterminal     noswallow    monitor */
	{ "st",                  NULL,       NULL,    0,            0,     	     1,		              1,             1,          -1 }, // dwm-centerfirstwindow // dwm-swallow
	{ "netease-cloud-music", NULL,       NULL,    0,            0,     	     1,		              0,             0,          -1 }, // dwm-centerfirstwindow // dwm-swallow
	{ "Gimp",                NULL,       NULL,    0,            1,           0,                   0,             0,          -1 }, // dwm-centerfirstwindow // dwm-swallow
	{ "Firefox",             NULL,       NULL,    1 << 8,       0,           0,                   0,            -1,          -1 }, // dwm-centerfirstwindow // dwm-swallow
    { "kitty",	             NULL,       NULL,	  0,		    0,			 1,                   0,             0,          -1 }, // dwm-centerfirstwindow // dwm-swallow
    { "vimb",	             NULL,       NULL,	  0,		    0,			 0,                   0,             0,          -1 }, // dwm-centerfirstwindow // dwm-swallow
};

/* layout(s) */
static const float mfact            = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster            = 1;    /* number of clients in master area */
// static const int resizehints     = 1;    /* 1 means respect size hints in tiled resizals */    // dwm-tatami
static const int resizehints        = 0;    /* 1 means respect size hints in tiled resizals */    // dwm-tatami
static const int lockfullscreen     = 1;    /* 1 will force focus on the fullscreen window */
static const int mcenterfirstwindow = 1;    /* factor of center first window size [0.20, 0.80] */ // dwm-centerfistwindow
static const float firstwindowszw   = 0.64; /* factor of center first window size width  [0.20, 0.80] */ // dwm-centerfistwindow
static const float firstwindowszh   = 0.48; /* factor of center first window size height [0.20, 0.80] */ // dwm-centerfistwindow
static const float cakewindowszw    = 0.64; /* factor of cake center window size width  [0.20, 0.80] */  // dwm-cake my layout
static const float cakewindowszh    = 0.48; /* factor of cake center window size height [0.20, 0.80] */  // dwm-cake my layout
static const float centerwindowszw  = 0.64; /* factor of center window size width  [0.20, 0.80] */       // dwm-center my layout
static const float centerwindowszh  = 0.48; /* factor of center window size height [0.20, 0.80] */       // dwm-center my layout

#include "layouts.c"                                                                    // layouts
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "Center",                        center }, // dwm-center
	{ "Cake Vertical",           cakevertical }, // dwm-cake
	{ "Cake Horizontal",       cakehorizontal }, // dwm-cake
	{ "Cake Full Bottom",      cakefullbottom }, // dwm-cake
	{ "Stack Vertical",        bstackvertical }, // dwm-bottomstack
	{ "Stack Horizontal",    bstackhorizontal }, // dwm-bottomstack
    { "Tile Left",                   tileleft }, // dwm-leftstack
    { "∅",                               NULL }, /* no layout function means floating behavior */
    { "Monocle",                      monocle },
    { "Tile Right",                      tile }, /* first entry is default */
	{ "Tile Wide",                   tilewide }, // dwm-tilewide
    { "Fibonacci",                     spiral }, // dwm-fibonacci
    { "Fibonacci",                    dwindle }, // dwm-fibonacci
    { "Grid",                     gaplessgrid }, // dwm-gaplessgrid
	{ "Deck",                            deck }, // dwm-deck-double
	{ "Tatami",                        tatami }, // dwm-tatami
	{ "Logarithmic Spiral", logarithmicspiral }, // dwm-logarithmicspiral
	{ NULL,                             NULL  }, // dwm-cyclelayouts
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
	/* modifier                     key            function           argument */
	{ MODKEY,                       XK_p,          spawn,             {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_Return,     spawn,             {.v = termcmd } },
	{ MODKEY,                       XK_b,          togglebar,         {0} },
	{ MODKEY,                       XK_j,          focusstack,        {.i = +1 } },
	{ MODKEY,                       XK_k,          focusstack,        {.i = -1 } },
	{ MODKEY,                       XK_i,          incnmaster,        {.i = +1 } },
	{ MODKEY,                       XK_d,          incnmaster,        {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,          setmfact,          {.f = -0.025} },
	{ MODKEY|ShiftMask,             XK_l,          setmfact,          {.f = +0.025} },
	{ MODKEY|ShiftMask,             XK_j,          movestack,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,          movestack,         {.i = -1 } },
	{ MODKEY,                       XK_Return,     zoom,              {0} },
	{ MODKEY,                       XK_Tab,        view,              {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,        {0} },
	{ MODKEY|ShiftMask,             XK_m,          setlayout,         {.v = &layouts[0]} },  // center
	{ MODKEY,                       XK_w,          setlayout,         {.v = &layouts[1]} },  // cakevertical
	{ MODKEY|ShiftMask,             XK_w,          setlayout,         {.v = &layouts[2]} },  // cakehorizontal
	{ MODKEY|ControlMask,           XK_w,          setlayout,         {.v = &layouts[3]} },  // cakefullbottom
	{ MODKEY,                       XK_e,          setlayout,         {.v = &layouts[4]} },  // bstack      dwm-bottomstack
	{ MODKEY|ShiftMask,             XK_e,          setlayout,         {.v = &layouts[5]} },  // bstackhoriz dwm-bottomstack
    { MODKEY,                       XK_t,          setlayout,         {.v = &layouts[6]} },  // lefttile    dwm-lefttile
	{ MODKEY|ShiftMask,             XK_f,          setlayout,         {.v = &layouts[7]} },  // no layout means floating
	{ MODKEY,                       XK_m,          setlayout,         {.v = &layouts[8]} },  // monocle
	{ MODKEY|ShiftMask,             XK_t,          setlayout,         {.v = &layouts[9]} },  // tile
	{ MODKEY,                       XK_y,          setlayout,         {.v = &layouts[10]} }, // tilewide    dwm-tilewide
	{ MODKEY,                       XK_r,          setlayout,         {.v = &layouts[11]} }, // sprial      dwm-fibonacci
	{ MODKEY|ShiftMask,             XK_r,          setlayout,         {.v = &layouts[12]} }, // dwindle     dwm-fibonacci
    { MODKEY,                       XK_g,          setlayout,         {.v = &layouts[13]} }, // gaplessgrid dwm-gaplessgrid
	{ MODKEY|ShiftMask,             XK_y,          setlayout,         {.v = &layouts[14]} }, // deck        dwm-deck-double
	{ MODKEY,                       XK_o,          setlayout,         {.v = &layouts[15]} }, // tatami      dwm-tatami
	{ MODKEY,                       XK_v,          setlayout,         {.v = &layouts[16]} }, // logarithmicspiral      dwm-tatami
	{ MODKEY,	                    XK_comma,      cyclelayout,       {.i = -1 } },
	{ MODKEY,                       XK_period,     cyclelayout,       {.i = +1 } },
	{ MODKEY,                       XK_space,      setlayout,         {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,    {0} },
	{ MODKEY|ShiftMask,             XK_s,          togglesticky,      {0} },                // dwm-sticky
	{ MODKEY,                       XK_f,          togglefullscreen,  {0} },                // dwm-actualfullscreen
	{ MODKEY,                       XK_0,          view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,               {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_comma,      focusmon,          {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,     focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,     tagmon,            {.i = +1 } },
    { MODKEY|ControlMask,           XK_h,          shiftview,         {.i = -1 } }, // shiftview
    { MODKEY|ControlMask,           XK_l,          shiftview,         {.i = +1 } }, // shiftview
 	{ MODKEY,                       XK_apostrophe, scratchpad_show,   {0} }, // dwm-scratchpad
 	{ MODKEY|ShiftMask,             XK_apostrophe, scratchpad_add,    {0} }, // dwm-scratchpad
 	{ MODKEY|ControlMask,           XK_apostrophe, scratchpad_remove, {0} }, // dwm-scratchpad
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
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
    { ClkTagBar,            0,              Button4,        shiftview,      { .i = -1 } }, // dwm-shiftview
    { ClkTagBar,            0,              Button5,        shiftview,      { .i = +1 } }, // dwm-shiftview
};

