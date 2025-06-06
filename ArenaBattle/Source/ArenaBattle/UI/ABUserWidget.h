// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABUserWidget.generated.h"

/**
 * 위젯에 소유한 액터 정보를 보관할 수 있도록 클래스를 확장
 */
UCLASS()
class ARENABATTLE_API UABUserWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	FORCEINLINE void SetOwningActor(AActor* NewOwner) { OwningActor = NewOwner; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Actor")
	TObjectPtr<AActor> OwningActor;
};
