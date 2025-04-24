#include "HealthComponent.h"
#include "GameFramework/Actor.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentHealth = MaxHealth;

    if (AActor* Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleTakeAnyDamage);
    }
}

void UHealthComponent::HandleTakeAnyDamage(
    AActor* DamagedActor,
    float Damage,
    const UDamageType* DamageType,
    AController* InstigatedBy,
    AActor* DamageCauser)
{
    if (Damage <= 0.0f || CurrentHealth <= 0.0f)
    {
        return;
    }

    CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
    UE_LOG(LogTemp, Warning, TEXT("Health Changed: %.1f / %.1f"), CurrentHealth, MaxHealth);

    if (CurrentHealth <= 0.0f)
    {
        OnDeath.Broadcast();
    }
}

void UHealthComponent::TakeDamage(float DamageAmount)
{
    HandleTakeAnyDamage(GetOwner(), DamageAmount, nullptr, nullptr, nullptr);
}

void UHealthComponent::Heal(float HealAmount)
{
    CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(CurrentHealth, MaxHealth);
}

bool UHealthComponent::IsDead() const
{
    return CurrentHealth <= 0.0f;
}