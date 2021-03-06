#ifndef CProcessManager_h__
#define CProcessManager_h__

#include "BlocoCore.h"

typedef list<shared_ptr<CProcess>> BLOCOCORE_API ProcessList;
class BLOCOCORE_API CProcessManager
{
public:
	void Attach (shared_ptr<CProcess> pProcess);

	bool HasProcesses();
	bool IsProcessActive(int nType);

	void UpdateProcesses(int deltaMilliseconds);
	~CProcessManager();

protected:
	ProcessList m_ProcessList;

private:
	void Detach (shared_ptr<CProcess> pProcess);
};

#endif // CProcesssManager_h__
