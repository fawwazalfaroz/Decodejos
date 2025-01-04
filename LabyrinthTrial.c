LabyrinthTrial.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

// Progress declaration, [0-19] main path, [20-39] item, [40-59]
int pathProgress[60] = {0};
// Progression item declaration
int axe = 0, cloth = 0, woodPlank = 1, lighter = 0, ladder = 0, storageKey = 0, gasoline = 0, branch = 0;
// Healing item declaration
int bandages = 0, medicine = 0, painkiller = 0, medkit = 0, heal = 0; 
// Story item declaration
int battery = 0;
// Screams declaration
char scream[20];
// Clue declaration
char clues[100][256];
int clueCount = 0, currentClueIndex = 0;

void showInventory (int axe, int cloth, int plank, int lighter, int ladder, int battery, char pass[]);
void mainTitle();
int mainMenu();
void gameOpening();
int pathForestStart(int choice, int startPhase, int phase, char exit);
int pathForestOne (int choice, int phase, char exit);
int pathForestPlane (int choice, int phase, char exit);
int pathCrashedPlane (int choice, int phase, char exit);
int pathForestTwo (int choice, int phase, char exit);
int pathForestRiver (int choice, int phase, char exit);
int pathRiverBoat (int choice, int phase, char exit, char pass[]);
int pathForestBridge (int choice, int phase, char exit);
int pathForestCabin (int choice, int phase, char exit);
int pathCabinInside (int choice, int phase, char exit);
int pathForestThree (int choice, int phase, char exit);
int pathForestBunker (int choice, int phase, char exit, char pass[]);
int pathBunkerInside (int choice, int phase, char exit);
int pathForestGraveyard (int choice, int phase, char exit, char pass[]);
int pathGraveyardInside (int choice, int phase, char exit);
void randomScreams(int phase);
int pathForestCave (int choice, int phase, char exit);
int firstEnd();
int secondEnd();
int thirdEnd();
void tampilkanKata(char *kata, int *tebakanBenar);
const char* clue();
void sortString(char *str);
int isAnagram(char *str1, char *str2);

int main () {

    int menuChoice, playerChoice;

    do {
        // Player input declaration
        int startChoicePhase = 0, choicePhase = 0;
        // Player progress declaration
        int playerProgress = 1;
        // Exit command declaration
        char exitChoice;

        // random initialization
        srand(time(NULL));

        // Password declaration
        char boatPass[] = "1990", bunkerPass[] = "58727", gravePass[] = "174";

        // Call menu module function
        mainTitle();
        menuChoice = mainMenu();

        // Game initialization
        system("cls");
        Sleep(1000);
        
        if (menuChoice == 1) {
            
            // Fake loading
            printf("Loading.");
            Sleep(1000);
            printf(".");
            Sleep(1000);
            printf(".");
            Sleep(1000);
            system("cls");
            Sleep(3000);

            do {
                // Call game intro function
                gameOpening();

                // Game start
                playerProgress = pathForestStart(playerChoice, startChoicePhase, choicePhase, exitChoice);
                if (playerProgress == 3) {
                    break;
                }
                system("cls");
                Sleep(2000);

                forestOne: // Forest one label
                playerProgress = pathForestOne(playerChoice, choicePhase, exitChoice);
                if (playerProgress == 3) {
                    break;
                }
                system("cls");
                Sleep(2000);
                pathProgress[0] = 1; // Keep track of progress

                forestPlane: // Forest plane label
                playerProgress = pathForestPlane(playerChoice, choicePhase, exitChoice);
                if (playerProgress == 4) {
                    break;
                }
                system("cls");
                Sleep(2000);
                pathProgress[1] = 1; // Keep track of progress

                if (playerProgress == 1) {
                    playerProgress = pathCrashedPlane(playerChoice, choicePhase, exitChoice);
                    if (playerProgress == 4) {
                        break;
                    }
                    system("cls");
                    Sleep(2000);
                    pathProgress[2] = 1; // Keep track of progress
                    if (pathProgress[3] == 0) {
                        pathProgress[3] = 1;
                    }

                    if (playerProgress == 3) {
                        goto forestPlane;
                    }

                } else if (playerProgress == 3) {
                    goto forestOne;
                }

                forestTwo: // Forest two label
                playerProgress = pathForestTwo(playerChoice, choicePhase, exitChoice);
                if (playerProgress == 4) {
                    break;
                }
                system("cls");
                Sleep(2000);
                pathProgress[3] = 2; // Keep track of progress

                if (playerProgress == 2) {
                    forestRiver: // River label
                    playerProgress = pathForestRiver(playerChoice, choicePhase, exitChoice);
                    if (playerProgress == 4) {
                        break;
                    }
                    system("cls");
                    Sleep(2000);
                    pathProgress[4] = 1; // Keep track of progress

                    if (playerProgress == 1) {
                        playerProgress = pathRiverBoat(playerChoice, choicePhase, exitChoice, boatPass);
                        if (playerProgress == 4) {
                            break;
                        }
                        system("cls");
                        Sleep(2000);
                        pathProgress[5] = 1; // Keep track of progress

                        if (playerProgress == 3) {
                            goto forestRiver;
                        }
                    } else if (playerProgress == 3) {
                        goto forestTwo;
                    }
                } else if (playerProgress == 3) {
                    goto forestPlane;
                }

                forestBridge: // Bridge label
                playerProgress = pathForestBridge(playerChoice, choicePhase, exitChoice);
                if (playerProgress == 4) {
                    break;
                }
                system("cls");
                Sleep(2000);
                pathProgress[7] = 1; // Keep track of progress

                if (playerProgress == 2) {
                    goto caveStart;
                } else if (playerProgress == 3) {
                    goto forestTwo;
                }

                forestCabin: // Cabin label
                playerProgress = pathForestCabin(playerChoice, choicePhase, exitChoice);
                if (playerProgress == 4) {
                    break;
                }
                system("cls");
                Sleep(2000);
                pathProgress[8] = 1; // Keep track of progress

                if (playerProgress == 1) {
                    playerProgress = pathCabinInside(playerChoice, choicePhase, exitChoice);
                    if (playerProgress == 4) {
                        break;
                    }
                    system("cls");
                    Sleep(2000);
                    pathProgress[9] = 1; // Keep track of progress

                    if (playerProgress == 2 || playerProgress == 3) {
                        goto forestCabin; 
                    }
                } else if (playerProgress == 3) {
                    goto forestBridge;
                }

                forestThree: // Forest three label
                playerProgress = pathForestThree(playerChoice, choicePhase, exitChoice);
                if (playerProgress == 4) {
                    break;
                }
                system("cls");
                Sleep(2000);
                pathProgress[10] = 1; // Keep track of progress
               
                if (playerProgress == 1) {
                    forestBunker: // Forest bunker label
                    playerProgress = pathForestBunker(playerChoice, choicePhase, exitChoice, bunkerPass);
                    if (playerProgress == 4) {
                        break;
                    }
                    system("cls");
                    Sleep(2000);
                    pathProgress[11] = 1; // Keep track of progress

                    if (playerProgress == 1) {
                        playerProgress = pathBunkerInside(playerChoice, choicePhase, exitChoice);
                        if (playerProgress == 4) {
                            break;
                        }
                        system("cls");
                        Sleep(2000);
                        pathProgress[12] = 1; // Keep track of progress

                        if (playerProgress == 3) {
                            goto forestBunker;
                        }
                    } else if (playerProgress == 3) {
                        goto forestThree;
                    }
                } else if (playerProgress == 2) {
                    playerProgress = pathForestGraveyard(playerChoice, choicePhase, exitChoice, gravePass);
                    playerProgress = pathBunkerInside(playerChoice, choicePhase, exitChoice);
                        if (playerProgress == 4) {
                            break;
                        }
                        system("cls");
                        Sleep(2000);
                        pathProgress[14] = 1; // Keep track of progress

                        if (playerProgress == 1) {
                            
                            playerProgress = pathGraveyardInside(playerChoice, choicePhase, exitChoice);
                        } else if (playerProgress == 2) {
                            goto forestThree;
                        }
                } else if (playerProgress == 3) {
                    goto forestCabin;
                }
                /* ------------------------------------------------- 
                End of main path, continue to endgame through bridge
                ------------------------------------------------- */

                caveStart: // Cave start label
                playerProgress = pathForestCave(playerChoice, choicePhase, exitChoice);
                if (playerProgress == 0) {
                    system("cls");
                    printf("You're weak.\n");
                    Sleep(3000);
                    printf("But you're not done just yet.\n");
                    Sleep(4000);
                    printf("Go and finish what you've started!\n");
                    Sleep(5000);
                    heal = 4;
                    goto caveStart;
                }

                printf("I ");
                Sleep(1000);
                printf("T ");
                Sleep(1000);
                printf("' S   ");
                Sleep(1000);
                printf("A ");
                Sleep(1000);
                printf("L ");
                Sleep(1000);
                printf("L   ");
                Sleep(1000);
                printf("Y ");
                Sleep(1000);
                printf("O ");
                Sleep(1000);
                printf("U ");
                Sleep(1000);
                printf("R   ");
                Sleep(1000);
                printf("F ");
                Sleep(1000);
                printf("A ");
                Sleep(1000);
                printf("U ");
                Sleep(1000);
                printf("L ");
                Sleep(1000);
                printf("T ");
                Sleep(5000);

                system("cls");
                printf(". ");
                Sleep(1000);
                printf(". ");
                Sleep(1000);
                printf(".");
                Sleep(1000);
                system("cls");
                Sleep(3000);
                playerProgress = 3;

            } while (playerProgress != 3);

            // Fake loading
            printf("Loading.");
            Sleep(1000);
            printf(".");
            Sleep(1000);
            printf(".");
            Sleep(1000);
            system("cls");
            Sleep(3000);

        } else {
            // Exit screen
            printf("Thanks for Playing!");
        }
    } while (menuChoice != 2);

    return 0;
}

// Show inventory
void showInventory (int axe, int cloth, int plank, int lighter, int ladder, int battery, char pass[]) {
    
    printf("%d\n", axe);
    printf("%d\n", cloth);
    printf("%d\n", plank);
    printf("%d\n", lighter);
    printf("%d\n", ladder);
    printf("%d\n", battery);
    printf("%s\n", pass);

}

