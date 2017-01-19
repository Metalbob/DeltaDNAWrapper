// Fill out your copyright notice in the Description page of Project Settings.

#include "FarAway.h"
#include "DeltaDNAGameInstance.h"

void UDeltaDNAGameInstance::Init()
{
	mgr = new DeltaDNAManager(urlCollect, urlEngage, keyDev, keyLive, environment, useLocalUtcTimestamp);


	DeltaDNAEvent ev("newPlayer", "0", EPlatform::PC_CLIENT, "", "0");
	LaunchEvent(&ev);
}

void UDeltaDNAGameInstance::LaunchEvent(DeltaDNAEvent * dnaEvent)
{
	mgr->LaunchEvent(dnaEvent);
}
