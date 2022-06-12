// layouts

 // dwm-centerfirstwindow
void
centerfirstwindow(Monitor *m) {
    float fwszw,fwszh = 0.5;
    Client * c = nexttiled(m->clients);

    fwszw = (firstwindowszw > 0.8) ? 0.8 : firstwindowszw;
    fwszw = (firstwindowszw < 0.2) ? 0.2 : firstwindowszw;
    fwszh = (firstwindowszh > 0.8) ? 0.8 : firstwindowszh;
    fwszh = (firstwindowszh < 0.2) ? 0.2 : firstwindowszh;

	resize(c, m->ww/2 - (m->ww * fwszw)/2, m->wh/2 - m->wh * fwszh/2, m->ww * fwszw - 2 * c->bw, m->wh * fwszh - 2 * c->bw, False);
    return;
}

/* dwm-logarithmic-spiral ------------------------------------------------------------ */
// control the shape of logarithmic spiral
static const float logarithmicspiralstart = -50;
static const float logarithmicspiralstop  = 50;
static const float logarithmicspiralstep  = 0.1;    // control the interval of each window
static const float logarithmicspiralalpha = 1;
static const float logarithmicspiralkapa  = 0.2;   // control the interval of each window cycle: 0.2, 0.025, 0.05, 0.3063489(golden LS)
static const int   logarithmicspirallen   = (const int) ((logarithmicspiralstop - logarithmicspiralstart )/logarithmicspiralstep);

#include<math.h>
void
logarithmicspiral(Monitor *m) {
	unsigned int n, idx;
    float i, v, minx, maxx, miny, maxy;
    float phi[logarithmicspirallen];

    float x[logarithmicspirallen];
    float y[logarithmicspirallen];

    float ww[logarithmicspirallen];
    float wh[logarithmicspirallen];
    float wx[logarithmicspirallen];
    float wy[logarithmicspirallen];

	Client *c;
                                                                             
    for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
    if(n == 0)
        return;

    for (idx = 0, i = logarithmicspiralstart; i < logarithmicspiralstop && idx < sizeof(phi) / sizeof(phi[0]); i += logarithmicspiralstep, phi[idx] = i, idx++);
    for (idx = 0; idx < sizeof(phi) / sizeof(phi[0]); idx++) {
        v = logarithmicspiralalpha * exp(logarithmicspiralkapa * phi[idx]);
        x[idx] = v * cos(phi[idx]);
        y[idx] = v * sin(phi[idx]);
    }

    // min max
    minx = maxx = x[0];
    miny = maxy = y[0];

    for (idx = 1; idx < sizeof(phi) / sizeof(phi[0]); idx++) {
        if (x[idx] < minx) { minx = x[idx]; }
        if (x[idx] > maxx) { maxx = x[idx]; }
        if (y[idx] < miny) { miny = y[idx]; }
        if (y[idx] > maxy) { maxy = y[idx]; }
    }

    // min max normal
    for (idx = 0; idx < sizeof(phi) / sizeof(phi[0]); idx++) {
        x[idx] = (x[idx] - minx)/(maxx-minx);
        y[idx] = (y[idx] - miny)/(maxy-miny);
    }

    // allocate window size
    for (idx = 0; idx < sizeof(phi) / sizeof(phi[0]); idx++) {
        ww[idx] = 96;
        wh[idx] = 32;
        wx[idx] = (m->ww - 2*ww[idx]/2) * x[idx] - ww[idx]/2;
        wy[idx] = (m->wh - 2*wh[idx]/2) * y[idx] - wh[idx]/2;
    }

    // last -1 window center
    idx = logarithmicspirallen-1;
    ww[idx] = 1280;
    wh[idx] = 480;
    wx[idx] = m->ww/2 - ww[idx]/2;
    wy[idx] = m->wh/2 - wh[idx]/2;

    // last -2 window center
    idx = logarithmicspirallen-2;
    ww[idx] = 420;
    wh[idx] = 140;
    wx[idx] = wx[idx] - ww[idx]/2;
    wy[idx] = wy[idx];
    
    // last -5 window center
    idx = logarithmicspirallen-5;
    ww[idx] = 320;
    wh[idx] = 120;
    wx[idx] = wx[idx] - ww[idx]/2;
    wy[idx] = wy[idx];
    
    // last -10 window center
    idx = logarithmicspirallen-10;
    ww[idx] = 360;
    wh[idx] = 120;
    wx[idx] = wx[idx] - ww[idx]/2;
    wy[idx] = wy[idx];
    
    // last -16 window center
    idx = logarithmicspirallen-16;
    ww[idx] = 640;
    wh[idx] = 240;
    wx[idx] = wx[idx] - ww[idx]/2;
    wy[idx] = wy[idx];
    
    // last -23 window center
    idx = logarithmicspirallen-23;
    ww[idx] = 240;
    wh[idx] = 80;
    wx[idx] = wx[idx] - ww[idx]/2;
    wy[idx] = wy[idx];
    
    // last -31 window center
    idx = logarithmicspirallen-31;
    ww[idx] = 320;
    wh[idx] = 120;
    wx[idx] = wx[idx] - ww[idx]/2;
    wy[idx] = wy[idx];
    
    // last -36 window center
    idx = logarithmicspirallen-36;
    ww[idx] = 240;
    wh[idx] = 80;
    wx[idx] = wx[idx] - ww[idx]/2;
    wy[idx] = wy[idx];
    
    // last -48 window center
    idx = logarithmicspirallen-48;
    ww[idx] = 320;
    wh[idx] = 120;
    wx[idx] = wx[idx] - ww[idx]/2;
    wy[idx] = wy[idx];
    
    if (n > 1) {
        // oldest window bottom right coner
        idx = logarithmicspirallen-1-(n-1);
        ww[idx] = 640;
        wh[idx] = 240;
        wx[idx] = m->ww - ww[idx];
        wy[idx] = m->wh - wh[idx];
    }

	for(i = 0, c = nexttiled(m->clients); c && i < logarithmicspirallen; c = nexttiled(c->next), i++) {
        idx = logarithmicspirallen - 1 - i;
        wx[idx] = wx[idx] < 0 ? 0: wx[idx];
        wy[idx] = wy[idx] < 0 ? 0: wy[idx];
        wx[idx] = wx[idx] + ww[idx] > m->ww ? m->ww - ww[idx]: wx[idx];
        wy[idx] = wy[idx] + wh[idx] > m->wh ? m->wh - wh[idx]: wy[idx];
	    resize(c, m->wx + wx[idx], m->wy + wy[idx], ww[idx] - 2 * c->bw, wh[idx] - 2 * c->bw, False);
	}
}