// Main title text display
void mainTitle () {

    printf("   ___    ___________  ______      _______________________     \n");
    printf(" _/   \\__/           \\/      \\____/                       \\_\n");
    printf("|  _________          _______  _____ _______ ______ _____   |\n");
    printf("| |__   __\\ \\        / /_   _|/ ____|__   __|  ____|  __ \\  |\n");
    printf("|    | |   \\ \\  /\\  / /  | | | (___    | |  | |__  | |  | | |\n");
    printf("|    | |    \\ \\/  \\/ /   | |  \\___ \\   | |  |  __| | |  | | |\n");
    printf("|    | |     \\  /\\  /   _| |_ ____) |  | |  | |____| |__| | |\n");
    printf("|    |_|   __ \\/  \\/   |_____|_____/  _|_|_ |______|_____/  |\n");
    printf("|          \\ \\        / / __ \\ / __ \\|  __ \\ / ____|        |\n");
    printf("|           \\ \\  /\\  / / |  | | |  | | |  | | (___          |\n");
    printf("|            \\ \\/  \\/ /| |  | | |  | | |  | |\\___ \\         |\n");
    printf("|             \\  /\\  / | |__| | |__| | |__| |____) |        |\n");
    printf("|              \\/  \\/   \\____/ \\____/|_____/|_____/         |\n");
    printf("|___________________________________________________________|\n");
    printf("   \\ |\\     |       \\    |     \\     |    \\   / \\ |   |  /\n");
    printf("    \\| \\   /         \\  /       |   /      | /   \\|   | |\n");
    printf("        | /           \\|        |  /       |/         |/   \n");
    printf("        |/                       \\|                       \n");
    printf("\n");

}

// Main menu choice
int mainMenu () {

    int menu;

    printf("\t\t\t    1. PLAY!\n");
    printf("\t\t\t    2. exit\n");
    printf("Your choice: ");
    
    do {
        scanf("%d", &menu);
        switch (menu) {
            case 1:
                return 1;
                break;
            case 2:
                return 2;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
        }
    } while (menu != 1 && menu != 2);

}

// Game intro (for MacOS, replace Sleep() with usleep() and Beep() with "\a" or putchar(7))
void gameOpening () {

    // Story
    printf("DeCodeJoss Presents");
    Sleep(3000);
    system("cls");
    Sleep(2000);

    Beep(500, 1000);
    printf("MAYDAY!! ");
    Beep(500, 1000);
    printf("MAYDAY!!\n");
    Sleep(1000);
    printf("This is flight 87.\n");
    Sleep(3000);
    printf("We have lost control of the plane!\n");
    Sleep(3000);
    printf("I repeat, we have lost control...");
    Sleep(2000);
    system("cls");

    printf("***static***");
    Beep(200, 1000);
    Sleep(1000);
    system("cls");
    Sleep(2000);

    printf("From the Algorithm & Programming Lab");
    Sleep(3000);
    system("cls");
    Sleep(2000);

    Beep(500, 1000);
    printf("We're losing altitude!\n"); 
    Beep(500, 1000);
    Sleep(2000);
    printf("Th- ");
    Sleep(1000);
    printf("There's something with the engine!\n");
    Sleep(3000);
    printf("I- It's not looking good...");
    Sleep(2000);
    system("cls");

    printf("***static***");
    Beep(200, 800);
    Beep(200, 200);
    Sleep(1000);
    system("cls");
    Sleep(2000);

    printf("A Simple Game Made in C Programming");
    Sleep(3000);
    system("cls");
    Sleep(2000);

    Beep(1000, 1000);
    Beep(1000, 1000);
    printf("Th- The engine has failed!\n"); 
    Beep(1000, 1000);
    Beep(1000, 1000);
    Beep(1000, 1000);
    printf("We're going down FAST!\n");
    Beep(1000, 1000);
    Beep(1000, 1000);
    Beep(1000, 1000);
    printf("PLEASE SEND HELP!\n");
    Beep(1000, 500);
    Beep(1000, 500);
    Beep(1000, 500);
    printf("PLEA-");
    Sleep(1000);
    system("cls");

    printf("***static***");
    Beep(200, 200);
    Beep(200, 200);
    Beep(200, 400);
    Beep(200, 200);
    Sleep(1000);
    system("cls");
    Sleep(2000);

    mainTitle();
    Sleep(5000);
    system("cls");
    Sleep(5000);

}

// Starting forest path
int pathForestStart (int choice, int startPhase, int phase, char exit) {

    // Story
    printf("\"It hurts...\"\n");
    Sleep(2000);
    system("cls");
    Sleep(3000);
    printf("\"It really hurts...\"\n");
    Sleep(2000);
    system("cls");
    Sleep(3000);
    printf("\"But I don't think you mind the pain.\"\n");
    Sleep(3000);
    system("cls");
    Sleep(3000);
    printf("\"Noone does.\"\n");
    Sleep(2000);
    system("cls");
    Sleep(3000);
    system("cls");

    Sleep(4000);
    printf("\"Get up!\"\n");
    Sleep(2000);
    printf("\"You're not done yet.\"\n");
    Sleep(3000);
    system("cls");
    Sleep(3000);

    printf("You wake up in an unfamiliar place, surrounded by dense forest.\n");
    Sleep(4000);
    printf("Tall trees looms over you, casting shadows that seem to stretch endlessly.\n");
    Sleep(4000);
    printf("Your leg aches as you force yourself to stand.\n");
    Sleep(4000);
    printf("Bird chirps faintly, ");
    Sleep(3000);
    printf("and the leaves rustle in the distance.\n");
    Sleep(4000);
    printf("But something feels ");
    Sleep(3000);
    printf("wrong...\n");
    Sleep(3000);
    printf("\n");

    // Take action input from player
    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Go forward\n");
        printf("2. Stay\n");
        printf("3. exit\n");
        scanf("%d", &choice); getchar();

        system("cls");
        switch (choice) {
            case 1:
                break;
            case 2:
                if (startPhase == 0) {
                    printf("You choose to stay.\n");
                    Sleep(3000);
                    printf("The unsettling stillness in the air is too much for you to progress forward.\n");
                    Sleep(4000);
                    printf("You're not going to risk it.");
                    Sleep(4000);
                    system("cls");
                    Sleep(3000);
                    printf("Yet something urges you to press forward.\n");
                    Sleep(3000);
                    startPhase++;
                } else if (startPhase >= 1) {
                    printf("You're an imbicile.\n");
                }
                phase++;
                break;
            case 3:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit);  getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");

                if (exit == 'Y') {
                    return 3;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
    } while (choice != 1);

    return 0;
}

// First forest path
int pathForestOne (int choice, int phase, char exit) {

    // Story
    // printf("%d\n", progress[0]);
    if (pathProgress[0] == 0) {
        printf("Despite your concern, you push forward.\n");
        Sleep(3000);
        printf("As you tread forward ");
        Sleep(2000);
        printf("questions start running trough your head");
        Sleep(3000);
        system("cls");
        Sleep(1000);
        printf("What happened? ");
        Sleep(2000);
        printf("Where are you? ");
        Sleep(2000);
        printf("Why are you here?\n");
        Sleep(2000);
        printf("Is this all a dream?\n");
        Sleep(2000);
        printf("Or is this real?\n");
        Sleep(3000);
        printf("These questions clutter your mind until suddenly...\n");
        Sleep(4000);
        system("cls");
        Beep(5000, 2000);

        printf("A loud guttural scream stops you in your track.\n");
        Sleep(4000);
        printf("It fills you with dread.\n");
        Sleep(2000);
        printf("But at the same time...\n");
        Sleep(2000);
        printf("it feels ");
        Sleep(3000);
        printf("familiar...\n");
        Sleep(3000);
        printf("\n");
    } else {
        printf("You're back at where you first heard the scream.\n");
        Sleep(4000);
        printf("You don't know why you let your curiosity get the better of you.\n");
        Sleep(4000);
        printf("But at the same time, standing here won't get you anywhere.\n");
        Sleep(4000);
        printf("\n");
    }

    // Take action input from player
    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Go forward\n");
        printf("2. Go back\n");
        printf("3. exit\n");
        scanf("%d", &choice); getchar();

        system("cls");
        switch (choice) {
            case 1:
                break;
            case 2:
                printf("It's no use going back.\n");
                Sleep(2000);
                printf("You'll be back where you started.\n");
                Sleep(3000);
                phase++;
                break;
            case 3:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 3;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
    } while (choice != 1);

    return 0;
}

// Forest plane path
int pathForestPlane (int choice, int phase, char exit) {

    // Story
    if (pathProgress[1] == 0) {
        printf("The scream guides you deeper into the forest.\n");
        Sleep(4000);
        printf("Slowly but surely, ");
        Sleep(2000);
        printf("you move your aching leg.\n");
        Sleep(3000);
        printf("Determined to know if that scream is the answer you seek.\n");
        Sleep(4000);
        printf("But that determination comes to a halt...");
        Sleep(4000);

        system("cls");
        Sleep(2000);
        printf("In front of you lies the remains of what seems to be a plane.\n");
        Sleep(4000);
        printf("It's shape, jagged and misshapen, a sorrow reminder of it former self.\n");
        Sleep(5000);
        printf("Twisted metal and scattered debris litter the scene.\n");
        Sleep(4000);
        printf("The view is grim, yet it might hold the answer.\n");
        Sleep(4000);
        printf("\n");
    } else {
        printf("You return to the plane wreckage...\n");
        Sleep(3000);
        printf("Standing in front of the grim display.\n");
        Sleep(3000);
        printf("It's presence still makes you feel uneasy.\n");
        Sleep(4000);
        printf("\n");
    }

    // Take action input from player
    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Go inside\n");
        printf("2. Go forward\n");
        printf("3. Go back\n");
        printf("4. exit\n");
        scanf("%d", &choice); getchar();

        system("cls");
        switch (choice) {
            case 1:
                return 1;
                break;
            case 2:
                return 2;
                break;
            case 3:
                return 3;
                break;
            case 4:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
    } while (1);

    return 0;
}

