/*************************************************************************
 * TGEP v.0.0.1
 * A game engine for Windows using Opengl and glfw
 *------------------------------------------------------------------------
 * The MIT License (MIT)
 *
 * Copyright (c) 2022 Toma-?tefan Cezar
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

#include "Application.h"
 // ---ENTRY POINT---
#include "EntryPoint.h"
//Event system 
#include "Events/Event.h"
//Layer system
#include "Layer.h"
//Imgui
#include "Layers/ImGuiLayer.h"
//Input
#include "Input.h"
//Key/Mouse codes
#include "Events/KeyCodes.h"
#include "Events/MouseCodes.h"
//ImGui
#include "imgui.h"
//Renderer system
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
//Buffer system
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
//Shader system
#include "Renderer/Shader.h"
#include "RenderAPI/OpenGL/OpenGLShader.h"
//Camera system
#include "Renderer/Camera.h"
//Time system
#include "DeltaTime.h"
//Textures
#include "Renderer/Texture.h"
//Networking
#include "Networking/connection.h"
#include "Networking/client.h"
#include "Networking/server.h"
#include "Networking/message.h"
#endif // _TGEP_h_