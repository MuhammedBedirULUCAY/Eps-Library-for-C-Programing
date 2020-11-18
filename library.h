#ifndef LIBRARY_H
#define LIBRARY_H

typedef struct Point2D{
	double x,y;
	struct Point2D *next_p;
	int jumper;
}Point2D;

typedef struct Color{
	double green,red,blue;	
}Color;

typedef struct Text{
	double x,y,
		   size_tx;
	int num;
	struct Text *next_txt;
}Text;

typedef struct Figure{
	double uprix,upriy,lwlx,lwly;
	double resolution, thickness;
	Color fcolor;
	Point2D *fPoint2D;
	Text *ftxt; 
}Figure;

typedef struct Tree{
	int number;
	struct Tree *left,*right;
}Tree;

Figure make_figure();
Figure * start_figure(double width, double height);

void set_thickness_resolution(Figure *fig, double thickness,double resolution);
void set_color(Figure * fig, Color c);

void draw_fx(Figure * fig, double f(double x),
	double start_x, double end_x,double step_size);
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
void add_element_tree(Tree *root,int side_no,int number);
Point2D* draw_node(Figure *fig,Tree *branch,Point2D *point,double center_x,double center_y,int radius,double x,int node_number);
void add_element_tree(Tree *root,int side_no,int number);
void make_same_figure(Figure *fig1,Figure *fig2);
int calculate_node_numbers(Tree *branch);
void add_end_text(Text *text,int number,double center_x, double center_y);
Figure* move_figure(Figure *fig,int x,int y);
void export_eps(Figure * fig, char * file_name);


#endif