// Inside crashed plane
int pathCrashedPlane (int choice, int phase, char exit) {

    // Story
    if (pathProgress[2] == 0) {
        printf("You step into the plane wreckage...\n");
        Sleep(3000);
        printf("Carefully treading over sharp, jagged debris and metal fragments.\n");
        Sleep(5000);
        printf("Inside...\n");
        Sleep(2000);
        printf("You're met with a grim display of what was once a majestic aircraft.\n");
        Sleep(5000);
        system("cls");
        Sleep(2000);
        printf("But there are two items in particular that have caught your attention.\n");
        Sleep(5000);
        printf("A black box, which might contain important informations about the plane's fate.\n");
        Sleep(5000);
        printf("As well as a briefcase, the only one left intact after the tragedy.\n");
        Sleep(5000);
        printf("\n");
    } else {
        printf("You step back inside of the plane wreckage...\n");
        Sleep(3000);
        printf("Still intrigued by what it might have to offer.\n");
        Sleep(4000);
        printf("\n");
    }

    // Take action input from player
    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Inspect the black box\n");
        printf("2. Inspect the briefcase\n");
        printf("3. Go back\n");
        printf("4. exit\n");
        scanf("%d", &choice); getchar();

        system("cls");
        switch (choice) {
            case 1:
                if (battery == 0) {
                    if (pathProgress[20] == 0) {
                        printf("You inspect the black box that sits at the front of the wreckage.\n");
                        Sleep(4000);
                        printf("You have a feeling that it will provide answers to all of this.\n");
                        Sleep(4000);
                        printf("You try everything to get it to work...\n");
                        Sleep(3000);
                        printf("To have it at least produce an audible sound.\n");
                        Sleep(3000);
                        printf("But it seems, however, that the black box has no power.\n");
                        Sleep(4000);
                    } else {
                        printf("It still has no power.\n");
                        Sleep(2000);
                    }
                } else {
                    if (pathProgress[20] == 0) {
                        printf("But it seems today is your lucky day...\n");
                        Sleep(3000);
                        printf("As it just so happened, you were carrying a battery.\n");
                        Sleep(4000);

                        system("cls");
                        Sleep(2000);
                        printf("Interesting...");
                        Sleep(3000);

                        Beep(1000, 2000);
                        printf("Inaudible sound.\n");
                    } else {
                        Beep(1000, 2000);
                        printf("Inaudible sound.\n");
                    }
                    
                }
                pathProgress[20] = 1;
                phase++;
                break;
            case 2:
                if (axe == 0) {
                    if (pathProgress[21] == 0) {
                        printf("You walk a bit deeper into the wreckage\n");
                        Sleep(3000);
                        printf("Walking past rows of torn and broken seats...\n");
                        Sleep(3000);
                        printf("You reach a lone briefcase at the end of the aisle.\n");
                        Sleep(4000);
                        printf("You lift the briefcase...\n");
                        Sleep(2000);
                        printf("It's weight signaling that there's probably something of importance inside.\n");
                        Sleep(5000);
                        printf("But despite your best efforts, ");
                        Sleep(2000);
                        printf("the lock wouldn't budge.\n");
                        Sleep(3000);
                    } else {
                        printf("It's locked.\n");
                        Sleep(2000);
                    }
                } else {
                    if (cloth == 0 || bandages == 0 || medicine == 0) { 
                        cloth = 1;
                        bandages = 1;
                        heal++;
                        medicine = 1;
                        heal++;
                        if (pathProgress[21] == 0) {
                            printf("But with the axe, that's conviniently sitting in your inventory...\n");
                            Sleep(4000);
                            printf("You break the briefcase open.\n");
                            Sleep(3000);

                            system("cls");
                            printf("Huh...");
                            Sleep(3000);

                            printf("Inside, there's a piece of cloth and a couple of bandages and medicine.\n");
                            Sleep(5000);
                            printf("You take it, just in case.\n");
                            Sleep(4000);
                        } else {
                            printf("With one swing, you break the briefcase open.\n");
                            Sleep(3000);
                            printf("Inside, there's a piece of cloth and a couple of bandages and medicine.\n");
                            Sleep(5000);
                            printf("It feels trivial, "); 
                            Sleep(2000);
                            printf("but you take it anyway just in case.\n");
                            Sleep(4000);
                        }
                    } else { 
                        printf("It's empty\n");
                        Sleep(2000);
                    }
                }
                pathProgress[21] = 1;
                phase++;
                break;
            case 3:
                return 3;
                break;
            case 4:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
    } while (1);

    return 0;
}

// Second forest path (left right) 
int pathForestTwo (int choice, int phase, char exit) {

    // Story
    if (pathProgress[3] == 0) {
        printf("Even though you were very curious beforehand...\n");
        Sleep(3000);
        printf("You decide to ignore the wreckage and continue your journey forward.\n");
        Sleep(4000);
        printf("It's presence sends chills down your spine and you're not risking going inside.\n");
        Sleep(5000);
        printf("But it's not long until you have to make another descision.\n");
        Sleep(4000);

        system("cls");
        Sleep(2000);
        printf("You reach a branching path, ");
        Sleep(2000);
        printf("both leading deeper into the forest.\n");
        Sleep(3000);
        printf("\n");
    } else if (pathProgress[3] == 1) {
        printf("After reaching a dead end inside the plane wreckage...\n");
        Sleep(3000);
        printf("You decide to ignore the wreckage and continue your journey forward.\n");
        Sleep(4000);
        printf("The thought of what had happened looms over your head\n");
        Sleep(3000);
        printf("But it's not long until you have to make another descision.\n");
        Sleep(4000);

        system("cls");
        Sleep(2000);
        printf("You reach a branching path, ");
        Sleep(2000);
        printf("both leading deeper into the forest.\n");
        Sleep(3000);
        printf("\n");
    } else {
        printf("You're back at the branching path.\n");
        Sleep(3000);
        printf("\n");
    }

    // Take action input from player
    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Go left\n");
        printf("2. Go right\n");
        printf("3. Go back\n");
        printf("4. exit\n");
        scanf("%d", &choice); getchar();

        system("cls");
        switch (choice) {
            case 1:
                return 1;
                break;
            case 2:
                return 2;
                break;
            case 3:
                return 3;
                break;
            case 4:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
    } while (1);

    return 0;
}

// Forest river path
int pathForestRiver (int choice, int phase, char exit) {

    // Story
    if (pathProgress[4] == 0) {
        printf("You choose to continue your journey to the path on the right.\n");
        Sleep(4000);
        printf("As you walk, you can hear a soft, murmured sound in the distance.\n");
        Sleep(4000);
        printf("It pulls you deeper...\n");
        Sleep(2000);
        printf("And it's not long until you reach the source of the sound.\n");
        Sleep(5000);

        system("cls");
        Sleep(2000);
        printf("In front of you lies a river.\n");
        Sleep(3000);
        printf("It's water constantly flowing, ");
        Sleep(3000);
        printf("producing a soothing sound for your ear.\n");
        Sleep(3000);
        printf("Along the riverside, you spotted a boat, abandoned and neglected.\n");
        Sleep(4000);
        printf("\n");
    } else {
        printf("You're back at the river.\n");
        Sleep(3000);
        printf("It's water fills you with a sense of calm.\n");
        Sleep(4000);
        printf("\n");
    }
	
	do {
		printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Inspect the boat\n");
        printf("2. Inspect the water\n");
        printf("3. Go back\n");
        printf("4. exit\n");
        scanf("%d", &choice); getchar();

        system("cls");
		switch (choice){
            case 1 : 
                return 1;
            case 2:
                printf("You approach the river.\n");
                Sleep(2000);
                printf("It's clear water mirrors the reflection of your face\n");
                Sleep(3000);
                printf("For the first time, ");
                Sleep(2000);
                printf("you felt safe and calm.\n");
                Sleep(3000);
                phase++;
                break;
            case 3:
                return 3;
            case 4:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
	}while (1);
	
	return 0;
}

// Inside river boat
int pathRiverBoat (int choice, int phase, char exit, char pass[]) {

    // Story
    if (pathProgress[5] == 0) {
        printf("You approach the abandoned boat, it's presence giving off an ominous vibe.\n");
        Sleep(5000);
        printf("As you look inside, two things captured your attention.\n");
        Sleep(4000);
        printf("There's a pile of wooden plank on the side of the boat.\n");
        Sleep(4000);
        printf("As well as a rusted box, located near the helm of the boat.\n");
        Sleep(5000);
        printf("\n");
    } else {
        printf("You're back at the boat.\n");
        Sleep(3000);
        printf("Still abandoned and neglected.\n");
        Sleep(4000);
        printf("\n");
    }

    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Inspect wood plank\n");
        printf("2. Inspect the rusted box\n");
        printf("3. Go back\n");
        printf("4. exit\n");
        scanf("%d", &choice); getchar();
        
        system("cls");
        char yourPass[4];
            //switch case in the boat
            switch (choice) {
            case 1:
                if (woodPlank == 0) {
                    woodPlank = 1;
                    printf("There's a few plank inside the boat\n");
                    Sleep(3000);
                    printf("It might be heavy, but it's always better to be safe.\n");
                    Sleep(4000);
                    printf("You picked up a few planks from the pile.\n");
                    Sleep(3000);
                }
                else if (woodPlank == 1){ 
                    printf("Your back is aching.\n");
                    Sleep(2000);
                    printf("You already have enough.\n");
                    Sleep(3000);
                }
                phase++;
                break;
            case 2:
                if (pathProgress[21] == 0) {
                    printf("You grab the rusty box.\n");
                    Sleep(3000);
                    printf("As you shake it, you can hear something glides around inside.\n");
                    Sleep(4000);
                    printf("But when you try to open it, the lock won't budge.\n");
                    Sleep(3000);  
                }
                printf("The lock requires a four digit code.\n");
                Sleep(3000);
                printf("Enter the code: ");
                scanf("%4s", yourPass); getchar();

                system("cls");
                if (lighter == 0) {
                    if (strcmp(pass, yourPass) == 0) {
                        lighter = 1;
                        if (pathProgress[24] == 1 && pathProgress[25] == 1) {
                            printf("The box swings open.\n");
                            Sleep(2000);
                            printf("Inside sits a lonely lighter, ");
                            Sleep(2000);
                            printf("still holding fuel despite its abandonment.\n");
                            Sleep(3000);
                            printf("You take the lighter, just in case.\n");
                            Sleep(3000);
                        } else {
                            printf("The box swings open.\n");
                            Sleep(4000);
                            printf("Miraculously, you've correctly guessed the code.\n");
                            Sleep(4000);
                            printf("It's like...\n");
                            Sleep(3000);

                            system("cls");
                            Sleep(2000);
                            printf("You've been here before...\n");
                            Sleep(4000);

                            system("cls");
                            Sleep(2000);
                            printf("Inside sits a lonely lighter, ");
                            Sleep(2000);
                            printf("still holding fuel despite its abandonment.\n");
                            Sleep(3000);
                            printf("You take the lighter, just in case.\n");
                            Sleep(3000);
                        }
                    } else {
                        printf("The box stays shut.\n");
                        Sleep(2000);
                    }
                } else {
                    printf("The box is empty.\n");
                    Sleep(2000);
                }
                pathProgress[21] = 1;
                phase++;
                break;
            case 3:
                return 3;
            case 4:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;    
            }
        } while (1);

    return 0;
    } 

