#ifndef HITTABLE
#define HITTABLE

#include "ray.h"

typedef struct hit_record {
	float t;
	float *p;
	float *normal;
	char ft_fc;
} hit_rc;

typedef char (*func_ptr)(float *ct, interval ray_t, float radius, ray *iray, hit_rc *ht);

typedef struct world {
	func_ptr hit;
	float *ct;
	float radius;
	struct world *next;
} world;

void st_fc_nm (ray *iray, float *ot_nm, hit_rc *ht){
	// ot_nm默认已经有了归一化处理

	ht->ft_fc = dot (direction (iray), ot_nm) < 0;
	ht->normal = ht->ft_fc ? ot_nm : opo (ot_nm);
}

char hit_ray(ray *iray, interval ray_t, hit_rc *ht, world *objs) {
    world *tos = objs;
    hit_rc *temp = malloc(sizeof(hit_rc));

    char hit_anything = 0;

    while (tos != NULL) {														// 遍历所有的物体
        if ((tos->hit)(tos->ct, ray_t, tos->radius, iray, temp)) {		// 调用碰撞检测函数
            hit_anything = 1;													// 碰到了就是1
            ray_t.tmax = temp->t;													// 因为将“最近的”作为碰撞点最远的传给了hit函数，所以如果能进到这个if里就是更近的一个
            *ht = *temp;														// 将结果复制到传入的hit_record
        }
        tos = tos->next;  // 移动到下一个物体
    }
    free(temp);
    return hit_anything;
}

// 对于C++，这里需要定义构造函数。但这是C，所以干脆就用一个个单个碰撞检测函数吧(･᷄ὢ･᷅)
#endif
