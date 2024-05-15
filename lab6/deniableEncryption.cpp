#include "NTL/ZZ.h"

using std::cout;
using std::endl;
using namespace NTL;

// Шифрування повідомлення
ZZ Encryption(const ZZ &M, const ZZ &K1, const ZZ &K2, const ZZ &p)
{
    ZZ x;
    x = PowerMod(M, K1, p); // Піднесення до степені за модулем: x = M1^K11 mod p1
    x = MulMod(x, K2, p);   // ZZ x = MulMod(const ZZ& a, const ZZ& b, const ZZ& n);
                            // x = (a * b) % n;
    return x;
}

// Розшифрування повідомлення
ZZ Decryption(const ZZ &C, const ZZ &K1m, const ZZ &K2m, const ZZ &p, const ZZ &M)
{
    ZZ x;
    x = MulMod(C, K2m, p);   // ZZ x = MulMod(const ZZ& a, const ZZ& b, const ZZ& n); x = (a * b) % n
    x = PowerMod(x, K1m, p); // Піднесення до степені за модулем : x = tmp^K11m mod   p1
    cout << "Порівняння розшифрованого повідомлення і вихідного...";
    if (x == M)
    {
        cout << "\tOk" << endl;
    }
    else
    {
        cout << "\n\tРозшифроване повідомлення і вихідне не збігаються!" << endl;
        exit(1);
    }
    return x;
}

void doTask(ZZ M1, ZZ M2, ZZ K11, ZZ K12, ZZ K21, ZZ K22, ZZ p1, ZZ p2)
{
    ZZ p1m;        // Зворотне до p1 по модулю p2
    ZZ K11m, K12m; // Зворотні по модулю до K11, K12
    ZZ K21m, K22m; // Зворотні по модулю до K21, K22
    ZZ p2m;        // Зворотне до p2 по модулю p1
    ZZ C, C1, C2;  // Зашифроване повідомлення
    ZZ tmp;
    cout << "\nВихідне значення:" << endl;
    cout << "M1 = " << M1 << " (" << NumBits(M1) << " біт)" << endl;
    cout << "K11 = " << K11 << " (" << NumBits(K11) << " біт)" << endl;
    cout << "K12 = " << K12 << " (" << NumBits(K12) << " біт)" << endl;
    cout << "p1 = " << p1 << " (" << NumBits(p1) << " біт)" << endl;
    cout << "M2 = " << M2 << " (" << NumBits(M2) << " біт)" << endl;
    cout << "K21 = " << K21 << " (" << NumBits(K21) << " біт)" << endl;
    cout << "K22 = " << K22 << " (" << NumBits(K22) << " біт)" << endl;
    cout << "p2 = " << p2 << " (" << NumBits(p2) << " біт)" << endl;

    // Шукаємо зворотне по модулю значення
    K11m = InvMod(K11, (p1 - 1)); // ZZ InvMod(const ZZ& a, const ZZ& n); // x = a^{-1} mod n(0 <= x < n);
    K12m = InvMod(K12, p1);
    K21m = InvMod(K21, (p2 - 1));
    K22m = InvMod(K22, p2);
    cout << "\nЗворотне значення до значень К:" << endl;
    cout << "K11m = " << K11m << " (" << NumBits(K11m) << " біт)" << endl;
    cout << "K12m = " << K12m << " (" << NumBits(K12m) << " біт)" << endl;
    cout << "K21m = " << K21m << " (" << NumBits(K21m) << " біт)" << endl;
    cout << "K22m = " << K22m << " (" << NumBits(K22m) << " біт)" << endl;

    // *** Шифрування повідомлення*** //
    C1 = Encryption(M1, K11, K12, p1); // Шифруємо повідомлення 1
    cout << "\nЗашифроване повідомлення1: ((M1^K11)*K12) mod p1 = " << C1 << endl;
    C2 = Encryption(M2, K21, K22, p2); // Шифруємо повідомлення 2
    cout << "Зашифроване повідомлення2: ((M2^K21)*K22) mod p2 = " << C2 << endl;
    // Рішення китайської теореми про залишки (КТЗ)
    tmp = p1;
    cout << "\nКТО=" << CRT(C1, tmp, C2, p2) << endl; // CRT повертає 1, якщо значення "a" змінилося
    cout << "1-а ітерація C1: " << C1 << "\ttmp: " << tmp << endl;
    if (C1 < 0)
        C = (C1 + tmp);
    else
        C = C1;
    cout << "Криптограма (результат рішення КТЗ): C = " << C << " (" << NumBits(C) << "бит)." << "\tПеревірка:" << endl;
    cout << "\tC mod p1 = " << C % p1;
    cout << "\tC mod p2 = " << C % p2 << endl;
    // *** Перевірка результату шляхом розшифрування отриманої криптограми *** //
    cout << "\nРасшифрування повідомлення 1:" << endl;
    tmp = Decryption(C, K11m, K12m, p1, M1); // Розшифровуємо повідомлення1
    cout << "\nРасшифрування повідомлення 2:" << endl;
    tmp = Decryption(C, K21m, K22m, p2, M2); // Розшифровуємо повідомлення1
}