// Forest bridge path
int pathForestBridge (int choice, int phase, char exit) {

    // Story
    if (pathProgress[7] == 0) {
        printf("You choose to continue your journey to the path on the left.\n");
        Sleep(4000);
        printf("In the distance, through the dense forest...\n");
        Sleep(3000);
        printf("You can see a clearing.\n");
        Sleep(3000);
        printf("The sky breaking trough, offering a glimpse of freedom.\n");
        Sleep(4000);
        printf("But that excitement comes to an abrupt halt.\n");
        Sleep(4000);

        system("cls");
        Sleep(2000);
        printf("Just in time actually.\n");
        Sleep(3000);
        printf("Right before you realize that the hope you've been chasing...\n");
        Sleep(4000);
        printf("Reveal itself to be a sheer ravine, cutting your path.\n");
        Sleep(4000);
        printf("Though a glimmer of hope shines again.\n");
        Sleep(3000);
        printf("When out of the corner of your eyes, ");
        Sleep(3000);
        printf("you catch a sight of a bridge.\n");
        Sleep(3000);
        printf("Looks old, but hopefully functional.\n");
        Sleep(3000);
        printf("\n");
    } else {
        printf("You're back at the bridge.\n");
        Sleep(3000);
        printf("Still hoping that it doesn't just fall apart.\n");
        Sleep(3000);
        printf("\n");
    }
    
    // Take action input from player
    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        if (ladder == 0) {
            printf("1. Go across\n");
            printf("2. Go back\n");
            printf("3. exit\n");
            scanf("%d", &choice); getchar();

            system("cls");
            switch (choice) {
                case 1:
                    if (pathProgress[8] == 0) {
                        if (woodPlank == 0) {
                            if (pathProgress[23] == 0) {
                                printf("You try to cross the bridge.\n");
                                Sleep(3000);
                                printf("But as you get halfway across, ");
                                Sleep(3000);
                                printf("You realize that there's quite a huge gap in the middle.\n");
                                Sleep(4000);
                                printf("You turn back, fully aware of you're weak physical state.\n");
                                Sleep(4000);
                                printf("Maybe there's something along your path that could help you get across safely?\n");
                                Sleep(5000);
                            } else {
                                printf("It's not safe to go across in this condition.\n");
                                Sleep(3000);
                            }
                            pathProgress[23] = 1;
                        } else {
                            if (pathProgress[23] == 0) {
                                printf("Using the wood planks that just so happened to have been obtained earlier...\n");
                                Sleep(5000);
                                printf("You close the gap on the bridge.\n");
                                Sleep(3000);

                                system("cls");
                                Sleep(2000);
                                printf("Well that's convenient...\n");
                                Sleep(3000);

                                system("cls");
                                Sleep(3000);
                                printf("Anyway...");
                                Sleep(2000);
                                pathProgress[23] = 1;
                            } else {
                                printf("Using the wooden planks, you close the gap on the bridge.\n");
                                Sleep(4000);
                                printf("With the gap already taken care of, you get across safely to the other side.\n");
                                Sleep(5000);
                            }
                        }
                    } else {
                        printf("You go across the bridge.\n");
                        Sleep(3000);
                        printf("Hoping that it doesn't just fall apart under your weight.\n");
                        Sleep(5000);
                    }
                    return 1;   
                    break;
                case 2:
                    return 3;
                    break;
                case 3:
                    // Exit command
                    printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                    
                    while (exit != 'Y' && exit != 'N'){
                        system("cls");
                        printf("Invalid input! Please choose from the given choice.\n");
                        scanf("%c", &exit); getchar();
                        exit = toupper(exit);
                    }
                    system("cls");
                    
                    if (exit == 'Y') {
                        return 4;
                    }
                    phase++;
                    break;
                default:
                    printf("Invalid input! Please choose from the given choice.\n");
                    phase++;
            }
        } else {
            printf("1. Go across\n");  
            printf("2. Go down\n");  
            printf("3. Go back\n");
            printf("4. exit\n");
            scanf("%d", &choice); getchar();

            system("cls");
            switch (choice) {
                case 1:
                    return 1;
                    break;
                case 2:
                    if (cloth == 0 || branch == 0 || lighter == 0 || gasoline == 0) {
                        printf("I dont think you're ready.\n");
                        Sleep(4000);
                        printf("It's really dark down there.\n");
                        Sleep(4000);
                    } else {
                        printf("Are you sure? [Y/N]\n");
                        Sleep(3000);
                        printf("Once you go down there there's no turning back\n");
                        Sleep(5000);

                        scanf("%c", &exit); getchar();
                        exit = toupper(exit);
                        
                        while (exit != 'Y' && exit != 'N'){
                            system("cls");
                            printf("Invalid input! Please choose from the given choice.\n");
                            scanf("%c", &exit); getchar();
                            exit = toupper(exit);
                        }
                        system("cls");
                        
                        if (exit == 'Y') {
                            return 2;
                        }
                    }
                    break;
                case 3:
                    return 3;
                    break;
                case 4:
                    // Exit command
                    printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                    
                    while (exit != 'Y' && exit != 'N'){
                        system("cls");
                        printf("Invalid input! Please choose from the given choice.\n");
                        scanf("%c", &exit); getchar();
                        exit = toupper(exit);
                    }
                    system("cls");
                    
                    if (exit == 'Y') {
                        return 4;
                    }
                    phase++;
                    break;
                default:
                    printf("Invalid input! Please choose from the given choice.\n");
                    phase++;
            }
        }
    } while (1);

    return 0;
}

// Forest cabin path
int pathForestCabin (int choice, int phase, char exit) {

    // Story
    if (pathProgress[26] == 0) {
        if (pathProgress[8] == 0) {
            printf("You keep pressing forward, shaking of the fatigue that starts to creep.\n");
            Sleep(5000);
            printf("But to your luck, you come across a little old cabin.\n");
            Sleep(4000);
            printf("It's presence, deep in the forest, is...\n");
            Sleep(3000);
            printf("enigmatic to say the least.\n");
            Sleep(3000);
            printf("\n");
        } else {
            if (pathProgress[9] == 0) {
                printf("You're standing in front of the old cabin.\n");
                Sleep(3000);
                printf("Your exhausted body urging you to look within.\n");
                Sleep(4000);
                printf("\n");
            }else {
                printf("You're standing in front of the old cabin.\n");
                Sleep(3000);
                printf("Puzzled by its presence deep in the forest\n");
                Sleep(4000);
                printf("\n");
            }
        }

        do {
		printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

		printf("1. Go inside\n");
		printf("2. Go back\n");
		printf("3. exit\n");
		scanf("%d", &choice); getchar();

		system("cls");
		system("cls");
        switch (choice) {
            case 1:
                return 1;
                break;
            case 2:
                return 3;
                break;
            case 3:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
            }   
	    } while (1);
    } else {
        printf("You're standing in front of the old cabin.\n");
        Sleep(3000);
        printf("Puzzled by its presence deep in the forest\n");
        Sleep(4000);
        printf("\n");

        do {
		printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

		printf("1. Go inside\n");
		printf("2. Go forward\n");
		printf("3. Go back\n");
		printf("4. exit\n");
		scanf("%d", &choice); getchar();

		system("cls");
		system("cls");
        switch (choice) {
            case 1:
                return 1;
                break;
            case 2:
                return 2;
            case 3:
                return 3;
                break;
            case 4:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
            }
        } while (1);
    }

    return 0;
}

