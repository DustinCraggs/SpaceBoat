# Search paths
dirs = Control Graphics Logic Physics Resources Libs

# Source files to compile
# Add source files here
control		= Control.cpp
logic		= Logic.cpp Entity.cpp
graphics 	= Graphics.cpp Model.cpp Camera.cpp Geometry.cpp ParticleRenderer.cpp Skybox.cpp CubeMapTexture.cpp
resources 	= Resources.cpp
physics 	= Physics.cpp ParticleSystem.cpp
libs		= tiny_obj_loader.cc Shader.cpp

# Debug mode
debug = true

control_files 	= $(addprefix Control/, $(control))
logic_files 	= $(addprefix Logic/, $(logic))
graphics_files 	= $(addprefix Graphics/, $(graphics))
resources_files	= $(addprefix Resources/, $(resources))
physics_files 	= $(addprefix Physics/, $(physics))
libs_files 		= $(addprefix Libs/, $(libs))

src_files = $(control_files)
src_files += $(logic_files)
src_files += $(graphics_files)
src_files +=$(resources_files)
src_files +=$(physics_files)
src_files +=$(libs_files)

I_flags = $(addprefix -I, $(dirs))
flags = -lGLEW `pkg-config --cflags glfw3` -std=c++11
ifeq ($(debug), true)
	I_flags += -g -D DEBUG
endif
endthing = `pkg-config --static --libs glfw3`

all:
	g++ $(I_flags) $(flags) $(src_files) -o solarSurfer driver.cpp $(endthing)

clean:
	rm *.o solarSurfer

# $(info $(src))
