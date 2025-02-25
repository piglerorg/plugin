/**
 * Copyright (c) 2023-2024 Arman Jussupgaliyev
 * Copyright (c) 2023 Mathew (curoviyxru)
 */

#ifndef PIGLERPROTOCOL
#define PIGLERPROTOCOL
#include <e32base.h>

enum TPiglerCommands {
	EInitApp = 1,
	ESetItem,
	ERemoveItem,
	ERemoveAppItems,
	EGetAppItems,
	EGetLastTappedAppItem,
	ESetRemoveItemOnTap,
	ESetItemIcon,
	EHandleTap, // client side
	EGetAPIVersion, // v2
	ESetLaunchOnTap,
	EGetItem,
	EGetNotificationsCount, // v3
	EGetMaxNotificationsCount, // v4
	EGetGlobalNotificationsCount,
	ERemoveApp,
	EGetBitmapSize,
	EGetTextLines, // v5
};

// DO NOT CHANGE!
struct TPiglerMessage
{
	TInt uid;
	TBuf<64> appName;
	TBuf<256> text;
	TInt argument; // removeOnTap or appId
};

#endif
