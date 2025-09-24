#include <PlayableAnimationSystem.h>
#include <PunchEvent.h>

void PlayableAnimationSystem::Update(TAKO::GameStorage& gameStorage) {
    for (auto& event : gameStorage.getEventsOfType<PunchEvent>()) {
        ///////////// Guards ////////////
        auto& entity = gameStorage.getEntity(event.entityID);
        FistComponent* fistComp = static_cast<FistComponent*>(entity.require(COMPONENT_FIST));
        if (!fistComp) continue;
        BBoxComponent* bboxComp = static_cast<BBoxComponent*>(entity.require(COMPONENT_BBOX));
        if (!bboxComp) continue;
        IrranimatednodeComponent* animNodeComp = static_cast<IrranimatednodeComponent*>(entity.require(COMPONENT_IRRANIMATEDNODE));
        if (!animNodeComp) continue;
        /////////////////////////////////

        std::string nextAnim = "N";
        if (event.fist == FistAction::left && !bboxComp->hlf) {
            nextAnim = "L";
        } else if (event.fist == FistAction::right && !bboxComp->hrf) {
            nextAnim = "R";
        }

        if (nextAnim == "N") continue;  // The fist event wasn't a punch.
        switch (fistComp->currentFist) {
            case FistEnum::DIRECT:
                nextAnim.insert(0, "Direct");
                break;
            case FistEnum::CROCHET:
                nextAnim.insert(0, "Crochet");
                break;
            case FistEnum::UPPERCUT:
                fistComp->currentlyCharging = true;
                if (fistComp->timerUppercut > 0) continue;
                nextAnim.insert(0, "UppercutPrevious");
                break;
        }
        if (animNodeComp->node.getCurrentAnimation().rfind(nextAnim, 0) == 0) continue;
        animNodeComp->node.changeToAnimation(nextAnim);
    }

    for (auto& playableTag : gameStorage.getComponentsOfType<TagPlayable>()) {
        ///////////// Guards ////////////
        auto& entity = gameStorage.getEntity(playableTag.entityID);
        VelocityComponent* velocityComp = static_cast<VelocityComponent*>(entity.require(COMPONENT_VELOCITY));
        if (!velocityComp) continue;
        IrranimatednodeComponent* animNodeComp = static_cast<IrranimatednodeComponent*>(entity.require(COMPONENT_IRRANIMATEDNODE));
        if (!animNodeComp) continue;
        FistComponent* fistComp = static_cast<FistComponent*>(entity.require(COMPONENT_FIST));
        if (!fistComp) continue;
        /////////////////////////////////

        const std::string& currentAnim = animNodeComp->node.getCurrentAnimation();
        std::string baseName = currentAnim.substr(0, currentAnim.find_last_of('_'));

        bool isUppercut = baseName.rfind("Uppercut", 0) == 0;
        if (isUppercut) {
            if (!fistComp->currentlyCharging && (baseName.rfind("UppercutPrevious", 0) == 0 || baseName.rfind("UppercutHold", 0) == 0)) {
                animNodeComp->node.changeToAnimation("Neutral");
            }
            fistComp->currentlyCharging = false;
        }

        if (velocityComp->jumping) {
            if (velocityComp->hitDown) {
                if (baseName != "GroundPound") {
                    animNodeComp->node.changeToAnimation("GroundPound");
                    continue;
                }
            } else {
                if (baseName == "") continue;
                if (baseName != "Jump") {
                    animNodeComp->node.changeToAnimation("Jump");
                    continue;
                }
            }
        } else if (baseName == "Jump" || baseName == "") {
            animNodeComp->node.changeToAnimation("Neutral");
            baseName = "Neutral";
        }

        if (isUppercut || baseName == "Jump" || baseName == "GroundPound") continue;

        if (velocityComp->blocking) {
            if (baseName.rfind("Neutral", 0) == 0) {
                animNodeComp->node.changeToAnimation("Block");
                baseName = "Block";
            }
        } else if (baseName.rfind("Block", 0) == 0) {
            animNodeComp->node.changeToAnimation("Neutral");
            baseName = "Neutral";
        }

        std::string suffix = "";

        if (velocityComp->vel.Z > 0) {
            suffix += "F";
        } else if (velocityComp->vel.Z < 0) {
            suffix += "B";
        } else if (velocityComp->vel.X > 0) {
            suffix += "L";
        } else if (velocityComp->vel.X < 0) {
            suffix += "R";
        }
        
        if (suffix != "") {
            baseName += "_" + suffix;
        }
        if (currentAnim != baseName) {
            animNodeComp->node.changeToAnimation(baseName, false);
        }
    }
}