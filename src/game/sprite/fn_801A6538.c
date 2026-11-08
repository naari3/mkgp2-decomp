#include "game/RaceVoiceRivalPrivate.h"

/* Rotating comment lists.  They are the initialisers of the voice module's
 * local arrays and live inside its .rodata block at 0x803810A8. */
typedef struct VoiceList6 { short v[6]; } VoiceList6;
typedef struct VoiceList5 { short v[5]; } VoiceList5;
typedef struct VoiceList10 { short v[10]; } VoiceList10;
typedef struct VoiceList3 { short v[3]; } VoiceList3;
/* Voice module constants, in original section order. */
#pragma force_active on
const float lbl_803810A8[255] = {
    1.0f, 0.699999988079071f, 0.8999999761581421f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 83.33333587646484f, 1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f, 83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f, 1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f, 83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f, 1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f, 83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f, 1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f, 83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f, 1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f, 83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f, 1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f, 83.33333587646484f, 5000.0f, 83.33333587646484f
};
const char lbl_803814A4[13] = "live_A01.dsp";
const char lbl_803814B4[13] = "live_A02.dsp";
const char lbl_803814C4[13] = "live_A03.dsp";
const char lbl_803814D4[13] = "live_A04.dsp";
const char lbl_803814E4[13] = "live_A05.dsp";
const char lbl_803814F4[13] = "live_A06.dsp";
const char lbl_80381504[13] = "live_A07.dsp";
const char lbl_80381514[13] = "live_A08.dsp";
const char lbl_80381524[13] = "live_A09.dsp";
const char lbl_80381534[13] = "live_A10.dsp";
const char lbl_80381544[13] = "live_A11.dsp";
const char lbl_80381554[13] = "live_A12.dsp";
const char lbl_80381564[13] = "live_A13.dsp";
const char lbl_80381574[13] = "live_A14.dsp";
const char lbl_80381584[13] = "live_A15.dsp";
const char lbl_80381594[13] = "live_A16.dsp";
const char lbl_803815A4[13] = "live_B01.dsp";
const char lbl_803815B4[13] = "live_B02.dsp";
const char lbl_803815C4[13] = "live_B03.dsp";
const char lbl_803815D4[13] = "live_B04.dsp";
const char lbl_803815E4[13] = "live_B05.dsp";
const char lbl_803815F4[13] = "live_B06.dsp";
const char lbl_80381604[13] = "live_B07.dsp";
const char lbl_80381614[13] = "live_B08.dsp";
const char lbl_80381624[13] = "live_B09.dsp";
const char lbl_80381634[13] = "live_B10.dsp";
const char lbl_80381644[13] = "live_B11.dsp";
const char lbl_80381654[13] = "live_B12.dsp";
const char lbl_80381664[13] = "live_B13.dsp";
const char lbl_80381674[13] = "live_B14.dsp";
const char lbl_80381684[13] = "live_B15.dsp";
const char lbl_80381694[13] = "live_B16.dsp";
const char lbl_803816A4[13] = "live_B17.dsp";
const char lbl_803816B4[13] = "live_B18.dsp";
const char lbl_803816C4[13] = "live_B19.dsp";
const char lbl_803816D4[13] = "live_B20.dsp";
const char lbl_803816E4[13] = "live_B21.dsp";
const char lbl_803816F4[13] = "live_B22.dsp";
const char lbl_80381704[13] = "live_B23.dsp";
const char lbl_80381714[13] = "live_B24.dsp";
const char lbl_80381724[13] = "live_B25.dsp";
const char lbl_80381734[13] = "live_B26.dsp";
const char lbl_80381744[13] = "live_B27.dsp";
const char lbl_80381754[13] = "live_B28.dsp";
const char lbl_80381764[13] = "live_B29.dsp";
const char lbl_80381774[13] = "live_B30.dsp";
const char lbl_80381784[13] = "live_B31.dsp";
const char lbl_80381794[13] = "live_B32.dsp";
const char lbl_803817A4[13] = "live_B35.dsp";
const char lbl_803817B4[13] = "live_B36.dsp";
const char lbl_803817C4[13] = "live_B33.dsp";
const char lbl_803817D4[13] = "live_B34.dsp";
const char lbl_803817E4[13] = "live_B37.dsp";
const char lbl_803817F4[13] = "live_B38.dsp";
const char lbl_80381804[14] = "live_C001.dsp";
const char lbl_80381814[14] = "live_C002.dsp";
const char lbl_80381824[14] = "live_C003.dsp";
const char lbl_80381834[14] = "live_C004.dsp";
const char lbl_80381844[14] = "live_C005.dsp";
const char lbl_80381854[14] = "live_C006.dsp";
const char lbl_80381864[14] = "live_C007.dsp";
const char lbl_80381874[14] = "live_C008.dsp";
const char lbl_80381884[14] = "live_C009.dsp";
const char lbl_80381894[14] = "live_C010.dsp";
const char lbl_803818A4[14] = "live_C011.dsp";
const char lbl_803818B4[14] = "live_C012.dsp";
const char lbl_803818C4[14] = "live_C013.dsp";
const char lbl_803818D4[14] = "live_C101.dsp";
const char lbl_803818E4[14] = "live_C102.dsp";
const char lbl_803818F4[14] = "live_C103.dsp";
const char lbl_80381904[14] = "live_C104.dsp";
const char lbl_80381914[14] = "live_C105.dsp";
const char lbl_80381924[14] = "live_C106.dsp";
const char lbl_80381934[14] = "live_C107.dsp";
const char lbl_80381944[14] = "live_C108.dsp";
const char lbl_80381954[14] = "live_C109.dsp";
const char lbl_80381964[14] = "live_C110.dsp";
const char lbl_80381974[14] = "live_C111.dsp";
const char lbl_80381984[14] = "live_C112.dsp";
const char lbl_80381994[14] = "live_C113.dsp";
const char lbl_803819A4[14] = "live_C201.dsp";
const char lbl_803819B4[14] = "live_C202.dsp";
const char lbl_803819C4[14] = "live_C203.dsp";
const char lbl_803819D4[14] = "live_C204.dsp";
const char lbl_803819E4[14] = "live_C205.dsp";
const char lbl_803819F4[14] = "live_C206.dsp";
const char lbl_80381A04[14] = "live_C207.dsp";
const char lbl_80381A14[14] = "live_C208.dsp";
const char lbl_80381A24[14] = "live_C209.dsp";
const char lbl_80381A34[14] = "live_C210.dsp";
const char lbl_80381A44[14] = "live_C211.dsp";
const char lbl_80381A54[14] = "live_C212.dsp";
const char lbl_80381A64[14] = "live_C213.dsp";
const char lbl_80381A74[14] = "live_C301.dsp";
const char lbl_80381A84[14] = "live_C302.dsp";
const char lbl_80381A94[14] = "live_C303.dsp";
const char lbl_80381AA4[14] = "live_C304.dsp";
const char lbl_80381AB4[14] = "live_C305.dsp";
const char lbl_80381AC4[14] = "live_C306.dsp";
const char lbl_80381AD4[14] = "live_C307.dsp";
const char lbl_80381AE4[14] = "live_C308.dsp";
const char lbl_80381AF4[14] = "live_C309.dsp";
const char lbl_80381B04[14] = "live_C310.dsp";
const char lbl_80381B14[14] = "live_C311.dsp";
const char lbl_80381B24[14] = "live_C312.dsp";
const char lbl_80381B34[14] = "live_C313.dsp";
const char lbl_80381B44[14] = "live_C401.dsp";
const char lbl_80381B54[14] = "live_C402.dsp";
const char lbl_80381B64[14] = "live_C403.dsp";
const char lbl_80381B74[14] = "live_C404.dsp";
const char lbl_80381B84[14] = "live_C405.dsp";
const char lbl_80381B94[14] = "live_C406.dsp";
const char lbl_80381BA4[14] = "live_C407.dsp";
const char lbl_80381BB4[14] = "live_C408.dsp";
const char lbl_80381BC4[14] = "live_C409.dsp";
const char lbl_80381BD4[14] = "live_C410.dsp";
const char lbl_80381BE4[14] = "live_C411.dsp";
const char lbl_80381BF4[14] = "live_C412.dsp";
const char lbl_80381C04[14] = "live_C413.dsp";
const char lbl_80381C14[14] = "live_D001.dsp";
const char lbl_80381C24[14] = "live_D002.dsp";
const char lbl_80381C34[14] = "live_D003.dsp";
const char lbl_80381C44[14] = "live_D004.dsp";
const char lbl_80381C54[14] = "live_D005.dsp";
const char lbl_80381C64[14] = "live_D006.dsp";
const char lbl_80381C74[14] = "live_D007.dsp";
const char lbl_80381C84[14] = "live_D008.dsp";
const char lbl_80381C94[14] = "live_D009.dsp";
const char lbl_80381CA4[14] = "live_D010.dsp";
const char lbl_80381CB4[14] = "live_D011.dsp";
const char lbl_80381CC4[14] = "live_D012.dsp";
const char lbl_80381CD4[14] = "live_D013.dsp";
const char lbl_80381CE4[14] = "live_D101.dsp";
const char lbl_80381CF4[14] = "live_D102.dsp";
const char lbl_80381D04[14] = "live_D103.dsp";
const char lbl_80381D14[14] = "live_D104.dsp";
const char lbl_80381D24[14] = "live_D105.dsp";
const char lbl_80381D34[14] = "live_D106.dsp";
const char lbl_80381D44[14] = "live_D107.dsp";
const char lbl_80381D54[14] = "live_D108.dsp";
const char lbl_80381D64[14] = "live_D109.dsp";
const char lbl_80381D74[14] = "live_D110.dsp";
const char lbl_80381D84[14] = "live_D111.dsp";
const char lbl_80381D94[14] = "live_D112.dsp";
const char lbl_80381DA4[14] = "live_D113.dsp";
const char lbl_80381DB4[14] = "live_D201.dsp";
const char lbl_80381DC4[14] = "live_D202.dsp";
const char lbl_80381DD4[14] = "live_D203.dsp";
const char lbl_80381DE4[14] = "live_D204.dsp";
const char lbl_80381DF4[14] = "live_D205.dsp";
const char lbl_80381E04[14] = "live_D206.dsp";
const char lbl_80381E14[14] = "live_D207.dsp";
const char lbl_80381E24[14] = "live_D208.dsp";
const char lbl_80381E34[14] = "live_D209.dsp";
const char lbl_80381E44[14] = "live_D210.dsp";
const char lbl_80381E54[14] = "live_D211.dsp";
const char lbl_80381E64[14] = "live_D212.dsp";
const char lbl_80381E74[14] = "live_D213.dsp";
const char lbl_80381E84[14] = "live_D301.dsp";
const char lbl_80381E94[14] = "live_D302.dsp";
const char lbl_80381EA4[14] = "live_D303.dsp";
const char lbl_80381EB4[14] = "live_D304.dsp";
const char lbl_80381EC4[14] = "live_D305.dsp";
const char lbl_80381ED4[14] = "live_D306.dsp";
const char lbl_80381EE4[14] = "live_D307.dsp";
const char lbl_80381EF4[14] = "live_D308.dsp";
const char lbl_80381F04[14] = "live_D309.dsp";
const char lbl_80381F14[14] = "live_D310.dsp";
const char lbl_80381F24[14] = "live_D311.dsp";
const char lbl_80381F34[14] = "live_D312.dsp";
const char lbl_80381F44[14] = "live_D313.dsp";
const char lbl_80381F54[14] = "live_D401.dsp";
const char lbl_80381F64[14] = "live_D402.dsp";
const char lbl_80381F74[14] = "live_D403.dsp";
const char lbl_80381F84[14] = "live_D404.dsp";
const char lbl_80381F94[14] = "live_D405.dsp";
const char lbl_80381FA4[14] = "live_D406.dsp";
const char lbl_80381FB4[14] = "live_D407.dsp";
const char lbl_80381FC4[14] = "live_D408.dsp";
const char lbl_80381FD4[14] = "live_D409.dsp";
const char lbl_80381FE4[14] = "live_D410.dsp";
const char lbl_80381FF4[14] = "live_D411.dsp";
const char lbl_80382004[14] = "live_D412.dsp";
const char lbl_80382014[14] = "live_D413.dsp";
const char lbl_80382024[14] = "live_E001.dsp";
const char lbl_80382034[14] = "live_E002.dsp";
const char lbl_80382044[14] = "live_E003.dsp";
const char lbl_80382054[14] = "live_E004.dsp";
const char lbl_80382064[14] = "live_E005.dsp";
const char lbl_80382074[14] = "live_E006.dsp";
const char lbl_80382084[14] = "live_E007.dsp";
const char lbl_80382094[14] = "live_E008.dsp";
const char lbl_803820A4[14] = "live_E009.dsp";
const char lbl_803820B4[14] = "live_E010.dsp";
const char lbl_803820C4[14] = "live_E011.dsp";
const char lbl_803820D4[14] = "live_E012.dsp";
const char lbl_803820E4[14] = "live_E013.dsp";
const char lbl_803820F4[14] = "live_E014.dsp";
const char lbl_80382104[14] = "live_E015.dsp";
const char lbl_80382114[14] = "live_E016.dsp";
const char lbl_80382124[14] = "live_E017.dsp";
const char lbl_80382134[14] = "live_E018.dsp";
const char lbl_80382144[14] = "live_E019.dsp";
const char lbl_80382154[14] = "live_E020.dsp";
const char lbl_80382164[14] = "live_E021.dsp";
const char lbl_80382174[14] = "live_E022.dsp";
const char lbl_80382184[14] = "live_E023.dsp";
const char lbl_80382194[14] = "live_E024.dsp";
const char lbl_803821A4[14] = "live_E025.dsp";
const char lbl_803821B4[14] = "live_E026.dsp";
const char lbl_803821C4[14] = "live_E027.dsp";
const char lbl_803821D4[14] = "live_E028.dsp";
const char lbl_803821E4[14] = "live_E029.dsp";
const char lbl_803821F4[14] = "live_E030.dsp";
const char lbl_80382204[14] = "live_E031.dsp";
const char lbl_80382214[14] = "live_E032.dsp";
const char lbl_80382224[14] = "live_E033.dsp";
const char lbl_80382234[14] = "live_E034.dsp";
const char lbl_80382244[14] = "live_E035.dsp";
const char lbl_80382254[14] = "live_E036.dsp";
const char lbl_80382264[14] = "live_E037.dsp";
const char lbl_80382274[14] = "live_E038.dsp";
const char lbl_80382284[14] = "live_E039.dsp";
const char lbl_80382294[14] = "live_E040.dsp";
const char lbl_803822A4[14] = "live_E041.dsp";
const char lbl_803822B4[14] = "live_E042.dsp";
const char lbl_803822C4[14] = "live_E043.dsp";
const char lbl_803822D4[14] = "live_E044.dsp";
const char lbl_803822E4[14] = "live_E045.dsp";
const char lbl_803822F4[14] = "live_E046.dsp";
const char lbl_80382304[14] = "live_E047.dsp";
const char lbl_80382314[14] = "live_E048.dsp";
const char lbl_80382324[14] = "live_E049.dsp";
const char lbl_80382334[14] = "live_E050.dsp";
const char lbl_80382344[14] = "live_E051.dsp";
const char lbl_80382354[14] = "live_E052.dsp";
const char lbl_80382364[14] = "live_E053.dsp";
const char lbl_80382374[14] = "live_E054.dsp";
const char lbl_80382384[14] = "live_E055.dsp";
const char lbl_80382394[14] = "live_E056.dsp";
const char lbl_803823A4[14] = "live_E057.dsp";
const char lbl_803823B4[14] = "live_E058.dsp";
const char lbl_803823C4[14] = "live_E059.dsp";
const char lbl_803823D4[14] = "live_E060.dsp";
const char lbl_803823E4[14] = "live_E061.dsp";
const char lbl_803823F4[14] = "live_E062.dsp";
const char lbl_80382404[14] = "live_E063.dsp";
const char lbl_80382414[14] = "live_E064.dsp";
const char lbl_80382424[14] = "live_E065.dsp";
const char lbl_80382434[14] = "live_E066.dsp";
const char lbl_80382444[14] = "live_E067.dsp";
const char lbl_80382454[14] = "live_E068.dsp";
const char lbl_80382464[14] = "live_E069.dsp";
const char lbl_80382474[14] = "live_E070.dsp";
const char lbl_80382484[14] = "live_E071.dsp";
const char lbl_80382494[14] = "live_E072.dsp";
const char lbl_803824A4[14] = "live_E073.dsp";
const char lbl_803824B4[14] = "live_E074.dsp";
const char lbl_803824C4[14] = "live_E075.dsp";
const char lbl_803824D4[14] = "live_E076.dsp";
const char lbl_803824E4[14] = "live_E077.dsp";
const char lbl_803824F4[14] = "live_E078.dsp";
const char lbl_80382504[14] = "live_E079.dsp";
const char lbl_80382514[14] = "live_E080.dsp";
const char lbl_80382524[14] = "live_E081.dsp";
const char lbl_80382534[14] = "live_E082.dsp";
const char lbl_80382544[14] = "live_E083.dsp";
const char lbl_80382554[14] = "live_E084.dsp";
const char lbl_80382564[14] = "live_E085.dsp";
const char lbl_80382574[14] = "live_E086.dsp";
const char lbl_80382584[14] = "live_E087.dsp";
const char lbl_80382594[14] = "live_E088.dsp";
const char lbl_803825A4[14] = "live_E089.dsp";
const char lbl_803825B4[14] = "live_E090.dsp";
const char lbl_803825C4[14] = "live_E107.dsp";
const char lbl_803825D4[13] = "live_F01.dsp";
const char lbl_803825E4[13] = "live_F02.dsp";
const char lbl_803825F4[13] = "live_F03.dsp";
const char lbl_80382604[13] = "live_F04.dsp";
const char lbl_80382614[13] = "live_F05.dsp";
const char lbl_80382624[13] = "live_F06.dsp";
const char lbl_80382634[13] = "live_G01.dsp";
const char lbl_80382644[13] = "live_G02.dsp";
const char lbl_80382654[13] = "live_G03.dsp";
const char lbl_80382664[13] = "live_G04.dsp";
const char lbl_80382674[13] = "live_G05.dsp";
const char lbl_80382684[13] = "live_G06.dsp";
const char lbl_80382694[13] = "live_G07.dsp";
const char lbl_803826A4[13] = "live_G08.dsp";
const char lbl_803826B4[13] = "live_G09.dsp";
const char lbl_803826C4[13] = "live_G10.dsp";
const char lbl_803826D4[13] = "live_G11.dsp";
const char lbl_803826E4[13] = "live_G12.dsp";
const char lbl_803826F4[13] = "live_G13.dsp";
const char lbl_80382704[13] = "live_G14.dsp";
const char lbl_80382714[13] = "live_G15.dsp";
const char lbl_80382724[13] = "live_G16.dsp";
const char lbl_80382734[13] = "live_G17.dsp";
const char lbl_80382744[13] = "live_G18.dsp";
const char lbl_80382754[13] = "live_G19.dsp";
const char lbl_80382764[13] = "live_G20.dsp";
const char lbl_80382774[13] = "live_G21.dsp";
const char lbl_80382784[14] = "live_S001.dsp";
const char lbl_80382794[14] = "live_S002.dsp";
const char lbl_803827A4[14] = "live_S003.dsp";
const char lbl_803827B4[14] = "live_S004.dsp";
const char lbl_803827C4[14] = "live_S005.dsp";
const char lbl_803827D4[14] = "live_S006.dsp";
const char lbl_803827E4[14] = "live_S007.dsp";
const char lbl_803827F4[14] = "live_S008.dsp";
const char lbl_80382804[14] = "live_S009.dsp";
const char lbl_80382814[14] = "live_S010.dsp";
const char lbl_80382824[14] = "live_S011.dsp";
const char lbl_80382834[14] = "live_S012.dsp";
const char lbl_80382844[14] = "live_S013.dsp";
const char lbl_80382854[14] = "live_S101.dsp";
const char lbl_80382864[14] = "live_S102.dsp";
const char lbl_80382874[14] = "live_S103.dsp";
const char lbl_80382884[14] = "live_S104.dsp";
const char lbl_80382894[14] = "live_S105.dsp";
const char lbl_803828A4[14] = "live_S106.dsp";
const char lbl_803828B4[14] = "live_S107.dsp";
const char lbl_803828C4[14] = "live_S108.dsp";
const char lbl_803828D4[14] = "live_S109.dsp";
const char lbl_803828E4[14] = "live_S110.dsp";
const char lbl_803828F4[14] = "live_S111.dsp";
const char lbl_80382904[14] = "live_S112.dsp";
const char lbl_80382914[14] = "live_S113.dsp";
const char lbl_80382924[14] = "live_S201.dsp";
const char lbl_80382934[14] = "live_S202.dsp";
const char lbl_80382944[14] = "live_S203.dsp";
const char lbl_80382954[14] = "live_S204.dsp";
const char lbl_80382964[14] = "live_S205.dsp";
const char lbl_80382974[14] = "live_S206.dsp";
const char lbl_80382984[14] = "live_S207.dsp";
const char lbl_80382994[14] = "live_S208.dsp";
const char lbl_803829A4[14] = "live_S209.dsp";
const char lbl_803829B4[14] = "live_S210.dsp";
const char lbl_803829C4[14] = "live_S211.dsp";
const char lbl_803829D4[14] = "live_S212.dsp";
const char lbl_803829E4[14] = "live_S213.dsp";
const char lbl_803829F4[14] = "live_S301.dsp";
const char lbl_80382A04[14] = "live_S302.dsp";
const char lbl_80382A14[14] = "live_S303.dsp";
const char lbl_80382A24[14] = "live_S304.dsp";
const char lbl_80382A34[14] = "live_S305.dsp";
const char lbl_80382A44[14] = "live_S306.dsp";
const char lbl_80382A54[14] = "live_S307.dsp";
const char lbl_80382A64[14] = "live_S308.dsp";
const char lbl_80382A74[14] = "live_S309.dsp";
const char lbl_80382A84[14] = "live_S310.dsp";
const char lbl_80382A94[14] = "live_S311.dsp";
const char lbl_80382AA4[14] = "live_S312.dsp";
const char lbl_80382AB4[14] = "live_S313.dsp";
const char lbl_80382AC4[14] = "live_S401.dsp";
const char lbl_80382AD4[14] = "live_S402.dsp";
const char lbl_80382AE4[14] = "live_S403.dsp";
const char lbl_80382AF4[14] = "live_S404.dsp";
const char lbl_80382B04[14] = "live_S405.dsp";
const char lbl_80382B14[14] = "live_S406.dsp";
const char lbl_80382B24[14] = "live_S407.dsp";
const char lbl_80382B34[14] = "live_S408.dsp";
const char lbl_80382B44[14] = "live_S409.dsp";
const char lbl_80382B54[14] = "live_S410.dsp";
const char lbl_80382B64[14] = "live_S411.dsp";
const char lbl_80382B74[14] = "live_S412.dsp";
const char lbl_80382B84[14] = "live_S413.dsp";
const char lbl_80382B94[14] = "live_X001.dsp";
const char lbl_80382BA4[14] = "live_X002.dsp";
const char lbl_80382BB4[14] = "live_X003.dsp";
const char lbl_80382BC4[14] = "live_X004.dsp";
const char lbl_80382BD4[14] = "live_X005.dsp";
const char lbl_80382BE4[14] = "live_X006.dsp";
const char lbl_80382BF4[14] = "live_X007.dsp";
const char lbl_80382C04[14] = "live_X008.dsp";
const char lbl_80382C14[14] = "live_X009.dsp";
const char lbl_80382C24[14] = "live_X010.dsp";
const char lbl_80382C34[14] = "live_X011.dsp";
const char lbl_80382C44[14] = "live_X012.dsp";
const char lbl_80382C54[14] = "live_X013.dsp";
const char lbl_80382C64[14] = "live_X014.dsp";
const char lbl_80382C74[14] = "live_X015.dsp";
const char lbl_80382C84[14] = "live_X016.dsp";
const char lbl_80382C94[14] = "live_X017.dsp";
const char lbl_80382CA4[14] = "live_X018.dsp";
const char lbl_80382CB4[14] = "live_X019.dsp";
const char lbl_80382CC4[14] = "live_X020.dsp";
const char lbl_80382CD4[14] = "live_X021.dsp";
const char lbl_80382CE4[14] = "live_X022.dsp";
const char lbl_80382CF4[14] = "live_X023.dsp";
const char lbl_80382D04[14] = "live_X024.dsp";
const char lbl_80382D14[14] = "live_X025.dsp";
const char lbl_80382D24[14] = "live_X026.dsp";
const char lbl_80382D34[14] = "live_Z001.dsp";
const char lbl_80382D44[14] = "live_Z002.dsp";
const char lbl_80382D54[14] = "live_Z003.dsp";
const char lbl_80382D64[14] = "live_Z009.dsp";
const char lbl_80382D74[14] = "live_Z011.dsp";
const char lbl_80382D84[14] = "live_Z013.dsp";
const char lbl_80382D94[14] = "live_Z015.dsp";
const char lbl_80382DA4[14] = "live_Z016.dsp";
const char lbl_80382DB4[14] = "live_Z017.dsp";
const char lbl_80382DC4[14] = "live_Z018.dsp";
const char lbl_80382DD4[14] = "live_Z019.dsp";
const char lbl_80382DE4[14] = "live_Z020.dsp";
const char lbl_80382DF4[14] = "live_Z021.dsp";
const char lbl_80382E04[14] = "live_Z022.dsp";
const char lbl_80382E14[14] = "live_Z023.dsp";
const char lbl_80382E24[14] = "live_Z025.dsp";
const char lbl_80382E34[14] = "live_Z026.dsp";
const char lbl_80382E44[14] = "live_Z027.dsp";
const char lbl_80382E54[14] = "live_Z028.dsp";
const char lbl_80382E64[14] = "live_Z029.dsp";
const char lbl_80382E74[14] = "live_Z030.dsp";
const char lbl_80382E84[14] = "live_Z031.dsp";
const char lbl_80382E94[14] = "live_Z032.dsp";
const char lbl_80382EA4[14] = "live_Z033.dsp";
const char lbl_80382EB4[14] = "live_Z034.dsp";
const char lbl_80382EC4[14] = "live_Z035.dsp";
const char lbl_80382ED4[14] = "live_Z037.dsp";
const char lbl_80382EE4[14] = "live_Z038.dsp";
const char lbl_80382EF4[14] = "live_Z039.dsp";
const char lbl_80382F04[14] = "live_Z040.dsp";
const char lbl_80382F14[14] = "live_Z041.dsp";
const char lbl_80382F24[14] = "live_Z042.dsp";
const char lbl_80382F34[14] = "live_Z043.dsp";
const char lbl_80382F44[14] = "live_Z044.dsp";
const char lbl_80382F54[14] = "live_Z045.dsp";
const char lbl_80382F64[14] = "live_Z046.dsp";
const char lbl_80382F74[14] = "live_Z047.dsp";
const char lbl_80382F84[14] = "live_Z048.dsp";
const char lbl_80382F94[14] = "live_Z049.dsp";
const char lbl_80382FA4[14] = "live_Z050.dsp";
const char lbl_80382FB4[14] = "live_Z052.dsp";
const char lbl_80382FC4[14] = "live_Z053.dsp";
const char lbl_80382FD4[14] = "live_Z054.dsp";
const char lbl_80382FE4[14] = "live_Z055.dsp";
const char lbl_80382FF4[14] = "live_Z056.dsp";
const char lbl_80383004[14] = "live_Z057.dsp";
const char lbl_80383014[14] = "live_Z058.dsp";
const char lbl_80383024[14] = "live_Z060.dsp";
const char lbl_80383034[14] = "live_Z061.dsp";
const char lbl_80383044[14] = "live_Z062.dsp";
const char lbl_80383054[14] = "live_Z063.dsp";
const char lbl_80383064[14] = "live_Z064.dsp";
const char lbl_80383074[14] = "live_Z065.dsp";
const char lbl_80383084[14] = "live_Z067.dsp";
const char lbl_80383094[14] = "live_Z068.dsp";
const char lbl_803830A4[14] = "live_Z069.dsp";
const char lbl_803830B4[14] = "live_Z070.dsp";
const char lbl_803830C4[14] = "live_Z071.dsp";
const char lbl_803830D4[14] = "live_Z072.dsp";
const char lbl_803830E4[14] = "live_Z073.dsp";
const char lbl_803830F4[14] = "live_Z077.dsp";
const char lbl_80383104[14] = "live_Z078.dsp";
const char lbl_80383114[14] = "live_Z079.dsp";
const char lbl_80383124[14] = "live_Z080.dsp";
const char lbl_80383134[14] = "live_Z083.dsp";
const char lbl_80383144[14] = "live_Z084.dsp";
const char lbl_80383154[14] = "live_Z085.dsp";
const char lbl_80383164[14] = "live_Z086.dsp";
const char lbl_80383174[14] = "live_Z087.dsp";
const char lbl_80383184[14] = "live_Z088.dsp";
const char lbl_80383194[14] = "live_Z089.dsp";
const char lbl_803831A4[14] = "live_Z091.dsp";
const char lbl_803831B4[14] = "live_Z092.dsp";
const char lbl_803831C4[14] = "live_Z093.dsp";
const char lbl_803831D4[14] = "live_Z094.dsp";
const char lbl_803831E4[14] = "live_Z097.dsp";
const char lbl_803831F4[14] = "live_Z098.dsp";
const char lbl_80383204[14] = "live_Z100.dsp";
const char lbl_80383214[14] = "live_Z101.dsp";
const char lbl_80383224[14] = "live_Z102.dsp";
const char lbl_80383234[14] = "live_Z103.dsp";
const char lbl_80383244[14] = "live_Z104.dsp";
const char lbl_80383254[14] = "live_Z105.dsp";
const char lbl_80383264[14] = "live_Z106.dsp";
const char lbl_80383274[14] = "live_Z107.dsp";
const char lbl_80383284[14] = "live_Z108.dsp";
const char lbl_80383294[14] = "live_Z109.dsp";
const char lbl_803832A4[14] = "live_Z110.dsp";
const char lbl_803832B4[14] = "live_Z111.dsp";
const char lbl_803832C4[14] = "live_Z114.dsp";
const char lbl_803832D4[14] = "live_Z115.dsp";
const char lbl_803832E4[14] = "live_Z116.dsp";
const char lbl_803832F4[14] = "live_Z117.dsp";
const char lbl_80383304[14] = "live_Z118.dsp";
const char lbl_80383314[14] = "live_Z119.dsp";
const char lbl_80383324[14] = "live_Z120.dsp";
const char lbl_80383334[14] = "live_Z121.dsp";
const char lbl_80383344[14] = "live_Z122.dsp";
const char lbl_80383354[14] = "live_Z123.dsp";
const char lbl_80383364[14] = "live_Z124.dsp";
const char lbl_80383374[14] = "live_Z125.dsp";
const char lbl_80383384[14] = "live_Z126.dsp";
const char lbl_80383394[14] = "live_Z128.dsp";
const char lbl_803833A4[14] = "live_Z129.dsp";
const char lbl_803833B4[14] = "live_Z130.dsp";
const char lbl_803833C4[14] = "live_Z131.dsp";
const char lbl_803833D4[14] = "live_Z132.dsp";
const char lbl_803833E4[14] = "live_Z133.dsp";
const char lbl_803833F4[14] = "live_Z134.dsp";
const char lbl_80383404[14] = "live_Z135.dsp";
const char lbl_80383414[14] = "live_Z136.dsp";
const char lbl_80383424[14] = "live_Z137.dsp";
const char lbl_80383434[14] = "live_Z138.dsp";
const char lbl_80383444[14] = "live_Z139.dsp";
const char lbl_80383454[14] = "live_Z140.dsp";
const char lbl_80383464[14] = "live_Z141.dsp";
const char lbl_80383474[14] = "live_Z142.dsp";
const char lbl_80383484[14] = "live_Z143.dsp";
const char lbl_80383494[14] = "live_Z144.dsp";
const char lbl_803834A4[14] = "live_Z145.dsp";
const char lbl_803834B4[14] = "live_Z146.dsp";
const char lbl_803834C4[14] = "live_Z147.dsp";
const char lbl_803834D4[14] = "live_Z148.dsp";
const char lbl_803834E4[14] = "live_Z149.dsp";
const char lbl_803834F4[14] = "live_Z150.dsp";
const char lbl_80383504[14] = "live_Z151.dsp";
const char lbl_80383514[14] = "live_Z152.dsp";
const char lbl_80383524[14] = "live_Z153.dsp";
const char lbl_80383534[14] = "live_Z154.dsp";
const char lbl_80383544[14] = "live_Z155.dsp";
const char lbl_80383554[14] = "live_Z156.dsp";
const char lbl_80383564[14] = "live_Z157.dsp";
const char lbl_80383574[14] = "live_Z158.dsp";
const char lbl_80383584[14] = "live_Z159.dsp";
const char lbl_80383594[14] = "live_Z160.dsp";
const char lbl_803835A4[14] = "live_Z161.dsp";
const char lbl_803835B4[14] = "live_Z162.dsp";
const char lbl_803835C4[14] = "live_Z163.dsp";
const char lbl_803835D4[14] = "live_Z164.dsp";
const char lbl_803835E4[14] = "live_Z166.dsp";
const char lbl_803835F4[14] = "live_Z167.dsp";
const char lbl_80383604[14] = "live_Z168.dsp";
const char lbl_80383614[14] = "live_Z169.dsp";
const char lbl_80383624[14] = "live_Z170.dsp";
const char lbl_80383634[14] = "live_Z171.dsp";
const char lbl_80383644[14] = "live_Z172.dsp";
const char lbl_80383654[14] = "live_Z173.dsp";
const char lbl_80383664[14] = "live_Z174.dsp";
const char lbl_80383674[14] = "live_Z175.dsp";
const char lbl_80383684[14] = "live_Z176.dsp";
const char lbl_80383694[14] = "live_Z177.dsp";
const char lbl_803836A4[14] = "live_Z178.dsp";
const char lbl_803836B4[14] = "live_Z179.dsp";
const char lbl_803836C4[14] = "live_Z180.dsp";
const char lbl_803836D4[14] = "live_Z181.dsp";
const char lbl_803836E4[14] = "live_Z182.dsp";
const char lbl_803836F4[14] = "live_Z183.dsp";
const char lbl_80383704[14] = "live_Z184.dsp";
const char lbl_80383714[14] = "live_Z185.dsp";
const char lbl_80383724[14] = "live_Z186.dsp";
const char lbl_80383734[14] = "live_Z187.dsp";
const char lbl_80383744[14] = "live_Z188.dsp";
const char lbl_80383754[14] = "live_Z189.dsp";
const char lbl_80383764[14] = "live_Z190.dsp";
const char lbl_80383774[14] = "live_Z191.dsp";
const char lbl_80383784[14] = "live_Z192.dsp";
const char lbl_80383794[14] = "live_Z193.dsp";
const char lbl_803837A4[14] = "live_Z194.dsp";
const char lbl_803837B4[14] = "live_Z195.dsp";
const char lbl_803837C4[14] = "live_Z196.dsp";
const char lbl_803837D4[14] = "live_Z197.dsp";
const char lbl_803837E4[14] = "live_Z198.dsp";
const char lbl_803837F4[14] = "live_Z199.dsp";
const char lbl_80383804[14] = "live_Z200.dsp";
const char lbl_80383814[14] = "live_Z201.dsp";
const char lbl_80383824[14] = "live_Z202.dsp";
const char lbl_80383834[14] = "live_Z203.dsp";
const char lbl_80383844[14] = "live_Z204.dsp";
const char lbl_80383854[14] = "live_Z205.dsp";
const char lbl_80383864[14] = "live_Z206.dsp";
const char lbl_80383874[14] = "live_Z207.dsp";
const char lbl_80383884[14] = "live_Z208.dsp";
const char lbl_80383894[14] = "live_Z209.dsp";
const char lbl_803838A4[14] = "live_Z210.dsp";
const char lbl_803838B4[14] = "live_Z211.dsp";
const char lbl_803838C4[14] = "live_Z212.dsp";
const char lbl_803838D4[14] = "live_Z213.dsp";
const char lbl_803838E4[14] = "live_Z214.dsp";
const char lbl_803838F4[14] = "live_Z215.dsp";
const char lbl_80383904[14] = "live_Z216.dsp";
const char lbl_80383914[14] = "live_Z217.dsp";
const char lbl_80383924[14] = "live_Z218.dsp";
const char lbl_80383934[14] = "live_Z219.dsp";
const char lbl_80383944[14] = "live_Z220.dsp";
const char lbl_80383954[14] = "live_Z221.dsp";
const char lbl_80383964[14] = "live_Z222.dsp";
const char lbl_80383974[14] = "live_Z223.dsp";
const char lbl_80383984[14] = "live_Z224.dsp";
const char lbl_80383994[14] = "live_Z225.dsp";
const char lbl_803839A4[14] = "live_Z226.dsp";
const char lbl_803839B4[14] = "live_Z227.dsp";
const char lbl_803839C4[14] = "live_Z228.dsp";
const char lbl_803839D4[14] = "live_Z229.dsp";
const char lbl_803839E4[14] = "live_Z230.dsp";
const char lbl_803839F4[14] = "live_Z231.dsp";
const char lbl_80383A04[14] = "live_Z232.dsp";
const char lbl_80383A14[14] = "live_Z233.dsp";
const char lbl_80383A24[14] = "live_Z234.dsp";
const char lbl_80383A34[14] = "live_Z235.dsp";
const char lbl_80383A44[14] = "live_Z236.dsp";
const char lbl_80383A54[14] = "live_Z237.dsp";
const char lbl_80383A64[14] = "live_Z238.dsp";
const char lbl_80383A74[14] = "live_Z239.dsp";
const char lbl_80383A84[14] = "live_Z240.dsp";
const char lbl_80383A94[14] = "live_Z241.dsp";
const char lbl_80383AA4[14] = "live_Z242.dsp";
const char lbl_80383AB4[14] = "live_Z243.dsp";
const char lbl_80383AC4[14] = "live_Z244.dsp";
const char lbl_80383AD4[14] = "live_Z245.dsp";
const char lbl_80383AE4[14] = "live_Z246.dsp";
const char lbl_80383AF4[14] = "live_Z247.dsp";
const char lbl_80383B04[14] = "live_Z248.dsp";
const char lbl_80383B14[14] = "live_Z249.dsp";
const char lbl_80383B24[14] = "live_Z250.dsp";
const char lbl_80383B34[14] = "live_Z251.dsp";
const char lbl_80383B44[14] = "live_Z252.dsp";
const char lbl_80383B54[14] = "live_Z253.dsp";
const char lbl_80383B64[14] = "live_Z254.dsp";
const char lbl_80383B74[14] = "live_Z255.dsp";
const char lbl_80383B84[14] = "live_Z256.dsp";
const char lbl_80383B94[14] = "live_Z257.dsp";
const char lbl_80383BA4[14] = "live_Z258.dsp";
const char lbl_80383BB4[10] = "CAM01.dsp";
const char lbl_80383BC0[10] = "CAM02.dsp";
const char lbl_80383BCC[10] = "CAM03.dsp";
const char lbl_80383BD8[10] = "CAM04.dsp";
const char lbl_80383BE4[10] = "CAM05.dsp";
const char lbl_80383BF0[10] = "CAM06.dsp";
const char lbl_80383BFC[10] = "CAM07.dsp";
const char lbl_80383C08[10] = "CAM08.dsp";
const char lbl_80383C14[11] = "DEMO01.dsp";
const char lbl_80383C20[11] = "DEMO02.dsp";
const char lbl_80383C2C[11] = "DEMO03.dsp";
const char lbl_80383C38[11] = "DEMO04.dsp";
const char lbl_80383C44[11] = "DEMO05.dsp";
const char lbl_80383C50[11] = "DEMO06.dsp";
const char lbl_80383C5C[12] = "muon_05.dsp";
const char lbl_80383C68[12] = "muon_08.dsp";
const char lbl_80383C74[12] = "muon_10.dsp";
const int kVoiceFinalLapCheckpointByTotalLaps[8] = {-1, -1, -1, 1, 2, 3, 4, 4};
const int kVoiceMidRaceCheckpointByTotalLaps[8] = {-1, -1, 0, 1, 2, -1, 3, 4};
static const VoiceList6 leadFar = {{609, 610, 611, 381, 382, 383}};
static const VoiceList5 leadNear = {{612, 613, 614, 384, 385}};
static const VoiceList5 leadClose = {{615, 616, 617, 386, 620}};
static const VoiceList10 chasing = {{618, 275, 619, 620, 621, 387, 388, 389, 390, 391}};
#pragma force_active reset
extern const VoiceList3 lbl_806D97E8;

