#include <stdio.h>
#include <stdlib.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>

#define tTailleMAX 25

int main()
{

    sfVideoMode mode = {1280, 720, 32};
    sfRenderWindow * renderwindow;
    renderwindow = sfRenderWindow_create(mode, "SFML works!", sfDefaultStyle ,NULL);

    sfTexture * texture;

    sfIntRect rectTexture;

    sfSprite * sprite;

    rectTexture.height = 100;
    rectTexture.width = 58;
    rectTexture.top = 0;
    rectTexture.left = 0;

    sprite = sfSprite_create();


    if (texture = sfTexture_createFromFile("totue.png", &rectTexture));
    {
        printf("SHIT");
    }

    sfSprite_setTexture(sprite, texture, 0);
    printf("SHIT");

    // run the program as long as the window is open

    sfVector2f posText;
    posText.x = 0.0;
    posText.y = 0.0;

    float vText = 10;

    sfText * text;
    sfFont * font;

    text = sfText_create();

            if (!(font = sfFont_createFromFile("Myndraine-webfont.ttf")))
            {
                // error...
                printf("Echec chargement police");
            }

    char textDraw[tTailleMAX] = "Hello world";


    while (sfRenderWindow_isOpen(renderwindow))
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sfEvent event;
        _Bool keyQ, keyS, keyZ, keyD ;

        sfVector2f posTotue;
        posTotue.x = sfMouse_getPosition(renderwindow).x;
        posTotue.y = sfMouse_getPosition(renderwindow).y;

        sfSprite_setPosition(sprite, posTotue);

        if (sfKeyboard_isKeyPressed(sfKeyQ) && keyQ == 0)
        {
            posText.x = - vText;
            printf("Q ");

            ajouterText(textDraw, "Q", tTailleMAX);
            keyQ = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyQ)== 0 && keyQ == 1)
        {
            keyQ = 0;
        }
        if (sfKeyboard_isKeyPressed(sfKeyS) && keyS == 0)
        {
            posText.y = + vText;
            printf("S ");

            ajouterText(textDraw, "S", tTailleMAX);
            keyS = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyS)== 0 && keyS == 1)
        {
            keyS = 0;
        }
        if (sfKeyboard_isKeyPressed(sfKeyD) && keyD == 0)
        {
            posText.x = + vText;
            printf("D ");

            ajouterText(textDraw, "D", tTailleMAX);
            keyD = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyD)== 0 && keyD == 1)
        {
            keyD = 0;
        }
        if (sfKeyboard_isKeyPressed(sfKeyZ) && keyZ == 0)
        {
            posText.y = - vText;
            printf("Z ");

            ajouterText(textDraw, "Z", tTailleMAX);
            keyZ = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyZ)== 0 && keyZ == 1)
        {
            keyZ = 0;
        }
        if (sfKeyboard_isKeyPressed(sfKeyEscape))
        {
            printf("Fin du programme");
            sfRenderWindow_close(renderwindow);
        }

        // check all the window's events that were triggered since the last iteration of the loop
        while (sfRenderWindow_pollEvent(renderwindow, &event))
        {

            // "close requested" event: we close the window
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(renderwindow);
            }

            // clear the window with black color
            sfRenderWindow_clear(renderwindow, sfBlack);

            // set the text

            sfText_setString(text,textDraw);
            sfText_setColor(text, sfWhite);
            sfText_setFont(text, font);

            sfText_move(text, posText);
            posText.y = 0;
            posText.x = 0;

            sfRenderWindow_drawText(renderwindow,text,NULL);
            sfRenderWindow_drawSprite(renderwindow,sprite,NULL);
            // end the current frame
            sfRenderWindow_display(renderwindow);
        }
    }

    return 0;
}

void ajouterText(text1, text2, taille)
{
    if (strlen(text1) + strlen(text2) < taille)
        strcat(text1, text2);
    else
    {
        printf("Texte trop grand annulé l'ajout %s a %s \n", text2, text1);
    }
}
