/* See LICENSE file for copyright and license details. */

/* clion (clang?) gets upset with a quoted string being passed in from the command line */
#define VERSION "6.2"

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
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

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY WLR_MODIFIER_ALT
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL,                     KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_SHIFT,                    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,  KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        		function        argument */
	{ MODKEY,                       XKB_KEY_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XKB_KEY_b,      togglebar,      {0} },
	{ MODKEY,                       XKB_KEY_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XKB_KEY_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XKB_KEY_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XKB_KEY_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XKB_KEY_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XKB_KEY_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XKB_KEY_Return, zoom,           {0} },
	{ MODKEY,                       XKB_KEY_Tab,    view,           {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_c,      killclient,     {0} },
	{ MODKEY,                       XKB_KEY_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XKB_KEY_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XKB_KEY_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XKB_KEY_space,  setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_space,  togglefloating, {0} },
	{ MODKEY,                       XKB_KEY_0,      view,           {.ui = ~0 } },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XKB_KEY_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XKB_KEY_period, focusmon,       {.i = +1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XKB_KEY_1,                      0)
	TAGKEYS(                        XKB_KEY_2,                      1)
	TAGKEYS(                        XKB_KEY_3,                      2)
	TAGKEYS(                        XKB_KEY_4,                      3)
	TAGKEYS(                        XKB_KEY_5,                      4)
	TAGKEYS(                        XKB_KEY_6,                      5)
	TAGKEYS(                        XKB_KEY_7,                      6)
	TAGKEYS(                        XKB_KEY_8,                      7)
	TAGKEYS(                        XKB_KEY_9,                      8)
	{ MODKEY|WLR_MODIFIER_SHIFT,    XKB_KEY_q,      quit,           {0} },
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
};

