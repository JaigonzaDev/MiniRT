#include "render.h"

double	solve(t_equation *eq)
{
	double	discriminant;

	discriminant = eq->b * eq->b - 4 * eq->a * eq->c;
	if (discriminant < 0)
	{
		eq->t1 = -1;
		eq->t2 = -1;
		return (0);
	}
	eq->t1 = (-eq->b - sqrt(discriminant)) / (2.0 * eq->a);
	eq->t2 = (-eq->b + sqrt(discriminant)) / (2.0 * eq->a);
	return (1);
}
