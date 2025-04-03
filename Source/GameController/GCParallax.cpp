// Fill out your copyright notice in the Description page of Project Settings.


#include "GCParallax.h"
#include <Kismet/GameplayStatics.h>
#include "PaperSprite.h"

AGCParallax::AGCParallax()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UPaperSprite>layer_0(TEXT("/Game/Assets/Parralax/Dessert/Try2/Desertparallax4_Sprite"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite>layer_1(TEXT("/Game/Assets/Parralax/Dessert/Try2/Desertparallax3_Sprite"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite>layer_2(TEXT("/Game/Assets/Parralax/Dessert/Try2/Desertparallax2_Sprite"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite>layer_3(TEXT("/Game/Assets/Parralax/Dessert/Try2/Desertparallax1_Sprite"));
	static ConstructorHelpers::FObjectFinder<UPaperSprite>layer_4(TEXT("/Game/Assets/Parralax/Dessert/Try2/Desertparallax5_Sprite"));

	ParallaxHolder = CreateDefaultSubobject<USceneComponent>(TEXT("ParallaxHolder"));
	RootComponent = ParallaxHolder;

	Layer0 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Layer0"));
	Layer0->SetupAttachment(ParallaxHolder);
	Layer0->SetSprite(layer_0.Object);
	Layer0->SetRelativeLocation(FVector(0.0f, -1000.000000f, 136.915305f));
	Layer0->SetRelativeScale3D(FVector(1.5f, 1.5f, 4.0f));

	Layer1 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Layer1"));
	Layer1->SetupAttachment(ParallaxHolder);
	Layer1->SetSprite(layer_1.Object);
	Layer1->SetRelativeLocation(FVector(0.0f, -949.603663f, 136.915304f));
	Layer1->SetRelativeScale3D(FVector::One() * 1.5f);

	Layer2 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Layer2"));
	Layer2->SetupAttachment(ParallaxHolder);
	Layer2->SetSprite(layer_2.Object);
	Layer2->SetRelativeLocation(FVector(0.0f, -870.852090f, 106.915305f));
	Layer2->SetRelativeScale3D(FVector::One() * 2.0f);

	Layer3 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Layer3"));
	Layer3->SetupAttachment(ParallaxHolder);
	Layer3->SetSprite(layer_3.Object);
	Layer3->SetRelativeLocation(FVector(0.0f, -708.888690f, 250.915304f));
	Layer3->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));

	Layer4 = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Layer4"));
	Layer4->SetupAttachment(ParallaxHolder);
	Layer4->SetSprite(layer_4.Object);
	Layer4->SetRelativeLocation(FVector(0.0f, -968.343636f, 136.915308f));
	Layer4->SetRelativeScale3D(FVector::One() * 1.5f);

	fValueParallax.Add(1.0f);
	fValueParallax.Add(2.0f);
	fValueParallax.Add(3.0f);
	fValueParallax.Add(4.0f);
	fValueParallax.Add(5.0f);
}

void AGCParallax::BeginPlay()
{
	Super::BeginPlay();

	aPlayer = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

	UMaterialInterface* layer_material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Assets/Parralax/M_ParralaxSprite.M_ParralaxSprite"));
	Layer0->SetMaterial(0, layer_material);
	Layer1->SetMaterial(0, layer_material);
	Layer2->SetMaterial(0, layer_material);
	Layer3->SetMaterial(0, layer_material);
	Layer4->SetMaterial(0, layer_material);

	TArray<USceneComponent*> children;
	ParallaxHolder->GetChildrenComponents(true, children);

	for (USceneComponent* child : children)
	{
		UPaperSpriteComponent* sprite = Cast<UPaperSpriteComponent>(child);

		if (!sprite) return;

		UMaterialInstanceDynamic* material = sprite->CreateDynamicMaterialInstance(0);

		if (!material) return;

		material->SetScalarParameterValue(FName("ParallaxMultiplier"), fValueParallax[iIndex]);

		iIndex++;
	}
}

void AGCParallax::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->SetActorLocation(FVector(aPlayer->GetActorLocation().X, aPlayer->GetActorLocation().Y, this->GetActorLocation().Z));
}

