/* Copyright (c) Colorado School of Mines, 1998.*/
/* All rights reserved.                          */

/* NIMAGE: $Revision: 1.35 $ ; $Date: 1997/07/29 15:42:44 $	*/

#include "par.h"
#include "xplot.h"
#include <X11/Xatom.h>
#include <X11/keysym.h>

/*********************** self documentation **********************/
char *sdoc[] = {
"									",
" NIMAGE - N IMAGE plot of a uniformly-sampled function x4=f(x1,x2,x3) 	",
"									",
" nimage n1= [optional parameters] <binaryfile				",
"									",
" X Functionality:							",
" Button 1	(over picture) Zoom with rubberband box			",
" 		(out picture) Scroll between planes			",
" Button 2	Show mouse (x1,x2,x3): x4 coordinates while pressed	",
" q or Q key	Quit							",
"									",
" ... change plane of view          					",
" 1          see planes perpendicular to 1 (first) axes       		",
" 2          see planes perpendicular to 2 (second) axes       		",
" 3          see planes perpendicular to 3 (third) axes       		",
" ... scroll between planes	       					",
" Button 1 or 								",
" arrow keys left-right-up-down 					",
"                                   					",
" ... change colormap interactively					",
" r	     install next RGB - colormap				",
" R	     install previous RGB - colormap				",
" h	     install next HSV - colormap				",
" H	     install previous HSV - colormap				",
" c or C     install user colormap (cmap=colormap_file)		        ",
" (Move mouse cursor out and back into window for r,R,h,H to take effect)",
" 									",
" Required Parameters:							",
" n1			 number of samples in 1st (fast) dimension	",
" n2			 number of samples in 2nd dimension		",
"									",
" Optional Parameters:							",
" oo1=0 (new)		 offset in samples(4 bytes) to take the first   ",
" o1=0 (new)		 offset in samples to jump to the first sample  ",
"                        in the 1st dimension                           ",
" p1=0 (new)		 number of samples to be taken in 1st direction ",
" d1=1.0		 sampling interval in 1st dimension		",
" f1=0.0		 first sample in 1st dimension			",
" o2=0 (new)		 offset in samples to jump to the first sample  ",
"                        in the 2nd dimension                           ",
" p2=0 (new)		 number of samples to be taken in 2nd direction ",
" d2=1.0		 sampling interval in 2nd dimension		",
" f2=0.0		 first sample in 2nd dimension			",
" n3=all		 number of samples in 3nd (slowest) dimension	",
" o3=0 (new)		 offset in samples to jump to the first sample  ",
"                        in the 3rd dimension                           ",
" p3=0 (new)		 number of samples to be taken in 3rd direction ",
" d3=1.0		 sampling interval in 3rd dimension		",
" f3=0.0		 first sample in 3rd dimension			",
" perc=100.0		 percentile used to determine clip		",
" clip=(perc percentile) clip used to determine bclip and wclip		",
" bperc=perc		 percentile for determining black clip value	",
" wperc=100.0-perc	 percentile for determining white clip value	",
" bclip=clip		 data values outside of [bclip,wclip] are clipped",
" wclip=-clip		 data values outside of [bclip,wclip] are clipped",
" cmap=hsv\'n\' or rgb\'m\' or cmap=colormap_file                       ",
" 				\'n\' is a number from 0 to 13		",
"				\'m\' is a number from 0 to 11		",
"				cmap=rgb0 is equal to cmap=gray		",
"				cmap=hsv1 is equal to cmap=hue		",
"				(compatibility to older versions)	",
" legend=0	      =1 display the color scale			",
" units=		unit label for legend				",
" legendfont=times_roman10    font name for title			",
" verbose=1		 =1 for info printed on stderr (0 for no info)	",
" xbox=50		 x in pixels of upper left corner of window	",
" ybox=50		 y in pixels of upper left corner of window	",
" wbox=550		 width in pixels of window			",
" hbox=700		 height in pixels of window			",
" lwidth=16		 colorscale (legend) width in pixels		",
" lheight=hbox/3	 colorscale (legend) height in pixels		",
" lx=3			 colorscale (legend) x-position in pixels	",
" ly=(hbox-lheight)/3    colorscale (legend) y-position in pixels	",
" x1beg=x1min		 value at which axis 1 begins			",
" x1end=x1max		 value at which axis 1 ends			",
" d1num=0.0		 numbered tic interval on axis 1 (0.0 for automatic)",
" f1num=x1min		 first numbered tic on axis 1 (used if d1num not 0.0)",
" n1tic=1		 number of tics per numbered tic on axis 1	",
" grid1=none		 grid lines on axis 1 - none, dot, dash, or solid",
" label1=		 label on axis 1				",
" x2beg=x2min		 value at which axis 2 begins			",
" x2end=x2max		 value at which axis 2 ends			",
" d2num=0.0		 numbered tic interval on axis 2 (0.0 for automatic)",
" f2num=x2min		 first numbered tic on axis 2 (used if d2num not 0.0)",
" n2tic=1		 number of tics per numbered tic on axis 2	",
" grid2=none		 grid lines on axis 2 - none, dot, dash, or solid",
" label2=		 label on axis 2				",
" x3beg=x3min		 value at which axis 3 begins			",
" x3end=x3max		 value at which axis 3 ends			",
" d3num=0.0		 numbered tic interval on axis 3 (0.0 for automatic)",
" f3num=x3min		 first numbered tic on axis 3 (used if d3num not 0.0)",
" n3tic=1		 number of tics per numbered tic on axis 3	",
" grid3=none		 grid lines on axis 3 - none, dot, dash, or solid",
" label3=		 label on axis 3				",
" labelfont=Erg14	 font name for axes labels			",
" title=		 title of plot					",
" titlefont=Rom22	 font name for title				",
" windowtitle=nimage	 title on window				",
" labelcolor=blue	 color for axes labels				",
" titlecolor=red	 color for title				",
" gridcolor=blue	 color for grid lines				",
" style=seismic		 normal (axis 1 horizontal, axis 2 vertical) or ",
"			 seismic (axis 1 vertical, axis 2 horizontal)	",
" blank=0		 This indicates what portion of the lower range ",
"			 to blank out (make the background color).  The ",
"			 value should range from 0 to 1.		",
" esize=4		 Tamanho em bytes de cada amostra.              ",
"			 4 para float		                    	",
"			 1 para byte            	        	",
"									",
NULL};
/*
 * AUTHOR:  Dave Hale, Colorado School of Mines, 08/09/90
 *
 * Stewart A. Levin, Mobil - Added ps print option
 *
 * Brian Zook, Southwest Research Institute, 6/27/96, added blank option
 *
 * Toralf Foerster, Baltic Sea Research Institute, 9/15/96, new colormaps
 *
 * Berend Scheffers, Delft, colorbar (legend)
 *
 * A. Vicentini, x3 coordinate when B2 pressed and colormap_file
 */
/**************** end self doc ********************************/

#define keyLEFT  65361
#define keyUP    65362
#define keyRIGHT 65363
#define keyDOWN  65364


/* functions defined and used internally */
void MostraCubo(Display *dpy, Window win, GC gc, int ind, float escala);
static void zoomBox (int x, int y, int w, int h,
	int xb, int yb, int wb, int hb,
	int nx, int ix, float x1, float x2,
	int ny, int iy, float y1, float y2,
	int *nxb, int *ixb, float *x1b, float *x2b,
	int *nyb, int *iby, float *y1b, float *y2b);
static unsigned char *newInterpBytes (int n1in, int n2in, unsigned char *bin,
	int n1out, int n2out);
void xMouseLoc(Display *dpy, Window win, XEvent event, int style, Bool show,
        int x, int y, int width, int height, int rgb,
        int ind, int ind1, int ind2, int ind3,
        float *z, int n1, int n2, int n3, float f1, float f2, float f3, 
        float d1, float d2, float d3,
	float x1begb, float x1endb, 
        float x2begb, float x2endb,
        float x3begb, float x3endb);
Colormap xCreateNEWColormap (Display *dpy, Window win,
                        char *arquivo, int verbose);
Colormap mxCreateRGBColormap (Display *dpy, Window win,
                        char *arquivo, int verbose);

unsigned long Black, Gray;

