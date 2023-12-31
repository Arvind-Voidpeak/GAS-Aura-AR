// Copyright Voidpeak


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interface/Interaction/CombatInterface.h"
#include "Actor/AuraProjectile.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "AuraGameplayTags.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UAuraProjectileSpell::SpawnProjectile()
{
	if (!GetAvatarActorFromActorInfo()->HasAuthority()) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (!CombatInterface) return;

	const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	//TODO: Set the Projectile Rotation.

	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	//TODO: Give the Projectile a Gameplay Effect Spec for causing Damage.



	Projectile->FinishSpawning(SpawnTransform);

}
