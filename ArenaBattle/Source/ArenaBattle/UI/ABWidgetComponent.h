// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "ABWidgetComponent.generated.h"

/**
 * 위젯 컴포넌트 초기화 단계에서 이를 설정할 수 있도록 확장
 */
UCLASS()
class ARENABATTLE_API UABWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
	
protected:
	virtual void InitWidget() override;
};
