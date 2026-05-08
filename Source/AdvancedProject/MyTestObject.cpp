// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTestObject.h"

void UMyTestObject::InitObject(FString InName)
{
	MemoName = InName;
}

void UMyTestObject::BeginDestroy()
{
	UObject::BeginDestroy();

	UE_LOG(LogTemp, Warning, TEXT("GC Start : %s object is ready to disappear."), *MemoName);
}

void UMyTestObject::FinishDestroy()
{
	UObject::FinishDestroy();

	UE_LOG(LogTemp, Warning, TEXT("GC Finished : %s object completely disappeared from memory"), *MemoName);
}
