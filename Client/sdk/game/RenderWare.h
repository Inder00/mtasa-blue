/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        sdk/game/RenderWare.h
*  PURPOSE:     RenderWare-compatible definitions for
*               Grand Theft Auto: San Andreas
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*  RenderWare is © Criterion Software
*
*****************************************************************************/

#ifndef __RENDERWARE_COMPAT
#define __RENDERWARE_COMPAT

/*****************************************************************************/
/** RenderWare rendering types                                              **/
/*****************************************************************************/

// RenderWare definitions
#define RW_STRUCT_ALIGN           ((int)((~((unsigned int)0))>>1))
#define RW_TEXTURE_NAME_LENGTH    32
#define RW_FRAME_NAME_LENGTH      23
#define RW_MAX_TEXTURE_COORDS     8


typedef struct RwV2d RwV2d;
typedef struct RwV3d RwV3d;
typedef struct RwPlane RwPlane;
typedef struct RwBBox RwBBox;
typedef struct RpGeometry RpGeometry;
typedef void   RpWorld;
typedef struct RpClump RpClump;
typedef struct RwRaster RwRaster;
typedef struct RpMaterialLighting RpMaterialLighting;
typedef struct RpMaterialList RpMaterialList;
typedef struct RpMaterial RpMaterial;
typedef struct RpTriangle RpTriangle;
typedef struct RwTextureCoordinates RwTextureCoordinates;
typedef struct RwColor      RwColor;
typedef struct RwColorFloat RwColorFloat;
typedef struct RwObjectFrame RwObjectFrame;
typedef struct RpAtomic RpAtomic;
typedef struct RwCamera RwCamera;
typedef struct RpLight RpLight;
typedef class CNightVertexColors CNightVertexColors;
typedef struct RwFrameList RwFrameList;
typedef struct RwLLLink  RwLLLink;
typedef struct RwLinkList RwLinkList;


typedef struct RpMeshHeader RpMeshHeader;
typedef struct RwResEntry RwResEntry;
typedef struct RpMorphTarget RpMorphTarget;
typedef RwCamera *(*RwCameraPreCallback) (RwCamera * camera);
typedef RwCamera *(*RwCameraPostCallback) (RwCamera * camera);
typedef RpAtomic *(*RpAtomicCallback) (RpAtomic * atomic);
typedef RpClump  *(*RpClumpCallback) (RpClump * clump, void *data);

// RenderWare primitive types
struct RwV2d
{   // 8-byte
    float x,y;
};
struct RwV3d
{   // 12-byte
    float x,y,z;
    CVector getVector() {
        CVector RwV3dVector;
        RwV3dVector.fX = x;
        RwV3dVector.fY = y;
        RwV3dVector.fZ = z;
        return RwV3dVector;
    }
};
struct RwPlane
{
    RwV3d normal;
    float length;
};
struct RwBBox
{
    RwV3d max;
    RwV3d min;
};
struct RwSphere
{
    RwV3d position;
    float radius;
};
struct RwMatrix
{   // 16-byte padded
    RwV3d          right;  // 0
    unsigned int   flags;  // 12
    RwV3d          up;     // 16
    unsigned int   pad1;   // 28
    RwV3d          at;     // 32
    unsigned int   pad2;   // 44
    RwV3d          pos;    // 48
    unsigned int   pad3;   // 60
};

// RenderWare enumerations
enum RwPrimitiveType
{
    PRIMITIVE_NULL = 0,
    PRIMITIVE_LINE_SEGMENT = 1,
    PRIMITIVE_LINE_SEGMENT_CONNECTED = 2,
    PRIMITIVE_TRIANGLE = 3,
    PRIMITIVE_TRIANGLE_STRIP = 4,
    PRIMITIVE_TRIANGLE_FAN = 5,
    PRIMITIVE_POINT = 6,
    PRIMITIVE_LAST = RW_STRUCT_ALIGN
};
enum RwCameraType
{
    RW_CAMERA_NULL = 0,
    RW_CAMERA_PERSPECTIVE = 1,
    RW_CAMERA_ORTHOGRAPHIC = 2,
    RW_CAMERA_LAST = RW_STRUCT_ALIGN
};
enum RpAtomicFlags
{
    ATOMIC_COLLISION = 1,
    ATOMIC_VISIBLE = 4,
    ATOMIC_LAST = RW_STRUCT_ALIGN
};
enum RwRasterLockFlags
{
    RASTER_LOCK_WRITE = 1,
    RASTER_LOCK_READ = 2,
    RASTER_LOCK_LAST = RW_STRUCT_ALIGN
};
enum RwTransformOrder
{
    TRANSFORM_INITIAL = 0,
    TRANSFORM_BEFORE = 1,
    TRANSFORM_AFTER = 2,
    TRANSFORM_LAST = RW_STRUCT_ALIGN
};
enum RpLightType
{
    LIGHT_TYPE_NULL = 0,
    
