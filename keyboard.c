#include "keyboard.h"
#include "RA8875.h"

#include "main.h"

unsigned int kb_back = 0xffff;
unsigned int kb_edge = 0x0000;
unsigned int kb_color = 0x0000;

unsigned int kb_width = 0;
unsigned int kb_height = 0;
unsigned int key_width = 0;
unsigned int key_height = 0;
unsigned int space_width = 0;
unsigned int key_top = 0;
unsigned int key_left = 0;

char isKey(Keyboard kb, unsigned int i_left, unsigned int i_top)
{
    unsigned int keycount = 128;
    unsigned int x;

    char isInX = 0;
    char isInY = 0;
    char KeyFound = 0;

    char keya;

    for(x=0;x<keycount;x++)
    {
        if(i_left >= kb.keys[x].left)
        {
            if(i_left <= (kb.keys[x].left+kb.keys[x].width))
            {
                isInY = 1;
            }
        }

        if(i_top >= kb.keys[x].top)
        {
            if(i_top <= (kb.keys[x].top+kb.keys[x].height))
            {
                isInX = 1;
            }
        }

        if((isInX + isInY) > 1)
            KeyFound = 1;

        isInX = isInY = 0;
        if(KeyFound > 0)
        {
            keya = (char)kb.keys[x].ascii;
            return keya;
        }
    }

    return 0;
}

Keyboard draw_kb(char isShift, unsigned int left, unsigned int top, unsigned int width, unsigned int ecolor, unsigned int bcolor, unsigned int tcolor)
{
    Keyboard tempKB2;

    if(isShift > 0)
    {
         tempKB2 = draw_shift(left,top,width,ecolor,bcolor,tcolor);
    }
    else
    {
        tempKB2 = draw_no_shift(left,top,width,ecolor,bcolor,tcolor);
    }

    tempKB2.shift = 0;
    tempKB2.caps = 0;
    tempKB2.left = left;
    tempKB2.top = top;
    
    if(isShift == SHIFT)
        tempKB2.shift = 1;
    if(isShift == CAPS)
        tempKB2.caps = 1;

    
    return tempKB2;
}

