// Fill out your copyright notice in the Description page of Project Settings.


#include "Student.h"
#include "Card.h"

UStudent::UStudent()
{
	Name = TEXT("김학생");
	Year = 1;
	Id = 1;
	Card->SetCardType(ECardType::Student);
}


void UStudent::DoLesson()
{
	//Super::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%d학년 %d번 %s 님이 수업을 듣습니다."), Year, Id, *Name);
}

void UStudent::GetNotification(const FString& School, const FString& NewCourseInfo)
{
	UE_LOG(LogTemp, Log, TEXT("[Student] %s 님이 %s 로부터 받은 메시지 : %s"), *Name, *School, *NewCourseInfo);
}
