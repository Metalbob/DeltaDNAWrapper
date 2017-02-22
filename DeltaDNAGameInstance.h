// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"

#include "DeltaDNAManager.h"
#include "DeltaDNAParams.h"

#include "DeltaDNAGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class UDeltaDNAGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category = "DeltaDNA Data")
		FString urlCollect;
	UPROPERTY(EditAnywhere, Category = "DeltaDNA Data")
		FString urlEngage;
	UPROPERTY(EditAnywhere, Category = "DeltaDNA Data")
		FString keyDev;
	UPROPERTY(EditAnywhere, Category = "DeltaDNA Data")
		FString keyLive;

	UPROPERTY(EditAnywhere, Category = "DeltaDNA Data")
		EEnvironment environment;
	//UPROPERTY(EditAnywhere, Category = "DeltaDNA Data")
	//	bool useLocalUtcTimestamp;
	UPROPERTY(EditAnywhere, Category = "DeltaDNA Data")
		bool bulkEventUseHash;

	DeltaDNAManager * mgr;
	
	void Init() override;
public:
	UFUNCTION(BlueprintCallable, Category = "DeltaDNA")
		bool LaunchEvent(UDeltaDNAEvent * dnaEvent);

	UFUNCTION(BlueprintCallable, Category = "DeltaDNA")
		bool LaunchBulkEvent(UDeltaDNABulkEvent * dnaBulkEvent);

	UFUNCTION(BlueprintCallable, Category = "DeltaDNA", meta = (AutoCreateRefTerm = "params"))
		UDeltaDNAEvent * CreateDeltaDNAEvent(FString eventName, FString userID, EPlatform platform, bool useLocalUtcTimestamp, bool & success, TArray<FDeltaDNAParam> params, FString eventUUID = "", FString sessionID = "");

	UFUNCTION(BlueprintCallable, Category = "DeltaDNA", meta = (AutoCreateRefTerm = "params"))
		UDeltaDNABulkEvent * CreateDeltaDNABulkEvent(TArray<UDeltaDNAEvent*> params, bool & success);
};