Keyboard draw_no_shift(unsigned int left, unsigned int top, unsigned int width, unsigned int ecolor, unsigned int bcolor, unsigned int tcolor)
{
    Keyboard tempKB;
    unsigned int next_y = left;
    int x;
    key_top = top;
    key_left = left;

    //LCD_Reset();
    tempKB.back_color = bcolor;
    tempKB.edge_color = ecolor;
    tempKB.text_color = tcolor;

    kb_back = bcolor;
    kb_edge = ecolor;
    kb_color = tcolor;

    tempKB.width = width;
    tempKB.key_width = width/15;
    tempKB.key_height = tempKB.key_width;
    tempKB.height = tempKB.key_height * 5;
    tempKB.left = left;
    tempKB.top = top;

    kb_width = width;
    key_width = kb_width / 15;
    key_height = key_width;
    kb_height = key_height * 5;

    for (x=0;x<128;x++)
    {
        tempKB.keys[x].width = key_width;
        tempKB.keys[x].height = key_height;
    }

    tempKB.keys[0].top = top;
    tempKB.keys[0].left = next_y;
    tempKB.keys[0].ascii = 0x60;
    next_y = draw_keys(tempKB.keys[0].left, tempKB.keys[0].top, 1, (char*)"`\0");

    tempKB.keys[1].top = top;
    tempKB.keys[1].left = next_y;
    tempKB.keys[1].ascii = 0x31;
    next_y = draw_keys(tempKB.keys[1].left, tempKB.keys[1].top, 1, (char*)"1\0");

    tempKB.keys[2].top = top;
    tempKB.keys[2].left = next_y;
    tempKB.keys[2].ascii = 0x32;
    next_y = draw_keys(tempKB.keys[2].left, tempKB.keys[2].top, 1, (char*)"2\0");

    tempKB.keys[3].top = top;
    tempKB.keys[3].left = next_y;
    tempKB.keys[3].ascii = 0x33;
    next_y = draw_keys(tempKB.keys[3].left, tempKB.keys[3].top, 1, (char*)"3\0");

    tempKB.keys[4].top = top;
    tempKB.keys[4].left = next_y;
    tempKB.keys[4].ascii = 0x34;
    next_y = draw_keys(tempKB.keys[4].left, tempKB.keys[4].top, 1, (char*)"4\0");

    tempKB.keys[5].top = top;
    tempKB.keys[5].left = next_y;
    tempKB.keys[5].ascii = 0x35;
    next_y = draw_keys(tempKB.keys[5].left, tempKB.keys[5].top, 1, (char*)"5\0");

    tempKB.keys[6].top = top;
    tempKB.keys[6].left = next_y;
    tempKB.keys[6].ascii = 0x36;
    next_y = draw_keys(tempKB.keys[6].left, tempKB.keys[6].top, 1, (char*)"6\0");

    tempKB.keys[7].top = top;
    tempKB.keys[7].left = next_y;
    tempKB.keys[7].ascii = 0x37;
    next_y = draw_keys(tempKB.keys[7].left, tempKB.keys[7].top, 1, (char*)"7\0");

    tempKB.keys[8].top = top;
    tempKB.keys[8].left = next_y;
    tempKB.keys[8].ascii = 0x38;
    next_y = draw_keys(tempKB.keys[8].left, tempKB.keys[8].top, 1, (char*)"8\0");

    tempKB.keys[9].top = top;
    tempKB.keys[9].left = next_y;
    tempKB.keys[9].ascii = 0x39;
    next_y = draw_keys(tempKB.keys[9].left, tempKB.keys[9].top, 1, (char*)"9\0");

    tempKB.keys[10].top = top;
    tempKB.keys[10].left = next_y;
    tempKB.keys[10].ascii = 0x30;
    next_y = draw_keys(tempKB.keys[10].left, tempKB.keys[10].top, 1, (char*)"0\0");

    tempKB.keys[11].top = top;
    tempKB.keys[11].left = next_y;
    tempKB.keys[11].ascii = 0x2d;
    next_y = draw_keys(tempKB.keys[11].left, tempKB.keys[11].top, 1, (char*)"-\0");

    tempKB.keys[12].top = top;
    tempKB.keys[12].left = next_y;
    tempKB.keys[12].ascii = 0x3d;
    next_y = draw_keys(tempKB.keys[12].left, tempKB.keys[12].top, 1, (char*)"=\0");

    tempKB.keys[13].top = top;
    tempKB.keys[13].width = key_width * 2;
    tempKB.keys[13].left = next_y;
    tempKB.keys[13].ascii = 0x08;
    next_y = draw_keys(tempKB.keys[13].left, tempKB.keys[13].top, 2, (char*)"BKSP\0");

    next_y = left;
    top += key_height;
    tempKB.keys[14].top = top;
    tempKB.keys[14].left = next_y;
    tempKB.keys[14].ascii = 0x09;
    tempKB.keys[14].width = key_width * 2;
    next_y = draw_keys(tempKB.keys[14].left, tempKB.keys[14].top, 2, (char*)"TAB\0");

    tempKB.keys[15].top = top;
    tempKB.keys[15].left = next_y;
    tempKB.keys[15].ascii = 0x71;
    next_y = draw_keys(tempKB.keys[15].left, tempKB.keys[15].top, 1, (char*)"q\0");

    tempKB.keys[16].top = top;
    tempKB.keys[16].left = next_y;
    tempKB.keys[16].ascii = 0x77;
    next_y = draw_keys(tempKB.keys[16].left, tempKB.keys[16].top, 1, (char*)"w\0");

    tempKB.keys[17].top = top;
    tempKB.keys[17].left = next_y;
    tempKB.keys[17].ascii = 0x65;
    next_y = draw_keys(tempKB.keys[17].left, tempKB.keys[17].top, 1, (char*)"e\0");

    tempKB.keys[18].top = top;
    tempKB.keys[18].left = next_y;
    tempKB.keys[18].ascii = 0x72;
    next_y = draw_keys(tempKB.keys[18].left, tempKB.keys[18].top, 1, (char*)"r\0");

    tempKB.keys[19].top = top;
    tempKB.keys[19].left = next_y;
    tempKB.keys[19].ascii = 0x74;
    next_y = draw_keys(tempKB.keys[19].left, tempKB.keys[19].top, 1, (char*)"t\0");

    tempKB.keys[20].top = top;
    tempKB.keys[20].left = next_y;
    tempKB.keys[20].ascii = 0x79;
    next_y = draw_keys(tempKB.keys[20].left, tempKB.keys[20].top, 1, (char*)"y\0");

    tempKB.keys[21].top = top;
    tempKB.keys[21].left = next_y;
    tempKB.keys[21].ascii = 0x75;
    next_y = draw_keys(tempKB.keys[21].left, tempKB.keys[21].top, 1, (char*)"u\0");

    tempKB.keys[22].top = top;
    tempKB.keys[22].left = next_y;
    tempKB.keys[22].ascii = 0x69;
    next_y = draw_keys(tempKB.keys[22].left, tempKB.keys[22].top, 1, (char*)"i\0");

    tempKB.keys[23].top = top;
    tempKB.keys[23].left = next_y;
    tempKB.keys[23].ascii = 0x6f;
    next_y = draw_keys(tempKB.keys[23].left, tempKB.keys[23].top, 1, (char*)"o\0");

    tempKB.keys[24].top = top;
    tempKB.keys[24].left = next_y;
    tempKB.keys[24].ascii = 0x70;
    next_y = draw_keys(tempKB.keys[24].left, tempKB.keys[24].top, 1, (char*)"p\0");

    tempKB.keys[25].top = top;
    tempKB.keys[25].left = next_y;
    tempKB.keys[25].ascii = 0x5b;
    next_y = draw_keys(tempKB.keys[25].left, tempKB.keys[25].top, 1, (char*)"[\0");

    tempKB.keys[26].top = top;
    tempKB.keys[26].left = next_y;
    tempKB.keys[26].ascii = 0x5d;
    next_y = draw_keys(tempKB.keys[26].left, tempKB.keys[26].top, 1, (char*)"]\0");

    tempKB.keys[27].top = top;
    tempKB.keys[27].left = next_y;
    tempKB.keys[27].ascii = 0x5c;
    next_y = draw_keys(tempKB.keys[27].left, tempKB.keys[27].top, 1, (char*)"\\\0");

    next_y = left;
    top += key_height;
    tempKB.keys[28].top = top;
    tempKB.keys[28].left = next_y;
    tempKB.keys[28].width = key_width * 2;
    tempKB.keys[28].ascii = 0x1c;
    next_y = draw_keys(tempKB.keys[28].left, tempKB.keys[28].top, 2, (char*)"CAPS\0");

    tempKB.keys[29].top = top;
    tempKB.keys[29].left = next_y;
    tempKB.keys[29].ascii = 0x61;
    next_y = draw_keys(tempKB.keys[29].left, tempKB.keys[29].top, 1, (char*)"a\0");

    tempKB.keys[30].top = top;
    tempKB.keys[30].left = next_y;
    tempKB.keys[30].ascii = 0x73;
    next_y = draw_keys(tempKB.keys[30].left, tempKB.keys[30].top, 1, (char*)"s\0");

    tempKB.keys[31].top = top;
    tempKB.keys[31].left = next_y;
    tempKB.keys[31].ascii = 0x64;
    next_y = draw_keys(tempKB.keys[31].left, tempKB.keys[31].top, 1, (char*)"d\0");

    tempKB.keys[32].top = top;
    tempKB.keys[32].left = next_y;
    tempKB.keys[32].ascii = 0x66;
    next_y = draw_keys(tempKB.keys[32].left, tempKB.keys[32].top, 1, (char*)"f\0");

    tempKB.keys[33].top = top;
    tempKB.keys[33].left = next_y;
    tempKB.keys[33].ascii = 0x67;
    next_y = draw_keys(tempKB.keys[33].left, tempKB.keys[33].top, 1, (char*)"g\0");

    tempKB.keys[34].top = top;
    tempKB.keys[34].left = next_y;
    tempKB.keys[34].ascii = 0x68;
    next_y = draw_keys(tempKB.keys[34].left, tempKB.keys[34].top, 1, (char*)"h\0");

    tempKB.keys[35].top = top;
    tempKB.keys[35].left = next_y;
    tempKB.keys[35].ascii = 0x6a;
    next_y = draw_keys(tempKB.keys[35].left, tempKB.keys[35].top, 1, (char*)"j\0");

    tempKB.keys[36].top = top;
    tempKB.keys[36].left = next_y;
    tempKB.keys[36].ascii = 0x6b;
    next_y = draw_keys(tempKB.keys[36].left, tempKB.keys[36].top, 1, (char*)"k\0");

    tempKB.keys[37].top = top;
    tempKB.keys[37].left = next_y;
    tempKB.keys[37].ascii = 0x6c;
    next_y = draw_keys(tempKB.keys[37].left, tempKB.keys[37].top, 1, (char*)"l\0");

    tempKB.keys[38].top = top;
    tempKB.keys[38].left = next_y;
    tempKB.keys[38].ascii = 0x3b;
    next_y = draw_keys(tempKB.keys[38].left, tempKB.keys[38].top, 1, (char*)";\0");

    tempKB.keys[39].top = top;
    tempKB.keys[39].left = next_y;
    tempKB.keys[39].ascii = 0x27;
    next_y = draw_keys(tempKB.keys[39].left, tempKB.keys[39].top, 1, (char*)"'\0");

    tempKB.keys[40].top = top;
    tempKB.keys[40].left = next_y;
    tempKB.keys[40].ascii = 0x0d;
    tempKB.keys[40].width = key_width * 2;
    next_y = draw_keys(tempKB.keys[40].left, tempKB.keys[40].top, 2, (char*)"ENTER\0");

    next_y = left+(tempKB.key_width/2);
    top += key_height;
    tempKB.keys[41].top = top;
    tempKB.keys[41].left = next_y;
    tempKB.keys[41].ascii = 0x1D;
    tempKB.keys[41].width = key_width * 2;
    next_y = draw_keys(tempKB.keys[41].left, tempKB.keys[41].top, 2, (char*)"SHIFT\0");

    tempKB.keys[42].top = top;
    tempKB.keys[42].left = next_y;
    tempKB.keys[42].ascii = 0x7a;
    next_y = draw_keys(tempKB.keys[42].left, tempKB.keys[42].top, 1, (char*)"z\0");

    tempKB.keys[43].top = top;
    tempKB.keys[43].left = next_y;
    tempKB.keys[43].ascii = 0x78;
    next_y = draw_keys(tempKB.keys[43].left, tempKB.keys[43].top, 1, (char*)"x\0");

    tempKB.keys[44].top = top;
    tempKB.keys[44].left = next_y;
    tempKB.keys[44].ascii = 0x63;
    next_y = draw_keys(tempKB.keys[44].left, tempKB.keys[44].top, 1, (char*)"c\0");

    tempKB.keys[45].top = top;
    tempKB.keys[45].left = next_y;
    tempKB.keys[45].ascii = 0x76;
    next_y = draw_keys(tempKB.keys[45].left, tempKB.keys[45].top, 1, (char*)"v\0");

    tempKB.keys[46].top = top;
    tempKB.keys[46].left = next_y;
    tempKB.keys[46].ascii = 0x62;
    next_y = draw_keys(tempKB.keys[46].left, tempKB.keys[46].top, 1, (char*)"b\0");

    tempKB.keys[47].top = top;
    tempKB.keys[47].left = next_y;
    tempKB.keys[47].ascii = 0x6e;
    next_y = draw_keys(tempKB.keys[47].left, tempKB.keys[47].top, 1, (char*)"n\0");

    tempKB.keys[48].top = top;
    tempKB.keys[48].left = next_y;
    tempKB.keys[48].ascii = 0x6d;
    next_y = draw_keys(tempKB.keys[48].left, tempKB.keys[48].top, 1, (char*)"m\0");

    tempKB.keys[49].top = top;
    tempKB.keys[49].left = next_y;
    tempKB.keys[49].ascii = 0x2c;
    next_y = draw_keys(tempKB.keys[49].left, tempKB.keys[49].top, 1, (char*)",\0");

    tempKB.keys[50].top = top;
    tempKB.keys[50].left = next_y;
    tempKB.keys[50].ascii = 0x2e;
    next_y = draw_keys(tempKB.keys[50].left, tempKB.keys[50].top, 1, (char*)".\0");

    tempKB.keys[51].top = top;
    tempKB.keys[51].left = next_y;
    tempKB.keys[51].ascii = 0x2f;
    next_y = draw_keys(tempKB.keys[51].left, tempKB.keys[51].top, 1, (char*)"/\0");

    tempKB.keys[52].top = top;
    tempKB.keys[52].left = next_y;
    tempKB.keys[52].ascii = 0x1D;
    tempKB.keys[52].width = key_width * 2;
    next_y = draw_keys(tempKB.keys[52].left, tempKB.keys[52].top, 2, (char*)"SHIFT\0");

    top += tempKB.key_height;
    next_y = left;
    tempKB.keys[53].top = top;
    tempKB.keys[53].left = next_y + (tempKB.key_width * 4) + (tempKB.key_width/2);
    tempKB.keys[53].ascii = 0x20;
    tempKB.keys[53].width = key_width * 6;
    next_y = draw_keys(tempKB.keys[53].left, tempKB.keys[53].top, 6, (char*)"SPACE\0");

    return tempKB;
}

