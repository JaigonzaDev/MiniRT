#include "vector.h"

t_vector vector_add (t_vector vec1, t_vector vec2)
{
    return ((t_vector){vec1.x + vec2.x,vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vector vector_sub (t_vector vec1, t_vector vec2)
{
    return ((t_vector){vec1.x - vec2.x,vec1.y - vec2.y, vec1.z - vec2.z});
}

t_vector vector_multi (t_vector vec1, t_vector vec2)
{
    return ((t_vector){vec1.x * vec2.x,vec1.y * vec2.y, vec1.z * vec2.z});
}

t_vector vector_div (t_vector vec1, t_vector vec2)
{
    return ((t_vector){vec1.x / vec2.x , vec1.y / vec2.y , vec1.z / vec2.z});
}