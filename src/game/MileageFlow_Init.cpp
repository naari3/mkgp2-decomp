#include "game/MileageFlowPrivate.h"
MileageFlow::MileageFlow() {
    MileageTables* table=&lbl_8049ACB0;
    vt=(char*)table+0x90;
    SetSyncTarget(0x13); PreloadResource(0x18dd);
    for(int i=0;i<11;i++) available[i]=0;
    available[0]=1;
    if(GetCoinMilage(g_playerData)<table->entries[0].miles) available[rand()%10+1]=1;
    else for(int i=1;i<11;i++) if(GetCoinMilage(g_playerData)>=table->entries[i-1].miles) available[i]=1;
    if(!IsCardValid()) for(int i=1;i<11;i++) available[i]=1;
    for(int i=0;i<11;i++) {
        if(i==0) {
            icons[i]=new FigureSprite(0x1b2,0,0);
            Sprite_SetAnimParam(icons[i],0xc32,table->character[g_characterId][1]); fn_801A0550(icons[i]);
            titles[i]=new FigureSprite(0x1ae,0,0);
            Sprite_SetAnimParam(titles[i],0x1cb7,table->character[g_characterId][0]); fn_801A0550(titles[i]);
        } else {
            if(available[i]) {
                icons[i]=new FigureSprite(0x1b3,0,0);
                Sprite_SetAnimParam(icons[i],0xc3f,table->entries[i-1].label); fn_801A0550(icons[i]);
                icons[i]->alpha=FLOAT_UNFOCUSED_ALPHA;
                icons[i]->sx=FLOAT_UNFOCUSED_SCALE; icons[i]->sy=FLOAT_UNFOCUSED_SCALE;
                count++;
            } else icons[i]=new FigureSprite(0x1b1,1,0);
            titles[i]=new FigureSprite(0x1ae,0,0);
            Sprite_SetAnimParam(titles[i],0x1cb7,table->entries[i-1].title); fn_801A0550(titles[i]);
        }
        icons[i]->SetPos(FLOAT_TITLE_STEP_X*(float)i+FLOAT_TITLE_BASE_X,FLOAT_TITLE_POS_Y);
        fn_8019FF6C(icons[i],1);
        titles[i]->SetPos(lbl_806D9C20,lbl_806D9C60);
        fn_8019FF6C(titles[i],1);
    }
    s30=new FigureSprite(0x1ad,0,lbl_806D9C20,lbl_806D9C38);
    s34=new FigureSprite(0x5e,1,FLOAT_TITLE_BASE_X,FLOAT_TITLE_POS_Y);
    s38=new FigureSprite(0x5f,1,lbl_806D9C20,lbl_806D9C38);
    s3c=new FigureSprite(0x63,1,lbl_806D9C20,lbl_806D9C38);
    s40=new FigureSprite(0x60,0,lbl_806D9C20,lbl_806D9C64);
    s44=new FigureSprite(0x61,0,lbl_806D9C20,lbl_806D9C64);
    complete=0; pending=0; field20=0; selection=0; field1c=0; s48=0; s4c=0; field28=0;
    camera=new MileageCamera;
    next=-1;
    camera->Start();
    if(GetInput()) { InputState* input=GetInput(); input->enabled=1; input->held=0; input->edge=0; }
    SetupBgSprites(0); g_confirmFlag=0;
    unsigned char allow=1;
    if(g_gameMode != 2 && !g_playerData[0x19d]) allow=0;
    if(!allow || !GetVBlankFlag() || VBlankValue_Get() == 1) {
        if(g_gameMode == 0) next=0x15;
        else if(g_gameMode == 1) next=0x17;
        skip=1; prompt=0; ticks=0xd2;
    } else {
        skip=0;
        prompt=new FigureSprite(0xcd,0,FLOAT_ANIM_RESET,FLOAT_ANIM_RESET);
        ticks=0; PlaySoundDSP(0x272); InitRumbleController(1); fn_801699D8(0,1);
    }
    fn_801B7B04(0);
}
