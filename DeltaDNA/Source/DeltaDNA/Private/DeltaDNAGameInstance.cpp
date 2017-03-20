#include "DeltaDNA.h"
#include "DeltaDNAGameInstance.h"

void UDeltaDNAGameInstance::Init()
{
	mgr = new DeltaDNAManager(urlCollect, urlEngage, keyDev, keyLive, environment/*, useLocalUtcTimestamp,*/, bulkEventUseHash);
}

bool UDeltaDNAGameInstance::LaunchEvent(UDeltaDNAEvent * dnaEvent)
{
	return mgr->LaunchEvent(dnaEvent);
}

bool UDeltaDNAGameInstance::LaunchBulkEvent(UDeltaDNABulkEvent * dnaBulkEvent)
{
	return mgr->LaunchBulkEvent(dnaBulkEvent);
}

UDeltaDNAEvent * UDeltaDNAGameInstance::CreateDeltaDNAEvent(
	FString eventName,
	FString userID,
	EPlatform platform,
	bool useLocalUtcTimestamp,
	bool & success,
	TArray<FDeltaDNAParam> params,
	FString eventUUID,
	FString sessionID)
{
	UDeltaDNAEvent * ev = NewObject<UDeltaDNAEvent>();

	if (ev == nullptr)
	{
		success = false;
		return nullptr;
	}

	ev->SetBaseInformation(eventName, userID, platform, useLocalUtcTimestamp,eventUUID, sessionID);

	for (int i = 0; i < params.Num(); i++)
		params[i].AddParameterTo(ev->GetEventParams().Get());

	success = true;
	return ev;
}

UDeltaDNABulkEvent * UDeltaDNAGameInstance::CreateDeltaDNABulkEvent(TArray<UDeltaDNAEvent*> params, bool & success)
{
	UDeltaDNABulkEvent * ev = NewObject<UDeltaDNABulkEvent>();

	if (ev == nullptr)
	{
		success = false;
		return nullptr;
	}

	for (int i = 0; i < params.Num(); i++)
		ev->AddEvent(params[i]);

	success = true;
	return ev;
}
