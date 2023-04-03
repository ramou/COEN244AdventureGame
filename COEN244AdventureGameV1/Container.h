#pragma once

#include <string>
#include <vector>
#include <map>



template<class T>
class Container {
public:
	T get(std::string name) {
		return stuffInContainer.find(name);
	}

	bool isEmpty() {
		return stuffInContainer.empty();
	}

	void put(T thing) {
		stuffInContainer.insert(std::pair<std::string, T>(thing.getName(), thing));
	}

	void put(std::vector<T> things) {
		for (T thing : things) {
			put(thing);
		}
	}

	/*
	void display(std::vector<std::string> &messages) {
		for (auto i : stuff){
			messages.push_back(i.second.getName());
		}
		
	}
	*/

	template<typename F>
	void process(F && strategy) {
		for(auto i : stuffInContainer) {
			strategy(i.second);
		}
		stuffInContainer.clear();
	}

private:
	std::map<const std::string, T> stuffInContainer;
};

