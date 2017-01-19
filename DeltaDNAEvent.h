#pragma once

/**
 * 
 */
#include <Runtime/Core/Public/Templates/SharedPointer.h>

UENUM()
enum class EPlatform : uint8
{
	IOS_MOBILE,
	IOS_TABLET,
	IOS_TV,
	ANDROID, 
	ANDROID_MOBILE, 
	ANDROID_TABLET, 
	ANDROID_CONSOLE, 
	WINDOWS_MOBILE, 
	WINDOWS_TABLET, 
	BLACKBERRY_MOBILE, 
	BLACKBERRY_TABLET, 
	FACEBOOK,
	WEB,
	PC_CLIENT,
	MAC_CLIENT,
	PS3,
	PS4,
	PSVITA,
	XBOX360,
	XBOXONE,
	IOS,
	UNKNOWN
};

class FARAWAY_API DeltaDNAEvent
{
protected:
	FString eventName;
	FString userID;
	FString eventUUID;
	FString sessionID;
	EPlatform platform;
	TSharedPtr<FJsonObject> eventParams;

public:
	DeltaDNAEvent(FString eventName, FString userID, EPlatform platform, FString eventUUID = "", FString sessionID = "");

	FString GetEventName() { return eventName; }
	FString GetUserID() { return userID; }
	FString GetEventID() { return eventUUID; }
	FString GetSessionID() { return sessionID; }
	TSharedPtr<FJsonObject> GetEventParams() { return eventParams; }

	~DeltaDNAEvent();
};
