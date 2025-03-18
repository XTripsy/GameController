// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "interface/InterfaceGameMode.h"
#include "GCGameModeBase.generated.h"

UCLASS()
class GAMECONTROLLER_API AGCGameModeBase : public AGameModeBase, public IInterfaceGameMode
{
	GENERATED_BODY()
	
public:
	AGCGameModeBase();

private:
	float fXCurrentLoc;

private:
	virtual void ISetCurrentLocation(float value) override;
	virtual float IGetCurrentLocation() override;
};