extern OSTime g_voiceTickTimeHi;
extern OSTime lbl_806D1728;
extern signed char lbl_806D1730;
extern unsigned char lbl_806D1734[8];
extern unsigned char lbl_806D1750;
extern unsigned char lbl_806D1760;
extern unsigned char lbl_806CFD36;
extern signed char lbl_806D178F;
extern const float lbl_806D9818, lbl_806D981C, lbl_806D9820;


#define SINCE(t) ((float)OSTicksToMilliseconds(now - (t)) / 1000.0f)
#define CLIP_PLAYED(id) (clips[id].playCount)

static inline short RaceVoice_DriverCharacter(RaceVoiceData *data, RaceVoiceDriver *driver) {
    int id;
    int character;
    character = driver->character;
    id = driver->id;
    return RaceVoice_Character(data, character, id);
}

static inline void *RaceVoice_Item(int playerIndex) {
    return g_raceEntryArray[playerIndex].item;
}

/* Character voice of every kart that is spinning out. */
static inline unsigned char RaceVoice_PushSpinning(RaceVoiceData *data) {
    unsigned char pushed = 0;
    int i;

    for (i = 0; i < 8; i++) {
        if (g_raceEntryArray[i].state == 5) {
            if (VoiceQueue_Push(RaceVoice_DriverCharacter(data, g_raceEntryArray[i].driver),
                                0x10, 0, 1)) {
                pushed = 1;
            }
        }
    }
    return pushed;
}

