/*************************************************************************
 * TGEP v.0.0.1
 * A game engine for Windows using Opengl and glfw 
 *------------------------------------------------------------------------
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 Toma-Ștefan Cezar 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *************************************************************************/
#ifndef _TGEP_h_
#define _TGEP_h_


#include "./TGEP/Application.h"
//Logging system 
#include "./TGEP/Log.h"
//#define LOG_ERROR(...) ::TGEP::Log::GetClientLogger()->error(__VA_ARGS__)
//#define LOG_WARN(...) ::TGEP::Log::GetClientLogger()->warn(__VA_ARGS__)
//#define LOG_INFO(...) ::TGEP::Log::GetClientLogger()->info(__VA_ARGS__)
// ---ENTRY POINT---
#include "./TGEP/EntryPoint.h"
//Event system 
#include "./TGEP/Events/Event.h"
//Layer system
#include "./TGEP/Layer.h"
//Imgui
#include "./TGEP/Layers/ImGuiLayer.h"
//Input
#include "./TGEP/Input.h"
//Key/Mouse codes
#include "./TGEP/Events/KeyCodes.h"
#include "./TGEP/Events/MouseCodes.h"
//ImGui
#include "./ImGui/imgui.h"

#endif // _TGEP_h_