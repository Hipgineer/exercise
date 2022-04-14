#ifndef __SHADER_H__
#define __SHADER_H__

#include "common.h"

CLASS_PTR(Shader);
//class Shader;
//using ShaderUPtr = std::unique_ptr<Shader>;

class Shader {
public:
    static ShaderUPtr CreateFromFile(const std::string& filename, GLenum shaderType);
    //static std::unique_ptr<Shader>CreateFromFile(const std::string& filename, GLenum shaderType);

    ~Shader();

    //2. Get은 있는데 Set이 없는 이유?
    // - 바깥에서 볼 수 없도록 해야해!!
    // - openGl에서만 그 값을 이용할 수 있어야함
    uint32_t Get() const { return m_shader; }

private:
    //1. 생성자 : 클레스를 밖에서 못만든다. (싱글톤)
    // - static 함수를 콜해야지만 생성할 수 있따.
    // -- Shader* shader = Shader::CreateFromFile(~~);
    // -- static 함수니까 딱하나이고, 유니크 포인터라 복사도 안된다!
    Shader() {}
    //초기화
    bool LoadFile(const std::string& filename, GLenum shaderType);
    uint32_t m_shader { 0 } ;
};



#endif // __SHADER_H__