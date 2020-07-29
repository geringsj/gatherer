#include "utils.hpp"

GLuint disk_load_shader(
	const boost::filesystem::path&	path,
	const GLenum 					type
)
{
	boost::filesystem::ifstream ifs{path};
	std::string str(
		(std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>())
	);
	ifs.close();
	const char* src = str.c_str();
	GLuint idx = glCreateShader(type);
	glShaderSource(idx, 1, &src, nullptr);
	glCompileShader(idx);

	GLint compile_status;
	glGetShaderiv(idx, GL_COMPILE_STATUS, &compile_status);
	if(compile_status == GL_FALSE)
	{
		BOOST_LOG_TRIVIAL(error) << "Shader has errors!";
		char info[512];
		glGetShaderInfoLog(idx, 512, NULL, info);
    	BOOST_LOG_TRIVIAL(error) << info;
		return -1;
	}
	BOOST_LOG_TRIVIAL(info) << "Compiled shader " << idx;

	return idx;
}

GLuint disk_load_shader_program(
	const boost::filesystem::path& vtxsha_path,
	const boost::filesystem::path& fragsha_path
)
{
	GLuint vtxsha_idx  = disk_load_shader(vtxsha_path,  GL_VERTEX_SHADER);
	GLuint fragsha_idx = disk_load_shader(fragsha_path, GL_FRAGMENT_SHADER);

	GLuint shaprog_idx;
	shaprog_idx = glCreateProgram();
	glAttachShader(shaprog_idx, vtxsha_idx);
	glAttachShader(shaprog_idx, fragsha_idx);
	glLinkProgram(shaprog_idx);

	GLint link_status;
	glGetProgramiv(shaprog_idx, GL_LINK_STATUS, &link_status);
	if(link_status == GL_FALSE)
	{
		BOOST_LOG_TRIVIAL(error) << "Shader program has errors!";
		char info[512];
		glGetProgramInfoLog(shaprog_idx, 512, NULL, info);
    	BOOST_LOG_TRIVIAL(error) << info;
		return -1;
	}
	BOOST_LOG_TRIVIAL(info) << "Created shader program " << shaprog_idx;

	glDeleteShader(vtxsha_idx);
	glDeleteShader(fragsha_idx);

	return shaprog_idx;
}