// Fill out your copyright notice in the Description page of Project Settings.


#include "GCProjectile.h"
#include <Kismet/GameplayStatics.h>
#include "PaperFlipbookComponent.h"
#include "PaperFlipbook.h"
#include "interface/InterfaceGameMode.h"
#include "GameFramework/GameModeBase.h"

AGCProjectile::AGCProjectile()
{
	this->SetActorHiddenInGame(true);
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook>tank_paper(TEXT("/Game/Assets/Projectile/projectile_Flipbook"));
	PaperTank = tank_paper.Object;

	PlayerPaperComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerPaper"));
	PlayerPaperComponent->SetupAttachment(RootComponent);

	PlayerPaperComponent->SetFlipbook(PaperTank);
	PlayerPaperComponent->SetRelativeScale3D(FVector::One() * .15);
}

void AGCProjectile::BeginPlay()
{
	Super::BeginPlay();
	InterfaceGameMode = Cast<IInterfaceGameMode>(GetWorld()->GetAuthGameMode());
}

void AGCProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGCProjectile::EndProjectile()
{
	this->SetActorHiddenInGame(true);
	InterfaceGameMode->IAddProjectile(this);
}

void AGCProjectile::IActivate(FVector start, FVector end)
{
	float distance = FVector::Dist(start, end);
	float normal = 3;//FMath::Clamp(distance / 10000, .25f, 1.0f);
	this->SetActorHiddenInGame(false);
	this->SetActorLocation(start + FVector(0, -15, 5));
	//this->SetActorRotation(FRotationMatrix::MakeFromX(hit_normal).Rotator());
	TweenActor = UDBTweenActor::DOMove("Move", normal, this, end, EaseType::Linear, false);
	TweenActor->OnComplete.AddUniqueDynamic(this, &AGCProjectile::EndProjectile);
}