    LIGHT_TYPE_DIRECTIONAL = 1,
    LIGHT_TYPE_AMBIENT = 2,
    
    LIGHT_TYPE_POINT = 0x80,
    LIGHT_TYPE_SPOT_1 = 0x81,
    LIGHT_TYPE_SPOT_2 = 0x82,

    LIGHT_TYPE_LAST = RW_STRUCT_ALIGN
};
enum RpLightFlags
{
    LIGHT_ILLUMINATES_ATOMICS = 1,
    LIGHT_ILLUMINATES_GEOMETRY = 2,
    LIGHT_FLAGS_LAST = RW_STRUCT_ALIGN
};


enum RpGeometryFlag
{
    rpGEOMETRYTRISTRIP = 0x00000001, /**<This geometry's meshes can be
                                     rendered as strips.
                                     \ref RpMeshSetTriStripMethod is
                                     used to change this method.*/
    rpGEOMETRYPOSITIONS = 0x00000002, /**<This geometry has positions */
    rpGEOMETRYTEXTURED = 0x00000004, /**<This geometry has only one set of
                                     texture coordinates. Texture
                                     coordinates are specified on a per
                                     vertex basis */
    rpGEOMETRYPRELIT = 0x00000008, /**<This geometry has pre-light colors */
    rpGEOMETRYNORMALS = 0x00000010, /**<This geometry has vertex normals */
    rpGEOMETRYLIGHT = 0x00000020, /**<This geometry will be lit */
    rpGEOMETRYMODULATEMATERIALCOLOR = 0x00000040, /**<Modulate material color
                                                  with vertex colors
                                                  (pre-lit + lit) */

    rpGEOMETRYTEXTURED2 = 0x00000080, /**<This geometry has at least 2 sets of
                                      texture coordinates. */

                                      /*
                                      * These above flags were stored in the flags field in an RwObject, they
                                      * are now stored in the flags file of the RpGeometry.
                                      */

    rpGEOMETRYNATIVE = 0x01000000,
    rpGEOMETRYNATIVEINSTANCE = 0x02000000,

    rpGEOMETRYFLAGSMASK = 0x000000FF,
    rpGEOMETRYNATIVEFLAGSMASK = 0x0F000000,

    rpGEOMETRYFLAGFORCEENUMSIZEINT = RW_STRUCT_ALIGN
};


enum RpMeshHeaderFlags
{
    /* NOTE: trilists are denoted by absence of any other
    *       primtype flags, so be careful that you test:
    *        (triListFlag == (flags&triListFlag))
    *       or:
    *        (0 == (flags&rpMESHHEADERPRIMMASK))
    *       and not:
    *        (flags&triListFlag)
    */
    rpMESHHEADERTRISTRIP = 0x0001, /**< Render as tristrips */
    rpMESHHEADERTRIFAN = 0x0002, /**< On PlayStation 2 these will be converted to trilists */
    rpMESHHEADERLINELIST = 0x0004, /**< Render as linelists */
    rpMESHHEADERPOLYLINE = 0x0008, /**< On PlayStation 2 these will be converted to linelists */
    rpMESHHEADERPOINTLIST = 0x0010, /**< Pointlists are supported only if rendered by
                                    *   custom pipelines; there is no default RenderWare
                                    *   way to render pointlists. */

    rpMESHHEADERPRIMMASK = 0x00FF, /**< All bits reserved for specifying primitive type */
    rpMESHHEADERUNINDEXED = 0x0100, /**< Topology is defined implicitly by vertex
                                    *   order, ergo the mesh contains no indices */
};

enum {
    FLAGS_TRISTRIP = 0x01,
    FLAGS_POSITIONS = 0x02,
    FLAGS_TEXTURED = 0x04,
    FLAGS_PRELIT = 0x08,
    FLAGS_NORMALS = 0x10,
    FLAGS_LIGHT = 0x20,
    FLAGS_MODULATEMATERIALCOLOR = 0x40,
    FLAGS_TEXTURED2 = 0x80
};

