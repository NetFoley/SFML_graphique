#include <stdio.h>
#include <stdlib.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>

#define tTailleMAX 25
#define nLARGEUR 10
#define nLONGUEUR 25

void ajouterText(text1, text2, taille);
sfVector2f changeDir(sfVector2f direc, char sens);
sfVector2f rebond(sfVector2f direc, sfVector2f posBall, sfVector2f dimBall, sfVector2f posEnnemis, sfVector2f dimEnnemis);
sfVector2f rebondBarre(sfVector2f direc, sfVector2f posBall, sfVector2f posPong, sfVector2f dimPong);

int main()
{
    sfVideoMode mode = {1280, 720, 32};
    sfRenderWindow * renderwindow;
    renderwindow = sfRenderWindow_create(mode, "SFML works!", sfDefaultStyle ,NULL);

    //Define sprite and texture
    sfTexture * texture;
    sfSprite * sprite;

    sfIntRect rectTexture;

    rectTexture.height = 100;
    rectTexture.width = 58;
    rectTexture.top = 0;
    rectTexture.left = 0;

    sprite = sfSprite_create();

    if (texture = sfTexture_createFromFile("totue.png", &rectTexture));
    {
        printf("Succes du chargement de l'image\n");
    }

    //Define positions of text and ball
    sfVector2f posText;
    posText.x = 0.0;
    posText.y = 0.0;

    sfVector2f posZero;
    posZero.x = 0.0;
    posZero.y = 0.0;

    sfVector2f dimPong;
    dimPong.x = 242.705098305;
    dimPong.y = 15.0;

    sfVector2f dimLBorder;
    dimLBorder.x = 1;
    dimLBorder.y = sfRenderWindow_getSize(renderwindow).y;

    sfVector2f dimRBorder;
    dimRBorder.x = 1;
    dimRBorder.y = sfRenderWindow_getSize(renderwindow).y;

    sfVector2f dimHBorder;
    dimHBorder.x = sfRenderWindow_getSize(renderwindow).x;
    dimHBorder.y = 1;

    sfVector2f posBall;
    posBall.x = 400;
    posBall.y = 550;

    sfVector2f posMort;
    posMort.x = -100;
    posMort.y = 0;

    sfVector2f originePong;
    originePong.x = dimPong.x /2;
    originePong.y = dimPong.y /2;

    //Define speed and direction of ball
    float vBall = 0.5;

    sfVector2f dirBall;
    dirBall.x = 0.5;
    dirBall.y = -0.5;

    //Shape of pong
    sfRectangleShape * rectanglePong = sfRectangleShape_create();
    sfRectangleShape_setSize(rectanglePong, dimPong);
    sfRectangleShape_setOrigin(rectanglePong, originePong);
    sfRectangleShape_setFillColor(rectanglePong, sfColor_fromRGB(97.4012,157.5986,255));

    //Shape left border
    sfRectangleShape * bordureGauche = sfRectangleShape_create();
    sfRectangleShape_setSize(bordureGauche, dimLBorder);
    sfRectangleShape_setPosition(bordureGauche, posZero);

    //Shape Top border
    sfRectangleShape * bordureHaute = sfRectangleShape_create();
    sfRectangleShape_setSize(bordureHaute, dimHBorder);
    sfRectangleShape_setPosition(bordureHaute, posZero);

    //Shape Right border
    sfVector2f posRBorder;
    posRBorder.x = sfRenderWindow_getSize(renderwindow).x;
    posRBorder.y = 0;

    sfRectangleShape * bordureDroite= sfRectangleShape_create();
    sfRectangleShape_setSize(bordureDroite, dimRBorder);
    sfRectangleShape_setPosition(bordureDroite, posRBorder);

    //Shape of ball
    sfVector2f dimBall;
    dimBall.y = 20*2;
    dimBall.x = 20*2;
    sfCircleShape * balle = sfCircleShape_create();
    sfCircleShape_setRadius(balle,20.f);
    sfCircleShape_setPosition(balle,posBall);



    //Les briques à casser
    sfVector2f dimEnnemis;
    dimEnnemis.x = 64.4;
    dimEnnemis.y = 20;

    int ecart = 15;

    sfVector2f posEnnemis[nLARGEUR][nLONGUEUR];

    sfRectangleShape * ennemisPong[nLARGEUR][nLONGUEUR];

    ennemisPong[0][0] = sfRectangleShape_create();
    sfRectangleShape_setSize(ennemisPong[0][0], dimEnnemis);
    sfRectangleShape_setFillColor(ennemisPong[0][0], sfColor_fromRGB(255,255,255));

    //Define brics positions
    for (int i = 0; i < nLARGEUR ; i++)
    {
        for (int j = 0 ; j < nLONGUEUR; j++)
        {
            ennemisPong[i][j] = sfRectangleShape_copy(ennemisPong[0][0]);
            posEnnemis[i][j].x = ecart + (dimEnnemis.x  + ecart) * j;
            posEnnemis[i][j].y = ecart + (dimEnnemis.y  + ecart) * i;
            sfRectangleShape_setPosition(ennemisPong[i][j],posEnnemis[i][j]);
        }
    }

    sfSprite_setTexture(sprite, texture, 0);
    sfVector2f origine;
    origine.x = (sfSprite_getTextureRect(sprite).width)/2;
    origine.y = (sfSprite_getTextureRect(sprite).height)/2;
    sfSprite_setOrigin(sprite, origine);
    // run the program as long as the window is open

    //Define Text
    float vText = 10;
    sfText * text;
    sfFont * font;

    text = sfText_create();

            if (!(font = sfFont_createFromFile("Myndraine-webfont.ttf")))
            {
                // error...
                printf("Echec chargement police");
            }

    char textDraw[tTailleMAX] = "Futur Pong";


    while (sfRenderWindow_isOpen(renderwindow))
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sfEvent event;
        _Bool keyQ, keyS, keyZ, keyD ;

        //Collision boxes
        sfFloatRect collision_balle = sfCircleShape_getGlobalBounds(balle);
        sfFloatRect collision_pong = sfRectangleShape_getGlobalBounds(rectanglePong);
        sfFloatRect collision_LBorder = sfRectangleShape_getGlobalBounds(bordureGauche);
        sfFloatRect collision_RBorder = sfRectangleShape_getGlobalBounds(bordureDroite);
        sfFloatRect collision_HBorder = sfRectangleShape_getGlobalBounds(bordureHaute);
        sfFloatRect collision_briques[nLARGEUR][nLONGUEUR];

        for (int i = 0; i < nLARGEUR ; i++)
        {
            for (int j =0 ; j < nLONGUEUR; j++)
            {
                collision_briques[i][j] = sfRectangleShape_getGlobalBounds(ennemisPong[i][j]);
            }
        }


        //Refresh positions
        sfVector2f posTotue;
        posTotue.x = sfMouse_getPosition(renderwindow).x;
        posTotue.y = sfMouse_getPosition(renderwindow).y;

        sfVector2f posPong;
        posPong.x = sfMouse_getPosition(renderwindow).x;
        posPong.y = sfRenderWindow_getSize(renderwindow).y - 75;

        sfSprite_setPosition(sprite, posTotue);

        posBall.x = posBall.x + dirBall.x * vBall;
        posBall.y = posBall.y + dirBall.y * vBall;

        sfCircleShape_setPosition(balle,posBall);
        // clear the window with black color
        sfRenderWindow_clear(renderwindow, sfBlack);

        // set the text

        sfText_setString(text,textDraw);
        sfText_setColor(text, sfWhite);
        sfText_setFont(text, font);

        // set pong rectangle
        sfRectangleShape_setPosition(rectanglePong, posPong);

        sfText_move(text, posText);
        posText.y = 0;
        posText.x = 0;

        sfRenderWindow_drawText(renderwindow,text,NULL);
        sfRenderWindow_drawSprite(renderwindow,sprite,NULL);
        sfRenderWindow_drawRectangleShape(renderwindow,rectanglePong,NULL);
        sfRenderWindow_drawCircleShape(renderwindow,balle,NULL);

        if (sfFloatRect_intersects(&collision_balle, &collision_pong, NULL))
        {
            dirBall =  rebondBarre(dirBall, posBall, posPong, dimPong);
            printf("collision bas\n");
        }

        if (sfFloatRect_intersects(&collision_RBorder, &collision_balle, NULL))
        {
            dirBall =  changeDir(dirBall,'g');
            printf("collision droite\n");
        }

        if (sfFloatRect_intersects(&collision_LBorder, &collision_balle, NULL))
        {
            dirBall =  changeDir(dirBall,'d');
            printf("collision gauche\n");
        }

        if (sfFloatRect_intersects(&collision_HBorder, &collision_balle, NULL))
        {
            dirBall =  changeDir(dirBall,'b');
            printf("collision haut\n");
        }

        for (int i = 0; i < nLARGEUR ; i++)
        {
            for (int j = 0 ; j < nLONGUEUR; j++)
            {
                sfRenderWindow_drawRectangleShape(renderwindow,ennemisPong[i][j],NULL);
                if (sfFloatRect_intersects(&collision_balle, &collision_briques[i][j], NULL))
                {
                    dirBall = rebond(dirBall, posBall, dimBall, posEnnemis[i][j], dimEnnemis);
                    sfRectangleShape_setPosition(ennemisPong[i][j], posMort);
                    printf("destruction %i %i \n", i , j);
                }
            }
        }

        // end the current frame
        sfRenderWindow_display(renderwindow);


        // check all the window's events that were triggered since the last iteration of the loop
        while (sfRenderWindow_pollEvent(renderwindow, &event))
        {

            // "close requested" event: we close the window
            if (event.type == sfEvtClosed)
            {
                sfRenderWindow_close(renderwindow);
            }
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

        }
    }

    return 0;
}

