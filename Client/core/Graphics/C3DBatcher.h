/*****************************************************************************
 *
 *  PROJECT:     Multi Theft Auto
 *  LICENSE:     See LICENSE in the top level directory
 *  FILE:        C3DBatcher.h
 *  PURPOSE:
 *
 *
 *****************************************************************************/

//
// Batches primitives drawing
//
class C3DBatcher
{
    friend CGraphics;
    friend CPrimitiveMaterialBatcher;

public:
    ZERO_ON_NEW
    C3DBatcher(CGraphics* graphics);
    ~C3DBatcher();
    void OnDeviceCreate(IDirect3DDevice9* pDevice, float fViewportSizeX, float fViewportSizeY);
    void OnChangingRenderTarget(uint uiNewViewportSizeX, uint uiNewViewportSizeY);
    void UpdateMatrices(float fViewportSizeX, float fViewportSizeY);
    virtual void Flush() = 0;
protected:
    CGraphics*                      m_pGraphics;
    IDirect3DDevice9*               m_pDevice;
    float                           m_fViewportSizeX;
    float                           m_fViewportSizeY;
    D3DXMATRIX                      m_MatWorld;
    D3DXMATRIX                      m_MatView;
    D3DXMATRIX                      m_MatProjection;
};
