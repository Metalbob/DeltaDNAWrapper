#include "FarAway.h"
#include "DeltaDNAEvent.h"

UDeltaDNAEvent::UDeltaDNAEvent()
{
	isUsable = false;
}

UDeltaDNAEvent::UDeltaDNAEvent(FString eventName, FString userID, EPlatform platform, bool useLocalUtcTimestamp, FString eventUUID, FString sessionID) :
	eventName{ eventName }, userID{ userID }, sessionID{ sessionID }, platform{ platform }, eventUUID{ eventUUID }, useLocalUtcTimestamp{ useLocalUtcTimestamp }
{
	
	const UEnum* platformEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlatform"));
	eventParams = MakeShareable(new FJsonObject);
	eventParams->SetStringField("platform", platformEnum->GetEnumName((int32)platform));

	if (useLocalUtcTimestamp)
	{
		FDateTime now = FDateTime::UtcNow();
		timestamp = FString::Printf(TEXT("%d-%02d-%02d %02d:%02d:%02d.%03d"),
			now.GetYear(), now.GetMonth(), now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond(), now.GetMillisecond());
	}

	isUsable = true;
}

void UDeltaDNAEvent::SetBaseInformation(FString peventName, FString puserID, EPlatform pplatform, bool puseLocalUtcTimestamp, FString peventUUID, FString psessionID)
{
	this->eventName = peventName;
	this->userID = puserID;
	this->sessionID = psessionID;
	this->platform = pplatform;
	this->eventUUID = peventUUID;
	this->useLocalUtcTimestamp = puseLocalUtcTimestamp;

	if (useLocalUtcTimestamp)
	{
		FDateTime now = FDateTime::UtcNow();
		timestamp = FString::Printf(TEXT("%d-%02d-%02d %02d:%02d:%02d.%03d"),
			now.GetYear(), now.GetMonth(), now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond(), now.GetMillisecond());
	}

	const UEnum* platformEnum = FindObject<UEnum>(ANY_PACKAGE, TEXT("EPlatform"));
	eventParams = MakeShareable(new FJsonObject);
	eventParams->SetStringField("platform", platformEnum->GetEnumName((int32)platform));
	isUsable = true;
}

void UDeltaDNAEvent::AddStringParam(FString key, FString value)
{
	this->eventParams->SetStringField(key, value);
}

void UDeltaDNAEvent::AddIntParam(FString key, int value)
{
	this->eventParams->SetNumberField(key, value);
}

void UDeltaDNAEvent::AddFloatParam(FString key, float value)
{
	this->eventParams->SetNumberField(key, value);
}

void UDeltaDNAEvent::AddBoolParam(FString key, bool value)
{
	this->eventParams->SetBoolField(key, value);
}

UDeltaDNAEvent::~UDeltaDNAEvent()
{
}


void UDeltaDNABulkEvent::AddEvent(UDeltaDNAEvent * dnaEvent)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	JsonObject->SetStringField("eventName", dnaEvent->GetEventName());
	JsonObject->SetStringField("userID", dnaEvent->GetUserID());
	if (dnaEvent->GetSessionID() != "")
		JsonObject->SetStringField("sessionID", dnaEvent->GetSessionID());
	if (dnaEvent->GetEventID() != "")
		JsonObject->SetStringField("eventID", dnaEvent->GetEventID());

	if (dnaEvent->GetUseLocalUtcTimestamp())
	{
		JsonObject->SetStringField("eventTimestamp", dnaEvent->GetTimestamp());
	}
	JsonObject->SetObjectField("eventParams", dnaEvent->GetEventParams());

	TSharedRef< FJsonValueObject > JsonValue = MakeShareable(new FJsonValueObject(JsonObject));

	events.Add(JsonValue);
}