sfVector2f changeDir(sfVector2f direc, char sens) {
    switch (sens){
        case 'h' :
        direc.y = -fabs(direc.y);
        printf("rebond haut\n");
        return direc;

        case 'b' :
        direc.y = fabs(direc.y);
        printf("rebond bas\n");
        return direc;

        case 'g' :
        direc.x = -fabs(direc.x);
        printf("rebond gauche\n");
        return direc;

        case 'd' :
        direc.x = fabs(direc.x);
        printf("rebond droite\n");
        return direc;
    }
}

sfVector2f rebond(sfVector2f direc, sfVector2f posBall, sfVector2f dimBall, sfVector2f posEnnemis, sfVector2f dimEnnnemis ) {
    if (posEnnemis.y < posBall.y)
    {
        direc.y = fabs(direc.y);
    }
    else
    {
        direc.y = -fabs(direc.y);
    }

    if((posBall.y + dimBall.y - 10 > posEnnemis.y) && (posBall.y +10< posBall.y + dimEnnnemis.y))
    {
        if(posBall.x < posEnnemis.x)
        {
            direc.x = -fabs(direc.x);
        }
        else
        {
            direc.x = fabs(direc.x);
        }
    }

    return direc;
}

sfVector2f rebondBarre(sfVector2f direc, sfVector2f posBall, sfVector2f posPong, sfVector2f dimPong) {
        direc.x = ((posBall.x - posPong.x)/(dimPong.x/2)) +0.15;
        direc.y = -(fabs(1 - fabs(direc.x)));
        printf("rebond haut sur barre direc.x = %f direc.y = %f\n", direc.x, direc.y);
        return direc;
}

void ajouterText(text1, text2, taille)
{
    if (strlen(text1) + strlen(text2) < taille)
        strcat(text1, text2);
    else
    {
        printf("Texte trop grand annulé l'ajout %s a %c \n", text2, text1);
    }
}