int
main (int argc,char **argv)
{
	int n1,n2,n3,ind,ind1,ind2,ind3,n1tic,n2tic,n3tic,nxtic=0,nytic=0,
		i1,i2,grid1,grid2,grid3,gridx=0,gridy=0,style,
		n1c,n2c,nx,ny,nw,i1beg,i1end,i2beg,i2end,i1c,i2c,
		nz,iz,i1step,i2step,verbose,oo1,o1,o2,o3,p1,p2,p3,
		xbox,ybox,wbox,hbox,
		xb,yb,wb,hb,rgb,
		x,y,width,height,x0=0,y0=0,inc,x1,y1,
		i,j,nxb,nyb,ixb,iyb,
		imageOutOfDate=1,winwidth=-1,winheight=-1,
		showloc=0,moveloc=0,onlyplane=0,esize=4,
		legend,lwidth,lheight,lx,ly; /* BEREND */
	unsigned long nfloats;
	float labelsize,titlesize,perc,clip,bperc,wperc,bclip,wclip,
		d1,f1,d2,f2,d3,f3,*z,*temp,zscale,zoffset,zi,escala=0.,
		x1beg,x1end,x2beg,x2end,x3beg,x3end,
		x1min,x1max,x2min,x2max,x3min,x3max,
		d1num,f1num,d2num,f2num,d3num,f3num,
                dxnum=0.,fxnum=0.,dynum=0.,fynum=0.,
		x1begb,x1endb,x2begb,x2endb,x3begb,x3endb,
                xbegb,xendb,yendb,ybegb,blank;
	unsigned char *cz=NULL,*czp=NULL,*czb=NULL,*czbp=NULL,*czbi=NULL;
	char *labelx="",*labely="",*label1="",*label2="",*label3="",
                *title="",*windowtitle="nimage",
		*units="", *legendfont="times_roman10",
		*labelfont="Erg14",*titlefont="Rom22",
		*styles="seismic",
                *grid1s="none",*grid2s="none",*grid3s="none",
		*labelcolor="blue",*titlecolor="red",
		*gridcolor="blue",*cmap="",keybuf[256];
	FILE *infp=stdin;
	Display *dpy;
	Window win;
	XEvent event;
	KeySym keysym;
	XComposeStatus keystat;
	XImage *image=NULL;
	XImage *image_legend=NULL; /* BEREND */
	unsigned char *data_legend; /* BEREND */
	GC gci;
	int scr,newcor=0;
	unsigned long black,white,pmin,pmax;
	int inc1;
	int inc2;
	int inc3;
	/* initialize getpar */
	initargs(argc,argv);
	requestdoc(1);
	
	if (!getparint("inc1",&inc1)) inc1=1;
	if (!getparint("inc2",&inc2)) inc2=1;
	if (!getparint("inc3",&inc3)) inc3=1;

	/* get parameters describing 1st dimension sampling */
	if (!getparint("n1",&n1))
		err("Must specify number of samples in 1st dimension!\n");
	d1 = 1.0;  getparfloat("d1",&d1);
	f1 = 0.0;  getparfloat("f1",&f1);
	x1min = (d1>0.0)?f1:f1+(n1-1)*d1;
	x1max = (d1<0.0)?f1:f1+(n1-1)*d1;

	/* get parameters describing 2nd dimension sampling */
	if (!getparint("n2",&n2)) {
		if (fseek(infp,0L,2)!=0)
			err("must specify n2 if in a pipe!\n");
		nfloats = eftell(infp)/sizeof(float);
		fseek(infp,0L,0);
		n2 = (int) (nfloats/n1);
                n3 = 1;
	}else{
 	     if (!getparint("n3",&n3)) {
		if (fseek(infp,0L,2)!=0)
			err("must specify n2 if in a pipe!\n");
		nfloats = ftell(infp)/sizeof(float);
		fseek(infp,0L,0);
		n3 = (int) (nfloats/(n1*n2));
	     }
	}
        warn("n1=%d n2=%d n3=%d",n1,n2,n3);

	d2 = 1.0;  getparfloat("d2",&d2);
	f2 = 0.0;  getparfloat("f2",&f2);
	x2min = (d2>0.0)?f2:f2+(n2-1)*d2;
	x2max = (d2<0.0)?f2:f2+(n2-1)*d2;
	d3 = 1.0;  getparfloat("d3",&d3);
	f3 = 0.0;  getparfloat("f3",&f3);
	x3min = (d3>0.0)?f3:f3+(n3-1)*d3;
	x3max = (d3<0.0)?f3:f3+(n3-1)*d3;

	esize = 4; getparint("esize",&esize);
        if (esize!=4 && esize!=1)
		err("invalid esize parameter");



        /* n1,n2,n3 sao originalmente os tamanhos totais
           lendo o1,o2,o3 e p1,p2,p3, os n's serao redefinidos
           para valores que serao lidos realmente
           o = quer dizer offset, amostras iniciais que serao puladas
           p = quer dizer pegas (amostras lidas do traco),
               amostras que serao lidas */
	/* read binary data to be plotted */
	oo1 = 0;      getparint("oo1",&oo1);
	o1 = 0;       getparint("o1",&o1);
	o2 = 0;       getparint("o2",&o2);
	o3 = 0;       getparint("o3",&o3);
	p1 = n1-o1;   getparint("p1",&p1);
	p2 = n2-o2;   getparint("p2",&p2);
	p3 = n3-o3;   getparint("p3",&p3);
	nz = p1*p2*p3;
        /*warn("o1=%d o2=%d o3=%d",o1,o2,o3);
        warn("p1=%d p2=%d p3=%d",p1,p2,p3);*/
	z = ealloc1float(nz);
        if (esize==1) {
	   cz = ealloc1(nz,sizeof(unsigned char));
           if (fread(cz,sizeof(unsigned char),nz,infp)!=nz)
                err("error reading input file");
           for(i=0;i<nz;i++) 
              z[i]=cz[i]; 
           free1(cz);
        }
        else {
           int o=0;
           long off;
           if(oo1!=0){ off=oo1*sizeof(float);
                       if(efseek(infp,off,0)!=0) err("erro no fseek oo1"); /* offset oo1-inicial */
           }
           if(o3!=0){ off=o3*n1*n2*sizeof(float);
                      if(efseek(infp,off,1)!=0) err("erro no fseek o3"); /* offset o3 */
           }
           for(i=0;i<p3;i++){ 
              if(o2!=0){ off=o2*n1*sizeof(float);
                         if(efseek(infp,off,1)!=0) err("erro no fseek o2"); /* offset o2 */
              }
              for(j=0;j<p2;j++){
                 if(o1!=0){ off=o1*sizeof(float);
                            if(efseek(infp,off,1)!=0) err("erro no fseek o1"); /* offset o1 */
                 }
                 if (fread(&z[o],sizeof(float),p1,infp)!=p1)
		    		err("error reading input file");
                 o=o+p1;
                 if((n1-o1-p1)!=0)
                   if(efseek(infp,(n1-o1-p1)*sizeof(float),1)!=0) err("erro no fseek p1");
              };
              if((n2-o2-p2)!=0) 
                 if(efseek(infp,(n2-o2-p2)*n1*sizeof(float),1)!=0) err("erro no fseek p2"); /* offset o2 */
           };
           n1=p1;
           n2=p2;
           n3=p3;
        };

	/* if necessary, determine clips from percentiles */
	if (getparfloat("clip",&clip)) {
		bclip = clip;
		wclip = -clip;
	}
	if ((!getparfloat("bclip",&bclip) || !getparfloat("wclip",&wclip)) &&
		!getparfloat("clip",&clip)) {
		perc = 100.0;  getparfloat("perc",&perc);
		temp = ealloc1float(nz);
		for (iz=0; iz<nz; iz++)
			temp[iz] = z[iz];
		if (!getparfloat("bclip",&bclip)) {
			bperc = perc;	getparfloat("bperc",&bperc);
			iz = (nz*bperc/100.0);
			if (iz<0) iz = 0;
			if (iz>nz-1) iz = nz-1;
			qkfind(iz,nz,temp);
			bclip = temp[iz];
		}
		if (!getparfloat("wclip",&wclip)) {
			wperc = 100.0-perc;  getparfloat("wperc",&wperc);
			iz = (nz*wperc/100.0);
			if (iz<0) iz = 0;
			if (iz>nz-1) iz = nz-1;
			qkfind(iz,nz,temp);
			wclip = temp[iz];
		}
		free1float(temp);
	}
	verbose = 1;  getparint("verbose",&verbose);
	if (verbose) warn("bclip=%g wclip=%g",bclip,wclip);

	/* get colormap specification */
	if (!(getparstring("cmap",&cmap))) {
		cmap = (char *)alloc1(5,1);
		sprintf(cmap,"%s","gray");
	}
	/* get legend specs BEREND */
	legend = 0; getparint("legend", &legend); /* BEREND */
	getparstring("units", &units); /* BEREND */
	getparstring("legendfont", &legendfont);     /* BEREND */

	blank = 0; getparfloat("blank",&blank);
        rgb=0;
        getparint("rgb",&rgb);

	/* get axes parameters */
	xbox = 50; getparint("xbox",&xbox);
	ybox = 50; getparint("ybox",&ybox);
	wbox = 550; getparint("wbox",&wbox);
	hbox = 700; getparint("hbox",&hbox);

	/* legend dimensions */
	if (!(getparint("lwidth",&lwidth)))	lwidth = 16;
	if (!(getparint("lheight",&lheight)))	lheight = hbox/3;
	if (!(getparint("lx",&lx)))	lx = 3;
	if (!(getparint("ly",&ly)))	ly = (hbox-lheight)/3;

        /*-----*/
	x1beg = x1min; getparfloat("x1beg",&x1beg);
	x1end = x1max; getparfloat("x1end",&x1end);
	d1num = 0.0; getparfloat("d1num",&d1num);
	f1num = x1min; getparfloat("f1num",&f1num);
	n1tic = 1; getparint("n1tic",&n1tic);
	getparstring("grid1",&grid1s);
	if (STREQ("dot",grid1s)) grid1 = DOT;
	else if (STREQ("dash",grid1s)) grid1 = DASH;
	else if (STREQ("solid",grid1s)) grid1 = SOLID;
	else grid1 = NONE;
	getparstring("label1",&label1);
        /*-----*/
	x2beg = x2min; getparfloat("x2beg",&x2beg);
	x2end = x2max; getparfloat("x2end",&x2end);
	d2num = 0.0; getparfloat("d2num",&d2num);
	f2num = 0.0; getparfloat("f2num",&f2num);
	n2tic = 1; getparint("n2tic",&n2tic);
	getparstring("grid2",&grid2s);
	if (STREQ("dot",grid2s)) grid2 = DOT;
	else if (STREQ("dash",grid2s)) grid2 = DASH;
	else if (STREQ("solid",grid2s)) grid2 = SOLID;
	else grid2 = NONE;
	getparstring("label2",&label2);
        /*-----*/
	x3beg = x3min; getparfloat("x3beg",&x3beg);
	x3end = x3max; getparfloat("x3end",&x3end);
	d3num = 0.0; getparfloat("d3num",&d3num);
	f3num = 0.0; getparfloat("f3num",&f3num);
	n3tic = 1; getparint("n3tic",&n3tic);
	getparstring("grid3",&grid3s);
	if (STREQ("dot",grid3s)) grid3 = DOT;
	else if (STREQ("dash",grid3s)) grid3 = DASH;
	else if (STREQ("solid",grid3s)) grid3 = SOLID;
	else grid3 = NONE;
	getparstring("label3",&label3);
        /*-----*/
	getparstring("labelfont",&labelfont);
	labelsize = 18.0; getparfloat("labelsize",&labelsize);
	getparstring("title",&title);
	getparstring("titlefont",&titlefont);
	titlesize = 24.0; getparfloat("titlesize",&titlesize);
	getparstring("style",&styles);
	if (STREQ("normal",styles)) style = NORMAL;
	else style = SEISMIC;
	style = SEISMIC;
	getparstring("titlecolor",&titlecolor);
	getparstring("labelcolor",&labelcolor);
	getparstring("gridcolor",&gridcolor);
	getparstring("windowtitle",&windowtitle);

	/* adjust x1beg and x1end to fall on sampled values */
	i1beg = NINT((x1beg-f1)/d1);
	i1beg = MAX(0,MIN(n1-1,i1beg));
	x1beg = f1+i1beg*d1;
	i1end = NINT((x1end-f1)/d1);
	i1end = MAX(0,MIN(n1-1,i1end));
	x1end = f1+i1end*d1;

	/* adjust x2beg and x2end to fall on sampled values */
	i2beg = NINT((x2beg-f2)/d2);
	i2beg = MAX(0,MIN(n2-1,i2beg));
	x2beg = f2+i2beg*d2;
	i2end = NINT((x2end-f2)/d2);
	i2end = MAX(0,MIN(n2-1,i2end));
	x2end = f2+i2end*d2;

	/* allocate space for image bytes */
	n1c = 1+abs(i1end-i1beg);
	n2c = 1+abs(i2end-i2beg);
	cz = ealloc1(n1c*n2c*n3,sizeof(unsigned char));

	/* convert data to be imaged into signed characters */
	zscale = (wclip!=bclip)?255.0/(wclip-bclip):1.0e10;
	zoffset = -bclip*zscale;
	i1step = (i1end>i1beg)?1:-1;
	i2step = (i2end>i2beg)?1:-1;
	if (style==NORMAL) {
		for (i2c=0,i2=i2beg; i2c<n2c; i2c++,i2+=i2step) {
			czp = cz+n1c*n2c-(i2c+1)*n1c;
			for (i1c=0,i1=i1beg; i1c<n1c; i1c++,i1+=i1step) {
				zi = zoffset+z[i1+i2*n1]*zscale;
				if (zi<0.0) zi = 0.0;
				if (zi>255.0) zi = 255.0;
				*czp++ = (unsigned char)zi;
			}
		}
	} else {
		czp = cz;
		for (ind3=0; ind3<n3; ind3++) {
		    for (i1c=0,i1=i1beg; i1c<n1c; i1c++,i1+=i1step) {
		    for (i2c=0,i2=i2beg; i2c<n2c; i2c++,i2+=i2step) {
				zi = zoffset+z[i1+i2*n1+ind3*n1*n2]*zscale;
				if (zi<0.0) zi = 0.0;
				if (zi>255.0) zi = 255.0;
				*czp++ = (unsigned char)zi;
			}
		    }
		}
	}
	/*free1float(z);*/
	
	/* initialize zoom box parameters */
	nxb = nx = (style==NORMAL ? n1c : n2c);
	nyb = ny = (style==NORMAL ? n2c : n1c);
        nw = n3;
        ixb = iyb = 0;
        ind=3;
        ind1 = 0;
        ind2 = 0;
        ind3 = 0;
	x1begb = x1beg;	 x1endb = x1end;
	x2begb = x2beg;	 x2endb = x2end;
	x3begb = x3beg;	 x3endb = x3end;

	/* connect to X server */
	if ((dpy=XOpenDisplay(NULL))==NULL)
		err("Cannot connect to display %s!\n",XDisplayName(NULL));
	scr = DefaultScreen(dpy);
	Black = black = BlackPixel(dpy,scr);
	white = WhitePixel(dpy,scr);
	Gray  = 16;
	
	/* create window */
	win = xNewWindow(dpy,xbox,ybox,wbox,hbox,(int) black,(int) white,windowtitle);

	/* backwards compatibility */
	if (STREQ(cmap,"gray")) {
		sprintf(cmap,"%s","rgb0");

	} else if (STREQ(cmap,"hue")) {
		/* free1(cmap); */
		cmap = (char *)alloc1(5,1);
		sprintf(cmap,"%s","hsv1");

	}  else  if ((strncmp(cmap,"hsv",3)) && (strncmp(cmap,"rgb",3))){
			if (verbose) warn ("cmap=%s using cmap=gray", cmap);
         
			/* free1(cmap); */
                      cmap = (char *)alloc1(5,1);
       			sprintf (cmap, "%s", "rgb0");
	}
          
	

	/* here are the new colormaps				*/
	if (strncmp(cmap, "rgb", 3) == 0)
		XSetWindowColormap(dpy,win,
			xCreateRGBColormap(dpy,win, cmap, verbose));
	else if (strncmp (cmap, "hsv", 3) == 0)
		XSetWindowColormap(dpy,win,
			xCreateHSVColormap(dpy,win, cmap, verbose));
	/*else {XSetWindowColormap(dpy,win,
			xCreateNEWColormap(dpy,win, cmap, verbose));
              newcor=1;
        }*/
	
	/* determine min and max pixels from standard colormap */
	pmin = xGetFirstPixel(dpy);
	pmax = xGetLastPixel(dpy);
	if(pmax==0L)pmax=255L;
	if (verbose) warn("pmin=%x,pmax=%x\n",pmin,pmax);

		
	
	/* BEREND create image */
	if (legend) {
	    data_legend = (unsigned char *) malloc(lwidth * lheight);
	    for (i=0; i<lwidth*lheight; i++)
		data_legend[i] = (unsigned char) (pmin + (pmax-pmin+1)*(i/lwidth)/lheight);
	    /*image_legend = XCreateImage(dpy, DefaultVisual(dpy,scr),
		DefaultDepth(dpy,scr), ZPixmap,
		0, data_legend, lwidth, lheight, BitmapPad(dpy), lwidth);*/
	}
		
	/* make GC for image */
	gci = XCreateGC(dpy,win,0,NULL);
	
	/* set normal event mask */
	XSelectInput(dpy,win,
		StructureNotifyMask |
		ExposureMask |
		KeyPressMask |
		PointerMotionMask |
		ButtonPressMask |
		ButtonReleaseMask |
		Button1MotionMask |
		Button2MotionMask);
	
	/* map window */
	XMapWindow(dpy,win);
					
	/* determine good size for axes box */
	xSizeAxesBox(dpy,win,
		labelfont,titlefont,style,
		&x,&y,&width,&height);
	
	/* clear the window */
	/*XClearWindow(dpy,win);*/
	
	/* note that image is out of date */
	imageOutOfDate = 1;

	/* main event loop */
	while(1) {


                if(imageOutOfDate==0)XNextEvent(dpy,&event);

		/* if window was resized */
		if (event.type==ConfigureNotify &&
                       (event.xconfigure.width!=winwidth ||
			event.xconfigure.height!=winheight)) {
			winwidth = event.xconfigure.width;
			winheight = event.xconfigure.height;
							
			/* determine good size for axes box */
			xSizeAxesBox(dpy,win,
				labelfont,titlefont,style,
				&x,&y,&width,&height);
			
			/* clear the window */
			/*XClearWindow(dpy,win);*/
			
			/* note that image is out of date */
			imageOutOfDate = 1;
                        
		/* else if window exposed */
                } else if (imageOutOfDate||event.type==Expose) {

			/* clear all expose events from queue */
			while (XCheckTypedEvent(dpy,Expose,&event));
			
			/* if necessary, make new image */
			if (imageOutOfDate) {
				if (czb!=NULL) free1(czb);
					czb = ealloc1(nxb*nyb,sizeof(signed char));
                    switch (ind) {
                    case 1:
				    	for (i=0,czbp=czb; i<nyb; i++) {
				     		czp = cz+ind1*nx+iyb+i+ixb*nx*ny;
				     		for (j=0; j<nxb; j++){
				        		*czbp++ = *czp; 
                                czp=czp+nx*ny;
                            }
				  		}
                        /*some variabels for grid*/
                        ybegb=x2begb; yendb=x2endb;
                        dxnum=d2num; fxnum=f2num;
                        nxtic=n2tic; gridx=grid2; 
                        labelx=label2;
                        xbegb=x3begb; xendb=x3endb;
                        dynum=d3num; fynum=f3num;
                        nytic=n3tic; gridy=grid3; 
                        labely=label3;
                        escala=(float)ind1/(float)(n1-1);
                        break;
	               case 2:
					   for (i=0,czbp=czb; i<nyb; i++) {
		                	czp = cz+ind2+(iyb+i)*nx+ixb*nx*ny;
				     		for (j=0; j<nxb; j++){
				        		*czbp++ = *czp; 
                                 czp=czp+nx*ny;
                            }
				   		}
                        /*some variabels for grid*/
                        ybegb=x1begb; yendb=x1endb;
                        dxnum=d1num; fxnum=f1num;
                        nxtic=n1tic; gridx=grid1; 
                        labelx=label1;
                        xbegb=x3begb; xendb=x3endb;
                        dynum=d3num; fynum=f3num;
                        nytic=n3tic; gridy=grid3; 
                        labely=label3;
                        escala=(float)ind2/(float)(n2-1);
                        break;
                  case 3:
				    	for (i=0,czbp=czb; i<nyb; i++) {
				    	    czp = cz+ind3*nx*ny+(iyb+i)*nx+ixb;
				     		for (j=0; j<nxb; j++)
				    		    *czbp++ = *czp++; 
				   		}
                        /*some variabels for grid*/
                        ybegb=x1begb; yendb=x1endb;
                        dxnum=d1num; fxnum=f1num;
                        nxtic=n1tic; gridx=grid1; 
                        labelx=label1;
                        xbegb=x2begb; xendb=x2endb;
                        dynum=d2num; fynum=f2num;
                        nytic=n2tic; gridy=grid2; 
                        labely=label2;
                        escala=(float)ind3/(float)(n3-1);
                        break;
				}
				if(czbi!=NULL) free1(czbi);
				czbi = newInterpBytes(nxb,nyb,czb,
					width,height);

				if (image!=NULL) XDestroyImage(image);
				image = xNewImage(dpy,pmin,pmax,
					width,height,blank,czbi);

				/* BEREND create image */
				if (legend) {
					if (image_legend!=NULL) XDestroyImage(image_legend);
					image_legend = xNewImage(dpy,pmin,pmax,lwidth,lheight,
                                                                 0,data_legend);
				}


				imageOutOfDate = 0;
	
			/* draw image (before axes so grid lines visible) */
			XPutImage(dpy,win,gci,image,0,0,x,y,
				image->width,image->height);


                        MostraCubo(dpy,win,gci,ind,escala);


			/* BEREND display image */
			if (legend&&(~onlyplane))
				XPutImage(dpy,win,gci,image_legend,
					0,0,lx,y+ly,lwidth,lheight);

			/* BEREND draw legend axes on top of image */
			if (legend&&(~onlyplane))
				xDrawLegendBox(dpy,win,
					lx,y+ly,lwidth,lheight,
					bclip,wclip,units,legendfont,
					labelfont,title,titlefont,
					labelcolor,titlecolor,gridcolor,
					style);
                        onlyplane=0;
			
			/* draw axes on top of image */
			xDrawAxesBox(dpy,win,
				x,y,width,height,
				ybegb,yendb,0.0,0.0,
				dxnum,fxnum,nxtic,gridx,labelx,
				xbegb,xendb,0.0,0.0,
				dynum,fynum,nytic,gridy,labely,
				labelfont,title,titlefont,
				labelcolor,titlecolor,gridcolor,
				style);


			xMouseLoc(dpy,win,event,style,showloc,
				     x,y,width,height,rgb,ind,ind1,ind2,ind3,
                                     z,n1,n2,n3,f1,f2,f3,d1,d2,d3,
				     x1begb,x1endb,x2begb,x2endb,x3begb,x3endb);
			}
                
		/* else if key down */
		} else if (event.type==KeyPress) {

			XLookupString(&(event.xkey),keybuf,0,&keysym,&keystat);
			if (keysym==XK_q || keysym==XK_Q) {
			/* This is the exit from the event loop */
				break;
			} else if (keysym==XK_1) {
                               if(n3>1){
                               ind =1;
                               printf("\nnimage: viewing plane 2-3\n");
			       /* reset box to initial values */
				x1begb = x1beg;
				x1endb = x1end;
				x2begb = x2beg;
				x2endb = x2end;
				x3begb = x3beg;
				x3endb = x3end;
				nxb = nw;
				nyb = nx;
				ixb = 0;
                                iyb = 0;
                                XClearArea(dpy,win,0,0,0,0,True);
				imageOutOfDate = 1;
                                }
			} else if (keysym==XK_2) {
                               if(n3>1){
                               ind = 2;
                               printf("\nnimage: viewing plane 1-3\n");
			       /* reset box to initial values */
				x1begb = x1beg;
				x1endb = x1end;
				x2begb = x2beg;
				x2endb = x2end;
				x3begb = x3beg;
				x3endb = x3end;
				nxb = nw;
				nyb = ny;
				ixb = 0;
                                iyb = 0;
                                XClearArea(dpy,win,0,0,0,0,True);
				imageOutOfDate = 1;
                                }
			} else if (keysym==XK_3) {
                               ind = 3;
                               printf("\nnimage: viewing plane 1-2\n");
			       /* reset box to initial values */
				x1begb = x1beg;
				x1endb = x1end;
				x2begb = x2beg;
				x2endb = x2end;
				x3begb = x3beg;
				x3endb = x3end;
				nxb = nx;
				nyb = ny;
				ixb = 0;
                iyb = 0;
                XClearArea(dpy,win,0,0,0,0,True);
				imageOutOfDate = 1;
                }else if(keysym==keyRIGHT) {
                                switch (ind){
                                case 2:
                                  if(ind2+inc2<n2-1){
                                    ind2+=inc2;
                                    imageOutOfDate = 1;
                                    onlyplane = 1;
                                  };
                                  break;
                                }
                } else if(keysym==keyLEFT) {
                               switch (ind){
                                case 2:
                                  if(ind2-inc2>0){
                                    ind2-=inc2;
                                    imageOutOfDate = 1;
                                    onlyplane = 1;
                                  };
                                  break;
                                }
                } else if(keysym==keyDOWN) {
			                    switch (ind){
                                case 1:
                                  if(ind1+inc1<n1-1){ 
                                    ind1+=inc1;
				  					imageOutOfDate = 1;
				    				onlyplane = 1;
                                  };
                                  break;
                                case 2:
                                  break;
                                case 3:
                                  if(ind3-inc3>0){ 
                                    ind3-=inc3;
								    imageOutOfDate = 1;
								    onlyplane = 1;
                                  };
                                  break;
                                }
                
			} else if (keysym==keyUP) {
				
                                switch (ind){
                                case 1:
                                  if(ind1-inc1>0){
                                    ind1-=inc1;
                                    imageOutOfDate = 1;
                                    onlyplane = 1;
                                  };
                                  break;
                                case 2:
                                  break;
                                case 3:
                                  if(ind3+inc3<n3-1){ 
                                    ind3+=inc3;
				    				imageOutOfDate = 1;
				  					 onlyplane = 1;
                                  };
                                  break;
                                }
                
			} else if (keysym==XK_r) {
				XSetWindowColormap(dpy,win,
					xCreateRGBColormap(dpy,win,"rgb_up",
					verbose));
                                XClearArea(dpy,win,0,0,0,0,True);
				imageOutOfDate = 1;
			} else if (keysym==XK_R) {
				XSetWindowColormap(dpy,win,
					xCreateRGBColormap(dpy,win,"rgb_down",
					verbose));
                                XClearArea(dpy,win,0,0,0,0,True);
				imageOutOfDate = 1;
			} else if (keysym==XK_h) {
				XSetWindowColormap(dpy,win,
					xCreateHSVColormap(dpy,win,"hsv_up",
					verbose));
                                XClearArea(dpy,win,0,0,0,0,True);
				imageOutOfDate = 1;
			} else if (keysym==XK_H) {
				XSetWindowColormap(dpy,win,
					xCreateHSVColormap(dpy,win,"hsv_down",
					verbose));			
                                XClearArea(dpy,win,0,0,0,0,True);
				imageOutOfDate = 1;
			} else if (((keysym==XK_c)||(keysym==XK_C))&&(newcor)){
				XSetWindowColormap(dpy,win,
					xCreateNEWColormap(dpy,win,cmap,
					verbose));			
                                XClearArea(dpy,win,0,0,0,0,True);
				imageOutOfDate = 1;
			} else {
                           /*printf("Teclou %c = %d\n",keysym,keysym);*/
				continue;
			}


		/* else if button down (1 == zoom, 2 == mouse tracking */
		} else if (event.type==ButtonPress) {
			/* if 1st button: zoom */
			if (event.xbutton.button==Button1) {

				/* track pointer and get new box */
				xRubberBox(dpy,win,event,&xb,&yb,&wb,&hb);
			
				/* if new box has tiny width or height */
				if (wb<4 || hb<4) {
				
					/* reset box to initial values */
                                        switch (ind) {
                                        case 1:
					  xbegb = x3begb = x3beg;
				  	  xendb = x3endb = x3end;
					  ybegb = x2begb = x2beg;
					  yendb = x2endb = x2end;
					  nxb = nw;
					  nyb = nx;
                                          break;
                                        case 2:
					  xbegb = x3begb = x3beg;
				  	  xendb = x3endb = x3end;
					  ybegb = x1begb = x1beg;
					  yendb = x1endb = x1end;
					  nxb = nw;
					  nyb = ny;
                                          break;
                                        case 3:
					  ybegb = x1begb = x1beg;
				  	  yendb = x1endb = x1end;
					  xbegb = x2begb = x2beg;
					  xendb = x2endb = x2end;
					  nxb = nx;
					  nyb = ny;
                                          break;
                                        }
					ixb = 0;
                                        iyb = 0;
			
				/* else, if new box has non-zero width */
				/* and height */
				} else {
			
					/* calculate new box parameters */
					if (style==NORMAL) {
					    zoomBox(x,y,width,height,
						    xb,yb,wb,hb,
						    nxb,ixb,xbegb,xendb,
						    nyb,iyb,ybegb,yendb,
						    &nxb,&ixb,&xbegb,&xendb,
						    &nyb,&iyb,&ybegb,&yendb);
					} else {
					    zoomBox(x,y,width,height,
						    xb,yb,wb,hb,
						    nxb,ixb,xbegb,xendb,
						    nyb,iyb,ybegb,yendb,
						    &nxb,&ixb,&xbegb,&xendb,
						    &nyb,&iyb,&ybegb,&yendb);
					}

                                        switch (ind) {
                                        case 1:
					  x3begb = xbegb;
				  	  x3endb = xendb;
					  x2begb = ybegb;
					  x2endb = yendb;
                                          break;
                                        case 2:
					  x3begb = xbegb;
				  	  x3endb = xendb;
					  x1begb = ybegb;
					  x1endb = yendb;
                                          break;
                                        case 3:
					  x1begb = ybegb;
				  	  x1endb = yendb;
					  x2begb = xbegb;
					  x2endb = xendb;
                                          break;
                                        }
				}
			
				/* clear area and force an expose event */
				XClearArea(dpy,win,0,0,0,0,True);
			
				/* note that image is out of date */
				imageOutOfDate = 1;
		
			/* else if 2nd button down: display mouse coords */
			} else if (event.xbutton.button==Button2) {

				showloc = 1;
				xMouseLoc(dpy,win,event,style,showloc,
				     x,y,width,height,rgb,ind,ind1,ind2,ind3,
                                     z,n1,n2,n3,f1,f2,f3,d1,d2,d3,
				     x1begb,x1endb,x2begb,x2endb,x3begb,x3endb);

			} else if (event.xbutton.button==Button3) {

			       moveloc = 1;
                               x0=event.xmotion.x;
                               y0=event.xmotion.y;

                        } else {
				continue;
			}

		/* else if pointer has moved */
		} else if (event.type==MotionNotify) {
			
			/* if button2 down, show mouse location */
                         if (showloc) {
				xMouseLoc(dpy,win,event,style,showloc,
				     x,y,width,height,rgb,ind,ind1,ind2,ind3,
                                     z,n1,n2,n3,f1,f2,f3,d1,d2,d3,
				     x1begb,x1endb,x2begb,x2endb,x3begb,x3endb);
                         } else {

                           if (moveloc) {
                              x1=event.xmotion.x;
                              y1=event.xmotion.y;
                              inc = (abs(y1-y0)>10 ? abs(y1-y0): 1);
                              inc = (abs(x1-x0)>inc ? abs(x1-x0): inc);
                              switch (ind){
                              case 1:
                                    if(ind1>0&&y1<y0){
                                      ind1-=inc;
                                      if(ind1<0)ind1=0;
                                      imageOutOfDate = 1;
                                      onlyplane = 1;
                                    }else if(ind1<n1-1&&y1>y0){ 
                                      ind1+=inc;
                                      if(ind1>n1-1)ind1=n1-1;
				      imageOutOfDate = 1;
  				      onlyplane = 1;
                                    };
                                    break;
                              case 2:
                                    if(ind2>0&&x1<x0){
                                      ind2-=inc;
                                      if(ind2<0)ind2=0;
                                      imageOutOfDate = 1;
                                      onlyplane = 1;
                                    }else if(ind2<n2-1&&x1>x0){
                                      ind2+=inc;
                                      if(ind2>n2-1)ind2=n2-1;
                                      imageOutOfDate = 1;
                                      onlyplane = 1;
                                    };
                                    break;
                              case 3:
                                    if(ind3<n3-1&&(y1<y0||x1>x0)){ 
                                      ind3+=inc;
                                      if(ind3>n3-1)ind3=n3-1;
				      imageOutOfDate = 1;
     				      onlyplane = 1;
                                    }else if(ind3>0&&(y1>y0||x1<x0)){ 
                                      ind3-=inc;
                                      if(ind3<0)ind3=0;
				      imageOutOfDate = 1;
				      onlyplane = 1;
                                    };
                                    break;
                              };
                            x0=x1;
                            y0=y1;
                            };

                         };

		/* else if button2 released, stop tracking */
		} else if (event.type==ButtonRelease &&
			   event.xbutton.button==Button2) {
			showloc = 0;
		} else if (event.type==ButtonRelease &&
			   event.xbutton.button==Button3) {
			moveloc = 0;
		}

	} /* end of event loop */

        free1float(z);

	/* close connection to X server */
	XCloseDisplay(dpy);

	return EXIT_SUCCESS;
}

