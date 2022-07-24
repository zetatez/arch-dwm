/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 0;        /* snap pixel */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */  // dwm-swallow
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

static const SkipSwallow skipswallow[] = {                            // dwm-swallow: fix dwm-swallow annoying "swallow all parrent process problem". by myself
    /* fix dwm-swallow annoying "swallow all parrent process problem" // dwm-swallow: fix dwm-swallow annoying "swallow all parrent process problem". by myself
    * you can specify parrent and child process name to skip swallow  // dwm-swallow: fix dwm-swallow annoying "swallow all parrent process problem". by myself
    *                                                                 // dwm-swallow: fix dwm-swallow annoying "swallow all parrent process problem". by myself
    */                                                                // dwm-swallow: fix dwm-swallow annoying "swallow all parrent process problem". by myself
    {"st", "vimb"},                                                   // dwm-swallow: fix dwm-swallow annoying "swallow all parrent process problem". by myself
    {"st", "surf"},                                                   // dwm-swallow: fix dwm-swallow annoying "swallow all parrent process problem". by myself
};                                                                    // dwm-swallow: fix dwm-swallow annoying "swallow all parrent process problem". by myself

/* layout(s) */
static const float mfact            = 0.50; /* factor of master area size [0.00..1.00] */                 // limit [0.05..0.95] had been extended to [0.00..1.00].
static const int nmaster            = 1;    /* number of clients in master area */
// static const int resizehints     = 1;    /* 1 means respect size hints in tiled resizals */            // dwm-tatami
static const int resizehints        = 0;    /* 1 means respect size hints in tiled resizals */            // dwm-tatami
static const int lockfullscreen     = 1;    /* 1 will force focus on the fullscreen window */
static const int mcenterfirstwindow = 0;    /* factor of center first window size [0.20, 0.80] */         // dwm-centerfistwindow
static const float firstwindowszw   = 0.64; /* factor of center first window size width  [0.20, 0.80] */  // dwm-centerfistwindow
static const float firstwindowszh   = 0.48; /* factor of center first window size height [0.20, 0.80] */  // dwm-centerfistwindow
static const float centerwindowszw  = 0.64; /* factor of center window size width  [0.20, 0.80] */        // dwm-center my layout
static const float centerwindowszh  = 0.48; /* factor of center window size height [0.20, 0.80] */        // dwm-center my layout
static const float freeh            = 0.50; /* factor of free h [0.00..1.00] */                           // free h, by myself
static const float frees            = 0.50; /* factor of free s [0.00..1.00] */                           // free s, by myself

#include "layouts.c"                                   // layouts
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "Center ER",                 centerequalratio }, // dwm-center
	{ "Center AS",                   centeranyshape }, // dwm-center
	{ "Overlaylayer",              overlaylayergrid }, // dwm-overlaylayergrid
	{ "Overlaylayer",        overlaylayerhorizontal }, // dwm-overlaylayerhorizontal
	{ "Overlaylayer",          overlaylayervertical }, // dwm-overlaylayervertical
	{ "Deck",                        deckhorizontal }, // dwm-deckhorizontal
	{ "Deck",                          deckvertical }, // dwm-deckvertical
    { "Fibonacci",                           spiral }, // dwm-fibonacci
    { "Fibonacci",                          dwindle }, // dwm-fibonacci
	{ "Bottom Stack",           bottomstackvertical }, // dwm-bottomstack
	{ "Bottom Stack",         bottomstackhorizontal }, // dwm-bottomstack
    { "Tile Right",                       tileright }, // tile -> tileright
    { "Tile Left",                         tileleft }, // dwm-leftstack
    { "Grid",                                  grid }, // dwm-grid
	{ "Tatami",                              tatami }, // dwm-tatami
	{ "Logarithmic Spiral",       logarithmicspiral }, // dwm-logarithmicspiral
    { "Monocle",                            monocle },
	{ "Deck",                deckhorizontalvertical }, // dwm-deckhorizontalvertical
	{ "AnyAny",                     anywhereanysize }, // dwm-anywhereanysize
    { "∅",                                     NULL }, /* no layout function means floating behavior */
	{ NULL,                                    NULL }, // dwm-cyclelayouts
};