enum {
    MATFX_BUMPMAP = 0x1,
    MATFX_ENVMAP = 0x2,
    MATFX_BUMPENVMAP = 0x3,
    MATFX_DUAL = 0x4,
    MATFX_UVTRANSFORM = 0x5,
    MATFX_DUALUVTRANSFORM = 0x6,
};

enum {
    FACETYPE_STRIP = 0x1,
    FACETYPE_LIST = 0x0
};

/* gta3 ps2: 302, 304, 310
* gta3 pc: 304, 310, 401ffff, 800ffff, c02ffff
* gtavc ps2: c02ffff
* gtavc pc: c02ffff, 800ffff, 1003ffff
* gtasa: 1803ffff */

enum {
    GTA3_1 = 0x00000302,
    GTA3_2 = 0x00000304,
    GTA3_3 = 0x00000310,
    GTA3_4 = 0x0800FFFF,
    VCPS2 = 0x0C02FFFF,
    VCPC = 0x1003FFFF,
    SA = 0x1803FFFF
};

/*
* Typedef for RpMeshHeaderFlags enumeration
* representing the different types of mesh
*/
typedef enum RpMeshHeaderFlags RpMeshHeaderFlags;

// RenderWare/plugin base types
struct RwObject
{
    unsigned char type;
    unsigned char subtype;
    unsigned char flags;
    unsigned char privateFlags;
    void *parent;                // should be RwFrame with RpClump
};
struct RwVertex
{
    RwV3d        position;
    RwV3d        normal;
    unsigned int color;
    float        u,v;
};
struct RwListEntry
{
    RwListEntry *next,*prev;
};
struct RwList
{
    RwListEntry root;
};
struct RwFrame
{
    RwObject         object;            // 0
    void             *pad1,*pad2;       // 8
    RwMatrix         modelling;         // 16
    RwMatrix         ltm;               // 32
    RwList           objects;           // 48
    struct RwFrame   *child;            // 56
    struct RwFrame   *next;             // 60
    struct RwFrame   *root;             // 64

    // Rockstar Frame extension (0x253F2FE) (24 bytes)
    unsigned char    pluginData[8];                       // padding
    char             szName[RW_FRAME_NAME_LENGTH+1];        // name (as stored in the frame extension)
};

struct RwFrameList
{
    RwFrame *frames;
    unsigned short numFrames;
};

struct RwLLLink
{
    RwLLLink *next;
    RwLLLink *prev;
};

struct RwLinkList
{
    RwLLLink link;
};

struct CNightVertexColors
{
    RwColor *night;
    RwColor *day;
    float   m_fLightingState;
};
struct RpMesh
{
    unsigned short *indices;
    unsigned int   numIndices;
    RpMaterial    *material;
};

struct RpMeshHeader
{
    unsigned int   flags;
    unsigned short numMeshes;
    unsigned short serialNum;
    unsigned int   totalIndicesInMesh;
    unsigned int   firstMeshOffset;
    RpMesh *getMeshes(void) { return (RpMesh*)(this + 1); }
    bool isValidMeshId(int meshId)
    {
        return (meshId != NULL && numMeshes >= meshId);
    }
};
struct RwTexDictionary
{
    RwObject     object;
    RwList       textures;
    RwListEntry  globalTXDs;
};
struct RwTexture
{
    RwRaster           *raster;
    RwTexDictionary    *txd;
    RwListEntry        TXDList;
    char               name[RW_TEXTURE_NAME_LENGTH];
    char               mask[RW_TEXTURE_NAME_LENGTH];
    unsigned int       flags;
    int                refs;
};
struct RwTextureCoordinates
{
    float u,v;
};
struct RwRaster
{
    RwRaster        *parent;               // 0
    unsigned char   *pixels;               // 4
    unsigned char   *palette;              // 8
    int             width, height, depth;  // 12, 16 / 0x10, 20
    int             numLevels;             // 24 / 0x18
    short           u, v;
    unsigned char   type;
    unsigned char   flags;
    unsigned char   privateFlags;
    unsigned char   format;
    unsigned char   *origPixels;
    int             origWidth, origHeight, origDepth;
    void*           renderResource;         // RwD3D9Raster continues from here
};
struct RwColorFloat
{
    float r,g,b,a;
};
struct RwColor
{
    unsigned char r,g,b,a;
};
struct RwObjectFrame
{
    RwObject     object;
    RwListEntry  lFrame;
    void         *callback;
};
struct RwCameraFrustum
{
    RwPlane       plane;
    unsigned char x,y,z;
    unsigned char unknown1;
};
struct RwCamera
{
    RwObjectFrame        object;
    RwCameraType         type;
    RwCameraPreCallback  preCallback;
    RwCameraPostCallback postCallback;
    RwMatrix             matrix;
    RwRaster             *bufferColor;
    RwRaster             *bufferDepth;
    RwV2d                screen;
    RwV2d                screenInverse;
    RwV2d                screenOffset;
    float                nearplane;
    float                farplane;
    float                fog;
    float                unknown1;
    float                unknown2;
    RwCameraFrustum      frustum4D[6];
    RwBBox               viewBBox;
    RwV3d                frustum3D[8];
};
struct RwGeometry
{
    unsigned char   unknown1[14];
    unsigned short  refs;
};
struct RpInterpolation
{
    unsigned int     unknown1;
    unsigned int     unknown2;
    float            unknown3;
    float            unknown4;
    float            unknown5;
};
struct RpAtomic
{
    RwObjectFrame    object;
    void             *info;
    RpGeometry       *geometry;
    RwSphere         bsphereLocal;
    RwSphere         bsphereWorld;
    RpClump          *clump;
    RwListEntry      globalClumps;
    RpAtomicCallback renderCallback;
    RpInterpolation  interpolation;
    unsigned short   frame;
    unsigned short   unknown7;
    RwList           sectors;
    void             *render;
    RwFrame * getFrame()
    {
        return reinterpret_cast<RwFrame *>(this->object.object.parent);
    }
};