/* update parameters associated with zoom box */
static void zoomBox (int x, int y, int w, int h, 
	int xb, int yb, int wb, int hb,
	int nx, int ix, float x1, float x2,
	int ny, int iy, float y1, float y2,
	int *nxb, int *ixb, float *x1b, float *x2b,
	int *nyb, int *iyb, float *y1b, float *y2b)
{
	/* if width and/or height of box are zero, just copy values */
	if (wb==0 || hb==0) {
		*nxb = nx; *ixb = ix; *x1b = x1; *x2b = x2;
		*nyb = ny; *iyb = iy; *y1b = y1; *y2b = y2;
		return;		
	} 
	
	/* clip box */
	if (xb<x) {
		wb -= x-xb;
		xb = x;
	}
	if (yb<y) {
		hb -= y-yb;
		yb = y;
	}
	if (xb+wb>x+w) wb = x-xb+w;
	if (yb+hb>y+h) hb = y-yb+h;
	
	/* determine number of samples in rubber box (at least 2) */
	*nxb = MAX(nx*wb/w,2);
	*nyb = MAX(ny*hb/h,2);
	
	/* determine indices of first samples in box */
	*ixb = ix+(xb-x)*(nx-1)/w;
	*ixb = MIN(*ixb,ix+nx-*nxb);
	*iyb = iy+(yb-y)*(ny-1)/h;
	*iyb = MIN(*iyb,iy+ny-*nyb);
	
	
	/* determine box limits to nearest samples */
	*x1b = x1+(*ixb-ix)*(x2-x1)/(nx-1);
	*x2b = x1+(*ixb+*nxb-1-ix)*(x2-x1)/(nx-1);
	*y1b = y1+(*iyb-iy)*(y2-y1)/(ny-1);
	*y2b = y1+(*iyb+*nyb-1-iy)*(y2-y1)/(ny-1);
}