// Inside cabin
int pathCabinInside (int choice, int phase, char exit) {

    // Story
    if (pathProgress[9] == 0) {
        printf("You step inside the cabin, ");
        Sleep(3000);   
        printf("doubtful yet hopeful at the same time.\n");
        Sleep(3000);
        printf("Yet, that worry is eased by a comforting view.\n");
        Sleep(4000);
        printf("Inside, there's a bed that you can rest on.\n");
        Sleep(3000);
        printf("Looks dirty, but at this point, you don't even care.\n");
        Sleep(4000);
        printf("There are also a few things adorning the cabin's interior.\n");
        Sleep(5000);
        printf("\n");
    } else {
        printf("You're back inside the cabin.\n");
        Sleep(3000);
        printf("It's cozy and warm atmosphere comforts you.\n");
        Sleep(4000);
        printf("\n");
    }

    do {
		printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

		printf("1. Inspect the cabin\n");
		printf("2. Take a rest\n");
		printf("3. Go back\n");
		printf("4. exit\n");
		scanf("%d", &choice); getchar();

		system("cls");
		switch (choice) {
            case 1 : 
                printf("The cabin is filled with a few stuff.\n");
                Sleep(3000);
                printf("There are items on the dinner table.\n");
                Sleep(3000);
                printf("Pictures hangs on the wall.\n");
                Sleep(3000);
                printf("And a book sits lonely on the bedside table.\n");
                Sleep(4000);
                printf("\n");

                do {
                    printf("What do you wish to do?\n");

                    if (phase == 0) {
                        Sleep(2000);
                    }

                    printf("1. Inspect the dinner table\n");
                    printf("2. Inspect the pictures\n");
                    printf("3. Inspect the book\n");
                    printf("4. Go back\n");
                    printf("5. exit\n");
                    scanf("%d", &choice); getchar();

                    system("cls");
                    switch (choice) {
                        case 1:
                            if (axe == 0 || painkiller == 0) {
                                axe = 1;
                                painkiller = 1;
                                heal++;
                                printf("You approach the dinner table.\n");
                                Sleep(3000);
                                printf("On top, there's an axe as well as a painkiller.\n");
                                Sleep(4000);
                                printf("Both of them seems useful, so you take them.\n");
                                Sleep(4000);
                            } else {
                                printf("The table is empty.\n");
                                Sleep(2000);
                                printf("You've already taken all the items.\n");
                                Sleep(3000);
                            }
                            break;
                        case 2:
                            if (pathProgress[25] == 0) {
                                pathProgress[25] = 1;
                                printf("You approach one of the cabin walls, it's adorned with a few pictures.\n");
                                Sleep(5000);
                                printf("Most of it are dirty and unclear.\n");
                                Sleep(3000);
                                printf("But one captured your attention.\n");
                                Sleep(3000);
                                printf(" ________________________\n");
                                printf("|  ____________________  |\n");
                                printf("| |////////////////////| |\n");
                                printf("| |////////////////////| |\n");
                                printf("| |////////////////////| |\n");
                                printf("| |////////////////////| |\n");
                                printf("|________________________|\n");
                                printf("|_________1990___________|\n");
                                Sleep(3000);
                                printf("It's a picture of what seems to be a man.\n");
                                Sleep(3000);
                                printf("Beside him is what seems to be a boat.\n");
                                Sleep(3000);
                                printf("He looked happy.\n");

                                getchar();
                                system("cls");
                            } else {
                                printf(" ________________________\n");
                                printf("|  ____________________  |\n");
                                printf("| |////////////////////| |\n");
                                printf("| |////////////////////| |\n");
                                printf("| |////////////////////| |\n");
                                printf("| |////////////////////| |\n");
                                printf("|________________________|\n");
                                printf("|_________1990___________|\n");

                                getchar();
                                system("cls");
                            }
                            break;
                        case 3 : 
                            if (pathProgress[24] == 0){
                                pathProgress[24] = 1;
                                printf("You approach the bedside table.\n");
                                Sleep(3000);
                                printf("Sitting on the bed, you grab the book and open it.\n");
                                Sleep(4000);
                                printf("Most of the pages are torn and illegible.\n");
                                Sleep(3000);
                                printf("But some of them are still readable.\n");
                                Sleep(4000);

                                system("cls");
                                printf("01/09/1992\n");
                                Sleep(2000);
                                printf("\"Living in this small cabin feels like\n");
                                printf("stepping away from the fast-paced world.\n");
                                Sleep(5000);
                                printf("Every morning, I wake up to sunlight streaming through the windows.\n");
                                Sleep(4000);
                                printf("The air here is fresh,\n");
                                Sleep(2000);
                                printf("filled with the scent of dew and the gentle sounds of bird chriping.\n");
                                Sleep(4000);
                                printf("Near here, just across the bridge, there's a river.\n");
                                Sleep(3000);
                                printf("There, lies my beloved boat, one of a kind really.\n");
                                Sleep(3000);
                                printf("I usually use it to get acrosss the river.\n");
                                Sleep(3000);
                                printf("But sometimes, fishing is on the schedule.\n");
                                Sleep(3000);
                                printf("Inside, there's a metal box, where i ususally keep my supply,\n");
                                Sleep(4000);
                                printf("especially the ones for my smoking needs.\n");
                                Sleep(3000);
                                printf("The box has a lock on it, for safety purposes.\n");
                                Sleep(3000);
                                printf("I don't want poeple tampering with my stuff.\n");
                                Sleep(3000);
                                printf("For the key, i use a four digit code, which is the year I get my beloved boat.\n");
                                Sleep(4000);
                                printf("That was a lovely day.\"\n");

                                getchar();
                                system("cls");
                            } else {
                                printf("01/09/1992\n");
                                printf("\"Living in this small cabin feels like\n");
                                printf("stepping away from the fast-paced world.\n");
                                printf("Every morning, I wake up to sunlight streaming through the windows.\n");
                                printf("The air here is fresh,\n");
                                printf("filled with the scent of dew and the gentle sounds of bird chriping.\n");
                                printf("Near here, just across the bridge, there's a river.\n");
                                printf("There, lies my beloved boat, one of a kind really.\n");
                                printf("I usually use it to get acrosss the river.\n");
                                printf("But sometimes, fishing is on the schedule.\n");
                                printf("Inside, there's a metal box, where i ususally keep my supply,\n");
                                printf("especially the ones for my smoking needs.\n");
                                printf("The box has a lock on it, for safety purposes.\n");
                                printf("I don't want poeple tampering with my stuff.\n");
                                printf("For the key, i use a four digit code, which is the year I get my beloved boat.\n");
                                printf("That was a lovely day.\"\n");

                                getchar();
                                system("cls");
                            }
                            break;
                        case 4:
                            printf("You're back, standing at the center of the cabin.\n");
                            Sleep(3000);
                            break;
                        case 5:
                            // Exit command
                            printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                            scanf("%c", &exit); getchar();
                            exit = toupper(exit);
                            
                            while (exit != 'Y' && exit != 'N'){
                                system("cls");
                                printf("Invalid input! Please choose from the given choice.\n");
                                scanf("%c", &exit); getchar();
                                exit = toupper(exit);
                            }
                            system("cls");
                            
                            if (exit == 'Y') {
                                return 4;
                            }
                            phase++;
                            break;
                        default:
                            printf("Invalid input! Please choose from the given choice.\n");
                            phase++;
                    }
                } while (choice != 4);
                break;
            case 2 :
                if (pathProgress[26] == 0) {
                    if (cloth == 1 && lighter == 1) {
                        printf("You proceed to take a rest.\n");
                        Sleep(3000);
                        printf("You lay your head on the bed.\n");
                        Sleep(3000);
                        printf("As your vision fading, \n");
                        Sleep(3000);
                        printf("You ask yourself whether you'll be able to escape this nightmare...\n");
                        Sleep(4000);
                        printf("Or will you be forever stuck here with no answers.\n");
                        Sleep(4000);
                        system("cls");

                        printf(".");
                        Sleep(1000);
                        printf(".");
                        Sleep(1000);
                        printf(".");
                        Sleep(1000);
                        system("cls");
                        Sleep(3000);
                        
                        Beep(1000, 1000);
                        printf("\"PLEASE!..\"\n");
                        Sleep(1000);
                        Beep(1000, 1000);
                        printf("\"I BEG YOU!..\"\n");
                        Sleep(1000);
                        Beep(1000, 1000);
                        printf("\"HE'S INNOCENT!..\"\n");
                        Sleep(1000);
                        Beep(1000, 1000);
                        printf("\"LET HIM HAVE A CHANCE AT LIFE!..\"\n");
                        Sleep(1000);
                        Beep(1000, 1000);
                        Sleep(1000);
                        Beep(1000, 1000);
                        printf("\"PLEEAASE, OH GOD-\"\n");
                        Beep(1000, 1000);
                        Sleep(1000);
                        Beep(1000, 1000);
                        Sleep(1000);
                        system("cls");
                        Sleep(3000);

                        printf("You wake up, drenched in sweat.\n");
                        Sleep(3000);
                        printf("Your heart pounding violently in your chest.\n");
                        Sleep(4000);
                        printf("The remnants of the nightmare cling to you like a heavy fog...\n");
                        Sleep(5000);
                        printf("Filling your head with even more questions.\n");
                        Sleep(4000);
                        printf("What's really hapening?");
                        Sleep(3000);
                        printf(" Why do you get these visions?..");
                        Sleep(3000);
                        system("cls");
                        Sleep(3000);
                        printf("What");
                        Sleep(1500);
                        printf(" have");
                        Sleep(1500);
                        printf(" you");
                        Sleep(1500);
                        printf(" done?");
                        Sleep(2000);
                        system("cls");
                        Sleep(3000);

                        printf("You decide to get out from the cabin.\n");
                        Sleep(3000);
                        printf("You're determined to find the answers to all of this.\n");
                        Sleep(4000);
                        printf("And it seems there's path that extends beyond the cabin.\n");
                        Sleep(5000);
                        pathProgress[26] = 1;
                        return 2;
                    } else {
                        printf("You're body urges you to take a rest.\n");
                        Sleep(3000);
                        printf("But you feel like there are still stuff you need to take care of.\n");
                        Sleep(4000);
                    }
                } else {
                    printf("You have enough rest.\n");
                    Sleep(2000);
                    printf("Lounging around won't give you answers.\n");
                    Sleep(4000);
                }
                break;
            case 3 :
                return 3;
                break;
            case 4:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
	} while (1);

    return 0;
}

// Third forest path (valley hill)
int pathForestThree (int choice, int phase, char exit) {

    if (pathProgress[10] == 0) {
        printf("You continue your journey beyond the cabin.\n");
        Sleep(4000);
        printf("It feels like the forest keeps stretching outward...\n");
        Sleep(5000);
        printf("Slowly revealing its hidden secrets\n");
        Sleep(4000);
        printf("But with your newfound energy, You press on.\n");
        Sleep(5000);
        printf("That is until another hurdle stands in your way.\n");
        Sleep(5000);

        system("cls");
        Sleep(2000);
        printf("In front of you lies another branching path.\n");
        Sleep(3000);
        printf("This time with varied elevation.\n");
        Sleep(3000);
        printf("\n");
    } else {
        printf("You're back at the branching path.\n");
        Sleep(3000);
        printf("The one with varied elevation.\n");
        Sleep(3000);
        printf("\n");
    }

    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Go down to the valley\n");
        printf("2. Go up to the hills\n");
        printf("3. Go back\n");
        printf("4. exit\n");
        scanf("%d", &choice); getchar();

        system("cls");
        switch (choice) {
            case 1:
                return 1;
                break;
            case 2:
                return 2;
                break;
            case 3:
                return 3;
                break;
            case 4:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
    } while (1);

    return 0;
}

// Forest bunker (valley)
int pathForestBunker (int choice, int phase, char exit, char pass[]) {

    if (pathProgress[11] == 0) {
        printf("You choose to go down the path on the left.\n");
        Sleep(4000);
        printf("As the path gradually descends, it eventually opens into a valley.\n");
        Sleep(5000);
        printf("The surrounding forest falls silent, as if preparing to unveil something.\n");
        Sleep(5000);
        printf("And unveil it does, as amidst the stillness, you discover a strange metal door.\n");
        Sleep(6000);

        system("cls");
        Sleep(2000);
        printf("You stand in front a metal door, deep in the forest.\n");
        Sleep(4000);
        printf("Its size, larger than most, gives off an imposing presence.\n");
        Sleep(5000);
        printf("Looking at the intricate detail adorning the door...\n");
        Sleep(4000);
        printf("It looks like the door is an entrance to a bunker.\n");
        Sleep(4000);
        printf("\n");
    } else {
        printf("You're back standing in front of the bunker.\n");
        Sleep(4000);
        printf("Its large metal door, gives off an imposing presence.\n");
        Sleep(5000);
        printf("\n");
    }

    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Go inside\n");
        printf("2. Inspect the surroundings\n");
        printf("3. Go back\n");
        printf("4. exit\n");
        scanf("%d", &choice); getchar();

        system("cls");
        switch (choice) {
            case 1:
                char yourPass[5];
                if (pathProgress[12] == 0) {
                    if (pathProgress[27] == 0) {
                        printf("You approach the large metal door.\n");
                        Sleep(3000); 
                        printf("Despite its old and rusty appearance, it's surprisingly firm.\n");
                        Sleep(5000); 
                        printf("You push against it with all your strength, trying to force it open.\n");
                        Sleep(5000); 
                        printf("But alas, you're not strong enough.\n");
                        Sleep(4000);

                        system("cls");
                        Sleep(2000);
                        printf("But after a closer inspection, ");
                        Sleep(2000);
                        printf("looks like the door needs a five digit code.\n"); 
                        Sleep(4000);
                        printf("\n");
                    } else {
                        
                        printf("The door needs a five digit code.\n");
                        Sleep(3000);
                        printf("\n");
                    }

                    printf("    /-----| /----[]-------|  /---\\  \n");
                    printf("   / &&   |/     ||  ##   | |     \\ \n");
                    printf("|\\|              ||       |/      #|\n");
                    printf("|    **          ||                |\n");
                    printf("|                ||               #|\n");
                    printf("|#     @@    +[] || []+           #|\n");
                    printf("|#    @  @       ||          *     |\n");
                    printf("|     @  @   +[] || []+            |\n");
                    printf("|      @         ||                |\n");
                    printf("|#               ||  *            _|\n");
                    printf("|_    *     \\    ||         \\    /  \n");
                    printf("  \\__ +++    |   ||      /   |  |   \n");
                    printf("     \\------/|---[]-----|\\--/|-/    \n");
                    printf("\n");
                    printf("Enter the code: ");
                    scanf("%5s", yourPass); 
                    
                    if (strcmp(yourPass, pass) == 0){
                        return 1;
                    } else {
                        printf("The door remains shut.\n");
                        Sleep(2000);
                        printf("Perhaps there's a clue around the bunker?\n");
                        Sleep(3000);
                    }
                    pathProgress[27] = 1;
                } else {
                    pathProgress[27] = 1;
                    printf("You enter the bunker.\n");
                    Sleep(2000);
                    return 1;
                }
                break;
            case 2:
                if (pathProgress[28] == 0){
                    printf("You walk around the bunker...\n");
                    Sleep(2000);
                    printf("Frantically searching for any sign of interest.\n");
                    Sleep(3000);
                    printf("The bunker surroundings were covered in moss and plantations.\n");
                    Sleep(4000);
                    printf("But amongst the green cover, you notice a clear concrete wall.\n");
                    Sleep(5000);
                    printf("On it, is a weird looking grafitti.\n");
                    Sleep(4000);
                    system("cls");
                    Sleep(2000);
                } else {
                    printf("You're back at the concrete wall.\n");
                    Sleep(2000);
                    printf("Still wondering why there's a grafitti deep in this forest.\n");
                    Sleep(4000);
                    printf("\n");
                }

                printf("           __ __        ___     ______ \n");
                printf("  __/|_ __/ // /_  __  ( _ )   / ____ \\\n");
                printf(" |    //_  _  __/_/ /_/ __ \\/|/ / __ `/\n");
                printf("/_ __|/_  _  __/_  __/ /_/  </ / /_/ / \n");
                printf(" |/    /_//_/   /_/  \\____/\\/\\ \\__,_/  \n");
                printf("                              \\____/   \n");
                printf("\n");
                printf("   __ __             __  ___         __ ___ \n");
                printf("  / // /__ _    __  /  |/  /_ ______/ //__ \\\n");
                printf(" / _  / _ \\ |/|/ / / /|_/ / // / __/ _ \\/__/\n");
                printf("/_//_/\\___/__,__/ /_/  /_/\\_,_/\\__/_//_(_)  \n");
                printf("\n");
                Sleep(2000);
                printf("Wonder what it signifies?\n");
                getchar();
                pathProgress[28] = 1;
                break;
            case 3:
                return 3;
                break;
            case 4:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
    } while (1);

    return 0;

}

// Inside cabin
int pathBunkerInside (int choice, int phase, char exit) {

    if (pathProgress[12] == 0) {
        if (pathProgress[28] == 0 && pathProgress[27] == 0) {
            printf("Congratulations...\n");
            Sleep(2000);
            printf("You successfully guessed the code.\n");
            Sleep(3000);
            printf("And on your first try too.\n");
            Sleep(3000);

            system("cls");
            printf("I guess you're really special huh...\n");
            Sleep(4000);

            system("cls");
            printf("Or are you starting to remember...\n");
            Sleep(4000);

            system("cls");
            printf("Whatever...\n");
            Sleep(3000);
            system("cls");
        } else if (pathProgress[28] == 0 && pathProgress[27] != 0) {
            printf("Congratulations...\n");
            Sleep(2000);
            printf("You successfully guessed the code.\n");
            Sleep(3000);

            system("cls");
            printf("I guess you're really special huh...\n");
            Sleep(4000);
            
            system("cls");
            printf("Whatever...\n");
            Sleep(3000);
            system("cls");
        } else {
            printf("The door creaks open, the loud sound echoing its age.\n");
            Sleep(5000);
        }

        printf("You stepped inside the bunker.\n");
        Sleep(3000);
        printf("The air is thick, heavy with the scent of decay and dust.\n");
        Sleep(5000);
        printf("The space is vast, its dimensions unclear in the dim light.\n");
        Sleep(5000);

        system("cls");
        Sleep(2000);
        printf("Fear begins to set in...\n");
        Sleep(3000);
        printf("A growing unease about the unknown that lies beyond\n");
        Sleep(5000);
        printf("Each steps only heightens the tension.\n");
        Sleep(4000);
        printf("But you know, it's either this or nothing at all.\n");
        Sleep(5000);
        
        system("cls");
        Sleep(2000);
        printf("You stand in the middle of the dark room.\n");
        Sleep(4000);
        printf("Amidst the darkness, you can spot a few different things.\n");
        Sleep(5000);
        printf("There's a safe in the corner of the room, dimly lit by a lonely bulb.\n");
        Sleep(5000);
        printf("And a door, located at the far end of the bunker.\n");
        Sleep(5000);
        printf("\n");
    } else {
        printf("You're back, standing in the middle of the dark room.\n");
        Sleep(4000);
        printf("The darkness sends shivers down our spine.\n");
        Sleep(5000);
    }

    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Inspect the safe\n");
        printf("2. Inspect the door\n");
        printf("3. Go back\n");
        printf("4. exit\n");
        scanf("%d", &choice); getchar();

        system("cls");
        switch (choice) {
            case 1:
                if (pathProgress[30] == 0) {
                    if (pathProgress[29] == 0) {
                        printf("You approach the safe...\n");
                        Sleep(3000);
                        printf("Hoping that it would just pry open without any trouble.\n");
                        Sleep(5000);
                        printf("But of course it's not that easy.\n");
                        Sleep(5000);

                        system("cls");
                        Sleep(2000);
                        printf("It will never be easy.\n");
                        Sleep(3000);
                        printf("Not for you...\n");
                        Sleep(3000);

                        system("cls");
                        Sleep(2000);

                        printf("It looks like the safe has a rotary combination lock.\n");
                        Sleep(5000);
                        printf("You know the drill.\n");
                        Sleep(3000);
                        printf("You must listen for a \"click sound\" before rotating the lock.\n");
                        printf("to the opposite direction.\n");
                        Sleep(7000);
                    } else {
                        printf("The safe has a rotary combination lock.\n");
                        Sleep(5000);
                        printf("Listen for a \"click sound\" before rotating the lock.\n");
                        printf("to the opposite direction.\n");
                        Sleep(6000);
                    }

                    pathProgress[29] = 1;
                    printf("Ready?\n");
                    getchar();
                    printf("Press any key to turn the lock.\n");
                    Sleep(2000);

                    int hits = 0;
                    int attempts = 0;
                    int fail = 0;
                    while (hits < 3) {
                        int delay = rand() % 9 + 1;
                        delay *= 1000;

                        Sleep(delay);

                        Beep(500, 500);
                        
                        int startTime = time(NULL);

                        while (!kbhit()) {
                            if (time(NULL) - startTime >= 2) {
                                printf("You failed!\n");
                                Sleep(2000);
                                fail = 1;
                                break;
                            }
                        }

                        if (fail != 0) {
                            break;
                        }

                        getch();
                        printf("Great!\n");
                        hits++;
                        attempts++;

                        if (hits == 3) {
                            system("cls");
                            printf("The safe cracked open!\n");
                            Sleep(2000);
                            break;
                        }
                    }
                    if (fail == 0) {
                        storageKey = 1;
                        battery = 1;
                        medkit = 1;
                        heal++;
                        pathProgress[30] = 1;
                        printf("Inside there's a few items that might be helpful.\n");
                        Sleep(5000);
                        printf("There's a battery, old but looks functional.\n");
                        Sleep(4000);
                        printf("There's also a key, a medkit, as well as a newspaper.\n");
                        Sleep(5000);
                        printf("You decided to take a read of the main news page.\n");
                        Sleep(5000);

                        system("cls");
                        Sleep(2000);
                        printf("Mystery Surrounds Plane 5046 Crash\n");
                        Sleep(2000);
                        printf("Flight ID 5046, a commercial airliner traveling from New York to Los Angeles,\n");
                        printf("crashed in Harrison, Indiana yesterday, killing all 174 aboard.\n");
                        Sleep(5000);
                        printf("While the cause remains under investigation,\n");
                        printf("authorities are leaning toward the possibility of a suicide bombing\n");
                        printf("after fragments of what may be an explosive device were found among the wreckage.\n");
                        Sleep(5000);
                        printf("The rest of the newspaper is unreadable.\n");
                        getchar();
                        system("cls");
                    }
                } else {
                    printf("Mystery Surrounds Plane 5046 Crash\n");
                    printf("Flight ID 5046, a commercial airliner traveling from New York to Los Angeles,\n");
                    printf("crashed in Harrison, Indiana yesterday, killing all 174 aboard.\n");
                    printf("While the cause remains under investigation,\n");
                    printf("authorities are leaning toward the possibility of a suicide bombing\n");
                    printf("after fragments of what may be an explosive device were found among the wreckage.\n");
                    printf("The rest of the newspaper is unreadable.\n");
                    getchar();
                    system("cls");
                }
                break;
            case 2:
                if (storageKey == 0) {
                    if (pathProgress[13] == 0) {
                        printf("You approach the lone door.\n");
                        Sleep(3000);
                        printf("Its existence is an enigma on its own.\n");
                        Sleep(4000);
                        printf("You try to open the door.\n");
                        Sleep(3000);
                        printf("But of course, the door is locked.\n");
                        Sleep(4000);
                        printf("Maybe there's a key laying around here somewhere?\n");
                        Sleep(5000);
                        pathProgress[13] = 1;
                    } else {
                        printf("The door is locked.\n");
                        Sleep(2000);
                        printf("Maybe there's a key laying around here somewhere?\n");
                        Sleep(5000);
                    }
                } else {
                    if (gasoline == 0) {
                        gasoline = 1;
                        printf("The door creaks open.\n");
                        Sleep(3000);
                        printf("As you open the door...\n");
                        Sleep(3000);
                        printf("A weird stench can be smelled from within the room.\n");
                        Sleep(5000);
                        printf("And you soon discover the source of the smell.\n");
                        Sleep(5000);
                        printf("A lone canister of gasoline sits neatly inside the storage room.\n");
                        Sleep(5000);
                        printf("Despite the smell, you grab it...\n");
                        Sleep(4000);
                        printf("Again, just in case.\n");
                        Sleep(3000);
                    } else {
                        printf("The room is empty.\n");
                        Sleep(2000);
                        printf("All that's left is the unpleasant stench.\n");
                        Sleep(4000);
                    }
                }
                break;
            case 3:
                return 3;
                break;
            case 4:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
    } while (1);

    return 0;
}

// Forest graveyard (hill)
int pathForestGraveyard (int choice, int phase, char exit, char pass[]){

    if (pathProgress[14] == 0) {
        printf("You choose to go down the path on the right.\n");
        Sleep(4000);
        printf("As the path gradually rises...\n");
        Sleep(3000); 
        printf("You wish you could see a way out of this nightmare.\n");
        Sleep(4000);
        printf("But any hope you had quickly fades as you're met with a grim sight.\n");
        Sleep(5000);

        system("cls");
        Sleep(2000);
        printf("At the top of the hill stands a graveyard, forsaken and deteriorating.\n");
        Sleep(5000);
        printf("Your first instinct is to immediately turn back.\n");
        Sleep(4000);
        printf("But something, or someone urges you to take a look.\n");
        Sleep(4000);
        printf("\n");
    } else {
        printf("You're back at the graveyard site.\n");
        Sleep(3000);
        printf("Still questioning what you’ve gotten yourself into.\n");
        Sleep(4000);
        printf("\n");
    }

    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Go to the gate\n");
        printf("2. Go back\n");
        printf("3. exit\n");
        scanf("%d", &choice); getchar();

        system("cls");
        switch (choice) {
            case 1:
                if (pathProgress[31] == 0) {
                    printf("You approach the gate.\n");
                    Sleep(3000);
                    printf("Its crooked shape fills you with a sense of unease.\n");
                    Sleep(5000);
                    printf("A skull-shaped lock hangs on the gate, waiting to be opened.\n");
                    Sleep(5000);
                    printf("The skull has three teeth...");
                    Sleep(3000);
                    printf("Each one designed to accept a single digit for a code.\n");
                    Sleep(5000);
                }

                pathProgress[31] = 1;
                char yourPass[3];
                printf("Beside the gate stands a sign, engraved with the words...\n");
                Sleep(5000);
                printf("Y O U R\n");
                printf("C A S U A L T I E S\n");
                Sleep(3000);
                printf("Enter the code: ");
                scanf("%3s", yourPass);
                
                if (strcmp(yourPass, pass) == 0){
                    return 1;
                } else {
                    printf("The gate remains shut.\n");
                    Sleep(2000);
                    printf("What does \"casualties\" means?\n");
                    Sleep(3000);
                }
                break;
            case 2:
                return 2;
                break;
            case 3:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
    } while (1);

    return 0;

}

// Inside graveyard function
int pathGraveyardInside (int choice, int phase, char exit) {

    int screamPhase = 0;
    int gravePhase = 0;
    pathProgress[15] = 1;
    if (pathProgress[15] == 0) {
        if (pathProgress[30] == 0) {
            printf("Another code solved quickly.\n");
            Sleep(2000);
            printf("You're really good at this.\n");
            Sleep(4000);

            system("cls");
            printf("I'm starting to think...\n");
            Sleep(3000); 
            printf("That my narration is just a hindrance for you.\n");
            Sleep(5000);

            system("cls");
            printf("You're no fun...\n");
            system("cls");
        } else {
            printf("The gate opens dramatically.\n");
            Sleep(5000);
        }

        printf("As you stepped inside the graveyard...\n");
        Sleep(3000);
        printf("You can immediately feel the presence of someone...\n");
        Sleep(4000);
        printf("Or everyone, its not that clear.\n");
        Sleep(3000);

        system("cls");
        Sleep(1500);
        Beep(750, 500);
        printf("\"HELP ME!..\"\n");
        Sleep(2000);
        printf("PLEASE!..\n");
        Sleep(3000);
        system("cls");
        printf("\n");
    } else {
        Beep(750, 500);
        randomScreams(screamPhase);
        printf("\"%s\"\n", scream);
        Sleep(4000);
        system("cls");
        printf("\n"); 
    }

    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Look around\n");
        printf("2. Go back\n");
        printf("3. exit\n");
        scanf("%d", &choice); getchar();
        
        gravePhase++;
        if (gravePhase == 5) {
            screamPhase++;
        }
        system("cls");
        switch (choice) {
            case 1:
                Sleep(1500);
                if (gravePhase == 4) {
                    branch = 1;
                    printf("You get a wooden branch.\n");
                    Sleep(4000);
                } else if (gravePhase == 10) {
                    ladder = 1;
                    printf("You found a ladder.\n");
                    Sleep(4000);
                    printf("Now that I mentioned a ladder...\n");
                    Sleep(4000);
                    printf("I think i saw something at the bottom of the bridge.\n");
                    Sleep(5000);
                    printf("Maybe you should check it out.\n");
                    Sleep(5000);
                } else if (gravePhase == 15) {
                    printf("Why are you still here?..\n");
                    Sleep(4000);
                } else if (gravePhase == 20) {
                    printf("You're weird?..\n");
                    Sleep(4000);
                } else if (gravePhase > 30) {
                    printf("...\n");
                    Sleep(4000);
                } else {
                    if (screamPhase == 0) {
                        Beep(750, 500);
                    } else {
                        Beep(250, 500);
                    }
                    randomScreams(screamPhase);
                    printf("\"%s\"\n", scream);
                    Sleep(4000);
                    system("cls");
                    printf("\n");
                }
                Sleep(2000);
                break;
            case 2:
                return 2;
                break;
            case 3:
                // Exit command
                printf("Are you sure you want to go back to the main menu? [Y/N]\n");
                scanf("%c", &exit); getchar();
                exit = toupper(exit);
                
                while (exit != 'Y' && exit != 'N'){
                    system("cls");
                    printf("Invalid input! Please choose from the given choice.\n");
                    scanf("%c", &exit); getchar();
                    exit = toupper(exit);
                }
                system("cls");
                
                if (exit == 'Y') {
                    return 4;
                }
                phase++;
                break;
            default:
                printf("Invalid input! Please choose from the given choice.\n");
                phase++;
        }
    } while (1);

    return 0;
}

