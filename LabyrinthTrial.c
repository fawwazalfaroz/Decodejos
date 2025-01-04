#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <conio.h>
#include <windows.h>

void showInventory (int axe, int cloth, int plank, int lighter, int ladder, int battery, char pass[]);
void mainTitle();
int mainMenu();
void gameOpening();
int pathForestStart(int choice, int startPhase, int phase, char exit);
int pathForestOne (int choice, int phase, char exit, int progress[]);
int pathForestPlane (int choice, int phase, char exit, int progress[]);
int pathCrashedPlane (int choice, int phase, char exit, int progress[], int battery, int axe, int *cloth, int *bandages, int *medicine);
int pathForestTwo (int choice, int phase, char exit, int progress[]);
int pathForestRiver (int choice, int phase, char exit, int progress[]);
int pathRiverBoat (int choice, int phase, char exit, int progress[], int *plank, int *lighter, char pass[]);
int pathForestBridge (int choice, int phase, char exit, int progress[], int plank, int ladder);
int pathForestCabin (int choice, int phase, char exit, int progress[]);
int pathCabinInside (int choice, int phase, char exit, int progress[], int *axe, int *painkiller, int cloth, int lighter);
int pathForestThree ();
int pathForestCave ();

int main () {

    int menuChoice, playerChoice;

    do {
        // Player input declaration
        int startChoicePhase = 0, choicePhase = 0;
        // Progression item declaration
        int axe = 0, cloth = 0, woodPlank = 0, lighter = 0, ladder = 0;
        // Healing item declaration
        int bandages = 0, medicine = 0, painkiller = 0; 
        // Story item declaration
        int battery = 0;
        // Exit command declaration
        char exitChoice;
        // Progress declaration, [0-19] main path, [20-39] item, [40-59]
        int playerProgress, pathProgress[60] = {0};

        // random initialization
        srand(time(NULL));

        // Password declaration
        char boatPass[] = "1990";

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
                // showInventory (axe, cloth, woodPlank, lighter, ladder, battery, boatPass);
                playerProgress = pathForestOne(playerChoice, choicePhase, exitChoice, pathProgress);
                if (playerProgress == 3) {
                    break;
                }
                system("cls");
                Sleep(2000);
                pathProgress[0] = 1; // Keep track of progress

                forestPlane: // Forest plane label
                // showInventory (axe, cloth, woodPlank, lighter, ladder, battery, boatPass);
                playerProgress = pathForestPlane(playerChoice, choicePhase, exitChoice, pathProgress);
                if (playerProgress == 4) {
                    break;
                }
                system("cls");
                Sleep(2000);
                pathProgress[1] = 1; // Keep track of progress

                if (playerProgress == 1) {
                    playerProgress = pathCrashedPlane(playerChoice, choicePhase, exitChoice, pathProgress, battery, axe, &cloth, &bandages, &medicine);
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
                // showInventory (axe, cloth, woodPlank, lighter, ladder, battery, boatPass);
                playerProgress = pathForestTwo(playerChoice, choicePhase, exitChoice, pathProgress);
                if (playerProgress == 4) {
                    break;
                }
                system("cls");
                Sleep(2000);
                pathProgress[3] = 2; // Keep track of progress

                if (playerProgress == 2) {
                    forestRiver: // River label
                    // showInventory (axe, cloth, woodPlank, lighter, ladder, battery, boatPass);
                    playerProgress = pathForestRiver(playerChoice, choicePhase, exitChoice, pathProgress);
                    if (playerProgress == 4) {
                        break;
                    }
                    system("cls");
                    Sleep(2000);
                    pathProgress[4] = 1; // Keep track of progress

                    if (playerProgress == 1) {
                        playerProgress = pathRiverBoat(playerChoice, choicePhase, exitChoice, pathProgress, &woodPlank, &lighter, boatPass);
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
                // showInventory (axe, cloth, woodPlank, lighter, ladder, battery, boatPass);
                playerProgress = pathForestBridge(playerChoice, choicePhase, exitChoice, pathProgress, woodPlank, ladder);
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
                // showInventory (axe, cloth, woodPlank, lighter, ladder, battery, boatPass);
                playerProgress = pathForestCabin(playerChoice, choicePhase, exitChoice, pathProgress);
                if (playerProgress == 4) {
                    break;
                }
                system("cls");
                Sleep(2000);
                pathProgress[8] = 1; // Keep track of progress

                if (playerProgress == 1) {
                    playerProgress = pathCabinInside(playerChoice, choicePhase, exitChoice, pathProgress, &axe, &painkiller, cloth, lighter);
                    if (playerProgress == 4) {
                        break;
                    }
                    system("cls");
                    Sleep(2000);
                    pathProgress[9] = 1; // Keep track of progress

                    if (playerProgress == 2) {
                        goto gameEnd;
                    } else if (playerProgress == 3) {
                        goto forestCabin; 
                    }
                } else if (playerProgress == 3) {
                    goto forestBridge;
                }

                playerProgress = pathForestThree();

                caveStart:
                playerProgress = pathForestCave();

                gameEnd:
                printf("To be continued.");
                Sleep(1000);
                printf(".");
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
int pathForestOne (int choice, int phase, char exit, int progress[]) {

    // Story
    // printf("%d\n", progress[0]);
    if (progress[0] == 0) {
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
int pathForestPlane (int choice, int phase, char exit, int progress[]) {

    // Story
    // printf("%d\n", progress[1]);
    if (progress[1] == 0) {
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
int pathCrashedPlane (int choice, int phase, char exit, int progress[], int battery, int axe, int *cloth, int *bandages, int *medicine) {

    // Story
    // printf("%d\n", progress[2]);
    if (progress[2] == 0) {
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
                    if (progress[20] == 0) {
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
                    if (progress[20] == 0) {
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
                progress[20] = 1;
                phase++;
                break;
            case 2:
                if (axe == 0) {
                    if (progress[21] == 0) {
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
                    if (*cloth == 0 || *bandages == 0 || *medicine == 0) { 
                        *cloth = 1;
                        *bandages = 1;
                        *medicine = 1;
                        if (progress[21] == 0) {
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
                progress[21] = 1;
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

// Second forest path 
int pathForestTwo (int choice, int phase, char exit, int progress[]) {

    // Story
    // printf("%d\n", progress[3]);
    if (progress[3] == 0) {
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
    } else if (progress[3] == 1) {
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

// Forest river
int pathForestRiver (int choice, int phase, char exit, int progress[]) {

    // Story
    // printf("%d\n", progress[4]);
    if (progress[4] == 0) {
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

int pathRiverBoat (int choice, int phase, char exit, int progress[], int *plank, int *lighter, char pass[]) {

    // Story
    // printf("%d\n", progress[5]);
    if (progress[5] == 0) {
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
            //switch case in the boat
            switch (choice) {
            case 1:
                if (*plank == 0) {
                    *plank = 1;
                    printf("There's a few plank inside the boat\n");
                    Sleep(3000);
                    printf("It might be heavy, but it's always better to be safe.\n");
                    Sleep(4000);
                    printf("You picked up a few planks from the pile.\n");
                    Sleep(3000);
                }
                else if (*plank == 1){ 
                    printf("Your back is aching.\n");
                    Sleep(2000);
                    printf("You already have enough.\n");
                    Sleep(3000);
                }
                phase++;
                break;
            case 2:
                char yourPass[4];
                if (progress[21] == 0) {
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
                if (*lighter == 0) {
                    if (strcmp(pass, yourPass) == 0) {
                        *lighter = 1;
                        if (progress[24] == 1 && progress[25] == 1) {
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
                progress[21] = 1;
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

// Forest bridge
int pathForestBridge (int choice, int phase, char exit, int progress[], int plank, int ladder) {

    // Story
    // printf("%d\n", progress[7]);
    if (progress[7] == 0) {
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
                    if (plank == 0) {
                        if (progress[23] == 0) {
                            printf("You try to cross the bridge.\n");
                            Sleep(3000);
                            printf("But as you get halfway across, ");
                            Sleep(3000);
                            printf("You realize that there's quite a huge gap in the mmiddle.\n");
                            Sleep(4000);
                            printf("You turn back, fully aware of you're weak physical state.\n");
                            Sleep(4000);
                            printf("Maybe there's something along your path that could help you get across safely?\n");
                            Sleep(5000);
                        } else {
                            printf("It's not safe to go across in this condition.\n");
                            Sleep(3000);
                        }
                        progress[23] = 1;
                    } else {
                        if (progress[23] == 0) {
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
                        } else {
                            printf("Using the wooden planks, you close the gap on the bridge.\n");
                            Sleep(4000);
                            printf("With the gap already taken care of, you get across safely to the other side.\n");
                            Sleep(5000);
                        }
                        return 1;
                    }   
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
        }
    } while (1);

    return 0;
}

// Forest cabin
int pathForestCabin (int choice, int phase, char exit, int progress[]) {

    // Story
    printf("%d\n", progress[8]);
    if (progress[26] == 0) {
        if (progress[8] == 0) {
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
            if (progress[9] == 0) {
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
int pathCabinInside (int choice, int phase, char exit, int progress[], int *axe, int *painkiller, int cloth, int lighter) {

    // Story
    printf("%d\n", progress[9]);
    if (progress[9] == 0) {
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
                            if (*axe == 0 || *painkiller == 0) {
                                *axe = 1;
                                *painkiller = 1;
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
                            if (progress[25] == 0) {
                                progress[25] = 1;
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
                            if (progress[24] == 0){
                                progress[24] = 1;
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
                    return 2;
                } else {
                    printf("You're body urges you to take a rest.\n");
                    Sleep(3000);
                    printf("But you feel like there are still stuff you need to take care of.\n");
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

int pathForestThree () {

    printf("Y u here?\n");

    return 0;
}

int pathForestCave () {

    printf("Y u here?\n");

    return 0;
}
