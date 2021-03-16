
#include "../miniRT.h"

int	lambertian(const t_ray *ray, const t_hit_record *hitted, t_vector *attenuation, t_ray *scattered)
{
	scattered->pos = hitted->pos;
	scattered->dir = get_reflected_dir(&(hitted->normal));
	attenuation = 
