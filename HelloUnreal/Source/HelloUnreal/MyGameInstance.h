// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StudentData.h"
#include "MyGameInstance.generated.h"


/**
 * 
 */
UCLASS()
class HELLOUNREAL_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UMyGameInstance();

	virtual void Init() override;
	
private:
	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;

	UPROPERTY()
	FString SchoolName;

	TArray<struct FStudentData> StudentsData;

	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;

	TMap<int32, FString> StudentsMap;
};
