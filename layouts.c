void                                                                         // dwm-fibonacci
fibonacci(Monitor *mon, int s) {                                             // dwm-fibonacci
	unsigned int i, n, nx, ny, nw, nh;                                       // dwm-fibonacci
	Client *c;                                                               // dwm-fibonacci
                                                                             // dwm-fibonacci
	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++); // dwm-fibonacci
	if(n == 0)                                                               // dwm-fibonacci
		return;                                                              // dwm-fibonacci
	                                                                         // dwm-fibonacci
	nx = mon->wx;                                                            // dwm-fibonacci
	ny = 0;                                                                  // dwm-fibonacci
	nw = mon->ww;                                                            // dwm-fibonacci
	nh = mon->wh;                                                            // dwm-fibonacci
	                                                                         // dwm-fibonacci
	for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {     // dwm-fibonacci
		if((i % 2 && nh / 2 > 2 * c->bw)                                     // dwm-fibonacci
		   || (!(i % 2) && nw / 2 > 2 * c->bw)) {                            // dwm-fibonacci
			if(i < n - 1) {                                                  // dwm-fibonacci
				if(i % 2)                                                    // dwm-fibonacci
					nh /= 2;                                                 // dwm-fibonacci
				else                                                         // dwm-fibonacci
					nw /= 2;                                                 // dwm-fibonacci
				if((i % 4) == 2 && !s)                                       // dwm-fibonacci
					nx += nw;                                                // dwm-fibonacci
				else if((i % 4) == 3 && !s)                                  // dwm-fibonacci
					ny += nh;                                                // dwm-fibonacci
			}                                                                // dwm-fibonacci
			if((i % 4) == 0) {                                               // dwm-fibonacci
				if(s)                                                        // dwm-fibonacci
					ny += nh;                                                // dwm-fibonacci
				else                                                         // dwm-fibonacci
					ny -= nh;                                                // dwm-fibonacci
			}                                                                // dwm-fibonacci
			else if((i % 4) == 1)                                            // dwm-fibonacci
				nx += nw;                                                    // dwm-fibonacci
			else if((i % 4) == 2)                                            // dwm-fibonacci
				ny += nh;                                                    // dwm-fibonacci
			else if((i % 4) == 3) {                                          // dwm-fibonacci
				if(s)                                                        // dwm-fibonacci
					nx += nw;                                                // dwm-fibonacci
				else                                                         // dwm-fibonacci
					nx -= nw;                                                // dwm-fibonacci
			}                                                                // dwm-fibonacci
			if(i == 0)                                                       // dwm-fibonacci
			{                                                                // dwm-fibonacci
				if(n != 1)                                                   // dwm-fibonacci
					nw = mon->ww * mon->mfact;                               // dwm-fibonacci
				ny = mon->wy;                                                // dwm-fibonacci
			}                                                                // dwm-fibonacci
			else if(i == 1)                                                  // dwm-fibonacci
				nw = mon->ww - nw;                                           // dwm-fibonacci
			i++;                                                             // dwm-fibonacci
		}                                                                    // dwm-fibonacci
		resize(c, nx, ny, nw - 2 * c->bw, nh - 2 * c->bw, False);            // dwm-fibonacci
	}                                                                        // dwm-fibonacci
}                                                                            // dwm-fibonacci
                                                                             // dwm-fibonacci
void                                                                         // dwm-fibonacci
dwindle(Monitor *mon) {                                                      // dwm-fibonacci
	fibonacci(mon, 1);                                                       // dwm-fibonacci
}                                                                            // dwm-fibonacci
                                                                             // dwm-fibonacci
void                                                                         // dwm-fibonacci
spiral(Monitor *mon) {                                                       // dwm-fibonacci
	fibonacci(mon, 0);                                                       // dwm-fibonacci
}                                                                            // dwm-fibonacci

void                                                                                // dwm-gaplessgrid
gaplessgrid(Monitor *m) {                                                           // dwm-gaplessgrid
	unsigned int n, cols, rows, cn, rn, i, cx, cy, cw, ch;                          // dwm-gaplessgrid
	Client *c;                                                                      // dwm-gaplessgrid
                                                                                    // dwm-gaplessgrid
	for(n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++) ;         // dwm-gaplessgrid
	if(n == 0)                                                                      // dwm-gaplessgrid
		return;                                                                     // dwm-gaplessgrid
                                                                                    // dwm-gaplessgrid
	/* grid dimensions */                                                           // dwm-gaplessgrid
	for(cols = 0; cols <= n/2; cols++)                                              // dwm-gaplessgrid
		if(cols*cols >= n)                                                          // dwm-gaplessgrid
			break;                                                                  // dwm-gaplessgrid
	if(n == 5) /* set layout against the general calculation: not 1:2:2, but 2:3 */ // dwm-gaplessgrid
		cols = 2;                                                                   // dwm-gaplessgrid
	rows = n/cols;                                                                  // dwm-gaplessgrid
                                                                                    // dwm-gaplessgrid
	/* window geometries */                                                         // dwm-gaplessgrid
	cw = cols ? m->ww / cols : m->ww;                                               // dwm-gaplessgrid
	cn = 0; /* current column number */                                             // dwm-gaplessgrid
	rn = 0; /* current row number */                                                // dwm-gaplessgrid
	for(i = 0, c = nexttiled(m->clients); c; i++, c = nexttiled(c->next)) {         // dwm-gaplessgrid
		if(i/rows + 1 > cols - n%cols)                                              // dwm-gaplessgrid
			rows = n/cols + 1;                                                      // dwm-gaplessgrid
		ch = rows ? m->wh / rows : m->wh;                                           // dwm-gaplessgrid
		cx = m->wx + cn*cw;                                                         // dwm-gaplessgrid
		cy = m->wy + rn*ch;                                                         // dwm-gaplessgrid
		resize(c, cx, cy, cw - 2 * c->bw, ch - 2 * c->bw, False);                   // dwm-gaplessgrid
		rn++;                                                                       // dwm-gaplessgrid
		if(rn >= rows) {                                                            // dwm-gaplessgrid
			rn = 0;                                                                 // dwm-gaplessgrid
			cn++;                                                                   // dwm-gaplessgrid
		}                                                                           // dwm-gaplessgrid
	}                                                                               // dwm-gaplessgrid
}                                                                                   // dwm-gaplessgrid
                                                                                    // dwm-gaplessgrid


