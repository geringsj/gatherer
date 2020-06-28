#ifndef _PATH_HPP_
#define _PATH_HPP_

#include "math.hpp"
#include <vector>

class Path
{
public:
	Path();
	Path(const size_t npoints);
	std::vector<Vec3h> points;
};

#endif
