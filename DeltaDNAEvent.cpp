#include "FarAway.h"
#include "DeltaDNAEvent.h"

DeltaDNAEvent::DeltaDNAEvent(FString eventName, FString userID, EPlatform platform, FString eventUUID, FString sessionID) : 
	eventName {eventName}, userID{userID}, sessionID {sessionID}, platform {platform}, eventUUID{eventUUID}
{
	const UEnum* platformEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlatform"));
	eventParams = MakeShareable(new FJsonObject);
	eventParams->SetStringField("platform", platformEnum->GetEnumName((int32)platform));
}

DeltaDNAEvent::~DeltaDNAEvent()
{
}
