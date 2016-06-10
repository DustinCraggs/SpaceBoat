# Search paths
dirs = Graphics Logic Physics Resources Libs

# Source files to compile
logic = Logic.cpp Entity.cpp
graphics = Graphics.cpp Model.cpp Camera.cpp
resources = Resources.cpp
physics = Physics.cpp
libs = tiny_obj_loader.cc Shader.cpp

src_files = $(addprefix Logic/, $(logic))
src_files += $(addprefix Graphics/, $(graphics))
src_files += $(addprefix Resources/, $(resources))
src_files += $(addprefix Physics/, $(physics))
src_files += $(addprefix Libs/, $(libs))

I_flags = $(addprefix -I, $(dirs))
flags = -lGLEW `pkg-config --cflags glfw3` -std=c++11 -g
endthing = `pkg-config --static --libs glfw3`
# $(info $(src))

all:
	g++ $(I_flags) $(flags) Graphics/Graphics.cpp $(endthing)
	# g++ $(I_flags) $(flags) $(src_files) $(endthing)

SkyBox.o: Graphics/SkyBox.cpp Graphics/SkyBox.hpp Graphics/Geometry.hpp
	g++ $(I_flags) $(flags) -c Graphics/SkyBox.cpp $(endthing)

Shader.o: Libs/Shader.cpp Libs/Shader.hpp
	g++ $(I_flags) $(flags) -c Libs/Shader.cpp $(endthing)

CubeMapTexture.o: CubeMapTexture.cpp CubeMapTexture.hpp
	g++ $(I_flags) $(flags) -c Graphics/CubeMapTexture.cpp $(endthing)

test: cubemap.o SkyBox.o Shader.o Entity.o Model.o tiny_obj_loader.o
	g++ $(I_flags) $(flags) -o test cubemap.o SkyBox.o Shader.o Entity.o Model.o tiny_obj_loader.o $(endthing)

cubemap.o: cubemap.cpp
	g++ $(I_flags) $(flags) -c cubemap.cpp $(endthing)

Entity.o: Logic/Entity.cpp Logic/Entity.hpp
	g++ $(I_flags) $(flags) -c Logic/Entity.cpp $(endthing)

Model.o: Graphics/Model.cpp Graphics/Model.hpp
	g++ $(I_flags) $(flags) -c Graphics/Model.cpp $(endthing)

tiny_obj_loader.o: Libs/tiny_obj_loader.cc Libs/tiny_obj_loader.h	
	g++ $(I_flags) $(flags) -c Libs/tiny_obj_loader.cc $(endthing)

clean:
	rm -rf *.o
