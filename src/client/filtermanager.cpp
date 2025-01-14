#include "filtermanager.hpp"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

void FilterManager::render(
	Camera& cam, 
	GLuint scenefbo_id, 
	GLuint scenedepthtex,
	GLuint scenebeautytex
) {
	for(std::shared_ptr<Filter> f : filterslist)
	{
		if(f->visible)
			f->render(cam, scenefbo_id, scenedepthtex, scenebeautytex);
	}
}

void FilterManager::addfilter(std::shared_ptr<Filter> filter)
{
	filterslist.push_back(filter);
	filter->globalid = progressiveid;
	progressiveid++;
}


void FilterManager::setframesize(Vec2i size)
{
	for(std::shared_ptr<Filter> f : filterslist)
	{
		f->setframesize(size);
	}
}

bool FilterManager::renderui()
{
	ImGui::Separator();
	bool modified = false;
	unsigned i = 0;
	for(
		std::list<std::shared_ptr<Filter>>::iterator it = filterslist.begin();
		it != filterslist.end();
	) {
		std::shared_ptr<Filter> filterptr = *it;

		ImGui::PushID(i);
		bool toerase = ImGui::Button("-");
		ImGui::SameLine();

		std::string label;
		if(filterptr->visible)
			label = "Hide";
		else
			label = "Show";
		bool visibilitytoggled = ImGui::Button(label.c_str());
		modified |= visibilitytoggled;
		filterptr->visible ^= visibilitytoggled;
		ImGui::SameLine();
		ImGui::PopID();

		ImGui::Text(
			"%s %u", 
			filterptr->filtertypename.c_str(), 
			filterptr->globalid
		);
		modified |= filterptr->renderstackui();
		ImGui::Separator();

		modified |= toerase;
		if(toerase)
		{
			it = filterslist.erase(it);
		}
		if(!toerase) ++it;
		++i;
	}
	return modified;
}

void FilterManager::computepaths(GatheredData& gd)
{
	gd.selectedpaths.resize(gd.npaths);
	std::iota(gd.selectedpaths.begin(), gd.selectedpaths.end(), 0);

	for(std::shared_ptr<Filter> f : filterslist)
	{
		f->computepaths(gd);
	}
}