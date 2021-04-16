#include "StdInc.h"
#include <diligentCore/Common/interface/BasicMath.hpp>
#include "diligentCore/Graphics/GraphicsTools/interface/MapHelper.hpp"

CDirectx11::CDirectx11(CCoreBasicInterface* pBasicInterface) : m_pBasicInterface(pBasicInterface)
{
    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
}

void CDirectx11::CreatePipelineState()
{
    // Pipeline state object encompasses configuration of all GPU stages

    GraphicsPipelineStateCreateInfo PSOCreateInfo;

    // Pipeline state name is used by the engine to report issues.
    // It is always a good idea to give objects descriptive names.
    PSOCreateInfo.PSODesc.Name = "Cube PSO";

    // This is a graphics pipeline
    PSOCreateInfo.PSODesc.PipelineType = PIPELINE_TYPE_GRAPHICS;

    // clang-format off
    // This tutorial will render to a single render target
    PSOCreateInfo.GraphicsPipeline.NumRenderTargets             = 1;
    // Set render target format which is the format of the swap chain's color buffer
    PSOCreateInfo.GraphicsPipeline.RTVFormats[0]                = m_pSwapChain->GetDesc().ColorBufferFormat;
    // Set depth buffer format which is the format of the swap chain's back buffer
    PSOCreateInfo.GraphicsPipeline.DSVFormat                    = m_pSwapChain->GetDesc().DepthBufferFormat;
    // Primitive topology defines what kind of primitives will be rendered by this pipeline state
    PSOCreateInfo.GraphicsPipeline.PrimitiveTopology            = PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    // Cull back faces
    PSOCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode      = CULL_MODE_BACK;
    // Enable depth testing
    PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = false;
    // clang-format on

    ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood.
    ShaderCI.SourceLanguage = SHADER_SOURCE_LANGUAGE_HLSL;

    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.UseCombinedTextureSamplers = true;

    // In this tutorial, we will load shaders from file. To be able to do that,
    // we need to create a shader source stream factory
    RefCntAutoPtr<IShaderSourceInputStreamFactory> pShaderSourceFactory;
    m_pFactoryD3D11->CreateDefaultShaderSourceStreamFactory(nullptr, &pShaderSourceFactory);
    ShaderCI.pShaderSourceStreamFactory = pShaderSourceFactory;
    // Create a vertex shader
    RefCntAutoPtr<IShader> pVS;
    {
        ShaderCI.Desc.ShaderType = SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Cube VS";
        ShaderCI.FilePath = "D:\\VISUAL STUDIO\\mtasa-blue\\bintests\\Directx11\\cube.vsh";
        m_pDevice->CreateShader(ShaderCI, &pVS);
        // Create dynamic uniform buffer that will store our transformation matrix
        // Dynamic buffers can be frequently updated by the CPU
        BufferDesc CBDesc;
        CBDesc.Name = "VS constants CB";
        CBDesc.uiSizeInBytes = sizeof(float4x4);
        CBDesc.Usage = USAGE_DYNAMIC;
        CBDesc.BindFlags = BIND_UNIFORM_BUFFER;
        CBDesc.CPUAccessFlags = CPU_ACCESS_WRITE;
        m_pDevice->CreateBuffer(CBDesc, nullptr, &m_VSConstants);
    }

    // Create a pixel shader
    RefCntAutoPtr<IShader> pPS;
    {
        ShaderCI.Desc.ShaderType = SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint = "main";
        ShaderCI.Desc.Name = "Cube PS";
        ShaderCI.FilePath = "D:\\VISUAL STUDIO\\mtasa-blue\\bintests\\Directx11\\cube.psh";
        m_pDevice->CreateShader(ShaderCI, &pPS);
    }

    // Define vertex shader input layout
    LayoutElement LayoutElems[] = {// Attribute 0 - vertex position
                                   LayoutElement{0, 0, 3, VT_FLOAT32, False},
                                   // Attribute 1 - vertex color
                                   LayoutElement{1, 0, 4, VT_FLOAT32, False}};

    PSOCreateInfo.GraphicsPipeline.InputLayout.LayoutElements = LayoutElems;
    PSOCreateInfo.GraphicsPipeline.InputLayout.NumElements = _countof(LayoutElems);

    PSOCreateInfo.pVS = pVS;
    PSOCreateInfo.pPS = pPS;

    // Define variable type that will be used by default
    PSOCreateInfo.PSODesc.ResourceLayout.DefaultVariableType = SHADER_RESOURCE_VARIABLE_TYPE_STATIC;

    m_pDevice->CreateGraphicsPipelineState(PSOCreateInfo, &m_pPSO);

    // Since we did not explcitly specify the type for 'Constants' variable, default
    // type (SHADER_RESOURCE_VARIABLE_TYPE_STATIC) will be used. Static variables never
    // change and are bound directly through the pipeline state object.
    m_pPSO->GetStaticVariableByName(SHADER_TYPE_VERTEX, "Constants")->Set(m_VSConstants);

    // Create a shader resource binding object and bind all static resources in it
    m_pPSO->CreateShaderResourceBinding(&m_pSRB, true);
}

