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
