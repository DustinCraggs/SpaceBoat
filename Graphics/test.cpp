#include <iostream>
#include "../Libs/tinydir.h"

int main(){
	tinydir_dir dir;
	tinydir_open(&dir, ".");

	while( dir.has_next ){
		tinydir_file file;
		tinydir_readfile(&dir, &file);

		std::cout << file.name;
		if( file.is_dir ){
			std::cout << "/";
		}
		std::cout << std::endl;

		tinydir_next(&dir);
	}

	tinydir_close(&dir);
}