// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"
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

	virtual void Shutdown() override;
	
	void SaveStudentPackage() const;
	void LoadStudentPackage() const;
	void LoadStudentObject() const;

private:
	static const FString PackageName;
	static const FString AssetName;

	UPROPERTY()
	TObjectPtr<class UCourseInfo> CourseInfo;

	UPROPERTY()
	FString SchoolName;

	TArray<struct FStudentData> StudentsData;

	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> Students;

	TMap<int32, FString> StudentsMap;

	UPROPERTY()
	TObjectPtr<class UStudent> PropStudent;

	UPROPERTY()
	TArray<TObjectPtr<class UStudent>> PropStudents;

	TObjectPtr<class UStudent> NonPropStudent;

	TArray<TObjectPtr<class UStudent>> NonPropStudents;

	class FStudentManager* StudentManager = nullptr;

	UPROPERTY()
	TObjectPtr<class UStudent> StudentSrc;

	FStreamableManager StreamableManager;
	TSharedPtr<FStreamableHandle> Handle;
};

void CheckUObjectIsVaild(const UObject* InObject, const FString& InTag);

void CheckUObjectIsNull(const UObject* InObject, const FString& InTag);

void PrintStudentInfo(const class UStudent* InStudent, const FString& InTag);