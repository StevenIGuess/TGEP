#include "TGEPconfig.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "../../vendor/imgui/imgui.h"
#include "../../vendor/imgui/imgui_impl_opengl3.h"
#include "../../vendor/imgui/imgui_impl_glfw.h"

#include "Core.h"

#include <utility>
#include <string>
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <functional>
#include <stdint.h>
#include <vector>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>