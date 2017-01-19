// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"

#include "DeltaDNAManager.h"


#include "DeltaDNAGameInstance.generated.h"

/**
 * 
 */

UCLASS()
class FARAWAY_API UDeltaDNAGameInstance : public UGameInstance
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
	UPROPERTY(EditAnywhere, Category = "DeltaDNA Data")
		bool useLocalUtcTimestamp;

	DeltaDNAManager * mgr;
	
	void Init() override;

	void LaunchEvent(DeltaDNAEvent * dnaEvent);
};
