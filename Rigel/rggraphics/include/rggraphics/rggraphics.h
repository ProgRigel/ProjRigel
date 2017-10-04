#pragma once
#include <rgcore\rgcore.h>

#include <Windows.h>
#include <memory>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

#include <d3d11.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dxguid.lib")

#include "rg_graphicsAPI.h"
#include "rg_graphicscontext.h"
#include "rg_render_context.h"

#include "rg_blend_state.h"
#include "rg_depthstencil_state.h"
#include "rg_rasterizer_state.h"


#include "rg_buffer.h"
#include "rg_command_list.h"
#include "rg_inputlayout.h"
#include "rg_material.h"
#include "rg_render_target.h"
#include "rg_sampler.h"
#include "rg_shader.h"
#include "rg_texture.h"
#include "rg_viewport.h"


