#ifndef _FIGURES_HPP_
#define _FIGURES_HPP_

#include <iostream>
#include <vector>

struct Cords{
	double x, y;
};

std::istream &operator>>(std::istream &is, Cords &c){
	is >> c.x >> c.y;
	return is;
}

std::istream &operator>>(std::istream &is, std::vector<Cords> &v){
	for(size_t i = 0; i < v.size(); i++){
		std::cin >> v[i];
	}
	return is;
}

std::ostream &operator<<(std::ostream &os, Cords c){
	os << "<" << c.x << ", " << c.y << ">";
	return os;
}

class Figure{
public:
	std::vector<Cords> cords;
	
	Figure(){}
	Figure(const Figure &f){
		for(size_t i = 0; i < f.cords.size(); i++){
			cords.push_back(f.cords[i]);
		}
	}
	virtual ~Figure(){}

	void read_cords(){
		for(size_t i = 0; i < cords.size(); i++){
			std::cin >> cords[i];
		}
	}
	
	virtual void print_name() = 0;
	virtual char get_figure() = 0;

	void print(){
		print_name();
		for(size_t i = 0; i < cords.size(); i++){
			std::cout << cords[i] << " ";
		}
		std::cout << '\n';
	}
};

class Square: public Figure{
public:
	Square(){
		for(size_t i = 0; i < 4; i++){
			cords.push_back({0, 0});
		}
	}
	Square(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		cords.push_back(c1);
		cords.push_back(c2);
		cords.push_back(c3);
		cords.push_back(c4);
	}
	Square(const Square &s){
		cords = s.cords;
	}
	Square(const std::vector<Cords> &v){
		cords = v;
	}
	~Square(){}

	void print_name(){
		std::cout << "Square: ";
	}

	char get_figure(){
		return 's';
	}
	
};

class Rectangle: public Figure{
public:
	Rectangle(){
		for(size_t i = 0; i < 4; i++){
			cords.push_back({0,0});
		}
	}
	Rectangle(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		cords.push_back(c1);
		cords.push_back(c2);
		cords.push_back(c3);
		cords.push_back(c4);
	}
	Rectangle(const Rectangle &r){
		cords = r.cords;
	}
	Rectangle(const std::vector<Cords> &v){
		cords = v;
	}
	~Rectangle(){}

	void print_name(){
		std::cout << "Rectangle: ";
	}

	char get_figure(){
		return 'r';
	}
};

class Trapezoid: public Figure{
public:
	Trapezoid(){
		for(size_t i = 0; i < 4; i++){
			cords.push_back({0,0});
		}
	}
	Trapezoid(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		cords.push_back(c1);
		cords.push_back(c2);
		cords.push_back(c3);
		cords.push_back(c4);
	}
	Trapezoid(const Trapezoid &t){
		cords = t.cords;
	}
	Trapezoid(const std::vector<Cords> &v){
		cords = v;
	}
	~Trapezoid(){}
	
	void print_name(){
		std::cout << "Trapezoid: ";
	}

	char get_figure(){
		return 't';
	}
};

class Factory{
public:
	virtual Figure *create_figure() = 0;
	virtual ~Factory(){}
};

class Square_Factory: public Factory{
public:
	Figure *create_figure(){
		return reinterpret_cast<Figure*>(new Square());
	}
	Figure *create_figure(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		return reinterpret_cast<Figure*>(new Square(c1, c2, c3, c4));
	}
	Figure *create_figure(const std::vector<Cords> &v){
		return reinterpret_cast<Figure*>(new Square(v));
	}
};

class Rectangle_Factory: public Factory{
public:
	Figure *create_figure(){
		return reinterpret_cast<Figure*>(new Rectangle());
	}
	Figure *create_figure(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		return reinterpret_cast<Figure*>(new Rectangle(c1, c2, c3, c4));
	}
	Figure *create_figure(const std::vector<Cords> &v){
		return reinterpret_cast<Figure*>(new Rectangle(v));
	}
};

class Trapezoid_Factory: public Factory{
public:
	Figure *create_figure(){
		return reinterpret_cast<Figure*>(new Trapezoid());
	}
	Figure *create_figure(const Cords &c1, const Cords &c2, const Cords &c3, const Cords &c4){
		return reinterpret_cast<Figure*>(new Trapezoid(c1, c2, c3, c4));
	}
	Figure *create_figure(const std::vector<Cords> &v){
		return reinterpret_cast<Figure*>(new Trapezoid(v));
	}
};

#endif