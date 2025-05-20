// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentManager.h"
#include "Student.h"

FStudentManager::FStudentManager()
{
}

FStudentManager::FStudentManager(UStudent* InStudent)
	: ManagedStudent(InStudent)
{
}

void FStudentManager::AddReferencedObjects(FReferenceCollector& Collector)
{
	if (ManagedStudent->IsValidLowLevel())
	{
		Collector.AddReferencedObject(ManagedStudent);
	}
}