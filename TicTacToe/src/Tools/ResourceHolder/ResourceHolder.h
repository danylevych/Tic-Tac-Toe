#pragma once

#include <map>
#include <memory>
#include <cassert>
#include <stdexcept>


template <typename Key, typename Value>
class ResourceHolder
{
private:
	std::map<Key, std::unique_ptr<Value>> resources;

public:
	void Load(const Key& key, const std::string& path)
	{
		std::unique_ptr<Value> resource{ new Value() };

		if (!resource->loadFromFile(path)) // Can't load the file.
		{
			throw std::runtime_error("Cannot load resource: " + path + " | in " + __func__);
		}

		resources[key] = std::move(resource);
	}

	const std::unique_ptr<Value>& Get(const Key& key) const
	{
		auto found = resources.find(key);

		assert(found != resources.end());

		return found->second;
	}

	std::unique_ptr<Value>& Get(const Key& key)
	{
		// We add const to 'this' because of we need to call the const varaint of 'Get()'.
		// Then we take off 'const' from the value we got.
		return const_cast<std::unique_ptr<Value>&>(const_cast<const ResourceHolder&>(*this).Get(key));
	}

};
