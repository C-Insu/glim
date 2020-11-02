#include "stdafx.h"
#include "reedsolomon.h"

int gfpwr[2][255];
int gflog[2][256];

int GFmul(int p1, int p2, int symbol_type)
{
	int i;
	if ((p1 == 0) || (p2 == 0)) return 0;
	i = gflog[symbol_type][p1] + gflog[symbol_type][p2];
	if (i > 254) i -= 255;
	i = gfpwr[symbol_type][i];
	return i;
}

int GFdiv(int p1, int p2, int symbol_type)
{
	int i;
	if (p2 == 0) return 0; //Devide by Zero..
	if (p1 == 0) return 0;
	i = gflog[symbol_type][p1] - gflog[symbol_type][p2];
	if (i < 0) i += 255;
	if (i > 254) i -= 255;
	i = gfpwr[symbol_type][i];
	return i;
}

#define GEN_DATAMATRIX		0x2d
#define GEN_QRCODE		0x1d

void InitLogTables()
{
	int i, j;
//DataMatrix
	for (j=0;j<256;j++) gflog[DATAMATRIX][j] = 0;	
	i = 1;
	for (j=0;j<255;j++)
	{
		gfpwr[DATAMATRIX][j] = i;
		gflog[DATAMATRIX][i] = j;
		i <<= 1;
		if (i > 255)
			i ^= GEN_DATAMATRIX + 256;
	}
//QRCode
	for (j=0;j<256;j++) gflog[QRCODE][j] = 0;	
	i = 1;
	for (j=0;j<255;j++)
	{
		gfpwr[QRCODE][j] = i;
		gflog[QRCODE][i] = j;
		i <<= 1;
		if (i > 255)
			i ^= GEN_QRCODE + 256;
	}
}

#define MAXBUF	256
#define	MAXTOEPLITZ		37
int logsym[MAXBUF];
int pwrlogsym[MAXBUF];
int syndrome[MAXBUF];
int tpltzarray[MAXTOEPLITZ*(MAXTOEPLITZ+10)];
int tpltzrslt[MAXTOEPLITZ];
int errloc[MAXTOEPLITZ];
int	ssize;
unsigned char * m_RSCode;

void CalcSyndromes(int size, int rssize, int isize, int v, int symbol_type) 
{
	int i, i1, j, n;

	/* init array of logs of sym chars */
	for (i = 0; i < size; i++ ) {
		i1 = ((m_RSCode[i]==0) ? 255 : gflog[symbol_type][m_RSCode[i]] );
		if (i1 != 255) {
			i1 = i1 + (size - i);
			i1 = ( (i1 > 254) ? (i1 - 255) : i1 );
		}
		logsym[i] = i1;
	}
	/* calculate syndromes */
	for (j = 0; j < rssize*2; j++) {
		syndrome[j] = 0;
		for (i = 0; i < size; i++) {
			if (logsym[i] != 255) {
				syndrome[j] ^= gfpwr[symbol_type][logsym[i]];
				n = logsym[i] + (size - i);
				logsym[i] = ( (n > 254) ? (n - 255) : n );
			}
		}
	}
	/* use syndromes to initialize solution matrix tpltzarray */
	for (j = n = 0; j < MAXTOEPLITZ*rssize; j += MAXTOEPLITZ, n++) {
		for (i = 0; i <= rssize; i++) {
			tpltzarray[j + i] = syndrome[n + i];
		}
	}
}

