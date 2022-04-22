#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "common.h"
#include "shader.h"

CLASS_PTR(Program)
class Program {
public:
    static ProgramUPtr Create(
        const std::vector<ShaderPtr>& shaders);
        // Shared pointer,
        // 여러 곳에서 공동으로 사용할 수 있으니까

    ~Program();
    uint32_t Get() const { return m_program; }
    void Use() const;

private:
    Program() {};
    // 초기화 함수
    bool Link(
            const std::vector<ShaderPtr>& shaders);
    uint32_t m_program {0};
};


#endif // __PROGRAM_H__
