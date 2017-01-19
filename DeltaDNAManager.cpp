#include "FarAway.h"

#include "DeltaDNAManager.h"

#include <Runtime/Core/Public/Templates/SharedPointer.h>

// Sets default values
DeltaDNAManager::DeltaDNAManager(FString urlCollect, FString urlEngage, FString keyDev, FString keyLive, EEnvironment environment, bool useLocalUtcTimestamp)
{
	this->urlCollect = urlCollect;
	this->urlEngage = urlEngage;
	this->keyDev = keyDev;
	this->keyLive = keyLive;

	this->environment = environment;
	this->useLocalUtcTimestamp = useLocalUtcTimestamp;
}

void DeltaDNAManager::LaunchEvent(DeltaDNAEvent * dnaEvent)
{
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

	if (useLocalUtcTimestamp)
	{
		FDateTime now = FDateTime::UtcNow();
		JsonObject->SetStringField("eventTimestamp", FString::Printf(TEXT("%d-%02d-%02d %02d:%02d:%02d.%03d"),
				now.GetYear(), now.GetMonth(), now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond(), now.GetMillisecond()));
		UE_LOG(LogTemp, Warning, TEXT("%d-%02d-%02d %02d:%02d:%02d.%03d"),
			now.GetYear(), now.GetMonth(), now.GetDay(), now.GetHour(), now.GetMinute(), now.GetSecond(), now.GetMillisecond());
	}

	JsonObject->SetObjectField("eventParams", dnaEvent->GetEventParams());

	FString OutputString;
	TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);
	request->SetContentAsString(OutputString);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *OutputString);
//	request->OnProcessRequestComplete().BindUObject(this, &ADeltaDNAManager::OnResponseReceived);
	request->OnProcessRequestComplete().BindRaw(this, &DeltaDNAManager::OnResponseReceived);
	
	if (request->ProcessRequest())
	{
		UE_LOG(LogTemp, Warning, TEXT("Request OK"));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Request NOT OK"));
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