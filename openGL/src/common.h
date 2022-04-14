#ifndef __COMMON_H__ // pragma once 랑 뭐가 다름? ==> 윈도우에서 많이 쓴다. // 크로스플랫폼!
#define __COMMON_H__

#include <memory>
#include <string>
#include <optional>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

// 여기서 ## 은 kalssNameUPtr 이렇게 붙여주는 역할!!!
#define CLASS_PTR(klassName) \
class klassName; \
using klassName ## UPtr=std::unique_ptr<klassName>; \
using klassName ## Ptr=std::shared_ptr<klassName>; \
using klassName ## WPtr=std::weak_ptr<klassName>; 


//있을때 없을때를! 
// string*로 선언할 수 있지만, 없으면 널포인터로 주소값이 동적할당되기 때문에 그만큼 메모리 손실
// 그래서 값이 들어올때만!
std::optional<std::string> LoadTextFile(const std::string& filename);

#endif // __COMMON_H__

