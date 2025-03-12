// Fill out your copyright notice in the Description page of Project Settings.


#include "GCGameModeBase.h"
#include "GCPlayerController.h"
#include "GCPlayer.h"

AGCGameModeBase::AGCGameModeBase()
{
	PlayerControllerClass = AGCPlayerController::StaticClass();
	DefaultPawnClass = AGCPlayer::StaticClass();
}
