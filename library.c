#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Figure make_figure();
Figure * start_figure(double width, double height);
void set_thickness_resolution(Figure *fig, double thickness,double resolution);
void set_color(Figure * fig, Color c);

void draw_fx(Figure * fig, double f(double x),double start_x, double end_x,double step_size);
void add_end_Point2D(Point2D *root,double x,double sin_x,int stats);

void create_link_between_two_point(Point2D *ll_p1,Point2D *ll_p2);
void draw_polyline(Figure *fig,Point2D * poly_line, int n);

void draw_circle(Figure *fig,double step_size,double r);
double circle_cal_func(double r,double x);

void draw_ellipse(Figure *fig,Point2D * centre, Point2D * width_height);
double ellipse_cal_func(Point2D * width_height,int x);

void draw_polygon(Figure *fig,Point2D *poly_line,int size);

void resize_figure(Figure *fig,Point2D *start_roi, Point2D *end_roi);
void append_figures(Figure * fig1, Figure * fig2);
void scale_figure(Figure *fig,double scale_x, double scale_y);

void draw_binary_tree(Figure *fig,Tree *root,double center_x,double center_y);
Point2D* draw_node(Figure *fig,Tree *branch,Point2D *point,double center_x,double center_y,int radius,double x,int node_number);
void add_element_tree(Tree *root,int side_no,int number);
int calculate_node_numbers(Tree *branch);
void add_end_text(Text *text,int number,double center_x, double center_y);

void make_same_figure(Figure *fig1,Figure *fig2);
Figure* move_figure(Figure *fig,int x,int y);
void export_eps(Figure * fig, char * file_name);

