/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientDFF.h
*  PURPOSE:     .dff model handling class
*  DEVELOPERS:  Christian Myhre Lundheim <>
*
*****************************************************************************/

class CClientDFF;

#ifndef __CCLIENTDFF_H
#define __CCLIENTDFF_H

#include <list>
#include "CClientEntity.h"

struct SLoadedClumpInfo
{
    SLoadedClumpInfo ( void ) : bTriedLoad ( false ), pClump ( NULL ) {} 
    bool     bTriedLoad;
    RpClump* pClump;
};


class CClientDFF : public CClientEntity
{
    DECLARE_CLASS( CClientDFF, CClientEntity )
    friend class CClientDFFManager;

public:
                                    CClientDFF              ( class CClientManager* pManager, ElementID ID );
                                    ~CClientDFF             ( void );

    eClientEntityType               GetType                 ( void ) const              { return CCLIENTDFF; }

    bool                            LoadDFF                 ( const SString& strFile, bool bIsRawData );

    bool                            ReplaceModel            ( unsigned short usModel, bool bAlphaTransparency );

    bool                            HasReplaced             ( unsigned short usModel );

    void                            RestoreModel            ( unsigned short usModel );
    void                            RestoreModels           ( void );

    static bool                     IsDFFData               ( const SString& strData );

    // Sorta a hack that these are required by CClientEntity...
    void                            Unlink                  ( void ) {};
    void                            GetPosition             ( CVector& vecPosition ) const {};
    void                            SetPosition             ( const CVector& vecPosition ) {};
    const RpGeometry * GeometryTriangleSetVertexIndices(const RpGeometry * geo, RpTriangle * tri, ushort v1, ushort v2, ushort v3);
    RpGeometry * GeometryTriangleSetMaterialId(RpGeometry * geo, RpTriangle * tri, RpMaterial * mat);
    RpAtomic * AtomicSetGeometry(RpAtomic * atomic, RpGeometry * geometry, unsigned int flags);
    static int ClumpGetNumAtomics(RpClump * clump);
    static RwTexture* CreateTexture(RwRaster* pRaster);
    static RwRaster*  CreateRaster(int width, int height, int depth, int flags);
    static int GetMeshIdFromPolygonId(RpGeometry* pGeometry, ushort uiTriangle);
    static int GetPolygonIdInMesh(RpGeometry* pGeometry, RpMesh* pMesh, ushort uiTriangle);
    static RpMesh* GetMeshFromPolygonId(RpGeometry* pGeometry, ushort uiTriangle);
    static bool CClientDFF::GeometryDestroyVertex(RpGeometry* pGeometry, ushort usVertex);
    static bool GeometryDestroyPolygon(RpGeometry* pGeometry, ushort uiTriangle);
    static char* GetometryFlags(RpGeometry* pGeometry);
    static bool CreatePolygon(RpGeometry* pGeometry, ushort vertex1, ushort vertex2, ushort vertex3, ushort usMesh);
    static ushort CreateMesh(RpGeometry* pGeometry);
    static RpMaterial* CreateMaterial(void);
    static RpLight* CreateLight(int type);
    static RpClump* ClumpAddLight(RpClump* clump, RpLight* light);
    static bool EnableVerticesLighting(RpGeometry* pGeometry);
    static std::vector < ushort > GetPolygonsUsedByVertex(RpGeometry* pGeometry, ushort usVertex);
    static bool CreateVertex(RpGeometry* pGeometry, CVector vecPosition);
    static bool SetPolygonPosition(RpGeometry* pGeometry, ushort usPolygon, CVector newPosition);

    static void GetVerticesInMesh(lua_State* luaVM, RpMesh* mesh);
    static void GetVertices(lua_State* luaVM, RpGeometry* pGeometry);
    static void GetVerticesInRange(lua_State* luaVM, RpGeometry* pGeometry, CVector vecPosition, float fRange);
    static void GetVertexNeares3d(lua_State* luaVM, RpGeometry* pGeometry, CVector vecPosition);
    static void GetVertexNeares2d(lua_State* luaVM, RpGeometry* pGeometry, CVector2D vecPosition);
    static CVector GetPolygonPosition(RpGeometry* pGeometry, ushort usPolygon);
    static bool SetPolygonVertices(RpGeometry* pGeometry, ushort usPolygon, ushort vertex1, ushort vertex2, ushort vertex3);

    bool TransformMove(std::vector< ushort > vertices, CVector vecMove);
    bool TransformScale(std::vector< ushort > vertices, CVector vecScale);

    static bool VerticesToolMakePlanear(lua_State* luaVM, RpGeometry* pGeometry, std::vector< ushort > vertices, SString axis);

    static RpMeshHeader* CreateMeshHeader(unsigned int size);
    static void Copy(RpClump* pClumpOrigin, RpClump* &pClumpDesc);
    static void CreateCollision(RpGeometry* pGeometry, CClientColModel* pCol);

    static bool CreateObjectPlane(RpGeometry* pGeometry, ushort usMesh, float fXs, float fYs, float fXe, float fYe, float fHeight, ushort usSegmentLenght, ushort usSegmentWidth);
    static bool CreateVertices(RpGeometry* pGeometry, std::vector < CVector > vecPosition);
    static bool CreatePolygons(RpGeometry* pGeometry, ushort usMesh, std::vector < RpTriangle > vecPolygons);

    static bool IsValidPosition(CVector vecPosition);


    RpClump*                        GetLoadedClump(ushort usModelId);

    ushort                            uimodel = NULL;
    SString                           strModelName = "";
    ushort                            uiGeometry = 0;

protected:
    bool                            DoReplaceModel          ( unsigned short usModel, bool bAlphaTransparency );
    void                            UnloadDFF               ( void );
    void                            InternalRestoreModel    ( unsigned short usModel );

    bool                            ReplaceObjectModel      ( RpClump* pClump, ushort usModel, bool bAlphaTransparency );
    bool                            ReplaceVehicleModel     ( RpClump* pClump, ushort usModel, bool bAlphaTransparency );
    bool                            ReplaceWeaponModel      ( RpClump* pClump, ushort usModel, bool bAlphaTransparency );
    bool                            ReplacePedModel         ( RpClump* pClump, ushort usModel, bool bAlphaTransparency );


    class CClientDFFManager*        m_pDFFManager;

    SString                         m_strDffFilename;
    CBuffer                         m_RawDataBuffer;
    bool                            m_bIsRawData;
    std::map < ushort, SLoadedClumpInfo > m_LoadedClumpInfoMap;

    std::list < unsigned short >    m_Replaced;
};

#endif