// Random screams
void randomScreams(int phase) {
    char screamList[6][20];

    if (phase == 0) {
        strcpy(screamList[0], "HELP ME!..");
        strcpy(screamList[1], "PLEASE!..");
        strcpy(screamList[2], "HAVE MERCY!..");
        strcpy(screamList[3], "PLEASE GOD!..");
        strcpy(screamList[4], "*screams*");
        strcpy(screamList[5], "*cries*");
    } else {
        strcpy(screamList[0], "IT'S YOUR FAULT!");
        strcpy(screamList[1], "YOU'RE A DISGRACE!");
        strcpy(screamList[2], "I HATE YOU!");
        strcpy(screamList[3], "BASTARD!");
        strcpy(screamList[4], "*laughs*");
        strcpy(screamList[5], "PITIFUL!");
    }

    int randomPicker = rand() % 7;
    strcpy(scream, screamList[randomPicker]);
}

int pathForestCave (int choice, int phase, char exit) {

    printf("You decided to go down the bridge.\n");
    Sleep(3000);
    printf("Darkness filled your surroundings.\n");
    Sleep(3000);
    printf("But that don't bother you...\n");
    Sleep(3000);
    printf("Not anymore.\n");
    Sleep(3000);
    printf("You start to wrap the cloth around the branch...\n");
    Sleep(5000);
    printf("Before dousing the cloth in gasoline.\n");
    Sleep(4000);
    printf("And with the help of the lighter...\n");
    Sleep(4000);
    printf("You ignite to your makeshift torch.\n");
    Sleep(5000);

    system("cls");
    Sleep(2000);
    printf("As you venture deeper...\n");
    Sleep(3000);
    printf("The questions in your mind shift into unwavering determination.\n");
    Sleep(6000);
    printf("And it's not long before that determination...\n");
    Sleep(5000);
    printf("Finally came to fruition.\n");
    Sleep(4000);

    system("cls");
    Sleep(2000);
    printf("In front of you lies three doors.\n");
    Sleep(4000);
    printf("Here it is.\n");
    Sleep(3000);
    printf("Your final hurdle.\n");
    Sleep(3000);

    do {
        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Go forward\n");
        getchar();
        getchar();

        system("cls");
        endOne:
        int END = firstEnd();
        if (END == 0) {
            heal--;
            if (heal == 0) {
                return 0;
            }
            printf("You have %d healing item left.\n", heal);
            Sleep(4000);
            printf("Use it wisely.\n");
            getchar();
            printf("Let's try that again shell we.\n");
            Sleep(5000);
            goto endOne;
        }

        printf("What do you wish to do?\n");

        if (phase == 0) {
            Sleep(2000);
        }

        printf("1. Go forward\n");
        getchar();
        getchar();

        
        endTwo:
        END = secondEnd();
        if (END == 0) {
            heal--;
            if (heal == 0) {
                return 0;
            }
            printf("You have %d healing item left.\n", heal);
            Sleep(4000);
            printf("Use it wisely.\n");
            getchar();
            printf("Let's try that again shall we.\n");
            Sleep(5000);
            goto endTwo;
        }

        endThree:
        END = thirdEnd();
        if (END == 0) {
            heal--;
            if (heal == 0) {
                return 0;
            }
            printf("You have %d healing item left.\n", heal);
            Sleep(4000);
            printf("Use it wisely.\n");
            getchar();
            printf("Let's try that again shall we.\n");
            Sleep(5000);
            goto endThree;
        }

        return 1;
        
    } while (1);

    return 0;
}

