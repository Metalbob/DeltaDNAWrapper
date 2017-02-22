// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DeltaDNAParams.generated.h"


USTRUCT()
struct FDeltaDNAParam
{
	GENERATED_BODY()

	FString Key;

	FDeltaDNAParam()
	{
		Key = "";
	}

	FDeltaDNAParam(FString key)
	{
		Key = key;
	}

	virtual void AddParameterTo(FJsonObject * eventParam) PURE_VIRTUAL(FDeltaDNAParam::AddParameterTo, ;);
};

USTRUCT()
struct FDeltaDNAStringParam : public FDeltaDNAParam
{
	GENERATED_BODY()

	FString Value;

	FDeltaDNAStringParam()
	{
		Value = "";
	}

	FDeltaDNAStringParam(FString key, FString value)
	{
		Key = key;
		Value = value;
	}

	void AddParameterTo(FJsonObject * eventParam) override
	{
		eventParam->SetStringField(Key, Value);
	}
};

USTRUCT()
struct FDeltaDNAIntParam : public FDeltaDNAParam
{
	GENERATED_BODY()

	int Value;

	FDeltaDNAIntParam()
	{
		Value = 0;
	}

	FDeltaDNAIntParam(FString key, int value)
	{
		Key = key;
		Value = value;
	}

	void AddParameterTo(FJsonObject * eventParam) override
	{
		eventParam->SetNumberField(Key, Value);
	}
};

USTRUCT()
struct FDeltaDNAFloatParam : public FDeltaDNAParam
{
	GENERATED_BODY()

	float Value;

	FDeltaDNAFloatParam()
	{
		Value = 0;
	}

	FDeltaDNAFloatParam(FString key, float value)
	{
		Key = key;
		Value = value;
	}

	void AddParameterTo(FJsonObject * eventParam) override
	{
		eventParam->SetNumberField(Key, Value);
	}
};

USTRUCT()
struct FDeltaDNABoolParam : public FDeltaDNAParam
{
	GENERATED_BODY()

	bool Value;

	FDeltaDNABoolParam()
	{
		Value = false;
	}

	FDeltaDNABoolParam(FString key, bool value)
	{
		Key = key;
		Value = value;
	}

	void AddParameterTo(FJsonObject * eventParam) override
	{
		eventParam->SetBoolField(Key, Value);
	}
};