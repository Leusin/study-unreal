// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HELLOUNREAL_API FStudentManager : public FGCObject
{
public:
	FStudentManager();
	FStudentManager(class UStudent* InStudent);

	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	virtual FString GetReferencerName() const override
	{
		return TEXT("FStudentManager");
	}

	FORCEINLINE const class UStudent* GetStudent() const 
	{
		return ManagedStudent; 
	}

private:
	class UStudent* ManagedStudent = nullptr;
};
