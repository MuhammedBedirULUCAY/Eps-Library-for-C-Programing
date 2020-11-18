#include "library.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){

	Figure *figs = (Figure*)malloc(sizeof(Figure)*11);

	for(int i=0; i<11 ; i++)
		figs[i] = make_figure();

	draw_fx(&figs[0],tan,-50,50,1000);

	draw_fx(&figs[5],tan,-50,50,1000);
	figs[6] = figs[5];
	while(figs[5].fPoint2D != NULL){	//Baslangic noktasi kaydiriliyor
		figs[5].fPoint2D->y = 100 + figs[5].fPoint2D->y;
		figs[5].fPoint2D->x = 100 + figs[5].fPoint2D->x;
		figs[5].fPoint2D = figs[5].fPoint2D->next_p;
	}

	draw_fx(&figs[9],tan,-50,50,1000);
	figs[10] = figs[9];
	while(figs[9].fPoint2D != NULL){ 	//Baslangic noktasi kaydiriliyor
		figs[9].fPoint2D->y = 300 + figs[9].fPoint2D->y;
		figs[9].fPoint2D->x = 200 + figs[9].fPoint2D->x;
		figs[9].fPoint2D = figs[9].fPoint2D->next_p;
	}

	Point2D *arr_poly= (Point2D*)malloc(100*sizeof(Point2D));
	for(int i = 0;i<100;i++){
		arr_poly[i].x= i; 		
		arr_poly[i].y= sqrt(i) ;
	}
	draw_polyline(&figs[1],arr_poly,100);
	
	Point2D *arr_polygon= (Point2D*)malloc(3*sizeof(Point2D));
	arr_polygon[0].x = 0;
	arr_polygon[0].y = 100;
	arr_polygon[1].x = 35;
	arr_polygon[1].y = 0;
	arr_polygon[2].x = -100;
	arr_polygon[2].y = 0;
	draw_polygon(&figs[2],arr_polygon,3);

	Point2D *center = (Point2D*)malloc(sizeof(Point2D));
	center->x = 0;		center->y = 0;
	Point2D *we_he = (Point2D*)malloc(sizeof(Point2D));
	we_he ->x = 150;	we_he ->y = 250;
	draw_ellipse(&figs[3],center,we_he);
	
	draw_ellipse(&figs[7],center,we_he);
	figs[8] = figs[7];
	while(figs[7].fPoint2D != NULL){	//Baslangic noktasi kaydiriliyor
		figs[7].fPoint2D->y = 100 + figs[7].fPoint2D->y;
		figs[7].fPoint2D->x = 100 + figs[7].fPoint2D->x;
		figs[7].fPoint2D = figs[7].fPoint2D->next_p;
	}

	Tree *t_root = (Tree*)malloc(sizeof(Tree));
	add_element_tree(t_root,0,10);
	add_element_tree(t_root,1,20);
	add_element_tree(t_root->left,0,30);
	add_element_tree(t_root->left,1,40);
	Point2D *start,*end;
	start = (Point2D*)malloc(sizeof(Point2D));
	end = (Point2D*)malloc(sizeof(Point2D));
	start->x=-100;	start->y=-100;
	end->x=100;		end->y=50;
	//resize_figure(&figs[4],start,end);
	draw_binary_tree(&figs[4],t_root,center->x,center->y);

	Point2D *en,*boy;
	en = (Point2D*)malloc(sizeof(Point2D));
	boy = (Point2D*)malloc(sizeof(Point2D));

	en->x = 0;
	en->y = 0;
	boy->x = 100;
	boy->y = 100;


	scale_figure(&figs[10],100,20);
	
	append_figures(&figs[8],&figs[6]);

	export_eps(&figs[0],"draw_fx.eps");
	export_eps(&figs[1],"polyline.eps");
	export_eps(&figs[2],"polygon.eps");
	export_eps(&figs[3],"ellipse.eps");
	export_eps(&figs[4],"binary_tree.eps");
	export_eps(&figs[8],"appended.eps");
	export_eps(&figs[10],"scale.eps");

	return 0;
}

