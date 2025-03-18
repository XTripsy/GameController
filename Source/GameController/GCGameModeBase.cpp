// Fill out your copyright notice in the Description page of Project Settings.


#include "GCGameModeBase.h"
#include "GCPlayerController.h"
#include "GCPlayer.h"

AGCGameModeBase::AGCGameModeBase()
{
	PlayerControllerClass = AGCPlayerController::StaticClass();
	DefaultPawnClass = AGCPlayer::StaticClass();

	fXCurrentLoc = 3500.0f;
}

void AGCGameModeBase::ISetCurrentLocation(float value)
{
	fXCurrentLoc = value;
}

float AGCGameModeBase::IGetCurrentLocation()
{
	return fXCurrentLoc;
}