/* return pointer to new interpolated array of bytes */
static unsigned char *newInterpBytes (int n1in, int n2in, unsigned char *bin,
	int n1out, int n2out)
{
	unsigned char *bout;
	float d1in,d2in,d1out,d2out,f1in,f2in,f1out,f2out;
	
	f1in = f2in = f1out = f2out = 0.0;
	d1in = d2in = 1.0;
	d1out = d1in*(float)(n1in-1)/(float)(n1out-1);
	d2out = d2in*(float)(n2in-1)/(float)(n2out-1);
	bout = ealloc1(n1out*n2out,sizeof(unsigned char));
	intl2b(n1in,d1in,f1in,n2in,d2in,f2in,bin,
		n1out,d1out,f1out,n2out,d2out,f2out,bout);
	return bout;
}
	

void xMouseLoc(Display *dpy, Window win, XEvent event, int style, Bool show,
        int x, int y, int width, int height, int rgb,
        int ind, int ind1, int ind2, int ind3,
        float *z, int n1, int n2, int n3, float f1, float f2, float f3, 
        float d1, float d2, float d3,
	float x1begb, float x1endb, 
        float x2begb, float x2endb,
        float x3begb, float x3endb)
{
	static XFontStruct *fs=NULL;
	static XCharStruct overall;
	static GC gc;
	int dummy,xoffset,yoffset,i1=0,i2=0,i3=0,r,g,b,c,
            i11,i12,i13,i14,
            i21,i22,i23,i24,
            i31,i32,i33,i34;
	float x1=0,x2=0,x3=0,x4,
              z1,z2,z3,z4,za,zb;
	char string[100],splane[100];

        xoffset=5; yoffset=5;

	/* if first time, get font attributes and make gc */
	if (fs==NULL) {
		fs = XLoadQueryFont(dpy,"fixed");
		gc = XCreateGC(dpy,win,0,NULL);

		/* make sure foreground/background are black/white */
		XSetForeground(dpy,gc,BlackPixel(dpy,DefaultScreen(dpy)));
		XSetBackground(dpy,gc,WhitePixel(dpy,DefaultScreen(dpy)));

		XSetFont(dpy,gc,fs->fid);
		overall.width = 1;
		overall.ascent = 1;
		overall.descent = 1;
	}

	/* erase previous string */
	XClearArea(dpy,win,xoffset,yoffset,
		overall.width,overall.ascent+overall.descent,False);

        switch (ind){
        case 1:
          sprintf(splane," plan1 = %d/%d ",ind1+1,n1);
          break;
        case 2:
          sprintf(splane," plan2 = %d/%d ",ind2+1,n2);
          break;
        case 3:
          sprintf(splane," plan3 = %d/%d ",ind3+1,n3);
          break;
        }

        if (!show) {

	XTextExtents(fs,splane,(int)strlen(splane),&dummy,&dummy,&dummy,&overall);
	XDrawString(dpy,win,gc,xoffset,yoffset+overall.ascent,
		splane,(int) strlen(splane));

	/* if not showing the position , then return */
	return;
        }

	/* convert mouse location to (x1,x2) coordinates */
        /* obtem indices da matriz z(), referentes as coordenadas (x1,x2) */
	if (style==NORMAL) {
		x1 = x1begb+(x1endb-x1begb)*(event.xmotion.x-x)/width;
		x2 = x2endb+(x2begb-x2endb)*(event.xmotion.y-y)/height;
                i1 = (int) ((x1-f1)/d1);
                i2 = (int) ((x2-f2)/d2);                                      
	} else {
              switch (ind) {
              case 1:
		x2 = x2begb+(x2endb-x2begb)*(event.xmotion.y-y)/height;
		x3 = x3begb+(x3endb-x3begb)*(event.xmotion.x-x)/width;
                i1 = ind1;
                i2 = (int) ((x2-f2)/d2);
                i3 = (int) ((x3-f3)/d3);
		x1 = f1+d1*i1;
                i11=i12=i13=i14=i1;
                i21=i23=i2;
                i22=i24=(i2<n2-1)?i2+1:i2;
                i31=i32=i3;
                i33=i34=(i3<n3-1)?i3+1:i3;
                za = ((x3-f3)/d3) - i3;
                zb = ((x2-f2)/d2) - i2;
                break;
              case 2:
		x1 = x1begb+(x1endb-x1begb)*(event.xmotion.y-y)/height;
		x3 = x3begb+(x3endb-x3begb)*(event.xmotion.x-x)/width;
                i1 = (int) ((x1-f1)/d1);
                i2 = ind2;
                i3 = (int) ((x3-f3)/d3);
                i11=i13=i1;
                i12=i14=(i1<n1-1)?i1+1:i1;
                i21=i22=i23=i24=i2;
                i31=i32=i3;
                i33=i34=(i3<n3-1)?i3+1:i3;
		x2 = f2+d2*i2;
                za = ((x3-f3)/d3) - i3;
                zb = ((x1-f1)/d1) - i1;
                break;
              case 3:
		x1 = x1begb+(x1endb-x1begb)*(event.xmotion.y-y)/height;
		x2 = x2begb+(x2endb-x2begb)*(event.xmotion.x-x)/width;
                i1 = (int) ((x1-f1)/d1);
                i2 = (int) ((x2-f2)/d2);                                      
                i3 = ind3;
                i11=i13=i1;
                i12=i14=(i1<n1-1)?i1+1:i1;
                i21=i22=i2;
                i23=i24=(i2<n2-1)?i2+1:i2;
                i31=i32=i33=i34=i3;
		x3 = f3+d3*i3;
                za = ((x2-f2)/d2) - i2;
                zb = ((x1-f1)/d1) - i1;
                break;
              }
	}
/*
        x4 = (x1<x1begb||x1>x1endb||x2<x2begb||x2>x2endb||x3<x3begb||x3>x3endb)? 
             0: z[i1+i2*n1+i3*n1*n2];
*/
        if (x1<x1begb||x1>x1endb||x2<x2begb||x2>x2endb||x3<x3begb||x3>x3endb) {
           x4 = 0;
        }else{
           /* interpola */
           z1 = z[i11+i21*n1+i31*n1*n2];
           z2 = z[i12+i22*n1+i32*n1*n2];
           z3 = z[i13+i23*n1+i33*n1*n2];
           z4 = z[i14+i24*n1+i34*n1*n2];
           x4 = z1+za*(z3-z1)+zb*(z2-z1)+za*zb*(z4+z1-z2-z3);
        }

        /* verifica valores rgb*/
        if(rgb){
          c=(int)x4;
          b=c/65536;
          g=(c-b*65536)/256;
          r=c-b*65536-g*256;
	  sprintf(string,"(%0.6g, %0.6g, %0.6g): %0.6g RGB=%d %d %d",x1,x2,x3,x4,r,g,b);
        } else{
	  /* draw string indicating mouse location */
	  sprintf(string,"(%0.6g, %0.6g, %0.6g): %0.6g ",x1,x2,x3,x4);
        }
        strcat(splane,string);

	XTextExtents(fs,splane,(int)strlen(splane),&dummy,&dummy,&dummy,&overall);
	XDrawString(dpy,win,gc,xoffset,yoffset+overall.ascent,
		splane,(int) strlen(splane));
}


