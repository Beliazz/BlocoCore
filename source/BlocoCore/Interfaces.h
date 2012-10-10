#ifndef INTERFACES_H
#define INTERFACES_H

#include "BlocoCore.h"

template<class T>
struct SortBy_SharedPtr_Content
{
	bool operator()(const shared_ptr<T> &lhs, const shared_ptr<T> &rhs) const
	{ return *lhs < *rhs; }
};

class BLOCOCORE_API IScreenElement
{
public:
	virtual HRESULT VOnRestore() = 0;
	virtual HRESULT VOnRender(double fTime, float fElapsedTime) = 0;
	virtual void VOnUpdate(int deltaMilliseconds) = 0;

	virtual int VGetZOrder() const = 0;
	virtual void VSetZOrder(int const zOrder) = 0;
	virtual bool VIsVisible() const = 0;
	virtual void VSetVisible(bool visible) = 0;

	virtual LRESULT CALLBACK VOnMsgProc( AppMsg msg )=0;

	virtual ~IScreenElement() { };
	virtual bool const operator <(IScreenElement const &other) { return VGetZOrder() < other.VGetZOrder(); }
};

typedef unsigned int BLOCOCORE_API ActorId;
class BLOCOCORE_API ActorParams;

class BLOCOCORE_API IActor
{
	friend class IGame;

public:
	// Yuk-these shouldn't be public
	virtual void VSetMat(  Mat newMat )=0;
	virtual void VSetID( ActorId id )=0;
	virtual void VTransform( Mat value )=0;

public:
	virtual ~IActor() { }
	virtual Mat* VGetMat()=0;
	virtual const int VGetType()=0;
	virtual ActorId VGetID()=0; 
	virtual shared_ptr<ActorParams> VGetParams()=0;
	virtual bool VIsPhysical()=0;
	virtual bool VIsGeometrical()=0;
	virtual void VOnUpdate(int deltaMilliseconds)=0;
	virtual void VRotateY(float angleRadians) = 0;
};


class BLOCOCORE_API IGamePhysics;

class BLOCOCORE_API IGameLogic
{
public:
	virtual shared_ptr<IActor> VGetActor(const ActorId id)=0;
	virtual void VAddActor(shared_ptr<IActor> actor, class ActorParams *p)=0;
	virtual void VRemoveActor(ActorId id)=0;
	virtual bool VLoadGame(std::string gameName)=0;
	virtual void VSetProxy()=0;				
	virtual void VOnUpdate(float time, float elapsedTime)=0;
	virtual void VChangeState(enum BaseGameState newState)=0;
	virtual void VTransformActor(const ActorId id, Mat const &mat)=0;
	virtual shared_ptr<IGamePhysics> VGetGamePhysics(void) = 0;

	// 
	virtual void VBuildInitialScene()=0;
};


enum BLOCOCORE_API GameViewType
{
	GameView_Human,
	GameView_Remote,
	GameView_AI,
	GameView_Recorder,
	GameView_Other
};

typedef unsigned int BLOCOCORE_API GameViewId;


class BLOCOCORE_API IGameView 
{
public:
	virtual HRESULT VOnRestore()=0;
	virtual void VOnRender(double fTime, float fElapsedTime)=0;
	virtual void VOnLostDevice()=0;
	virtual GameViewType VGetType()=0;
	virtual GameViewId VGetId() const=0;
	virtual void VOnAttach(GameViewId vid, optional<ActorId> aid)=0;

	virtual LRESULT CALLBACK VOnMsgProc( AppMsg msg )=0;
	virtual void VOnUpdate( int deltaMilliseconds )=0;

	virtual ~IGameView() { };
};



typedef std::list<shared_ptr<IScreenElement> > BLOCOCORE_API ScreenElementList;
typedef std::list<shared_ptr<IGameView> > BLOCOCORE_API GameViewList;


class BLOCOCORE_API IJoystickHandler
{
	virtual bool VOnButtonDown(int const button, int const pressure)=0;
	virtual bool VOnButtonUp(int const button)=0;
	virtual bool VOnJoystick(float const x, float const y)=0;
};

class BLOCOCORE_API IGamepadHandler
{
	virtual bool VOnTrigger(bool const left, float const pressure)=0;
	virtual bool VOnButtonDown(int const button, int const pressure)=0;
	virtual bool VOnButtonUp(int const button)=0;
	virtual bool VOnDirectionalPad(int directionFlags)=0;
	virtual bool VOnThumbstick(int const stickNum, float const x, float const y)=0;
};


/////////////////////////////////////////////////////////////////////////////
// RenderPass Description
//
//   3D scenes are drawn in passes - this enum defines the render passes
//   supported by the 3D scene graph created by class Scene.
/////////////////////////////////////////////////////////////////////////////

enum BLOCOCORE_API RenderPass
{
	RenderPass_0,
	RenderPass_Static = RenderPass_0,
	RenderPass_Actor,
	RenderPass_Sky,
	RenderPass_Last
};

/////////////////////////////////////////////////////////////////////////////
// ISceneNode Description
//
//   This is the public interface for nodes in a 3D scene graph.
/////////////////////////////////////////////////////////////////////////////

class BLOCOCORE_API ICamera
{
public:
	Frustum	m_Frustum;
	Mat		m_Projection;
	Mat		m_View;

	virtual Mat GetProjection() = 0;
	virtual Mat GetView()       = 0;
	virtual Vec GetPosition()   = 0;

	virtual Frustum& GetFrustum() { return m_Frustum; }
};

