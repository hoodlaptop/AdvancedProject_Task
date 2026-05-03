// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyTestObject.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDPROJECT_API UMyTestObject : public UObject
{
	GENERATED_BODY()
	
public:
	
	void InitObject(FString InName);
	
	virtual void BeginDestroy() override;
	virtual void FinishDestroy() override;
	
private:
	
	FString MemoName;
};
