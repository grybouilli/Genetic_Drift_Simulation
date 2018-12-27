#include <Headers/Application.hpp>
#include <iostream>

int main() {
	
	Application app;
	
	try {
		
		app.run();
		
	} catch(const std::exception& e) {
		
		std::cerr << "Exception was caught: " << e.what() << std::endl;
	}
}