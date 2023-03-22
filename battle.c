/*
@file battle.c
@author entire team
@date 3/22/2023
@brief Battle mechanics
*/

//todo

//intro anim
void battleIntro()
{

}
//outro anim
void battleOutro()
{

}
//battle anim
void battleAnimation()
{

}

//Create base functions and logic for battling. Pokemon battle style
uchar battle(uchar attacker, uchar defender){
    cls();
    if (attacker == defender || entities[attacker].party == entities[defender].party){
        return 0;
    }

    //start battle scene
    // battleIntro();
    //attacker attacks    
    //todo: fix to not go negative        
    //todo: edit the algorithm

    //entities[defender].health -= 5;
     entities[defender].health = (entities[defender].health >= 5) ? 
         entities[defender].health - 5 : 
         0;
        
    if (entities[defender].health <= 0) {        
        //remove from map
        //entities[defender] = 0;
        return 2;
    }

    //defender counters
    entities[attacker].health = (entities[attacker].health >= 8) ? 
        entities[attacker].health - 8 : 
        0;
    //entities[attacker].health -= 8;

    if (entities[attacker].health <= 0) {              
        //remove from map
        //entities[attacker] = 0;
        return 1;
    }
    return 0;

    //if (entities[defender].health == 0 || entities[defender].health > entities[defender].maxHealth){
    //    entities[defender].health = 0;
    //    //remove from map
    //    return 2;
    //}
    ////defender counters
    //entities[attacker].health -= 8;
    //if (entities[attacker].health <= 0 || entities[attacker].health > entities[attacker].maxHealth){
    //    entities[attacker].health == 0;
    //    //remove from map
    //    return 1;
    //}    
}