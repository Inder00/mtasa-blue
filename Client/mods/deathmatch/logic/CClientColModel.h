/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientColModel.h
*  PURPOSE:     Model collision (.col file) entity class
*  DEVELOPERS:  Christian Myhre Lundheim <>
*
*****************************************************************************/

#ifndef __CCLIENTCOLMODEL_H
#define __CCLIENTCOLMODEL_H

#include <list>
#include "CClientEntity.h"

class CClientColModel : public CClientEntity
{
    DECLARE_CLASS( CClientColModel, CClientEntity )
public:
                                    CClientColModel         ( class CClientManager* pManager, ElementID ID );
                                    ~CClientColModel        ( void );

    eClientEntityType               GetType                 ( void ) const              { return CCLIENTCOL; }

    bool                            LoadCol                 ( const SString& strFile, bool bIsRawData );
    inline bool                     IsLoaded                ( void )                    { return m_pColModel != NULL; };

    bool                            Replace                 ( unsigned short usModel );
    void                            Restore                 ( unsigned short usModel );
    void                            RestoreAll              ( void );

    bool                            HasReplaced             ( unsigned short usModel );
    static bool                     IsCOLData               ( const SString& strData );


    // Sorta a hack that these are required by CClientEntity...
    void                            Unlink                  ( void ) {};
    void                            GetPosition             ( CVector& vecPosition ) const {};
    void                            SetPosition             ( const CVector& vecPosition ) {};
    unsigned short GetModelPolygonCount();
    unsigned short GetModelVerticesCount();
    float GetModelBoundingBoxRadius();
    CVector GetModelBoundingBoxOffset();
    CVector GetModelBoundingBoxVecMin();
    CVector GetModelBoundingBoxVecMax();
    CVector GetVertexPosition(unsigned short usPolygonId);
    bool SetModelPolygonSurface(unsigned short usPolygonId, unsigned short usSurfaceId);
    bool SetTriangleSetLighting(unsigned short usPolygon, unsigned short day, unsigned short night);
    bool SetVertexPosition(unsigned short usVertex, CVector position);
    void GetTriangleConnectedVertices(unsigned short usPolygon, unsigned short &vertex1, unsigned short &vertex2, unsigned short &vertex3);
    bool SetTriangleConnectedVertices(unsigned short usPolygon, unsigned short vertex1, unsigned short vertex2, unsigned short vertex3);
    unsigned short CreateVertex(CVector vecPosition);
    bool DestroyVertex(unsigned short usVertex);
    bool DestroyPolygon(unsigned short usPolygon);
    unsigned short CreatePolygon(unsigned short vertex1, unsigned short vertex2, unsigned short vertex3);
    CVector GetTrianglePosition(unsigned short usPolygon);
    bool IsValidPolygonId(unsigned short usPolygon);
    bool SelectElement(lua_State* luaVM, unsigned short usPolygon);
    void GetNeighbors(CColTriangleSA polygon, std::vector < CColTriangleSA > &polygons, std::vector < int > &neighbors, bool recursion);
    bool Grow(lua_State* luaVM, unsigned short usPolygon, unsigned short &usNext);


    void UpdateBoundingBox();
    std::vector < CColTriangleSA > GetAllPolygons();
    CColModel*                      m_pColModel;
    unsigned short usModel=NULL;
private:
    void                            InternalRestore         ( unsigned short usModel );

    class CClientColModelManager*   m_pColModelManager;
    
    std::list < unsigned short >    m_Replaced;
};

#endif
