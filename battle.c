//todo

uchar attacker = 0;
uchar defender = 0;

//intro anim
void battleIntro() {

}
//outro anim
void battleOutro() {

}
//battle anim
void battleAnimation() {

}

uchar determineAdvantage() {
    
    //advantage type of space
    uchar attackerPriority = advantage[MAPS[mapIndex][entities[attacker].x*16][entities[attacker].y*16]];
    uchar defenderPriority = advantage[MAPS[mapIndex][entities[defender].x*16][entities[defender].y*16]];

    //0-10 advantage    

    if(attackerPriority > defenderPriority) {
        return 7;
    }
    else {
        return 3;
    }       
}

//Create base functions and logic for battling. Pokemon battle style
uchar battle(uchar nAttacker, uchar nDefender) {
    attacker = nAttacker;
    defender = nDefender;

    if (attacker == defender || entities[attacker].party == entities[defender].party){
        return 0;
    }

    //cls();
    HIDE_SPRITES;
    HIDE_BKG;
    HIDE_WIN;

    //start battle scene
    //battleIntro();    

    //function to calculate advantage with uchar  
    //display arrow in top left
        
    //todo: fix to not go negative        
    //todo: edit the algorithm    

    /*
    fire emblem confirm battle
    cue movie with sequence of random moves bewteen characters
    */

    //attacker attacks
     entities[defender].health = (entities[defender].health >= 5) ? 
         entities[defender].health - 5 : 
         0;
     //entities[defender].health -= 5;

    if (entities[defender].health <= 0) {        
        //remove from map        
        return 2;
    }    

    //defender counters
    entities[attacker].health = (entities[attacker].health >= 8) ? 
        entities[attacker].health - 8 : 
        0;


    //entities[attacker].health -= 8;

    if (entities[attacker].health <= 0) {              
        //remove from map        
        return 1;
    }
    return 0;

    //battleOutro();

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