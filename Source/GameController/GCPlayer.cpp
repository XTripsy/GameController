// Fill out your copyright notice in the Description page of Project Settings.


#include "GCPlayer.h"
#include "PaperZD.h"
#include "PaperFlipbookComponent.h"
#include "PaperZDAnimationComponent.h"
#include "PaperFlipbook.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include <Kismet/GameplayStatics.h>

AGCPlayer::AGCPlayer()
{
	//PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook>tank_paper(TEXT("/Game/Assets/Player/Flipbook/MoveRight"));
	PaperTank = tank_paper.Object;

	PlayerCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuelComponent"));
	RootComponent = PlayerCapsuleComponent;

	PlayerPaperComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerPaper"));
	PlayerPaperComponent->SetupAttachment(RootComponent);

	PlayerSpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	PlayerSpringArmComponent->SetupAttachment(RootComponent);

	PlayerCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
	PlayerCameraComponent->SetupAttachment(PlayerSpringArmComponent);

	PaperAnimationComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>(TEXT("AnimationComponent"));

	PlayerCapsuleComponent->InitCapsuleSize(30.0f, 25.0f);
	PlayerCapsuleComponent->SetSimulatePhysics(true);
	PlayerCapsuleComponent->SetCollisionProfileName(TEXT("Pawn"));
	PlayerCapsuleComponent->BodyInstance.bLockZRotation = true;
	PlayerCapsuleComponent->BodyInstance.bLockYRotation = true;
	PlayerCapsuleComponent->BodyInstance.bLockXRotation = true;
	PlayerCapsuleComponent->BodyInstance.bLockYTranslation = true;

	PlayerPaperComponent->SetRelativeLocation(FVector(3, 0, -5));
	PlayerPaperComponent->SetRelativeScale3D(FVector::One() * 1.5f);

	PlayerSpringArmComponent->bEnableCameraLag = true;
	PlayerSpringArmComponent->CameraLagSpeed = 5;

	PlayerSpringArmComponent->SetRelativeRotation(FRotator(0, -90, 0));
	PlayerSpringArmComponent->bDoCollisionTest = false;

	PlayerPaperComponent->SetFlipbook(PaperTank);
	PlayerPaperComponent->SetLooping(true);
	PlayerPaperComponent->SetPlayRate(0.4f);
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

