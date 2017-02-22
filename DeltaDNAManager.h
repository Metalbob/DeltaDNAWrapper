#pragma once


#include <Runtime/Online/HTTP/Public/Http.h>

#include "DeltaDNAEvent.h"

UENUM(BlueprintType)
enum class EEnvironment : uint8
{
	DEV 	UMETA(DisplayName = "Dev"),
	LIVE 	UMETA(DisplayName = "Live"),
};

class DeltaDNAManager
{

	FString urlCollect;
	FString urlEngage;
	FString keyDev;
	FString keyLive;

	EEnvironment environment;
//	bool useLocalUtcTimestamp;
	bool bulkEventUseHash;

public:

	DeltaDNAManager(FString urlCollect, FString urlEngage, FString keyDev, FString keyLive, EEnvironment environment/*, bool useLocalUtcTimestamp*/, bool bulkEventUseHash);

	bool LaunchEvent(UDeltaDNAEvent * dnaEvent);
	bool LaunchBulkEvent(UDeltaDNABulkEvent * dnaEvent);
	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
};
