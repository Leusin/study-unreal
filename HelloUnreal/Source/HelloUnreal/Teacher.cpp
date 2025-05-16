// Fill out your copyright notice in the Description page of Project Settings.


#include "Teacher.h"

UTeacher::UTeacher()
{
	Name = TEXT("김선생");
	Year = 3;
	Id = 1;
}

void UTeacher::DoLesson()
{
	Super::DoLesson();
	UE_LOG(LogTemp, Log, TEXT("%d년차 선생님 %s 님이 수업을 듣습니다."), Year, *Name);
}