/*============================================================*/
Figure make_figure(){

	Figure *fig;
	Color c;
	c.red = 1;
	c.blue = 0;
	c.green = 0;

	fig = start_figure(1000,1000);
	set_thickness_resolution(fig,0.5,20);
	set_color(fig,c);

	return *fig;
}
/*============================================================*/
Figure * start_figure(double width, double height){

	Figure *figure = (Figure*)malloc(sizeof(Figure));

	figure->uprix = width/2.0;
	figure->upriy =height/2.0;
	figure->lwlx =-width/2.0; 
	figure->lwly =-height/2.0;
	figure->ftxt=NULL; 

	return figure; 
}
/*============================================================*/
void set_thickness_resolution(Figure *fig, double thickness,double resolution){
		fig->resolution=resolution;
		fig->thickness=thickness;
}
/*============================================================*/
void set_color(Figure * fig, Color c){
	fig->fcolor.green= c.green;
	fig->fcolor.red  = c.red;
	fig->fcolor.blue = c.blue;
}
/*============================================================*/
void draw_fx(Figure * fig, double f(double x),
	double start_x, double end_x,double step_size){
	
	Point2D *iter;
	Point2D *root = (Point2D*)calloc(step_size,sizeof(Point2D));
	root->next_p = NULL;

	iter = root;

	for(double i= start_x; i<=end_x; i += (end_x-start_x) / step_size){
		iter->x = i;
		iter->y = f(i);
		iter->jumper = 0;
		iter->next_p = (Point2D*)malloc(sizeof(Point2D));
		iter->next_p->next_p = NULL;	
		iter = iter->next_p;
	}
	iter->x = end_x;
	iter->y = f(end_x);
	iter->jumper = 0;	

	fig->fPoint2D = root;
	iter = root;
}
/*=========================================================================*/
void draw_polyline(Figure *fig,Point2D * poly_line, int n){

	int count = 1;
	Point2D * root = (Point2D*)malloc(sizeof(Point2D));

	root->x = poly_line[0].x;
	root->y = poly_line[0].y;
	root->jumper = 0;

	while(count<n){
		create_link_between_two_point(root,&poly_line[count]);
		count++;
	}
	fig->fPoint2D = root;
}
/*=========================================================================*/
void add_end_Point2D(Point2D *root,double x,double y,int stats){

	Point2D *iter,*new;

	if(root == NULL)
		return;
	iter = root;

	while(iter->next_p != NULL){
		iter = iter->next_p; 
	}

	new = (Point2D*)malloc(sizeof(Point2D));
	new ->x = x;
	new ->y = y;
	new ->jumper = stats;
	new->next_p = NULL;

	iter->next_p = new;
}
/*=========================================================================*/
void create_link_between_two_point(Point2D *ll_p1,Point2D *ll_p2){
	Point2D *tmp = ll_p1;	

	while(tmp->next_p != NULL){
		tmp = tmp->next_p;
	}	
	tmp->next_p = ll_p2;
}
/*=========================================================================*/
void draw_circle(Figure *fig,double step_size,double r){

	double strt_p = -r,
		   end_p = r; 
	Point2D *root = (Point2D*)malloc(sizeof(Point2D));

	root->x = strt_p;
	root->y = circle_cal_func(r,strt_p);
	root->jumper = 0;

	for(double i = strt_p; i<=end_p; i += (end_p-strt_p) / step_size )
		add_end_Point2D(root,i,circle_cal_func(r,i),0);

	for(double i = end_p; i>=strt_p; i -= (end_p-strt_p) / step_size )
		add_end_Point2D(root,i,-circle_cal_func(r,i),0);

	add_end_Point2D(root,strt_p,circle_cal_func(r,strt_p),0);

	fig->fPoint2D = root;
}
/*=========================================================================*/
double circle_cal_func(double r,double x){
	return sqrt(r*r - x*x);	
}
/*=========================================================================*/
void draw_ellipse(Figure *fig,Point2D * centre, Point2D * width_height){

	double strt_p = -width_height->x, 
		   end_p  = width_height->x;

	Point2D *mover = (Point2D*)malloc(sizeof(Point2D));
	Point2D *root = (Point2D*)malloc(sizeof(Point2D));
	
	root->jumper = 0;
	root->y = ellipse_cal_func(width_height,strt_p);		   
	root->x = strt_p;

	for(double i=strt_p; i<=end_p; i+=0.2)
			add_end_Point2D(root,i,ellipse_cal_func(width_height,i),0);
	for(double i=end_p; i>=strt_p; i-=0.2)
			add_end_Point2D(root,i,-ellipse_cal_func(width_height,i),0);

	add_end_Point2D(root,strt_p,ellipse_cal_func(width_height,strt_p),0);

	fig->fPoint2D = root;

	if(centre->x!=0 || centre->y!=0){
		mover=fig->fPoint2D;
		while(mover!=NULL){

			mover->x+=centre->x;
			mover->y+=centre->y;
			mover=mover->next_p;
		}
	}
}
/*=========================================================================*/
double ellipse_cal_func(Point2D * width_height,int x){
	return sqrt((1-((x*x)/(width_height->x*width_height->x)))*(width_height->y*width_height->y));
}
/*=========================================================================*/
void draw_polygon(Figure *fig,Point2D *poly_line,int size){
	int count = 1;
	Point2D *iter,*root;
	root = (Point2D*)malloc(sizeof(Point2D));
	root->next_p = NULL;
	iter = root;

	for(int i=0; i<size; i++){
		iter->x = poly_line[i].x;
		iter->y = poly_line[i].y;
		iter->jumper = 0;
		iter -> next_p = (Point2D*)malloc(sizeof(Point2D));
		iter -> next_p ->next_p = NULL;	
		iter = iter -> next_p;
	}
	iter->x = poly_line[0].x;
	iter->y = poly_line[0].y;
	iter->jumper = 0;
	iter->next_p = NULL;	
	fig->fPoint2D = root;
}
/*=========================================================================*/
void append_figures(Figure * fig1, Figure * fig2){

	Point2D *iter_1 = fig1->fPoint2D;
	Point2D *iter_2 = fig2->fPoint2D;

	Point2D *write  = iter_1;

	add_end_Point2D(iter_1,iter_2->x,iter_2->y, 1);

	while(write->next_p!=NULL){
		write = write->next_p;
	}

	write->next_p = fig2->fPoint2D;
}
/*=========================================================================*/
void scale_figure(Figure *fig,double scale_x, double scale_y){

	Point2D *imlec;

	double max_x, max_y,
		   min_x, min_y,
		   centre_x, centre_y;

	imlec = fig->fPoint2D;
	
	max_x = imlec->x;
	max_y=imlec->y;

	min_x=imlec->x;
	min_y=imlec->y;

	while(imlec!=NULL){

		if(imlec->x > max_x)	
			max_x=imlec->x;
		if(imlec->y > max_y)	
			max_y=imlec->y;
		if(imlec->x < min_x)	
			min_x=imlec->x;
		if(imlec->y < min_y)	
			min_y=imlec->y;
		
		imlec=imlec->next_p;
	}	    

	centre_x = (max_x + min_x) / 2.0;
	centre_y = (max_y + min_y) / 2.0;

	imlec = fig->fPoint2D;
	while(imlec!= NULL){
		imlec->x=((imlec->x-centre_x)*scale_x)+centre_x;
		imlec->y=((imlec->y-centre_y)*scale_y)+centre_y;
		imlec=imlec->next_p;
	}
}
/*=========================================================================*/
void resize_figure(Figure *fig,Point2D *start_roi, Point2D *end_roi){
	fig->ftxt = NULL;
	fig->lwlx = start_roi->x;
	fig->lwly = start_roi->y;
	fig->upriy = end_roi->y;
	fig->uprix = end_roi->x;
}
/*=========================================================================*/
void draw_binary_tree(Figure *fig,Tree *root,double center_x,double center_y){

	double	radius=13.0; /* general size of representation */
	int node_th;

	fig->ftxt=(Text*)malloc(sizeof(Text));
	fig->ftxt->num = root-> number;
	fig->ftxt->x = center_x-radius/3.0;
	fig->ftxt->y = center_y;

	Point2D *point = (Point2D*)malloc(sizeof(Point2D));
	point->x=center_x;
	point->y=center_y;

	node_th = (calculate_node_numbers(root)/2)+1;

	fig->fPoint2D = draw_node(fig,root,point,center_x,center_y,radius,1.0,node_th);
}
/*=========================================================================*/
void add_element_tree(Tree *root,int side_no,int number){

	Tree *side=(Tree*)malloc(sizeof(Tree));
	side->number=number;

	if(side_no==1)	
		root->left=side;
	else  				
		root->right=side;
}
/*=========================================================================*/
int calculate_node_numbers(Tree *branch){

	if(branch == NULL)
		return 0;
	else
		return (1 + (calculate_node_numbers(branch->left) + calculate_node_numbers(branch->right)));
}
/*=========================================================================*/
Point2D* draw_node(Figure *fig,Tree *branch,Point2D *points,double center_x,double center_y,int r,double x,int node_th){

	if(branch==NULL)
		return points;

	Figure *tmpfig = (Figure*)malloc(sizeof(Figure)); 
	Point2D *rad;

	rad = (Point2D*)malloc(sizeof(Point2D));

	rad->x = r;
	rad->y = r;
	points->	x = center_x;
	points-> y = center_y;

	make_same_figure(tmpfig,fig);
	draw_circle(tmpfig,1000,r);
	//draw_ellipse(fig,points,rad);
	create_link_between_two_point(points,tmpfig->fPoint2D);

	if(branch->left!=NULL){
		add_end_Point2D(points,center_x,center_y-r,0);
		add_end_Point2D(points,center_x-(node_th)*x*r,center_y-(node_th-1)*r,0);
	}
	
	if(branch->right!=NULL){
		add_end_Point2D(points,center_x,center_y-r,0);
		add_end_Point2D(points,center_x+(node_th)*x*r,center_y-(node_th-1)*r,0);
	}

	draw_node(fig,branch->left,points,center_x-r*x*(node_th),center_y-r*(node_th),r,x/2.0,node_th);
	draw_node(fig,branch->right,points,center_x+r*x*(node_th),center_y-r*(node_th),r,x/2.0,node_th);

	return points;
}

