#ifndef PIGLERTAPSERVER
#define PIGLERTAPSERVER
#include <e32base.h>
#include "PiglerProtocol.h"

class IPiglerTapHandler {
public:
	virtual void handleTap(TInt uid, TBuf<64> appName, TBuf<256> text, TBool remove) = 0;
};

NONSHARABLE_CLASS(CPiglerTapServer): public CServer2
{
private:
	IPiglerTapHandler *handler;
	CSession2* NewSessionL(const TVersion& version, const RMessage2& message) const;
	
public:
	CPiglerTapServer();
	void SetHandler(IPiglerTapHandler *handler);
};

NONSHARABLE_CLASS(CPiglerTapSession): public CSession2
{
private:
	IPiglerTapHandler *handler;
	TPiglerMessage ReadMessage(const RMessage2& message);

public:
	CPiglerTapSession(IPiglerTapHandler *handler);
	void ServiceL(const RMessage2& message);
	void ServiceError(const RMessage2& message, TInt error);
};
#endif
