#include "model3/ResourceAPI.h"

namespace m3
{

static ResourceAPI::Callback CB;

void ResourceAPI::InitCallback(const Callback& cb)
{
	CB = cb;
}

void* ResourceAPI::CreateImg(const std::string& filepath)
{
	return CB.create_img(filepath);
}

void ResourceAPI::ReleaseImg(void* img)
{
	CB.release_img(img);
}

int ResourceAPI::GetTexID(const void* img)
{
	return CB.get_tex_id(img);
}

}