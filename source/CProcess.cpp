#include "BlocoCore.h"

const int BLOCOCORE_API PROCESS_FLAG_ATTACHED	= 0x00000001;

CProcess::CProcess(int ntype, unsigned int uOrder /* = 0 */) : 
	m_iType( ntype ),
	m_bKill( false ),
	m_bActive( true ),
	m_uProcessFlags( 0 ),
	m_bPaused( false ),
	m_bInitialUpdate( true )
{};
CProcess::~CProcess()
{

}

void CProcess::VOnUpdate(const int deltaMilliseconds)
{
	if (m_bInitialUpdate)
	{
		VOnInitialize();
		m_bInitialUpdate = false;
	}
}
bool CProcess::IsAttached() const 
{
	return (m_uProcessFlags & PROCESS_FLAG_ATTACHED) ? true : false;
}
void CProcess::SetAttached(const bool wantAttached)
{
	if(wantAttached)
	{
		m_uProcessFlags |= PROCESS_FLAG_ATTACHED;
	}
	else
	{
		m_uProcessFlags &= ~PROCESS_FLAG_ATTACHED;
	}
}