#ifndef _GATHEREDDATA_HPP_
#define _GATHEREDDATA_HPP_

#include <set>

#include "utils.hpp"

#include "json.hpp"
#include "gatherer.hpp"

class GatheredData
{
public:
	boost::filesystem::path datafolder;

	Vec2i rendersize;
	unsigned rendersamples;

	std::vector<uint8_t> pathslength;
	std::vector<Vec3h> bouncesposition;
	std::vector<Vec3h> pathsluminance;
	std::vector<CameraSample> pathscamerasamples;

	std::vector<unsigned> firstbounceindexes;

	std::set<unsigned> selectedpaths;
	void addpaths(std::set<unsigned>& paths);
	void removepaths(std::set<unsigned>& paths);

	void loadall(const boost::filesystem::path& folder);
};

#endif