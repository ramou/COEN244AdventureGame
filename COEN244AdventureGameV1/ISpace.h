#pragma once
#include <iostream>

class ISpace
{
public:
	virtual ISpace& move(ISpace& origin) = 0;
	virtual ISpace& makeMove(char m) = 0;
	virtual void draw() = 0;

	virtual void setNorth(ISpace& s) {}
	virtual void setSouth(ISpace& s) {}
	virtual void setEast(ISpace& s) {}
	virtual void setWest(ISpace& s) {}

};


class Wall :
    public ISpace
{
public:
    void draw() {
        std::cout << "#";
    }

    virtual ISpace& move(ISpace& origin) {
        return origin;
    }

    virtual ISpace& makeMove(char m) {
        return *this;
    }

	static Wall * WALL;

private:
	static Wall w;
};

class VoidSpace :
    public Wall
{
    void draw() {
        std::cout << " ";
    }
};

class Floor : public ISpace
{
public:
	Floor() {}

	virtual ISpace& move(ISpace& origin) {
		return *this;
	}

	virtual ISpace& makeMove(char m);


	virtual void draw() {
		std::cout << ".";
	};

	void setNorth(ISpace& s) { north = &s; }
	void setSouth(ISpace& s) { south = &s; }
	void setEast(ISpace& s) { east = &s; }
	void setWest(ISpace& s) { west = &s; }

private:
	ISpace* north = Wall::WALL;
	ISpace* south = Wall::WALL;
	ISpace* east = Wall::WALL;
	ISpace* west = Wall::WALL;

};


//It broke because we didn't check for a bunch
//of the other things like items, stairs or the
//"other" player starting position from the map
//we grabbed. Instead of dying horribly, when
//we start up, how about this to notify the user
//and keep goind?
class OtherSpace :
	public Floor
{
public:
	OtherSpace(char c) : c(c) {
		std::cout << "Found an unexpected character " << c << std::endl;
	}
private:
	char c;
};

class Stairs :
	public Floor
{
	void draw() {
		std::cout << "<";
	}
};
