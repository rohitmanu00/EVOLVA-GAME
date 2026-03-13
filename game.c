#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"
#define RESET "\033[0m"

typedef struct {
    char name[50];
    int hp;
    int attack;
    int defense;
} Character;

int specialUnlocked = 0;
int specialUsed = 0;

int genjutsuUnlocked = 0;
int genjutsuUsed = 0;
int evolved = 0;

// Normal attack
void attack(Character *attacker, Character *defender) {

    int damage = attacker->attack - defender->defense;
    if(damage < 0) damage = 0;

    defender->hp -= damage;

    printf(RED "%s attacks %s for %d damage!\n" RESET,
           attacker->name, defender->name, damage);
}

// Special attack (400–500)
void specialAttack(Character *attacker, Character *defender) {

    if(specialUsed) {
        printf("Special attack already used!\n");
        return;
    }

    int damage = (rand() % 101) + 400;
    defender->hp -= damage;

    printf(RED "%s uses SPECIAL ATTACK on %s for %d damage!\n" RESET,
           attacker->name, defender->name, damage);

    specialUsed = 1;
}

// Genjutsu (HP Swap)
void genjutsu(Character *player, Character *enemy) {

    if(genjutsuUsed) {
        printf("Genjutsu already used!\n");
        return;
    }

    int temp = player->hp;
    player->hp = enemy->hp;
    enemy->hp = temp;

    printf(PURPLE "ZEUS uses GENJUTSU! HP Swapped!\n" RESET);

    genjutsuUsed = 1;
}

// Battle loop
void battle(Character *player, Character *enemy) {

    printf("\nA wild %s appears!\n", enemy->name);

    while(player->hp > 0 && enemy->hp > 0) {

        // Evolution trigger
        if(player->hp < 200 && !evolved) {
            printf(PURPLE "\nZEUS IS EVOLVING!!!\n" RESET);
            printf(PURPLE "GENJUTSU UNLOCKED!\n" RESET);
            genjutsuUnlocked = 1;
            evolved = 1;
        }

        printf("\n%s HP: %d | %s HP: %d\n",
               player->name, player->hp,
               enemy->name, enemy->hp);

        printf(BLUE "Defense -> %s:%d  %s:%d\n" RESET,
               player->name, player->defense,
               enemy->name, enemy->defense);

        printf("Choose action:\n");
        printf("1. Attack\n");
        printf("2. Heal\n");

        if(specialUnlocked)
            printf("3. Special Attack\n");

        if(genjutsuUnlocked)
            printf("4. Genjutsu (HP Swap)\n");

        int choice;
        scanf("%d", &choice);

        if(choice == 1) {
            attack(player, enemy);
        }

        else if(choice == 2) {
            int heal = 10;
            player->hp += heal;
            printf(GREEN "%s heals %d HP!\n" RESET,
                   player->name, heal);
        }

        else if(choice == 3 && specialUnlocked) {
            specialAttack(player, enemy);
        }

        else if(choice == 4 && genjutsuUnlocked) {
            genjutsu(player, enemy);
        }

        if(enemy->hp > 0) {
            attack(enemy, player);
        }
    }

    if(player->hp <= 0) {
        printf(RED "You have been defeated!\n" RESET);
    }
    else {
        printf(GREEN "You defeated %s!\n" RESET, enemy->name);
    }
}

int main() {

    srand(time(NULL));

    Character player;
    strcpy(player.name, "ZEUS");
    player.hp = 500;
    player.attack = 180;
    player.defense = 50;

    Character enemy;
    strcpy(enemy.name, "KIRMADA");
    enemy.hp = 500;
    enemy.attack = 80;
    enemy.defense = 100;

    battle(&player, &enemy);

    // After defeating KIRMADA
    if(player.hp > 0) {

        printf(GREEN "\nZEUS absorbed KIRMADA's power!\n" RESET);
        printf(BLUE "+800 HP gained!\n" RESET);

        player.hp += 800;

        printf(GREEN "Special attack unlocked!\n" RESET);

        specialUnlocked = 1;
        specialUsed = 0;

        Character boss;
        strcpy(boss.name, "IGRIS");
        boss.hp = 2000;
        boss.attack = 120;
        boss.defense = 120;

        battle(&player, &boss);
    }

    return 0;
}