int main()
{
    // *** Оголошення змінних*** //

    // Параметри для повідомлення1
    ZZ M1;       // Вихідне повідомлення
    ZZ p1;       // Просте число
    ZZ K11, K12; // Секретні ключі

    // Параметри для повідомлення 2
    ZZ M2; // Вихідне повідомлення
    ZZ p2; // Просте число

    ZZ K21, K22; // Секретні ключі

    // *** Ініціалізація вхідних значень*** //
    M1 = 250;
    K11 = 191;
    K12 = 154;
    p1 = 599;
    M2 = 217;
    K21 = 173;
    K22 = 217;
    p2 = 829;

    // Виконання завдання 1 8 bits
    cout << "1. 8 bits" << endl;
    doTask(M1, M2, K11, K12, K21, K22, p1, p2);

    // *** Ініціалізація вхідних значень*** //
    M1 = conv<ZZ>("1011109662256038274933924");
    K11 = conv<ZZ>("804392430191507639660877");
    K12 = conv<ZZ>("1056896793610305593846855");
    p1 = conv<ZZ>("1070991298289515186815972969359");
    M2 = conv<ZZ>("640211350424735669957646");
    K21 = conv<ZZ>("675811907529545598518929");
    K22 = conv<ZZ>("1198539389397647895353097");
    p2 = conv<ZZ>("726620101735479544996821229223");

    // Виконання завдання 2 80 bits
    cout << "2. 80 bits" << endl;
    doTask(M1, M2, K11, K12, K21, K22, p1, p2);

    // *** Ініціалізація вхідних значень*** //
    M1 = conv<ZZ>("635569459000106941985840635892589203048601607239091331084162604544733825749526468681451070331812598208085231273567972888665855667272465006133756842393863753519165196485157108262660524108888776846175068935929314435048805030854890219710008988067869286322611827116903350494783861845090309879472941559778324889049346639990177503415559955960558143117840423991768253935240075319396280749956529771504741623421557311055891091262756091389716507735691624454434878452174382453493235550243455213826053922547636334441578573353361111566442801719868319807479964574840964178744873137376127895887770085917577501243839936779485472687996946310384318396659655168316223270510465314488492170629274881253670002838265898292920549606402623069540365328765101187791208449330812836673540633329996729224413795536975303329854766278286549805865148085356219477362976564670941293448547678189224426363753754267646860298401737355235957958650373357414378618987690995795955630878550589817463925926014261220991806352651019716320453496901815606252458720287056552747141910924400420971517697294171284481680527708915177289730546371760214419854822680623082786148155033597503831491496138461436609185711380540910165836493337153616511883539425327544826386213149198354290933113931");
    K11 = conv<ZZ>("587011698322043872170557899406617617790536598016809492899603679083297607347608185831026712451494082068357782860715225097975112202005833227783592830468646473083792390617063654282177472396044392154176499657993146518031705549828089219783686295974913256512648104735119177412303048579193846508745016451476455065402564182944111525875940580509562103236288711913678459042275302625368338433920611701416552408881390827683214373082113196906203280694874088272291548446849371729887556617624498677786332068627982989293915864675872633335214705861948627583682117559250341616099120652726196729353045128991940663153919923280837445614194069116853470564103069114215746492551922561096016792003681232960116766723464285564807361255263997490228938435428757976815432841203647995355527233716403639643114363348160729676571703289126449613501556821759085189774483816089500685700788122194207871922947628424838431127633327548686498798148831752342522506710723713768520849911083361299773335686257020020588751789915714830051839764486074312759722656779601412127998172150942963571167681035434170058412211440182989522887699385414719950709847412886779565883832657386403976018699122967673104106774681153754505160137265546620998383013128110251305037224054661946789765936141");
    K12 = conv<ZZ>("639799557291176234901915896277099813484381516461390098335214083167099338401785802998621855385733403402590847347987727299966403599565031227682670300941697197682403073963173312978632958495089085445613758170548788543523622588339520027031628307412945736547613468378240246314195398716647275167793281529181787115443374540020999614113978051129147540136047582006750145803032733436326347114387226171439243758224503205943273881043770217482044892495394186279646213861837827278434373384591759784013684289646341163252599935494621544140092736570273751929451920205293526924475551025082629506334234077169702979342692133524771791469268036003447590997311043838661938356246051432212720425217361920368608799567166342716663732368283130009310676410959334351484175404836258366504259859789707162943190742890660819472224833492759075817775606617809017427958337062021689916767948935125272219144450083061224603305024876395638955115086893252778568620993943911632867735093098353275842619386864712749978849301516538853447253571344395712351680976347495339773662639417765317195126162370879174773056886943945569910644733401047847096066719847153036569097036636167446866620863209754007427161227843812336147127779809391701741471107564353008856388636601189109428054664651");
    p1 = conv<ZZ>("14203984739138783183265012151643228712307137322260213417023792389751233853880830865019056016305090602835121820985197824742855639812617066127099431552072824067878987078319412315372321966886080691121365380656093224412020718028293872552534507229333181002250973814806333438181031920779858097271583111209209795495702521220039236377797005069834696810855485299591369964019914818665311256115255941331084169415114892682933142869811475937050961150228928503623613588035247985374824337654988551098175745234221775815581989970021121982898849670500431044294466372013946657048912239663295686198212239739538012261166316801291102974344601708631851930419776251829977465872787207071064636632367288086366629711277632762188658375464899004888859367251649196958605619401391358755520150530009062520538338639559809333942026560213623753138037731943115228399625079015905089030766516875260045068351761489711373743135898890176636966437030242559424132201310694434874198324842317664211596916088658062716932661806887760823858875480951048712196748796997367816093247964653661202246379183378090725946438356467464986032600704222954768333594330941151259010884130531479759064098512436097420494440558178733653190938271212269234991073086206944343837753966738345891139229634453");
    M2 = conv<ZZ>("1032744924476742594176922179466795571867854309465704532846757247510918639626301014175140473471454586696124448157499724752856503478980073603743273835597491174564005233977133689500364996344744567654523271566808467110767977028267186829712471892084571744255509723511372160677563482535358917024956155011204226166238875139605662247500210093702547891165058735084768116385421183489634834667871257978750030020828034343536338821637174847395577840752167858513008500744814662176337596191820215957609236278317085514520765122401899403175616554134819931643159100350336540779374802988248600495581426781051340738819498641210385155036982942460734243601029124661255092061274797601431610224105082589473886741031314691779857625404467439161635117649885154700887841517401300019593419941249618723796529144930975452992357653261202950843858501308246206306525988540571071679004145892006598272309846164459821999653318823214449882616425365061634895829057212712561188992281765315411526914632976535930180707071056332099707278997623194589173004384343849518236800105560564192841419908920265267011812090407819238121002920447815833778141269588328484982818699024150810328198110517517655263662324138518588869160540294945880256872316331872355917186635447460455168955054363");
    K21 = conv<ZZ>("639620083236258994560186977222322240017080806633211681890806376892214531145835872098860480410353980790688250306411050103659979501122474732562563659268618609205314132097104599768228285198464927329643783415625803837749235607212276443554839475342200584579505910071132298176332863334624457174996134769423556320547374929683059692315366172282789125106836789605878816517676490825471078633050714304495750387504466773281554044884099940366581683143971353117399675363210513705779736658661893637561502767456844142191305791661391476039342579490227587573994953699485090498852512984898253380721883369899611896789145528799486754018219383766536986261920557247692930481671883026691482195259628155161573120987388057505224563602486215664536270465141076142566710277059710053525314681353469879919518466761149969937288342579169818668376947466781540228943806068054954738535643820913074639828315341460595944449229440073314407917868025581179506717306689179807940657226635213555435374581417462441454656888362733198069387638348025186308208172139472065243426057420783569649135001440125103458838292366223273123187308985428205249095827944142708996276880855685701739920423452810751689803385445406537568542216302034515365397437289213448119159456986067266481928493097");
    K22 = conv<ZZ>("819122286199467278497287414518265449060338297470303970995994622563901779967737714173982192530391401012620898454607198933480795350020112604666584953724329399596261558638560041245852489463314117772425078096884235189148392981752682459987349548011635926656332372157240630341355551141784367740318011790639570697905191619754724371536639959630207591992846381801693458945180314870722505949246316904221868625917479930240642339622318265458870259868012976418012656005236817690220824056259021041207039527565148845528792492205878474747574622253898255986666649487446071078608582583451393401539397776341509884663420200691615548545620706792129298238580075588664800788512661472989997177499002674076344289484942304273024767509462835147703998174904002418448025346927706421618860920261715501295186720519295999936424661232177293852754557412090220351945796784326056384068884755404524892390645628017684800690669859627325911834401899884893397032274388260326252505459137289590137000904069385724299763271850092743631801476510281779115342081792803955763419289979043698020549109112368537080576491010711121488116597266563134897131139210089332833265433649597782667020819875258274378050215908195297459824223912904689547016043358163943330530713140780064834174143623");
    p2 = conv<ZZ>("8665227369679389344851849738163685881207275877961344511753083413236127149475548265670153719545482355856039787192514820120224713137838263475822582991774088589931616841110032134155548618122866439768430541031951424084014620464758815937229076494792607930270900293608445631794582203323558708165292575784521501135556448123290911189865824189910907040740433777029243351927062757873306712752274616572131864870235077121261644513111459511862367668051467119092536316880564061902329603267557209194278167244887057060198939617334722695434719541325504085686763677814200328027836987897955072805802405957658046590720898260558534683771761412064122808430463105072159620653136404789623855423387142828954434495164354127701874220685982795470998000637717015306178611837889406562929835402968200369147725750528249864179762262398693193060112084628483838212155889181913675776651939775259640607059435790975203686858804773934891943257100539823485460400551815534763019454076986793819744917098275737169026005239989765679488807444434994005881256037744286363651084333218559879630578724868802319835586482541142003278397021319548978225076161638465478029900450862994975551111604786362486012878184065750117366479649825054912086549558395274630604264756898028847953715410717");

    // Виконання завдання 3 4096 bits
    cout << "3. 4096 bits" << endl;
    doTask(M1, M2, K11, K12, K21, K22, p1, p2);

    return 0;
}