struct RwMatrixWeights
{
    float w0;
    float w1;
    float w2;
    float w3;
};

struct RpSkin
{
    unsigned int     numBones;
    unsigned int     numBoneIds;
    unsigned char   *boneIds;
    RwMatrix        *skinToBoneMatrices;
    unsigned int     maxNumWeightsForVertex;
    unsigned int    *vertexBoneIndices;
    RwMatrixWeights *vertexBoneWeights;
    char             field_1C[8];
    unsigned int     boneLimit;
    unsigned int     numMeshes;
    unsigned int     numRLE;
    unsigned char   *meshBoneRemapIndices;
    unsigned int     meshBoneRLECount;
    void            *meshBoneRLE;
    void            *field_3C;
};

struct RpAtomicContainer {
    RpAtomic    *atomic;
    char        szName[17];
};
struct RpLight
{
    RwObjectFrame   object;
    float           radius;
    RwColorFloat    color;
    float           unknown1;
    RwList          sectors;
    RwListEntry     globalLights;
    unsigned short  frame;
    unsigned short  unknown2;
};
struct RpClump
{   // RenderWare (plugin) Clump (used by GTA)
    RwObject        object;
    /* Information about all the Atomics */
    RwList          atomics;
    RwList          lights;
    /* Lists of lights and cameras */
    RwList          cameras;
    /* The clump in a world */
    RwListEntry     globalClumps;
    RpClumpCallback callback;
    RpAtomic* getAtomic()
    {
        return (RpAtomic*)((this->atomics.root.next) - 0x8);
    }
};
struct RpMaterialLighting
{
    float ambient, specular, diffuse;
};
struct RpMaterial
{
    RwTexture*          texture;
    RwColor             color;
    void                *render;
    RpMaterialLighting  lighting;
    short               refs;
    short               id;
};

struct RwSurfaceProperties
{
    float ambient;
    // GTA Flags
    union
    {
        float specular;
        unsigned int m_dwFlags; /* HAS_ENV_MAP   = 0x00000001,
                                HAS_ENV_MAP_X = 0x00000002,
                                HAS_SPECULAR  = 0x00000004 */
    };
    float diffuse;
};

class CBreakableGeometry
{
public:
    unsigned int         m_uiPosRule;
    unsigned short       m_usNumVertices;
    char                 _pad0[2];
    RwV3d               *m_pVertexPos;
    RwTextureCoordinates *m_pTexCoors;
    RwColor              *m_pVertexColors;
    unsigned short       m_usNumTriangles;
    char                 _pad1[2];
    RpTriangle          *m_pTriangles;
    unsigned short      *m_pMaterialAssignments;
    unsigned short       m_usNumMaterials;
    char                 _pad2[2];
    RwTexture          **m_pTextures;
    char                *m_pTextureNames;
    char                *m_pMaskNames;
    RwSurfaceProperties *m_pMaterialProperties;
    /* some data here with random size
    RwV3d                m_avVertexPos[m_usNumVertices];
    RwTexCoords          m_asTexCoords[m_usNumVertices];
    RwRGBA               m_asVertexColors[m_usNumVertices];
    RpTriangle           m_asTriangles[m_usNumTriangles];
    unsigned short       m_ausMaterialAssignments[m_usNumTriangles];
    char                 m_acTextureNames[m_usNumMaterials][32];
    char                 m_acMaskNames[m_usNumMaterials][32];
    RwSurfaceProperties  m_asMaterialProperties[m_usNumMaterials];
    */
};
class C2dfxStore
{
public:
    unsigned int m_uiNum2dfx;
    /* Data with random size here
    C2dfx        m_as2dfx[m_uiNumEffects];
    */
};