Keyboard draw_shift(unsigned int s_left, unsigned int s_top, unsigned int s_width, unsigned int ecolor, unsigned int bcolor, unsigned int tcolor)
{
    Keyboard tempKB3;
    unsigned int next_y = s_left;
    int x;
    key_top = s_top;
    key_left = s_left;

    //LCD_Reset();
    tempKB3.back_color = bcolor;
    tempKB3.edge_color = ecolor;
    tempKB3.text_color = tcolor;

    kb_back = bcolor;
    kb_edge = ecolor;
    kb_color = tcolor;

    tempKB3.width = s_width;
    tempKB3.key_width = s_width/15;
    tempKB3.key_height = tempKB3.key_width;
    tempKB3.height = tempKB3.key_height * 5;
    tempKB3.left = s_left;
    tempKB3.top = s_top;

    kb_width = s_width;
    key_width = kb_width / 15;
    key_height = key_width;
    kb_height = key_height * 5;

    for (x=0;x<128;x++)
    {
        tempKB3.keys[x].width = key_width;
        tempKB3.keys[x].height = key_height;
    }

    tempKB3.keys[0].top = s_top;
    tempKB3.keys[0].left = next_y;
    tempKB3.keys[0].ascii = 0x7e;
    next_y = draw_keys(tempKB3.keys[0].left, tempKB3.keys[0].top, 1,  (char*)"~\0");

    tempKB3.keys[1].top = s_top;
    tempKB3.keys[1].left = next_y;
    tempKB3.keys[1].ascii = 0x21;
    next_y = draw_keys(tempKB3.keys[1].left, tempKB3.keys[1].top, 1,  (char*)"!\0");

    tempKB3.keys[2].top = s_top;
    tempKB3.keys[2].left = next_y;
    tempKB3.keys[2].ascii = 0x40;
    next_y = draw_keys(tempKB3.keys[2].left, tempKB3.keys[2].top, 1,  (char*)"@\0");

    tempKB3.keys[3].top = s_top;
    tempKB3.keys[3].left = next_y;
    tempKB3.keys[3].ascii = 0x23;
    next_y = draw_keys(tempKB3.keys[3].left, tempKB3.keys[3].top, 1,  (char*)"#\0");

    tempKB3.keys[4].top = s_top;
    tempKB3.keys[4].left = next_y;
    tempKB3.keys[4].ascii = 0x24;
    next_y = draw_keys(tempKB3.keys[4].left, tempKB3.keys[4].top, 1,  (char*)"$\0");

    tempKB3.keys[5].top = s_top;
    tempKB3.keys[5].left = next_y;
    tempKB3.keys[5].ascii = 0x25;
    next_y = draw_keys(tempKB3.keys[5].left, tempKB3.keys[5].top, 1,  (char*)"%\0");

    tempKB3.keys[6].top = s_top;
    tempKB3.keys[6].left = next_y;
    tempKB3.keys[6].ascii = 0x5e;
    next_y = draw_keys(tempKB3.keys[6].left, tempKB3.keys[6].top, 1,  (char*)"^\0");

    tempKB3.keys[7].top = s_top;
    tempKB3.keys[7].left = next_y;
    tempKB3.keys[7].ascii = 0x26;
    next_y = draw_keys(tempKB3.keys[7].left, tempKB3.keys[7].top, 1,  (char*)"&\0");

    tempKB3.keys[8].top = s_top;
    tempKB3.keys[8].left = next_y;
    tempKB3.keys[8].ascii = 0x2a;
    next_y = draw_keys(tempKB3.keys[8].left, tempKB3.keys[8].top, 1,  (char*)"*\0");

    tempKB3.keys[9].top = s_top;
    tempKB3.keys[9].left = next_y;
    tempKB3.keys[9].ascii = 0x28;
    next_y = draw_keys(tempKB3.keys[9].left, tempKB3.keys[9].top, 1,  (char*)"(\0");

    tempKB3.keys[10].top = s_top;
    tempKB3.keys[10].left = next_y;
    tempKB3.keys[10].ascii = 0x29;
    next_y = draw_keys(tempKB3.keys[10].left, tempKB3.keys[10].top, 1,  (char*)")\0");

    tempKB3.keys[11].top = s_top;
    tempKB3.keys[11].left = next_y;
    tempKB3.keys[11].ascii = 0x5f;
    next_y = draw_keys(tempKB3.keys[11].left, tempKB3.keys[11].top, 1,  (char*)"_\0");

    tempKB3.keys[12].top = s_top;
    tempKB3.keys[12].left = next_y;
    tempKB3.keys[12].ascii = 0x2b;
    next_y = draw_keys(tempKB3.keys[12].left, tempKB3.keys[12].top, 1,  (char*)"+\0");

    tempKB3.keys[13].top = s_top;
    tempKB3.keys[13].left = next_y;
    tempKB3.keys[13].ascii = 0x08;
    next_y = draw_keys(tempKB3.keys[13].left, tempKB3.keys[13].top, 2,  (char*)"BKSP\0");

    s_top+= tempKB3.key_height;
    next_y = s_left;
    tempKB3.keys[14].top = s_top;
    tempKB3.keys[14].left = next_y;
    tempKB3.keys[14].ascii = 0x09;
    next_y = draw_keys(tempKB3.keys[14].left, tempKB3.keys[14].top, 2,  (char*)"TAB\0");

    tempKB3.keys[15].top = s_top;
    tempKB3.keys[15].left = next_y;
    tempKB3.keys[15].ascii = 0x51;
    next_y = draw_keys(tempKB3.keys[15].left, tempKB3.keys[15].top, 1,  (char*)"Q\0");

    tempKB3.keys[16].top = s_top;
    tempKB3.keys[16].left = next_y;
    tempKB3.keys[16].ascii = 0x57;
    next_y = draw_keys(tempKB3.keys[16].left, tempKB3.keys[16].top, 1,  (char*)"W\0");

    tempKB3.keys[17].top = s_top;
    tempKB3.keys[17].left = next_y;
    tempKB3.keys[17].ascii = 0x45;
    next_y = draw_keys(tempKB3.keys[17].left, tempKB3.keys[17].top, 1,  (char*)"E\0");

    tempKB3.keys[18].top = s_top;
    tempKB3.keys[18].left = next_y;
    tempKB3.keys[18].ascii = 0x52;
    next_y = draw_keys(tempKB3.keys[18].left, tempKB3.keys[18].top, 1,  (char*)"R\0");

    tempKB3.keys[19].top = s_top;
    tempKB3.keys[19].left = next_y;
    tempKB3.keys[19].ascii = 0x54;
    next_y = draw_keys(tempKB3.keys[19].left, tempKB3.keys[19].top, 1,  (char*)"T\0");

    tempKB3.keys[20].top = s_top;
    tempKB3.keys[20].left = next_y;
    tempKB3.keys[20].ascii = 0x59;
    next_y = draw_keys(tempKB3.keys[20].left, tempKB3.keys[20].top, 1,  (char*)"Y\0");

    tempKB3.keys[21].top = s_top;
    tempKB3.keys[21].left = next_y;
    tempKB3.keys[21].ascii = 0x55;
    next_y = draw_keys(tempKB3.keys[21].left, tempKB3.keys[21].top, 1,  (char*)"U\0");

    tempKB3.keys[22].top = s_top;
    tempKB3.keys[22].left = next_y;
    tempKB3.keys[22].ascii = 0x49;
    next_y = draw_keys(tempKB3.keys[22].left, tempKB3.keys[22].top, 1,  (char*)"I\0");

    tempKB3.keys[23].top = s_top;
    tempKB3.keys[23].left = next_y;
    tempKB3.keys[23].ascii = 0x4f;
    next_y = draw_keys(tempKB3.keys[23].left, tempKB3.keys[23].top, 1,  (char*)"O\0");

    tempKB3.keys[24].top = s_top;
    tempKB3.keys[24].left = next_y;
    tempKB3.keys[24].ascii = 0x50;
    next_y = draw_keys(tempKB3.keys[24].left, tempKB3.keys[24].top, 1,  (char*)"P\0");

    tempKB3.keys[25].top = s_top;
    tempKB3.keys[25].left = next_y;
    tempKB3.keys[25].ascii = 0x7b;
    next_y = draw_keys(tempKB3.keys[25].left, tempKB3.keys[25].top, 1,  (char*)"{\0");

    tempKB3.keys[26].top = s_top;
    tempKB3.keys[26].left = next_y;
    tempKB3.keys[26].ascii = 0x7d;
    next_y = draw_keys(tempKB3.keys[26].left, tempKB3.keys[26].top, 1,  (char*)"}\0");

    tempKB3.keys[27].top = s_top;
    tempKB3.keys[27].left = next_y;
    tempKB3.keys[27].ascii = 0x7c;
    next_y = draw_keys(tempKB3.keys[27].left, tempKB3.keys[27].top, 1,  (char*)"|\0");

    s_top+= tempKB3.key_height;
    next_y = s_left;
    tempKB3.keys[28].top = s_top;
    tempKB3.keys[28].left = next_y;
    tempKB3.keys[28].ascii = 0x1c;
    next_y = draw_keys(tempKB3.keys[28].left, tempKB3.keys[28].top, 2,  (char*)"CAPS\0");

    tempKB3.keys[29].top = s_top;
    tempKB3.keys[29].left = next_y;
    tempKB3.keys[29].ascii = 0x41;
    next_y = draw_keys(tempKB3.keys[29].left, tempKB3.keys[29].top, 1,  (char*)"A\0");

    tempKB3.keys[30].top = s_top;
    tempKB3.keys[30].left = next_y;
    tempKB3.keys[30].ascii = 0x53;
    next_y = draw_keys(tempKB3.keys[30].left, tempKB3.keys[30].top, 1,  (char*)"S\0");

    tempKB3.keys[31].top = s_top;
    tempKB3.keys[31].left = next_y;
    tempKB3.keys[31].ascii = 0x44;
    next_y = draw_keys(tempKB3.keys[31].left, tempKB3.keys[31].top, 1,  (char*)"D\0");

    tempKB3.keys[32].top = s_top;
    tempKB3.keys[32].left = next_y;
    tempKB3.keys[32].ascii = 0x46;
    next_y = draw_keys(tempKB3.keys[32].left, tempKB3.keys[32].top, 1,  (char*)"F\0");

    tempKB3.keys[33].top = s_top;
    tempKB3.keys[33].left = next_y;
    tempKB3.keys[33].ascii = 0x47;
    next_y = draw_keys(tempKB3.keys[33].left, tempKB3.keys[33].top, 1,  (char*)"G\0");

    tempKB3.keys[34].top = s_top;
    tempKB3.keys[34].left = next_y;
    tempKB3.keys[34].ascii = 0x48;
    next_y = draw_keys(tempKB3.keys[34].left, tempKB3.keys[34].top, 1,  (char*)"H\0");

    tempKB3.keys[35].top = s_top;
    tempKB3.keys[35].left = next_y;
    tempKB3.keys[35].ascii = 0x4a;
    next_y = draw_keys(tempKB3.keys[35].left, tempKB3.keys[35].top, 1,  (char*)"J\0");

    tempKB3.keys[36].top = s_top;
    tempKB3.keys[36].left = next_y;
    tempKB3.keys[36].ascii = 0x4b;
    next_y = draw_keys(tempKB3.keys[36].left, tempKB3.keys[36].top, 1,  (char*)"K\0");

    tempKB3.keys[37].top = s_top;
    tempKB3.keys[37].left = next_y;
    tempKB3.keys[37].ascii = 0x4c;
    next_y = draw_keys(tempKB3.keys[37].left, tempKB3.keys[37].top, 1,  (char*)"L\0");

    tempKB3.keys[38].top = s_top;
    tempKB3.keys[38].left = next_y;
    tempKB3.keys[38].ascii = 0x3a;
    next_y = draw_keys(tempKB3.keys[38].left, tempKB3.keys[38].top, 1,  (char*)":\0");

    tempKB3.keys[39].top = s_top;
    tempKB3.keys[39].left = next_y;
    tempKB3.keys[39].ascii = 0x22;
    next_y = draw_keys(tempKB3.keys[39].left, tempKB3.keys[39].top, 1,  (char*)"\"\0");

    tempKB3.keys[40].top = s_top;
    tempKB3.keys[40].left = next_y;
    tempKB3.keys[40].ascii = 0x0d;
    next_y = draw_keys(tempKB3.keys[40].left, tempKB3.keys[40].top, 2,  (char*)"ENTER\0");

    s_top+= tempKB3.key_height;
    next_y = s_left+(tempKB3.key_width/2);
    tempKB3.keys[41].top = s_top;
    tempKB3.keys[41].left = next_y;
    tempKB3.keys[41].ascii = 0x1D;
    next_y = draw_keys(tempKB3.keys[41].left, tempKB3.keys[41].top, 2,  (char*)"SHIFT\0");

    tempKB3.keys[42].top = s_top;
    tempKB3.keys[42].left = next_y;
    tempKB3.keys[42].ascii = 0x5a;
    next_y = draw_keys(tempKB3.keys[42].left, tempKB3.keys[42].top, 1,  (char*)"Z\0");

    tempKB3.keys[43].top = s_top;
    tempKB3.keys[43].left = next_y;
    tempKB3.keys[43].ascii = 0x58;
    next_y = draw_keys(tempKB3.keys[43].left, tempKB3.keys[43].top, 1,  (char*)"X\0");

    tempKB3.keys[44].top = s_top;
    tempKB3.keys[44].left = next_y;
    tempKB3.keys[44].ascii = 0x43;
    next_y = draw_keys(tempKB3.keys[44].left, tempKB3.keys[44].top, 1,  (char*)"C\0");

    tempKB3.keys[45].top = s_top;
    tempKB3.keys[45].left = next_y;
    tempKB3.keys[45].ascii = 0x56;
    next_y = draw_keys(tempKB3.keys[45].left, tempKB3.keys[45].top, 1,  (char*)"V\0");

    tempKB3.keys[46].top = s_top;
    tempKB3.keys[46].left = next_y;
    tempKB3.keys[46].ascii = 0x42;
    next_y = draw_keys(tempKB3.keys[46].left, tempKB3.keys[46].top, 1,  (char*)"B\0");

    tempKB3.keys[47].top = s_top;
    tempKB3.keys[47].left = next_y;
    tempKB3.keys[47].ascii = 0x4e;
    next_y = draw_keys(tempKB3.keys[47].left, tempKB3.keys[47].top, 1,  (char*)"N\0");

    tempKB3.keys[48].top = s_top;
    tempKB3.keys[48].left = next_y;
    tempKB3.keys[48].ascii = 0x4d;
    next_y = draw_keys(tempKB3.keys[48].left, tempKB3.keys[48].top, 1,  (char*)"M\0");

    tempKB3.keys[49].top = s_top;
    tempKB3.keys[49].left = next_y;
    tempKB3.keys[49].ascii = 0x3c;
    next_y = draw_keys(tempKB3.keys[49].left, tempKB3.keys[49].top, 1,  (char*)"<\0");

    tempKB3.keys[50].top = s_top;
    tempKB3.keys[50].left = next_y;
    tempKB3.keys[50].ascii = 0x3e;
    next_y = draw_keys(tempKB3.keys[50].left, tempKB3.keys[50].top, 1,  (char*)">\0");

    tempKB3.keys[51].top = s_top;
    tempKB3.keys[51].left = next_y;
    tempKB3.keys[51].ascii = 0x3f;
    next_y = draw_keys(tempKB3.keys[51].left, tempKB3.keys[51].top, 1,  (char*)"?\0");

    tempKB3.keys[52].top = s_top;
    tempKB3.keys[52].left = next_y;
    tempKB3.keys[52].ascii = 0x1D;
    next_y = draw_keys(tempKB3.keys[52].left, tempKB3.keys[52].top, 2,  (char*)"SHIFT\0");

    s_top += tempKB3.key_height;
    next_y = s_left;
    tempKB3.keys[53].top = s_top;
    tempKB3.keys[53].left = next_y + (tempKB3.key_width * 4) + (tempKB3.key_width/2);
    tempKB3.keys[53].ascii = 0x20;
    next_y = draw_keys(tempKB3.keys[53].left, tempKB3.keys[53].top, 6, (char*)"SPACE\0");

    return tempKB3;
}
unsigned int getLen (char *text)
{
    unsigned int len = 0;

    while(*text)
    {
        text++;
        len++;
    }

    return len;
}
unsigned int draw_keys(unsigned int left, unsigned int top, char key_scale, char *text)
{
    unsigned int keyW = key_width*key_scale;
    unsigned int next_left = left + keyW;
    unsigned int tLeft, tTop;
    unsigned int tLen;


    
    tLen = getLen(text) * 6;
    tLeft = (keyW / 2) - (tLen / 2) + left - 3;
    tTop = ((key_height / 2) - 7) + top;

    
    drawRect(left+1, top+1, keyW-2, key_height-2, kb_back, 1); delay_us(100);//delay_us(40);
    drawRect(left, top, keyW, key_height, kb_edge, 0); delay_us(100);


    FontWrite_Position(tLeft,tTop);
    SetColors(kb_color,kb_back);

    String(text);
    
    return next_left;
}