#ifndef __PLAINS
#define __PLAINS

#include <string>
namespace lab3 {
	
	class Environment;
	
	class Plains : public Environment {		
		
		public:
			Plains(std::string d, std::pair<int,int> c);
	};
}
#endif