/* Announcer update: spin-outs, rival hits, goal line, course lines,
 * overtakes, item hits, boost and the rotating mid-race comments.
 * NonMatching (~98%): the .rodata pool is defined above in section order.
 * The shared .data pool still uses an extern aggregate: MWCC folds the
 * clip-table (+0x1534) and goal-line (+0xF8C) offsets into the index, with
 * residual register allocation differences.  The time divisor is a
 * literal so each check reloads it without preserving f31 across calls. */
#pragma push
#pragma optimization_level 3
void fn_801A6538(void) {
    RaceVoiceData *data = &lbl_80496C38;
    OSTime now = OSGetTime();
    unsigned char pushed;
    int i;
    int count;
    RaceVoiceEntry *entry;
    RaceVoiceEntry *first;
    unsigned char cond;
    float timer;
    short voice;
    VoiceClip *clips;
    VoiceList10 chaseCur;
    VoiceList10 chaseList;
    VoiceList6 farCur;
    VoiceList5 nearCur;
    VoiceList5 closeCur;
    VoiceList6 farList;
    VoiceList5 nearList;
    VoiceList5 closeList;
    VoiceList3 backCur;
    VoiceList3 backList;

    if (!RaceVoice_Queued(0x10) && RaceVoice_PushSpinning(data)) {
        if (g_voiceTickCounter % 2 == 0) VoiceQueue_Push(0x1CB, 0x10, 0, 0);
        else VoiceQueue_Push(0x1CC, 0x10, 0, 0);
        return;
    }

    if (!RaceVoice_CanQueue(0x11)) {
        return;
    }

    if (SINCE(g_voiceTickTimeHi) >= lbl_806D9818) {
        count = 0;
        for (i = 0; i < 8; i++) {
            if (g_raceEntryArray[i].rival != 0 &&
                (g_taMinLapPlayerIndex == i || g_taMinLapPlayerIndex == g_raceEntryArray[i].rival->playerIndex)) {
                lbl_806D1734[i] = 1;
                count = 1;
            }
        }
        if (SINCE(lbl_806D1728) <= lbl_806D9818) {
            if (count) {
                lbl_806D1730++;
            }
        } else {
            lbl_806D1728 = now;
            lbl_806D1730 = 0;
            for (i = 0; i < 8; i++) {
                lbl_806D1734[i] = 0;
            }
        }
        if (lbl_806D1730 >= 4) {
            count = 0;
            for (i = 0; i < 8; i++) {
                if (lbl_806D1734[i]) {
                    count++;
                }
            }
            if (count != 0 && !RaceVoice_Queued(0x11)) {
                if (g_voiceTickCounter % 5 == 0) VoiceQueue_Push(0x1EF, 0x11, 1, 1);
                else if (g_voiceTickCounter % 5 == 1) VoiceQueue_Push(0x1F0, 0x11, 1, 1);
                else if (g_voiceTickCounter % 5 == 2) VoiceQueue_Push(0x1F1, 0x11, 1, 1);
                else if (g_voiceTickCounter % 5 == 3) VoiceQueue_Push(0x1F2, 0x11, 1, 1);
                else VoiceQueue_Push(0x1F3, 0x11, 1, 1);
                switch (count) {
                case 3:
                    if (g_voiceTickCounter % 3 == 0) {
                        VoiceQueue_Push(0x1F7, 0x11, 1, 1);
                    } else if (g_voiceTickCounter % 3 == 1) {
                        VoiceQueue_Push(0x1F8, 0x11, 1, 1);
                        VoiceQueue_Push(0x1F5, 0x11, 1, 1);
                    } else {
                        VoiceQueue_Push(0x1F9, 0x11, 1, 1);
                        VoiceQueue_Push(0x1F6, 0x11, 1, 1);
                    }
                    break;
                case 4:
                case 5:
                case 6:
                    if (g_voiceTickCounter % 3 == 0) VoiceQueue_Push(0x1FA, 0x11, 1, 1);
                    else if (g_voiceTickCounter % 3 == 1) VoiceQueue_Push(0x1FB, 0x11, 1, 1);
                    else VoiceQueue_Push(0x1FC, 0x11, 1, 1);
                    break;
                default:
                    for (i = 0; i < 8; i++) {
                        if (lbl_806D1734[i]) {
                            VoiceQueue_Push(ENTRY_VOICE(&g_raceEntryArray[i]), 0x11, 1, 1);
                        }
                    }
                    if (g_voiceTickCounter % 4 == 0) VoiceQueue_Push(0x1F4, 0x11, 1, 1);
                    else if (g_voiceTickCounter % 4 == 1) VoiceQueue_Push(0x1F5, 0x11, 1, 1);
                    else if (g_voiceTickCounter % 4 == 2) VoiceQueue_Push(0x1F6, 0x11, 1, 1);
                    else VoiceQueue_Push(0x1A8, 0x11, 1, 1);
                    break;
                }
            }
            for (i = 0; i < 8; i++) {
                lbl_806D1734[i] = 0;
            }
            lbl_806D1728 = now;
            lbl_806D1730++;
        }
    }

    if (!RaceVoice_CanQueue(0x12)) {
        return;
    }

    if (!lbl_806D1760) {
        entry = RaceVoice_FindByRank(1);
        if (entry->participant &&
            fn_801A1BD0(data->goalLines + ((g_cupId - 1) * 16 + g_longRoundFlag * 8 + g_reverseRoundFlag * 4),
                        entry)) {
            lbl_806D1760 = 1;
            if (!entry->silent && VoiceQueue_Push(ENTRY_VOICE(entry), 0x12, 0, 1)) {
                VoiceQueue_Push(0x1FD, 0x12, 0, 0);
                return;
            }
        }
    }

    if (g_voiceCupLongRoundTable != 0 && !KartItem_GetByte_f4(g_raceEntryArray[g_taMinLapPlayerIndex].item)) {
        for (i = 0;; i++) {
            if (fn_801A1BD0(g_voiceCupLongRoundTable[i].line, &g_raceEntryArray[g_taMinLapPlayerIndex]) &&
                VoiceQueue_Push(ENTRY_VOICE(&g_raceEntryArray[g_taMinLapPlayerIndex]), 0x13, 0, 1)) {
                if (g_voiceTickCounter % 2 == 0) VoiceQueue_Push(0x1FE, 0x12, 0, 0);
                else VoiceQueue_Push(0x1FF, 0x12, 0, 0);
                break;
            }
            if (g_voiceCupLongRoundTable[i].last == 1) {
                break;
            }
        }
    }

    pushed = 0;
    for (i = 0; i < 8; i++) {
        entry = &g_raceEntryArray[i];
        if (entry->overtaken) {
            if (!pushed) {
                VoiceQueue_Push(0x1CD, 0x14, 0, 1);
            }
            VoiceQueue_Push(ENTRY_VOICE(entry), 0x14, 0, 0);
            pushed = 1;
            entry->overtaken = 0;
        }
    }
    if (pushed) {
        VoiceQueue_Push(0x200, 0x14, 0, 0);
        return;
    }

    for (i = 0; i < 8; i++) {
        entry = &g_raceEntryArray[i];
        pushed = 0;
        if (entry->participant) {
            cond = 0;
            if (g_gameMode == 2) {
                if (entry->player >= 2 && entry->hits >= 2) cond = 1;
            } else {
                if (entry->player >= 3 && entry->hits >= 2) cond = 1;
            }
            if (cond) {
                VoiceQueue_Push(ENTRY_VOICE(entry), 0x1D, 0, 1);
                entry->hits = 0;
                pushed = 1;
            }
        }
        if (pushed) {
            if (g_voiceTickCounter % 6 == 0) VoiceQueue_Push(0x254, 0x1D, 0, 0);
            else if (g_voiceTickCounter % 6 == 1) VoiceQueue_Push(0x255, 0x1D, 0, 0);
            else if (g_voiceTickCounter % 6 == 2) VoiceQueue_Push(0x256, 0x1D, 0, 0);
            else if (g_voiceTickCounter % 6 == 3) VoiceQueue_Push(0x257, 0x1D, 0, 0);
            else if (g_voiceTickCounter % 6 == 4) VoiceQueue_Push(0x258, 0x1D, 0, 0);
            else VoiceQueue_Push(0x259, 0x1D, 0, 0);
            return;
        }
    }

    if (g_gameMode == 0) {
        void *item = RaceVoice_Item(g_taMinLapPlayerIndex);
        if (item != 0 && KartItem_GetBoostArmedAndTimer(item, &timer)) {
            if (!lbl_806CFD36 && timer >= lbl_806D9818 &&
                VoiceQueue_Push(ENTRY_VOICE(&g_raceEntryArray[g_taMinLapPlayerIndex]), 0x1E, 0, 1)) {
                if (g_voiceTickCounter % 3 == 0) VoiceQueue_Push(0x25C, 0x1E, 0, 0);
                else if (g_voiceTickCounter % 3 == 1) VoiceQueue_Push(0x25D, 0x1E, 0, 0);
                else VoiceQueue_Push(0x25E, 0x1E, 0, 0);
                lbl_806CFD36 = 1;
                return;
            }
        } else {
            lbl_806CFD36 = 0;
        }
        if (lbl_806D178F >= 5 &&
            VoiceQueue_Push(ENTRY_VOICE(&g_raceEntryArray[g_taMinLapPlayerIndex]), 0x1E, 0, 1)) {
            VoiceQueue_Push(0x25F, 0x1E, 0, 0);
            lbl_806D178F = 0;
            return;
        }
    }

    if (SINCE(g_voiceTickTimeHi) >= lbl_806D981C) {
        if (!(SINCE(g_voiceLastTime) >= lbl_806D9820)) {
            return;
        }
        entry = &g_raceEntryArray[g_taMinLapPlayerIndex];
        pushed = 0;
        if (entry == 0) {
            return;
        }
        switch (entry->player) {
        case 0:
            first = RaceVoice_FindByRank(1);
            if (first == 0 || first->distance >= 7) {
                farList = leadFar;
                for (i = 0; i < 6; i++) {
                    clips = data->clips;
                    farCur = farList;
                    voice = farCur.v[(lbl_806D1750 + i) % 6];
                    if (!CLIP_PLAYED(voice)) {
                        VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 0);
                        break;
                    }
                }
            } else if (first->distance >= 2) {
                nearList = leadNear;
                for (i = 0; i < 5; i++) {
                    clips = data->clips;
                    nearCur = nearList;
                    voice = nearCur.v[(lbl_806D1750 + i) % 5];
                    if (!CLIP_PLAYED(voice)) {
                        VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 0);
                        break;
                    }
                }
            } else {
                closeList = leadClose;
                for (i = 0; i < 5; i++) {
                    clips = data->clips;
                    closeCur = closeList;
                    voice = closeCur.v[(lbl_806D1750 + i) % 5];
                    if (!CLIP_PLAYED(voice)) {
                        if (voice == 0x267 || voice == 0x268) {
                            VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                            pushed = VoiceQueue_Push(voice, 0x1F, 0, 0);
                        } else {
                            pushed = VoiceQueue_Push(voice, 0x1F, 0, 1);
                        }
                        break;
                    }
                }
            }
            break;
        case 1:
        case 2:
        case 3:
        case 4:
            chaseList = chasing;
            for (i = 0; i < 10; i++) {
                clips = data->clips;
                chaseCur = chaseList;
                voice = chaseCur.v[(lbl_806D1750 + i) % 10];
                if (voice == 0x113) {
                    if (!CLIP_PLAYED(voice + entry->player)) {
                        VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                        pushed = VoiceQueue_Push(voice + entry->player, 0x1F, 0, 0);
                        break;
                    }
                } else if (!CLIP_PLAYED(voice)) {
                    if ((unsigned short)(voice - 0x26A) <= 1 || voice == 0x186 || voice == 0x187) {
                        VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 0);
                    } else {
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 1);
                    }
                    break;
                }
            }
            break;
        default:
            backList = lbl_806D97E8;
            for (i = 0; i < 3; i++) {
                clips = data->clips;
                backCur = backList;
                voice = backCur.v[(lbl_806D1750 + i) % 3];
                if (!CLIP_PLAYED(voice)) {
                    if (voice == 0x26E || voice == 0x26F) {
                        VoiceQueue_Push(ENTRY_VOICE(entry), 0x1F, 0, 1);
                        if (voice == 0x26F) {
                            VoiceQueue_Push(0x118, 0x1F, 0, 0);
                        }
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 0);
                    } else {
                        pushed = VoiceQueue_Push(voice, 0x1F, 0, 1);
                    }
                    break;
                }
            }
            break;
        }
        g_voiceLastTime = now;
        if (pushed) {
            lbl_806D1750++;
        }
    }
}
#pragma pop

