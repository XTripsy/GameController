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
#include "Components/SphereComponent.h"

AGCProjectile::AGCProjectile()
{
	Tags.Add("Projectile");
	this->SetActorHiddenInGame(true);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SphereComponent->InitSphereRadius(5.0f);
	SphereComponent->SetCollisionProfileName(TEXT("Trigger"));
	RootComponent = SphereComponent;

	static ConstructorHelpers::FObjectFinder<UPaperFlipbook>projectile_loop(TEXT("/Game/Assets/Projectile/Bullet/Sprite/FlipBook/Gun_Projeectile_Loop"));
	static ConstructorHelpers::FObjectFinder<UPaperFlipbook>projectile_hit(TEXT("/Game/Assets/Projectile/Bullet/Sprite/FlipBook/Gun_Projectile_Impact"));
	Projectile = projectile_loop.Object;
	HitProjectile = projectile_hit.Object;

	PaperComponent = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("PlayerPaper"));
	PaperComponent->SetupAttachment(RootComponent);

	PaperComponent->SetFlipbook(Projectile);
	PaperComponent->SetLooping(true);
	PaperComponent->SetPlayRate(1.5f);
	PaperComponent->SetRelativeScale3D(FVector::One() * .75);

	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AGCProjectile::OnOverlapBegin);
}

void AGCProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Enemy"))
	{
		UE_LOG(LogTemp, Error, TEXT("ENEMY COKK"));
		UGameplayStatics::ApplyDamage(OtherActor, 1.0f, nullptr, this, nullptr);
	}
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
	FVector origin = GetActorLocation();
	FVector player = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn()->GetActorLocation();

	PaperComponent->SetFlipbook(HitProjectile);
	PaperComponent->SetLooping(false);
	PaperComponent->Play();

	InterfaceGameMode->IAddProjectile(this);

	if (FVector::DotProduct(Direction, FVector(0, 0, -1)) < -.5f && FVector::Dist(origin, player) < 100)
		InterfacePlayer->IJump();
	
	SphereComponent->SetGenerateOverlapEvents(false);
}

void AGCProjectile::IActivate(FVector start, FVector end)
{
	SphereComponent->SetGenerateOverlapEvents(true);

	PaperComponent->SetFlipbook(Projectile);
	PaperComponent->SetLooping(true);

	Direction = (start - end).GetSafeNormal();

	float distance = FVector::Dist(start, end);
	float normal = FMath::Clamp(distance / 1000, .15f, 4.0f);
	this->SetActorHiddenInGame(false);
	this->SetActorLocation(start + FVector(0, -15, 5));
	FRotator rot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), end);
	this->SetActorRotation(rot);
	TweenActor = UDBTweenActor::DOMove("Move", normal, this, end, EaseType::Linear, false);
	TweenActor->OnComplete.AddUniqueDynamic(this, &AGCProjectile::EndProjectile);
}

