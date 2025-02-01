// Namespace : regroupe des identificateurs pour éviter d'avoir des conflits de nom (utilisation un peu à la manière d'une classe, cependant là où il faut instancier une classe pour utiliser une méthode, là on ne surcharge pas la mémoire avec des créations d'objets)
// C'est vraiment pour de l'organisation du code 

// setx PROJETGD "C:\chemin\vers\ton\projet"
// doskey PROJETGD=cd /d %PROJETGD%

/*
Pour commit sur github son dossier :

cd %PROJETGD%

git init
git remote add origin https://github.com/NABL-A/CHALLENGE.git



*/


#include <windows.h>
#include <iostream>
#include <thread> // Pour std::this_thread::sleep_for

void simulateKeyPress(WORD key) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD; // ça pourrait être un mouse input ou hardware input mi ou hi
    input.ki.wVk = key; // Code de la touche

    // Envoi de l'événement "touche enfoncée"
    SendInput(1, &input, sizeof(INPUT));

    // Attendre un peu pour simuler une pression réelle
    Sleep(50);

    // Envoi de l'événement "touche relâchée"
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

HWND trouverFenetre(const std::string& titre) {
    return FindWindowA(NULL, titre.c_str());
}

void activerFenetre(HWND hwnd) {
    if (hwnd) {
        SetForegroundWindow(hwnd); // Met la fenêtre en avant-plan
    }
}

void simulerTouche(WORD touche) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = touche;

    SendInput(1, &input, sizeof(INPUT)); // Touche enfoncée
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); // Pause
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT)); // Touche relâchée
}

int main() {
    HWND hwnd = FindWindowA(NULL, "Geometry Dash");

    if (hwnd == NULL) {
        std::cerr << "Fenêtre non trouvée !" << std::endl;
        return 1;
    }

    std::cout << "Fenêtre trouvée, activation..." << std::endl;
    activerFenetre(hwnd);
    
    std::cout << "Envoi de la touche ESPACE..." << std::endl;
    simulerTouche(VK_SPACE); // Envoie la touche ESPACE

    return 0;
}

