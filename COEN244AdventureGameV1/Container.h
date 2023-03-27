#pragma once

#include <string>
#include <vector>
#include <map>


template<class T>
class Container {
public:
	T get(std::string name) {
		return stuff.find(name);
	}

	bool isEmpty() {
		return stuff.empty();
	}

	void put(T thing) {
		stuff.insert(std::pair<std::string, T>(thing.getName(), thing));
	}

	void display(std::vector<std::string> &messages) {
		for (auto i : stuff){
			messages.push_back(i.second.getName());
		}
	}

private:
	std::map<const std::string, T> stuff;
};

