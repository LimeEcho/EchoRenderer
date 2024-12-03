#ifndef CAMERA
#define CAMERA

// 在main最后include的，所以不需要include任何头文件
#define im_w 500
#define RATIO ((float)16 / (float)9)
#define FL (float)1
#define vp_h (float)2

FILE *file;
int im_h;
float vp_w;
float *cm_ct;
float *vp_u;
float *vp_v;
float *px_dl_u;
float *px_dl_v;
float *vp_ul;
float *px_00_lc;
int all;
float step;
float current;
obj_info *objsh;																// 构建场景物体集
obj_info *objst;															// 链表结构

void add_obj(obj_info **objsh, obj_info **objst, float *ct, float radius) {				// 一个标准的操作链表函数（骄傲）∠( ᐛ 」∠)＿
	obj_info *new_obj = malloc(sizeof(obj_info));

	new_obj->hit = &sph_ht;
	new_obj->ct = ct;
	new_obj->radius = radius;
	new_obj->next = NULL;

	if (*objsh == NULL) {
		*objsh = *objst =  new_obj;
	}else{
		(*objst)->next = new_obj;
		*objst = (*objst)->next;
	}
}



void initalize (void){
	objsh = NULL;																// 构建场景物体集
	objst = objsh;															// 链表结构

	im_h = ((int)(im_w / RATIO) < 1) ? 1 : (int)(im_w / RATIO);						// 根据比例计算图像高度

	vp_w = vp_h * ((float)im_w / im_h);											// 视图宽度
	cm_ct = req (0.0, 0.0, 0.0);													// 相机中心

	vp_u = req (vp_w, 0.0, 0.0);													// 详见explanation/ViewPort.png
	vp_v = req (0.0, -vp_h, 0.0);

	px_dl_u = divi (vp_u, im_w);
	px_dl_v = divi (vp_v, im_h);

	vp_ul = sub(sub (cm_ct, req (0.0, 0.0, FL)), add (divi (vp_u, 2), divi (vp_v, 2)));	// 左上角像素，也就是P (0,0)
	px_00_lc = add (vp_ul, mul (add (px_dl_u, px_dl_v), 0.5));							// 左上角像素坐标
	file = fopen ("a.ppm", "w");
	fprintf (file, "P3\n%d %d\n255\n", im_w, im_h);
	all = im_h * im_w;
	step = 100.0 / all;
	current = 0.0;
}

void render (void){
	for (int y = 0; y < im_h; y++){
		for (int x = 0; x < im_w; x++){
			current += step;
			printf ("\rCurrent: %.2f%%", current);
			float *px_ct = add (px_00_lc, add (mul (px_dl_u, x), mul (px_dl_v, y)));			// 像素中心坐标
			float *ray_dir = sub (px_ct, cm_ct);												// 发射射线
			ray *r = reqray (cm_ct, ray_dir);													// 创建
			ray_col (r, objsh);																	// 写出像素颜色（其中检测是否相交）
		}
	}
	printf ("\rCurrent: 100.0%%\n");
}

#endif