Colormap mxCreateRGBColormap (Display *dpy, Window win,
                        char *str_cmap, int verbose)
{
        Screen *scr=XDefaultScreenOfDisplay(dpy);
        /* Window root=XRootWindowOfScreen(scr);  --unused? */
        Colormap cmap,wcmap;
        XColor color;
        XWindowAttributes wa;
        int i,ncells;
        unsigned long npixels;
        unsigned long bpixel,epixel,pixel[4096];

# define RGB_BLACK      {0x00, 0x00, 0x00}
# define RGB_WHITE      {0xff, 0xff, 0xff}
# define RGB_GRAY       {0x80, 0x80, 0x80}

# define RGB_ORANGE     {0xff, 0x80, 0x00}

# define RGB_RED        {0xe0, 0x00, 0x50}
# define RGB_BLUE       {0x00, 0x40, 0xc0}
# define RGB_GREEN      {0x06, 0x5b, 0x3f}
# define RGB_BROWN      {0x72, 0x5b, 0x3f}
# define RGB_REDBROWN   {0xa0, 0x40, 0x00}

# define RGB_GRAY2      {0xb0, 0xb0, 0xb0}

# define RGB_LGRAY      {0xf0, 0xf0, 0xf0}
# define RGB_LBLUE      {0x55, 0x9c, 0xe0}
# define RGB_YELLOW     {0xd0, 0xb0, 0x20}

        float c_rgb [][3][3]  = {
        { RGB_BLACK,    RGB_GRAY,   RGB_WHITE  },
        { RGB_WHITE,    RGB_BLUE,   RGB_BLUE  },
        { RGB_RED,      RGB_LGRAY,  RGB_GREEN },
        { RGB_BROWN,    RGB_LGRAY,  RGB_BLUE  },
        { RGB_GREEN,    RGB_LGRAY,  RGB_GREEN },
        { RGB_YELLOW,   RGB_LGRAY,  RGB_BLUE  },
        { RGB_REDBROWN, RGB_LGRAY,  RGB_GREEN },
        { RGB_ORANGE,   RGB_LGRAY,  RGB_BLUE  },
        { RGB_BLUE,     RGB_LGRAY,  RGB_GREEN },
        { RGB_BLACK,    RGB_GRAY2,  RGB_GREEN },
        { RGB_RED,      RGB_BLUE,   RGB_BLUE  },
        { RGB_BROWN,    RGB_YELLOW, RGB_BLUE  }
        };

        static int      c_nr = -1;
        unsigned long   max_cmap, ih;

        /* determine beginning and ending pixels in contiguous range    */
        bpixel = xGetFirstPixel(dpy);
        epixel = xGetLastPixel(dpy);
        if (epixel<=bpixel) return None;

        /* determine window's current colormap */
        XGetWindowAttributes(dpy,win,&wa);
        wcmap = wa.colormap;

        /* create new colormap and allocate all cells read/write */
        cmap = XCreateColormap(dpy,win,DefaultVisualOfScreen(scr),AllocNone);
        ncells = CellsOfScreen(scr);
        XAllocColorCells(dpy,cmap,True,NULL,0,pixel,ncells);

        /* copy color cells from window's colormap to new colormap */
        for (i=0; i<ncells; ++i) {
                if (i<bpixel || i>epixel) {
                        color.pixel = i;
                        XQueryColor(dpy,wcmap,&color);
                        XFreeColors(dpy,cmap,&pixel[i],1,0);
                        XAllocColor(dpy,cmap,&color);
                }
        }

        /* build scale in contiguous cells in new colormap */
        npixels = epixel-bpixel+1;

        max_cmap = sizeof (c_rgb) / sizeof (float[3][3]);
        /* We got the specific number of the cmap from the string       */
        if (STREQ (str_cmap, "rgb_up"))
                c_nr++;
        else if (STREQ (str_cmap, "rgb_down"))
                c_nr--;
        else    {
                if (strlen (str_cmap) > 3)      {
                        str_cmap[0] = str_cmap[1] = str_cmap[2] = ' ';
                        c_nr = atoi (str_cmap);
                        if (c_nr < 0 || c_nr >= max_cmap)       {
                                warn ("\"cmap=rgb%i\" not installed !", c_nr);
                                c_nr = 0;
                                warn (" using : \"cmap=rgb%i\"", c_nr);
                        }
                }
        }

        /* cycle through the cmaps                                      */
        while (c_nr < 0)
                c_nr += max_cmap;

        while (c_nr >= max_cmap)
                c_nr -= max_cmap;

        if (verbose == 1)
                warn (" using : \"cmap=rgb%i\"", c_nr);

        /* Build the 1st ramp                                           */
        for (ih = 0; ih < npixels; ++ih) {
                color.pixel = bpixel + ih;
                color.red   = c_rgb[c_nr][0][0] +
                        (c_rgb[c_nr][1][0] - c_rgb[c_nr][0][0]) * ((float) ih)/(
(float) npixels);
                color.green = c_rgb[c_nr][0][1] +
                        (c_rgb[c_nr][1][1] - c_rgb[c_nr][0][1]) * ((float) ih)/(
(float) npixels);
                color.blue  = c_rgb[c_nr][0][2] +
                        (c_rgb[c_nr][1][2] - c_rgb[c_nr][0][2]) * ((float) ih)/(
(float) npixels);

                color.red   *= 257.0;
                color.green *= 257.0;
                color.blue  *= 257.0;

                color.flags = DoRed|DoGreen|DoBlue;
                XStoreColor(dpy,cmap,&color);
        }

        /* return colormap */
        return cmap;
}



