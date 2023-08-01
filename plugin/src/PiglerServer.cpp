#include "PiglerServer.h"
#include "PiglerPlugin.h"

TInt CPiglerTapSession::Connect(TBuf<64> aAppName)
{
	TBuf<128> serverName(_L("PiglerHandler_"));
	serverName.Append(aAppName);
	return CreateSession(serverName, TVersion(1, 0, 0));
}

TInt CPiglerTapSession::SendMessage(TInt function, const TPiglerMessage aMessage)
{
	TPckg<TPiglerMessage> data(aMessage);
	TIpcArgs args(&data);
	return SendReceive(function, args);
}

void CPiglerTapSession::Close()
{
	RSessionBase::Close();
}

CPiglerServer::CPiglerServer(PiglerPlugin* plugin) :
	CServer2(EPriorityStandard), iPlugin(plugin)
{
}

CSession2* CPiglerServer::NewSessionL(const TVersion& version, const RMessage2& message) const
{
	return new (ELeave) CPiglerSession(iPlugin);
}

CPiglerSession::CPiglerSession(PiglerPlugin* aPlugin) :
	CSession2(), iPlugin(aPlugin)
{
}

void CPiglerSession::ServiceL(const RMessage2& aMessage)
{
	switch (aMessage.Function()) {
	case EInitApp:
	{
		iPlugin->InitApp(ReadMessage(aMessage), aMessage.SecureId().iId);
		aMessage.Complete(KErrNone);
	}
	break;
	case ESetItem:
	{
		aMessage.Complete(iPlugin->SetItem(ReadMessage(aMessage)));
	}
	break;
	case ERemoveItem:
	{
		aMessage.Complete(iPlugin->RemoveItem(ReadMessage(aMessage)));
	}
	break;
	case ERemoveAppItems:
	{
		aMessage.Complete(iPlugin->RemoveItems(ReadMessage(aMessage)));
	}
	break;
	case EGetLastTappedAppItem:
	{
		aMessage.Complete(iPlugin->GetLastTappedAppItem(ReadMessage(aMessage)));
	}
	break;
	case ESetRemoveItemOnTap:
	{
		aMessage.Complete(iPlugin->SetRemoveItemOnTap(ReadMessage(aMessage)));
	}
	break;
	case ESetItemIcon:
	{
		TPiglerMessage message;
		TPckg<TPiglerMessage> data(message);
		aMessage.ReadL(0, data);
		HBufC8* iconBuf = HBufC8::NewL(aMessage.GetDesLengthL(1));
		TPtr8 bufPtr(iconBuf->Des());
		aMessage.ReadL(1, bufPtr);
		aMessage.Complete(iPlugin->SetItemIcon(message, iconBuf));
	}
	break;
	default:
	{
		aMessage.Complete(KErrNotFound);
	}
	}
}

TPiglerMessage CPiglerSession::ReadMessage(const RMessage2& aMessage) {
	TPiglerMessage message;
	TPckg<TPiglerMessage> data(message);
	aMessage.ReadL(0, data);
	return message;
}

void CPiglerSession::ServiceError(const RMessage2& aMessage, TInt aError)
{
	aMessage.Complete(aError);
}
