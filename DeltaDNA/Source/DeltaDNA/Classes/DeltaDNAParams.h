// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "DeltaDNAParams.generated.h"


USTRUCT()
struct DELTADNA_API FDeltaDNAParameter
{
	GENERATED_BODY()
	
	enum ParameterType
	{
		STRING,
		INT,
		FLOAT,
		BOOL,
	};


	FString Key;

	FString stringValue;
	int intValue;
	float floatValue;
	bool boolValue;

	ParameterType type;

	FDeltaDNAParameter()
	{
		Key = "";
	}

	FDeltaDNAParameter(FString key, FString value)
	{
		Key = key;
		stringValue = value;
		type = ParameterType::STRING;
	}

	FDeltaDNAParameter(FString key, int value)
	{
		Key = key;
		intValue = value;
		type = ParameterType::INT;
	}

	FDeltaDNAParameter(FString key, float value)
	{
		Key = key;
		floatValue = value;
		type = ParameterType::FLOAT;
	}

	FDeltaDNAParameter(FString key, bool value)
	{
		Key = key;
		boolValue = value;
		type = ParameterType::BOOL;
	}

	void AddParameterTo(FJsonObject * eventParam)
	{
		if (type == ParameterType::STRING)
			eventParam->SetStringField(Key, stringValue);
		else if (type == ParameterType::INT)
			eventParam->SetNumberField(Key, intValue);
		else if (type == ParameterType::FLOAT)
			eventParam->SetNumberField(Key, floatValue);
		else if (type == ParameterType::BOOL)
			eventParam->SetBoolField(Key, boolValue);
	}
};