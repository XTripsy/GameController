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
#include "Kismet/KismetMathLibrary.h"
#include "library/LibraryFunction.h"
#include "GCParallax.h"

AGCPlayer::AGCPlayer()
{
	Tags.Add("Player");
	//PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook>car_paper(TEXT("/Game/Assets/Player/Flipbook/tes_mobil"));
	Car = car_paper.Object;

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
	PlayerCapsuleComponent->SetCollisionResponseToChannel(ECC_EngineTraceChannel2, ECR_Ignore);
	PlayerCapsuleComponent->BodyInstance.bLockZRotation = true;
	PlayerCapsuleComponent->BodyInstance.bLockYRotation = true;
	PlayerCapsuleComponent->BodyInstance.bLockXRotation = true;
	PlayerCapsuleComponent->BodyInstance.bLockYTranslation = true;

	PlayerPaperComponent->SetRelativeLocation(FVector(3, 0, 4.0f));
	PlayerPaperComponent->SetRelativeScale3D(FVector::One() * .4f);

	PlayerSpringArmComponent->bEnableCameraLag = true;
	PlayerSpringArmComponent->CameraLagSpeed = 12.5f;

	PlayerSpringArmComponent->SetRelativeRotation(FRotator(0, -90, 0));
	PlayerSpringArmComponent->bDoCollisionTest = false;
	PlayerSpringArmComponent->TargetArmLength = 600;
	//PlayerSpringArmComponent->TargetOffset = FVector(200.0f, 0.0f, 120.0f);
	PlayerSpringArmComponent->TargetOffset = FVector(FVector::Zero());

	PlayerPaperComponent->SetFlipbook(Car);
	PlayerPaperComponent->SetLooping(true);
	PlayerPaperComponent->SetPlayRate(0.4f);
}

void AGCPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->SpawnActor<AGCParallax>(AGCParallax::StaticClass(), this->GetActorLocation(), FRotator::ZeroRotator, FActorSpawnParameters());
}

void AGCPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	PlayerCapsuleComponent->AddWorldOffset(GetActorForwardVector() * 300.0f * DeltaTime);
	Slope(DeltaTime);
}

void AGCPlayer::Slope(float deltatime)
{
	FVector start = GetActorLocation();
	FVector end = start + GetActorUpVector() * -40;

	float out_pitch, out_roll;
	FRotator rot = PlayerPaperComponent->GetRelativeRotation();

	LibraryFunction::LibraryLineTraceByChannel(GetWorld(), start, end, ECollisionChannel::ECC_Visibility, this, false,
		[&](FHitResult hit)
		{
			UKismetMathLibrary::GetSlopeDegreeAngles(GetActorRightVector(), hit.ImpactNormal, GetActorUpVector(), out_pitch, out_roll);
			out_pitch = FMath::Clamp(out_pitch, -45, 45);
			out_roll = FMath::Clamp(out_roll, -45, 45);
			FVector2D vec = FVector2D(out_pitch, out_roll);
			rot.Pitch = out_pitch;
			FRotator interp = UKismetMathLibrary::RInterpTo(PlayerPaperComponent->GetRelativeRotation(), rot, deltatime, 1);
			PlayerPaperComponent->SetWorldRotation(rot);
		},
		[]()
		{

		}
	);
}

void AGCPlayer::IJump()
{
	PlayerCapsuleComponent->AddImpulse(FVector(0, 0, 475), FName("None"), true);
}
