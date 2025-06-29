// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CCharacter.h"
#include "InputActionValue.h"
#include "GAS/CGameplayAbilityTypes.h"
#include "CPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ACPlayerCharacter : public ACCharacter
{
	GENERATED_BODY()
public:
	ACPlayerCharacter();
	virtual void PawnClientRestart() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const  override;
private:
	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleDefaultsOnly, Category = "View")
	class UCameraComponent* ViewCam;

	FVector GetLookRightDir() const;
	FVector GetLookFwdDir() const;
	FVector GetMoveFwdDir() const;
	/*************************************************************/
	/*                       Gameplay Ability                    */
	/*************************************************************/
private:
	virtual void OnAimStateChanged(bool bIsAimming) override;
	UPROPERTY()
	class UCHeroAttributeSet* HeroAttributeSet;

	/*************************************************************/
	/*                           Input                           */
	/*************************************************************/
private:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* JumpInputAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LookInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* MoveInputAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* LearnAbilityLeaderAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputAction* UseInventoryItemAction;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TMap<ECAbilityInputID, class UInputAction*> GameplayAbilityInputActions;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	class UInputMappingContext* GameplayInputMappingContext;

	void HandleLookInput(const FInputActionValue& InputActionValue);
	void HandleMoveInput(const FInputActionValue& InputActionValue);
	void LearnAbiltiyLeaderDown(const FInputActionValue& InputActionValue);
	void LearnAbiltiyLeaderUp(const FInputActionValue& InputActionValue);
	void UseInventoryItem(const FInputActionValue& InputActionValue);
	bool bIsLearnAbilityLeaderDown = false;
	void HandleAbilityInput(const FInputActionValue& InputActionValue, ECAbilityInputID InputID);
	void SetInputEnabledFromPlayerController(bool bEnabled);
	/*************************************************************/
	/*                           Stun                            */
	/*************************************************************/
	virtual void OnStun() override;
	virtual void OnRecoverFromStun() override;
	/*************************************************************/
	/*                      Death and Respawn                    */
	/*************************************************************/

	virtual void OnDead() override;
	virtual void OnRespawn() override;
	/*************************************************************/
	/*                      Camer View                           */
	/*************************************************************/
private:
	UPROPERTY(EditDefaultsOnly, Category = view)
	FVector CameraAimLocalOffset;

	UPROPERTY(EditDefaultsOnly, Category = view)
	float CamerLerpSpeed = 20.f;
	
	FTimerHandle CamerLerpTimerHandle;

	void LerpCameraToLocalOffsetLocation(const FVector& Goal);
	void TickCameraLocalOffsetLerp(FVector Goal);


	/*************************************************************/
	/*                      Inventory                            */
	/*************************************************************/
private:
	class UInventoryComponent* InventoryComponent;
};