/* key definitions */
#define SUPKEY Mod1Mask
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
	{ MODKEY|ShiftMask,             XK_j,          setfreeh,          {.f = -0.025} },       // free h, by myself
	{ MODKEY|ShiftMask,             XK_k,          setfreeh,          {.f = +0.025} },       // free h, by myself
	{ MODKEY|ShiftMask,             XK_o,          setfrees,          {.f = -0.025} },       // free s, by myself
	{ MODKEY|ShiftMask,             XK_i,          setfrees,          {.f = +0.025} },       // free s, by myself
    { MODKEY,	                    XK_comma,      cyclelayout,       {.i = -1 } },
	{ MODKEY,                       XK_period,     cyclelayout,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,      movestack,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period,     movestack,         {.i = -1 } },
    { MODKEY|ControlMask,           XK_comma,      shiftview,         {.i = -1 } },          // shiftview
    { MODKEY|ControlMask,           XK_period,     shiftview,         {.i = +1 } },          // shiftview
	{ MODKEY,                       XK_0,          view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,          tag,               {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_m,          setlayout,         {.v = &layouts[0]} },  // centerequalratio         dwm-layouts
    { MODKEY,                       XK_v,          setlayout,         {.v = &layouts[1]} },  // centeranyshape           dwm-layouts
    { MODKEY,                       XK_g,          setlayout,         {.v = &layouts[2]} },  // overlaylayergrid         dwm-layouts
    { MODKEY,                       XK_w,          setlayout,         {.v = &layouts[3]} },  // overlaylayerhorizontal   dwm-layouts
    { MODKEY|ShiftMask,             XK_w,          setlayout,         {.v = &layouts[4]} },  // overlaylayervertical     dwm-layouts
	{ MODKEY,                       XK_e,          setlayout,         {.v = &layouts[5]} },  // deckvertical             dwm-layouts
	{ MODKEY|ShiftMask,             XK_e,          setlayout,         {.v = &layouts[6]} },  // deckhorizontal           dwm-layouts
	{ MODKEY,                       XK_r,          setlayout,         {.v = &layouts[7]} },  // sprial                   dwm-fibonacci
	{ MODKEY|ShiftMask,             XK_r,          setlayout,         {.v = &layouts[8]} },  // dwindle                  dwm-fibonacci
	{ MODKEY,                       XK_y,          setlayout,         {.v = &layouts[9]} },  // bstack                   dwm-bottomstackvertical
	{ MODKEY|ShiftMask,             XK_y,          setlayout,         {.v = &layouts[10]} }, // bstack                   dwm-bottomstackhorizontal
	{ MODKEY,                       XK_t,          setlayout,         {.v = &layouts[11]} }, // tileright                default tile
    { MODKEY|ShiftMask,             XK_t,          setlayout,         {.v = &layouts[12]} }, // lefttile                 dwm-lefttile
    { MODKEY|ShiftMask,             XK_g,          setlayout,         {.v = &layouts[13]} }, // gaplessgrid              dwm-gaplessgrid
	{ MODKEY,                       XK_o,          setlayout,         {.v = &layouts[14]} }, // tatami                   dwm-tatami
    { MODKEY|ShiftMask,             XK_v,          setlayout,         {.v = &layouts[15]} }, // logarithmicspiral        dwm-layouts
	{ MODKEY,                       XK_m,          setlayout,         {.v = &layouts[16]} }, // monocle
	{ MODKEY,                       XK_u,          setlayout,         {.v = &layouts[17]} }, // deckhorizontalvertical   dwm-layouts
	{ MODKEY|ShiftMask,             XK_u,          setlayout,         {.v = &layouts[18]} }, // anywhereanysize          dwm-anywhereanysize
	{ MODKEY|ShiftMask,             XK_f,          setlayout,         {.v = &layouts[19]} }, // no layout means floating
	{ MODKEY,                       XK_Return,     zoom,              {0} },
	{ MODKEY,                       XK_Tab,        view,              {0} },
	{ MODKEY|ShiftMask,             XK_c,          killclient,        {0} },
	{ MODKEY,                       XK_space,      setlayout,         {0} },
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,    {0} },
	{ MODKEY|ShiftMask,             XK_s,          togglesticky,      {0} },                 // dwm-sticky
	{ MODKEY,                       XK_f,          togglefullscreen,  {0} },                 // dwm-actualfullscreen
 	{ MODKEY,                       XK_apostrophe, scratchpad_show,   {0} },                 // dwm-scratchpad
 	{ MODKEY|ShiftMask,             XK_apostrophe, scratchpad_hide,   {0} },                 // dwm-scratchpad
 	{ MODKEY|ControlMask,           XK_apostrophe, scratchpad_remove, {0} },                 // dwm-scratchpad
	{ MODKEY,                       XK_minus,      focusmon,          {.i = -1 } },
	{ MODKEY,                       XK_equal,      focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_minus,      tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,      tagmon,            {.i = +1 } },
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