int firstEnd () {
    char kata[] = "PREGNANCY"; 
    int panjangKata = strlen(kata);
    int tebakanBenar[50] = {0}; 
    char tebakan;
    int peluang = 7;
    int semuaTebakanBenar = 0;

    printf("Welcome to your first END.\n");
    Sleep(3000);
    printf("In front of you lies an image.\n");
    Sleep(3000);
    printf("Its a bit vague, but you can make out the form.\n");
    Sleep(5000);
    system("cls");
    printf("  __                    \n");
    printf(" /  \\                  \n");
    printf("|    |                \n");
    printf(" \\__/         __          \n");
    printf(" /           /  \\       \n");
    printf("|            \\__/       \n");
    printf("|              |         \n");
    printf("|___      _____|         \n");
    printf("|   \\____/     |       \n");
    printf("|\\             |        \n");
    printf("| \\           /|         \n");
    printf("|  |         |  \\__    \n");
    printf("|  |          \\          \n");
    printf("| /                      \n");
    printf("\n");
    printf("  H O W   C O U L D \n");
    printf("      Y O U \n");
    printf("\n");
    Sleep(5000);

    while (peluang > 0 && semuaTebakanBenar < panjangKata) {

        const char *nextClue;
        nextClue = clue();
        printf("%s\n", nextClue);
        tampilkanKata(kata, tebakanBenar);
        printf("Guess: ");
        scanf(" %c", &tebakan);
        tebakan = toupper(tebakan);

        int adaTebakanBenar = 0;

        for (int i = 0; i < panjangKata; i++) {
            if (kata[i] == tebakan) {
                tebakanBenar[i] = 1; 
                adaTebakanBenar = 1;
                semuaTebakanBenar++;
            }
        }

        if (!adaTebakanBenar) {
            peluang--;
            printf("You should pay more attention, %d left.\n", peluang);
        }
    }
    system("cls");
    Sleep(2000);
    if (semuaTebakanBenar == panjangKata) {
        printf("Congragulation...");
        Sleep(2000);
        printf("You have finished your first END.\n");
        Sleep(4000);
        printf("I'll be waiting for you in the next room.\n");
        getchar();
        getchar();
        return 1;
    } else {
        printf("Ouch, that hurts.\n");
        getchar();
        getchar();
        return 0;
    }

    return 0;
}