struct RpMaterials
{
    RpMaterial **materials;
    int        entries;
    int        unknown;
};
struct RpMorphTarget
{
    RpGeometry *parentGeom;
    RwSphere    boundingSphere;
    RwV3d      *verts;
    RwV3d      *normals;
};
struct RpTriangle
{
    unsigned short v[3];
    unsigned short matId;
};

struct RwMeshCache
{
    int    lengthOfMeshesArray; /**< Number of meshes in the object */
    RwResEntry *meshes[1]; /**< The RwMeshCache structure will be
                           * allocated sufficiently big that this tail
                           * array can hold lengthOfMeshesArray pointers to
                           * \ref RwResEntry's */
};

struct RwResEntry
{
    RwLLLink       link;
    int        size;     /* RwResEntry + pad + data(+junk) */
    void          *owner;    /* RpGeometry */
    RwResEntry   **ownerRef; /* points back into RwMeshCache */
    void* destroyNotify;
};


struct RpGeometry
{
    RwObject             object;
    unsigned int         flags;
    unsigned short       unknown1;
    short                refs;

    unsigned int         triangles_size;
    unsigned int         vertices_size;
    unsigned int         morphTarget_size;
    unsigned int         texcoords_size;

    RpMaterials          materials;
    RpTriangle           *triangles;
    RwColor              *colors;
    RwTextureCoordinates *texcoords[RW_MAX_TEXTURE_COORDS];
    RpMeshHeader       *mesh;
    RwResEntry         *repEntry;
    RpMorphTarget      *morphTarget;
    bool isValidTriangleId(int triangleId)
    {
        return (triangleId != NULL && triangles_size >= triangleId);
    }
    bool isValidVertexId(int vertexId)
    {
        return (vertexId != NULL && vertices_size >= vertexId);
    }
    bool isValidTexCoordsId(int textCoordId)
    {
        return (textCoordId != NULL && texcoords_size >= textCoordId);
    }
};

/*****************************************************************************/
/** RenderWare I/O                                                          **/
/*****************************************************************************/

// RenderWare type definitions
typedef int          (* RwIOCallbackClose) (void *data);
typedef unsigned int (* RwIOCallbackRead)  (void *data, void *buffer, unsigned int length);
typedef int          (* RwIOCallbackWrite) (void *data, const void *buffer, unsigned int length);
typedef int          (* RwIOCallbackOther) (void *data, unsigned int offset);

// RenderWare enumerations
enum RwStreamType
{
    STREAM_TYPE_NULL = 0,
    STREAM_TYPE_FILE = 1,
    STREAM_TYPE_FILENAME = 2,
    STREAM_TYPE_BUFFER = 3,
    STREAM_TYPE_CALLBACK = 4,
    STREAM_TYPE_LAST = RW_STRUCT_ALIGN
};
enum RwStreamMode
{
    STREAM_MODE_NULL = 0,
    STREAM_MODE_READ = 1,
    STREAM_MODE_WRITE = 2,
    STREAM_MODE_APPEND = 3,
    STREAM_MODE_LAST = RW_STRUCT_ALIGN
};

// RenderWare base types
struct RwBuffer
{
    void            *ptr;
    unsigned int    size;
};
union RwStreamTypeData
{
    struct {
        unsigned int      position;
        unsigned int      size;
        void              *ptr_file;
    };
    struct {
        void              *file;
    };
    struct {
        RwIOCallbackClose callbackClose;
        RwIOCallbackRead  callbackRead;
        RwIOCallbackWrite callbackWrite;
        RwIOCallbackOther callbackOther;
        void              *ptr_callback;
    };
};
struct RwStream
{
    RwStreamType        type;
    RwStreamMode        mode;
    int                 pos;
    RwStreamTypeData    data;
    int                 id;
};
struct RwError
{
    int err1,err2;
};
#endif
