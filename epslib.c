#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int main(){

	Figure *fig = (Figure*)malloc(sizeof(Figure)*9);
	Point2D *center=(Point2D*)malloc(sizeof(Point2D));
	center->x=0.0; 			center->y=25.0;
	fig[0] = make_figure();

	Tree *root = (Tree*)malloc(sizeof(Tree));
	add_element_tree(root,0,10);
	add_element_tree(root,1,20);
	add_element_tree(root->left,0,30);
	add_element_tree(root->left,1,40);
	add_element_tree(root->right,0,50);
	add_element_tree(root->right,1,60);
	
	Point2D *start,*end;

	start = (Point2D*)malloc(sizeof(Point2D));
	end = (Point2D*)malloc(sizeof(Point2D));

	start->x=-100;
	start->y=-100;
	end->x=100;
	end->y=50;
	resize_figure(fig,start,end);
	draw_binary_tree(fig,root,center->x,center->y);
	export_eps(fig,"binary.eps");

	/////////////////////////////////////////////////////


	// for(int i=0; i<9; i++){
	// 	*(fig+i) = make_figure();
	// }

	// draw_fx(&fig[0],tan,-50,50,1000);
	// export_eps(&fig[0],"circle.eps");


	// scale_figure(&fig[0],1,1);
	// export_eps(&fig[0],"gggggggg.eps");

////////////////////////////////////////////////////////

	// fig[0] = make_figure();
	// Point2D *arr_poly= (Point2D*)malloc(20*sizeof(Point2D));

	// for(int i = 0;i<20;i++){
	// 	arr_poly[i].x= i;
	// 	arr_poly[i].y= (i*i) ;
	// }
	// draw_polyline(&fig[0],arr_poly,20);
	// printf(";lasdkaskd\n");
	// export_eps(&fig[0],"line.eps");
////////////////////////////////////////////////////////


	 //figg[0] = make_figure();
	// printf("lkfdg;kdl;fgkd;lfkg\n");
	 //draw_circle(&fig[1],100,50);
	 //printf("alskdlajsd\n");
	 //export_eps(&fig[1],"cirle.eps");
	 //append_figures(fig,figg);
	 //export_eps(&fig[0],"app.eps");

////////////////////////////////////////////////////////
	// fig[0] = make_figure();
	// Point2D *centre, *width_height;
	// Point2D *en,*boy;

	// en = (Point2D*)malloc(sizeof(Point2D));
	// boy = (Point2D*)malloc(sizeof(Point2D));

	// en->x = 0;
	// en->y = 0;
	// boy->x = 100;
	// boy->y = 100;
	
	// centre = (Point2D*)malloc(sizeof(Point2D));
	// width_height = (Point2D*)malloc(sizeof(Point2D));
	// centre->x = 0;
	// centre->y = 0;
	// width_height->x = 100.0;
	// width_height->y = 100.0;
	// width_height->jumper = 0;

	// draw_ellipse(&fig[0],centre,width_height);

	// export_eps(&fig[0],"ellipse.eps");
	// resize_figure(&fig[0],en,boy);
	// export_eps(&fig[0],"ellipeee.eps");
////////////////////////////////////////////////////////

	// fig[0] = make_figure();

	// Point2D *arr_poly= (Point2D*)malloc(6*sizeof(Point2D));

	// arr_poly[0].x = 0;
	// arr_poly[0].y = 0;

	// arr_poly[1].x = 3;
	// arr_poly[1].y = 3;

	// arr_poly[2].x = 7;
	// arr_poly[2].y = 3;

	// arr_poly[3].x = 10;
	// arr_poly[3].y = 0;

	// arr_poly[4].x = 7;
	// arr_poly[4].y = -3;

	// arr_poly[5].x = 3;
	// arr_poly[5].y = -3;

	// draw_polygon(&fig[0],arr_poly,6);
	// export_eps(&fig[0],"polygn.eps");
////////////////////////////////////////////////////////


	 free(fig);

	return 0;
}
