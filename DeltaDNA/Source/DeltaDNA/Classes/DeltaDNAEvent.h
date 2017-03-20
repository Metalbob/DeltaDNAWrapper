#pragma once

/**
 * 
 */

#include <Runtime/Core/Public/Templates/SharedPointer.h>

#include "DeltaDNAParams.h"


#include "DeltaDNAEvent.generated.h"


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

UCLASS(Blueprintable)
class DELTADNA_API UDeltaDNAEvent : public UObject
{
	GENERATED_BODY()

	bool isUsable;

protected:
	FString eventName;
	FString userID;
	FString eventUUID;
	FString sessionID;
	EPlatform platform;
	FString timestamp;
	TSharedPtr<FJsonObject> eventParams;
	bool useLocalUtcTimestamp;

public:

	UDeltaDNAEvent();
	UDeltaDNAEvent(FString eventName, FString userID, EPlatform platform, bool useLocalUtcTimestamp, FString eventUUID = "", FString sessionID = "");

	FString GetEventName() { return eventName; }
	FString GetUserID() { return userID; }
	FString GetEventID() { return eventUUID; }
	FString GetSessionID() { return sessionID; }
	FString GetTimestamp() { return timestamp; }
	TSharedPtr<FJsonObject> GetEventParams() { return eventParams; }
	bool GetUseLocalUtcTimestamp() { return useLocalUtcTimestamp; }

	bool IsUsable() { return isUsable; }

	void SetBaseInformation(FString eventName, FString userID, EPlatform platform, bool useLocalUtcTimestamp, FString eventUUID, FString sessionID);


	UFUNCTION(BlueprintCallable, Category = "DeltaDNA")
		void AddStringParam(FString key, FString value);

	UFUNCTION(BlueprintCallable, Category = "DeltaDNA")
		void AddIntParam(FString key, int value);

	UFUNCTION(BlueprintCallable, Category = "DeltaDNA")
		void AddFloatParam(FString key, float value);

	UFUNCTION(BlueprintCallable, Category = "DeltaDNA")
		void AddBoolParam(FString key, bool value);

	UFUNCTION(BlueprintPure, Category = "DeltaDNA")
	static FDeltaDNAParam CreateStringParam(FString key, FString value)
	{
		return FDeltaDNAStringParam(key, value);
	}

	UFUNCTION(BlueprintPure, Category = "DeltaDNA")
	static FDeltaDNAParam CreateIntParam(FString key, int value)
	{
		return FDeltaDNAIntParam(key, value);
	}

	UFUNCTION(BlueprintPure, Category = "DeltaDNA")
	static FDeltaDNAParam CreateFloatParam(FString key, float value)
	{
		return FDeltaDNAFloatParam(key, value);
	}

	UFUNCTION(BlueprintPure, Category = "DeltaDNA")
	static FDeltaDNAParam CreateBoolParam(FString key, bool value)
	{
		return FDeltaDNABoolParam(key, value);
	}

	~UDeltaDNAEvent();

};

UCLASS(Blueprintable)
class DELTADNA_API UDeltaDNABulkEvent : public UObject
{
	GENERATED_BODY()

	TArray<TSharedPtr<FJsonValue>> events;
public:

	UFUNCTION(BlueprintCallable, Category = "DeltaDNA")
		void AddEvent(UDeltaDNAEvent * eventToAdd);

	TArray<TSharedPtr<FJsonValue>> GetEvents() { return events; }
};