/* dwm-cake ------------------------------------------------------------ */
void
cakevertical(Monitor *m) {
	unsigned int n, i;
	Client *c;
                                                                                    
	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++) ;
	if(n == 0)
		return;
    
    float cwszw,cwszh,cfact;

    // allow dynamic
    cfact = m->mfact;
    
    cfact = (m->mfact > 0.8) ? 0.8 : m->mfact;
    cfact = (m->mfact < 0.2) ? 0.2 : m->mfact;

    /* cfact = (cakefact > 0.8) ? 0.8 : cakefact; */
    /* cfact = (cakefact < 0.2) ? 0.2 : cakefact; */

    cwszw = (cakewindowszw > 0.8) ? 0.8 : cakewindowszw;
    cwszw = (cakewindowszw < 0.2) ? 0.2 : cakewindowszw;
    cwszh = (cakewindowszh > 0.8) ? 0.8 : cakewindowszh;
    cwszh = (cakewindowszh < 0.2) ? 0.2 : cakewindowszh;

    cwszh = (cwszh > cfact) ? cfact : cwszh;
    
	for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
        if (i < 1) {
            if (n != 1 && m->sel->centerfirstwindow)  { resize(c, m->ww/2 - (m->ww * cwszw)/2, m->wy + m->wh * cfact - m->wh * cwszh, m->ww * cwszw - 2 * c->bw, m->wh * cwszh - 2 * c->bw, False); }
            if (n != 1 && !m->sel->centerfirstwindow) { resize(c, 0, m->wy, m->ww - 2 * c->bw, m->wh * cfact - 2 * c->bw, False); }
            if (n == 1 && m->sel->centerfirstwindow)  { resize(c, m->ww/2 - m->ww * cwszw/2, m->wy + m->wh * cfact - m->wh * cwszh, m->ww * cwszw - 2 * c->bw, m->wh * cwszh - 2 * c->bw, False); }
            if (n == 1 && !m->sel->centerfirstwindow) { resize(c, 0, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, False); }
        /* } else if (i == n-1 && n != 1 && n != 2) { // oldest on top */
		    /* resize(c, m->ww/2 - m->ww * cwszw * 0.7/2, m->wy, m->ww * cwszw * 0.7 - 2 * c->bw, m->wh * (cfact - cwszh) - 2 * c->bw, False); */
        } else { // else always buttom
		    resize(c, m->wx + (n-i-1) * m->ww/(n-1), m->wy + m->wh * cfact, m->ww/(n-1) - 2 * c->bw, m->wh * (1 - cfact) - 2 * c->bw, False);
        }
	}
}

