//todo

//intro anim

//outro anim

//battle anim

uchar battle(uchar attacker, uchar defender){
    if (attacker == defender || entities[attacker].party == entities[defender].party){
        return 0;
    }
    //start battle scene
    //attacker attacks
    //todo: fix to not go negative
    //todo: edit the algorithm
    entities[defender].health -= 5;
    if (entities[defender].health == 0 || entities[defender].health > entities[defender].maxHealth){
        entities[defender].health = 0;
        //remove from map
        return 2;
    }
    //defender counters
    entities[attacker].health -= 8;
    if (entities[attacker].health <= 0 || entities[attacker].health > entities[attacker].maxHealth){
        entities[attacker].health == 0;
        //remove from map
        return 1;
    }
    return 0;
}