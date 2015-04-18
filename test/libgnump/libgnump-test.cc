#include <gtest/gtest.h>

#include <iostream>
#include <gmpxx.h>

TEST(GNUMPLibTest, modulo) {
  mpz_class big1 =
      78329166105986438001881453303746828693497318678553783528817511246296543097866809263662010895124816875566758003582944712849068007863934520544742706588852395845946773240778249875527119260078778873582105250889195966978223912954828455925425101325843996312260593152935277805346303655508895683585098333769852175501520423266134083946017922264269570544968459007461760197727002233229426876197929990078566165627037666991396861473867843582587255056585890447962235632514178101175631279625632025125038791327472906620216307748771227705894976141034761937789106887524256341598886963477609416266949872530925858864694675586914596276785487943493420811929887653506570646657712570264827365173487676325850500639661380994122731452771403134358801118036935159498709288504970866384570333012335056793820466320984366613733721574265088779891745179604617949076975159222254676583715921133046200555970925618986728792873178286611224103547328442718710269503125714233054783592497892633609932260491788770043979492484699706809960190133096861328883740059174443763374680285483957487416310567616638492880977997266368461464023809275183069496268315561128880880894735339223639300423323607734456442725097681010039229500491236863334870219058630352507706768285353125530236564275125_mpz;
  mpz_class big2 =
      9068007863934520544742706588852395845946773240778249875527119260078778873582105250889195966978223912954828455925425101325843996312260593152935277805346303655508895683585098333769852175501520423266134083946017922264269570544968459007461760197727002233229426876197929990078566165627037666991396861473867843582587255056585890447962235632514178101175631279625632025125038791327472906620216307748771227705894976141034761937789106887524256341598886963477609416266949872530925858864694675586914596276785487943493420811929887653506570646657712570264827365173487676325850500639661380994122731452771403134358801118036935159498709288504970866384570333012335056793820466320984366613733721574265088779891745179604617949076975159222254676583715921133046200555970925618986728792873178286611224103547328442718710269503125714233054783592497892633609932260491788770043979492484699706809960190133096861328883740059174443763374680285483957487416310567616638492880977997266368461464023809275183069496268315561128880880894735339223639300423323607734456442725097681010039229500491236863334870219058630352507706768285353125530236564275125_mpz;
  mpz_class expected =
      5240445567026831643976076160972970486112847343674617749170524556344144395950046377772134125120583921545716198030340995296249757150262611108945200279928611472240738678971724534604801366180951886324452916051505320200575022639040559508317772830736686513348805528256157302684926324219487048981025078913083014231831954132503694838640728108610571800303757886579522009015469000102160534001513717054167378107068191786901788042145460409774035825864506513095971088395691998831165632424700108398554630994353224602391015144922881778202770933314388052333295167425474372813220956830340205073948519572336508446374262795147678292435967851380093412680511269404451617936656163175330404630405472088129661463377672032187911016870766203027947576885220755361783712568886339134396773303278307622625356158495076232625910003802003534662025454164263116318729049489156584677458339274997011330603000467428608256214236660630791912413689335230039972456460279083714910168751182155824071238890710556586849826907703780093864004837580738013660508242379790388860170331258184064923550014679931827171668194252207089382117684372121393815908502018477500_mpz;
  mpz_class answer = big1 % big2;
  EXPECT_EQ(expected, answer);
}