void
cakehorizontal(Monitor *m) {
	unsigned int n, i;
	Client *c;
                                                                                    
	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++) ;
	if(n == 0)
		return;
    
    float cwszw,cwszh,cfact;

    // allow dynamic
    cfact = m->mfact;
    
    cfact = (m->mfact > 0.8) ? 0.8 : m->mfact;
    cfact = (m->mfact < 0.2) ? 0.2 : m->mfact;

    /* cfact = (cakefact > 0.8) ? 0.8 : cakefact; */
    /* cfact = (cakefact < 0.2) ? 0.2 : cakefact; */

    cwszw = (cakewindowszw > 0.8) ? 0.8 : cakewindowszw;
    cwszw = (cakewindowszw < 0.2) ? 0.2 : cakewindowszw;
    cwszh = (cakewindowszh > 0.8) ? 0.8 : cakewindowszh;
    cwszh = (cakewindowszh < 0.2) ? 0.2 : cakewindowszh;

    cwszh = (cwszh > cfact) ? cfact : cwszh;

	for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
        if (i < 1) {
            if (n != 1 && m->sel->centerfirstwindow)  { resize(c, m->ww/2 - (m->ww * cwszw)/2, m->wy + m->wh * cfact - m->wh * cwszh, m->ww * cwszw - 2 * c->bw, m->wh * cwszh - 2 * c->bw, False); }
            if (n != 1 && !m->sel->centerfirstwindow) { resize(c, 0, m->wy, m->ww - 2 * c->bw, m->wh * cfact - 2 * c->bw, False); }
            if (n == 1 && m->sel->centerfirstwindow)  { resize(c, m->ww/2 - m->ww * cwszw/2, m->wy + m->wh * cfact - m->wh * cwszh, m->ww * cwszw - 2 * c->bw, m->wh * cwszh - 2 * c->bw, False); }
            if (n == 1 && !m->sel->centerfirstwindow) { resize(c, 0, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, False); }
        /* } else if (i == n-1 && n != 1 && n != 2) { // oldest on top */
		    /* resize(c, m->ww/2 - m->ww * cwszw * 0.7/2, m->wy, m->ww * cwszw * 0.7 - 2 * c->bw, m->wh * (cfact - cwszh) - 2 * c->bw, False); */
        } else { // else always buttom
		    resize(c, 0, m->wy + m->wh * cfact + (n-i-1) * m->wh * (1 - cfact)/(n-1), m->ww - 2 * c->bw, m->wh * (1 - cfact) / (n-1) - 2 * c->bw, False);
        }
	}
}
void
cakefullbottom(Monitor *m) {
	unsigned int n, i;
	Client *c;
                                                                                    
	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++) ;
	if(n == 0)
		return;
    
    float cwszw,cwszh,cfact;

    // allow dynamic
    cfact = m->mfact;
    
    cfact = (m->mfact > 0.8) ? 0.8 : m->mfact;
    cfact = (m->mfact < 0.2) ? 0.2 : m->mfact;

    /* cfact = (cakefact > 0.8) ? 0.8 : cakefact; */
    /* cfact = (cakefact < 0.2) ? 0.2 : cakefact; */

    cwszw = (cakewindowszw > 0.8) ? 0.8 : cakewindowszw;
    cwszw = (cakewindowszw < 0.2) ? 0.2 : cakewindowszw;
    cwszh = (cakewindowszh > 0.8) ? 0.8 : cakewindowszh;
    cwszh = (cakewindowszh < 0.2) ? 0.2 : cakewindowszh;

    cwszh = (cwszh > cfact) ? cfact : cwszh;
    
	for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
        if (i < 1) {
            if (n != 1 && m->sel->centerfirstwindow)  { resize(c, m->ww/2 - (m->ww * cwszw)/2, m->wy + m->wh * cfact - m->wh * cwszh, m->ww * cwszw - 2 * c->bw, m->wh * cwszh - 2 * c->bw, False); }
            if (n != 1 && !m->sel->centerfirstwindow) { resize(c, 0, m->wy, m->ww - 2 * c->bw, m->wh * cfact - 2 * c->bw, False); }
            if (n == 1 && m->sel->centerfirstwindow)  { resize(c, m->ww/2 - m->ww * cwszw/2, m->wy + m->wh * cfact - m->wh * cwszh, m->ww * cwszw - 2 * c->bw, m->wh * cwszh - 2 * c->bw, False); }
            if (n == 1 && !m->sel->centerfirstwindow) { resize(c, 0, m->wy, m->ww - 2 * c->bw, m->wh - 2 * c->bw, False); }
        /* } else if (i == n-1 && n != 1 && n != 2) { // oldest on top */
		    /* resize(c, m->ww/2 - m->ww * cwszw * 0.7/2, m->wy, m->ww * cwszw * 0.7 - 2 * c->bw, m->wh * (cfact - cwszh) - 2 * c->bw, False); */
        } else { // else always buttom
		    resize(c, 0, m->wy + m->wh * cfact, m->ww - 2 * c->bw, m->wh * (1 - cfact) - 2 * c->bw, False);
        }
	}
}

