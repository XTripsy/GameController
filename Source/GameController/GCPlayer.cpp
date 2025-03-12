// Fill out your copyright notice in the Description page of Project Settings.


#include "GCPlayer.h"
#include "PaperZD.h"
#include "PaperFlipbookComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AGCPlayer::AGCPlayer()
{
	//PrimaryActorTick.bCanEverTick = true;

	PlayerCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuelComponent"));
	RootComponent = PlayerCapsuleComponent;

	PlayerPaperComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerPaper"));
	PlayerPaperComponent->SetupAttachment(RootComponent);

	PlayerSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	PlayerSpringArmComponent->SetupAttachment(RootComponent);

	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCameraComponent->SetupAttachment(PlayerSpringArmComponent);

	PlayerSpringArmComponent->bEnableCameraLag = true;
	PlayerSpringArmComponent->CameraLagSpeed = 5;
}

void AGCPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGCPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerCapsuleComponent->AddWorldOffset(GetActorForwardVector() * 5);
}