Colormap xCreateNEWColormap (Display *dpy, Window win,
                        char *arquivo, int verbose)
{
        Screen *scr=XDefaultScreenOfDisplay(dpy);
        Colormap cmap,wcmap;
        XColor color;
        XWindowAttributes wa;
        int i,ncells;
        unsigned long npixels;
        unsigned long bpixel,epixel,pixel[4096];

        float c_rgb [64][3];
        unsigned long  ncolors, ip;
        int ic1,ic2,ica;
        float ic,R,G,B,FATOR;

        /* Leitura do arquivo de cores */
        FILE *pf;
        pf = fopen(arquivo,"r");
        ncolors=0;
        FATOR=255.;
        while(ncolors<64){
          fscanf(pf,"%f%f%f",&R,&G,&B);
          c_rgb[ncolors][0]=R*FATOR;
          c_rgb[ncolors][1]=G*FATOR;
          c_rgb[ncolors][2]=B*FATOR;
          ncolors++;
        }
        fclose(pf);
        

        /* determine beginning and ending pixels in contiguous range    */
        bpixel = xGetFirstPixel(dpy);
        epixel = xGetLastPixel(dpy);
        if (epixel<=bpixel) return None;

        /* determine window's current colormap */
        XGetWindowAttributes(dpy,win,&wa);
        wcmap = wa.colormap;

        /* create new colormap and allocate all cells read/write */
        cmap = XCreateColormap(dpy,win,DefaultVisualOfScreen(scr),AllocNone);
        ncells = CellsOfScreen(scr);
        XAllocColorCells(dpy,cmap,True,NULL,0,pixel,ncells);

        /* copy color cells from window's colormap to new colormap */
        for (i=0; i<ncells; ++i) {
                if (i<bpixel || i>epixel) {
                        color.pixel = i;
                        XQueryColor(dpy,wcmap,&color);
                        XFreeColors(dpy,cmap,&pixel[i],1,0);
                        XAllocColor(dpy,cmap,&color);
                }
        }

        /* build scale in contiguous cells in new colormap */
        npixels = epixel-bpixel+1;
        /*ncolors = sizeof (c_rgb) / sizeof (float[3]);*/

        if (verbose == 1)
                warn (" using : \"cmap=%s\"", arquivo);

        /* interpolacao de ncolors cores em npixels pixels*/
        FATOR = (float)(ncolors-1)/(float)(npixels-1);
        ica=-1;
        for (ip = 0; ip < npixels; ++ip) {
                ic=FATOR*(float)(ip);
                ic1=(int)ic;
                if(ic1>=ncolors)ic1=ncolors-1;
                ic2=ic1+1;
                if(ic2>=ncolors)ic2=ncolors-1;
                if(ica==ic1)ic=ic-ic1;
                else ic=0.;
                /*
                printf("ip=%d ic1=%d ic2=%d ic=%f ica=%d\n",ip,ic1,ic2,ic,ica);
                */
                ica=ic1;

                color.pixel = bpixel++;
                color.red   = c_rgb[ic1][0] +
                        (c_rgb[ic2][0] - c_rgb[ic1][0]) * ic ;
                color.green = c_rgb[ic1][1] +
                        (c_rgb[ic2][1] - c_rgb[ic1][1]) * ic ;
                color.blue  = c_rgb[ic1][2] +
                        (c_rgb[ic2][2] - c_rgb[ic1][2]) * ic ;

                color.red   *= 257.0;
                color.green *= 257.0;
                color.blue  *= 257.0;

                color.flags = DoRed|DoGreen|DoBlue;
                XStoreColor(dpy,cmap,&color);
        }

        /* return colormap */
        return cmap;
}

