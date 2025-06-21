// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ABAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ABAI.h"

AABAIController::AABAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/ArenaBattle/AI/BB_ABCharactor.BB_ABCharactor"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/ArenaBattle/AI/BT_ABCharactor.BT_ABCharactor"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}
}

void AABAIController::RunAI()
{
	/*
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset, BlackboardPtr))
	{
		Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

		bool RunResult = RunBehaviorTree(BTAsset);

		ensure(RunResult);
	}
	*/


    UE_LOG(LogTemp, Warning, TEXT("RunAI() 호출됨"));

    UBlackboardComponent* BlackboardPtr = Blackboard.Get();

    if (!BBAsset)
    {
        UE_LOG(LogTemp, Error, TEXT("BBAsset == nullptr"));
    }

    if (!BTAsset)
    {
        UE_LOG(LogTemp, Error, TEXT("BTAsset == nullptr"));
    }

    if (UseBlackboard(BBAsset, BlackboardPtr))
    {
        UE_LOG(LogTemp, Warning, TEXT("Blackboard 성공 연결"));

        Blackboard->SetValueAsVector(BBKEY_HOMEPOS, GetPawn()->GetActorLocation());

        bool RunResult = RunBehaviorTree(BTAsset);
        if (!RunResult)
        {
            UE_LOG(LogTemp, Error, TEXT("BehaviorTree 실행 실패"));
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("BehaviorTree 실행 성공"));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Blackboard 연결 실패"));
    }
}

void AABAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AABAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}