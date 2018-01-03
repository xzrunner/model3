#pragma once

#include <string>

namespace n3
{

class ResourceAPI
{
public:
	struct Callback
	{
		void* (*create_img)(const std::string& filepath);
		void  (*release_img)(void* img);
		int   (*get_tex_id)(const void* img);
	};

	static void InitCallback(const Callback& cb);

	static void* CreateImg(const std::string& filepath);
	static void ReleaseImg(void* img);
	static int GetTexID(const void* img);

}; // ResourceAPI

}