class BLOCOCORE_API IScene 
{
public:
	virtual shared_ptr<ICamera> GetCamera() = 0;
};
class BLOCOCORE_API Scene;
class BLOCOCORE_API SceneNodeProperties;
class BLOCOCORE_API RayCast;

class BLOCOCORE_API ISceneNode
{
protected:

public:
	vector<shared_ptr<ISceneNode>> m_Children;
	ISceneNode *m_pParent;

	virtual SceneNodeProperties *  VGet()=0;
	vector<shared_ptr<ISceneNode>> GetChildren() { return m_Children; }
	virtual shared_ptr<ISceneNode> VFindChild( string name )= 0;


	virtual void VSetTransform(Mat toWorld= MatIdentity(), Mat fromWorld = MatIdentity()) = 0;
	virtual void VAddTransform(Mat value) = 0;

	virtual HRESULT VPreRender(Scene *pScene)=0;
	virtual HRESULT VRender(Scene *pScene)=0;
	virtual HRESULT VPostRender(Scene *pScene)=0;

	virtual bool VAddChild(shared_ptr<ISceneNode> kid)=0;
	virtual bool VRemoveChild(ActorId id)=0;
	virtual HRESULT VRenderChildren(Scene *pScene)=0;
	virtual HRESULT VOnRestore(Scene *pScene)=0;
	virtual bool VIsVisible(Scene *pScene) const=0;
	virtual HRESULT VPick(Scene *pScene, RayCast *pRayCast)=0;
	virtual bool VSetTexture( string filename, unsigned int index )=0;
	virtual void VSetSelected( bool value ) = 0;
	virtual bool VIsEnable() = 0;
	virtual void VSetEnable( bool value ) = 0;
	virtual void VSetStatic( bool value ) { }
	virtual HRESULT VOnUpdate(Scene *, DWORD const elapsedMs)=0;



	virtual ~ISceneNode() { };
};

/////////////////////////////////////////////////////////////////////////////
// IGamePhysics Description
//
//   The interface definition for a generic physics API.
/////////////////////////////////////////////////////////////////////////////

typedef std::list<Vec> BLOCOCORE_API VecList;
class btRigidBody;
class btCollisionShape;
class btCompoundShape;
class CKinematicController;
class BLOCOCORE_API IGamePhysics
{
public:

	// Initialization and Maintenance of the Physics World
	virtual bool VInitialize()=0;
	virtual void VSyncVisibleScene() = 0;
	virtual void VOnUpdate( float deltaSeconds ) = 0; 
	virtual void TogglePause(){}

	// find the rigid body associated with the given actor ID
	virtual btRigidBody * FindActorBody( ActorId id ) const { return NULL; };


	// Initialization of Physics Objects
	virtual void VAddPlane(Vec planeNormal, float planeConstante, IActor *actor, float specificGravity, enum PhysicsMaterial mat)=0;
	virtual void VAddSphere(float radius, IActor *actor, float specificGravity, enum PhysicsMaterial mat)=0;
	virtual void VAddBox(Vec dimensions, IActor *gameActor, float specificGravity, enum PhysicsMaterial mat) = 0;
	virtual void VAddPointCloud(Vec *verts, int numPoints, IActor *gameActor, float specificGravity, enum PhysicsMaterial mat)=0;
	virtual void VAddTriangleMesh(btCollisionShape* shape, IActor *gameActor, float specificGravity, enum PhysicsMaterial mat)=0;
	virtual void VSetCompoundShapeChild(ActorId parentID, IActor* childActor, unsigned int index)=0;
	virtual void VAddCompoundShape(btCompoundShape* shape, IActor *actor, float specificGravity, enum PhysicsMaterial mat) = 0;
	virtual void VRemoveActor(ActorId id)=0;
	virtual Vec  VRayCast( Vec start, Vec end, bool& hit ) =0;
	virtual void VAddKinematicController(shared_ptr<CKinematicController> kinematicController, IActor *actor, float specificGravity, enum PhysicsMaterial mat) = 0;

	// Debugging
	virtual void VRenderDiagnostics(IScene *pScene) = 0;
	virtual void DebugDrawWorld(bool value) {};
	virtual void VSetDebugMode( int mode ) {};

	// Physics world modifiers
	virtual void VCreateTrigger(Vec pos, const float dim, int triggerID)=0;
	virtual void VApplyForce(Vec dir, float newtons, ActorId aid)=0;
	virtual void VApplyTorque(Vec dir, float newtons, ActorId aid)=0;
	virtual bool VKinematicMove(Mat mat, ActorId aid)=0;

	// Physics actor states
	virtual void VRotateY(ActorId actorId, float angleRadians, float time) = 0;
	virtual float VGetOrientationY(ActorId actorId) = 0;
	virtual void VStopActor(ActorId actorId) = 0;
	virtual void VSetVelocity(ActorId actorId, Vec vel) = 0;
	virtual void VTranslate(ActorId actorId, Vec vec) = 0;
	virtual void VStaticActor( ActorId actorId ) = 0;

	virtual int GetNumKinematicController()		 { return 0; }
	virtual int GetNumPhysicActor()				 { return 0; }
	virtual int GetNumPhysicCompoundActor()		 { return 0; }
	virtual int GetNumPhysicCompoundChildActor() { return 0; }

	virtual float GetStepSimulationTime()		{ return 0.0f; }
	virtual float GetSyncVisualSceneTime()		{ return 0.0f; }
	virtual float GetKinematicControllerTime()	{ return 0.0f; }
	virtual float GetDebugDrawWorldTime()		{ return 0.0f; }

	virtual ~IGamePhysics() { };
};

#endif
