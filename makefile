# Search paths
dirs = Graphics Logic Physics Resources Libs

# Source files to compile
logic = Logic.cpp Entity.cpp
graphics = Graphics.cpp Model.cpp Camera.cpp
resources = Resources.cpp
physics = Physics.cpp
libs = tiny_obj_loader.cc

src_files = $(addprefix Logic/, $(logic))
src_files += $(addprefix Graphics/, $(graphics))
src_files += $(addprefix Resources/, $(resources))
src_files += $(addprefix Physics/, $(physics))
src_files += $(addprefix Libs/, $(libs))

I_flags = $(addprefix -I, $(dirs))
flags = -lGLEW `pkg-config --cflags glfw3` -std=c++11
endthing = `pkg-config --static --libs glfw3`
# $(info $(src))

all:
	# g++ $(I_flags) $(flags) Graphics/Graphics.cpp $(endthing)
	g++ $(I_flags) $(flags) $(src_files) $(endthing)