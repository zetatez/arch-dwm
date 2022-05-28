// layouts

 // dwm-centerfirstwindow
void
centerfirstwindow(int n) {
    if (!mcenterfirstwindow) { return; }

    float fwszw,fwszh = 0.5;
    fwszw = (firstwindowszw > 0.8) ? 0.8 : firstwindowszw;
    fwszw = (firstwindowszw < 0.2) ? 0.2 : firstwindowszw;
    fwszh = (firstwindowszh > 0.8) ? 0.8 : firstwindowszh;
    fwszh = (firstwindowszh < 0.2) ? 0.2 : firstwindowszh;

	if (n == 1 && selmon->sel->CenterThisWindow)
        resizeclient(selmon->sel,
                (selmon->mw - selmon->mw * fwszw) / 2,
                (selmon->mh - selmon->mh * fwszh) / 2,
                selmon->mw * fwszw,
                selmon->mh * fwszh);
}

/* dwm-fibonacci ------------------------------------------------------------ */
void
fibonacci(Monitor *mon, int s) {
	unsigned int i, n, nx, ny, nw, nh;
	Client *c;
                                                                             
    for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
    if(n == 0)
        return;

    nx = mon->wx;
    ny = 0;
    nw = mon->ww;
    nh = mon->wh;

    for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
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
                    nw = mon->ww * mon->mfact;
                ny = mon->wy;
            }
            else if(i == 1)
                nw = mon->ww - nw;
            i++;
        }
        resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);
    }

    centerfirstwindow(n);
}
                                                                             
void
dwindle(Monitor *mon) {
	fibonacci(mon, 1);
}
                                                                             
void
spiral(Monitor *mon) {
	fibonacci(mon, 0);
}

/* dwm-gaplessgrid ------------------------------------------------------------ */
void
gaplessgrid(Monitor *m) {
	unsigned int n, cols, rows, cn, rn, i, cx, cy, cw, ch;
	Client *c;
                                                                                    
	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++) ;
	if(n == 0)
		return;
                                                                                    
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
    
    centerfirstwindow(n);
}
                                                                                    
/* dwm-lefttile ------------------------------------------------------------ */
void
lefttile(Monitor *m)
{
	unsigned int i, n, h, mw, my, ty;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

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

    centerfirstwindow(n);
}

/* dwm-bottomstack ------------------------------------------------------------ */
static void
bstack(Monitor *m) {
	int w, h, mh, mx, tx, ty, tw;
	unsigned int i, n;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;
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
    
    centerfirstwindow(n);
}

static void
bstackhoriz(Monitor *m) {
	int w, mh, mx, tx, ty, th;
	unsigned int i, n;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;
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

    centerfirstwindow(n);
}

/* dwm-deck-double ------------------------------------------------------------ */
void
deck(Monitor *m) {
    unsigned int i, n, mw;
    Client *c;

    for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
    if(n == 0)
        return;

    if(n > m->nmaster)
        mw = m->nmaster ? m->ww * m->mfact : 0;
    else
        mw = m->ww;

    for(i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), i++)
        if(i < m->nmaster)
            resize(c, m->wx, m->wy, mw - (2*c->bw), m->wh - (2*c->bw), c->bw);
        else
            resize(c, m->wx + mw, m->wy, m->ww - mw - (2*c->bw), m->wh - (2*c->bw), c->bw);

    centerfirstwindow(n);
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

    centerfirstwindow(n);
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

    centerfirstwindow(n);
}