/* dwm-fibonacci ------------------------------------------------------------ */
void
fibonacci(Monitor *m, int s) {
	unsigned int i, n, nx, ny, nw, nh;
	Client *c;
                                                                             
    for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
    if(n == 0)
        return;

    if (n == 1 && mcenterfirstwindow && m->sel->centerfirstwindow) { centerfirstwindow(m);  return; };        // dwm-centerfirstwindow

    nx = m->wx;
    ny = 0;
    nw = m->ww;
    nh = m->wh;

    for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
        if((i % 2 && nh / 2 > 2 * c->bw)
                || (!(i % 2) && nw / 2 > 2 * c->bw)) {
            if(i < n - 1) {
                if(i % 2)
                    nh /= 2;
                else
                    nw /= 2;
                if((i % 4) == 2 && !s)
                    nx += nw;
                else if((i % 4) == 3 && !s)
                    ny += nh;
            }
            if((i % 4) == 0) {
                if(s)
                    ny += nh;
                else
                    ny -= nh;
            }
            else if((i % 4) == 1)
                nx += nw;
            else if((i % 4) == 2)
                ny += nh;
            else if((i % 4) == 3) {
                if(s)
                    nx += nw;
                else
                    nx -= nw;
            }
            if(i == 0)
            {
                if(n != 1)
                    nw = m->ww * m->mfact;
                ny = m->wy;
            }
            else if(i == 1)
                nw = m->ww - nw;
            i++;
        }
        resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
    }
}
                                                                             
void
dwindle(Monitor *m) {
	fibonacci(m, 1);
}
                                                                             
void
spiral(Monitor *m) {
	fibonacci(m, 0);
}

/* dwm-gaplessgrid ------------------------------------------------------------ */
void
gaplessgrid(Monitor *m) {
	unsigned int n, cols, rows, cn, rn, i, cx, cy, cw, ch;
	Client *c;
                                                                                    
	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++) ;
	if(n == 0)
		return;
    
    if(n == 1 && m->sel->centerfirstwindow) { centerfirstwindow(m); return; }                                // dwm-centerfirstwindow
                                                                                    
	/* grid dimensions */
	for(cols = 0; cols <= n/2; cols++)
		if(cols*cols >= n)
			break;
	if(n == 5) /* set layout against the general calculation: not 1:2:2, but 2:3 */
		cols = 2;
	rows = n/cols;
                                                                                    
	/* window geometries */
	cw = cols ? m->ww / cols : m->ww;
	cn = 0; /* current column number */
	rn = 0; /* current row number */
	for(i = 0, c = nexttiled(m->clients); c; i++, c = nexttiled(c->next)) {
		if(i/rows + 1 > cols - n%cols)
			rows = n/cols + 1;
		ch = rows ? m->wh / rows : m->wh;
		cx = m->wx + cn*cw;
		cy = m->wy + rn*ch;
		resize(c, cx, cy, cw - 2 * c->bw, ch - 2 * c->bw, False);
		rn++;
		if(rn >= rows) {
			rn = 0;
			cn++;
		}
	}
}
                                                                                    
