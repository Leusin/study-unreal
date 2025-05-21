// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StudentData.generated.h"

USTRUCT()
struct FStudentData
{
	GENERATED_BODY()

	FStudentData()
		: Name(TEXT("홍길동")), Order(-1)
	{
	}

	FStudentData(const FString& InName, int32 InOrder)
		: Name(InName), Order(InOrder)
	{
	}

	bool operator==(const FStudentData& InOther) const
	{
		return Order == InOther.Order;
	}

	friend FORCEINLINE uint32 GetTypeHash(const FStudentData& InStudentData)
	{
		return GetTypeHash(InStudentData.Order);
	}

	friend FArchive& operator<<(FArchive& Ar, FStudentData& InStudentData)
	{
		Ar << InStudentData.Order;
		Ar << InStudentData.Name;
		return Ar;
	}

	UPROPERTY()
	FString Name;

	UPROPERTY()
	int32 Order;
};

FString MakeRandomName();