/*=========================================================================*/
void add_end_text(Text *root_text,int number,double center_x, double center_y){

	Text *txt=(Text*)malloc(sizeof(Text)); /* new text */

	txt->num=number;
	txt->x=center_x;
	txt->y=center_y;
	txt->next_txt=NULL;

	while(root_text->next_txt!=NULL)
		root_text=root_text->next_txt;
	root_text->next_txt=txt; /* insert to text list */

}
/*=========================================================================*/
void make_same_figure(Figure *fig1,Figure *fig2){

	fig1->lwlx=fig2->lwlx;
	fig1->lwly=fig2->lwly;
	fig1->uprix=fig2->uprix;
	fig1->upriy=fig2->upriy;
	fig1->resolution=fig2->resolution;
	fig1->thickness=fig2->thickness;
	fig1->fcolor.red=fig2->fcolor.red;
	fig1->fcolor.green=fig2->fcolor.green;
	fig1->fcolor.blue=fig2->fcolor.blue;
}
/*=========================================================================*/
// Figure* move_figure(Figure *fig,int x,int y){

// 	Figure *res_fig;

// 	*res_fig = make_figure();

// 	while(fig->fPoint2D ->next_p!= NULL){
// 		res_fig->fPoint2D = (Point2D*)malloc(sizeof(Point2D));
// 		res_fig->fPoint2D->y = 150 + fig->fPoint2D->y;
// 		res_fig->fPoint2D->x = 150 + fig->fPoint2D->x;
// 		//printf("%f    %f  \n",fig->fPoint2D->x,fig->fPoint2D->y );
// 		res_fig->fPoint2D = fig->fPoint2D->next_p;
// 	}
// 	return fig;
//}
/*=========================================================================*/
void export_eps(Figure * fig, char * file_name)
{
	Point2D *tmp; /* temporary Point2D */
	FILE *fp;

	fp=fopen(file_name,"wt"); /* both read and write */

	fprintf(fp,"%%!PS-Adobe-3.0 EPSF-3.0");
	fprintf(fp,"\n%%%%BoundingBox: %d %d %d %d",(int)fig->lwlx,(int)fig->lwly,(int)fig->uprix,(int)fig->upriy);
	fprintf(fp,"\n%d setlinewidth",(int)fig->thickness);
	fprintf(fp,"\n%.1f %.1f %.1f setrgbcolor",fig->fcolor.red,fig->fcolor.green,fig->fcolor.blue);

	if(fig->ftxt!=NULL){

		fprintf(fp,"\n/Times-Roman findfont\n5 scalefont\nsetfont"); /* configurations */
		while(fig->ftxt!=NULL){
			fprintf(fp,"\n%d %d moveto",(int)fig->ftxt->x,(int)fig->ftxt->y);
			fprintf(fp,"\n(%d) show",fig->ftxt->num);
			fig->ftxt=fig->ftxt->next_txt;
		}
	}

	fprintf(fp,"\n%1.f %1.f moveto",fig->fPoint2D->x,fig->fPoint2D->y);
	tmp=fig->fPoint2D->next_p;
	while(tmp!=NULL) {
		fprintf(fp,"\n%.1f %.1f ",tmp->x,tmp->y);
		if(tmp->jumper)	
			fprintf(fp,"moveto");
		else 
		    fprintf(fp,"lineto");
		tmp=tmp->next_p;
	}
	
	fprintf(fp,"\nstroke\n");
	fclose(fp);
}





