#ifndef INTERFACES_H
#define INTERFACES_H

#include "BlocoCore.h"


class Actor;
class ActorComponent;

typedef unsigned int ActorId;
typedef unsigned int ComponentId;

const ActorId INVALID_ACTOR_ID = 0;
const ComponentId INVALID_COMPONENT_ID = 0;


typedef shared_ptr<Actor> StrongActorPtr;
typedef weak_ptr<Actor> WeakActorPtr;
typedef shared_ptr<ActorComponent> StrongActorComponentPtr;
typedef weak_ptr<ActorComponent> WeakActorComponentPtr;

typedef std::string ActorType;

class BLOCOCORE_API ICamera;

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
public:
	virtual ActorId	GetId(void)=0;

	virtual Mat* GetGlobalMatrix()=0;
	virtual Mat* GetLocalMatrix()=0;
	virtual Mat  GetActorTransform()=0;

	virtual void SetLocalMatrix(Mat value)=0;

	virtual void SetTranslationInternal(Vec value)=0;
	virtual void SetTranslationInternal(Mat value)=0;
	virtual void SetRotationInternal(Vec value)=0;
	virtual void SetRotationInternal(Mat value)=0;
	virtual void SetScalingInternal(Vec value)=0;
	virtual void SetScalingInternal(Mat value)=0;


	virtual void Move(Vec value)=0;
	virtual void Move(Mat value)=0;
	virtual void Rotate(Vec value)=0;
	virtual void Rotate(Mat value)=0;
	virtual void Scale(Vec value)=0;
	virtual void Scale(Mat value)=0;

	virtual void SetTranslation(Vec value)=0;
	virtual void SetTranslation(Mat value)=0;
	virtual void SetRotation(Vec value)=0;
	virtual void SetRotation(Mat value)=0;
	virtual void SetScaling(Vec value)=0;
	virtual void SetScaling(Mat value)=0;

	virtual Mat  GetTranslation()=0;
	virtual Mat  GetRotation()=0;
	virtual Mat  GetScaling()=0;
};

class BLOCOCORE_API IGamePhysics;

enum BLOCOCORE_API GameViewType
{
	GameView_Human,
	GameView_Remote,
	GameView_AI,
	GameView_Recorder,
	GameView_Other
};

typedef unsigned int BLOCOCORE_API GameViewId;
const GameViewId INVALID_GAMEVIEW_ID = 0xffffffff;

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

	virtual void VSetCamera( ICamera* pCamera )=0;
	virtual ICamera* VGetCamera()=0;

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
	virtual Mat  GetProjection() = 0;
	virtual Mat  GetView()       = 0;
	virtual void GetDirectionFrom2D(Vec screenCoord, Vec* direction, Vec* position ) {}
};

class BLOCOCORE_API IScene 
{
public:
	virtual ICamera* GetCamera() = 0;
};
class BLOCOCORE_API Scene;
class BLOCOCORE_API SceneNodeProperties;
class BLOCOCORE_API RayCast;

#endif