/* dwm-lefttile ------------------------------------------------------------ */
void
tileleft(Monitor *m)
{
	unsigned int i, n, h, mw, my, ty;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

    if (n == 1 && mcenterfirstwindow && m->sel->centerfirstwindow) { centerfirstwindow(m);  return; };        // dwm-centerfirstwindow

	if (n > m->nmaster)
		mw = m->nmaster ? m->ww * m->mfact : 0;
	else
		mw = m->ww;
	for (i = my = ty = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
		if (i < m->nmaster) {
			h = (m->wh - my) / (MIN(n, m->nmaster) - i);
// 			resize(c, m->wx, m->wy + my, mw - (2*c->bw), h - (2*c->bw), 0);
			resize(c, m->wx + m->ww - mw, m->wy + my, mw - (2*c->bw), h - (2*c->bw), 0);
			if (my + HEIGHT(c) < m->wh)
				my += HEIGHT(c);
		} else {
			h = (m->wh - ty) / (n - i);
//          resize(c, m->wx + mw, m->wy + ty, m->ww - mw - (2*c->bw), h - (2*c->bw), 0);
			resize(c, m->wx, m->wy + ty, m->ww - mw - (2*c->bw), h - (2*c->bw), 0);
			if (ty + HEIGHT(c) < m->wh)
				ty += HEIGHT(c);
		}
}

/* dwm-bottomstack ------------------------------------------------------------ */
static void
bstackvertical(Monitor *m) {
	int w, h, mh, mx, tx, ty, tw;
	unsigned int i, n;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

    if (n == 1 && mcenterfirstwindow && m->sel->centerfirstwindow) { centerfirstwindow(m);  return; };        // dwm-centerfirstwindow
                                                                                //
	if (n > m->nmaster) {
		mh = m->nmaster ? m->mfact * m->wh : 0;
		tw = m->ww / (n - m->nmaster);
		ty = m->wy + mh;
	} else {
		mh = m->wh;
		tw = m->ww;
		ty = m->wy;
	}
	for (i = mx = 0, tx = m->wx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (i < m->nmaster) {
			w = (m->ww - mx) / (MIN(n, m->nmaster) - i);
			resize(c, m->wx + mx, m->wy, w - (2 * c->bw), mh - (2 * c->bw), 0);
			mx += WIDTH(c);
		} else {
			h = m->wh - mh;
			resize(c, tx, ty, tw - (2 * c->bw), h - (2 * c->bw), 0);
			if (tw != m->ww)
				tx += WIDTH(c);
		}
	}
}

static void
bstackhorizontal(Monitor *m) {
	int w, mh, mx, tx, ty, th;
	unsigned int i, n;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

    if (n == 1 && mcenterfirstwindow && m->sel->centerfirstwindow) { centerfirstwindow(m);  return; };        // dwm-centerfirstwindow

	if (n > m->nmaster) {
		mh = m->nmaster ? m->mfact * m->wh : 0;
		th = (m->wh - mh) / (n - m->nmaster);
		ty = m->wy + mh;
	} else {
		th = mh = m->wh;
		ty = m->wy;
	}
	for (i = mx = 0, tx = m->wx, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++) {
		if (i < m->nmaster) {
			w = (m->ww - mx) / (MIN(n, m->nmaster) - i);
			resize(c, m->wx + mx, m->wy, w - (2 * c->bw), mh - (2 * c->bw), 0);
			mx += WIDTH(c);
		} else {
			resize(c, tx, ty, m->ww - (2 * c->bw), th - (2 * c->bw), 0);
			if (th != m->wh)
				ty += HEIGHT(c);
		}
	}
}

/* dwm-deck-double ------------------------------------------------------------ */
void
deck(Monitor *m) {
    unsigned int i, n, mw;
    Client *c;

    for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
    if(n == 0)
        return;

    if (n == 1 && mcenterfirstwindow && m->sel->centerfirstwindow) { centerfirstwindow(m);  return; };        // dwm-centerfirstwindow

    if(n > m->nmaster)
        mw = m->nmaster ? m->ww * m->mfact : 0;
    else
        mw = m->ww;

    for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
        if(i < m->nmaster)
            resize(c, m->wx, m->wy, mw - (2*c->bw), m->wh - (2*c->bw), c->bw);
        else
            resize(c, m->wx + mw, m->wy, m->ww - mw - (2*c->bw), m->wh - (2*c->bw), c->bw);
}

/* dwm-tilewide ------------------------------------------------------------ */
void
tilewide(Monitor *m)
{
    unsigned int i, n, w, h, mw, mx, ty;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

    if (n == 1 && mcenterfirstwindow && m->sel->centerfirstwindow) { centerfirstwindow(m);  return; };        // dwm-centerfirstwindow

	if (n > m->nmaster)
		mw = m->nmaster ? m->ww * m->mfact : 0;
	else
		mw = m->ww;
	for (i = mx = ty = 0, c = nexttiled(m->clients); c;
	     c = nexttiled(c->next), i++)
		if (i < m->nmaster) {
		        w = (mw - mx) / (MIN(n, m->nmaster) - i);
		        resize(c, m->wx + mx, m->wy, w - (2*c->bw), (m->wh - ty) - (2*c->bw), 0);
		        if  (mx + WIDTH(c) < m->ww)
		                mx += WIDTH(c);
		} else {
			h = (m->wh - ty) / (n - i);
			resize(c, m->wx + mw, m->wy + ty, m->ww - mw - (2*c->bw), h - (2*c->bw), 0);
			if (ty + HEIGHT(c) < m->wh)
				ty += HEIGHT(c);
		}
}

/* dwm-tatami ------------------------------------------------------------ */
void
tatami(Monitor *m) {
	unsigned int i, n, nx, ny, nw, nh,
				 mats, tc,
				 tnx, tny, tnw, tnh;
	Client *c;

	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), ++n);
	if(n == 0)
		return;

    if (n == 1 && mcenterfirstwindow && m->sel->centerfirstwindow) { centerfirstwindow(m);  return; };        // dwm-centerfirstwindow
	
	nx = m->wx;
	ny = 0;
	nw = m->ww;
	nh = m->wh;
	
	c = nexttiled(m->clients);
	
	if(n != 1)  nw = m->ww * m->mfact;
				ny = m->wy;
				
	resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
	
	c = nexttiled(c->next);
	
	nx += nw;
	nw = m->ww - nw;
	
	if(n>1)
	{
	
	tc = n-1;
	mats = tc/5;
	
	nh/=(mats + (tc % 5 > 0));
	
	for(i = 0; c && (i < (tc % 5)); c = nexttiled(c->next))
	{
		tnw=nw;
		tnx=nx;
		tnh=nh;
		tny=ny;
		switch(tc - (mats*5))
				{
					case 1://fill
						break;
					case 2://up and down
						if((i % 5) == 0) //up
						tnh/=2;
						else if((i % 5) == 1) //down
						{
							tnh/=2;
							tny += nh/2;
						}
						break;
					case 3://bottom, up-left and up-right
						if((i % 5) == 0) //up-left
						{
						tnw = nw/2;
						tnh = (2*nh)/3;
						}
						else if((i % 5) == 1)//up-right
						{
							tnx += nw/2;
							tnw = nw/2;
							tnh = (2*nh)/3;
						}
						else if((i % 5) == 2)//bottom
						{
							tnh = nh/3;
							tny += (2*nh)/3;
						}
						break;
					case 4://bottom, left, right and top
						if((i % 5) == 0) //top
						{
							tnh = (nh)/4;
						}
						else if((i % 5) == 1)//left
						{
							tnw = nw/2;
							tny += nh/4;
							tnh = (nh)/2;
						}
						else if((i % 5) == 2)//right
						{
							tnx += nw/2;
							tnw = nw/2;
							tny += nh/4;
							tnh = (nh)/2;
						}
						else if((i % 5) == 3)//bottom
						{
							tny += (3*nh)/4;
							tnh = (nh)/4;
						}
						break;
				}
		++i;
		resize(c, tnx, tny, tnw - 2 * c->bw, tnh - 2 * c->bw, False);
	}
	
	++mats;
	
	for(i = 0; c && (mats>0); c = nexttiled(c->next)) {

			if((i%5)==0)
			{
			--mats;
			if(((tc % 5) > 0)||(i>=5))
			ny+=nh;
			}
			
			tnw=nw;
			tnx=nx;
			tnh=nh;
			tny=ny;
			

			switch(i % 5)
			{
				case 0: //top-left-vert
					tnw = (nw)/3;
					tnh = (nh*2)/3;
					break;
				case 1: //top-right-hor
					tnx += (nw)/3;
					tnw = (nw*2)/3;
					tnh = (nh)/3;
					break;
				case 2: //center
					tnx += (nw)/3;
					tnw = (nw)/3;
					tny += (nh)/3;
					tnh = (nh)/3;
					break;
				case 3: //bottom-right-vert
					tnx += (nw*2)/3;
					tnw = (nw)/3;
					tny += (nh)/3;
					tnh = (nh*2)/3;
					break;
				case 4: //(oldest) bottom-left-hor
					tnw = (2*nw)/3;
					tny += (2*nh)/3;
					tnh = (nh)/3;
					break;
				default:
					break;
			}
			
			++i;
			//i%=5;
		resize(c, tnx, tny, tnw - 2 * c->bw, tnh - 2 * c->bw, False);
		}
	}
}