int NormlzToeplitz(int size,int symbol_type) 
{
	int x, y, x1, y1, n;

	for (x = y = 0; x < size; x++, y++) {
		/* if entry in top row is 0; swap it with a lower non-0 row */
		if (tpltzarray[x+(MAXTOEPLITZ*y)] == 0) {
			for (y1 = y+1; y1 < size; y1++) {
				if (tpltzarray[x+(MAXTOEPLITZ*y1)] != 0) {
					for (x1 = x; x1 <= size; x1++) {
						/* swap entries */
						n = tpltzarray[x1+(MAXTOEPLITZ*y1)];
						tpltzarray[x1+(MAXTOEPLITZ*y1)] = tpltzarray[x1+(MAXTOEPLITZ*y)];
						tpltzarray[x1+(MAXTOEPLITZ*y)] = n;
					}
					break;
				}
			}
			/* if all were 0, same row but increment to next column */
			if (y1 == size) {
				y--;
				continue;
			}
		}
		/* use y row to 0 all higher x column entries */
		for (y1 = y+1; y1 < size; y1++) {
			if (tpltzarray[x+(MAXTOEPLITZ*y1)] != 0) {
				n = GFdiv( tpltzarray[x+(MAXTOEPLITZ*y1)], tpltzarray[x+(MAXTOEPLITZ*y)],symbol_type);
				tpltzarray[x+(MAXTOEPLITZ*y1)] = 0;
				for (x1 = x+1; x1 <= size; x1++) {
					tpltzarray[x1+(MAXTOEPLITZ*y1)] ^= GFmul(n, tpltzarray[x1+(MAXTOEPLITZ*y)],symbol_type);
				}
			}
		}
	}
	return(y);
}

void SolveToeplitz(int size, int symbol_type) 
{
	int x, x1, r;

	/* solve for each xi */
	for (x = size-1; x >= 0; x--) {
		r = tpltzarray[size + (MAXTOEPLITZ*x)];
		/* first substitute any previously solved xi's */
		for (x1 = size-1; x1 > x; x1--) {
			r ^= GFmul(tpltzrslt[x1], tpltzarray[x1 + (MAXTOEPLITZ*x)],symbol_type);
		}
		tpltzrslt[x] = GFdiv(r, tpltzarray[x + (MAXTOEPLITZ*x)],symbol_type);
	}
}

int ChienSearch(int size, int symbol_type) 
{
	int i, j, r, e = 0;
	int	log[MAXTOEPLITZ];

	for (i = 0; i < size; i++) {
		log[i] = gflog[symbol_type][tpltzrslt[size-1-i]];
	}
	for (j = 1; j <= ssize; j++) {
		r = 1;
		for (i = 0; i < size; i++) {
			if ((log[i] -= i+1) < 0) {
				log[i] += 255;
			}
			r ^= gfpwr[symbol_type][log[i]];
		}
		if (r == 0) {
			errloc[e] = (j < 255) ? j : 0;
			e++;
			if (e >= size) break;
		}
	}
	return(e >= size);
}

void ErrLocInit(int size,int symbol_type) 
{
	int i, j;
	int log[MAXTOEPLITZ], log1[MAXTOEPLITZ];

	for (i = 0; i < size; i++) {
		log[i] = log1[i] = errloc[i];
	}
	for (j = 0; j < size; j++) {
		for (i = 0; i < size; i++) {
			tpltzarray[i+(MAXTOEPLITZ*j)] = gfpwr[symbol_type][log1[i]];
			if ((log1[i] += log[i]) > 254) { log1[i] -= 255; }
		}
		tpltzarray[i+(MAXTOEPLITZ*j)] = syndrome[j];
	}
}

int CorrectErrs(unsigned char *code,int data_size,int check_size,int inter_size,int symbol_type) 
{
	int i, e, errcnt, v;
	int	dsize, csize, isize;

	dsize = data_size;
	csize = check_size;
	isize = inter_size;
	ssize = dsize + csize;
	m_RSCode = code;
	e = 0;
	for (v = 0; v < isize; v++) {
		CalcSyndromes(ssize, csize/2, isize, v,symbol_type);
		errcnt = NormlzToeplitz(csize/2,symbol_type);
		if (errcnt > 0) {
			if (tpltzarray[0] == 0) { return(-1); }
			SolveToeplitz(errcnt,symbol_type);
			if (!ChienSearch(errcnt,symbol_type)) { return(-1); }
			ErrLocInit(errcnt,symbol_type);
			if (NormlzToeplitz(errcnt,symbol_type) != errcnt) { return(-1); }
			SolveToeplitz(errcnt,symbol_type);
			for (i = 0; i < errcnt; i++) {
				m_RSCode[v + ((ssize-((errloc[i] == 0) ? 255 : errloc[i]))  * isize)]
						^= tpltzrslt[i];
			}
		}
		e += errcnt;
	}
	return e;
}