void MostraCubo(Display *dpy, Window win, GC gc, int ind, float s)
{
  int x1=0,y1=0;
  int i,j,x0=10,y0=90,x2,y2;
  float px[4],py[4],pz[4];
  float teta=3.141593/7.,escx=3,escy=3,escz=2.5;
  float ct=cos(teta),st=sin(teta);
  unsigned int line_back=1,line_width=2;

  XClearArea(dpy,win,x0,y0-15*3,20*3,2*15*3,False);

  XSetForeground (dpy,gc,Gray);
  XSetLineAttributes(dpy,gc,line_back,LineSolid,CapNotLast,JoinMiter);

  /* plota um quadrado */
  px[0]= 0.; py[0]= 0.; pz[0]= 0.;
  px[1]= 0.; py[1]=10.; pz[1]= 0.;
  px[2]=10.; py[2]=10.; pz[2]= 0.;
  px[3]=10.; py[3]= 0.; pz[3]= 0.;
  for(i=1,j=0;i<5;i++){
     if(i==1){x1=x0+escx*px[0]+escz*pz[0]*ct;
             y1=y0+escy*py[0]-escz*pz[0]*st;}
     if(i<4) {j++;} else j=0;
     x2=x0+escx*px[j]+escz*pz[j]*ct;
     y2=y0+escy*py[j]-escz*pz[j]*st;
     XDrawLine (dpy,win,gc,x1,y1,x2,y2);
     x1=x2;
     y1=y2;
  };
  /* plota um quadrado */
  px[0]= 0.; py[0]= 0.; pz[0]= 0.;
  px[1]= 0.; py[1]= 0.; pz[1]=10.;
  px[2]=10.; py[2]= 0.; pz[2]=10.;
  px[3]=10.; py[3]= 0.; pz[3]= 0.;
  for(i=1,j=0;i<5;i++){
     if(i==1){x1=x0+escx*px[0]+escz*pz[0]*ct;
             y1=y0+escy*py[0]-escz*pz[0]*st;}
     if(i<4) {j++;} else j=0;
     x2=x0+escx*px[j]+escz*pz[j]*ct;
     y2=y0+escy*py[j]-escz*pz[j]*st;
     XDrawLine (dpy,win,gc,x1,y1,x2,y2);
     x1=x2;
     y1=y2;
  };
  /* plota um quadrado */
  px[0]=10.; py[0]= 0.; pz[0]= 0.;
  px[1]=10.; py[1]=10.; pz[1]= 0.;
  px[2]=10.; py[2]=10.; pz[2]=10.;
  px[3]=10.; py[3]= 0.; pz[3]=10.;
  for(i=1,j=0;i<5;i++){
     if(i==1){x1=x0+escx*px[0]+escz*pz[0]*ct;
             y1=y0+escy*py[0]-escz*pz[0]*st;}
     if(i<4) {j++;} else j=0;
     x2=x0+escx*px[j]+escz*pz[j]*ct;
     y2=y0+escy*py[j]-escz*pz[j]*st;
     XDrawLine (dpy,win,gc,x1,y1,x2,y2);
     x1=x2;
     y1=y2;
  };

  XSetForeground (dpy,gc,Black);
  XSetLineAttributes(dpy,gc,line_width,LineSolid,CapNotLast,JoinMiter);
  /* plota um quadrado */
  switch (ind) {
  case 1:
    px[0]= 0.; py[0]=10.*s; pz[0]= 0.;
    px[1]=10.; py[1]=10.*s; pz[1]= 0.;
    px[2]=10.; py[2]=10.*s; pz[2]=10.;
    px[3]= 0.; py[3]=10.*s; pz[3]=10.;
    break;
  case 2:
    px[0]=10.*s; py[0]= 0.; pz[0]= 0.;
    px[1]=10.*s; py[1]=10.; pz[1]= 0.;
    px[2]=10.*s; py[2]=10.; pz[2]=10.;
    px[3]=10.*s; py[3]= 0.; pz[3]=10.;
    break;
  case 3:
    px[0]= 0.; py[0]= 0.; pz[0]=10.*s;
    px[1]= 0.; py[1]=10.; pz[1]=10.*s;
    px[2]=10.; py[2]=10.; pz[2]=10.*s;
    px[3]=10.; py[3]= 0.; pz[3]=10.*s;
    break;
  }
  for(i=1,j=0;i<5;i++){
     if(i==1){x1=x0+escx*px[0]+escz*pz[0]*ct;
             y1=y0+escy*py[0]-escz*pz[0]*st;}
     if(i<4) {j++;} else j=0;
     x2=x0+escx*px[j]+escz*pz[j]*ct;
     y2=y0+escy*py[j]-escz*pz[j]*st;
     XDrawLine (dpy,win,gc,x1,y1,x2,y2);
     x1=x2;
     y1=y2;
  };
}
