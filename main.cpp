/*
Фигурный редактор
М8О-201Б-18
Баранников Степан Алексеевич
*/

#include <iostream>
#include <vector>
#include <memory>
#include <string>

#include "figures.hpp"
#include "serialize.hpp"

void print_actions(){
	std::cout << "Actions:\n";
	std::cout << "-\tgenerate N\n";
	std::cout << "-\tpush_begin <figure name> <cords>\n";
	std::cout << "-\tpush_end <figure name> <cords>\n";
	std::cout << "-\tpop_begin\n";
	std::cout << "-\tpop_end\n";
	std::cout << "-\tundo\n";
	std::cout << "-\timport <filename>\n";
	std::cout << "-\texport <filename>\n";
}

int main(){
	std::unique_ptr<Square_Factory> square_factory(new Square_Factory);
	std::unique_ptr<Rectangle_Factory> rectangle_factory(new Rectangle_Factory);
	std::unique_ptr<Trapezoid_Factory> trapezoid_factory(new Trapezoid_Factory);

	Serializable_Vector sv;
	
	print_actions();

	std::string action = "";
	while(action != "exit"){
		std::cout << "\nBUFFER:\n";
		sv.print();
		std::cout << "------------------\n";
		std::cout << "> ";
		std::cin >> action;
		
		std::string figure_name;
		std::string file_name;

		if(action == "push_begin" || action == "push_end"){
			std::cin >> figure_name;
			std::vector<Cords> v(4);
			std::cin >> v;

			if(figure_name == "square"){
				if(action == "push_begin"){
					sv.push_begin(square_factory->create_figure(v));
				}else{
					sv.push_end(square_factory->create_figure(v));
				}
			}else if(figure_name == "rectangle"){
				if(action == "push_begin"){
					sv.push_begin(rectangle_factory->create_figure(v));
				}else{
					sv.push_end(rectangle_factory->create_figure(v));
				}
			}else if(figure_name == "trapezoid"){
				if(action == "push_begin"){
					sv.push_begin(trapezoid_factory->create_figure(v));
				}else{
					sv.push_end(trapezoid_factory->create_figure(v));
				}
			}else{
				std::cout << "Error: wrong figure name\n";
			}
		}else if(action == "pop_begin"){
			sv.pop_begin();
		}else if(action == "pop_end"){
			sv.pop_end();
		}else if(action == "import" || action == "export"){
			std::cin >> file_name;
			if(action == "import"){
				sv.import_file(file_name);
			}else{
				sv.export_file(file_name);
			}
		}else if(action == "undo"){
			sv.undo();
		}else if(action == "generate"){
			unsigned n;
			std::cin >> n;
			sv.generate(n);
		}else if(action == "exit"){
			if(!sv.is_saved()){
				std::cout << "Warning! Your buffer is not saved.\n";
				std::cout << "Continue? (y/n): ";
				char ans;
				std::cin >> ans;
				if(ans != 'y'){
					action = "";
				}
			}
		}else{
			std::cout << "Wrong command\n";		
		}
	}
}
