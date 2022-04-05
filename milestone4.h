#include "Types.h"

/*
 * This function is to help you dynamically allocate
 *  memory for a generic 2D Environemnt.
 */
Env make_env(const int rows, const int cols);

/*
 * This function is to help you delete a 
 * dynamically allocated 2D Environment.
 */
void delete_env(Env env, int rows, int cols);