int  i = 0;
void CDirectx11::DoPulse()
{
    printf("------- RENDER START -------\n");
    if (!m_pFactoryD3D11 && m_pBasicInterface->GetHookedWindow() != 0)
    {
        printf("Hook %p\n", m_pBasicInterface->GetHookedWindow());
        Create(m_pBasicInterface->GetHookedWindow());
    }

    const float ClearColor[] = {0.350f, 0.350f, 0.350f, 1.0f};
    auto*       pRTV = m_pSwapChain->GetCurrentBackBufferRTV();
    auto*       pDSV = m_pSwapChain->GetDepthBufferDSV();
    m_pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
   
    m_pImmediateContext->ClearRenderTarget(pRTV, ClearColor, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    m_pImmediateContext->ClearDepthStencil(pDSV, CLEAR_DEPTH_FLAG, 1.f, 0, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    i++;
    float4x4 m_WorldViewProjMatrix = float4x4::Translation(100, sin(i / 20.0f) * 100.0f, cos(i / 20.0f) * 100.0f);
    {
        // Map the buffer and write current world-view-projection matrix
        struct VSConstants
        {
            float4x4 WorldViewProj;
        };
        MapHelper<VSConstants> CBConstants(m_pImmediateContext, m_VSConstants, MAP_WRITE, MAP_FLAG_DISCARD);
        CBConstants->WorldViewProj = m_WorldViewProjMatrix;
    }

    m_pImmediateContext->CommitShaderResources(m_pSRB, RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    for (const auto& mesh : m_vecMeshes)
    {
        mesh->Draw();
    }
    m_pImmediateContext->Flush();
    m_pImmediateContext->FinishFrame();
    m_pSwapChain->Present();
    printf("------- RENDER END %i -------\n", i);
}

void CDirectx11::CreateMesh(const std::vector<Vertex>& vertices, const std::vector<Uint32> indices)
{
    m_vecMeshes.push_back(std::make_unique<CMesh>(this, vertices, indices));
}

void CDirectx11::SetDefaultPipeline()
{
    GetImmediateContext()->SetPipelineState(m_pPSO);
}

void CDirectx11::Create(HWND window)
{
    m_pFactoryD3D11 = GetEngineFactoryD3D11();
    EngineD3D11CreateInfo EngineCI;
    SwapChainDesc         chainDesc;

    m_pFactoryD3D11->CreateDeviceAndContextsD3D11(EngineCI, &m_pDevice, &m_pImmediateContext);
    m_pFactoryD3D11->CreateSwapChainD3D11(m_pDevice, m_pImmediateContext, chainDesc, FullScreenModeDesc{}, NativeWindow{window}, &m_pSwapChain);

    CreatePipelineState();
}
