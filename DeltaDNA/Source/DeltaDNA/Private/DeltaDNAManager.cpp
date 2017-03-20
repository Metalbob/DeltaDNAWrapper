#include "DeltaDNA.h"

#include "DeltaDNAManager.h"

#include <Runtime/Core/Public/Templates/SharedPointer.h>

DeltaDNAManager::DeltaDNAManager(FString urlCollect, FString urlEngage, FString keyDev, FString keyLive, EEnvironment environment/*, bool useLocalUtcTimestamp*/, bool bulkEventUseHash)
{
	this->urlCollect = urlCollect;
	this->urlEngage = urlEngage;
	this->keyDev = keyDev;
	this->keyLive = keyLive;

	this->environment = environment;
	//this->useLocalUtcTimestamp = useLocalUtcTimestamp;
	this->bulkEventUseHash = bulkEventUseHash;
}

bool DeltaDNAManager::LaunchEvent(UDeltaDNAEvent * dnaEvent)
{
	if (dnaEvent == nullptr || !dnaEvent->IsUsable())
	{
		UE_LOG(LogTemp, Error, TEXT("The event failed to create or is not initialized"));
		return false;
	}

	TSharedRef<IHttpRequest> request = FHttpModule::Get().CreateRequest();
	request->SetVerb("POST");

	if (environment == EEnvironment::DEV)
		request->SetURL(urlCollect + "/" + keyDev + "/");
	else
		request->SetURL(urlCollect + "/" + keyLive + "/");
	
	request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

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

	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	request->SetContentAsString(OutputString);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputString);

	request->OnProcessRequestComplete().BindRaw(this, &DeltaDNAManager::OnResponseReceived);
	
	if (request->ProcessRequest())
	{
		UE_LOG(LogTemp, Warning, TEXT("Request OK"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Request NOT OK"));
		return false;
	}
}


bool DeltaDNAManager::LaunchBulkEvent(UDeltaDNABulkEvent * dnaBulkEvent)
{
	if (dnaBulkEvent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The bulk event failed to create or is null"));
		return false;
	}

	if (dnaBulkEvent->GetEvents().Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("The bulk event is empty"));
		return false;
	}

	TSharedRef<IHttpRequest> request = FHttpModule::Get().CreateRequest();
	request->SetVerb("POST");

	if (environment == EEnvironment::DEV)
		request->SetURL(urlCollect + "/" + keyDev + "/bulk" + ((bulkEventUseHash) ? "/hash/" : ""));
	else
		request->SetURL(urlCollect + "/" + keyLive + "/bulk" + ((bulkEventUseHash) ? "/hash/" : ""));

	request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	JsonObject->SetArrayField("eventList", dnaBulkEvent->GetEvents());

	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	request->SetContentAsString(OutputString);

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputString);

	request->OnProcessRequestComplete().BindRaw(this, &DeltaDNAManager::OnResponseReceived);

	if (request->ProcessRequest())
	{
		UE_LOG(LogTemp, Warning, TEXT("Request OK"));
		return true;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Request NOT OK"));
		return false;
	}

}


void DeltaDNAManager::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!Response.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Error: Unable to process HTTP Request!"));
	}
	else if (EHttpResponseCodes::IsOk(Response->GetResponseCode()))
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Response->GetContentAsString());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HTTP Error: %d - %s"), Response->GetResponseCode(), *Response->GetContentAsString());
	}
}