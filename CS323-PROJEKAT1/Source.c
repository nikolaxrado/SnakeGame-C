
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>



#define red 20 // broj redova
#define kol 40 // broj kolona za polje

int i, j, Zmijica[red][kol];
int x, y, glava, rep, Gy;
int igra;
int jabuka; // zmijja to jede
int a, b;
int varijabla;
int direkcija;
int poeni;
int HighScore;

FILE* f;

struct igrac {

    char name[30];
};

void struktura()
{
    struct igrac* ptr;
    int i, n;

    printf("Unesite broj igraca: ");
    scanf("%d", &n);

    // alociranje memorije za n broj igraca
    ptr = (struct igrac*)malloc(n * sizeof(struct igrac));

    for (i = 0; i < n; ++i)
    {
        printf("Unesite ime/na: ");

        //uzimanje podataka preko -> name
        scanf("%s %d", (ptr + i)->name);
        printf("Name: %s\t", (ptr + i)->name);
    }
}


//zmija pravljenje za pocetak igre
void zmija() {
    f = fopen("highscore.txt", "r");
    fscanf(f, "%d", &HighScore);
    fclose(f);



    for (i = 0; i < red; i++) {
        for (j = 0; j < kol; j++) {
            Zmijica[i][j] = 0;
        }
    }

    //namestanje zmijice i jabuke u polju
    x = red / 2;
    y = kol / 2;
    glava = 5;
    rep = 1;
    Gy = y;
    igra = 0;
    jabuka = 0;
    direkcija = 'd';
    poeni = 0;

    for (i = 0; i < glava; i++) {
        Gy++;
        Zmijica[x][Gy - glava] = i + 1;
    }
}


void jabukaIgra() {
    //random pojavljivajne na ekranu
    srand(time(0));
    a = 1 + rand() % 18;
    b = 1 + rand() % 38;

    if (jabuka == 0 && Zmijica[a][b] == 0) {
        Zmijica[a][b] = -1;
        jabuka = 1;
    }
}

void repBrisanje() {

    for (i = 0; i < red; i++) {
        for (j = 0; j < kol; j++) {
            if (Zmijica[i][j] == rep) {
                Zmijica[i][j] = 0;
            }
        }
    }
    rep++;
}

int dobijPomeraj() {

    if (_kbhit()) {
        return _getch();
    }
    else {
        return -1;
    }
}

void pomeranjZmije() {

    varijabla = dobijPomeraj();
    varijabla = tolower(varijabla);

    if ((varijabla == 'd' || varijabla == 'a') || (varijabla == 's' || varijabla == 'w') && (abs(direkcija - varijabla) > 5)) {
        direkcija = varijabla;
    }

    if (direkcija == 'd') {
        y++;

        if (Zmijica[x][y] != 0 && Zmijica[x][y] != -1) {

            krajIgre();
        }
        if (y == kol - 1) {
            y = 0;
        }
        if (Zmijica[x][y] == -1) {
            jabuka = 0;
            rep = rep - 2;
            poeni += 5;

        }
        glava++;
        Zmijica[x][y] = glava;

    }
    if (direkcija == 'a') {
        y--;
        if (Zmijica[x][y] != 0 && Zmijica[x][y] != -1) {

            krajIgre();
        }
        if (y == kol - 1) { // da se zmija vraæa u isti red kao iz kog je posla
            y = 0;
        }
        if (Zmijica[x][y] == -1) {
            jabuka = 0;
            rep = rep - 2;
            poeni += 5;
        }
        glava++;
        Zmijica[x][y] = glava;

    }
    if (direkcija == 'w') {
        x--;
        if (Zmijica[x][y] != 0 && Zmijica[x][y] != -1) {

            krajIgre();
        }
        if (x == -1) {
            x = red - 1;
        }
        if (Zmijica[x][y] == -1) {
            jabuka = 0;
            rep = rep - 2;
            poeni += 5;
        }
        glava++;
        Zmijica[x][y] = glava;

    }
    if (direkcija == 's') {
        x++;
        if (Zmijica[x][y] != 0 && Zmijica[x][y] != -1) {

            krajIgre();
        }
        if (x == red - 1) {
            x = 0;
        }
        if (Zmijica[x][y] == -1) {
            jabuka = 0;
            rep = rep - 2;
            poeni += 5;
        }
        glava++;
        Zmijica[x][y] = glava;
    }
}
int krajIgre() {

    printf("\a");
    Sleep(1000);
    system("Cls"); // kraj igre, brisanje celog polja

    if (poeni > HighScore) {
        printf("  New HighScore %d!!!!!!\n\n", poeni);
        system("pause");
        f = fopen("highscore.txt", "w");
        fprintf(f, "Poeni %d\n", poeni);
        fclose(f);
    }

    system("Cls");
    printf("\n\n         GAME OVER !!!!!!\n");
    printf("             Score : %d \n\n", poeni);

    igra = 1;
    return igra;
}



void  resetuj() {
    HANDLE out;
    COORD pozicija;
    out = GetStdHandle(STD_OUTPUT_HANDLE);
    pozicija.X = 0;
    pozicija.Y = 0;
    SetConsoleCursorPosition(out, pozicija);
}

void polje() {

    //pravljenje polja za igru ascii oblici za pravljenje 
    // petlja za pravljenje bloka 

    for (i = 0; i <= kol + 1; i++) {
        if (i == 0) {
            printf("%c", 201);
        }
        else if (i == kol + 1) {
            printf("%c", 187);
        }
        else {
            printf("%c", 205);
        }
    }
    printf("   Current Score: %d  HighScore: %d", poeni, HighScore);
    printf("\n");

    for (i = 0; i < red; i++) {
        printf("%c", 186);
        for (j = 0; j < kol; j++) { //prikazivanje zmijice u polju
            if (Zmijica[i][j] == 0) {
                printf(" ");
            } if (Zmijica[i][j] > 0 && Zmijica[i][j] != glava) {
                printf("%c", 176);

            }if (Zmijica[i][j] == glava) {
                printf("%c", 178);
            }
            if (Zmijica[i][j] == -1) { //prikaz jabuke
                printf("%c", 224);
            }
            if (j == kol - 1) {
                printf("%c\n", 186);
            }
        }
    }
    for (i = 0; i <= kol + 1; i++) {
        if (i == 0) {
            printf("%c", 200);
        }
        else if (i == kol + 1) {
            printf("%c", 188);
        }
        else {
            printf("%c", 205);
        }
    }
}

void main() {
    char str[] = "Igrica zmijica\n";

    // print string
    printf("%s", str);
    struktura();
    zmija();

    while (igra == 0) {

        polje();
        resetuj();
        jabukaIgra();
        repBrisanje();
        pomeranjZmije();
        Sleep(99);
    }



}