int secondEnd () {

    int low = 1, high = 20;
    int target, guess, attempts = 5;

    target = (rand() % (high - low + 1)) + low;

    printf("For your second END...\n");
    Sleep(3000);
    printf("You see a bomb, resting on a pedestal.\n");
    Sleep(4000);
    printf("You feel conflicted...\n");
    Sleep(3000);
    printf("But it's never wrong to defuse a bomb that can harm hundred of lives, right?\n");
    Sleep(6000);
    printf("Defuse it by guessing a number between 1 and 20\n");
    Sleep(5000);

    while (1) {
        printf("Guess: ");
        scanf("%d", &guess);

        if (guess < target) {
            printf("Hinger!\n");
            low = guess + 1;
        } else if (guess > target) {
            printf("Lower!\n");
            high = guess - 1;
        } else {
            printf("Congratulation!..\n");
            Sleep(2000);
            printf("You're getting closer.\n" );
            Sleep(3000);
            return 1;
        }

        //binary search
        int suggestion = (low + high) / 2;
        printf("Clue!! Near %d.\n", suggestion);
        attempts--;
        printf("%d tries left.\n", attempts);
    }

}

int thirdEnd () {

    char *testcases[20][2] = {
        {"hatchers", "Thecrash"},
        {"spineboxblooms", "bombexplosions"},
        {"notationatdesk", "Detonationtask"},
        {"loyalsuit", "Itsallyou"},
        {"artfulloyalsuit", "Itsallyourfault"}
    };
    char input1[100], input2[100];

    printf("And here we are, at your third and last END.\n");
    Sleep(5000);
    printf("Aren't you excited.\n");
    Sleep(3000);
    printf("Excited to know the answers to of all of this.\n");
    Sleep(5000);
    printf("Well...\n");
    Sleep(2000);
    printf("Why dont you rearangge these words first.\n");
    Sleep(5000);
    printf("Then, you will know the answer.\n");
    Sleep(5000);
    system("cls");
    Sleep(2000);
    printf("Oh yeah, one more thing.\n");
    Sleep(4000);
    printf("You only get one try for each question.\n");
    Sleep(5000);
    system("cls");
    Sleep(2000);
    
    printf("FIRST!! %s\n", testcases[0][0]);
    printf("CLUE!! T _ _ - _ R A _ H");
    printf("Guess: ");
    scanf("%s", input2);

    if (isAnagram(testcases[0][0], input2)) {
            printf("Correct!");
        } else {
            printf("Ouch\n");
            Sleep(3000);
            return 0;
        }

    printf("SECOND!! %s\n", testcases[1][0]);
    printf("CLUE!! B _ M _- _ _ P _ O _ _ _ O N");
    printf("Guess: ");
    scanf("%s", input2);

    if (isAnagram(testcases[1][0], input2)) {
            printf("Correct!");
        } else {
            printf("Well, you tried\n");
            Sleep(3000);
            return 0;
        }


    printf("THIRD!! %s\n", testcases[2][0]);
    printf("CLUE!! D _ _ O _ _ T _ _ O _ - _ A _ K");
    printf("Guess: ");
    scanf("%s", input2);

    if (isAnagram(testcases[2][0], input2)) {
            printf("Correct!");
        } else {
            printf("Tough luck\n");
            Sleep(3000);
            return 0;
        }


    printf("FOURTH!! %s\n", testcases[3][0]);
    printf("CLUE!! I _ _ - A _ _ - _ U O");
    printf("Guess: ");
    scanf("%s", input2);

    if (isAnagram(testcases[3][0], input2)) {
            printf("Correct!");
        } else {
            printf("Sorry\n");
            Sleep(3000);
            return 0;
        }


    printf("LAST!! %s\n", testcases[4][0]);
    printf("CLUE!! _ _ S - _ L _ - _ O _ _ - _ A _ _ T");
    printf("Guess: ");
    scanf("%s", input2);

    if (isAnagram(testcases[4][0], input2)) {
            printf("Correct!");
        } else {
            printf("So close\n");
            Sleep(3000);
            return 0;
        }
    return 1;
}

void tampilkanKata(char *kata, int *tebakanBenar) {
    for (int i = 0; i < strlen(kata); i++) {
        if (tebakanBenar[i]) {
            printf("%c ", kata[i]); 
        } else {
            printf("_ "); 
        }
    }
    printf("\n");
}

const char* clue() {
    if (clueCount == 0) {
        FILE *file = fopen("clues.txt", "r");
        if (file == NULL) {
            perror("Error opening file");
            return NULL;
        }

        while (fgets(clues[clueCount], 256, file) != NULL) {
            clues[clueCount][strcspn(clues[clueCount], "\n")] = '\0'; // Remove newline
            clueCount++;
            if (clueCount >= 100) break;
        }

        fclose(file);
        for (int i = 0; i < clueCount; i++) {
            int j = rand() % clueCount; 
            char temp[256];
            strcpy(temp, clues[i]);
            strcpy(clues[i], clues[j]);
            strcpy(clues[j], temp);
        }
        currentClueIndex = 0;
    }

    if (currentClueIndex < clueCount) {
        return clues[currentClueIndex++];
    } else {
        return NULL;
    }
}

void sortString(char *str) {
    int n = strlen(str);
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (str[j] > str[j + 1]) {
                char temp = str[j];
                str[j] = str[j + 1];
                str[j + 1] = temp;
            }
        }
    }
}

int isAnagram(char *str1, char *str2) {

    if (strlen(str1) != strlen(str2)) {
        return 0;
    }

  
    char *sortedStr1 = strdup(str1);
    char *sortedStr2 = strdup(str2);

   
    sortString(sortedStr1);
    sortString(sortedStr2);

    
    int result = strcmp(sortedStr1, sortedStr2) == 0;

   
    free(sortedStr1);
    free(sortedStr2);

    return result;
}