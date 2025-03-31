// Fill out your copyright notice in the Description page of Project Settings.


#include "GCProjectile.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetMathLibrary.h"
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "interface/InterfaceGameMode.h"
#include "interface/InterfacePlayer.h"
#include "GameFramework/GameModeBase.h"
#include "library/LibraryFunction.h"

AGCProjectile::AGCProjectile()
{
	this->SetActorHiddenInGame(true);
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook>projectile_loop(TEXT("/Game/Assets/Projectile/Bullet/Sprite/FlipBook/Gun_Projeectile_Loop"));
	Projectile = projectile_loop.Object;

	PaperComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerPaper"));
	PaperComponent->SetupAttachment(RootComponent);

	PaperComponent->SetFlipbook(Projectile);
	PaperComponent->SetLooping(true);
	PaperComponent->SetPlayRate(1.5f);
	PaperComponent->SetRelativeScale3D(FVector::One() * .75);
}

void AGCProjectile::BeginPlay()
{
	Super::BeginPlay();
	InterfaceGameMode = Cast<IInterfaceGameMode>(GetWorld()->GetAuthGameMode());
	InterfacePlayer = Cast<IInterfacePlayer>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn());
}

void AGCProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGCProjectile::EndProjectile()
{
	this->SetActorHiddenInGame(true);
	InterfaceGameMode->IAddProjectile(this);

	FVector origin = GetActorLocation();
	FVector player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();

	if (FVector::Dist(origin, player) < 100)
		InterfacePlayer->IJump();
}

void AGCProjectile::IActivate(FVector start, FVector end)
{
	float distance = FVector::Dist(start, end);
	float normal = FMath::Clamp(distance / 1000, .15f, 4.0f);
	this->SetActorHiddenInGame(false);
	this->SetActorLocation(start + FVector(0, -15, 5));
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), end);
	this->SetActorRotation(rot);
	TweenActor = UDBTweenActor::DOMove("Move", normal, this, end, EaseType::Linear, false);
	TweenActor->OnComplete.AddUniqueDynamic(this, &AGCProjectile::EndProjectile);
}

