#pragma once

#include <string>
#include <vector>

template <class T>
class Obstacle{
public:
	Obstacle(T *sol) : solution(sol) {};

	virtual bool attemptResolution(std::vector<T*> sols) {
		for (T* k : sols) {
			if (matches(k))return true;
		}
		return false;
	}


	virtual std::string successfulResolution() = 0;
	virtual std::string failedResolution() = 0;

	virtual bool matches(T* attempt) {
		return solution == attempt;
	}

	virtual T* getSolution() {
		return solution;
	}

private:
	T *solution;

};

