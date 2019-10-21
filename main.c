#include <stdio.h>
#include <stdlib.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>

int main()
{

    sfVideoMode mode = {400, 400, 32};
    sfRenderWindow * renderwindow;
    renderwindow = sfRenderWindow_create(mode, "SFML works!", sfDefaultStyle ,NULL);

    // run the program as long as the window is open

    sfVector2f deplacement;
    deplacement.x = 0.0;
    deplacement.y = 0.0;

    while (sfRenderWindow_isOpen(renderwindow))
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sfEvent event;
        _Bool keyQ, keyS, keyZ, keyD ;

        if (sfKeyboard_isKeyPressed(sfKeyQ) && keyQ == 0)
        {
            deplacement.x = deplacement.x - 5.0;
            printf("Q ");
            keyQ = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyQ)== 0 && keyQ == 1)
        {
            keyQ = 0;
        }
        if (sfKeyboard_isKeyPressed(sfKeyS) && keyS == 0)
        {
            deplacement.y = deplacement.y + 5.0;
            printf("S ");
            keyS = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyS)== 0 && keyS == 1)
        {
            keyS = 0;
        }
        if (sfKeyboard_isKeyPressed(sfKeyD) && keyD == 0)
        {
            deplacement.x = deplacement.x + 5.0;
            printf("D ");
            keyD = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyD)== 0 && keyD == 1)
        {
            keyD = 0;
        }
        if (sfKeyboard_isKeyPressed(sfKeyZ) && keyZ == 0)
        {
            deplacement.y = deplacement.y - 5.0;
            printf("Z ");
            keyZ = 1;
        }
        if (sfKeyboard_isKeyPressed(sfKeyZ)== 0 && keyZ == 1)
        {
            keyZ = 0;
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

            sfText * text;
            sfFont * font;

            text = sfText_create();
            if (!(font = sfFont_createFromFile("Myndraine-webfont.ttf")))
            {
                // error...
                printf("Echec chargement police");
            }

            // set the text
            sfText_setString(text,"Hello WORLD");
            sfText_setColor(text, sfWhite);
            sfText_setFont(text, font);

            sfText_move(text, deplacement);



            sfRenderWindow_drawText(renderwindow,text,NULL);
            // end the current frame
            sfRenderWindow_display(renderwindow);
        }
    }

    return 0;
}
